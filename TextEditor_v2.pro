#-------------------------------------------------
#
# Project created by QtCreator 2020-12-25T09:37:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TextEditor_v2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    documenttextedit.cpp

HEADERS  += mainwindow.h \
    documenttextedit.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc

TRANSLATIONS += QtLanguage_en.ts
CODECFORSRC     = UTF-8
