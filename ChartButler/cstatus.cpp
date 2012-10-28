/****************************************************************************************
*
*   This file is part of the ChartButler Project.
*   Copyright (C) 2012 Joerg Pauly
*   All Rights reserved
*
*   ChartButler ist Freie Software: Sie k�nnen es unter den Bedingungen
*   der GNU General Public License, wie von der Free Software Foundation,
*   Version 3 der Lizenz oder (nach Ihrer Option) jeder sp�teren
*   ver�ffentlichten Version, weiterverbreiten und/oder modifizieren.
*
*   Dieses Programm wird in der Hoffnung, dass es n�tzlich sein wird, aber
*   OHNE JEDE GEW�HRLEISTUNG, bereitgestellt; sogar ohne die implizite
*   Gew�hrleistung der MARKTF�HIGKEIT oder EIGNUNG F�R EINEN BESTIMMTEN ZWECK.
*   Siehe die GNU General Public License f�r weitere Details.
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
    QStringList lHeaders;
    lHeaders.append("Platz / Karten");
    lHeaders.append("Aktion");
    ui->tblStatus->setHeaderLabels(lHeaders);
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
    ui->tblStatus->clear();
}

void CStatus::appendList(QTreeWidgetItem* pItem)
{    
    ui->tblStatus->addTopLevelItem(pItem);
}
