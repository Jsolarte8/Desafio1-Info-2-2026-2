#ifndef ABSTRACCIONDEMEMORIA_H
#define ABSTRACCIONDEMEMORIA_H

const int FICHA_VACIA = 6;

void calcularUbicacion(int indice, int& byte_objetivo, int& posicion_interna, int& bits_disponibles);
int leerFichaIndice(const unsigned char* tablero, int indice);
void escribirFichaIndice(unsigned char* tablero, int indice, int nueva_ficha);

int leerFicha(const unsigned char* tablero, int columnas, int fila, int col);
void escribirFicha(unsigned char* tablero, int columnas, int fila, int col, int nueva_ficha);

#endif
