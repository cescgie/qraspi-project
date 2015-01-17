#-------------------------------------------------
#
# Project created by QtCreator 2014-12-03T14:23:17
#
#-------------------------------------------------

QT       += opengl
QT       += widgets
QT       += core gui multimedia
unix:!macx{
LIBS     += -lGLU
}
QT       += sql xml

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
    infosmoves.cpp \
    board.cpp \
    infoview.cpp \
    ai.cpp \
    infoai.cpp \
    playersetting.cpp \
    moves.cpp \
    listmoves.cpp \
    highscore.cpp

HEADERS  += \
    define.h \
    graphics.h \
    game.h \
    glview.h \
    square.h \
    player.h \
    infosmoves.h \
    board.h \
    infoview.h \
    ai.h \
    infoai.h \
    playersetting.h \
    moves.h \
    listmoves.h \
    highscore.h

FORMS += \
    playersetting.ui

RESOURCES += \
    Resources.qrc

