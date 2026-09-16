#ifndef ABSTRACCIONDEMEMORIA_H
#define ABSTRACCIONDEMEMORIA_H

void calcularUbicacion(int columnas, int fila, int col, int& byte_objetivo, int& posicion_interna, int& bits_disponibles);
int leerFicha(unsigned char* tablero, int columnas, int fila, int col);
void escribirFicha(unsigned char* tablero, int columnas, int fila, int col, int nueva_ficha);

#endif
