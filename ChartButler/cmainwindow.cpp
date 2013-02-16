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
    setupMenu();
    SetupTree();
}

CMainWindow::~CMainWindow()
{
    delete ui;
    delete mdb;
    delete mnet;
    delete mopt;
}

void CMainWindow::setupMenu()
{
    m_contextMenu = new QMenu(this);
    QList<QAction*> lActions;
    m_actRemove = new QAction("Platz entfernen", this);
    lActions.append(m_actRemove);
    m_actShowInReader = new QAction("Karte anzeigen", this);
    lActions.append(m_actShowInReader);
    m_actUpdate = new QAction("Aktualisieren",this);
    lActions.append(m_actUpdate);
    m_contextMenu->addActions(lActions);

    connect(m_actRemove,SIGNAL(triggered()),this,SLOT(on_actRemove()));
    connect(m_actShowInReader,SIGNAL(triggered()),this,SLOT(on_actShow()));
    connect(m_actUpdate,SIGNAL(triggered()),this,SLOT(on_actUpdate()));
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

void CMainWindow::contextMenuEvent(QContextMenuEvent *e)
{
    m_contextMenu->exec(e->globalPos());
}

QList<QString*> *CMainWindow::parseFields(QString pICAO)
{
    QList<QString*> *lList = new QList<QString*>();
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
                lList->append(lChr);
                lChr = new QString();
            }
        }
        cnt++;
    } while(cnt <= pICAO.length());
    return lList;
}


void CMainWindow::on_cmdAdd_clicked()
{
    // Input-Dialog zusammenbasteln
    QInputDialog *inDlg = new QInputDialog(this);
    inDlg->setOkButtonText("Platz suchen");
    inDlg->setCancelButtonText("Suche abbrechen");
    inDlg->setLabelText("Bitte geben Sie den oder die ICAO-Codes\ndes gesuchten Platzes ein\n(Mehrere ICAO-Codes durch Leerzeichen, Komma, Semikolon\noder Minus getrennt):");

    // anzeigen und auswerten
    if(inDlg->exec() == QInputDialog::Accepted)
    {
        QString icao;
        icao = inDlg->textValue().toUpper();        
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

void CMainWindow::updateField(QString *pICAO)
{
    CDatabaseManager::s_Field* lfld = new CDatabaseManager::s_Field();
    QString lICAO(*pICAO);
    mdb->GetField(lICAO,lfld);
    ui->trvCharts->setCurrentItem(0);
    mdb->RemoveField(&lfld->IACO);
    mnet->getChart(&lICAO);
    SetupTree();
}

void CMainWindow::nextField()
{
    m_networkReady = true;
}

void CMainWindow::markAmmendedFields()
{
    for(int i=0; i< m_AmendedFields->count(); i++)
    {
        QTreeWidgetItem* item = ui->trvCharts->findItems(m_AmendedFields->at(i).toUtf8(),Qt::MatchStartsWith,0).at(0);
        QFont fnt = item->font(0);
        fnt.setBold(true);
        item->setFont(0, fnt);
    }
}

void CMainWindow::on_cmdUpdate_clicked()
{
    mnet->updateCharts();
}

void CMainWindow::on_trvCharts_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    QString lFname(item->data(0, Qt::UserRole).toString());
    QFont fnt = item->font(0);
    fnt.setBold(false);
    item->setFont(0, fnt);
    if(lFname.right(4).toLower() == ".pdf")
    {
        #ifdef Q_OS_WIN
            QStringList lArg(lFname);
            QProcess lReader;
            QString pdfRead(mopt->pdfExe());
            lReader.startDetached(pdfRead, lArg);
        #endif

        #ifdef Q_OS_LINUX
            lFname.insert(0, "file://");
            QUrl lUrl(lFname);
            QDesktopServices::openUrl(lUrl);
        #endif
    }
}

void CMainWindow::on_actRemove()
{
    QMessageBox *lBox = new QMessageBox(this);
    lBox->setWindowTitle("Platz löschen");
    CDatabaseManager::s_Field* lfld = new CDatabaseManager::s_Field();
    QString lICAO(m_clickedItem->text(0).left(4).toUpper());
    mdb->GetField(lICAO,lfld);
    QString msg("Wollen Sie den Flugplatz\n");
    msg.append(lfld->Name);
    msg.append("\nwirklich löschen?");
    lBox->setText(msg);
    lBox->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    lBox->setButtonText(QMessageBox::Yes,"Ja, flieg ich eh nicht mehr hin...");
    lBox->setButtonText(QMessageBox::No, "Um Himmels Willen, NEIN!!!");
    lBox->setDefaultButton(QMessageBox::No);
    if(lBox->exec() == QMessageBox::Yes)
    {
        ui->trvCharts->setCurrentItem(0);
        mdb->RemoveField(&lfld->IACO);
        SetupTree();
    }
}

void CMainWindow::on_actShow()
{
    on_trvCharts_itemDoubleClicked(m_clickedItem, 0);
}

void CMainWindow::on_actUpdate()
{
    CDatabaseManager::s_Field* lfld = new CDatabaseManager::s_Field();
    QString lICAO(m_clickedItem->text(0).left(4).toUpper());
    mdb->GetField(lICAO,lfld);
    ui->trvCharts->setCurrentItem(0);
    mdb->RemoveField(&lfld->IACO);
    mnet->getChart(&lICAO);
    SetupTree();
}

void CMainWindow::on_trvCharts_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    if(current == 0)
    {
        return;
    }

    previous = 0;
    m_clickedItem = current;
    QString lPath(current->data(0, Qt::UserRole).toString());
    if(lPath.right(4).toLower() == ".pdf" )
    {
        CDatabaseManager::s_Field lfld;
        mdb->GetField(lPath.left(4),&lfld);
        m_contextMenu->setTitle(lfld.Name);
        m_actRemove->setEnabled(false);
        m_actShowInReader->setEnabled(true);
        m_actUpdate->setEnabled(false);
    }
    else
    {
        m_contextMenu->setTitle(current->text(0));
        m_actRemove->setEnabled(true);
        m_actShowInReader->setEnabled(false);
        m_actUpdate->setEnabled(true);
    }
}

void CMainWindow::on_trvCharts_itemChanged(QTreeWidgetItem *item, int column)
{

}

void CMainWindow::on_cmdHelpInfo_clicked()
{
    CHelp *help = new CHelp(this);
    help->exec();
    delete help;
}

void CMainWindow::on_cmdGat24_clicked()
{
    QUrl lUrl("http://www.gat24.de");
    QDesktopServices::openUrl(lUrl);
}
