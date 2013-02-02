/****************************************************************************************
*
*   This file is part of the ChartButler Project.
*   Copyright (C) 2012 Joerg Pauly
*   All Rights reserved
*
*   ChartButler ist Freie Software: Sie können es unter den Bedingungen
*   der GNU Lesser General Public License, wie von der Free Software Foundation,
*   Version 3 der Lizenz oder (nach Ihrer Option) jeder späteren
*   veröffentlichten Version, weiterverbreiten und/oder modifizieren.
*
*   Dieses Programm wird in der Hoffnung, dass es nützlich sein wird, aber
*   OHNE JEDE GEWÄHRLEISTUNG, bereitgestellt; sogar ohne die implizite
*   Gewährleistung der MARKTFÄHIGKEIT oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.
*   Siehe die GNU Lesser General Public License für weitere Details.
*
*   Sie sollten eine Kopie der GNU Lesser General Public License zusammen mit diesem
*   Programm erhalten haben. Wenn nicht, siehe <http://www.gnu.org/licenses/>.
*
*****************************************************************************************/
/****************************************************************************************
*
*   CNetworkManager.cpp
*   CNetworkManager regelt den kompletten Datenverkehr mit dem GAT24.de-Server.
*
*****************************************************************************************/

#include "cnetworkmanager.h"
#include "coptions.h"
#include "cmainwindow.h"
#include "cstatus.h"
#include "globals.h"

CNetworkManager::CNetworkManager(QObject *parent) :
    QObject(parent)
{
    // Save the parent.
    m_parent = parent;
    m_dlProgress = new QProgressDialog();    
    // Connect the Request's finished()-signal to our slot
    connect(&m_nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(dlFinished(QNetworkReply*)));
    connect(this, SIGNAL(chartDlFinished()),SLOT(onChartDlFinished()));
    connect(this,SIGNAL(fieldDlFinished()),SLOT(dlNextField()));
    checkForUpdate();
    // Get a settings object and extract login data
    QSettings l_opts(gCOMPANY, gAPP);
    m_uid = l_opts.value("UID").toString();
    m_pw = l_opts.value("PW").toString();

    // Log on to get a SID
    getSID();
}

void CNetworkManager::updateCharts()
{
    /* Check the Changes Site
       Check if some of the changed charts are in db
       Check if change is younger than stored chart
       Download chart, if necessary */
    m_action = ACT_UPD;
    // Clean Up list of new Charts...
    m_newCharts = new QList<QString>();
    QString lsUrl(AMENDURL);
    QString lcmp("SID=");
    int lcnt = lsUrl.indexOf(lcmp)+4;
    lsUrl.insert(lcnt,m_sid);
    QUrl lUrl(lsUrl);
    downloadData(&lUrl);
}

void CNetworkManager::updateField(QString *pICAO)
{
    m_action = ACT_UPD;
    m_newCharts = new QList<QString>();
    m_ICAO = *pICAO;
    QString lsUrl(ICAOURL);
    lsUrl.append(pICAO);
    lsUrl.append("&SID=");
    lsUrl.append(m_sid);
    QUrl* lUrl = new QUrl(lsUrl);
    downloadData(lUrl);
}

void CNetworkManager::getChart(QString* pICAO)
{
    /* Check if there are charts for the field
       Create directory
       Download the Charts
       Store chart's data in db */
    m_action = ACT_NEW;
    // Clean up list of new charts
    m_newCharts = new QList<QString>();
    m_fieldList = new QList<QString>();
    m_fieldList = parseFields(*pICAO);
    m_fieldInSequence = 0;
    dlNextField();
}

void CNetworkManager::getChartFromList()
{
    m_action = ACT_UPD;
    m_newCharts = new QList<QString>();
    m_fieldInSequence = 0;
    dlNextField();
}

void CNetworkManager::downloadData(QUrl* pUrl, bool pShowState)
{
    // Set URL in request
    m_request.setUrl(*pUrl);
    // Send request
    QNetworkReply* lReply = m_nam.get(m_request);
    connect(lReply, SIGNAL(downloadProgress(qint64,qint64)), SLOT(dlProgress(qint64,qint64)));

    if(pShowState)
    {
        m_dlProgress = new QProgressDialog();
        m_dlProgress->setCancelButton(0);
        m_dlProgress->setLabelText("Lade Datei");
        m_dlProgress->setValue(0);
        m_dlProgress->setAutoClose(true);
        m_dlProgress->exec();
    }
}

