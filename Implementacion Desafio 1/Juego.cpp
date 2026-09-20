#include "Juego.h"
#include "abstraccionDeMemoria.h"
#include "logicaTablero.h"

bool eliminarFicha(unsigned char* tablero, int filas, int columnas, int fila, int col) {

    if (fila < 0 || fila >= filas || col < 0 || col >= columnas) {
        return false;
    }

    escribirFicha(tablero, columnas, fila, col, FICHA_VACIA);

    return true;
}

void aplicarGravedad(unsigned char* tablero, int filas, int columnas) {

    for (int col = 0; col < columnas; ++col) {

        int filaDestino = filas - 1;

        for (int fila = filas - 1; fila >= 0; --fila) {

            int valorFicha = leerFicha(tablero, columnas, fila, col);

            if (valorFicha == FICHA_VACIA) {
                continue;
            }

            if (fila != filaDestino) {
                escribirFicha(tablero, columnas, filaDestino, col, valorFicha);
                escribirFicha(tablero, columnas, fila, col, FICHA_VACIA);
            }

            --filaDestino;
        }
    }
}

void rellenarVaciosSuperiores(unsigned char* tablero, int filas, int columnas) {

    for (int fila = 0; fila < filas; ++fila) {
        for (int col = 0; col < columnas; ++col) {

            if (leerFicha(tablero, columnas, fila, col) == FICHA_VACIA) {
                escribirFicha(tablero, columnas, fila, col, generarFichaAleatoria());
            }
        }
    }
}