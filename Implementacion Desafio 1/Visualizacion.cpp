#include "Visualizacion.h"
#include "AbstraccionDeMemoria.h"
#include "LogicaTablero.h"

#include <iostream>

using namespace std;

static char simboloFicha(int ficha) {
    switch (ficha) {
    case 0: return 'A';
    case 1: return 'B';
    case 2: return 'C';
    case 3: return 'D';
    case 4: return 'E';
    case 5: return 'F';
    case FICHA_VACIA: return '.';
    default: return '?';
    }
}

void mostrarTableroFichas(const unsigned char* tablero, int filas, int columnas) {

    cout << "\nTABLERO DE FICHAS\n\n";

    cout << "   ";
    for (int col = 0; col < columnas; ++col) {
        cout << col << ' ';
    }
    cout << '\n';

    for (int fila = 0; fila < filas; ++fila) {
        cout << fila << ": ";
        for (int col = 0; col < columnas; ++col) {
            int valorFicha = leerFicha(tablero, columnas, fila, col);
            cout << simboloFicha(valorFicha) << ' ';
        }
        cout << '\n';
    }
}

void mostrarTableroBinario(const unsigned char* tablero, int filas, int columnas) {

    cout << "\nTABLERO EN CODIGOS DE 3 BITS\n\n";

    int totalPosiciones = filas * columnas;

    for (int indice = 0; indice < totalPosiciones; ++indice) {

        int valorFicha = leerFichaIndice(tablero, indice);

        cout << ((valorFicha >> 2) & 1)
             << ((valorFicha >> 1) & 1)
             << (valorFicha & 1)
             << ' ';

        if ((indice + 1) % columnas == 0) {
            cout << '\n';
        }
    }
}

void mostrarMemoriaFisica(const unsigned char* tablero, int filas, int columnas) {

    int bytesOcupados = bytesNecesariosTablero(filas, columnas);

    cout << "\nMEMORIA FISICA (bit 7 -> bit 0)\n\n";

    for (int i = 0; i < bytesOcupados; ++i) {
        cout << "Byte " << i << ": ";
        for (int bit = 7; bit >= 0; --bit) {
            cout << ((tablero[i] >> bit) & 1);
        }
        cout << '\n';
    }
}

void mostrarEstadisticas(
    int filas,
    int columnas,
    int eliminacionesUsuario,
    int fichasEliminadasTotal,
    int combinacionesTotales,
    int cascadasEnEstaJugada,
    int puntuacion)
{
    cout << "\n=== ESTADO DEL JUEGO ===\n";
    cout << "Dimensiones actuales:       " << filas << " x " << columnas << "\n";
    cout << "Eliminaciones del usuario:  " << eliminacionesUsuario << "\n";
    cout << "Fichas eliminadas en total: " << fichasEliminadasTotal << "\n";
    cout << "Combinaciones detectadas:   " << combinacionesTotales << "\n";
    cout << "Cascadas en esta jugada:    " << cascadasEnEstaJugada << "\n";
    cout << "Puntuacion:                 " << puntuacion << "\n";
}
