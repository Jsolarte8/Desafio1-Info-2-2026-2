#include "estructuraTablero.h"
#include "abstraccionDeMemoria.h"
#include "logicaTablero.h"

unsigned char* agregarFila(unsigned char* tableroActual, int& filas, int columnas, int posicionInsercion) {

    int filasResultantes = filas + 1;
    int bytesResultantes = bytesNecesariosTablero(filasResultantes, columnas);

    unsigned char* tableroResultante = new unsigned char[bytesResultantes];
    for (int i = 0; i < bytesResultantes; i++) {
        tableroResultante[i] = 0;
    }

    for (int filaActual = 0; filaActual < posicionInsercion; filaActual++) {
        for (int columnaActual = 0; columnaActual < columnas; columnaActual++) {
            int valorFicha = leerFicha(tableroActual, columnas, filaActual, columnaActual);
            escribirFicha(tableroResultante, columnas, filaActual, columnaActual, valorFicha);
        }
    }

    for (int columnaActual = 0; columnaActual < columnas; columnaActual++) {
        escribirFicha(tableroResultante, columnas, posicionInsercion, columnaActual, generarFichaAleatoria());
    }

    for (int filaActual = posicionInsercion; filaActual < filas; filaActual++) {
        for (int columnaActual = 0; columnaActual < columnas; columnaActual++) {
            int valorFicha = leerFicha(tableroActual, columnas, filaActual, columnaActual);
            escribirFicha(tableroResultante, columnas, filaActual + 1, columnaActual, valorFicha);
        }
    }

    delete[] tableroActual;
    filas = filasResultantes;
    return tableroResultante;
}

unsigned char* eliminarFila(unsigned char* tableroActual, int& filas, int columnas, int posicionEliminacion) {

    int filasResultantes = filas - 1;
    int bytesResultantes = bytesNecesariosTablero(filasResultantes, columnas);
    int bytesActuales    = bytesNecesariosTablero(filas, columnas);

    unsigned char* tableroTemporal = new unsigned char[bytesResultantes];
    for (int i = 0; i < bytesResultantes; i++) {
        tableroTemporal[i] = 0;
    }

    int filaDestino = 0;
    for (int filaActual = 0; filaActual < filas; filaActual++) {
        if (filaActual == posicionEliminacion) {
            continue;
        }
        for (int columnaActual = 0; columnaActual < columnas; columnaActual++) {
            int valorFicha = leerFicha(tableroActual, columnas, filaActual, columnaActual);
            escribirFicha(tableroTemporal, columnas, filaDestino, columnaActual, valorFicha);
        }
        filaDestino++;
    }

    filas = filasResultantes;

    bool utilizacionCaeDebajoDel65Porciento = (bytesResultantes * 100) < (bytesActuales * 65);

    if (utilizacionCaeDebajoDel65Porciento) {
        delete[] tableroActual;
        return tableroTemporal;
    }

    for (int i = 0; i < bytesResultantes; i++) {
        tableroActual[i] = tableroTemporal[i];
    }
    delete[] tableroTemporal;
    return tableroActual;
}

unsigned char* agregarColumna(unsigned char* tableroActual, int filas, int& columnas, int posicionInsercion) {

    int columnasResultantes = columnas + 1;
    int bytesResultantes    = bytesNecesariosTablero(filas, columnasResultantes);

    unsigned char* tableroResultante = new unsigned char[bytesResultantes];
    for (int i = 0; i < bytesResultantes; i++) {
        tableroResultante[i] = 0;
    }

    for (int filaActual = 0; filaActual < filas; filaActual++) {

        for (int columnaActual = 0; columnaActual < posicionInsercion; columnaActual++) {
            int valorFicha = leerFicha(tableroActual, columnas, filaActual, columnaActual);
            escribirFicha(tableroResultante, columnasResultantes, filaActual, columnaActual, valorFicha);
        }

        escribirFicha(tableroResultante, columnasResultantes, filaActual, posicionInsercion, generarFichaAleatoria());

        for (int columnaActual = posicionInsercion; columnaActual < columnas; columnaActual++) {
            int valorFicha = leerFicha(tableroActual, columnas, filaActual, columnaActual);
            escribirFicha(tableroResultante, columnasResultantes, filaActual, columnaActual + 1, valorFicha);
        }
    }

    delete[] tableroActual;
    columnas = columnasResultantes;
    return tableroResultante;
}

unsigned char* eliminarColumna(unsigned char* tableroActual, int filas, int& columnas, int posicionEliminacion) {

    int columnasResultantes = columnas - 1;
    int bytesResultantes    = bytesNecesariosTablero(filas, columnasResultantes);
    int bytesActuales       = bytesNecesariosTablero(filas, columnas);

    unsigned char* tableroTemporal = new unsigned char[bytesResultantes];
    for (int i = 0; i < bytesResultantes; i++) {
        tableroTemporal[i] = 0;
    }

    for (int filaActual = 0; filaActual < filas; filaActual++) {
        int columnaDestino = 0;
        for (int columnaActual = 0; columnaActual < columnas; columnaActual++) {
            if (columnaActual == posicionEliminacion) {
                continue;
            }
            int valorFicha = leerFicha(tableroActual, columnas, filaActual, columnaActual);
            escribirFicha(tableroTemporal, columnasResultantes, filaActual, columnaDestino, valorFicha);
            columnaDestino++;
        }
    }

    columnas = columnasResultantes;

    bool utilizacionCaeDebajoDel65Porciento = (bytesResultantes * 100) < (bytesActuales * 65);

    if (utilizacionCaeDebajoDel65Porciento) {
        delete[] tableroActual;
        return tableroTemporal;
    }

    for (int i = 0; i < bytesResultantes; i++) {
        tableroActual[i] = tableroTemporal[i];
    }
    delete[] tableroTemporal;
    return tableroActual;
}