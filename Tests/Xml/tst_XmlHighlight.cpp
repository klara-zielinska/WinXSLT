#include "tst_XmlHighlight.h"
#include "testtools.h"
#include "Utils/xsltutils.h"
#include <libxml2/libxml/tree.h>


tst_XmlHighlight::tst_XmlHighlight()
{
}

tst_XmlHighlight::~tst_XmlHighlight()
{
}

void tst_XmlHighlight::initTestCase()
{
    QFile f1(":/resources/XmlDir/cds/book.xml");
    f1.open(QFile::ReadOnly);
    xmlDoc1 = QString::fromUtf8(f1.readAll());
    f1.close();

    QFile f2(":/resources/XmlDir/cds/cds2html.xslt");
    f2.open(QFile::ReadOnly);
    xmlDoc2 = QString::fromUtf8(f2.readAll());
    f2.close();

    QFile f3(":/resources/XmlDir/cds/book_highlight.html");
    f3.open(QFile::ReadOnly);
    xmlDocHighlight1 = QString::fromUtf8(f3.readAll());
    f3.close();

    QFile f4(":/resources/XmlDir/cds/cds2html_highlight.html");
    f4.open(QFile::ReadOnly);
    xmlDocHighlight2 = QString::fromUtf8(f4.readAll());
    f4.close();
}

void tst_XmlHighlight::cleanupTestCase()
{
}

void tst_XmlHighlight::testInHtml1()
{
    QString higlight = XmlHighlight::InHtml(xmlDoc1);
    xmlDocPtr highlightDoc =
            xmlParseDocEx(XmlCString::of(higlight.toUtf8()));
    xmlDocPtr expectedDoc =
            xmlParseDocEx(XmlCString::of(xmlDocHighlight1.toUtf8()));
    QVERIFY(xmlSimpleNodesEq(xmlDocGetRootElement(highlightDoc),
                             xmlDocGetRootElement(expectedDoc)));
    xmlFreeDoc(highlightDoc);
    xmlFreeDoc(expectedDoc);
}

void tst_XmlHighlight::testInHtml2()
{
    QString higlight = XmlHighlight::InHtml(xmlDoc2);
    xmlDocPtr highlightDoc =
            xmlParseDocEx(XmlCString::of(higlight.toUtf8()));
    xmlDocPtr expectedDoc =
            xmlParseDocEx(XmlCString::of(xmlDocHighlight2.toUtf8()));
    QVERIFY(xmlSimpleNodesEq(xmlDocGetRootElement(highlightDoc),
                             xmlDocGetRootElement(expectedDoc)));
    xmlFreeDoc(highlightDoc);
    xmlFreeDoc(expectedDoc);
}
