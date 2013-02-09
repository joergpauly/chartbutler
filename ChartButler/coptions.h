/****************************************************************************************
*
*   This file is part of the ChartButler Project.
*   Copyright (C) 2012 Joerg Pauly
*   All Rights reserved
*
*   ChartButler ist Freie Software: Sie k�nnen es unter den Bedingungen
*   der GNU Lesser General Public License, wie von der Free Software Foundation,
*   Version 3 der Lizenz oder (nach Ihrer Option) jeder sp�teren
*   ver�ffentlichten Version, weiterverbreiten und/oder modifizieren.
*
*   Dieses Programm wird in der Hoffnung, dass es n�tzlich sein wird, aber
*   OHNE JEDE GEW�HRLEISTUNG, bereitgestellt; sogar ohne die implizite
*   Gew�hrleistung der MARKTF�HIGKEIT oder EIGNUNG F�R EINEN BESTIMMTEN ZWECK.
*   Siehe die GNU Lesser General Public License f�r weitere Details.
*
*   Sie sollten eine Kopie der GNU Lesser General Public License zusammen mit diesem
*   Programm erhalten haben. Wenn nicht, siehe <http://www.gnu.org/licenses/>.
*
*****************************************************************************************/
/****************************************************************************************
*
*   COptions.h
*   Diese Klasse stellt den Dialog f�r Voreinstellungen
*   sowie das Objekt zu deren Speicherung bereit.
*
*****************************************************************************************/

#ifndef COPTIONS_H
#define COPTIONS_H

// System-Header
#include <QtWidgets/QDialog>
#include <QSettings>
#include <QDir>
#include <QtWidgets/QFileDialog>

// Private Header
#include "cdatabasemanager.h"
#include "globals.h"

namespace Ui
{
    class COptions;
}

// Klassendeklaration
class COptions : public QDialog
{
    Q_OBJECT

private:
     Ui::COptions *ui;
     QSettings* settings;
     CDatabaseManager* mdb;
     QObject* m_parent;

public:
     explicit COptions(QWidget *parent = 0);
     QString uid();
     QString pw();
     QString chartPath();
     QString pdfExe();

signals:

public slots:

private slots:
     void on_cmdBrowsePath_clicked();
     void on_buttonBox_accepted();
     void on_buttonBox_rejected();
     void on_cmdBrowsePdf_clicked();
};

#endif // COPTIONS_H
