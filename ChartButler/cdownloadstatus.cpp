#include "cdownloadstatus.h"
#include "ui_cdownloadstatus.h"

CDownloadStatus::CDownloadStatus(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDownloadStatus)
{
    ui->setupUi(this);
}

CDownloadStatus::CDownloadStatus(QString *pFileName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDownloadStatus)
{
    ui->setupUi(this);
    ui->lblState->setText("Lade Datei");
    ui->lblInfo->setText(*pFileName);
}

CDownloadStatus::~CDownloadStatus()
{
    delete ui;
}

void CDownloadStatus::setStatusText(QString *pStatus)
{
    ui->lblState->setText(*pStatus);
}

void CDownloadStatus::setFileName(QString *pFileName)
{
    ui->lblInfo->setText(*pFileName);
}

void CDownloadStatus::setActualProgress(qint64 pRcvd, qint64 pTotal)
{
    int lPercent = pRcvd * 100 / pTotal;
    ui->prbDlStatus->setValue(lPercent);
    if(lPercent == 100)
    {
        hide();
    }
}
