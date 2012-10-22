/****************************************************************************************
*
*   This file is part of the ChartButler Project.
*   Copyright (C) 2012 Joerg Pauly
*   All Rights reserved
*
*   ChartButler ist Freie Software: Sie können es unter den Bedingungen
*   der GNU General Public License, wie von der Free Software Foundation,
*   Version 3 der Lizenz oder (nach Ihrer Option) jeder späteren
*   veröffentlichten Version, weiterverbreiten und/oder modifizieren.
*
*   Dieses Programm wird in der Hoffnung, dass es nützlich sein wird, aber
*   OHNE JEDE GEWÄHRLEISTUNG, bereitgestellt; sogar ohne die implizite
*   Gewährleistung der MARKTFÄHIGKEIT oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.
*   Siehe die GNU General Public License für weitere Details.
*
*   Sie sollten eine Kopie der GNU General Public License zusammen mit diesem
*   Programm erhalten haben. Wenn nicht, siehe <http://www.gnu.org/licenses/>.
*
*****************************************************************************************/
/*************************************************************************************************
  CDatabaseManager: Class to manage connection and traffic with the SQLite database holding
  the chart's data.

  (C) 2011 Joerg Pauly

 *************************************************************************************************/

#ifndef CDATABASEMANAGER_H
#define CDATABASEMANAGER_H

// System-Header
#include <QApplication>
#include <QObject>
#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <qsql.h>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QList>
#include <QDate>
#include "qsql_sqlite.h"


class CDatabaseManager : public QObject
{
    Q_OBJECT

// Member-Deklarationen
private:
    QSqlDatabase    m_db;



public:
// Struct to publish a whole field's data
    class s_Field
    {
    public:
        int     ID;
        QString IACO;
        QString Name;
        QString Path;
    };

// ...and same for the chart.
    class s_Chart
    {
    public:
        int     ID;
        int     FID;
        QString Name;
        QString Path;
        QDate   Date;
    };

    QSqlQuery* qryFields;
    QSqlQuery* qryCharts;

// Constructor / Destructor
public:
    explicit CDatabaseManager(QObject *parent = 0);
    ~CDatabaseManager();

// Memberfunktionen
public:
    bool GetField(QString p_icao, s_Field* p_field);
    s_Field* GetActualField();
    bool BrowseFields();
    int AddField(QString picao, QString pname, QString ppath);
    bool FirstField();
    bool LastField();
    bool NextField();
    bool PrevField();
    void AddChart(int FID, QString Name, QString Path, QDate Date);
    bool BrowseCharts(int FID);
    s_Chart* GetActualChart();
    bool NextChart();
    bool PrevChart();
    void RemoveField(QString* pICAO);



signals:

public slots:

};

#endif // CDATABASEMANAGER_H
