#ifndef VISUALIZACION_H
#define VISUALIZACION_H

void mostrarTableroFichas(const unsigned char* tablero, int filas, int columnas);
void mostrarTableroBinario(const unsigned char* tablero, int filas, int columnas);
void mostrarMemoriaFisica(const unsigned char* tablero, int filas, int columnas);

void mostrarEstadisticas(
    int filas,
    int columnas,
    int eliminacionesUsuario,
    int fichasEliminadasTotal,
    int combinacionesTotales,
    int cascadasEnEstaJugada,
    int puntuacion
    );

#endif
