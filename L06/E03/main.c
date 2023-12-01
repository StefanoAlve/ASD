#include "inventario.h"

int main() {
    oggetti_s *oggetti;
    char nomeFile[maxL] = "inventario.txt";
    int numOggetti = 0;

    oggetti = caricaOggetti(nomeFile, &numOggetti);
    stampaOggetti(oggetti, numOggetti);
    deallocaOggetti(oggetti);

    return 0;
}
