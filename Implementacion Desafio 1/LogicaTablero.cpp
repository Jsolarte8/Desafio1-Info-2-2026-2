#include "logicaTablero.h"
#include "abstraccionDeMemoria.h"
#include <cstdlib>

unsigned char* crearTablero(int filas, int columnas) {

    int total_posiciones = filas * columnas;
    int total_bits = total_posiciones * 3;
    int bytes_necesarios = (total_bits + 7) / 8;

    unsigned char* tablero = new unsigned char[bytes_necesarios];

    for (int i = 0; i < bytes_necesarios; i++) {
        tablero[i] = 0;
    }

    for (int f = 0; f < filas; f++) {
        for (int c = 0; c < columnas; c++) {
            int ficha_aleatoria = rand() % 6;
            escribirFicha(tablero, columnas, f, c, ficha_aleatoria);
        }
    }

    return tablero;
}

void liberarTablero(unsigned char* tablero) {
    if (tablero != nullptr) {
        delete[] tablero;
    }
}