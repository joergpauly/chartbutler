#ifndef CREGISTER_H
#define CREGISTER_H

#include <QDialog>
#include <QSettings>

#include "cnetworkmanager.h"
#include "globals.h"

namespace Ui {
  class CRegister;
}

class CRegister : public QDialog
{
  Q_OBJECT
  
public:
  explicit CRegister(QWidget *parent = 0);
  ~CRegister();
  
private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
  Ui::CRegister *ui;
  QSettings* settings;
};

#endif // CREGISTER_H
