#include "tst_testtools.h"
#include "Utils/tst_tools.h"
#include "Utils/tst_xsltutils.h"
#include "Xml/tst_XmlPatterns.h"
#include "Xml/tst_XmlReader.h"
#include "Xml/tst_XmlHighlight.h"
#include <libxslt/xsltutils.h>
#include <QtTest>


void silentErrorHandler(void *ctx, const char *msg, ...)
{
}

int main(int argc, char** argv)
{
    auto run = [argc, argv](QObject &test) {
        return QTest::qExec(&test, argc, argv); };

    xmlSubstituteEntitiesDefault(1);
    xmlLoadExtDtdDefaultValue = 1;
    xmlSetGenericErrorFunc(nullptr, &silentErrorHandler);
    xsltSetGenericErrorFunc(nullptr, &silentErrorHandler);

    tst_testtools tstTestTools;
    tst_tools tstTools;
    tst_xsltutils tstXsltUtils;
    tst_XmlPatterns tstXmlPatterns;
    tst_XmlReader tstXmlReader;
    tst_XmlHighlight tstXmlHighlight;

    run(tstTestTools);
    run(tstTools);
    run(tstXsltUtils);
    run(tstXmlPatterns);
    run(tstXmlReader);
    run(tstXmlHighlight);
    return 0;
}