void CNetworkManager::getSID()
{
    QString lLogin("txtBenutzername=");
    lLogin.append(m_uid);
    lLogin.append("&txtPasswort=");
    lLogin.append(m_pw);
    lLogin.append("&btnSubmitLogin=Login");
    QUrl lUrl;
    lUrl.setUrl(LOGINURL);
    m_request.setUrl(lUrl);
    m_request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    m_nam.post(m_request,lLogin.toAscii());
}

void CNetworkManager::dlFinished(QNetworkReply* pReply)
{
    m_dlData = pReply->readAll();
    QString lcontent = pReply->header(QNetworkRequest::ContentTypeHeader).toString();
    QString ldlData(m_dlData);

    if(ldlData.contains("Eingeloggt"))
    {
        extractSID();
        return;
    }

    if(ldlData.contains("Karten und Daten zum"))
    {
        GetAmendedFieldsList();
        return;
    }

    if(ldlData.contains("Zu diesem Flugplatz sind keine Karten vorhanden"))
    {
        CMainWindow* lparent = (CMainWindow*)m_parent;
        QMessageBox *lmsg = new QMessageBox(lparent);
        lmsg->setParent(lparent);
        lmsg->setWindowTitle("Keine Karten gefunden");
        lmsg->setText("Zu diesem Platz wurden keine Karten gefunden!");
        lmsg->setInformativeText("Auf dem GAT24-Server konnten keine Karten zu Ihrer Auswahl gefunden werden.");
        lmsg->setDefaultButton(QMessageBox::Ok);
        lmsg->setIcon(QMessageBox::Information);
        lmsg->exec();
        delete lmsg;
        return;
    }

    if(ldlData.contains(">Karten - AIP VFR Deutschland</td>"))
    {
        getFieldName(&ldlData);
        QList<QString>* ldlList = getLinkList(&ldlData);
        getNewAirfield(&m_ICAO, ldlList);
    }

    if(lcontent == "application/x-download")
    {
        if(m_action == ACT_NEW)
        {
            QFile* lChartFile = new QFile();
            QString lAttachment(pReply->rawHeader("Content-Disposition"));
            QString lLimiter("\"");
            QString lFileName(getTextBetween(&lAttachment, &lLimiter, &lLimiter, 0)->text);            
            QString lCFPath(m_FieldDir);
            if(lCFPath.right(1) != "/")
            {
                lCFPath.append("/");
            }
            lCFPath.append(lFileName);
            lChartFile->setFileName(lCFPath);
            lChartFile->open(QFile::WriteOnly);
            lChartFile->write(m_dlData);
            lChartFile->flush();
            lChartFile->close();
            storeChartInDb(&lFileName, &lCFPath);
            m_newCharts->append(lCFPath);
            emit chartDlFinished();
        }        
    }

    if(ldlData.contains("cbver"))
    {
        QString lStart("cbver");
        QString lEnd("..");
        txtPos lMaj = *getTextBetween(&ldlData,&lStart,&lEnd,0);
        txtPos lMin = *getTextBetween(&ldlData,&lEnd,&lEnd,lMaj.pos);
        txtPos lRev = *getTextBetween(&ldlData,&lEnd,&lEnd,lMin.pos);
        bool upd = false;
        if(lMaj.text.toInt() > MAJOR)
        {
            upd = true;
        }
        if((lMaj.text.toInt() == MAJOR) & (lMin.text.toInt() > MINOR))
        {
            upd = true;
        }
        if((lMaj.text.toInt() == MAJOR) &
           (lMin.text.toInt() == MINOR) &
            (lRev.text.toInt() > REV))
        {
            upd = true;
        }

        if(upd)
        {
            QMessageBox *lBox = new QMessageBox();
            lBox->setWindowTitle("Update verfügbar");
            lBox->setText("Es ist ein Update verfügbar");
            QString lver;
            lver = "Installierte Version: ";
            lver.append(QString::number(MAJOR));
            lver.append(".");
            lver.append(QString::number(MINOR));
            lver.append(".");
            lver.append(QString::number(REV));
            lver.append("\n");
            lver.append("Verfügbare Version: ");
            lver.append(lMaj.text);
            lver.append(".");
            lver.append(lMin.text);
            lver.append(".");
            lver.append(lRev.text);
            lver.append("\n\n");
            lver.append("Wollen Sie zur Download-Seite geleitet werden?");
            lBox->setInformativeText(lver);
            lBox->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            lBox->setButtonText(QMessageBox::Yes, "Klar, man will ja up2date bleiben!");
            lBox->setButtonText(QMessageBox::No, "Nö, wieso? Läuft doch...");
            lBox->setDefaultButton(QMessageBox::Yes);
            if(lBox->exec() == QMessageBox::Yes)
            {
                QUrl lUrl("http://megamover.de/luftfahrt-nur-fliegen-ist-schoener/softwarefuerdenfliegeralltag/chartbutler/index.html");
                QDesktopServices::openUrl(lUrl);
            }
        }
    }
}

