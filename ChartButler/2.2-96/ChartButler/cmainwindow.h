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
#include <QtWidgets/QMainWindow>
#include <QCloseEvent>
#include <QMouseEvent>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QInputDialog>
#include <QDesktopServices>
#include <QtWidgets/QTreeWidgetItem>
#include <QtWidgets/QMenu>
#include <QtWidgets/QAction>
#include <QList>


#ifdef Q_OS_WIN
#include <QProcess>
#endif


// Projekt-Header
#include "cnetworkmanager.h"
#include "cdatabasemanager.h"
#include "coptions.h"
#include "chelp.h"
#include "cregister.h"

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
    QTreeWidgetItem *m_clickedItem;
    QSettings *m_settings;
    bool m_networkReady;


// Public Member
public:
    QList<QString>* m_AmendedFields;
    QList<QString>* m_AmendedCharts;
    CDatabaseManager *GetDBman();
    CNetworkManager *getNetworkMan();
    void SetupTree();
    void updateField(QString* pICAO);
    void nextField();
    void markAmmendedFields();
    explicit CMainWindow(QWidget *parent = 0);
    QSettings* settings();
    ~CMainWindow();

// Private Member

private:
    void setupMenu();
    bool checkRegistered();

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
    void on_cmdGat24_clicked();

private:
    Ui::CMainWindow *ui;
    void closeEvent(QCloseEvent *e);    
    void contextMenuEvent(QContextMenuEvent* e);
    QList<QString*>* parseFields(QString pICAO);

};

#endif // CMAINWINDOW_H
