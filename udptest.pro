#-------------------------------------------------
#
# Project created by QtCreator 2015-12-14T18:51:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = udptest
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    listener.cpp \
    sender.cpp \
    joystick.cpp

HEADERS  += mainwindow.h \
    listener.h \
    sender.h \
    joystick.h

FORMS    += mainwindow.ui


QT += network

LIBS += -LC:/Users/Esam/Downloads/SDL-devel-1.2.15-mingw32/SDL-1.2.15/lib -lSDL
INCLUDEPATH += C:/Users/Esam/Downloads/SDL-devel-1.2.15-mingw32/SDL-1.2.15/include/SDL
