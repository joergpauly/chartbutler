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

#ifndef CPROGRESS_H
#define CPROGRESS_H

#include <QDialog>

namespace Ui {
class CProgress;
}

class CProgress : public QDialog
{
    Q_OBJECT

public:
    explicit CProgress(QWidget *parent = 0);
    ~CProgress();
    void setFields(int pFlds);
    void setFiles(int pFiles);
    void setFieldName(QString pName);
    void setFileName(QString pName);
    void setActualFields(int pFlds);
    void setActualFiles(int pFiles);

private:
    Ui::CProgress *ui;
    int m_Fields;
    int m_actFld;
    int m_Files;
    int m_actFile;
    QString m_FieldName;
    QString m_FileName;

private slots:
    void updateData();

signals:
    void newData();
};

#endif // CPROGRESS_H
