#include "tst_testtools.h"
#include "testtools.h"
#include <QBuffer>


tst_testtools::tst_testtools()
{ }

tst_testtools::~tst_testtools()
{ }

void tst_testtools::initTestCase()
{
    QDir dir = QDir::current();
    dir.mkdir("EmptyDir");

    dir = QDir::current();
    dir.mkdir("NoXmlDir");
}

void tst_testtools::cleanupTestCase()
{
    QDir("EmptyDir").removeRecursively();
    QDir("NoXmlDir").removeRecursively();
}

//void tst_testtools::testUntar1()
//{
//    QDir dir("EmptyDir");
//    QString s = dir.absolutePath();
//    auto* source = QTemporaryFile::createNativeFile(":/EmptyDir.tar");
//    try { untar(*source, dir); }
//    catch (const std::runtime_error& e) { QFAIL(e.what()); }

//    QVERIFY(dir.entryList(QDir::AllEntries | QDir::NoDotAndDotDot).size() == 0);

//    delete source;
//}

//void tst_testtools::testUntar2()
//{
//    QDir dir("NoXmlDir");
//    auto* source = QTemporaryFile::createNativeFile(":/NoXmlDir.tar");
//    try { untar(*source, dir); }
//    catch (const std::runtime_error &e) { QFAIL(e.what()); }

//    auto dirEntries = [&dir](){
//        return dir.entryList(QDir::AllEntries | QDir::NoDotAndDotDot, QDir::Name);
//    };
//    QVERIFY(dirEntries() == QStringList({"ABC", "D E F", "bar", "foo"}));
//    dir.cd("ABC");
//    QVERIFY(dirEntries() == QStringList({"a.txt", "b.txt", "c.txt"}));
//    dir.cdUp();
//    dir.cd("D E F");
//    QVERIFY(dirEntries() == QStringList({"_D.txt", "_E F.txt"}));
//    dir.cd("../bar");
//    QVERIFY(dirEntries() == QStringList({"1.txt", "2.txt", "barfoo", "foobar"}));
//    dir.cd("foobar");
//    QByteArray buf =
//        "XR0UHmUuzI4YXTA8v0WI\r\n"
//        "FcAPCKk3I4Hx5vBjEKn3\r\n"
//        "Kdnrry5gyEGotpeKprrj\r\n"
//        "BNm4kTWCfqwdwpXGenxg\r\n"
//        "yjDuTs2t1YcXiZ64C0iX\r\n"
//        "3eE0OnCUgVD8CR19DWu3\r\n"
//        "y7IxC6gBVhnJhggE23Fu\r\n"
//        "KBOrZn9cvVjCEVf0RQzV\r\n"
//        "05JGb4BthZi9IemaNJ08\r\n"
//        "hToh4yx3FkRdd6EUJ8bP";
//    QBuffer content(&buf);
//    QFile file(dir.filePath("foobar.txt"));
//    QVERIFY(qIODevEq(file, content));
//    dir.cd("../../foo");
//    QVERIFY(dirEntries() == QStringList({"foobar", "foofoo"}));

//    delete source;
//}

//void tst_testtools::testCopyToTempFile()
//{
//    QFile f("mmc3a.txt");
//    auto* tf = QTemporaryFile::createNativeFile(f);

//    try { QVERIFY(qIODevEq(f, *tf)); }
//    catch (const std::runtime_error &e) { QFAIL(e.what()); }

//    delete tf;
//}

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

