include(../config.pri)

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = WinXSLT
TEMPLATE = app


SOURCES += src/main.cpp \
    src/Utils/tools.cpp \
    src/Utils/xsltutils.cpp \
    src/WindowController.cpp \
    src/Window.cpp \
    src/Xml/XmlReader.cpp \
    src/Xml/XmlPatterns.cpp \
    src/Xml/XmlHighlight.cpp

HEADERS  += \
    src/Utils/xsltutils.h \
    src/Xml/XmlToken.h \
    src/Utils/tools.h \
    src/WindowController.h \
    src/IWindowController.h \
    src/Window.h \
    src/Xml/XmlReader.h \
    src/Xml/XmlPatterns.h \
    src/Xml/XmlHighlight.h

FORMS    += \
    src/Window.ui

!isEmpty(XMLINCLUDEPATH) {
INCLUDEPATH += \
    $$XMLINCLUDEPATH \
    $$XMLINCLUDEPATH/libxml2
}

!isEmpty(XMLLIBPATH) {
LIBS += \
    -L$$XMLLIBPATH
}

LIBS += \
    -lxml2 \
    -lxslt

DISTFILES += \
    Doxyfile

RESOURCES += \
    resources.qrc



RC_ICONS = resources/icon.ico
