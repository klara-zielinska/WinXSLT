include(../config.pri)

QT += testlib gui
CONFIG += c++11 qt warn_on depend_includepath testcase

TEMPLATE = app

HEADERS += \
    Utils/tst_tools.h \
    Utils/tst_xsltutils.h \
    testtools.h \
    tst_testtools.h

SOURCES += \
    Utils/tst_tools.cpp \
    Utils/tst_xsltutils.cpp \
    main.cpp \
    testtools.cpp \
    tst_testtools.cpp

INCLUDEPATH += ../Application/src \
    $$XMLINCLUDEPATH \
    $$XMLINCLUDEPATH/libxml2

CONFIG(debug, debug|release){
    LIBS += $$shadowed($$PWD)/../Application/debug/tools.o \
            $$shadowed($$PWD)/../Application/debug/xsltutils.o }
CONFIG(release, debug|release){
    LIBS += $$shadowed($$PWD)/../Application/release/tools.o \
            $$shadowed($$PWD)/../Application/release/xsltutils.o }

LIBS += \
    -L$$XMLLIBPATH \
    -lxml2 \
    -lxslt \
    -llibarchive_static

DISTFILES +=

RESOURCES += \
    res.qrc
