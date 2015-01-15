#-------------------------------------------------
#
# Project created by QtCreator 2014-12-03T14:23:17
#
#-------------------------------------------------

QT       += opengl
QT       += widgets
QT       += core gui multimedia

TARGET = QTReversi
TEMPLATE = app
DEPENDPATH += .
INCLUDEPATH += .


SOURCES += main.cpp \
    graphics.cpp \
    game.cpp \
    glview.cpp \
    square.cpp \
    player.cpp \
    move.cpp \
    infosmoves.cpp \
    board.cpp \
    infoview.cpp \
    ai.cpp \
    infoai.cpp \
    playersetting.cpp

HEADERS  += \
    define.h \
    graphics.h \
    game.h \
    glview.h \
    square.h \
    player.h \
    move.h \
    infosmoves.h \
    board.h \
    infoview.h \
    ai.h \
    infoai.h \
    playersetting.h

FORMS += \
    playersetting.ui

RESOURCES += \
    Resources.qrc

