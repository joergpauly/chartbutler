#include "cregister.h"
#include "ui_cregister.h"

CRegister::CRegister(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::CRegister)
{
  ui->setupUi(this);
}

CRegister::~CRegister()
{
  delete ui;
}
