/********************************************************************************
** Form generated from reading UI file 'cstatus.ui'
**
** Created: Sat 3. Nov 17:53:22 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CSTATUS_H
#define UI_CSTATUS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CStatus
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *lblStatus;
    QTreeWidget *tblStatus;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *CStatus)
    {
        if (CStatus->objectName().isEmpty())
            CStatus->setObjectName(QString::fromUtf8("CStatus"));
        CStatus->resize(584, 526);
        verticalLayoutWidget = new QWidget(CStatus);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 561, 511));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lblStatus = new QLabel(verticalLayoutWidget);
        lblStatus->setObjectName(QString::fromUtf8("lblStatus"));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        lblStatus->setFont(font);

        verticalLayout->addWidget(lblStatus);

        tblStatus = new QTreeWidget(verticalLayoutWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(1, QString::fromUtf8("2"));
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        tblStatus->setHeaderItem(__qtreewidgetitem);
        tblStatus->setObjectName(QString::fromUtf8("tblStatus"));
        tblStatus->setFocusPolicy(Qt::NoFocus);
        tblStatus->setContextMenuPolicy(Qt::NoContextMenu);
        tblStatus->setAutoFillBackground(true);
        tblStatus->setFrameShape(QFrame::Box);
        tblStatus->setFrameShadow(QFrame::Raised);
        tblStatus->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tblStatus->setTabKeyNavigation(false);
        tblStatus->setProperty("showDropIndicator", QVariant(false));
        tblStatus->setDragDropOverwriteMode(false);
        tblStatus->setAlternatingRowColors(true);
        tblStatus->setSelectionMode(QAbstractItemView::NoSelection);
        tblStatus->setSelectionBehavior(QAbstractItemView::SelectRows);
        tblStatus->setTextElideMode(Qt::ElideNone);
        tblStatus->setItemsExpandable(false);
        tblStatus->setAnimated(false);
        tblStatus->setExpandsOnDoubleClick(false);
        tblStatus->setColumnCount(2);
        tblStatus->header()->setDefaultSectionSize(300);
        tblStatus->header()->setMinimumSectionSize(300);
        tblStatus->header()->setStretchLastSection(true);

        verticalLayout->addWidget(tblStatus);

        buttonBox = new QDialogButtonBox(verticalLayoutWidget);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(CStatus);
        QObject::connect(buttonBox, SIGNAL(accepted()), CStatus, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), CStatus, SLOT(reject()));

        QMetaObject::connectSlotsByName(CStatus);
    } // setupUi

    void retranslateUi(QDialog *CStatus)
    {
        CStatus->setWindowTitle(QApplication::translate("CStatus", "Dialog", 0, QApplication::UnicodeUTF8));
        lblStatus->setText(QApplication::translate("CStatus", "TextLabel", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tblStatus->setToolTip(QApplication::translate("CStatus", "Aktions-Protokoll des Updates", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    } // retranslateUi

};

namespace Ui {
    class CStatus: public Ui_CStatus {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CSTATUS_H
