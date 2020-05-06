QT       += core gui
QT       +=network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

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
    game/game.cpp \
    game/gamethread.cpp \
    game/room.cpp \
    game/roomman.cpp \
    game/user.cpp \
    game/userman.cpp \
    gobang.cpp \
    network/api.cpp \
    network/server.cpp \
    util.cpp \
    view/homewidget.cpp \
    main.cpp

HEADERS += \
    game/game.h \
    game/gamethread.h \
    game/room.h \
    game/roomman.h \
    game/user.h \
    game/userman.h \
    gobang.h \
    network/api.h \
    network/server.h \
    util.h \
    view/homewidget.h


FORMS += \
    view/homewidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
