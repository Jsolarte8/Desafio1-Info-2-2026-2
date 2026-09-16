QT += core
QT -= gui

TEMPLATE = app

CONFIG += console c++17
CONFIG -= app_bundle


SOURCES += \
    main.cpp \
    abstraccionDeMemoria.cpp \
    logicaTablero.cpp \
    combinaciones.cpp \
    visualizacion.cpp


HEADERS += \
    abstraccionDeMemoria.h \
    logicaTablero.h \
    combinaciones.h \
    visualizacion.h