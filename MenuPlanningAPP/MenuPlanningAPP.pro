#-------------------------------------------------
#
# Project created by QtCreator 2016-01-27T18:30:26
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MenuPlanningAPP
TEMPLATE = app

CONFIG += console

SOURCES += main.cpp\
        mainwindowmenuplan.cpp \
    database.cpp \
    ingredientes.cpp \
    platos.cpp \
    planificador.cpp \
    tablaplatos.cpp \
    individuo.cpp \
    poblacion.cpp \
    quicksort.cpp \
    visualizacionplan.cpp \
    planespecial.cpp \
    test_output.cpp \
    matlab_script.cpp
    images

HEADERS  += mainwindowmenuplan.h \
    database.h \
    enums.h \
    individuo.h

FORMS    += mainwindowmenuplan.ui

RESOURCES += resourceFile.qrc
