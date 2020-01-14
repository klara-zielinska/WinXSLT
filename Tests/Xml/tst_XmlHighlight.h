#pragma once

#include "Xml/XmlHighlight.h"
#include <QTest>

class tst_XmlHighlight : public QObject
{
    Q_OBJECT

    QString xmlDoc1, xmlDoc2;
    QString xmlDocHighlight1, xmlDocHighlight2;

public:
    tst_XmlHighlight();
    ~tst_XmlHighlight();

private slots:
    void initTestCase();
    void cleanupTestCase();

    void testInHtml1();
    void testInHtml2();
};
