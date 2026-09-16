#ifndef ABSTRACCIONDEMEMORIA_H
#define ABSTRACCIONDEMEMORIA_H

int bytesNecesariosTablero(int filas, int columnas);

void calcularUbicacionIndice(
    int indice,
    int& byte_objetivo,
    int& posicion_interna,
    int& bits_disponibles
    );

void calcularUbicacion(
    int columnas,
    int fila,
    int col,
    int& byte_objetivo,
    int& posicion_interna,
    int& bits_disponibles
    );

int leerFichaIndice(
    const unsigned char* tablero,
    int indice
    );

int leerFicha(
    const unsigned char* tablero,
    int columnas,
    int fila,
    int col
    );

void escribirFichaIndice(
    unsigned char* tablero,
    int indice,
    int nueva_ficha
    );

void escribirFicha(
    unsigned char* tablero,
    int columnas,
    int fila,
    int col,
    int nueva_ficha
    );

#endif
