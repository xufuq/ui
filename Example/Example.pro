
QT       += core gui
QT += charts multimedia
QT += widgets serialport

RC_FILE = myico.rc

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Example
TEMPLATE = app


SOURCES += main.cpp\
        content.cpp \
    camera.cpp \
    electric.cpp \
    usart.cpp \
    menu.cpp \
    emythread.cpp \
    echart.cpp \
    epoint.cpp

HEADERS  += content.h \
    camera.h \
    electric.h \
    usart.h \
    menu.h \
    emythread.h \
    echart.h \
    epoint.h

DISTFILES += \
    ../build-Example-Desktop_Qt_5_10_0_MinGW_32bit-Debug/debug/qt.png

RESOURCES += \
    image.qrc
