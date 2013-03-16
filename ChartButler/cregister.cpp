#include "cregister.h"
#include "ui_cregister.h"

CRegister::CRegister(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::CRegister)
{
  ui->setupUi(this);
  settings = new QSettings(gCOMPANY, gAPP);
}

CRegister::~CRegister()
{
  delete ui;
}

void CRegister::on_buttonBox_accepted()
{
    settings->setValue("userMail", ui->txtEmail->text());
    settings->setValue("userName", ui->txtName->text());
    settings->setValue("nomoreRegister",false);
    CNetworkManager* lnet = new CNetworkManager();
    if(lnet->sendRegistration())
    {
        settings->setValue("nomoreRegister", true);
    }
}

void CRegister::on_buttonBox_rejected()
{
    settings->setValue("userMail", "Unregistriert");
    settings->setValue("userName", "");
    settings->setValue("nomoreRegister",true);
}
