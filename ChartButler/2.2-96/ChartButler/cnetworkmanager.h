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

#ifndef CNETWORKMANAGER_H
#define CNETWORKMANAGER_H
#include <QObject>
#include <QString>
#include <QStringList>
#include <QByteArray>
#include <QFile>
#include <QDataStream>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QList>
#include <QDate>
#include <QtWidgets/QProgressDialog>
#include <QMessageBox>
#include "cdatabasemanager.h"
#include "cparser.h"
#include "cprogress.h"


#define ACT_NEW 0
#define ACT_UPD 1

class CNetworkManager : public QObject
{
    Q_OBJECT


private:
    //Private Member
    QObject *m_parent;
    QString m_uid;
    QString m_pw;
    QString m_sid;
    QString *m_ICAO;
    QString *m_FieldName;
    QString m_FieldDir;
    int m_FID;
    QList<QString*> *m_FieldList;
    int m_FieldsToLoad;
    int m_actualFieldToLoad;
    QList<QString*> *m_ChartList;
    int m_ChartsToLoad;
    int m_actualChartToLoad;
    QNetworkAccessManager m_nam;
    QNetworkRequest m_request;
    CParser m_parser;
    CProgress *m_progress;
    int m_ReplyType;

    enum ReplyType //WAS haben wir angefordert?
    {
        LoginPage,
        SidReply,
        AirfieldChartLinkList,
        PDFdoc,
        AppVersion
    };

    //Private Funktionen
    void getSID();
    void extractSID(QString *pStream);
    void getChartListForNewField();
    void getChartsFromList();
    void getLinkList(QString *pStream);
    void getFieldName(QString *pStream);
    void loadFromChartList(QString *pStream);
    void storeAirfieldInDB();
    void storeSingleChart(QNetworkReply* pReply, QByteArray pStream);

public:
    explicit CNetworkManager(QObject *parent = 0);
    void getNewAirfields(QList<QString *> *pList);

private slots:
    void downloadFinished(QNetworkReply *pReply);
    void downloadNextField();
    void downloadNextChart();

signals:
    void fieldDownloadFinished();
    void chartDownloadFinished();

};

#endif // CNETWORKMANAGER_H
