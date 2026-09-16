#include "combinaciones.h"
#include "abstraccionDeMemoria.h"
#include "logicaTablero.h"


//Mascara de eliminacion

static int bytesNecesariosMascara(
    int filas,
    int columnas)
{
    int total_posiciones =
        filas * columnas;

    /*
     * Solamente necesitamos 1 bit por posicion:
     *
     * 0 = conservar
     * 1 = eliminar
     */

    return (total_posiciones + 7) >> 3;
}


static void marcarIndice(
    unsigned char* mascara,
    int indice)
{
    // indice / 8
    int byte =
        indice >> 3;

    // indice % 8
    int bit =
        indice & 7;


    mascara[byte] |=
        static_cast<unsigned char>(
            1 << bit
            );
}


static bool indiceMarcado(
    const unsigned char* mascara,
    int indice)
{
    int byte =
        indice >> 3;

    int bit =
        indice & 7;


    return (
               mascara[byte]
               &
               static_cast<unsigned char>(
                   1 << bit
                   )
               ) != 0;
}


unsigned char* crearMascaraEliminacion(
    int filas,
    int columnas)
{
    int bytes =
        bytesNecesariosMascara(
            filas,
            columnas
            );


    unsigned char* mascara =
        new unsigned char[bytes];


    for (int i = 0;
         i < bytes;
         ++i)
    {
        mascara[i] = 0;
    }


    return mascara;
}


void liberarMascaraEliminacion(
    unsigned char* mascara)
{
    delete[] mascara;
}


void limpiarMascaraEliminacion(
    unsigned char* mascara,
    int filas,
    int columnas)
{
    int bytes =
        bytesNecesariosMascara(
            filas,
            columnas
            );


    for (int i = 0;
         i < bytes;
         ++i)
    {
        mascara[i] = 0;
    }
}


// Combinaciones Horizontales

static int buscarHorizontales(
    const unsigned char* tablero,
    int filas,
    int columnas,
    unsigned char* mascara)
{
    int combinaciones = 0;


    for (int fila = 0;
         fila < filas;
         ++fila)
    {
        if (columnas <= 0)
        {
            continue;
        }


        int base =
            fila * columnas;


        int valor_anterior =
            leerFichaIndice(
                tablero,
                base
                );


        int inicio = 0;
        int longitud = 1;


        /*
         * El <= columnas es intencional.
         *
         * Cuando col == columnas simulamos
         * un valor diferente para poder
         * procesar la ultima secuencia.
         */

        for (int col = 1;
             col <= columnas;
             ++col)
        {
            int valor_actual = -1;


            if (col < columnas)
            {
                valor_actual =
                    leerFichaIndice(
                        tablero,
                        base + col
                        );
            }


            if (
                col < columnas
                &&
                valor_actual == valor_anterior
                &&
                valor_anterior != FICHA_VACIA
                )
            {
                ++longitud;
            }
            else
            {
                /*
                 * Terminamos de recorrer
                 * una secuencia.
                 */

                if (
                    valor_anterior
                        != FICHA_VACIA
                    &&
                    longitud >= 3
                    )
                {
                    ++combinaciones;


                    /*
                     * Marcamos todas las posiciones,
                     * pero NO las eliminamos todavia.
                     */

                    for (
                        int k = inicio;
                        k < inicio + longitud;
                        ++k
                        )
                    {
                        marcarIndice(
                            mascara,
                            base + k
                            );
                    }
                }


                inicio = col;
                longitud = 1;
                valor_anterior =
                    valor_actual;
            }
        }
    }


    return combinaciones;
}


// Combinaciones Verticales

static int buscarVerticales(
    const unsigned char* tablero,
    int filas,
    int columnas,
    unsigned char* mascara)
{
    int combinaciones = 0;


    for (int col = 0;
         col < columnas;
         ++col)
    {
        if (filas <= 0)
        {
            continue;
        }


        int valor_anterior =
            leerFichaIndice(
                tablero,
                col
                );


        int inicio_fila = 0;
        int longitud = 1;


        for (int fila = 1;
             fila <= filas;
             ++fila)
        {
            int valor_actual = -1;


            if (fila < filas)
            {
                int indice =
                    fila * columnas
                    + col;


                valor_actual =
                    leerFichaIndice(
                        tablero,
                        indice
                        );
            }


            if (
                fila < filas
                &&
                valor_actual
                    == valor_anterior
                &&
                valor_anterior
                    != FICHA_VACIA
                )
            {
                ++longitud;
            }
            else
            {
                if (
                    valor_anterior
                        != FICHA_VACIA
                    &&
                    longitud >= 3
                    )
                {
                    ++combinaciones;


                    for (
                        int k = 0;
                        k < longitud;
                        ++k
                        )
                    {
                        int indice =
                            (inicio_fila + k)
                                * columnas
                            + col;


                        marcarIndice(
                            mascara,
                            indice
                            );
                    }
                }


                inicio_fila =
                    fila;

                longitud = 1;

                valor_anterior =
                    valor_actual;
            }
        }
    }


    return combinaciones;
}


// Detectar todas las combinaciones

int detectarCombinaciones(
    const unsigned char* tablero,
    int filas,
    int columnas,
    unsigned char* mascara)
{
    /*
     * Importante:
     *
     * Primero limpiamos la mascara.
     *
     * Luego buscamos horizontal y vertical
     * sobre EL MISMO tablero sin modificarlo.
     */

    limpiarMascaraEliminacion(
        mascara,
        filas,
        columnas
        );


    int horizontales =
        buscarHorizontales(
            tablero,
            filas,
            columnas,
            mascara
            );


    int verticales =
        buscarVerticales(
            tablero,
            filas,
            columnas,
            mascara
            );


    return horizontales
           + verticales;
}



// Eliminar todas las posiciones marcadas


int eliminarMarcadas(
    unsigned char* tablero,
    int filas,
    int columnas,
    const unsigned char* mascara)
{
    int total_posiciones =
        filas * columnas;


    int eliminadas = 0;


    for (
        int indice = 0;
        indice < total_posiciones;
        ++indice
        )
    {
        if (
            indiceMarcado(
                mascara,
                indice
                )
            )
        {
            escribirFichaIndice(
                tablero,
                indice,
                FICHA_VACIA
                );


            ++eliminadas;
        }
    }


    return eliminadas;
}


//Cascada

int procesarCascadas(
    unsigned char* tablero,
    int filas,
    int columnas,
    unsigned char* mascara,
    int& fichas_eliminadas_total,
    int& combinaciones_totales)
{
    int cascadas = 0;


    /*
     * Repetir hasta que el tablero
     * no tenga combinaciones.
     */

    while (true)
    {
        int combinaciones =
            detectarCombinaciones(
                tablero,
                filas,
                columnas,
                mascara
                );


        // Tablero estable.
        if (combinaciones == 0)
        {
            break;
        }


        int eliminadas =
            eliminarMarcadas(
                tablero,
                filas,
                columnas,
                mascara
                );


        fichas_eliminadas_total +=
            eliminadas;


        combinaciones_totales +=
            combinaciones;


        ++cascadas;


        // Las fichas restantes caen.
        aplicarGravedad(
            tablero,
            filas,
            columnas
            );


        // Se generan nuevas fichas.
        rellenarVaciosSuperiores(
            tablero,
            filas,
            columnas
            );


        /*
         * El while vuelve al comienzo
         * y verifica si las fichas nuevas
         * generaron otra combinacion.
         */
    }


    return cascadas;
}