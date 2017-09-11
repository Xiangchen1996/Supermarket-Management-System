#-------------------------------------------------
#
# Project created by QtCreator 2017-06-21T14:46:09
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Market
TEMPLATE = app


SOURCES +=\
    umethod.cpp \
    maindialog.cpp \
    employeedialog.cpp \
    main.cpp \
    purchasedialog.cpp \
    storagedialog.cpp \
    providerdialog.cpp \
    logindialog.cpp \
    jsonwrapper.cpp \
    jsonparser.cpp \
    selldialog.cpp \
    systemdialog.cpp \
    vipdialog.cpp \
    welcomedialog.cpp \
    exportexcelobject.cpp


HEADERS  += \
    umethod.h \
    maindialog.h \
    timethread.h \
    employeedialog.h \
    purchasedialog.h \
    storagedialog.h \
    providerdialog.h \
    logindialog.h \
    jsonwrapper.h \
    jsonparser.h \
    selldialog.h \
    systemdialog.h \
    vipdialog.h \
    welcomedialog.h \
    exportexcelobject.h


FORMS    += \
    maindialog.ui \
    employeedialog.ui \
    purchasedialog.ui \
    storagedialog.ui \
    providerdialog.ui \
    logindialog.ui \
    selldialog.ui \
    systemdialog.ui \
    vipdialog.ui \
    welcomedialog.ui

RESOURCES += \
    images.qrc

DISTFILES += \
    images/chart.png \
    images/control-panel.png \
    images/inventory-maintenance.png \
    images/members.png \
    images/packing2.png \
    images/report_calc.png \
    images/smart-folder.png
RC_FILE = shop.rc
