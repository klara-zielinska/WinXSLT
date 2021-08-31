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

!isEmpty(XMLINCLUDEPATH) {
INCLUDEPATH += \
    $$XMLINCLUDEPATH \
    $$XMLINCLUDEPATH/libxml2
}

INCLUDEPATH += \
    ../Application/src

LIBS += $$shadowed($$PWD)/../Application/tools.o \
        $$shadowed($$PWD)/../Application/xsltutils.o \
        $$shadowed($$PWD)/../Application/XmlPatterns.o \
        $$shadowed($$PWD)/../Application/XmlReader.o \
        $$shadowed($$PWD)/../Application/XmlHighlight.o

#CONFIG(debug, debug|release){
#    LIBS += $$shadowed($$PWD)/../Application/debug/tools.o \
#            $$shadowed($$PWD)/../Application/debug/xsltutils.o \
#            $$shadowed($$PWD)/../Application/debug/XmlPatterns.o \
#            $$shadowed($$PWD)/../Application/debug/XmlReader.o \
#            $$shadowed($$PWD)/../Application/debug/XmlHighlight.o }
#CONFIG(release, debug|release){
#    LIBS += $$shadowed($$PWD)/../Application/release/tools.o \
#            $$shadowed($$PWD)/../Application/release/xsltutils.o \
#            $$shadowed($$PWD)/../Application/release/XmlPatterns.o \
#            $$shadowed($$PWD)/../Application/release/XmlReader.o \
#            $$shadowed($$PWD)/../Application/release/XmlHighlight.o }

!isEmpty(XMLLIBPATH) {
LIBS += \
    -L$$XMLLIBPATH
}

LIBS += \
    -lxml2 \
    -lxslt \
    -larchive

DISTFILES +=

RESOURCES += \
    res.qrc
