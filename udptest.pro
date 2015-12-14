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
    sender.cpp

HEADERS  += mainwindow.h \
    listener.h \
    sender.h

FORMS    += mainwindow.ui


QT += network
