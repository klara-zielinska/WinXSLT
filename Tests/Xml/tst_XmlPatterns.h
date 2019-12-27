#pragma once

#include "Xml/XmlPatterns.h"
#include <QTest>

class tst_XmlPatterns : public QObject
{
    Q_OBJECT

public:
    tst_XmlPatterns();
    ~tst_XmlPatterns();

private slots:
    void initTestCase();
    void cleanupTestCase();

    void testOpenTag1();
    void testOpenTag2();
    void testOpenTag3();
    void testOpenTag4();
    void testOpenTag5();

    void testInTag1();
    void testInTag2();
    void testInTag3();
    void testInTag4();

    void testInAttrs1();
    void testInAttrs2();
    void testInAttrs3();
    void testInAttrs4();
    void testInAttrs5();
    void testInAttrs6();

    void testInAttr1();
    void testInAttr2();
    void testInAttr3();
    void testInAttr4();
    void testInAttr5();
    void testInAttr6();

    void testInVal1();
    void testInVal2();
    void testInVal3();
    void testInVal4();
    void testInVal5();
    void testInVal6();
};
