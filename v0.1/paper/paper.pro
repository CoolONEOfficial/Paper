#-------------------------------------------------
#
# Project created by QtCreator 2016-01-27T22:42:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Paper
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    controls.cpp

HEADERS  += widget.h

FORMS    += widget.ui \
    dialog.ui

RC_ICONS = icon.ico
