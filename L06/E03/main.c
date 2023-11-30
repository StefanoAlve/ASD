#include "pg.h"
#define nomeFile "inventario.txt"
int main() {
    ptabInv inventario;
    inventario = leggiInventario(nomeFile);

    return 0;
}
