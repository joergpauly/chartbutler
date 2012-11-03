/********************************************************************************
** Form generated from reading UI file 'coptions.ui'
**
** Created: Sat 3. Nov 17:53:22 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COPTIONS_H
#define UI_COPTIONS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include "coptions.h"

QT_BEGIN_NAMESPACE

class Ui_COptions
{
public:
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBox;
    QLineEdit *txtChartPath;
    QPushButton *cmdBrowsePath;
    QGroupBox *groupBox_2;
    QLineEdit *txtUserName;
    QLabel *label;
    QLineEdit *txtPassword;
    QLabel *label_2;
    QGroupBox *groupBox_3;
    QLineEdit *txtPdfExePath;
    QPushButton *cmdBrowsePdf;

    void setupUi(QDialog *COptions)
    {
        if (COptions->objectName().isEmpty())
            COptions->setObjectName(QString::fromUtf8("COptions"));
        COptions->setWindowModality(Qt::ApplicationModal);
        COptions->resize(386, 280);
        buttonBox = new QDialogButtonBox(COptions);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(290, 20, 81, 141));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        groupBox = new QGroupBox(COptions);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 20, 261, 61));
        txtChartPath = new QLineEdit(groupBox);
        txtChartPath->setObjectName(QString::fromUtf8("txtChartPath"));
        txtChartPath->setGeometry(QRect(10, 20, 211, 20));
        cmdBrowsePath = new QPushButton(groupBox);
        cmdBrowsePath->setObjectName(QString::fromUtf8("cmdBrowsePath"));
        cmdBrowsePath->setGeometry(QRect(220, 20, 31, 23));
        groupBox_2 = new QGroupBox(COptions);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(9, 90, 261, 71));
        txtUserName = new QLineEdit(groupBox_2);
        txtUserName->setObjectName(QString::fromUtf8("txtUserName"));
        txtUserName->setGeometry(QRect(82, 20, 161, 20));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 20, 61, 16));
        txtPassword = new QLineEdit(groupBox_2);
        txtPassword->setObjectName(QString::fromUtf8("txtPassword"));
        txtPassword->setGeometry(QRect(80, 40, 161, 20));
        txtPassword->setEchoMode(QLineEdit::Password);
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 40, 46, 13));
        groupBox_3 = new QGroupBox(COptions);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 170, 261, 61));
        txtPdfExePath = new QLineEdit(groupBox_3);
        txtPdfExePath->setObjectName(QString::fromUtf8("txtPdfExePath"));
        txtPdfExePath->setGeometry(QRect(10, 20, 211, 20));
        cmdBrowsePdf = new QPushButton(groupBox_3);
        cmdBrowsePdf->setObjectName(QString::fromUtf8("cmdBrowsePdf"));
        cmdBrowsePdf->setGeometry(QRect(220, 20, 31, 23));

        retranslateUi(COptions);
        QObject::connect(buttonBox, SIGNAL(accepted()), COptions, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), COptions, SLOT(reject()));

        QMetaObject::connectSlotsByName(COptions);
    } // setupUi

    void retranslateUi(QDialog *COptions)
    {
        COptions->setWindowTitle(QApplication::translate("COptions", "Programmoptionen", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("COptions", "Karten-Verzeichnis", 0, QApplication::UnicodeUTF8));
        cmdBrowsePath->setText(QApplication::translate("COptions", "...", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("COptions", "GAT24.de-Login-Daten", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("COptions", "Username:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("COptions", "Passwort:", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("COptions", "PDF-Reader (ausf\303\274hrbare Datei)", 0, QApplication::UnicodeUTF8));
        cmdBrowsePdf->setText(QApplication::translate("COptions", "...", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class COptions: public Ui_COptions {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COPTIONS_H
