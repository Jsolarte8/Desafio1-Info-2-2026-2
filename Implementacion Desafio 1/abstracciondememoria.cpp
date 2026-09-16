#include "abstraccionDeMemoria.h"


int bytesNecesariosTablero(int filas, int columnas)
{
    int total_bits = filas * columnas * 3;

    // Dividir entre 8 redondeando hacia arriba.
    // Equivale a: (total_bits + 7) / 8
    return (total_bits + 7) >> 3;
}


void calcularUbicacionIndice(
    int indice,
    int& byte_objetivo,
    int& posicion_interna,
    int& bits_disponibles)
{
    int bit_inicial = indice * 3;

    // /8
    byte_objetivo = bit_inicial >> 3;

    // %8
    posicion_interna = bit_inicial & 7;

    bits_disponibles = 8 - posicion_interna;
}


void calcularUbicacion(
    int columnas,
    int fila,
    int col,
    int& byte_objetivo,
    int& posicion_interna,
    int& bits_disponibles)
{
    int indice = fila * columnas + col;

    calcularUbicacionIndice(
        indice,
        byte_objetivo,
        posicion_interna,
        bits_disponibles
        );
}


int leerFichaIndice(
    const unsigned char* tablero,
    int indice)
{
    int byte_objetivo = 0;
    int posicion_interna = 0;
    int bits_disponibles = 0;

    calcularUbicacionIndice(
        indice,
        byte_objetivo,
        posicion_interna,
        bits_disponibles
        );

    // Caso 1:
    // Los 3 bits caben en el mismo byte

    if (bits_disponibles >= 3)
    {
        int ficha =
            tablero[byte_objetivo] >> posicion_interna;

        return ficha & 7;
    }

    // Caso 2:
    // La ficha esta repartida entre dos bytes

    int mascara1 =
        (1 << bits_disponibles) - 1;

    int pedazo1 =
        (tablero[byte_objetivo] >> posicion_interna)
        & mascara1;

    int bits_faltantes =
        3 - bits_disponibles;

    int mascara2 =
        (1 << bits_faltantes) - 1;

    int pedazo2 =
        tablero[byte_objetivo + 1]
        & mascara2;

    int ficha_completa =
        (pedazo2 << bits_disponibles)
        | pedazo1;

    return ficha_completa;
}


int leerFicha(
    const unsigned char* tablero,
    int columnas,
    int fila,
    int col)
{
    int indice =
        fila * columnas + col;

    return leerFichaIndice(
        tablero,
        indice
        );
}


void escribirFichaIndice(
    unsigned char* tablero,
    int indice,
    int nueva_ficha)
{
    int byte_objetivo = 0;
    int posicion_interna = 0;
    int bits_disponibles = 0;

    // Garantiza que solamente usemos 3 bits

    nueva_ficha &= 7;

    calcularUbicacionIndice(
        indice,
        byte_objetivo,
        posicion_interna,
        bits_disponibles
        );

    // Caso 1:
    // La ficha cabe completamente en un byte

    if (bits_disponibles >= 3)
    {
        int mascara =
            7 << posicion_interna;

        // Apagamos los 3 bits anteriores.
        tablero[byte_objetivo] &=
            static_cast<unsigned char>(~mascara);

        // Escribimos los nuevos bits.
        tablero[byte_objetivo] |=
            static_cast<unsigned char>(
                nueva_ficha << posicion_interna
                );

        return;
    }

    // Caso 2:
    // La ficha esta dividida entre dos bytes

   // Primer Byte

    int mascara1 =
        ((1 << bits_disponibles) - 1)
        << posicion_interna;

    int pedazo1 =
        (nueva_ficha
         & ((1 << bits_disponibles) - 1))
        << posicion_interna;

    tablero[byte_objetivo] &=
        static_cast<unsigned char>(~mascara1);

    tablero[byte_objetivo] |=
        static_cast<unsigned char>(pedazo1);



    // Segundo Byte

    int bits_faltantes =
        3 - bits_disponibles;

    int mascara2 =
        (1 << bits_faltantes) - 1;

    int pedazo2 =
        (nueva_ficha >> bits_disponibles)
        & mascara2;

    tablero[byte_objetivo + 1] &=
        static_cast<unsigned char>(~mascara2);

    tablero[byte_objetivo + 1] |=
        static_cast<unsigned char>(pedazo2);
}


void escribirFicha(
    unsigned char* tablero,
    int columnas,
    int fila,
    int col,
    int nueva_ficha)
{
    int indice =
        fila * columnas + col;

    escribirFichaIndice(
        tablero,
        indice,
        nueva_ficha
        );
}