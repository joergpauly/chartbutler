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
/****************************************************************************************
*
*   CMainWindow.h
*   Klasse zur Erstellung des Hauptfensters und der Menü- und Button-Prozeduren.
*
*****************************************************************************************/
#include "cmainwindow.h"
#include "ui_cmainwindow.h"

CMainWindow::CMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CMainWindow)
{
    ui->setupUi(this);
    mdb = new CDatabaseManager(this);
    mnet = new CNetworkManager(this);
    mopt = new COptions(this);
    SetupTree();
}

CMainWindow::~CMainWindow()
{
    delete ui;
    delete mdb;
    delete mnet;
    delete mopt;
}

void CMainWindow::on_cmdClose_clicked()
{
    this->close();
}

void CMainWindow::closeEvent(QCloseEvent *e)
{
    // MessageBox zusammenbasteln
    QMessageBox *msg = new QMessageBox(this);
    msg->setText("Wollen Sie ChartButler beenden?");
    msg->setStandardButtons(QMessageBox::Ok | QMessageBox::Abort);
    msg->setDefaultButton(QMessageBox::Ok);
    msg->setIcon(QMessageBox::Question);
    msg->setButtonText(QMessageBox::Abort, "Nicht schließen");

    // Anzeigen und auswerten
    if(msg->exec() == QMessageBox::Ok)
    {
        // es kann geschlossen werden.
        e->accept();
    }
    else
    {
        // closeEvent wird verworfen.
        e->ignore();
    }

    // Aufräumen
    delete msg;
}

void CMainWindow::on_cmdAdd_clicked()
{
    // Input-Dialog zusammenbasteln
    QInputDialog *inDlg = new QInputDialog(this);
    inDlg->setOkButtonText("Platz suchen");
    inDlg->setCancelButtonText("Suche abbrechen");
    inDlg->setLabelText("Bitte geben Sie den ICAO-Code des gesuchten Platzes ein:");

    // anzeigen und auswerten
    if(inDlg->exec() == QInputDialog::Accepted)
    {
        QString icao;
        icao = inDlg->textValue().toUpper();
        // Suchfunktion in Netzwerk-Klasse anstoßen
        mnet->getChart(&icao);
    }

    // Aufräumen
    delete inDlg;
}

void CMainWindow::on_cmdOptions_clicked()
{    
    mopt->exec();
    mnet = new CNetworkManager(this);
}

CDatabaseManager* CMainWindow::GetDBman()
{
    return mdb;
}

void CMainWindow::SetupTree()
{
    // Clear the tree...
    ui->trvCharts->clear();
    // Fill query...
    mdb->BrowseFields();
    // ...and iterate it to fill the tree
    do
    {
        CDatabaseManager::s_Field* fld = mdb->GetActualField();
        QTreeWidgetItem* item = new QTreeWidgetItem();
        QString FldTitle = fld->IACO;
        FldTitle.append(" - ");
        FldTitle.append(fld->Name);
        item->setText(0, FldTitle);
        item->setData(0,Qt::UserRole,fld->Path);
        // Get the charts for the field...
        mdb->BrowseCharts(fld->ID);
        // ...and put them into the tree
        do
        {
            CDatabaseManager::s_Chart* crt = mdb->GetActualChart();
            QTreeWidgetItem *chld = new QTreeWidgetItem();
            chld->setText(0, crt->Name);
            chld->setText(1, crt->Date.toString("dd.MM.yyyy"));
            chld->setData(0, Qt::UserRole, crt->Path);
            chld->setData(1, Qt::UserRole, crt->Date);
            item->addChild(chld);
        }while(mdb->NextChart());
        ui->trvCharts->addTopLevelItem(item);
    }while (mdb->NextField());
    QStringList lheaders;
    lheaders.append("Plätze/Karten");
    lheaders.append("Stand vom");
    ui->trvCharts->setHeaderLabels(lheaders);
}

void CMainWindow::on_cmdUpdate_clicked()
{
    mnet->updateCharts();
}

void CMainWindow::on_trvCharts_itemDoubleClicked(QTreeWidgetItem *item, int column)
{

    QString lFname(item->data(0, Qt::UserRole).toString());
    if(lFname.right(4).toLower() == ".pdf")
    {
        #ifdef Q_WS_WIN
            QStringList lArg(lFname);
            m_reader = new QProcess();
            QString pdfRead(mopt->pdfExe());
            m_reader->start(pdfRead, lArg);
        #else
            QUrl lUrl(lFName);
            QDesktopServices::openUrl(lUrl);
        #endif
    }
}
