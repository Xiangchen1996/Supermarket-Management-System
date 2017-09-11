#-------------------------------------------------
#
# Project created by QtCreator 2017-06-22T14:49:17
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MarketServer
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    fortuneserver.cpp \
    fortunethread.cpp \
    jsonparser.cpp \
    jsonwrapper.cpp

HEADERS  += dialog.h \
    fortuneserver.h \
    fortunethread.h \
    jsonparser.h \
    jsonwrapper.h

RESOURCES += \
    res.qrc
