#include "Combinaciones.h"
#include "AbstraccionDeMemoria.h"
#include "LogicaTablero.h"
#include "Juego.h"

static int bytesNecesariosMascara(int filas, int columnas) {
    int total_posiciones = filas * columnas;
    return (total_posiciones + 7) >> 3;
}

static void marcarIndice(unsigned char* mascara, int indice) {
    int byte = indice >> 3;
    int bit  = indice & 7;
    mascara[byte] |= static_cast<unsigned char>(1 << bit);
}

static bool indiceMarcado(const unsigned char* mascara, int indice) {
    int byte = indice >> 3;
    int bit  = indice & 7;
    return (mascara[byte] & static_cast<unsigned char>(1 << bit)) != 0;
}

unsigned char* crearMascaraEliminacion(int filas, int columnas) {
    int bytes = bytesNecesariosMascara(filas, columnas);
    unsigned char* mascara = new unsigned char[bytes];
    for (int i = 0; i < bytes; ++i) {
        mascara[i] = 0;
    }
    return mascara;
}

void liberarMascaraEliminacion(unsigned char* mascara) {
    delete[] mascara;
}

void limpiarMascaraEliminacion(unsigned char* mascara, int filas, int columnas) {
    int bytes = bytesNecesariosMascara(filas, columnas);
    for (int i = 0; i < bytes; ++i) {
        mascara[i] = 0;
    }
}

static int buscarHorizontales(const unsigned char* tablero, int filas, int columnas, unsigned char* mascara) {

    int combinaciones = 0;

    for (int fila = 0; fila < filas; ++fila) {

        int indiceBaseDeEstaFila = fila * columnas;
        int valorAnterior        = leerFichaIndice(tablero, indiceBaseDeEstaFila);
        int inicioSecuencia      = 0;
        int longitudSecuencia    = 1;

        for (int col = 1; col <= columnas; ++col) {

            int valorActual = -1;
            if (col < columnas) {
                valorActual = leerFichaIndice(tablero, indiceBaseDeEstaFila + col);
            }

            if (col < columnas && valorActual == valorAnterior && valorAnterior != FICHA_VACIA) {
                ++longitudSecuencia;
            } else {
                if (valorAnterior != FICHA_VACIA && longitudSecuencia >= 3) {
                    ++combinaciones;
                    for (int k = inicioSecuencia; k < inicioSecuencia + longitudSecuencia; ++k) {
                        marcarIndice(mascara, indiceBaseDeEstaFila + k);
                    }
                }
                inicioSecuencia   = col;
                longitudSecuencia = 1;
                valorAnterior     = valorActual;
            }
        }
    }

    return combinaciones;
}

static int buscarVerticales(const unsigned char* tablero, int filas, int columnas, unsigned char* mascara) {

    int combinaciones = 0;

    for (int col = 0; col < columnas; ++col) {

        int valorAnterior     = leerFichaIndice(tablero, col);
        int inicioFila        = 0;
        int longitudSecuencia = 1;

        for (int fila = 1; fila <= filas; ++fila) {

            int valorActual = -1;
            if (fila < filas) {
                valorActual = leerFichaIndice(tablero, fila * columnas + col);
            }

            if (fila < filas && valorActual == valorAnterior && valorAnterior != FICHA_VACIA) {
                ++longitudSecuencia;
            } else {
                if (valorAnterior != FICHA_VACIA && longitudSecuencia >= 3) {
                    ++combinaciones;
                    for (int k = 0; k < longitudSecuencia; ++k) {
                        marcarIndice(mascara, (inicioFila + k) * columnas + col);
                    }
                }
                inicioFila        = fila;
                longitudSecuencia = 1;
                valorAnterior     = valorActual;
            }
        }
    }

    return combinaciones;
}

int detectarCombinaciones(const unsigned char* tablero, int filas, int columnas, unsigned char* mascara) {

    limpiarMascaraEliminacion(mascara, filas, columnas);

    int horizontales = buscarHorizontales(tablero, filas, columnas, mascara);
    int verticales   = buscarVerticales(tablero, filas, columnas, mascara);

    return horizontales + verticales;
}

int eliminarMarcadas(unsigned char* tablero, int filas, int columnas, const unsigned char* mascara) {

    int totalPosiciones = filas * columnas;
    int eliminadas      = 0;

    for (int indice = 0; indice < totalPosiciones; ++indice) {
        if (indiceMarcado(mascara, indice)) {
            escribirFichaIndice(tablero, indice, FICHA_VACIA);
            ++eliminadas;
        }
    }

    return eliminadas;
}

int procesarCascadas(unsigned char* tablero, int filas, int columnas, unsigned char* mascara,
                     int& fichas_eliminadas_total, int& combinaciones_totales) {

    int cascadas = 0;

    while (true) {

        int combinacionesEnEstaRonda = detectarCombinaciones(tablero, filas, columnas, mascara);

        if (combinacionesEnEstaRonda == 0) {
            break;
        }

        int fichasEliminadasEnEstaRonda = eliminarMarcadas(tablero, filas, columnas, mascara);

        fichas_eliminadas_total += fichasEliminadasEnEstaRonda;
        combinaciones_totales   += combinacionesEnEstaRonda;

        ++cascadas;

        aplicarGravedad(tablero, filas, columnas);
        rellenarVaciosSuperiores(tablero, filas, columnas);
    }

    return cascadas;
}