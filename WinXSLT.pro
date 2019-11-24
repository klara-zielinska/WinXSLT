#-------------------------------------------------
#
# Project created by QtCreator 2017-11-25T00:15:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = WinXSLT
TEMPLATE = app


SOURCES += src/main.cpp \
    src/Utils/tools.cpp \
    src/WindowController.cpp \
    src/Window.cpp \
    src/Xml/XmlReader.cpp \
    src/Xml/XmlPatterns.cpp \
    src/Xml/XmlHighlight.cpp \
    src/Utils/xsltex.cpp

HEADERS  += \
    src/Xml/XmlToken.h \
    src/Utils/tools.h \
    src/WindowController.h \
    src/IWindowController.h \
    src/Window.h \
    src/Xml/XmlReader.h \
    src/Xml/XmlPatterns.h \
    src/Xml/XmlHighlight.h \
    src/Utils/xsltex.h

FORMS    += \
    src/Window.ui


XMLINCLUDEPATH = C:/Qt/Tools/mingw730_64/opt/include
XMLLIBPATH     = C:/Qt/Tools/mingw730_64/opt/lib

INCLUDEPATH += $$XMLINCLUDEPATH \
    $$XMLINCLUDEPATH/libxml2

LIBS += -lxml2 \
    -lxslt \
    -L$$XMLLIBPATH

DISTFILES += \
    Doxyfile

RESOURCES += \
    resources.qrc

RC_ICONS = resources/icon.ico
