/********************************************************************************
** Form generated from reading UI file 'cstatus.ui'
**
** Created: Sat 6. Oct 19:37:35 2012
**      by: Qt User Interface Compiler version 4.7.4
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
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CStatus
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *lblStatus;
    QTextEdit *txtStatus;
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

        verticalLayout->addWidget(lblStatus);

        txtStatus = new QTextEdit(verticalLayoutWidget);
        txtStatus->setObjectName(QString::fromUtf8("txtStatus"));

        verticalLayout->addWidget(txtStatus);

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
    } // retranslateUi

};

namespace Ui {
    class CStatus: public Ui_CStatus {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CSTATUS_H
