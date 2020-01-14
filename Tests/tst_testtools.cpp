#include "tst_testtools.h"
#include "testtools.h"
#include "Utils/xsltutils.h"
#include <QBuffer>


tst_testtools::tst_testtools()
{ }

tst_testtools::~tst_testtools()
{ }

void tst_testtools::initTestCase()
{
    xmlSubstituteEntitiesDefault(1);
    xmlLoadExtDtdDefaultValue = 1;

    QFile f1(":/resources/XmlDir/cmp/ex1a.xml");
    f1.open(QFile::ReadOnly);
    xmlDoc1a = xmlParseDocEx(XmlCString::of(f1.readAll()));
    f1.close();

    QFile f2(":/resources/XmlDir/cmp/ex1b.xml");
    f2.open(QFile::ReadOnly);
    xmlDoc1b = xmlParseDocEx(XmlCString::of(f2.readAll()));
    f2.close();

    QFile f3(":/resources/XmlDir/cmp/ex1c.xml");
    f3.open(QFile::ReadOnly);
    xmlDoc1c = xmlParseDocEx(XmlCString::of(f3.readAll()));
    f3.close();

    QFile f4(":/resources/XmlDir/cmp/ex2a.xml");
    f4.open(QFile::ReadOnly);
    xmlDoc2a = xmlParseDocEx(XmlCString::of(f4.readAll()));
    f4.close();

    QFile f5(":/resources/XmlDir/cmp/ex2b.xml");
    f5.open(QFile::ReadOnly);
    xmlDoc2b = xmlParseDocEx(XmlCString::of(f5.readAll()));
    f5.close();

    QFile f6(":/resources/XmlDir/cmp/ex2c.xml");
    f6.open(QFile::ReadOnly);
    xmlDoc2c = xmlParseDocEx(XmlCString::of(f6.readAll()));
    f6.close();

    QFile f7(":/resources/XmlDir/cmp/ex2d.xml");
    f7.open(QFile::ReadOnly);
    xmlDoc2d = xmlParseDocEx(XmlCString::of(f7.readAll()));
    f7.close();

    QFile f8(":/resources/XmlDir/cmp/ex2e.xml");
    f8.open(QFile::ReadOnly);
    xmlDoc2e = xmlParseDocEx(XmlCString::of(f8.readAll()));
    f8.close();

    QFile f9(":/resources/XmlDir/cmp/ex2f.xml");
    f9.open(QFile::ReadOnly);
    xmlDoc2f = xmlParseDocEx(XmlCString::of(f9.readAll()));
    f9.close();

    QFile f10(":/resources/XmlDir/cmp/ex3a.xml");
    f10.open(QFile::ReadOnly);
    xmlDoc3a = xmlParseDocEx(XmlCString::of(f10.readAll()));
    f10.close();

    QFile f11(":/resources/XmlDir/cmp/ex3b.xml");
    f11.open(QFile::ReadOnly);
    xmlDoc3b = xmlParseDocEx(XmlCString::of(f11.readAll()));
    f11.close();

    QFile f12(":/resources/XmlDir/cmp/ex3c.xml");
    f12.open(QFile::ReadOnly);
    xmlDoc3c = xmlParseDocEx(XmlCString::of(f12.readAll()));
    f12.close();

    QFile f13(":/resources/XmlDir/cmp/ex3d.xml");
    f13.open(QFile::ReadOnly);
    xmlDoc3d = xmlParseDocEx(XmlCString::of(f13.readAll()));
    f13.close();

    QFile f14(":/resources/XmlDir/cmp/ex3e.xml");
    f14.open(QFile::ReadOnly);
    xmlDoc3e = xmlParseDocEx(XmlCString::of(f14.readAll()));
    f14.close();
}

void tst_testtools::cleanupTestCase()
{
    xmlFreeDoc(xmlDoc1a);
    xmlFreeDoc(xmlDoc1b);
    xmlFreeDoc(xmlDoc1c);

    xmlFreeDoc(xmlDoc2a);
    xmlFreeDoc(xmlDoc2b);
    xmlFreeDoc(xmlDoc2c);
    xmlFreeDoc(xmlDoc2d);
    xmlFreeDoc(xmlDoc2e);
    xmlFreeDoc(xmlDoc2f);
}

void tst_testtools::testQIODevEq1()
{
    QFile f1(":/resources/mmc3a.txt");
    QFile f2(":/resources/mmc3a.txt");
    try { QVERIFY(qIODevEq(f1, f2)); }
    catch (const std::runtime_error& e) { QFAIL(e.what()); }
}

void tst_testtools::testQIODevEq2()
{
    QFile f1(":/resources/mmc3a.txt");
    QFile f2(":/resources/mmc3b.txt");
    QVERIFY(!qIODevEq(f1, f2));
}

void tst_testtools::testXmlSimpleNodesEq1()
{
    QVERIFY(xmlSimpleNodesEq(xmlDocGetRootElement(xmlDoc1a),
                             xmlDocGetRootElement(xmlDoc1b)));
    QVERIFY(!xmlSimpleNodesEq(xmlDocGetRootElement(xmlDoc1a),
                             xmlDocGetRootElement(xmlDoc1c)));
}

void tst_testtools::testXmlSimpleNodesEq2()
{
    QVERIFY(xmlSimpleNodesEq(xmlDocGetRootElement(xmlDoc2a),
                             xmlDocGetRootElement(xmlDoc2b)));
    QVERIFY(!xmlSimpleNodesEq(xmlDocGetRootElement(xmlDoc2a),
                             xmlDocGetRootElement(xmlDoc2c)));
    QVERIFY(!xmlSimpleNodesEq(xmlDocGetRootElement(xmlDoc2a),
                             xmlDocGetRootElement(xmlDoc2d)));
    QVERIFY(!xmlSimpleNodesEq(xmlDocGetRootElement(xmlDoc2a),
                             xmlDocGetRootElement(xmlDoc2e)));
    QVERIFY(!xmlSimpleNodesEq(xmlDocGetRootElement(xmlDoc2a),
                             xmlDocGetRootElement(xmlDoc2f)));
}

void tst_testtools::testXmlSimpleNodesEq3()
{
    QVERIFY(xmlSimpleNodesEq(xmlDocGetRootElement(xmlDoc3a),
                             xmlDocGetRootElement(xmlDoc3b)));
    QVERIFY(!xmlSimpleNodesEq(xmlDocGetRootElement(xmlDoc3a),
                             xmlDocGetRootElement(xmlDoc3c)));
    QVERIFY(!xmlSimpleNodesEq(xmlDocGetRootElement(xmlDoc3a),
                             xmlDocGetRootElement(xmlDoc3d)));
    QVERIFY(!xmlSimpleNodesEq(xmlDocGetRootElement(xmlDoc3a),
                             xmlDocGetRootElement(xmlDoc3e)));
}
