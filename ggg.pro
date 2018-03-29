#-------------------------------------------------
#
# Project created by QtCreator 2018-03-28T14:44:22
#
#-------------------------------------------------

QT       += core gui
QT += sql
QT += network \
      xml \
      multimedia \
      multimediawidgets \
      widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ggg
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    databaseDriver/connection.cpp \
    databaseDriver/databasedriver.cpp \
    musicPlayer/histogramwidget.cpp \
    musicPlayer/player.cpp \
    musicPlayer/playercontrols.cpp \
    musicPlayer/playlistmodel.cpp \
    musicPlayer/videowidget.cpp

HEADERS += \
        mainwindow.h \
    databaseDriver/connection.h \
    databaseDriver/databasedriver.h \
    musicPlayer/histogramwidget.h \
    musicPlayer/player.h \
    musicPlayer/playercontrols.h \
    musicPlayer/playlistmodel.h \
    musicPlayer/videowidget.h

FORMS += \
        mainwindow.ui \
    databaseDriver/databasedriver.ui
