#include <cstdlib>
#include <ctime>

#include "Partida.h"

int main() {
    srand(static_cast<unsigned int>(time(0)));
    ejecutarPartida();
    return 0;
}
