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
/***********************************************************
*
*   globals.h
*   Einige globale #define's.
*
**********************************************************/


#ifndef GLOBALS_H
#define GLOBALS_H

// Settings-Schl�ssel
#define gCOMPANY "MEGAMover.de"
#define gAPP "ChartButler V2.1"

// Version
#define MAJOR 2
#define MINOR 1
#define REV   55

// Server-URLs
#define LOGINURL "http://www.gat24.de/data.php?rubrik=aktuell&unterrubrik=neues&dokument=neues&SID=0"
#define ICAOURL "http://www.gat24.de/data.php?rubrik=briefing&unterrubrik=flugplaetze&dokument=karten&ICAO="
#define AMENDURL "http://www.gat24.de/data.php?rubrik=aktuell&unterrubrik=neues&dokument=aip_aktuell&SID=&printable=true"

#endif // GLOBALS_H
