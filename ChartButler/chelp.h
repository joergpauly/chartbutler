#ifndef CHELP_H
#define CHELP_H

#include <QtWidgets/QDialog>

namespace Ui {
class CHelp;
}

class CHelp : public QDialog
{
    Q_OBJECT
    
public:
    explicit CHelp(QWidget *parent = 0);
    ~CHelp();
    
private:
    Ui::CHelp *ui;
};

#endif // CHELP_H
