#-------------------------------------------------
#
# Project created by QtCreator 2018-04-15T18:34:01
#
#-------------------------------------------------

QT       += widgets multimedia
QT += multimediawidgets

TARGET = musicVideo
TEMPLATE = app
DESTDIR = ../bin

DEFINES += MUSICVIDEO_LIBRARY

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
#        musicvideo.cpp \
    lyricfile.cpp \
    musicplayer.cpp \
    musicvideo.cpp \
    mylistwidget.cpp \
    videowidget.cpp \
    main.cpp

HEADERS += \
#        musicvideo.h \
        musicvideo_global.h \ 
    lyricfile.h \
    musicplayer.h \
    musicvideo.h \
    musicvideo_global.h \
    mylistwidget.h \
    videowidget.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    musicplayer.ui
