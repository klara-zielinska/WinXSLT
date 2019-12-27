#include "tst_XmlPatterns.h"

tst_XmlPatterns::tst_XmlPatterns()
{
}

tst_XmlPatterns::~tst_XmlPatterns()
{
}

void tst_XmlPatterns::initTestCase()
{
}

void tst_XmlPatterns::cleanupTestCase()
{
}

void tst_XmlPatterns::testOpenTag1()
{
    const QRegularExpression* regex = XmlPatterns::Patterns[0];
    const QRegularExpressionMatch& match =
            regex->match("<!--e--><t>", 0,
                         QRegularExpression::NormalMatch,
                         QRegularExpression::AnchoredMatchOption);
    QVERIFY(match.captured("comment") == "<!--e-->");
    QVERIFY(match.captured("tagOpen").isNull());
    QVERIFY(match.captured("text").isNull());
}

void tst_XmlPatterns::testOpenTag2()
{
    const QRegularExpression* regex = XmlPatterns::Patterns[0];
    const QRegularExpressionMatch& match =
            regex->match("<tag>", 0,
                         QRegularExpression::NormalMatch,
                         QRegularExpression::AnchoredMatchOption);
    QVERIFY(match.captured("comment").isNull());
    QVERIFY(match.captured("tagOpen") == "<");
    QVERIFY(match.captured("text").isNull());
}

void tst_XmlPatterns::testOpenTag3()
{
    const QRegularExpression* regex = XmlPatterns::Patterns[0];
    const QRegularExpressionMatch& match =
            regex->match("text<tag>", 0,
                         QRegularExpression::NormalMatch,
                         QRegularExpression::AnchoredMatchOption);
    QVERIFY(match.captured("comment").isNull());
    QVERIFY(match.captured("tagOpen").isNull());
    QVERIFY(match.captured("text") == "text");
}

void tst_XmlPatterns::testOpenTag4()
{
    const QRegularExpression* regex = XmlPatterns::Patterns[0];
    const QRegularExpressionMatch& match =
            regex->match("<?xml", 0,
                         QRegularExpression::NormalMatch,
                         QRegularExpression::AnchoredMatchOption);
    QVERIFY(match.captured("comment").isNull());
    QVERIFY(match.captured("tagOpen") == "<?");
    QVERIFY(match.captured("text").isNull());
}

void tst_XmlPatterns::testOpenTag5()
{
    const QRegularExpression* regex = XmlPatterns::Patterns[0];
    const QRegularExpressionMatch& match =
            regex->match("<!ENTITY", 0,
                         QRegularExpression::NormalMatch,
                         QRegularExpression::AnchoredMatchOption);
    QVERIFY(match.captured("comment").isNull());
    QVERIFY(match.captured("tagOpen") == "<!");
    QVERIFY(match.captured("text").isNull());
}

void tst_XmlPatterns::testInTag1()
{
    const QRegularExpression* regex = XmlPatterns::Patterns[1];
    const QRegularExpressionMatch& match =
            regex->match("tag x='4'>", 0,
                         QRegularExpression::NormalMatch,
                         QRegularExpression::AnchoredMatchOption);
    QVERIFY(match.captured("tagName") == "tag");
    QVERIFY(match.captured("invTag").isNull());
}

void tst_XmlPatterns::testInTag2()
{
    const QRegularExpression* regex = XmlPatterns::Patterns[1];
    const QRegularExpressionMatch& match =
            regex->match(" tag x='4'>abc", 0,
                         QRegularExpression::NormalMatch,
                         QRegularExpression::AnchoredMatchOption);
    QVERIFY(match.captured("tagName").isNull());
    QVERIFY(match.captured("invTag") == " tag x='4'>");
}

void tst_XmlPatterns::testInTag3()
{
    const QRegularExpression* regex = XmlPatterns::Patterns[1];
    const QRegularExpressionMatch& match =
            regex->match("<>abc", 0,
                         QRegularExpression::NormalMatch,
                         QRegularExpression::AnchoredMatchOption);
    QVERIFY(match.captured("tagName").isNull());
    QVERIFY(match.captured("invTag") == "<>");
}

void tst_XmlPatterns::testInTag4()
{
    const QRegularExpression* regex = XmlPatterns::Patterns[1];
    const QRegularExpressionMatch& match =
            regex->match(u8"świerszcz>", 0,
                         QRegularExpression::NormalMatch,
                         QRegularExpression::AnchoredMatchOption);
    QVERIFY(match.captured("tagName") == QString::fromUtf8(u8"świerszcz"));
    QVERIFY(match.captured("invTag").isNull());
}

