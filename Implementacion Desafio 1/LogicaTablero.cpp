#include "LogicaTablero.h"
#include "AbstraccionDeMemoria.h"
#include <cstdlib>

int bytesNecesariosTablero(int filas, int columnas) {
    int total_posiciones = filas * columnas;
    int total_bits = total_posiciones * 3;
    return (total_bits + 7) / 8;
}

int generarFichaAleatoria() {
    return rand() % 6;
}

unsigned char* crearTablero(int filas, int columnas) {

    int bytes_necesarios = bytesNecesariosTablero(filas, columnas);

    unsigned char* tablero = new unsigned char[bytes_necesarios];

    for (int i = 0; i < bytes_necesarios; i++) {
        tablero[i] = 0;
    }

    for (int f = 0; f < filas; f++) {
        for (int c = 0; c < columnas; c++) {
            escribirFicha(tablero, columnas, f, c, generarFichaAleatoria());
        }
    }

    return tablero;
}

void liberarTablero(unsigned char* tablero) {
    if (tablero != nullptr) {
        delete[] tablero;
    }
}
