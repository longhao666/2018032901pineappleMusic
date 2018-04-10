#-------------------------------------------------
#
# Project created by QtCreator 2018-04-09T15:43:10
#
#-------------------------------------------------

QT       += widgets

QT       += core gui
#QT += sql
QT += network \
      xml \
      multimedia \
      multimediawidgets \
      widgets

TARGET = musicPlayer
TEMPLATE = lib
DESTDIR = ../bin

#DEFINES += LLLL_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


HEADERS += \
    histogramwidget.h \
    player.h \
    playercontrols.h \
    playlistmodel.h \
    videowidget.h

SOURCES += \
    histogramwidget.cpp \
    player.cpp \
    playercontrols.cpp \
    playlistmodel.cpp \
    videowidget.cpp