void tst_XmlPatterns::testInAttrs1()
{
    const QRegularExpression* regex = XmlPatterns::Patterns[2];
    const QRegularExpressionMatch& match =
            regex->match("  x='4'>", 0,
                         QRegularExpression::NormalMatch,
                         QRegularExpression::AnchoredMatchOption);
    QVERIFY(match.captured("s") == "  ");
    QVERIFY(match.captured("attrName").isNull());
    QVERIFY(match.captured("tagClose").isNull());
    QVERIFY(match.captured("invTag").isNull());
}

void tst_XmlPatterns::testInAttrs2()
{
    const QRegularExpression* regex = XmlPatterns::Patterns[2];
    const QRegularExpressionMatch& match =
            regex->match("x='4'>", 0,
                         QRegularExpression::NormalMatch,
                         QRegularExpression::AnchoredMatchOption);
    QVERIFY(match.captured("s").isNull());
    QVERIFY(match.captured("attrName") == "x");
    QVERIFY(match.captured("tagClose").isNull());
    QVERIFY(match.captured("invTag").isNull());
}

void tst_XmlPatterns::testInAttrs3()
{
    const QRegularExpression* regex = XmlPatterns::Patterns[2];
    const QRegularExpressionMatch& match =
            regex->match("> anr", 0,
                         QRegularExpression::NormalMatch,
                         QRegularExpression::AnchoredMatchOption);
    QVERIFY(match.captured("s").isNull());
    QVERIFY(match.captured("attrName").isNull());
    QVERIFY(match.captured("tagClose") == ">");
    QVERIFY(match.captured("invTag").isNull());
}

void tst_XmlPatterns::testInAttrs4()
{
    const QRegularExpression* regex = XmlPatterns::Patterns[2];
    const QRegularExpressionMatch& match =
            regex->match("/> anr", 0,
                         QRegularExpression::NormalMatch,
                         QRegularExpression::AnchoredMatchOption);
    QVERIFY(match.captured("s").isNull());
    QVERIFY(match.captured("attrName").isNull());
    QVERIFY(match.captured("tagClose") == "/>");
    QVERIFY(match.captured("invTag").isNull());
}

void tst_XmlPatterns::testInAttrs5()
{
    const QRegularExpression* regex = XmlPatterns::Patterns[2];
    const QRegularExpressionMatch& match =
            regex->match("='4'> anr", 0,
                         QRegularExpression::NormalMatch,
                         QRegularExpression::AnchoredMatchOption);
    QVERIFY(match.captured("s").isNull());
    QVERIFY(match.captured("attrName").isNull());
    QVERIFY(match.captured("tagClose").isNull());
    QVERIFY(match.captured("invTag") == "='4'>");
}

void tst_XmlPatterns::testInAttrs6()
{
    const QRegularExpression* regex = XmlPatterns::Patterns[2];
    const QRegularExpressionMatch& match =
            regex->match(QString::fromUtf8(u8"łączność='3'"), 0,
                         QRegularExpression::NormalMatch,
                         QRegularExpression::AnchoredMatchOption);
    QVERIFY(match.captured("s").isNull());
    QVERIFY(match.captured("attrName") == "łączność");
    QVERIFY(match.captured("tagClose").isNull());
    QVERIFY(match.captured("invTag").isNull());
}

void tst_XmlPatterns::testInAttr1()
{
    const QRegularExpression* regex = XmlPatterns::Patterns[3];
    const QRegularExpressionMatch& match =
            regex->match("    = 'abc'", 0,
                         QRegularExpression::NormalMatch,
                         QRegularExpression::AnchoredMatchOption);
    QVERIFY(match.captured("s") == "    ");
    QVERIFY(match.captured("eq").isNull());
    QVERIFY(match.captured("tagClose").isNull());
    QVERIFY(match.captured("invTag").isNull());
}

void tst_XmlPatterns::testInAttr2()
{
    const QRegularExpression* regex = XmlPatterns::Patterns[3];
    const QRegularExpressionMatch& match =
            regex->match("= 'abc'", 0,
                         QRegularExpression::NormalMatch,
                         QRegularExpression::AnchoredMatchOption);
    QVERIFY(match.captured("s").isNull());
    QVERIFY(match.captured("eq") == "=");
    QVERIFY(match.captured("tagClose").isNull());
    QVERIFY(match.captured("invTag").isNull());
}

void tst_XmlPatterns::testInAttr3()
{
    const QRegularExpression* regex = XmlPatterns::Patterns[3];
    const QRegularExpressionMatch& match =
            regex->match(">lo", 0,
                         QRegularExpression::NormalMatch,
                         QRegularExpression::AnchoredMatchOption);
    QVERIFY(match.captured("s").isNull());
    QVERIFY(match.captured("eq").isNull());
    QVERIFY(match.captured("tagClose") == ">");
    QVERIFY(match.captured("invTag").isNull());
}

