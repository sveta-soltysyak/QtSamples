#-------------------------------------------------
#
# Project created by QtCreator 2015-12-27T11:46:20
#
#-------------------------------------------------

QT       += core gui
QT += positioning

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GPSSample
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gpspositionprovider.cpp

HEADERS  += mainwindow.h \
    gpspositionprovider.h

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = 

