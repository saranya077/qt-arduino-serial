QT += core gui serialport widgets

CONFIG += c++11

TARGET = SerialPortExample
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui
