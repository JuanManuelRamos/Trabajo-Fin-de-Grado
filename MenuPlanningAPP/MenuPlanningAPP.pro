#-------------------------------------------------
#
# Project created by QtCreator 2016-01-27T18:30:26
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MenuPlanningAPP
TEMPLATE = app


SOURCES += main.cpp\
        mainwindowmenuplan.cpp \
    database.cpp \
    ingredientes.cpp \
    platos.cpp \
    planificador.cpp \
    tablaplatos.cpp
    images

HEADERS  += mainwindowmenuplan.h \
    database.h \
    enums.h

FORMS    += mainwindowmenuplan.ui

RESOURCES += resourceFile.qrc