void CNetworkManager::dlProgress(qint64 pRcvd, qint64 pTotal)
{
    if(pTotal == -1)
    {
        return;
    }
    m_dlProgress->setValue(pRcvd * 100 / pTotal);    
    m_dlProgress->setAutoClose(true);
}

void CNetworkManager::onChartDlFinished()
{
    if(m_chartInSequence < m_chartsToLoad)
    {
        QUrl lUrl(m_linkList->at(m_chartInSequence));
        m_chartInSequence++;
        downloadData(&lUrl,true);
    }
    else
    {
        emit fieldDlFinished();
    }
}

void CNetworkManager::dlNextField()
{    
    if(m_fieldInSequence < m_fieldList->count())
    {
        m_ICAO = m_fieldList->at(m_fieldInSequence);
        QString lUrlString(ICAOURL);
        lUrlString.append(m_ICAO);
        lUrlString.append("&SID=");
        lUrlString.append(m_sid);
        QUrl lUrl(lUrlString);
        downloadData(&lUrl);
    }
    m_fieldInSequence++;
}

void CNetworkManager::extractSID()
{
    QString lStream(m_dlData);
    QString lStart("SID=");
    QString lEnd("\">Mitglied");
    m_sid = getTextBetween(&lStream, &lStart, &lEnd, 0)->text;
    CMainWindow* lparent = (CMainWindow*) m_parent;
    QMessageBox *dlgLogin = new QMessageBox(lparent);
    dlgLogin->setStandardButtons(QMessageBox::Ok);
    if(m_sid == "0")
    {
        dlgLogin->setText("Ihre Sitzung wurde vom GAT24-Server nicht authorisiert.");
        dlgLogin->setDetailedText("Der GAT24-Server konnte keine Sitzungs-ID zuteilen.\nMeist liegt dies an fehlenden oder ungültigen Login-daten.");
        dlgLogin->setInformativeText("Bitte überprüfen Sie Ihre Zugangs-Daten.");
        dlgLogin->setWindowTitle("Authorisierungs-Fehler!");
    }
    else
    {
        dlgLogin->setText("Verbindung erfolgreich aufgebaut");
        QString lSidInfo("Sitzungs-ID:\n");
        lSidInfo.append(m_sid);
        dlgLogin->setInformativeText(lSidInfo);
        dlgLogin->setWindowTitle("Server-Verbindung");
    }
    dlgLogin->exec();
}

