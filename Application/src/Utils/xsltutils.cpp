#include "xsltutils.h"

#include <libxslt/transform.h>
#include <libxslt/xsltutils.h>


xmlDocPtr xmlParseDocEx(const xmlChar* cur)
{
    auto res = xmlParseDoc(cur);

    if (res == nullptr) throw XmlException();
    else                return res;
}

xmlDocPtr xmlParseFileEx(const char* filename)
{
    auto res = xmlParseFile(filename);

    if (res == nullptr) throw XmlException();
    else                return res;
}

xsltStylesheetPtr xsltParseStylesheetDocEx(xmlDocPtr doc)
{
    auto res = xsltParseStylesheetDoc(doc);

    if (res == nullptr) throw XmlException();
    else                return res;
}

xmlDocPtr xsltApplyStylesheetEx(xsltStylesheetPtr style, xmlDocPtr doc,
                                const char** params)
{
    auto res = xsltApplyStylesheet(style, doc, params);

    if (res == nullptr) throw XmlException();
    else                return res;
}

int xsltSaveResultToFileEx(FILE* file, xmlDocPtr result,
                           xsltStylesheetPtr style)
{
    auto res = xsltSaveResultToFile(file, result, style);

    if (res == -1) throw XmlException();
    else           return res;
}
