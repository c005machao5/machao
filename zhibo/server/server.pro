QT -= gui

QT += network sql

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    server/server.cpp \
    socket/clientsocket.cpp \
    sql/sqldao.cpp \
    sql/sqlmanager.cpp \
    protocol/protocol.cpp \
    model/user.cpp \
    room/guest.cpp \
    room/room.cpp \
    room/roommanager.cpp

HEADERS += \
    server/server.h \
    socket/clientsocket.h \
    sql/sqldao.h \
    sql/sqlmanager.h \
    protocol/protocol.h \
    model/user.h \
    room/guest.h \
    room/room.h \
    room/roommanager.h
