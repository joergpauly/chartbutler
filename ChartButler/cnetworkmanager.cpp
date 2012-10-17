/****************************************************************************************
*
*   This file is part of the ChartButler Project.
*   Copyright (C) 2012 Joerg Pauly
*   All Rights reserved
*
*   ChartButler ist Freie Software: Sie k�nnen es unter den Bedingungen
*   der GNU General Public License, wie von der Free Software Foundation,
*   Version 3 der Lizenz oder (nach Ihrer Option) jeder sp�teren
*   ver�ffentlichten Version, weiterverbreiten und/oder modifizieren.
*
*   Dieses Programm wird in der Hoffnung, dass es n�tzlich sein wird, aber
*   OHNE JEDE GEW�HRLEISTUNG, bereitgestellt; sogar ohne die implizite
*   Gew�hrleistung der MARKTF�HIGKEIT oder EIGNUNG F�R EINEN BESTIMMTEN ZWECK.
*   Siehe die GNU General Public License f�r weitere Details.
*
*   Sie sollten eine Kopie der GNU General Public License zusammen mit diesem
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
    // Connect the Request's finished()-signal to our slot
    connect(&m_nam,SIGNAL(finished(QNetworkReply*)),this,SLOT(dlFinished(QNetworkReply*)));

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
    QString lsUrl(AMENDURL);
    QString lcmp("SID=");
    int lcnt = lsUrl.indexOf(lcmp)+4;
    lsUrl.insert(lcnt,m_sid);
    QUrl lUrl(lsUrl);
    downloadData(&lUrl);
}

void CNetworkManager::getChart(QString* pICAO)
{
    /* Check if there are charts for the field
       Create directory
       Download the Charts
       Store chart's data in db */
    m_action = ACT_NEW;
    m_ICAO = *pICAO;
    QString lsUrl(ICAOURL);
    lsUrl.append(pICAO);
    lsUrl.append("&SID=");
    lsUrl.append(m_sid);
    QUrl* lUrl = new QUrl(lsUrl);
    downloadData(lUrl);
}

void CNetworkManager::downloadData(QUrl* pUrl)
{
    // Set URL in request
    m_request.setUrl(*pUrl);
    // Send request
    m_nam.get(m_request);
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
            QDataStream out(lChartFile);
            out << ldlData;
            lChartFile->flush();
            lChartFile->close();
        }

    }

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
        dlgLogin->setDetailedText("Der GAT24-Server konnte keine Sitzungs-ID zuteilen.\nMeist liegt dies an fehlenden oder ung�ltigen Login-daten.");
        dlgLogin->setInformativeText("Bitte �berpr�fen Sie Ihre Zugangs-Daten.");
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
    int i;
    for(i = 0; i < pLinkList->count(); i++)
    {
        QUrl lUrl(pLinkList->at(i));
        downloadData(&lUrl);
    }
}

QList<CDatabaseManager::s_Field>* CNetworkManager::GetAmendedFieldsList()
{
    QList<CDatabaseManager::s_Field> *lFldList = new QList<CDatabaseManager::s_Field>;
    QString ldlData(m_dlData);
    QString lCmp("Karten und Daten zum ");
    txtPos* lDate = getTextAfter(&ldlData, &lCmp, 10, 0);
    m_lastAmmended = QDate::fromString(lDate->text,"dd.MM.yyyy");

    // Datum der letzten �nderung in CStatus anzeugen...
    CMainWindow* lparent = (CMainWindow*) m_parent;
    CStatus* status = new CStatus(lparent);
    QString lstatus("�nderungen vom ");
    lstatus.append(m_lastAmmended.toString("dd.MM.yyyy"));
    status->setWindowTitle("Pr�fung auf ge�nderte Karten");
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
        if(ldbman->GetField(lFld->IACO,lFieldCheck))
        {
            if(lFullName.length() < 15)
            {
                lFullName.append("\t");
            }
            lFullName.append("\t\t...im Abo; wird gepr�ft.");
            status->appendList(&lFullName);
            if(ldbman->BrowseCharts(lFieldCheck->ID))
            {
                CDatabaseManager::s_Chart *lchart = ldbman->GetActualChart();
                if(lchart->Date < m_lastAmmended)
                {
                    lFullName = "\t\t\t...wird erneuert.";
                    status->appendList(&lFullName);
                    // TODO: Charts downloaden und DB nachpflegen...
                }
                else
                {
                    lFullName = "\t\t\t...ist aktuell!";
                    status->appendList((&lFullName));
                }
            }
        }
        else
        {
            if(lFullName.length() < 15)
            {
                lFullName.append("\t");
            }
            lFullName.append("\t\t...�bersprungen");
            status->appendList(&lFullName);
        }
        lFld->Name = lFldDef->text;
        lFldList->append(*lFld);
        lLastPos = lFldDef->pos;
    }
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

void CNetworkManager::storeChartFile(QByteArray* pStream, QString* pFilename)
{

}

void CNetworkManager::storeNewField(QString *pICAO)
{

}