void tst_XmlPatterns::testInAttr4()
{
    const QRegularExpression* regex = XmlPatterns::Patterns[3];
    const QRegularExpressionMatch& match =
            regex->match("/>lo", 0,
                         QRegularExpression::NormalMatch,
                         QRegularExpression::AnchoredMatchOption);
    QVERIFY(match.captured("s").isNull());
    QVERIFY(match.captured("eq").isNull());
    QVERIFY(match.captured("tagClose") == "/>");
    QVERIFY(match.captured("invTag").isNull());
}

void tst_XmlPatterns::testInAttr5()
{
    const QRegularExpression* regex = XmlPatterns::Patterns[3];
    const QRegularExpressionMatch& match =
            regex->match("kiwi >", 0,
                         QRegularExpression::NormalMatch,
                         QRegularExpression::AnchoredMatchOption);
    QVERIFY(match.captured("s").isNull());
    QVERIFY(match.captured("eq").isNull());
    QVERIFY(match.captured("tagClose").isNull());
    QVERIFY(match.captured("invTag") == "kiwi >");
}

void tst_XmlPatterns::testInAttr6()
{
    const QRegularExpression* regex = XmlPatterns::Patterns[3];
    const QRegularExpressionMatch& match =
            regex->match("== >", 0,
                         QRegularExpression::NormalMatch,
                         QRegularExpression::AnchoredMatchOption);
    QVERIFY(match.captured("s").isNull());
    QVERIFY(match.captured("eq") == "=");
    QVERIFY(match.captured("tagClose").isNull());
    QVERIFY(match.captured("invTag").isNull());
}

void tst_XmlPatterns::testInVal1()
{
    const QRegularExpression* regex = XmlPatterns::Patterns[4];
    const QRegularExpressionMatch& match =
            regex->match("  'abc' >", 0,
                         QRegularExpression::NormalMatch,
                         QRegularExpression::AnchoredMatchOption);
    QVERIFY(match.captured("s") == "  ");
    QVERIFY(match.captured("value").isNull());
    QVERIFY(match.captured("invTag").isNull());
}

void tst_XmlPatterns::testInVal2()
{
    const QRegularExpression* regex = XmlPatterns::Patterns[4];
    const QRegularExpressionMatch& match =
            regex->match("'abc' >", 0,
                         QRegularExpression::NormalMatch,
                         QRegularExpression::AnchoredMatchOption);
    QVERIFY(match.captured("s").isNull());
    QVERIFY(match.captured("value") == "'abc'");
    QVERIFY(match.captured("invTag").isNull());
}

void tst_XmlPatterns::testInVal3()
{
    const QRegularExpression* regex = XmlPatterns::Patterns[4];
    const QRegularExpressionMatch& match =
            regex->match("\"abc\" >", 0,
                         QRegularExpression::NormalMatch,
                         QRegularExpression::AnchoredMatchOption);
    QVERIFY(match.captured("s").isNull());
    QVERIFY(match.captured("value") == "\"abc\"");
    QVERIFY(match.captured("invTag").isNull());
}

void tst_XmlPatterns::testInVal4()
{
    const QRegularExpression* regex = XmlPatterns::Patterns[4];
    const QRegularExpressionMatch& match =
            regex->match("abc' >lo", 0,
                         QRegularExpression::NormalMatch,
                         QRegularExpression::AnchoredMatchOption);
    QVERIFY(match.captured("s").isNull());
    QVERIFY(match.captured("value").isNull());
    QVERIFY(match.captured("invTag") == "abc' >");
}

void tst_XmlPatterns::testInVal5()
{
    const QRegularExpression* regex = XmlPatterns::Patterns[4];
    const QRegularExpressionMatch& match =
            regex->match("\"&quot;abc&quot;\" >lo", 0,
                         QRegularExpression::NormalMatch,
                         QRegularExpression::AnchoredMatchOption);
    QVERIFY(match.captured("s").isNull());
    QVERIFY(match.captured("value") == "\"&quot;abc&quot;\"");
    QVERIFY(match.captured("invTag").isNull());
}

void tst_XmlPatterns::testInVal6()
{
    const QRegularExpression* regex = XmlPatterns::Patterns[4];
    const QRegularExpressionMatch& match =
            regex->match("'abc&#xA;&#xd;' >lo", 0,
                         QRegularExpression::NormalMatch,
                         QRegularExpression::AnchoredMatchOption);
    QVERIFY(match.captured("s").isNull());
    QVERIFY(match.captured("value") == "'abc&#xA;&#xd;'");
    QVERIFY(match.captured("invTag").isNull());
}
