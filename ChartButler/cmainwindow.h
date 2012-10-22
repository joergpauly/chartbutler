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
/**********************************************************************************
  CMainWindow:
  Das Hauptfenster mit Karten-Liste und Funktions-Leiste

  (C) 2011 Jörg Pauly

  **********************************************************************************/

#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

// System-Header
#include <QMainWindow>
#include <QCloseEvent>
#include <QMessageBox>
#include <QInputDialog>
#include <QProcess>
#include <QTreeWidgetItem>
#include <QUrl>
#include <QDesktopServices>

// Projekt-Header
#include "cnetworkmanager.h"
#include "cdatabasemanager.h"
#include "coptions.h"

namespace Ui {
    class CMainWindow;
}

class CMainWindow : public QMainWindow
{
    Q_OBJECT

// Private Member
private:
    CDatabaseManager *mdb;
    CNetworkManager *mnet;
    COptions *mopt;
    QProcess* m_reader;

// Public Member
public:
    CDatabaseManager *GetDBman();
    void SetupTree();

public:
    explicit CMainWindow(QWidget *parent = 0);
    ~CMainWindow();


private slots:
    void on_cmdClose_clicked();
    void on_cmdAdd_clicked();
    void on_cmdOptions_clicked();

    void on_cmdUpdate_clicked();

    void on_trvCharts_itemDoubleClicked(QTreeWidgetItem *item, int column);

private:
    Ui::CMainWindow *ui;
    void closeEvent(QCloseEvent *e);

};

#endif // CMAINWINDOW_H
