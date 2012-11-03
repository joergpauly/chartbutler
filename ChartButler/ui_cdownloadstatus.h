/********************************************************************************
** Form generated from reading UI file 'cdownloadstatus.ui'
**
** Created: Mon 22. Oct 20:07:54 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CDOWNLOADSTATUS_H
#define UI_CDOWNLOADSTATUS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>

QT_BEGIN_NAMESPACE

class Ui_CDownloadStatus
{
public:
    QLabel *lblState;
    QLabel *lblInfo;
    QProgressBar *prbDlStatus;

    void setupUi(QDialog *CDownloadStatus)
    {
        if (CDownloadStatus->objectName().isEmpty())
            CDownloadStatus->setObjectName(QString::fromUtf8("CDownloadStatus"));
        CDownloadStatus->resize(400, 113);
        lblState = new QLabel(CDownloadStatus);
        lblState->setObjectName(QString::fromUtf8("lblState"));
        lblState->setGeometry(QRect(30, 20, 351, 16));
        lblInfo = new QLabel(CDownloadStatus);
        lblInfo->setObjectName(QString::fromUtf8("lblInfo"));
        lblInfo->setGeometry(QRect(30, 40, 351, 16));
        prbDlStatus = new QProgressBar(CDownloadStatus);
        prbDlStatus->setObjectName(QString::fromUtf8("prbDlStatus"));
        prbDlStatus->setGeometry(QRect(20, 70, 361, 23));
        prbDlStatus->setValue(0);

        retranslateUi(CDownloadStatus);

        QMetaObject::connectSlotsByName(CDownloadStatus);
    } // setupUi

    void retranslateUi(QDialog *CDownloadStatus)
    {
        CDownloadStatus->setWindowTitle(QApplication::translate("CDownloadStatus", "Dialog", 0, QApplication::UnicodeUTF8));
        lblState->setText(QApplication::translate("CDownloadStatus", "TextLabel", 0, QApplication::UnicodeUTF8));
        lblInfo->setText(QApplication::translate("CDownloadStatus", "TextLabel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CDownloadStatus: public Ui_CDownloadStatus {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CDOWNLOADSTATUS_H
