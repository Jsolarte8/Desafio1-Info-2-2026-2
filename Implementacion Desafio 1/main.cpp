#include <iostream>
#include <cstdlib>
#include <ctime>
#include "logicaTablero.h"

using namespace std;

int main() {
    // Semilla para que los números aleatorios cambien en cada ejecución
    srand(time(0));

    int filas = 4;
    int columnas = 4;

    cout << "Creando tablero de " << filas << "x" << columnas << "..." << endl;
    unsigned char* miTablero = crearTablero(filas, columnas);

    cout << "Tablero creado exitosamente en memoria dinamica." << endl;

    // Liberación de memoria al finalizar
    liberarTablero(miTablero);
    miTablero = nullptr;

    return 0;
}
