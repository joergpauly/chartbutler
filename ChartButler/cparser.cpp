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

#include "cparser.h"

CParser::CParser()
{
}

CParser::txtPos* CParser::getTextBetween(QString* pSource, QString* pStart, QString* pEnd, int pStartPos = 0)
{
    txtPos* lps = new txtPos();
    int lStart = pSource->indexOf(*pStart, pStartPos) + pStart->length();
    if(lStart == -1)
    {
        lps->pos = -1;
        return lps;
    }
    int lEnd = pSource->indexOf(*pEnd,lStart);
    if(lEnd < lStart)
    {
        lps->pos = -1;
        return lps;
    }
    if(lEnd == -1)
    {
        lps->pos = -1;
        return lps;
    }
    lps->text = pSource->mid(lStart,lEnd-lStart);
    lps->pos = lEnd;
    return lps;
}

CParser::txtPos* CParser::getTextAfter(QString* pSource, QString* pStart, int pLen, int pStartPos = 0)
{
    txtPos* lps = new txtPos();
    int lStart = pSource->indexOf(*pStart, pStartPos) + pStart->length();
    if(lStart == -1)
    {
        lps->pos = -1;
        return lps;
    }
    lps->text = pSource->mid(lStart,pLen);
    lps->pos = lStart + pLen;
    return lps;
}

QDate *CParser::fromHTMLDate(QString pHTMLtag)
{
    QDate* lDate = new QDate();
    int d;
    int m;
    int y;

    pHTMLtag = pHTMLtag.left(pHTMLtag.length() - 13);
    pHTMLtag = pHTMLtag.right(pHTMLtag.length() - 5);
    d = pHTMLtag.left(2).toInt();
    y = pHTMLtag.right(4).toInt();
    QString lTag(pHTMLtag.mid(3,3));

    if(lTag == "Jan")
        m = 1;

    if(lTag == "Feb")
        m = 2;

    if(lTag == "Mar")
        m = 3;

    if(lTag == "Apr")
        m = 4;

    if(lTag == "May")
        m = 5;

    if(lTag == "Jun")
        m = 6;

    if(lTag == "Jul")
        m = 7;

    if(lTag == "Aug")
        m = 8;

    if(lTag == "Sep")
        m = 9;

    if(lTag == "Oct")
        m = 10;

    if(lTag == "Nov")
        m = 11;

    if(lTag == "Dec")
        m = 12;

    lDate->setDate(y,m,d);
    return lDate;
}
