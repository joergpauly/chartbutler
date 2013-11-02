#-------------------------------------------------
#
# Project created by QtCreator 2011-11-17T18:13:01
#
#-------------------------------------------------

QT += core widgets sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChartButler
TEMPLATE = app
VERSION = 2.1.72

SOURCES += main.cpp\
        cmainwindow.cpp \
    cdatabasemanager.cpp \
    coptions.cpp \
    cstatus.cpp \
    chelp.cpp \
    cregister.cpp \
    cnetworkmanager.cpp \
    cparser.cpp


HEADERS  += cmainwindow.h \
    cdatabasemanager.h \
    coptions.h \
    globals.h \
    cstatus.h \
    chelp.h \
    cregister.h \
    cnetworkmanager.h \
    cparser.h


FORMS    += cmainwindow.ui \
    coptions.ui \
    cstatus.ui \
    chelp.ui \
    cregister.ui

RESOURCES += \
    cbRessources.qrc

OTHER_FILES += \
    cb.ico \
    cb.png \
    gat24.jpg









