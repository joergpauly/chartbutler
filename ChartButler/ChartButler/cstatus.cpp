/****************************************************************************************
*
*   This file is part of the ChartButler Project.
*   Copyright (C) 2012 Joerg Pauly
*   All Rights reserved
*
*   ChartButler ist Freie Software: Sie können es unter den Bedingungen
*   der GNU General Public License, wie von der Free Software Foundation,
*   Version 3 der Lizenz oder (nach Ihrer Option) jeder späteren
*   veröffentlichten Version, weiterverbreiten und/oder modifizieren.
*
*   Dieses Programm wird in der Hoffnung, dass es nützlich sein wird, aber
*   OHNE JEDE GEWÄHRLEISTUNG, bereitgestellt; sogar ohne die implizite
*   Gewährleistung der MARKTFÄHIGKEIT oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.
*   Siehe die GNU General Public License für weitere Details.
*
*   Sie sollten eine Kopie der GNU General Public License zusammen mit diesem
*   Programm erhalten haben. Wenn nicht, siehe <http://www.gnu.org/licenses/>.
*
*****************************************************************************************/

#include "cstatus.h"

CStatus::CStatus(QWidget *parent) :
    QDialog(parent)
{
    ui = new Ui::CStatus();
    ui->setupUi(this);
}

void CStatus::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void CStatus::setHeader(QString* pText)
{
    ui->lblStatus->setText(*pText);
}

void CStatus::clearList()
{
    ui->txtStatus->clear();
}

void CStatus::appendList(QString* pText)
{
    ui->txtStatus->append(*pText);
}
