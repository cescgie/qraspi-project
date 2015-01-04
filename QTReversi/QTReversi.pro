#-------------------------------------------------
#
# Project created by QtCreator 2014-12-03T14:23:17
#
#-------------------------------------------------

QT       += opengl
QT       += widgets

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
    preferencesdialog.cpp \
    ai.cpp

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
    preferencesdialog.h \
    ai.h

FORMS += \
    preferencesdialog.ui

RESOURCES += \
    Resources.qrc

