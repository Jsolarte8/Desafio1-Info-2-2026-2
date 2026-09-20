#ifndef JUEGO_H
#define JUEGO_H

bool eliminarFicha(unsigned char* tablero, int filas, int columnas, int fila, int col);
void aplicarGravedad(unsigned char* tablero, int filas, int columnas);
void rellenarVaciosSuperiores(unsigned char* tablero, int filas, int columnas);

#endif
