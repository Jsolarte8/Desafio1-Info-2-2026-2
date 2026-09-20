#ifndef ESTRUCTURATABLERO_H
#define ESTRUCTURATABLERO_H

unsigned char* agregarFila(unsigned char* tableroActual, int& filas, int columnas, int posicionInsercion);
unsigned char* eliminarFila(unsigned char* tableroActual, int& filas, int columnas, int posicionEliminacion);
unsigned char* agregarColumna(unsigned char* tableroActual, int filas, int& columnas, int posicionInsercion);
unsigned char* eliminarColumna(unsigned char* tableroActual, int filas, int& columnas, int posicionEliminacion);

#endif