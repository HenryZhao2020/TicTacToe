QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Attr.cpp \
    Board.cpp \
    Dialog.cpp \
    FileUtil.cpp \
    Game.cpp \
    GameAI.cpp \
    GameBar.cpp \
    IconUtil.cpp \
    Main.cpp \
    ScoreBoard.cpp \
    Square.cpp

HEADERS += \
    Attr.h \
    Board.h \
    Dialog.h \
    FileUtil.h \
    Game.h \
    GameAI.h \
    GameBar.h \
    IconUtil.h \
    ScoreBoard.h \
    Square.h

TARGET = "Tic Tac Toe"
QMAKE_TARGET_DESCRIPTION = "Tic Tac Toe"
RC_ICONS = "TTT.ico"
VERSION = "3.0.0"

TRANSLATIONS += \
    TTT_zh_CN.ts \
    TTT_zh_TW.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    TTT.qrc

DISTFILES +=
