/****************************************************************************************
*
*   This file is part of the ChartButler Project.
*   Copyright (C) 2012 Joerg Pauly
*   All Rights reserved
*
*   ChartButler ist Freie Software: Sie k�nnen es unter den Bedingungen
*   der GNU Lesser General Public License, wie von der Free Software Foundation,
*   Version 3 der Lizenz oder (nach Ihrer Option) jeder sp�teren
*   ver�ffentlichten Version, weiterverbreiten und/oder modifizieren.
*
*   Dieses Programm wird in der Hoffnung, dass es n�tzlich sein wird, aber
*   OHNE JEDE GEW�HRLEISTUNG, bereitgestellt; sogar ohne die implizite
*   Gew�hrleistung der MARKTF�HIGKEIT oder EIGNUNG F�R EINEN BESTIMMTEN ZWECK.
*   Siehe die GNU Lesser General Public License f�r weitere Details.
*
*   Sie sollten eine Kopie der GNU Lesser General Public License zusammen mit diesem
*   Programm erhalten haben. Wenn nicht, siehe <http://www.gnu.org/licenses/>.
*
*****************************************************************************************/

#include <QtWidgets/QApplication>
#include "cmainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);    
    CMainWindow w;
    w.show();

    return a.exec();
}
