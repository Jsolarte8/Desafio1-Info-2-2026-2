QT += core
QT -= gui

TEMPLATE = app

CONFIG += console c++17
CONFIG -= app_bundle


SOURCES += \
    AbstraccionDeMemoria.cpp \
    Combinaciones.cpp \
    EstructuraTablero.cpp \
    Juego.cpp \
    LogicaTablero.cpp \
    Partida.cpp \
    Visualizacion.cpp \
    main.cpp


HEADERS += \
    AbstraccionDeMemoria.h \
    Combinaciones.h \
    EstructuraTablero.h \
    Juego.h \
    LogicaTablero.h \
    Partida.h \
    Visualizacion.h