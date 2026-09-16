#include <iostream>
#include <cstdlib>
#include <ctime>

#include "logicaTablero.h"
#include "combinaciones.h"
#include "visualizacion.h"

using namespace std;


int main()
{
    // Semilla aleatoria.
    srand(
        static_cast<unsigned int>(
            time(0)
            )
        );


    int filas = 0;
    int columnas = 0;


    // Pedir dimenciones

    do
    {
        cout
            << "Filas del tablero: ";

        cin >> filas;


        cout
            << "Columnas del tablero: ";

        cin >> columnas;


        if (
            filas <= 0
            ||
            columnas <= 0
            )
        {
            cout
                << "Las dimensiones deben "
                   "ser positivas.\n";
        }

    } while (
        filas <= 0
        ||
        columnas <= 0
        );


    // Crear Tablero

    unsigned char* tablero =
        crearTablero(
            filas,
            columnas
            );


    // Crear Mascara para combinaciones

    unsigned char* mascara =
        crearMascaraEliminacion(
            filas,
            columnas
            );


    /*
     * El tablero inicial es aleatorio.
     *
     * Puede ocurrir que nazca con una
     * combinacion de 3 o mas fichas.
     *
     * Antes de iniciar la partida
     * estabilizamos el tablero.
     *
     * Estas eliminaciones NO cuentan
     * dentro de las estadisticas del jugador.
     */

    int fichas_iniciales_descartadas = 0;
    int combinaciones_iniciales_descartadas = 0;


    procesarCascadas(
        tablero,
        filas,
        columnas,
        mascara,
        fichas_iniciales_descartadas,
        combinaciones_iniciales_descartadas
        );


    // Estadisticas

    int eliminaciones_usuario = 0;

    int fichas_eliminadas_total = 0;

    int combinaciones_totales = 0;

    int cascadas_actuales = 0;


    // Mostrar Tablero Inicial

    mostrarTableroFichas(
        tablero,
        filas,
        columnas
        );


    mostrarTableroBinario(
        tablero,
        filas,
        columnas
        );


    mostrarMemoriaFisica(
        tablero,
        filas,
        columnas
        );


    // Menu

    int opcion = -1;


    while (opcion != 0)
    {
        cout << "\n";

        cout
            << "=========================\n";

        cout
            << "      SWEET CRUSH\n";

        cout
            << "=========================\n";

        cout
            << "1. Eliminar una ficha\n";

        cout
            << "2. Mostrar tablero\n";

        cout
            << "0. Salir\n";

        cout
            << "Opcion: ";


        cin >> opcion;


        // Eliminar Ficha

        if (opcion == 1)
        {
            int fila = 0;
            int col = 0;


            cout
                << "Fila: ";

            cin >> fila;


            cout
                << "Columna: ";

            cin >> col;


            if (
                !eliminarFicha(
                    tablero,
                    filas,
                    columnas,
                    fila,
                    col
                    )
                )
            {
                cout
                    << "Coordenada invalida.\n";

                continue;
            }


            /*
             * Una ficha fue eliminada
             * directamente por el usuario.
             */

            ++eliminaciones_usuario;

            ++fichas_eliminadas_total;


            // Fase 3

            aplicarGravedad(
                tablero,
                filas,
                columnas
                );


            rellenarVaciosSuperiores(
                tablero,
                filas,
                columnas
                );


           // Fase 4

            cascadas_actuales =
                procesarCascadas(
                    tablero,
                    filas,
                    columnas,
                    mascara,
                    fichas_eliminadas_total,
                    combinaciones_totales
                    );


            // Mostrar Resultado

            mostrarTableroFichas(
                tablero,
                filas,
                columnas
                );


            mostrarTableroBinario(
                tablero,
                filas,
                columnas
                );


            mostrarMemoriaFisica(
                tablero,
                filas,
                columnas
                );


            // Estadisticas

            cout << "\n";

            cout
                << "Eliminaciones hechas "
                   "por el usuario: "
                << eliminaciones_usuario
                << '\n';


            cout
                << "Fichas eliminadas "
                   "en total: "
                << fichas_eliminadas_total
                << '\n';


            cout
                << "Combinaciones "
                   "detectadas: "
                << combinaciones_totales
                << '\n';


            cout
                << "Cascadas de esta "
                   "jugada: "
                << cascadas_actuales
                << '\n';
        }


       // Mostrar Tablero

        else if (opcion == 2)
        {
            mostrarTableroFichas(
                tablero,
                filas,
                columnas
                );


            mostrarTableroBinario(
                tablero,
                filas,
                columnas
                );


            mostrarMemoriaFisica(
                tablero,
                filas,
                columnas
                );
        }




        else if (opcion != 0)
        {
            cout
                << "Opcion invalida.\n";
        }
    }

    //Liberar Memoria

    liberarMascaraEliminacion(
        mascara
        );

    mascara = nullptr;


    liberarTablero(
        tablero
        );

    tablero = nullptr;


    return 0;
}