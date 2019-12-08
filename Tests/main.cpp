#include "tst_testtools.h"
#include "Utils/tst_tools.h"
#include "Utils/tst_xsltutils.h"
#include <QtTest>


int main(int argc, char** argv)
{
    auto run = [argc, argv](QObject &test) {
        return QTest::qExec(&test, argc, argv); };

   tst_testtools tstTestTools;
   tst_tools tstTools;
   tst_xsltutils tstXsltEx;

   run(tstTestTools);
   run(tstTools);
   run(tstXsltEx);

   return 0;
}
