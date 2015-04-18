#-------------------------------------------------
#
# Project created by QtCreator 2015-03-30T23:28:29
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_asynctasktest
CONFIG   += console c++11
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_asynctasktest.cpp \
    task.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    task.h
