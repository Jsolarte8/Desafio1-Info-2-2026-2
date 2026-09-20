#include "AbstraccionDeMemoria.h"
#include <iostream>
using namespace std;

void calcularUbicacion(int indice, int& byte_objetivo, int& posicion_interna, int& bits_disponibles) {

    int bit_inicial = indice * 3;

    byte_objetivo = bit_inicial / 8;
    posicion_interna = bit_inicial % 8;

    bits_disponibles = 8 - posicion_interna;
}

int leerFichaIndice(const unsigned char* tablero, int indice) {
    int byte_objetivo = 0;
    int posicion_interna = 0;
    int bits_disponibles = 0;

    calcularUbicacion(indice, byte_objetivo, posicion_interna, bits_disponibles);

    if (bits_disponibles >= 3) {
        int ficha = tablero[byte_objetivo] >> posicion_interna;
        return ficha & 7;
    } else {
        int pedazo1 = tablero[byte_objetivo] >> posicion_interna;
        int mascara1 = (1 << bits_disponibles) - 1;
        pedazo1 = pedazo1 & mascara1;

        int bits_faltantes = 3 - bits_disponibles;
        int mascara2 = (1 << bits_faltantes) - 1;
        int pedazo2 = tablero[byte_objetivo + 1] & mascara2;

        int ficha_completa = (pedazo2 << bits_disponibles) | pedazo1;
        return ficha_completa;
    }
}

void escribirFichaIndice(unsigned char* tablero, int indice, int nueva_ficha) {

    int byte_objetivo = 0;
    int posicion_interna = 0;
    int bits_disponibles = 0;

    calcularUbicacion(indice, byte_objetivo, posicion_interna, bits_disponibles);

    if (bits_disponibles >= 3) {
        int mascara_demolicion = ~(7 << posicion_interna);
        tablero[byte_objetivo] = tablero[byte_objetivo] & mascara_demolicion;

        tablero[byte_objetivo] = tablero[byte_objetivo] | (nueva_ficha << posicion_interna);

    } else {

        int mascara_limpieza1 = ~(((1 << bits_disponibles) - 1) << posicion_interna);
        tablero[byte_objetivo] = tablero[byte_objetivo] & mascara_limpieza1;

        int pedazo1 = nueva_ficha & ((1 << bits_disponibles) - 1);
        tablero[byte_objetivo] = tablero[byte_objetivo] | (pedazo1 << posicion_interna);


        int bits_faltantes = 3 - bits_disponibles;
        int mascara_limpieza2 = ~((1 << bits_faltantes) - 1);
        tablero[byte_objetivo + 1] = tablero[byte_objetivo + 1] & mascara_limpieza2;

        int pedazo2 = nueva_ficha >> bits_disponibles;
        tablero[byte_objetivo + 1] = tablero[byte_objetivo + 1] | pedazo2;
    }
}

int leerFicha(const unsigned char* tablero, int columnas, int fila, int col) {
    int indice = (fila * columnas) + col;
    return leerFichaIndice(tablero, indice);
}

void escribirFicha(unsigned char* tablero, int columnas, int fila, int col, int nueva_ficha) {
    int indice = (fila * columnas) + col;
    escribirFichaIndice(tablero, indice, nueva_ficha);
}