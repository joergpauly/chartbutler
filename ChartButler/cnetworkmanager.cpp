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

    m_nam.post(m_request,lLogin.toLatin1());

}


void CNetworkManager::extractSID()
{
    QString lStream(m_dlData);
    QString lStart("SID=");
    QString lEnd("\">Mitglied");
    m_sid = getTextBetween(&lStream, &lStart, &lEnd, 0)->text;
    CMainWindow* lparent = (CMainWindow*) m_parent;
    if(m_sid == "0")
    {
        QMessageBox *dlgLogin = new QMessageBox(lparent);
        dlgLogin->setStandardButtons(QMessageBox::Ok);
        dlgLogin->setText("Ihre Sitzung wurde vom GAT24-Server nicht authorisiert.");
        dlgLogin->setDetailedText("Der GAT24-Server konnte keine Sitzungs-ID zuteilen.\nMeist liegt dies an fehlenden oder ungültigen Login-daten.");
        dlgLogin->setInformativeText("Bitte überprüfen Sie Ihre Zugangs-Daten.");
        dlgLogin->setWindowTitle("Authorisierungs-Fehler!");
        dlgLogin->exec();
    }       
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
    QChar lfst(m_FieldName.at(0).toUpper().toLatin1());
    m_FieldName.replace(0,1,QString(lfst));
    int i = m_FieldName.indexOf("-");
    if(i != -1)
    {
        QChar list(m_FieldName.at(i+1).toUpper().toLatin1());
        m_FieldName.replace(i+1,1,QString(list));
    }
}

void CNetworkManager::storeChartInDb(QString* pFileName, QString* pPath, QDate *pDate)
{
    CMainWindow* lparent = (CMainWindow*)m_parent;
    CDatabaseManager* ldbman = lparent->GetDBman();
    ldbman->AddChart(m_FID, *pFileName, *pPath, *pDate);
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

QDate *CNetworkManager::fromHTMLDate(QString pHTMLtag)
{
    QDate* lDate = new QDate();
    int d;
    int m;
    int y;

    pHTMLtag = pHTMLtag.left(pHTMLtag.length() - 13);
    pHTMLtag = pHTMLtag.right(pHTMLtag.length() - 5);
    d = pHTMLtag.left(2).toInt();
    y = pHTMLtag.right(4).toInt();
    QString lTag(pHTMLtag.mid(3,3));

    if(lTag == "Jan")
        m = 1;

    if(lTag == "Feb")
        m = 2;

    if(lTag == "Mar")
        m = 3;

    if(lTag == "Apr")
        m = 4;

    if(lTag == "May")
        m = 5;

    if(lTag == "Jun")
        m = 6;

    if(lTag == "Jul")
        m = 7;

    if(lTag == "Aug")
        m = 8;

    if(lTag == "Sep")
        m = 9;

    if(lTag == "Oct")
        m = 10;

    if(lTag == "Nov")
        m = 11;

    if(lTag == "Dec")
        m = 12;

    lDate->setDate(y,m,d);
    return lDate;
}

