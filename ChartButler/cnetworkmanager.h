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
/*****************************************************************************************
*
*   CNetworkManager.h
*   CNetworkManager regelt den kompletten Datenverkehr mit dem GAT24.de-Server.
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
#include <QProgressDialog>
#include "cdatabasemanager.h"

#define ACT_NEW 0
#define ACT_UPD 1

class CNetworkManager : public QObject
{
    Q_OBJECT
public:
    explicit CNetworkManager(QObject *parent = 0);
    void updateCharts();
    void updateField(QString* pICAO);
    void getChart(QString* pICAO);



private:
    QObject* m_parent;
    QString m_uid;
    QString m_pw;
    QString m_sid;
    QString m_ICAO;
    QString m_FieldName;
    QString m_FieldDir;
    QDate   m_lastAmmended;
    int     m_action;
    int     m_FID;
    QByteArray m_dlData;
    QNetworkAccessManager m_nam;
    QNetworkRequest m_request;
    QList<QString> *m_fieldList;
    QList<QString> *m_newCharts;
    QProgressDialog* m_dlProgress;
    bool m_lastRetrieve;
    bool m_nextField;
    int m_chartInSequence;
    int m_chartsToLoad;
    int m_fieldInSequence;
    QList<QString> *m_linkList;

    struct txtPos
    {
        QString text;
        int     pos;
    };

    void getSID();
    void downloadData(QUrl* pUrl, bool pShowState = false);
    void extractSID();
    void getNewAirfield(QString* pICAO, QList<QString>* pLinkList);
    QList<CDatabaseManager::s_Field>* GetAmendedFieldsList();
    txtPos *getTextBetween(QString* pSource, QString* pStart, QString* pEnd, int pStartPos);
    txtPos *getTextAfter(QString* pSource, QString* pStart, int pLen, int pStartPos);
    QStringList* getLinkList(QString* pStream);
    void getFieldName(QString* pStream);
    void storeChartInDb(QString *pFileName, QString *pPath);
    QList<QString> *parseFields(QString pICAO);
    void checkForUpdate();

public slots:
    void dlFinished(QNetworkReply* pReply);
    void dlProgress(qint64 pRcvd, qint64 pTotal);
    void onChartDlFinished();
    void dlNextField();

signals:
    void chartDlFinished();
    void fieldDlFinished();

};

#endif // CNETWORKMANAGER_H
