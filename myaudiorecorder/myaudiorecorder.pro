#-------------------------------------------------
#
# Project created by QtCreator 2016-04-30T10:21:36
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = myaudiorecorder
TEMPLATE = lib
DESTDIR = ../bin

DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += main.cpp \
    myRecorderWidget.cpp

HEADERS  += \
    myRecorderWidget.h

FORMS    += \
    myRecorderWidget.ui
