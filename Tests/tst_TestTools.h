#pragma once

#include <libxml2/libxml/tree.h>
#include <QTest>

class tst_testtools : public QObject
{
    Q_OBJECT

    xmlDocPtr xmlDoc1a, xmlDoc1b, xmlDoc1c,
              xmlDoc2a, xmlDoc2b, xmlDoc2c, xmlDoc2d, xmlDoc2e, xmlDoc2f,
              xmlDoc3a, xmlDoc3b, xmlDoc3c, xmlDoc3d, xmlDoc3e;

public:
    tst_testtools();
    ~tst_testtools();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testQIODevEq1();
    void testQIODevEq2();
    void testXmlSimpleNodesEq1();
    void testXmlSimpleNodesEq2();
    void testXmlSimpleNodesEq3();
};
