#ifndef CREGISTER_H
#define CREGISTER_H

#include <QDialog>

namespace Ui {
  class CRegister;
}

class CRegister : public QDialog
{
  Q_OBJECT
  
public:
  explicit CRegister(QWidget *parent = 0);
  ~CRegister();
  
private:
  Ui::CRegister *ui;
};

#endif // CREGISTER_H
