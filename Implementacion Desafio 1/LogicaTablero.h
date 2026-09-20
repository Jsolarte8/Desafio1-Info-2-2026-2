#ifndef LOGICATABLERO_H
#define LOGICATABLERO_H

int bytesNecesariosTablero(int filas, int columnas);
int generarFichaAleatoria();
unsigned char* crearTablero(int filas, int columnas);
void liberarTablero(unsigned char* tablero);

#endif
