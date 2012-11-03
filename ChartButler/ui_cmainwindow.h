/********************************************************************************
** Form generated from reading UI file 'cmainwindow.ui'
**
** Created: Sat 3. Nov 17:53:20 2012
**      by: Qt User Interface Compiler version 4.8.1
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
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horiInner;
    QTreeWidget *trvCharts;
    QVBoxLayout *vertiInner;
    QPushButton *cmdAdd;
    QPushButton *cmdUpdate;
    QPushButton *cmdOptions;
    QSpacerItem *verticalSpacer;
    QPushButton *cmdGat24;
    QSpacerItem *verticalSpacer_2;
    QPushButton *cmdHelpInfo;
    QPushButton *cmdClose;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CMainWindow)
    {
        if (CMainWindow->objectName().isEmpty())
            CMainWindow->setObjectName(QString::fromUtf8("CMainWindow"));
        CMainWindow->resize(604, 604);
        QIcon icon;
        icon.addFile(QString::fromUtf8("Icon1.ico"), QSize(), QIcon::Normal, QIcon::Off);
        CMainWindow->setWindowIcon(icon);
        centralWidget = new QWidget(CMainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horiInner = new QHBoxLayout();
        horiInner->setSpacing(6);
        horiInner->setObjectName(QString::fromUtf8("horiInner"));
        horiInner->setSizeConstraint(QLayout::SetMinAndMaxSize);
        trvCharts = new QTreeWidget(centralWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(1, QString::fromUtf8("2"));
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        trvCharts->setHeaderItem(__qtreewidgetitem);
        trvCharts->setObjectName(QString::fromUtf8("trvCharts"));
        trvCharts->setContextMenuPolicy(Qt::ActionsContextMenu);
        trvCharts->setAutoFillBackground(true);
        trvCharts->setProperty("showDropIndicator", QVariant(false));
        trvCharts->setAlternatingRowColors(true);
        trvCharts->setAnimated(true);
        trvCharts->setColumnCount(2);
        trvCharts->header()->setDefaultSectionSize(300);
        trvCharts->header()->setMinimumSectionSize(100);
        trvCharts->header()->setStretchLastSection(false);

        horiInner->addWidget(trvCharts);


        horizontalLayout->addLayout(horiInner);

        vertiInner = new QVBoxLayout();
        vertiInner->setSpacing(6);
        vertiInner->setObjectName(QString::fromUtf8("vertiInner"));
        cmdAdd = new QPushButton(centralWidget);
        cmdAdd->setObjectName(QString::fromUtf8("cmdAdd"));

        vertiInner->addWidget(cmdAdd);

        cmdUpdate = new QPushButton(centralWidget);
        cmdUpdate->setObjectName(QString::fromUtf8("cmdUpdate"));

        vertiInner->addWidget(cmdUpdate);

        cmdOptions = new QPushButton(centralWidget);
        cmdOptions->setObjectName(QString::fromUtf8("cmdOptions"));

        vertiInner->addWidget(cmdOptions);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vertiInner->addItem(verticalSpacer);

        cmdGat24 = new QPushButton(centralWidget);
        cmdGat24->setObjectName(QString::fromUtf8("cmdGat24"));
        cmdGat24->setMaximumSize(QSize(130, 130));
        cmdGat24->setLayoutDirection(Qt::LeftToRight);
        cmdGat24->setAutoFillBackground(true);
        cmdGat24->setText(QString::fromUtf8(""));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("../ChartButlerCS/ChartButlerCS/gat24.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        cmdGat24->setIcon(icon1);
        cmdGat24->setIconSize(QSize(128, 128));

        vertiInner->addWidget(cmdGat24);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vertiInner->addItem(verticalSpacer_2);

        cmdHelpInfo = new QPushButton(centralWidget);
        cmdHelpInfo->setObjectName(QString::fromUtf8("cmdHelpInfo"));

        vertiInner->addWidget(cmdHelpInfo);

        cmdClose = new QPushButton(centralWidget);
        cmdClose->setObjectName(QString::fromUtf8("cmdClose"));

        vertiInner->addWidget(cmdClose);


        horizontalLayout->addLayout(vertiInner);

        CMainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(CMainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 604, 20));
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
        trvCharts->setToolTip(QApplication::translate("CMainWindow", "<html><head/><body><p>Doppel-Click zum Anzeigen</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
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
        cmdGat24->setToolTip(QString());
#endif // QT_NO_TOOLTIP
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
