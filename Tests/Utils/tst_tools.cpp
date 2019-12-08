#include "Utils/tst_tools.h"
#include "Utils/tools.h"
#include "testtools.h"
#include <limits>


QFileInfoList getFilesByPattern(const QString& path);


tst_tools::tst_tools()
{
}

tst_tools::~tst_tools()
{
}

void tst_tools::initTestCase()
{
    resourcesDir = QDir("resources");
    copyDir(QDir(":/resources"), resourcesDir);
}

void tst_tools::cleanupTestCase()
{
    resourcesDir.removeRecursively();
}

void tst_tools::testSize1()
{
    int a[10];
    QCOMPARE(size(a), 10);
}

void tst_tools::testSize2()
{
    int a[3628];
    QCOMPARE(size(a), 3628);
}

void tst_tools::testGetFilesByPattern1()
{
    QDir dir(resourcesDir.filePath("EmptyDir"));
    QVERIFY(getFilesByPattern(dir.filePath("abc.txt")).size() == 0);
    QVERIFY(getFilesByPattern(dir.filePath("ab*c.txt")).size() == 0);
    QVERIFY(getFilesByPattern(dir.filePath("*/ab*c.txt")).size() == 0);
}

void tst_tools::testGetFilesByPattern2()
{
    QDir dir(resourcesDir.filePath("NoXmlDir"));
    QVERIFY(getFilesByPattern(dir.filePath("abc.txt")).size() == 0);
    QVERIFY(getFilesByPattern(dir.filePath("ABC/a.txt")).size() == 1);
    QVERIFY(getFilesByPattern(dir.filePath("*/foobar/foobar.txt")).size() == 2);
}
