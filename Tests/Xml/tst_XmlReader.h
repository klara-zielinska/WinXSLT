#pragma once

#include "Xml/XmlReader.h"
#include <QTest>

class tst_XmlReader : public QObject
{
    Q_OBJECT

    XmlReader* xmlReader1;
    XmlReader* xmlReader2;

public:
    tst_XmlReader();
    ~tst_XmlReader();

private slots:
    void initTestCase();
    void cleanupTestCase();

    void testNextToken1();
    void testNextToken2();
};
