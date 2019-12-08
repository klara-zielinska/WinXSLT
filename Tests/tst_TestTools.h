#pragma once

#include <QTest>

class tst_testtools : public QObject
{
    Q_OBJECT

public:
    tst_testtools();
    ~tst_testtools();

private slots:
    void initTestCase();
    void cleanupTestCase();
//    void testUntar1();
//    void testUntar2();
//    void testCopyToTempFile();
    void testQIODevEq1();
    void testQIODevEq2();
};