void CNetworkManager::getNewAirfield(QString *pICAO, QList<QString> *pLinkList)
{
    m_lastRetrieve = false;
    CMainWindow* lparent = (CMainWindow*)m_parent;
    CDatabaseManager *ldbman = lparent->GetDBman();
    CDatabaseManager::s_Field* pFld = new CDatabaseManager::s_Field();
    if(ldbman->GetField(*pICAO, pFld) == true)
    {
        QMessageBox* lbox = new QMessageBox(lparent);
        lbox->setWindowTitle("Flugplatz vorhanden");
        lbox->setText("Der Flugplatz ist bereits gespeichert!");
        lbox->setDefaultButton(QMessageBox::Ok);
        lbox->setIcon(QMessageBox::Information);
        lbox->exec();
        delete lbox;
        return;
    }
    QString lFullName(m_ICAO);
    lFullName.append(" - ");
    lFullName.append(m_FieldName);

    QSettings* settings = new QSettings(gCOMPANY, gAPP);
    QString CPath(settings->value("ChartPath").toString());
    QDir* lChartDir = new QDir(CPath);
    lChartDir->mkdir(lFullName);
    CPath.append("/");
    CPath.append(lFullName);
    lChartDir = new QDir(CPath);
    CPath.append("/");
    m_FieldDir = CPath;
    m_FID = ldbman->AddField(m_ICAO, m_FieldName, m_FieldDir);
    lparent->SetupTree();

    m_chartsToLoad = pLinkList->count();
    m_chartInSequence = 0;
    m_linkList = pLinkList;
    emit chartDlFinished();
}

QList<CDatabaseManager::s_Field>* CNetworkManager::GetAmendedFieldsList()
{
    m_fieldList = new QList<QString>();
    QList<CDatabaseManager::s_Field> *lFldList = new QList<CDatabaseManager::s_Field>;
    QString ldlData(m_dlData);
    QString lCmp("Karten und Daten zum ");
    txtPos* lDate = getTextAfter(&ldlData, &lCmp, 10, 0);
    m_lastAmmended = QDate::fromString(lDate->text,"dd.MM.yyyy");

    // Datum der letzten Änderung in CStatus anzeugen...
    CMainWindow* lparent = (CMainWindow*) m_parent;
    CStatus* status = new CStatus(lparent);
    QString lstatus("Änderungen vom ");
    lstatus.append(m_lastAmmended.toString("dd.MM.yyyy"));
    status->setWindowTitle("Prüfung auf geänderte Karten");
    status->show();
    status->setHeader(&lstatus);
    status->clearList();
    CDatabaseManager* ldbman = lparent->GetDBman();
    txtPos *lFldDef;
    int lLastPos = lDate->pos;
    while(true)
    {
        QString lFullName;
        QString* lStart = new QString("&ICAO=");
        QString* lEnd = new QString("' target='");
        lFldDef = getTextBetween(&ldlData,lStart, lEnd,lLastPos);
        CDatabaseManager::s_Field *lFld = new CDatabaseManager::s_Field();
        if(lFldDef->pos < lLastPos)
        {
            break;
        }
        lFullName = lFldDef->text;
        lFld->IACO = lFldDef->text;
        lStart = new QString("left\">");
        lEnd = new QString("</td>");
        lFldDef = getTextBetween(&ldlData, lStart, lEnd, lFldDef->pos);
        delete lStart;
        delete lEnd;
        lFullName.append(" - ");
        lFullName.append(lFldDef->text);        

        CDatabaseManager::s_Field *lFieldCheck = new CDatabaseManager::s_Field();
        QString lState;        
        QTreeWidgetItem *lTopItem = new QTreeWidgetItem();
        lTopItem->setText(0,lFullName);
        if(ldbman->GetField(lFld->IACO,lFieldCheck))
        {
            lState = "...im Abo; wird geprüft.";
            lTopItem->setText(1,lState);
            status->appendList(lTopItem);
            QTreeWidgetItem *lChildItem = new QTreeWidgetItem();
            if(ldbman->BrowseCharts(lFieldCheck->ID))
            {
                CDatabaseManager::s_Chart *lchart = ldbman->GetActualChart();
                if(lchart->Date < m_lastAmmended)
                {
                    lState = "...wird erneuert!";                    
                    m_fieldList->append(lFld->IACO);
                }
                else
                {
                    lState = "...ist aktuell!";                                        
                }
                lChildItem->setText(1, lState);
                status->appendList(lChildItem);
            }
        }
        else
        {                        
            lState = "...übersprungen";
            lTopItem->setText(1, lState);
            status->appendList(lTopItem);
        }
        lFld->Name = lFldDef->text;
        lFldList->append(*lFld);
        lLastPos = lFldDef->pos;
    }
    getChartFromList();
    return lFldList;
}



