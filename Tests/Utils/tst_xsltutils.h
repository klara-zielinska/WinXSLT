#pragma once

#include <QTest>

class tst_xsltutils : public QObject
{
    Q_OBJECT

    QDir xmlDir;

public:
    tst_xsltutils();
    ~tst_xsltutils();

private slots:
    void initTestCase();
    void cleanupTestCase();

    void testXmlCStringOf1();
    void testXmlCStringOf2();
    void testXmlCStringOf3();
    void testXmlCStringOf4();

    void testXmlParseDocEx1();
    void testXmlParseDocEx2();
    void testXmlParseFileEx1();
    void testXmlParseFileEx2();
    void testXsltParseStylesheetDocEx();
    void testXsltApplyStylesheetEx();
    void testXsltSaveResultToFileEx();
};
