QT       += core gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = GoBangClient
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    api/api.cpp \
    game/game.cpp \
    net/client.cpp \
    game/room.cpp \
    pvpchess.cpp \
    test.cpp \
    user.cpp \
    view/connectdig.cpp \
    view/mainwindow.cpp \
    view/notifydig.cpp \
    view/pvpwindow.cpp \
    view/pvmwindow.cpp \
    chess.cpp \
    view/dialogchoosepiece.cpp \
    view/dialoggameover.cpp \
    view/roomselect.cpp\
    aigame/possiblepositionmanager.cpp \
    aigame/chessai.cpp \
    aigame/acsearcher.cpp \
    aigame/chessengine.cpp \
    main.cpp


HEADERS += \
    api/api.h \
    game/game.h \
    global.h \
    net/client.h \
    game/room.h \
    pvpchess.h \
    test.h \
    user.h \
    view/connectdig.h \
    view/mainwindow.h \
    view/mainwindow.h \
    view/notifydig.h \
    view/pvpwindow.h \
    view/pvmwindow.h \
    chess.h \
    view/dialogchoosepiece.h \
    view/dialoggameover.h \
    view/roomselect.h\
    aigame/acsearcher.h \
    aigame/possiblepositionmanager.h \
    aigame/chessengine.h \
    aigame/chessai.h

FORMS += \
    pvpchess.ui \
    view/connectdig.ui \
    view/mainwindow.ui \
    view/notifydig.ui \
    view/pvpwindow.ui \
    view/pvmwindow.ui \
    chess.ui \
    view/dialogchoosepiece.ui \
    view/dialoggameover.ui \
    view/roomselect.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    aigame/acsearcher.h \
    aigame/chessai.h \
    aigame/chessengine.h \
    aigame/possiblepositionmanager.h \
    api/api.h \
    chess.h \
    global.h \
    test.h \
    user.h \
    view/connectdig.h \
    view/dialogchoosepiece.h \
    view/dialoggameover.h \
    view/mainwindow.h \
    view/notifydig.h \
    view/pvmwindow.h \
    view/pvpwindow.h \
    view/roomselect.h
