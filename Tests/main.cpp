#include "tst_testtools.h"
#include "Utils/tst_tools.h"
#include "Utils/tst_xsltutils.h"
#include "Xml/tst_XmlPatterns.h"
#include "Xml/tst_XmlReader.h"
#include <QtTest>


int main(int argc, char** argv)
{
    auto run = [argc, argv](QObject &test) {
        return QTest::qExec(&test, argc, argv); };

   tst_testtools tstTestTools;
   tst_tools tstTools;
   tst_xsltutils tstXsltUtils;
   tst_XmlPatterns tstXmlPatterns;
   tst_XmlReader tstXmlReader;

   run(tstTestTools);
   run(tstTools);
   run(tstXsltUtils);
   run(tstXmlPatterns);
   run(tstXmlReader);
   return 0;
}
