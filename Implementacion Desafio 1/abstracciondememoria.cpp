#include "abstraccionDeMemoria.h"
#include <iostream>
using namespace std;

void calcularUbicacion(int columnas, int fila, int col, int& byte_objetivo, int& posicion_interna, int& bits_disponibles) {

    int indice = (fila * columnas) + col;
    int bit_inicial = indice * 3;

    byte_objetivo = bit_inicial / 8;
    posicion_interna = bit_inicial % 8;

    bits_disponibles = 8 - posicion_interna;
}

int leerFicha(unsigned char* tablero, int columnas, int fila, int col){
    int byte_objetivo = 0;
    int posicion_interna = 0;
    int bits_disponibles = 0;

    calcularUbicacion(columnas, fila, col, byte_objetivo, posicion_interna, bits_disponibles);

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

void escribirFicha(unsigned char* tablero, int columnas, int fila, int col, int nueva_ficha) {

    // 1. Declaramos las variables vacías
    int byte_objetivo = 0;
    int posicion_interna = 0;
    int bits_disponibles = 0;

    // 2. Usamos nuestra función matemática reciclada
    calcularUbicacion(columnas, fila, col, byte_objetivo, posicion_interna, bits_disponibles);

    // [Debugger] Supongamos que queremos meter el 5 (101 en binario).
    // [Debugger] Estado: nueva_ficha = 5, bits_disponibles = 2, posicion_interna = 6.

    // -----------------------------------------------------------------
    // LA ENCRUCIJADA DE LA ESCRITURA
    // -----------------------------------------------------------------

    if (bits_disponibles >= 3) {
        // [Camino A] La ficha cabe completa.

        // DEMOLICIÓN: Creamos el hueco de ceros.
        int mascara_demolicion = ~(7 << posicion_interna);
        tablero[byte_objetivo] = tablero[byte_objetivo] & mascara_demolicion;

        // INSERCIÓN: Metemos la ficha nueva en el hueco.
        tablero[byte_objetivo] = tablero[byte_objetivo] | (nueva_ficha << posicion_interna);

    } else {
        // [Camino B] La ficha no cabe (Ej: solo quedan 2 asientos). Toca partirla.

        // --- PARTE 1: Vagón actual ---

        // [Debugger] 1. DEMOLICIÓN PARTE 1: Limpiamos los 2 asientos que quedan.
        int mascara_limpieza1 = ~(((1 << bits_disponibles) - 1) << posicion_interna);
        tablero[byte_objetivo] = tablero[byte_objetivo] & mascara_limpieza1;

        // [Debugger] 2. INSERCIÓN PARTE 1: Cortamos el pedazo de la ficha que sí cabe (el '01' del '101').
        int pedazo1 = nueva_ficha & ((1 << bits_disponibles) - 1);
        tablero[byte_objetivo] = tablero[byte_objetivo] | (pedazo1 << posicion_interna);


        // --- PARTE 2: Siguiente vagón ---

        int bits_faltantes = 3 - bits_disponibles;
        // [Debugger] bits_faltantes = 1. (Nos falta acomodar 1 persona).

        // [Debugger] 3. DEMOLICIÓN PARTE 2: Limpiamos el asiento 0 del siguiente byte.
        int mascara_limpieza2 = ~((1 << bits_faltantes) - 1);
        tablero[byte_objetivo + 1] = tablero[byte_objetivo + 1] & mascara_limpieza2;

        // [Debugger] 4. INSERCIÓN PARTE 2: Sacamos el pedazo restante de la ficha (el '1' del '101').
        int pedazo2 = nueva_ficha >> bits_disponibles;
        tablero[byte_objetivo + 1] = tablero[byte_objetivo + 1] | pedazo2;
    }
}