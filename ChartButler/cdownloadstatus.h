#ifndef CDOWNLOADSTATUS_H
#define CDOWNLOADSTATUS_H

#include <QDialog>

namespace Ui {
class CDownloadStatus;
}

class CDownloadStatus : public QDialog
{
    Q_OBJECT
    
public:
    explicit CDownloadStatus(QWidget *parent = 0);
    explicit CDownloadStatus(QString* pFileName, QWidget* parent = 0);
    ~CDownloadStatus();

    void setStatusText(QString* pStatus);
    void setFileName(QString* pFileName);
    void setActualProgress(qint64 pRcvd, qint64 pTotal);
    
private:
    Ui::CDownloadStatus *ui;
};

#endif // CDOWNLOADSTATUS_H
