#include "tst_XmlReader.h"


bool operator== (const XmlToken&& t1, const XmlToken&& t2)
{
    return  t1.type == t2.type && t1.text == t2.text;
}


tst_XmlReader::tst_XmlReader()
{
}

tst_XmlReader::~tst_XmlReader()
{
}

void tst_XmlReader::initTestCase()
{
    QFile f(":/resources/XmlDir/cds/book.xml");
    f.open(QFile::ReadOnly);
    xmlReader = new XmlReader(QString::fromUtf8(f.readAll()));
    f.close();
}

void tst_XmlReader::cleanupTestCase()
{
    delete xmlReader;
}

void tst_XmlReader::testNextToken1()
{
    QVERIFY(xmlReader->NextToken() ==
            (XmlToken{ .type = XmlToken::TagOpen, .text = "<?" }));
    QVERIFY(xmlReader->NextToken() ==
            (XmlToken{ .type = XmlToken::TagName, .text = "xml" }));
    QVERIFY(xmlReader->NextToken() ==
            (XmlToken{ .type = XmlToken::InS, .text = " " }));
    QVERIFY(xmlReader->NextToken() ==
            (XmlToken{ .type = XmlToken::AttrName, .text = "version" }));
    QVERIFY(xmlReader->NextToken() ==
            (XmlToken{ .type = XmlToken::AttrEq, .text = "=" }));
    QVERIFY(xmlReader->NextToken() ==
            (XmlToken{ .type = XmlToken::AttrValue, .text = "\"1.0\"" }));
    QVERIFY(xmlReader->NextToken() ==
            (XmlToken{ .type = XmlToken::InS, .text = " " }));
    QVERIFY(xmlReader->NextToken() ==
            (XmlToken{ .type = XmlToken::AttrName, .text = "encoding" }));
    QVERIFY(xmlReader->NextToken() ==
            (XmlToken{ .type = XmlToken::AttrEq, .text = "=" }));
    QVERIFY(xmlReader->NextToken() ==
            (XmlToken{ .type = XmlToken::AttrValue, .text = "\"UTF-8\"" }));
    QVERIFY(xmlReader->NextToken() ==
            (XmlToken{ .type = XmlToken::TagClose, .text = "?>" }));
    QVERIFY(xmlReader->NextToken() ==
            (XmlToken{ .type = XmlToken::Text, .text = "\r\n" }));
    QVERIFY(xmlReader->NextToken() ==
            (XmlToken{ .type = XmlToken::TagOpen, .text = "<" }));
    QVERIFY(xmlReader->NextToken() ==
            (XmlToken{ .type = XmlToken::TagName, .text = "book" }));
    QVERIFY(xmlReader->NextToken() ==
            (XmlToken{ .type = XmlToken::TagClose, .text = ">" }));
    QVERIFY(xmlReader->NextToken() ==
            (XmlToken{ .type = XmlToken::Text, .text = "\r\n\t" }));
    QVERIFY(xmlReader->NextToken() ==
            (XmlToken{ .type = XmlToken::TagOpen, .text = "<" }));
    xmlReader->NextToken();
    xmlReader->NextToken();
    xmlReader->NextToken();
    xmlReader->NextToken();
    xmlReader->NextToken();
    xmlReader->NextToken();
    xmlReader->NextToken();
    xmlReader->NextToken();
    xmlReader->NextToken();
    xmlReader->NextToken();
    xmlReader->NextToken();
    xmlReader->NextToken();
    xmlReader->NextToken();
    xmlReader->NextToken();
    xmlReader->NextToken();
    xmlReader->NextToken();
    xmlReader->NextToken();
    xmlReader->NextToken();
    xmlReader->NextToken();
    QVERIFY(xmlReader->NextToken() ==
            (XmlToken { .type = XmlToken::TagOpen, .text = "</"}));
    QVERIFY(xmlReader->NextToken() ==
            (XmlToken { .type = XmlToken::TagName, .text = "book"}));
    QVERIFY(xmlReader->NextToken() ==
            (XmlToken { .type = XmlToken::TagClose, .text = ">"}));
    QVERIFY(xmlReader->NextToken().type == XmlToken::End);
}
