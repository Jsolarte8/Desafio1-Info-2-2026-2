#ifndef COMBINACIONES_H
#define COMBINACIONES_H


unsigned char* crearMascaraEliminacion(
    int filas,
    int columnas
    );


void liberarMascaraEliminacion(
    unsigned char* mascara
    );


void limpiarMascaraEliminacion(
    unsigned char* mascara,
    int filas,
    int columnas
    );


int detectarCombinaciones(
    const unsigned char* tablero,
    int filas,
    int columnas,
    unsigned char* mascara
    );


int eliminarMarcadas(
    unsigned char* tablero,
    int filas,
    int columnas,
    const unsigned char* mascara
    );


int procesarCascadas(
    unsigned char* tablero,
    int filas,
    int columnas,
    unsigned char* mascara,
    int& fichas_eliminadas_total,
    int& combinaciones_totales
    );


#endif