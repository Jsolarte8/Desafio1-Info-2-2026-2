#ifndef LOGICATABLERO_H
#define LOGICATABLERO_H


// 000 a 101 = seis fichas normales
// 110 = vacio
// 111 = reservado

const int FICHA_VACIA = 6;
const int FICHA_RESERVADA = 7;


int generarFichaAleatoria();


unsigned char* crearTablero(
    int filas,
    int columnas
    );


void liberarTablero(
    unsigned char* tablero
    );


// Fase 3

bool eliminarFicha(
    unsigned char* tablero,
    int filas,
    int columnas,
    int fila,
    int col
    );


void aplicarGravedad(
    unsigned char* tablero,
    int filas,
    int columnas
    );


void rellenarVaciosSuperiores(
    unsigned char* tablero,
    int filas,
    int columnas
    );


#endif