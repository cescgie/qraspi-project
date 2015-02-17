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
QT       += printsupport
ICON = QtM.icns

TEMPLATE = app
TARGET = QTReversi
DEPENDPATH += .
INCLUDEPATH += .
CONFIG += qt

# Input
HEADERS += \
    player.h \
    square.h \
    board.h \
    define.h \
    ai.h \
    game.h \
    graphics.h \
    highscore.h \
    imove.h \
    glview.h \
    infosmoves.h \
    infoview.h \
    infoai.h \
    playersetting.h \
    listmoves.h
FORMS += \
    playersetting.ui
SOURCES += \
    main.cpp \
    player.cpp \
    square.cpp \
    board.cpp \
    ai.cpp \
    game.cpp \
    graphics.cpp \
    highscore.cpp \
    imove.cpp \
    glview.cpp \
    infosmoves.cpp \
    infoai.cpp \
    infoview.cpp \
    playersetting.cpp \
    listmoves.cpp

RESOURCES += Resources.qrc
