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
    QFile f1(":/resources/XmlDir/cds/book.xml");
    f1.open(QFile::ReadOnly);
    xmlReader1 = new XmlReader(QString::fromUtf8(f1.readAll()));
    f1.close();

    QFile f2(":/resources/XmlDir/dir/book_bad.xml");
    f2.open(QFile::ReadOnly);
    xmlReader2 = new XmlReader(QString::fromUtf8(f2.readAll()));
    f2.close();
}

void tst_XmlReader::cleanupTestCase()
{
    delete xmlReader1;
    delete xmlReader2;
}

void tst_XmlReader::testNextToken1()
{
    QVERIFY(xmlReader1->NextToken() ==
            (XmlToken{ .type = XmlToken::TagOpen, .text = "<?" }));
    QVERIFY(xmlReader1->NextToken() ==
            (XmlToken{ .type = XmlToken::TagName, .text = "xml" }));
    QVERIFY(xmlReader1->NextToken() ==
            (XmlToken{ .type = XmlToken::InS, .text = " " }));
    QVERIFY(xmlReader1->NextToken() ==
            (XmlToken{ .type = XmlToken::AttrName, .text = "version" }));
    QVERIFY(xmlReader1->NextToken() ==
            (XmlToken{ .type = XmlToken::AttrEq, .text = "=" }));
    QVERIFY(xmlReader1->NextToken() ==
            (XmlToken{ .type = XmlToken::AttrValue, .text = "\"1.0\"" }));
    QVERIFY(xmlReader1->NextToken() ==
            (XmlToken{ .type = XmlToken::InS, .text = " " }));
    QVERIFY(xmlReader1->NextToken() ==
            (XmlToken{ .type = XmlToken::AttrName, .text = "encoding" }));
    QVERIFY(xmlReader1->NextToken() ==
            (XmlToken{ .type = XmlToken::AttrEq, .text = "=" }));
    QVERIFY(xmlReader1->NextToken() ==
            (XmlToken{ .type = XmlToken::AttrValue, .text = "\"UTF-8\"" }));
    QVERIFY(xmlReader1->NextToken() ==
            (XmlToken{ .type = XmlToken::TagClose, .text = "?>" }));
    QVERIFY(xmlReader1->NextToken() ==
            (XmlToken{ .type = XmlToken::Text, .text = "\r\n" }));
    QVERIFY(xmlReader1->NextToken() ==
            (XmlToken{ .type = XmlToken::TagOpen, .text = "<" }));
    QVERIFY(xmlReader1->NextToken() ==
            (XmlToken{ .type = XmlToken::TagName, .text = "book" }));
    QVERIFY(xmlReader1->NextToken() ==
            (XmlToken{ .type = XmlToken::TagClose, .text = ">" }));
    QVERIFY(xmlReader1->NextToken() ==
            (XmlToken{ .type = XmlToken::Text, .text = "\r\n\t" }));
    QVERIFY(xmlReader1->NextToken() ==
            (XmlToken{ .type = XmlToken::TagOpen, .text = "<" }));
    for (int i = 0; i < 19; ++i)
        xmlReader1->NextToken();
    QVERIFY(xmlReader1->NextToken() ==
            (XmlToken { .type = XmlToken::TagOpen, .text = "</"}));
    QVERIFY(xmlReader1->NextToken() ==
            (XmlToken { .type = XmlToken::TagName, .text = "book"}));
    QVERIFY(xmlReader1->NextToken() ==
            (XmlToken { .type = XmlToken::TagClose, .text = ">"}));
    QVERIFY(xmlReader1->NextToken().type == XmlToken::End);
}

void tst_XmlReader::testNextToken2()
{
    QVERIFY(xmlReader2->NextToken() ==
            (XmlToken{ .type = XmlToken::TagOpen, .text = "<?" }));
    QVERIFY(xmlReader2->NextToken() ==
            (XmlToken{ .type = XmlToken::TagName, .text = "xml" }));
    QVERIFY(xmlReader2->NextToken() ==
            (XmlToken{ .type = XmlToken::InS, .text = " " }));
    QVERIFY(xmlReader2->NextToken() ==
            (XmlToken{ .type = XmlToken::AttrName, .text = "version" }));
    for (int i = 0; i < 13; ++i)
        xmlReader2->NextToken();
    QVERIFY(xmlReader2->NextToken() ==
            (XmlToken{ .type = XmlToken::TagName, .text = "title" }));
    QVERIFY(xmlReader2->NextToken() ==
            (XmlToken{ .type = XmlToken::InS, .text = " " }));
    QVERIFY(xmlReader2->NextToken() ==
            (XmlToken{ .type = XmlToken::AttrName, .text = "language" }));
    QVERIFY(xmlReader2->NextToken() ==
            (XmlToken{ .type = XmlToken::AttrEq, .text = "=" }));
    QVERIFY(xmlReader2->NextToken() ==
            (XmlToken{ .type = XmlToken::InvTagEnding, .text = ">" }));
    QVERIFY(xmlReader2->NextToken() ==
            (XmlToken{ .type = XmlToken::Text, .text = "Odyssey" }));
    for (int i = 0; i < 7; ++i)
        xmlReader2->NextToken();
    QVERIFY(xmlReader2->NextToken() ==
            (XmlToken { .type = XmlToken::Text, .text = "Homer"}));
    QVERIFY(xmlReader2->NextToken() ==
            (XmlToken { .type = XmlToken::TagOpen, .text = "</"}));
    QVERIFY(xmlReader2->NextToken() ==
            (XmlToken { .type = XmlToken::TagName, .text = "author"}));
    QVERIFY(xmlReader2->NextToken() ==
            (XmlToken { .type = XmlToken::InS, .text = "\r\n"}));
    QVERIFY(xmlReader2->NextToken() ==
            (XmlToken { .type = XmlToken::InvTagEnding, .text = "</book>"}));
    QVERIFY(xmlReader2->NextToken().type == XmlToken::End);
}
