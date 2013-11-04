/****************************************************************************************
*
*   This file is part of the ChartButler Project.
*   Copyright (C) 2013 Joerg Pauly
*   Created 02.11.2013 by joerg
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

#ifndef CPARSER_H
#define CPARSER_H

#include <QString>
#include <QDate>

class CParser
{
public:


    struct txtPos
       {
           QString text;
           int     pos;
       };

    CParser();
    txtPos *getTextBetween(QString* pSource, QString* pStart, QString* pEnd, int pStartPos);
    txtPos *getTextAfter(QString* pSource, QString* pStart, int pLen, int pStartPos);
    void getFieldName(QString* pStream);
    QDate* fromHTMLDate(QString pHTMLtag);
};

#endif // CPARSER_H
