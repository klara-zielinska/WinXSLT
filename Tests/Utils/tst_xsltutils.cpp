#include "tst_xsltutils.h"
#include "testtools.h"
#include "Utils/xsltutils.h"
#include <QTemporaryFile>
#include <iterator>
#include <algorithm>

tst_xsltutils::tst_xsltutils()
{
}

tst_xsltutils::~tst_xsltutils()
{
}

void tst_xsltutils::initTestCase()
{
    xmlDir = QDir("XmlDir");
    copyDir(QDir(":/resources/XmlDir"), xmlDir);
}

void tst_xsltutils::cleanupTestCase()
{
    xmlDir.removeRecursively();
}

void tst_xsltutils::testXmlCStringOf1()
{
    char str[] = "abc";
    char* str_ptr = str;
    XmlCString& xstr = XmlCString::of(str_ptr);
    QVERIFY(reinterpret_cast<char*&>(xstr) == str);
}

void tst_xsltutils::testXmlCStringOf2()
{
    char str[] = "abc";
    QVERIFY(XmlCString::of((char*)str) == str);
}

void tst_xsltutils::testXmlCStringOf3()
{
    const char* str = "abc";
    const XmlCString& xstr = XmlCString::of(str);
    QVERIFY(reinterpret_cast<const char *const &>(xstr) == str);
}

void tst_xsltutils::testXmlCStringOf4()
{
    const char str[] = "abc";
    QVERIFY(XmlCString::of(str) == str);
}

void tst_xsltutils::testXmlParseDocEx1()
{
    const char* xml = 1 + R"TXT(
<?xml version="1.0" encoding="UTF-8"?>
<catalog>
  <cd>
    <title>Empire Burlesque</title>
    <artist>Bob Dylan</artist>
    <country>USA</country>
    <company>Columbia</company>
    <price>10.90</price>
    <year>1985</year>
  </cd>
  <cd>
    <title>Hide your heart</title>
    <artist>Bonnie Tyler</artist>
    <country>UK</country>
    <company>CBS Records</company>
    <price>9.90</price>
    <year>1988</year>
  </cd>
</catalog>)TXT";

    xmlDocPtr xmlDoc = xmlParseDocEx(XmlCString::of(xml));

    QVERIFY(QString(XmlCString::of(xmlDoc->encoding))
            .compare("utf-8", Qt::CaseInsensitive) == 0);

    xmlNode* node = xmlDocGetRootElement(xmlDoc);
    xmlChar* content;
    QVERIFY(QString(XmlCString::of(node->name)) == "catalog");

    node = xmlFirstElementChild(node);
    node = xmlNextElementSibling(node);
    QVERIFY(QString(XmlCString::of(node->name)) == "cd");
    node = xmlFirstElementChild(node);
    QVERIFY(QString(XmlCString::of(node->name)) == "title");
    content = xmlNodeGetContent(node);
    QVERIFY(QString(XmlCString::of(content)) == "Hide your heart");
    node = xmlNextElementSibling(node);
    QVERIFY(QString(XmlCString::of(node->name)) == "artist");

    xmlFreeDoc(xmlDoc);
}

void tst_xsltutils::testXmlParseDocEx2()
{
    const char* xml = 1 + R"TXT(
<?xml version="1.0" encoding="UTF-8"?>
<catalog>
  <cd>
    <title>Empire Burlesque</title>
    <artist>Bob Dylan</artist
    <country>USA</country>
  </cd>
</catalog>)TXT";

    try { xmlParseDocEx(XmlCString::of(xml)); }
    catch (const XmlException&) { return; }
    QFAIL("Exception expected");
}

void tst_xsltutils::testXmlParseFileEx1()
{
    xmlDocPtr xmlDoc = xmlParseFileEx(QDir::current().filePath(
                       QString::fromWCharArray(L"XmlDir/goodł.xml")).toUtf8());

    QVERIFY(QString(XmlCString::of(xmlDoc->encoding))
            .compare("utf-8", Qt::CaseInsensitive) == 0);

    xmlNode* node = xmlDocGetRootElement(xmlDoc);
    xmlChar* content;

    node = xmlFirstElementChild(node);
    node = xmlFirstElementChild(node);
    QVERIFY(QString(XmlCString::of(node->name)) == "title");
    content = xmlNodeGetContent(node);
    QVERIFY(QString::fromUtf8(XmlCString::of(content)) == L"Empireł Burlesquę");
    node = xmlNextElementSibling(node);
    QVERIFY(QString(XmlCString::of(node->name)) == "artist");
    content = xmlNodeGetContent(node);
    QVERIFY(QString::fromUtf8(XmlCString::of(content)) == L"Bób Dylań");
    node = xmlNextElementSibling(node);
    QVERIFY(QString(XmlCString::of(node->name)) == "country");
    content = xmlNodeGetContent(node);
    QVERIFY(QString::fromUtf8(XmlCString::of(content)) == L"UŚĄ");

    xmlFreeDoc(xmlDoc);
}

void tst_xsltutils::testXmlParseFileEx2()
{
    try {
        QString path = QDir::current().filePath("XmlDir/bad.xml");
        xmlDocPtr xmlDoc = xmlParseFileEx(path.toUtf8());
        xmlFreeDoc(xmlDoc);
    }
    catch (const XmlException&) { return; }
    QFAIL("Exception expected");
}

