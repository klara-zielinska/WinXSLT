#ifndef XSLTEX_H
#define XSLTEX_H

#include <libxml/tree.h>
#include <libxslt/xsltInternals.h>
#include <exception>

class XsltException : public std::exception
{ };


xmlDocPtr         xmlParseDocEx(const xmlChar* cur);
xmlDocPtr         xmlParseFileEx(const char* filename);
xsltStylesheetPtr xsltParseStylesheetDocEx(xmlDocPtr doc);
xmlDocPtr         xsltApplyStylesheetEx(xsltStylesheetPtr style, xmlDocPtr doc,
                                        const char ** params);
int               xsltSaveResultToFileEx(FILE* file, xmlDocPtr result,
                                         xsltStylesheetPtr style);

#endif // XSLTEX_H
