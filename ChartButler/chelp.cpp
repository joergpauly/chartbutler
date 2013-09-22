#include "chelp.h"
#include "ui_chelp.h"

CHelp::CHelp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CHelp)
{   
    QSettings *lsettings = new QSettings(gCOMPANY, gAPP);
    QString lAbout;
    lAbout = "ChartButler V";
    lAbout.append(MAJOR);
    lAbout.append(".");
    lAbout.append(MINOR);
    lAbout.append(".");
    lAbout.append(REV);
    lAbout.append("\n\n");
    if(lsettings->value("userMail", "NIL")=="NIL")
    {
        lAbout.append("Dieses Programm ist unregistriert.");
    }
    else
    {
        lAbout.append("Dieses Programm ist registriert für:\n");
        lAbout.append(lsettings->value("userName").toString());
        lAbout.append(" - ");
        lAbout.append(lsettings->value("userMail").toString());        
        lAbout.append("\n\n");

    }
    ui->setupUi(this);
    ui->txtAbout->setText(lAbout);    
}

CHelp::~CHelp()
{
    delete ui;
}