void tst_xsltutils::testXsltParseStylesheetDocEx1()
{
    QString path =
            QDir::current().filePath("XmlDir/cds/cds2html.xslt");
    xmlDocPtr xmlDoc = xmlParseFileEx(path.toUtf8());
    xsltStylesheetPtr xslt = xsltParseStylesheetDocEx(xmlDoc);
    QVERIFY(xslt != nullptr);
    xsltFreeStylesheet(xslt);
}

void tst_xsltutils::testXsltParseStylesheetDocEx2()
{
    QString path =
            QDir::current().filePath("XmlDir/dir/cds2html_bad.xslt");
    xmlDocPtr xmlDoc = xmlParseFileEx(path.toUtf8());
    try {
        xsltStylesheetPtr xslt = xsltParseStylesheetDocEx(xmlDoc);
        xsltFreeStylesheet(xslt);
        QFAIL("Exception expected");
    }
    catch (const XmlException&) { }
}

void tst_xsltutils::testXsltApplyStylesheetEx1()
{
    QString path =
            QDir::current().filePath("XmlDir/cds/cds2html.xslt");
    xsltStylesheetPtr xslt =
            xsltParseStylesheetDocEx(xmlParseFileEx(path.toUtf8()));

    path = QDir::current().filePath("XmlDir/cds/cds.xml");
    xmlDocPtr xmlDoc = xmlParseFile(path.toUtf8());
    xmlDocPtr xmlResDoc = xsltApplyStylesheetEx(xslt, xmlDoc, { nullptr });

    xmlBufferPtr buf1 = xmlBufferCreate();
    xmlNodeDump(buf1, xmlResDoc, xmlDocGetRootElement(xslt->doc), 0, 0);

    path = QDir::current().filePath("XmlDir/cds/cds.html");
    xmlDocPtr xmlCmpDoc = xmlParseFile(path.toUtf8());
    xmlBufferPtr buf2 = xmlBufferCreate();
    xmlNodeDump(buf2, xmlCmpDoc, xmlDocGetRootElement(xslt->doc), 0, 0);

    QVERIFY(buf1->use == buf2->use);
    QVERIFY(std::equal(buf1->content, buf1->content + buf1->use,
                       buf2->content));

    xmlBufferFree(buf1);
    xmlBufferFree(buf2);
    xmlFreeDoc(xmlDoc);
    xmlFreeDoc(xmlResDoc);
    xmlFreeDoc(xmlCmpDoc);
    xsltFreeStylesheet(xslt);
}

void tst_xsltutils::testXsltApplyStylesheetEx2()
{
//    QString path =
//            QDir::current().filePath("XmlDir/cds/cds2html.xslt");
//    xsltStylesheetPtr xslt =
//            xsltParseStylesheetDocEx(xmlParseFileEx(path.toUtf8()));

//    path = QDir::current().filePath("XmlDir/cds/cds3.xml");
//    xmlDocPtr xmlDoc = xmlParseFile(path.toUtf8());
//    try {
//        xmlDocPtr xmlResDoc = xsltApplyStylesheetEx(xslt, xmlDoc, { nullptr });
//        xmlFreeDoc(xmlResDoc);
//        QFAIL("Exception expected");
//    }
//    catch (const XmlException&) { }
//    xmlFreeDoc(xmlDoc);
//    xsltFreeStylesheet(xslt);
}

void tst_xsltutils::testXsltSaveResultToFileEx1()
{
    QString path =
            QDir::current().filePath("XmlDir/cds/cds2html.xslt");
    xsltStylesheetPtr xslt =
            xsltParseStylesheetDocEx(xmlParseFileEx(path.toUtf8()));

    path = QDir::current().filePath("XmlDir/cds/cds.xml");
    xmlDocPtr xmlDoc = xmlParseFile(path.toUtf8());
    xmlDocPtr xmlResDoc = xsltApplyStylesheetEx(xslt, xmlDoc, { nullptr });

    FILE* f = fopen(tmpFileName, "w");
    QVERIFY(xsltSaveResultToFileEx(f, xmlResDoc, xslt) >= 0);
    fclose(f);

    QFile f2(tmpFileName);
    QFile f3("XmlDir/cds/cds.html");
    QVERIFY(qIODevEq(f2, f3));

    f2.remove();
}

void tst_xsltutils::testXsltSaveResultToFileEx2()
{
    QString path =
            QDir::current().filePath("XmlDir/cds/cds2html.xslt");
    xsltStylesheetPtr xslt =
            xsltParseStylesheetDocEx(xmlParseFileEx(path.toUtf8()));

    path = QDir::current().filePath("XmlDir/cds/cds.xml");
    xmlDocPtr xmlDoc = xmlParseFile(path.toUtf8());
    xmlDocPtr xmlResDoc = xsltApplyStylesheetEx(xslt, xmlDoc, { nullptr });

    FILE* f = fopen(tmpFileName, "w");
    fclose(f);
    try {
        xsltSaveResultToFileEx(f, xmlResDoc, xslt);
        QFAIL("Exception expected");
    }
    catch (const XmlException&) { }

    xmlFreeDoc(xmlDoc);
    xmlFreeDoc(xmlResDoc);
    xsltFreeStylesheet(xslt);
}
