#include "visualizacion.h"
#include "abstraccionDeMemoria.h"
#include "logicaTablero.h"

#include <iostream>

using namespace std;


static char simboloFicha(
    int ficha)
{
    switch (ficha)
    {
    case 0:
        return 'A';

    case 1:
        return 'B';

    case 2:
        return 'C';

    case 3:
        return 'D';

    case 4:
        return 'E';

    case 5:
        return 'F';

    case FICHA_VACIA:
        return '.';

    default:
        return '?';
    }
}


void mostrarTableroFichas(
    const unsigned char* tablero,
    int filas,
    int columnas)
{
    cout << "\n";
    cout << "TABLERO DE FICHAS\n\n";


    cout << "   ";

    for (int col = 0;
         col < columnas;
         ++col)
    {
        cout << col << ' ';
    }

    cout << '\n';


    for (int fila = 0;
         fila < filas;
         ++fila)
    {
        cout << fila << ": ";


        for (int col = 0;
             col < columnas;
             ++col)
        {
            int ficha =
                leerFicha(
                    tablero,
                    columnas,
                    fila,
                    col
                    );


            cout
                << simboloFicha(ficha)
                << ' ';
        }


        cout << '\n';
    }
}


void mostrarTableroBinario(
    const unsigned char* tablero,
    int filas,
    int columnas)
{
    cout << "\n";
    cout << "TABLERO EN CODIGOS DE 3 BITS\n\n";


    int total_posiciones =
        filas * columnas;


    for (
        int indice = 0;
        indice < total_posiciones;
        ++indice
        )
    {
        int ficha =
            leerFichaIndice(
                tablero,
                indice
                );


        cout
            << ((ficha >> 2) & 1)
            << ((ficha >> 1) & 1)
            << (ficha & 1)
            << ' ';


        if (
            (indice + 1)
                % columnas
            == 0
            )
        {
            cout << '\n';
        }
    }
}


void mostrarMemoriaFisica(
    const unsigned char* tablero,
    int filas,
    int columnas)
{
    int bytes =
        bytesNecesariosTablero(
            filas,
            columnas
            );


    cout << "\n";
    cout << "MEMORIA FISICA "
            "(bit 7 -> bit 0)\n\n";


    for (
        int i = 0;
        i < bytes;
        ++i
        )
    {
        cout
            << "Byte "
            << i
            << ": ";


        for (
            int bit = 7;
            bit >= 0;
            --bit
            )
        {
            cout
                << (
                       (tablero[i] >> bit)
                       & 1
                       );
        }


        cout << '\n';
    }
}