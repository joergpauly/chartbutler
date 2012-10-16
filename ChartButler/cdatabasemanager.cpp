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
/*************************************************************************************************
  CDatabaseManager: Class to manage connection and traffic with the SQLite database holding
  the chart's data.

  (C) 2012 Joerg Pauly
 *************************************************************************************************/

#include "cdatabasemanager.h"


CDatabaseManager::CDatabaseManager(QObject *parent) :
    QObject(parent)
{
    /* Define & open db
     * if the file doesn't exist, it will be created and
     * populated with the table definitions
     */
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    QString dbname = QApplication::applicationDirPath();
    dbname.append("/cb.sqlite");
    m_db.setDatabaseName(dbname);

    // Let's check if the file exists
    QFile dbfile(dbname);
    bool dbmiss = false;
    if (!dbfile.open(QFile::ReadOnly))
    {
        // file isn't there; set a flag to create it
        dbmiss = true;
    }

    if (!m_db.open())
    {
        QMessageBox* msg = new QMessageBox();
        msg->setText("Fehler beim �ffnen der Datenbank!");
        msg->setInformativeText("Datenbank l�sst sich nicht �ffnen!");
        msg->setIcon(QMessageBox::Critical);
        msg->exec();
    }

    if (dbmiss)
    {
        // opening the db created a plain file; now let's create the tables
        QString crc;
        crc = "CREATE TABLE \"Charts\" (\"ID\" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL , \"FID\" INTEGER NOT NULL , \"CName\" TEXT, \"CPath\" TEXT, \"Date\" DATETIME)";
        QSqlQuery* crcharts = new QSqlQuery(crc, m_db);
        crcharts->exec();
        QString crf;
        crf = "CREATE TABLE \"Fields\" (\"ID\" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL , \"ICAO\" TEXT, \"Name\" TEXT, \"Path\" TEXT)";
        QSqlQuery* crfields = new QSqlQuery(crf, m_db);
        crfields->exec();
    }
}

CDatabaseManager::~CDatabaseManager()
{
    // close db
    m_db.close();
}


bool CDatabaseManager::GetField(QString p_icao, s_Field* p_field)
{
    qryFields = new QSqlQuery(m_db);
    // Get the data identified by ICAO
    qryFields->prepare("SELECT ID, ICAO, Name, Path FROM Fields WHERE ICAO = :ICAO");
    qryFields->bindValue(":ICAO", p_icao);
    qryFields->exec();
    qryFields->first();
    if (qryFields->isValid())
    {
        p_field->ID   = qryFields->value(qryFields->record().indexOf("ID")).toInt(),
        p_field->IACO = qryFields->value(qryFields->record().indexOf("ICAO")).toString();
        p_field->Name = qryFields->value(qryFields->record().indexOf("Name")).toString();
        p_field->Path = qryFields->value(qryFields->record().indexOf("Path")).toString();
        return true;
    }
    else
    {
        return false;
    }
}

int CDatabaseManager::AddField(QString p_icao, QString p_name, QString p_path)
{
    qryFields = new QSqlQuery(m_db);
    // Check if passed field exists in database
    qryFields->prepare("SELECT * FROM Fields WHERE ICAO = :ICAO");
    qryFields->bindValue(":ICAO", p_icao);
    qryFields->exec();
    qryFields->first();
    if (qryFields->isValid())
    {
        return qryFields->value(qryFields->record().indexOf("ID")).toInt();
    }
    // Ok, a new field, so write it down.
    qryFields->prepare("INSERT INTO Fields (ICAO,Name,Path) VALUES (:ICAO, :Name, :Path)");
    qryFields->bindValue(":ICAO", p_icao);
    qryFields->bindValue(":Name", p_name);
    qryFields->bindValue(":Path", p_path);
    qryFields->exec();
    qryFields->prepare("SELECT * FROM Fields WHERE ICAO = :ICAO");
    qryFields->bindValue(":ICAO", p_icao);
    qryFields->exec();
    qryFields->first();
    return qryFields->value(qryFields->record().indexOf("ID")).toInt();
}

bool CDatabaseManager::BrowseFields()
{
    // Fill the query with all the records and point ton the 1st one
    qryFields = new QSqlQuery(m_db);
    qryFields->exec("SELECT ID, ICAO, Name, Path FROM Fields");
    qryFields->first();
    return true;
}

CDatabaseManager::s_Field* CDatabaseManager::GetActualField()
{
    // Get data of the actual record. Use only with a valid query!!!
    s_Field* fld = new s_Field;
    fld->ID   = qryFields->value(qryFields->record().indexOf("ID")).toInt(),
    fld->IACO = qryFields->value(qryFields->record().indexOf("ICAO")).toString();
    fld->Name = qryFields->value(qryFields->record().indexOf("Name")).toString();
    fld->Path = qryFields->value(qryFields->record().indexOf("Path")).toString();
    return fld;
}


// Wrappers for the field navigation
bool CDatabaseManager::NextField()
{
    return qryFields->next();
}

bool CDatabaseManager::PrevField()
{
    return qryFields->previous();
}

void CDatabaseManager::AddChart(int p_FID, QString p_name, QString p_path, QDate p_date)
{
    // Check if there's already a chart with that file name
    qryCharts = new QSqlQuery(m_db);
    qryCharts->prepare("SELECT * FROM Charts WHERE CName = :CNAME");
    qryCharts->bindValue(":CNAME", p_name);
    qryCharts->exec();
    qryCharts->first();
    if(qryCharts->isValid())
    {
        // We got it. Nothing to do.
        return;
    }
    // It's a new one, so add it.
    qryCharts->prepare("INSERT INTO Charts (FID, CName, CPath, Date) VALUES (:FID, :CNAME, :CPATH, :CDATE)");
    qryCharts->bindValue(":FID", p_FID);
    qryCharts->bindValue(":CNAME", p_name);
    qryCharts->bindValue(":CPATH", p_path);
    qryCharts->bindValue(":CDATE", p_date);
    qryCharts->exec();
}


bool CDatabaseManager::BrowseCharts(int FID)
{
    qryCharts = new QSqlQuery(m_db);
    qryCharts->prepare("SELECT * FROM Charts WHERE FID = :FID");
    qryCharts->bindValue(":FID", FID);
    qryCharts->exec();
    qryCharts->first();
    return true;
}

CDatabaseManager::s_Chart* CDatabaseManager::GetActualChart()
{
    s_Chart* chart = new s_Chart();
    chart->FID = qryCharts->value(qryCharts->record().indexOf("FID")).toInt();
    chart->ID = qryCharts->value(qryCharts->record().indexOf("ID")).toInt();
    chart->Name = qryCharts->value(qryCharts->record().indexOf("CName")).toString();
    chart->Path = qryCharts->value(qryCharts->record().indexOf("CPath")).toString();
    chart->Date = qryCharts->value(qryCharts->record().indexOf("Date")).toDate();
    return chart;
}

bool CDatabaseManager::NextChart()
{
    return qryCharts->next();
}

bool CDatabaseManager::PrevChart()
{
    return qryCharts->previous();
}

bool CDatabaseManager::FirstField()
{
    return qryCharts->first();
}

bool CDatabaseManager::LastField()
{
    return qryFields->last();
}