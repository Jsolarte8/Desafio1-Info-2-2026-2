#include "Partida.h"
#include "LogicaTablero.h"
#include "Combinaciones.h"
#include "Visualizacion.h"
#include "Juego.h"
#include "estructuraTablero.h"

#include <iostream>
using namespace std;

static int pedirDimension(const char* mensaje) {
    int valor = 0;
    do {
        cout << mensaje;
        cin >> valor;
        if (valor <= 0) {
            cout << "Debe ser un numero positivo.\n";
        }
    } while (valor <= 0);
    return valor;
}

static void mostrarMenu() {
    cout << "\n=========================\n";
    cout << "      SWEET CRUSH\n";
    cout << "=========================\n";
    cout << "1. Eliminar una ficha\n";
    cout << "2. Mostrar tablero\n";
    cout << "3. Agregar fila\n";
    cout << "4. Eliminar fila\n";
    cout << "5. Agregar columna\n";
    cout << "6. Eliminar columna\n";
    cout << "0. Salir\n";
    cout << "Opcion: ";
}

static void mostrarEstadoCompleto(
    const unsigned char* tablero,
    int filas, int columnas,
    int eliminaciones_usuario,
    int fichas_eliminadas_total,
    int combinaciones_totales,
    int cascadas_actuales,
    int cascadas_acumuladas_totales)
{
    mostrarTableroFichas(tablero, filas, columnas);
    //mostrarTableroBinario(tablero, filas, columnas);// //<--------
    //mostrarMemoriaFisica(tablero, filas, columnas);//

    int puntuacion = fichas_eliminadas_total    * 10
                     + combinaciones_totales       * 30
                     + cascadas_acumuladas_totales * 50;

    mostrarEstadisticas(filas, columnas, eliminaciones_usuario,
                        fichas_eliminadas_total, combinaciones_totales,
                        cascadas_actuales, puntuacion);
}

static void renovarMascaraYCascadas(
    unsigned char*  tablero,
    unsigned char*& mascara,
    int  filas, int  columnas,
    int& fichas_eliminadas_total,
    int& combinaciones_totales,
    int& cascadas_actuales,
    int& cascadas_acumuladas_totales)
{
    liberarMascaraEliminacion(mascara);
    mascara = crearMascaraEliminacion(filas, columnas);

    cascadas_actuales = procesarCascadas(tablero, filas, columnas, mascara,
                                         fichas_eliminadas_total,
                                         combinaciones_totales);
    cascadas_acumuladas_totales += cascadas_actuales;
}

