#-------------------------------------------------
#
# Project created by QtCreator 2014-10-30T09:29:26
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = serverJob
TEMPLATE = app


SOURCES += main.cpp\
        mainwindowserver.cpp \
    SocketServer.cpp \
    tcpthread.cpp \
    somFun.cpp \
    glo.cpp

HEADERS  += mainwindowserver.h \
    SocketServer.h \
    tcpthread.h \
    somFun.h \
    glo.h

FORMS    += mainwindowserver.ui
