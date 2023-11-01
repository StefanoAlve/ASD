#include <stdio.h>
#include <stdlib.h>

int **malloc2dR(char *nomeFile, int *nr, int *nc);

void contaDimensione(int *nr, int *nc, int *nBianchi, int *nNeri);

void separa(int **mat, int *nr, int *nc, int **vB, int **vN, int nBianchi, int nNeri);

void stampa_vettori(int *vBianchi, int *vNeri, int nBianchi, int nNeri);

void free_mat2dR(int **mat, int *nr);


int main() {
    int **mat = NULL, nr, nc, *vB = NULL, *vN = NULL, dim, nBianchi, nNeri;
    char nomeFile[30];
    printf("\nInserire il nome del file da aprire: ");
    scanf("%s", nomeFile);
    mat = malloc2dR(nomeFile, &nr, &nc);//uso passaggio di nr e nc by reference
    printf("\nSeparando i contenuti delle celle..");
    contaDimensione(&nr, &nr, &nBianchi, &nNeri);//conto se matrice ha dimensione nr*nc pari o dispari
    separa(mat, &nr, &nc, &vB, &vN, nBianchi, nNeri);//chiamo funzione di separazione
    stampa_vettori(vB, vN, nBianchi, nNeri);//chiamo funzione di stampa
    free_mat2dR(mat, &nr);
    free(vB);//libero i vettori vB e vN
    free(vN);
    return 0;
}

int **malloc2dR(char *nomeFile, int *nr, int *nc) {
    int **mat;//vettore di puntatori
    int i, j;
    FILE *fp;
    if ((fp = fopen(nomeFile, "r")) == NULL) {
        printf("\nErrore. Impossibile aprire il file");
        exit(1);
    }
    printf("\nFile aperto.");
    fscanf(fp, "%d %d", nr, nc);//leggo prima riga in accordo con specifiche per trovare dimensioni matrice
    printf("\nLeggendo ed allocando da %s una matrice di %d righe e %d colonne.\n\n", nomeFile, *nr, *nc);
    mat = (int **) malloc((*nr) * (sizeof(int *)));//provo ad allocare vettore di puntatori
    if (mat == NULL) exit(1);
    for (i = 0; i < (*nr); i++) {
        mat[i] = (int *) malloc((*nc) * sizeof(int *));//alloco ogni puntatore per il numero di colonne
        if (mat[i] == NULL) exit(3);
    }
    for (i = 0; i < (*nr); i++) {
        for (j = 0; j < (*nc); j++) {
            fscanf(fp, "%d", &mat[i][j]);
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
    return mat;
}

void separa(int **mat, int *nr, int *nc, int **vB, int **vN, int nBianchi, int nNeri) {
    int i = 0, j = 0, num_neri = 0, num_bianchi = 0;
    *vB = (int *) malloc(nBianchi * sizeof(int *));
    *vN = (int *) malloc(nNeri * sizeof(int *));
    if ((*vB) == NULL || (*vN) == NULL) {
        printf("\nImpossibile allocare i due vettori dinamicamente.");
        exit(4);
    }
    for (i = 0; i < (*nr); i++) {
        for (j = 0; j < (*nc); j++) {
            if ((i + j) % 2 == 0) {
                (*vB)[num_bianchi] = mat[i][j];
                num_bianchi++;
            } else {
                (*vN)[num_neri] = mat[i][j];
                num_neri++;
            }
        }
    }
}

void stampa_vettori(int *vBianchi, int *vNeri, int nBianchi, int nNeri) {
    printf("\nIl vettore delle caselle bianche contiene:\n");
    for (int i = 0; i < nBianchi; i++) {
        printf("%d ", vBianchi[i]);
    }
    printf("\nIl vettore delle caselle nere contiene:\n");
    for (int j = 0; j < nNeri; j++) {
        printf("%d ", vNeri[j]);
    }
}

void contaDimensione(int *nr, int *nc, int *nBianchi, int *nNeri) {
    int dim;
    dim = (*nr) * (*nc);
    if (dim % 2 == 0) {
        *nBianchi = dim / 2;
        *nNeri = dim / 2;
    } else {
        *nBianchi = (dim / 2) + 1;
        *nNeri = (dim - *nBianchi);
    }
}

void free_mat2dR(int **mat, int *nr) {
    for (int i = 0; i < (*nr); i++) {
        free(mat[i]);
    }
    free(mat);
}