CNetworkManager::txtPos* CNetworkManager::getTextBetween(QString* pSource, QString* pStart, QString* pEnd, int pStartPos = 0)
{
    txtPos* lps = new txtPos();
    int lStart = pSource->indexOf(*pStart, pStartPos) + pStart->length();
    if(lStart == -1)
    {
        lps->pos = -1;
        return lps;
    }
    int lEnd = pSource->indexOf(*pEnd,lStart);
    if(lEnd == -1)
    {
        lps->pos = -1;
        return lps;
    }
    lps->text = pSource->mid(lStart,lEnd-lStart);
    lps->pos = lEnd;
    return lps;
}

CNetworkManager::txtPos* CNetworkManager::getTextAfter(QString* pSource, QString* pStart, int pLen, int pStartPos = 0)
{
    txtPos* lps = new txtPos();
    int lStart = pSource->indexOf(*pStart, pStartPos) + pStart->length();
    if(lStart == -1)
    {
        lps->pos = -1;
        return lps;
    }
    lps->text = pSource->mid(lStart,pLen);
    lps->pos = lStart + pLen;
    return lps;
}

QStringList *CNetworkManager::getLinkList(QString *pStream)
{
    QStringList* lLinkList = new QStringList();
    int lpos = pStream->indexOf("pdfkarten.php?&icao=");
    if(lpos == -1)
    {
        return 0;
    }
    int fstlpos = lpos;
    while(lpos >= fstlpos)
    {
        QString lStart("pdfkarten.php?&icao=");
        QString lEnd("&");
        txtPos* chartBuf = getTextBetween(pStream, &lStart, &lEnd, lpos);
        lpos = chartBuf->pos;
        if(chartBuf->text.contains("W3C"))
        {
            break;
        }
        QString lhdr("http://www.gat24.de/dokumente/briefing/flugplaetze/pdfkarten.php?&icao=");
        lhdr.append(chartBuf->text);
        lhdr.append("&SID=");
        lhdr.append(m_sid);
        lLinkList->append(lhdr);
    }
    return lLinkList;
}

void CNetworkManager::getFieldName(QString *pStream)
{
    QString lStart("style=\"width:300px\">");
    QString lEnd("</td>");
    m_FieldName = getTextBetween(pStream, &lStart, &lEnd, 0)->text;
    m_FieldName.replace(m_FieldName.indexOf("/"),1,"-");
    m_FieldName = m_FieldName.toLower();
    QChar lfst(m_FieldName.at(0).toUpper().toAscii());
    m_FieldName.replace(0,1,QString(lfst));
    int i = m_FieldName.indexOf("-");
    if(i != -1)
    {
        QChar list(m_FieldName.at(i+1).toUpper().toAscii());
        m_FieldName.replace(i+1,1,QString(list));
    }
}

void CNetworkManager::storeChartInDb(QString* pFileName, QString* pPath)
{
    CMainWindow* lparent = (CMainWindow*)m_parent;
    CDatabaseManager* ldbman = lparent->GetDBman();
    ldbman->AddChart(m_FID, *pFileName, *pPath, QDate::currentDate());
    lparent->SetupTree();
}


QList<QString> *CNetworkManager::parseFields(QString pICAO)
{
    pICAO.append("  ");
    QList<QString> *lList = new QList<QString>();
    int cnt = 0;
    QString *lChr = new QString();
    do
    {

        if((pICAO.mid(cnt,1) != " ") &
                (pICAO.mid(cnt,1) != ",") &
                (pICAO.mid(cnt,1) != ";") &
                (pICAO.mid(cnt,1) != "-"))
        {
            lChr->append(pICAO.mid(cnt,1));
        }
        else
        {
            if(lChr->length() == 4)
            {
                lList->append(*lChr);
                lChr = new QString();
            }
        }
        cnt++;
    } while(cnt <= pICAO.length());
    return lList;
}

void CNetworkManager::checkForUpdate()
{
    QUrl lUrl("http://www.megamover.de/downloads/cb/version.txt");
    downloadData(&lUrl);
}
