#-------------------------------------------------
#
# Project created by QtCreator 2014-02-18T14:30:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AssToSymbol
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    AsmToBin.cpp

HEADERS  += mainwindow.h \
    AsmToBin.h

FORMS    += mainwindow.ui

RESOURCES += \
    tr.qrc

QMAKE_CXXFLAGS += -std=c++0x
