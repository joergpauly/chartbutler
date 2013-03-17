#include "cregister.h"
#include "ui_cregister.h"

#include "cmainwindow.h"

CRegister::CRegister(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::CRegister)
{
    ui->setupUi(this);
    m_settings = ((CMainWindow*)parent)->settings();
}

CRegister::~CRegister()
{
    delete ui;
    delete m_settings;
}

void CRegister::on_buttonBox_accepted()
{
    m_settings->setValue("userMail", ui->txtEmail->text());
    m_settings->setValue("userName", ui->txtName->text());
    m_settings->setValue("nomoreRegister",false);
    CNetworkManager* lnet = new CNetworkManager();
    if(lnet->sendRegistration())
    {
        m_settings->setValue("nomoreRegister", true);
    }
}

void CRegister::on_buttonBox_rejected()
{
    m_settings->setValue("userMail", "Unregistriert");
    m_settings->setValue("userName", "");
    m_settings->setValue("nomoreRegister",true);
}
