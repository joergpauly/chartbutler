/****************************************************************************************
*
*   This file is part of the ChartButler Project.
*   Copyright (C) 2013 Joerg Pauly
*   Created 04.11.2013 by joerg
*   All Rights reserved
*
*   ChartButler ist Freie Software: Sie können es unter den Bedingungen
*   der GNU Lesser General Public License, wie von der Free Software Foundation,
*   Version 3 der Lizenz oder (nach Ihrer Option) jeder späteren
*   veröffentlichten Version, weiterverbreiten und/oder modifizieren.
*
*   Dieses Programm wird in der Hoffnung, dass es nützlich sein wird, aber
*   OHNE JEDE GEWÄHRLEISTUNG, bereitgestellt; sogar ohne die implizite
*   Gewährleistung der MARKTFÄHIGKEIT oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.
*   Siehe die GNU Lesser General Public License für weitere Details.
*
*   Sie sollten eine Kopie der GNU Lesser General Public License zusammen mit diesem
*   Programm erhalten haben. Wenn nicht, siehe <http://www.gnu.org/licenses/>.
*
*****************************************************************************************/

#include "cprogress.h"
#include "ui_cprogress.h"

CProgress::CProgress(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CProgress)
{
    setModal(true);
    connect(this, SIGNAL(newData()), this, SLOT(updateData()));
    ui->setupUi(this);
}

CProgress::~CProgress()
{
    delete ui;
}

void CProgress::setFields(int pFlds)
{
    m_Fields = pFlds;
    emit newData();
}

void CProgress::setFiles(int pFiles)
{
    m_Files = pFiles;
    emit newData();
}

void CProgress::setFieldName(QString pName)
{
    m_FieldName = pName;
    emit newData();
}

void CProgress::setFileName(QString pName)
{
    m_FileName = pName;
    emit newData();
}

void CProgress::setActualFields(int pFlds)
{
    m_actFld = pFlds;
    emit newData();
}

void CProgress::setActualFiles(int pFiles)
{
    m_actFile = pFiles;
    emit newData();
}

void CProgress::updateData()
{
    ui->txtFieldName->setText(m_FieldName);
    ui->txtFileName->setText(m_FileName);
    ui->prgFields->setMinimum(0);
    ui->prgFields->setMaximum(m_Fields);
    ui->prgFields->setFormat("%v/%m");
    ui->prgFields->setValue(m_actFld);
    ui->prgFiles->setMinimum(0);
    ui->prgFiles->setMaximum(m_Files);
    ui->prgFiles->setFormat("%v/%m");
    ui->prgFiles->setValue(m_actFile);
    ui->prgFields->update();
    ui->prgFiles->update();
}
