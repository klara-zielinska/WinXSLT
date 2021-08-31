#pragma once

#include <QTest>

class tst_tools : public QObject
{
    Q_OBJECT

    QDir resourcesDir;

public:
    tst_tools();
    ~tst_tools();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testSize1();
    void testSize2();
    void testGetFilesByPattern1();
    void testGetFilesByPattern2();
};
