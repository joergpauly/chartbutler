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
*   COptions.cpp
*   Diese Klasse stellt den Dialog f�r Voreinstellungen
*   sowie das Objekt zu deren Speicherung bereit.
*
*****************************************************************************************/

// Functional Headers only for the definitions.
#include "coptions.h"
#include "ui_coptions.h"
#include "cmainwindow.h"


// The constructor: we need some info about our environment.
// This is provided by the "parent" parameter.
COptions::COptions(QWidget *parent) :
    QDialog(parent), ui(new Ui::COptions)
{
    // Save the parent's pointer to a private member
    m_parent = parent;
    // now convert it to something we can work with...
    CMainWindow* l_Parent = (CMainWindow*) m_parent;

    // ...and extract the essentials. (The Database Manager)
    mdb = l_Parent->GetDBman();

    // We just need to instantiate QSettings, as it is reentrant.
    settings = new QSettings(gCOMPANY, gAPP);

    // Set up the GUI...
    ui->setupUi(this);

    // ...and feed it!
    ui->txtChartPath->setText(settings->value("ChartPath").toString());
    ui->txtUserName->setText(settings->value("UID").toString());
    ui->txtPassword->setText(settings->value("PW").toString());
    ui->txtPdfExePath->setText(settings->value("PDFexe").toString());
}



void COptions::on_cmdBrowsePath_clicked()
{
    // Let's create and show a nice dialog to choose a directory...
    QFileDialog* dirDlg = new QFileDialog(this, "Karten-Verzeichnis");
    dirDlg->setDirectory(ui->txtChartPath->text());
    dirDlg->setOption(QFileDialog::ShowDirsOnly, true);
    dirDlg->setFileMode(QFileDialog::Directory);
    dirDlg->exec();

    // We're only interested in the first entry of the list coming from the dialog.
    // This one's going to our txt-field.
    ui->txtChartPath->setText(dirDlg->selectedFiles()[0]);

}

void COptions::on_buttonBox_accepted()
{
    // Show the Wait Cursor
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    // Write the value to the settings storage, where ever it is...
    settings->setValue("ChartPath", ui->txtChartPath->text());
    settings->setValue("UID", ui->txtUserName->text());
    settings->setValue("PW",ui->txtPassword->text());
    settings->setValue("PDFexe",ui->txtPdfExePath->text());

    // Get all subdir's names...
    QDir* basedir = new QDir(settings->value("ChartPath").toString());
    QStringList dirlist = basedir->entryList();

    // Iterate and parse them...
    foreach (QString fielddir, dirlist)
    {
        QString icao = fielddir.left(4);
        QString name = fielddir.right(fielddir.length()-7);
        QString fieldpath = basedir->absolutePath();
        fieldpath.append("/");
        fieldpath.append(fielddir);

        // We don't need parent and actual dir, so we sort'em out...
        if(icao.left(1) != ".")
        {
            // Give ICAO and name to the database manager...
            int FID = mdb->AddField(icao, name, fieldpath);
            QString cdirname = fieldpath;
            cdirname.append("/");
            QDir* chartdir = new QDir(cdirname);
            QFileInfoList lDirInfo;
            lDirInfo = chartdir->entryInfoList();
            foreach(QFileInfo chart, lDirInfo)
            {
                // Skip directories...
                if(chart.fileName().left(1) != ".")
                {
                    QString CPath = cdirname;
                    CPath.append(chart.fileName());
                    mdb->AddChart(FID, chart.fileName(), CPath, chart.lastModified().date());
                }
            }
        }
    }
    // After refilling the database show the main window with updated data
    CMainWindow* l_mainWin = (CMainWindow*)m_parent;
    l_mainWin->SetupTree();
    // Show normal Cursor again...
    QApplication::restoreOverrideCursor();
}

void COptions::on_buttonBox_rejected()
{
    // Simply do nothing...
}

void COptions::on_cmdBrowsePdf_clicked()
{
    QFileDialog* dlgReaderPath = new QFileDialog(this,"PDF-Reader");
    dlgReaderPath->setDirectory(ui->txtPdfExePath->text());
    dlgReaderPath->setOption(QFileDialog::ShowDirsOnly, false);
    dlgReaderPath->setFileMode(QFileDialog::ExistingFile);
    dlgReaderPath->exec();
    ui->txtPdfExePath->setText(dlgReaderPath->selectedFiles()[0]);
}

// Property-Get-Functions

QString COptions::uid()
{
    return settings->value("UID").toString();
}

QString COptions::pw()
{
    return settings->value("PW").toString();
}

QString COptions::chartPath()
{
    return settings->value("ChartPath").toString();
}

QString COptions::pdfExe()
{
    return settings->value("PDFexe").toString();
}
