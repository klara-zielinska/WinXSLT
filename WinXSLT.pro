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
    src/tools.cpp \
    src/WindowController.cpp \
    src/Window.cpp \
    src/XmlReader.cpp \
    src/XmlPatterns.cpp \
    src/XmlHighlight.cpp

HEADERS  += \
    src/tools.h \
    src/WindowController.h \
    src/IWindowController.h \
    src/Window.h \
    src/XmlReader.h \
    src/XmlPatterns.h \
    src/XmlHighlight.h

FORMS    += \
    src/Window.ui

INCLUDEPATH += $$(XALANCINCLUDE) \
    $$(XALANCNLS) \
    $$(XERCESCROOT)/include

LIBS += -L$$(XERCESCROOT)/lib \
    -L$$(XALANCLIB) \
    -lxerces-c_3 \
    -lXalan-C_1

DISTFILES +=

RESOURCES += \
    resources.qrc

RC_ICONS = resources/icon.ico