void ejecutarPartida() {

    int filas    = pedirDimension("Filas del tablero: ");
    int columnas = pedirDimension("Columnas del tablero: ");

    unsigned char* tablero = crearTablero(filas, columnas);
    unsigned char* mascara = crearMascaraEliminacion(filas, columnas);

    int fichasDescartadasAlInicializar        = 0;
    int combinacionesDescartadasAlInicializar = 0;
    procesarCascadas(tablero, filas, columnas, mascara,
                     fichasDescartadasAlInicializar,
                     combinacionesDescartadasAlInicializar);

    int eliminaciones_usuario       = 0;
    int fichas_eliminadas_total     = 0;
    int combinaciones_totales       = 0;
    int cascadas_actuales           = 0;
    int cascadas_acumuladas_totales = 0;

    mostrarEstadoCompleto(tablero, filas, columnas,
                          eliminaciones_usuario, fichas_eliminadas_total,
                          combinaciones_totales, cascadas_actuales,
                          cascadas_acumuladas_totales);

    int opcion = -1;

    while (opcion != 0) {

        mostrarMenu();
        cin >> opcion;

        if (opcion == 1) {

            int filaSeleccionada    = 0;
            int columnaSeleccionada = 0;
            cout << "Fila: ";
            cin >> filaSeleccionada;
            cout << "Columna: ";
            cin >> columnaSeleccionada;

            if (!eliminarFicha(tablero, filas, columnas, filaSeleccionada, columnaSeleccionada)) {
                cout << "Coordenada invalida.\n";
                continue;
            }

            eliminaciones_usuario++;
            fichas_eliminadas_total++;

            aplicarGravedad(tablero, filas, columnas);
            rellenarVaciosSuperiores(tablero, filas, columnas);

            cascadas_actuales = procesarCascadas(tablero, filas, columnas, mascara,
                                                 fichas_eliminadas_total,
                                                 combinaciones_totales);
            cascadas_acumuladas_totales += cascadas_actuales;

            mostrarEstadoCompleto(tablero, filas, columnas,
                                  eliminaciones_usuario, fichas_eliminadas_total,
                                  combinaciones_totales, cascadas_actuales,
                                  cascadas_acumuladas_totales);
        }

        else if (opcion == 2) {

            mostrarEstadoCompleto(tablero, filas, columnas,
                                  eliminaciones_usuario, fichas_eliminadas_total,
                                  combinaciones_totales, cascadas_actuales,
                                  cascadas_acumuladas_totales);
        }

        else if (opcion == 3) {

            int posicionNuevaFila = 0;
            cout << "Posicion para la nueva fila (0 a " << filas << "): ";
            cin >> posicionNuevaFila;

            if (posicionNuevaFila < 0 || posicionNuevaFila > filas) {
                cout << "Posicion invalida.\n";
                continue;
            }

            tablero = agregarFila(tablero, filas, columnas, posicionNuevaFila);
            renovarMascaraYCascadas(tablero, mascara, filas, columnas,
                                    fichas_eliminadas_total, combinaciones_totales,
                                    cascadas_actuales, cascadas_acumuladas_totales);
            mostrarEstadoCompleto(tablero, filas, columnas,
                                  eliminaciones_usuario, fichas_eliminadas_total,
                                  combinaciones_totales, cascadas_actuales,
                                  cascadas_acumuladas_totales);
        }

        else if (opcion == 4) {

            if (filas <= 1) {
                cout << "No se puede eliminar la unica fila restante.\n";
                continue;
            }

            int posicionFilaAEliminar = 0;
            cout << "Fila a eliminar (0 a " << filas - 1 << "): ";
            cin >> posicionFilaAEliminar;

            if (posicionFilaAEliminar < 0 || posicionFilaAEliminar >= filas) {
                cout << "Posicion invalida.\n";
                continue;
            }

            tablero = eliminarFila(tablero, filas, columnas, posicionFilaAEliminar);
            renovarMascaraYCascadas(tablero, mascara, filas, columnas,
                                    fichas_eliminadas_total, combinaciones_totales,
                                    cascadas_actuales, cascadas_acumuladas_totales);
            mostrarEstadoCompleto(tablero, filas, columnas,
                                  eliminaciones_usuario, fichas_eliminadas_total,
                                  combinaciones_totales, cascadas_actuales,
                                  cascadas_acumuladas_totales);
        }

        else if (opcion == 5) {

            int posicionNuevaColumna = 0;
            cout << "Posicion para la nueva columna (0 a " << columnas << "): ";
            cin >> posicionNuevaColumna;

            if (posicionNuevaColumna < 0 || posicionNuevaColumna > columnas) {
                cout << "Posicion invalida.\n";
                continue;
            }

            tablero = agregarColumna(tablero, filas, columnas, posicionNuevaColumna);
            renovarMascaraYCascadas(tablero, mascara, filas, columnas,
                                    fichas_eliminadas_total, combinaciones_totales,
                                    cascadas_actuales, cascadas_acumuladas_totales);
            mostrarEstadoCompleto(tablero, filas, columnas,
                                  eliminaciones_usuario, fichas_eliminadas_total,
                                  combinaciones_totales, cascadas_actuales,
                                  cascadas_acumuladas_totales);
        }

        else if (opcion == 6) {

            if (columnas <= 1) {
                cout << "No se puede eliminar la unica columna restante.\n";
                continue;
            }

            int posicionColumnaAEliminar = 0;
            cout << "Columna a eliminar (0 a " << columnas - 1 << "): ";
            cin >> posicionColumnaAEliminar;

            if (posicionColumnaAEliminar < 0 || posicionColumnaAEliminar >= columnas) {
                cout << "Posicion invalida.\n";
                continue;
            }

            tablero = eliminarColumna(tablero, filas, columnas, posicionColumnaAEliminar);
            renovarMascaraYCascadas(tablero, mascara, filas, columnas,
                                    fichas_eliminadas_total, combinaciones_totales,
                                    cascadas_actuales, cascadas_acumuladas_totales);
            mostrarEstadoCompleto(tablero, filas, columnas,
                                  eliminaciones_usuario, fichas_eliminadas_total,
                                  combinaciones_totales, cascadas_actuales,
                                  cascadas_acumuladas_totales);
        }

        else if (opcion != 0) {
            cout << "Opcion invalida.\n";
        }
    }

    liberarMascaraEliminacion(mascara);
    mascara = nullptr;

    liberarTablero(tablero);
    tablero = nullptr;
}