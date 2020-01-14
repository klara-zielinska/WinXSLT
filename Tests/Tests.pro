include(../config.pri)

QT += testlib gui
CONFIG += c++11 qt warn_on depend_includepath testcase

TEMPLATE = app

HEADERS += \
    Utils/tst_tools.h \
    Utils/tst_xsltutils.h \
    Xml/tst_XmlHighlight.h \
    Xml/tst_XmlPatterns.h \
    Xml/tst_XmlReader.h \
    testtools.h \
    tst_testtools.h

SOURCES += \
    Utils/tst_tools.cpp \
    Utils/tst_xsltutils.cpp \
    Xml/tst_XmlHighlight.cpp \
    Xml/tst_XmlPatterns.cpp \
    Xml/tst_XmlReader.cpp \
    main.cpp \
    testtools.cpp \
    tst_testtools.cpp

INCLUDEPATH += ../Application/src \
    $$XMLINCLUDEPATH \
    $$XMLINCLUDEPATH/libxml2

CONFIG(debug, debug|release){
    LIBS += $$shadowed($$PWD)/../Application/debug/tools.o \
            $$shadowed($$PWD)/../Application/debug/xsltutils.o \
            $$shadowed($$PWD)/../Application/debug/XmlPatterns.o \
            $$shadowed($$PWD)/../Application/debug/XmlReader.o \
            $$shadowed($$PWD)/../Application/debug/XmlHighlight.o }
CONFIG(release, debug|release){
    LIBS += $$shadowed($$PWD)/../Application/release/tools.o \
            $$shadowed($$PWD)/../Application/release/xsltutils.o \
            $$shadowed($$PWD)/../Application/release/XmlPatterns.o \
            $$shadowed($$PWD)/../Application/release/XmlReader.o \
            $$shadowed($$PWD)/../Application/release/XmlHighlight.o }

LIBS += \
    -L$$XMLLIBPATH \
    -lxml2 \
    -lxslt \
    -llibarchive_static

DISTFILES +=

RESOURCES += \
    res.qrc
