#include "logicaTablero.h"
#include "abstraccionDeMemoria.h"

#include <cstdlib>
#include <climits>


int generarFichaAleatoria()
{

    unsigned long long rango =
        static_cast<unsigned long long>(RAND_MAX)
        + 1ULL;

    unsigned long long limite =
        rango - (rango % 6ULL);

    int valor = 0;

    do
    {
        valor = rand();

    } while (
        static_cast<unsigned long long>(valor)
        >= limite
        );

    return valor % 6;
}


unsigned char* crearTablero(
    int filas,
    int columnas)
{
    int bytes_necesarios =
        bytesNecesariosTablero(
            filas,
            columnas
            );

    unsigned char* tablero =
        new unsigned char[bytes_necesarios];


    for (int i = 0;
         i < bytes_necesarios;
         ++i)
    {
        tablero[i] = 0;
    }


    int total_posiciones =
        filas * columnas;


    for (int indice = 0;
         indice < total_posiciones;
         ++indice)
    {
        escribirFichaIndice(
            tablero,
            indice,
            generarFichaAleatoria()
            );
    }


    return tablero;
}


void liberarTablero(
    unsigned char* tablero)
{
    delete[] tablero;
}



// Fase 3


bool eliminarFicha(
    unsigned char* tablero,
    int filas,
    int columnas,
    int fila,
    int col)
{

    if (fila < 0 ||
        fila >= filas ||
        col < 0 ||
        col >= columnas)
    {
        return false;
    }


    escribirFicha(
        tablero,
        columnas,
        fila,
        col,
        FICHA_VACIA
        );


    return true;
}


void aplicarGravedad(
    unsigned char* tablero,
    int filas,
    int columnas)
{

    for (int col = 0;
         col < columnas;
         ++col)
    {
        int fila_escritura =
            filas - 1;


        // Buscar fichas de abajo hacia arriba
        for (int fila_lectura = filas - 1;
             fila_lectura >= 0;
             --fila_lectura)
        {
            int indice_lectura =
                fila_lectura * columnas
                + col;


            int ficha =
                leerFichaIndice(
                    tablero,
                    indice_lectura
                    );


            // Solo nos interesan fichas reales
            if (ficha != FICHA_VACIA)
            {
                /*
                 * Si ya esta donde debe estar,
                 * no hacemos una escritura
                 * innecesaria.
                 */

                if (fila_escritura
                    != fila_lectura)
                {
                    int indice_escritura =
                        fila_escritura
                            * columnas
                        + col;


                    escribirFichaIndice(
                        tablero,
                        indice_escritura,
                        ficha
                        );
                }


                --fila_escritura;
            }
        }


        /*
         * Todo lo que quede por encima de las
         * fichas compactadas debe quedar vacio.
         */

        while (fila_escritura >= 0)
        {
            int indice =
                fila_escritura
                    * columnas
                + col;


            escribirFichaIndice(
                tablero,
                indice,
                FICHA_VACIA
                );


            --fila_escritura;
        }
    }
}


void rellenarVaciosSuperiores(
    unsigned char* tablero,
    int filas,
    int columnas)
{
    /*
     * Despues de aplicar gravedad,
     * los vacios solamente pueden estar
     * agrupados en la parte superior.
     *
     * Por eso recorremos desde arriba
     * y detenemos el recorrido cuando
     * encontramos la primera ficha real.
     */


    for (int col = 0;
         col < columnas;
         ++col)
    {
        for (int fila = 0;
             fila < filas;
             ++fila)
        {
            int indice =
                fila * columnas
                + col;


            int ficha =
                leerFichaIndice(
                    tablero,
                    indice
                    );


            if (ficha != FICHA_VACIA)
            {
                break;
            }


            escribirFichaIndice(
                tablero,
                indice,
                generarFichaAleatoria()
                );
        }
    }
}