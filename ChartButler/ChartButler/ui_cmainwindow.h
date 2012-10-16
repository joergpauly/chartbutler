/********************************************************************************
** Form generated from reading UI file 'cmainwindow.ui'
**
** Created: Sun 7. Oct 13:11:45 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CMAINWINDOW_H
#define UI_CMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CMainWindow
{
public:
    QWidget *centralWidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QTreeWidget *trvCharts;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *cmdAdd;
    QPushButton *cmdUpdate;
    QPushButton *cmdOptions;
    QSpacerItem *verticalSpacer;
    QPushButton *cmdHelpInfo;
    QPushButton *cmdClose;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CMainWindow)
    {
        if (CMainWindow->objectName().isEmpty())
            CMainWindow->setObjectName(QString::fromUtf8("CMainWindow"));
        CMainWindow->resize(585, 579);
        QIcon icon;
        icon.addFile(QString::fromUtf8("Icon1.ico"), QSize(), QIcon::Normal, QIcon::Off);
        CMainWindow->setWindowIcon(icon);
        centralWidget = new QWidget(CMainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(-1, -1, 431, 531));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        trvCharts = new QTreeWidget(horizontalLayoutWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(1, QString::fromUtf8("2"));
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        trvCharts->setHeaderItem(__qtreewidgetitem);
        trvCharts->setObjectName(QString::fromUtf8("trvCharts"));
        trvCharts->setColumnCount(2);
        trvCharts->header()->setDefaultSectionSize(200);
        trvCharts->header()->setMinimumSectionSize(100);

        horizontalLayout->addWidget(trvCharts);

        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(430, 0, 151, 531));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        cmdAdd = new QPushButton(verticalLayoutWidget);
        cmdAdd->setObjectName(QString::fromUtf8("cmdAdd"));

        verticalLayout->addWidget(cmdAdd);

        cmdUpdate = new QPushButton(verticalLayoutWidget);
        cmdUpdate->setObjectName(QString::fromUtf8("cmdUpdate"));

        verticalLayout->addWidget(cmdUpdate);

        cmdOptions = new QPushButton(verticalLayoutWidget);
        cmdOptions->setObjectName(QString::fromUtf8("cmdOptions"));

        verticalLayout->addWidget(cmdOptions);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        cmdHelpInfo = new QPushButton(verticalLayoutWidget);
        cmdHelpInfo->setObjectName(QString::fromUtf8("cmdHelpInfo"));

        verticalLayout->addWidget(cmdHelpInfo);

        cmdClose = new QPushButton(verticalLayoutWidget);
        cmdClose->setObjectName(QString::fromUtf8("cmdClose"));

        verticalLayout->addWidget(cmdClose);

        CMainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(CMainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 585, 21));
        CMainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CMainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        CMainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(CMainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        CMainWindow->setStatusBar(statusBar);

        retranslateUi(CMainWindow);

        QMetaObject::connectSlotsByName(CMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *CMainWindow)
    {
        CMainWindow->setWindowTitle(QApplication::translate("CMainWindow", "ChartButler (C) 2012 Joerg Pauly", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        cmdAdd->setToolTip(QApplication::translate("CMainWindow", "Einen neuen Flugplatz abonnieren und die Karten herunterladen.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        cmdAdd->setText(QApplication::translate("CMainWindow", "Flugplatz hinzuf\303\274gen...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        cmdUpdate->setToolTip(QApplication::translate("CMainWindow", "Alle abonnierten Karten auf Aktualit\303\244t pr\303\274fen und ggf. aktualisieren.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        cmdUpdate->setText(QApplication::translate("CMainWindow", "Karten aktualisieren", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        cmdOptions->setToolTip(QApplication::translate("CMainWindow", "Login-Daten f\303\274r GAT24.de und Karten-Ablagepfad festlegen.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        cmdOptions->setText(QApplication::translate("CMainWindow", "Optionen...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        cmdHelpInfo->setToolTip(QApplication::translate("CMainWindow", "Hilfe zu und Informationen \303\274ber ChartButler anzeigen.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        cmdHelpInfo->setText(QApplication::translate("CMainWindow", "Hilfe / Info...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        cmdClose->setToolTip(QApplication::translate("CMainWindow", "ChartButler beenden und Fenster schlie\303\237en.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        cmdClose->setText(QApplication::translate("CMainWindow", "Schlie\303\237en", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CMainWindow: public Ui_CMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CMAINWINDOW_H
