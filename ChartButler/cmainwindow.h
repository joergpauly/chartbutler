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
#include <QMouseEvent>
#include <QMessageBox>
#include <QInputDialog>
#include <QTreeWidgetItem>
#include <QMenu>
#include <QAction>


#ifdef Q_WS_WIN
#include <QProcess>
#endif

#ifdef Q_WS_X11
#include <QUrl>
#include <QDesktopServices>
#endif

// Projekt-Header
#include "cnetworkmanager.h"
#include "cdatabasemanager.h"
#include "coptions.h"
#include "chelp.h"

namespace Ui
{
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
    QMouseEvent* m_lastMouseEvent;
    QMenu *m_contextMenu;
    QAction *m_actRemove;
    QAction *m_actUpdate;
    QAction *m_actShowInReader;
    QTreeWidgetItem* m_clickedItem;


// Public Member
public:
    CDatabaseManager *GetDBman();
    void SetupTree();
    void updateField(QString* pICAO);
    explicit CMainWindow(QWidget *parent = 0);
    ~CMainWindow();

// Private Member

private:
    void setupMenu();

private slots:
    void on_cmdClose_clicked();
    void on_cmdAdd_clicked();
    void on_cmdOptions_clicked();
    void on_cmdUpdate_clicked();
    void on_trvCharts_itemDoubleClicked(QTreeWidgetItem *item, int column);
    void on_actRemove();
    void on_actShow();
    void on_actUpdate();
    void on_trvCharts_itemChanged(QTreeWidgetItem *item, int column);

    void on_trvCharts_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    void on_cmdHelpInfo_clicked();

private:
    Ui::CMainWindow *ui;
    void closeEvent(QCloseEvent *e);    
    void contextMenuEvent(QContextMenuEvent* e);

};

#endif // CMAINWINDOW_H
