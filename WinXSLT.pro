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

INCLUDEPATH += $$(XALANCROOT)/c/src \
    $$(XERCESCROOT)/src

debug {
INCLUDEPATH += $$(XALANCROOT)/c/Build/Win64/VC10/Debug/Nls/Include
}

release {
INCLUDEPATH += $$(XALANCROOT)/c/Build/Win64/VC10/Release/Nls/Include
}

LIBS += -L$$(XERCESCROOT)/lib \
    -L$$(XALANCLIB)

debug {
LIBS += -L$$(XERCESCROOT)/Build/Win64/VC10/Debug \
    -L$$(XALANCROOT)/c/Build/Win64/VC10/Debug \
    -lxerces-c_3D \
    -lXalan-C_1D
}

release {
LIBS += -L$$(XERCESCROOT)/Build/Win64/VC10/Release \
    -L$$(XALANCROOT)/c/Build/Win64/VC10/Release \
    -lxerces-c_3 \
    -lXalan-C_1
}

DISTFILES +=

RESOURCES += \
    resources.qrc

RC_ICONS = resources/icon.ico
