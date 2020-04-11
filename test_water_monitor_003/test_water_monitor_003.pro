#-------------------------------------------------
#
# Project created by QtCreator 2019-08-04T21:02:10
#
#-------------------------------------------------

QT       += core gui
QT+=charts
QT+=network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test_water_monitor_003
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
main.cpp \
        mainwindow.cpp \
    mainwindowreg.cpp \
    mainwindoworduser.cpp \
    mainwindowadmuser.cpp\
    #realtimedisplay.cpp \
    history_data_query.cpp \
        historydataanalyse.cpp \
        showtable.cpp \
        showlinechart.cpp \
        showbarchart.cpp    \
        realtimedisplay.cpp \
        clientsocket.cpp \
   signal_s.cpp




HEADERS += \
mainwindow.h \
    mainwindowreg.h \
    mainwindoworduser.h \
    mainwindowadmuser.h\
    #realtimedisplay.h \
    history_data_query.h \
        historydataanalyse.h \
        showtable.h \
        showlinechart.h \
        showbarchart.h  \
        realtimedisplay.h \
       clientsocket.h \
       signal_s.h\
       WS2tcpip.h\
   WinSock2.h





FORMS += \
 mainwindow.ui \
    mainwindowreg.ui \
    mainwindoworduser.ui \
    mainwindowadmuser.ui\
    history_data_query.ui \
    historydataanalyse.ui \
    showtable.ui \
    showlinechart.ui \
    showbarchart.ui \
    realtimedisplay.ui
LIBS  +=\
    -lws2_32



