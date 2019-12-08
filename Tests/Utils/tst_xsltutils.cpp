#include "tst_xsltutils.h"
#include "testtools.h"
#include "Utils/xsltutils.h"
#include <QTemporaryFile>

tst_xsltutils::tst_xsltutils()
{
}

tst_xsltutils::~tst_xsltutils()
{
}

void tst_xsltutils::initTestCase()
{
    xmlSubstituteEntitiesDefault(1);
    xmlLoadExtDtdDefaultValue = 1;

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
    xmlParseFileEx(QDir::current().filePath(
                       QString::fromWCharArray(L"XmlDir/goodł.xml")).toUtf8());
}

void tst_xsltutils::testXmlParseFileEx2()
{
}

void tst_xsltutils::testXsltParseStylesheetDocEx()
{
    throw 1;
}

void tst_xsltutils::testXsltApplyStylesheetEx()
{
    throw 1;
}

void tst_xsltutils::testXsltSaveResultToFileEx()
{
    throw 1;
}
