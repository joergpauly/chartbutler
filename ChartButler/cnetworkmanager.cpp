/****************************************************************************************
*
*   This file is part of the ChartButler Project.
*   Copyright (C) 2013 Joerg Pauly
*   Created 02.11.2013 by joerg
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
 *  CNetworkManager
 *  Stellt die gesamte Kommunikation mit dem GAT24-Server zur Verfügung
 ****************************************************************************************/


#include "cnetworkmanager.h"
#include "coptions.h"
#include "cmainwindow.h"

CNetworkManager::CNetworkManager(QObject *parent) : QObject(parent)
{
    //"Parent" sichern
    m_parent = parent;
    //Signal des QNetworkAccessManager fangen
    connect(&m_nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(downloadFinished(QNetworkReply*)));
    //Login-Daten aus Settings holen
    QSettings l_opts(gCOMPANY, gAPP);
    m_uid = l_opts.value("UID").toString();
    m_pw = l_opts.value("PW").toString();
    //Einloggen, um SID zu bekommen
    getSID();
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
    m_ReplyType = LoginPage;
    m_nam.post(m_request,lLogin.toLatin1());

}

/****************************************************************************
 *  Die Anforderungen von CMainWindow landen hier!
 ****************************************************************************/

void CNetworkManager::getNewAirfields(QList<QString*> *pList)
{
    //Es sollen neue Flugplätze geladen werden.
    for(int i = 0; i <= pList->count(); i++)
    {
        getChartsForNewField(pList->at(i));
    }
}

/****************************************************************************
 *  Hilfsfunktionen für die CMainWindow-Anforderungen
 ****************************************************************************/

void CNetworkManager::getChartsForNewField(QString *pIcao)
{
    //Für einen neu zu ladenden Platz wird die Chart-Linkliste geladen
    m_ICAO = new QString(*pIcao);
    QString lUrlString(ICAOURL);
    lUrlString.append(pIcao);
    lUrlString.append("&SID=");
    lUrlString.append(m_sid);
    QUrl lUrl(lUrlString);
    m_request.setUrl(lUrl);
    m_ReplyType = AirfieldChartLinkList;
    m_nam.get(m_request);
}



/****************************************************************************
 *  Alle Replies landen hier.
 *  Es wird anhand des Requests sortiert
 ****************************************************************************/
void CNetworkManager::downloadFinished(QNetworkReply *pReply)
{
    QString lStream(QString::fromLatin1(pReply->readAll()));
    switch (m_ReplyType)
    {
    case LoginPage:
        extractSID(&lStream);
        break;
    case AirfieldChartLinkList:
        getFieldName(&lStream);
        getLinkList(&lStream);
        //TODO: Datenbank nachführen.
        storeAirfieldInDB();
        //TODO: Charts nacheinander laden.

    default:
        break;
    }
}

/****************************************************************************
 *  Ab hier werden die Replies bearbeitet
 ****************************************************************************/

void CNetworkManager::extractSID(QString *pStream)
{
    QString lStart("SID=");
    QString lEnd("\">Mitglied");
    m_sid = m_parser.getTextBetween(pStream, &lStart, &lEnd, 0)->text;
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

void CNetworkManager::getLinkList(QString *pStream)
{
    m_LinkList = new QList<QString*>();
    int lpos = pStream->indexOf("pdfkarten.php?&icao=");
    if(lpos == -1)
    {
        return;
    }
    int fstlpos = lpos;
    while(lpos >= fstlpos)
    {
        QString lStart("pdfkarten.php?&icao=");
        QString lEnd("&");
        CParser::txtPos* chartBuf = m_parser.getTextBetween(pStream, &lStart, &lEnd, lpos);
        lpos = chartBuf->pos;
        if(chartBuf->text.contains("W3C"))
        {
            break;
        }
        QString *lhdr =new QString("http://www.gat24.de/dokumente/briefing/flugplaetze/pdfkarten.php?&icao=");
        lhdr->append(chartBuf->text);
        lhdr->append("&SID=");
        lhdr->append(m_sid);
        m_LinkList->append(lhdr);
    }
}

void CNetworkManager::getFieldName(QString *pStream)
{
    QString lStart("style=\"width:300px\">");
    QString lEnd("</td>");
    m_FieldName = new QString();
    *m_FieldName = m_parser.getTextBetween(pStream, &lStart, &lEnd, 0)->text;
    m_FieldName->replace(m_FieldName->indexOf("/"),1,"-");
    *m_FieldName = m_FieldName->toLower();
    QChar lfst(m_FieldName->at(0).toUpper().toLatin1());
    m_FieldName->replace(0,1,QString(lfst));
    int i = m_FieldName->indexOf("-");
    if(i != -1)
    {
        QChar list(m_FieldName->at(i+1).toUpper().toLatin1());
        m_FieldName->replace(i+1,1,QString(list));
    }
}

void CNetworkManager::storeAirfieldInDB()
{
    CMainWindow *lMain = (CMainWindow *)m_parent;
    CDatabaseManager *lDB = lMain->GetDBman();
    CDatabaseManager::s_Field *lField = new CDatabaseManager::s_Field();
    if(lDB->GetField(*m_ICAO, lField))
    {
        //Der Platz ist vorhanden; er wird aktualisiert!
        //Dazu wird er zunächst gelöscht.
        lDB->RemoveField(m_ICAO);
    }
    QString lFullName(*m_ICAO);
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
    m_FID = lDB->AddField(*m_ICAO, *m_FieldName, m_FieldDir);
    lMain->SetupTree();

}
