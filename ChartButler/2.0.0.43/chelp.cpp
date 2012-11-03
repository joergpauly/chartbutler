#include "chelp.h"
#include "ui_chelp.h"

CHelp::CHelp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CHelp)
{
    ui->setupUi(this);
}

CHelp::~CHelp()
{
    delete ui;
}
