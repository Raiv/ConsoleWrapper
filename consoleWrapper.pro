#-------------------------------------------------
#
# Project created by QtCreator 2014-12-05T22:49:06
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = consoleWrapper
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    consolewrapper.cpp \
    controlthread.cpp \
    threadpoolwithsignals.cpp \
    multithreadtcpserver.cpp \
    incomingconnection.cpp

HEADERS += \
    consolewrapper.h \
    controlthread.h \
    threadpoolwithsignals.h \
    multithreadtcpserver.h \
    incomingconnection.h
