#pragma once

#include <QTest>

class tst_xsltutils : public QObject
{
    Q_OBJECT

    const char* tmpFileName = "tmp";
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
    void testXsltParseStylesheetDocEx1();
    void testXsltParseStylesheetDocEx2();
    void testXsltApplyStylesheetEx1();
    void testXsltApplyStylesheetEx2(); // TO THINK: an error test
    void testXsltSaveResultToFileEx1();
    void testXsltSaveResultToFileEx2();
};
