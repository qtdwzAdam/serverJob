#-------------------------------------------------
#
# Project created by QtCreator 2014-10-30T09:29:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = serverJob
TEMPLATE = app


SOURCES += main.cpp\
        mainwindowserver.cpp \
    SocketServer.cpp \
    protocol.cpp

HEADERS  += mainwindowserver.h \
    SocketServer.h \
    protocol.h

FORMS    += mainwindowserver.ui
