#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXL 50

typedef struct {
    char pietra[MAXL];
    int numero;
}stones;

int leggiFile(char nomeFile[MAXL], stones **pietre);

int main() {
    char nomeFile[MAXL];
    stones *pietre;
    int nr;

    printf("inserire nome file: \n");
    scanf("%s", nomeFile);

    nr = leggiFile(nomeFile, &pietre);

    return 0;
}


int leggiFile(char nomeFile[MAXL], stones **pietre) {

}