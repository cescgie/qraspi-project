#-------------------------------------------------
#
# Project created by QtCreator 2014-12-03T14:23:17
#
#-------------------------------------------------

QT       += core gui
QT       += opengl
QT       += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTReversi
TEMPLATE = app


SOURCES += main.cpp \
    graphics.cpp \
    game.cpp \
    glview.cpp

HEADERS  += \
    define.h \
    graphics.h \
    game.h \
    glview.h
