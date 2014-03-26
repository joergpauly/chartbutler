/****************************************************************************************
*
*   This file is part of the ChartButler Project.
*   Copyright (C) 2012 Joerg Pauly
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
/***********************************************************
*
*   globals.h
*   Einige globale #define's.
*
**********************************************************/

#ifndef GLOBALS_H
#define GLOBALS_H

// Settings-Schlüssel
#define gCOMPANY "MEGAMover.de"
#define gAPP "ChartButler V2.1"

// Version
#define MAJOR 2
#define MINOR 2
#define REV   96

// Server-URLs
#define LOGINURL "http://www.gat24.de/data.php?rubrik=aktuell&unterrubrik=neues&dokument=neues&SID=0"
#define ICAOURL "http://www.gat24.de/data.php?rubrik=briefing&unterrubrik=flugplaetze&dokument=karten&ICAO="
#define UPDATEURLLEAD "http://www.gat24.de/data.php?rubrik=aktuell&unterrubrik=neues&dokument=aip_aktuell&SID="
#define UPDATEURLTAIL "&printable=true"

#endif // GLOBALS_H
