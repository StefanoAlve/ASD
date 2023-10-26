#include <stdio.h>
#include <stdlib.h>
#define MAXL 30

int  **malloc2dR(char nomeFile[], int *nr, int *nc);
void dealloca2d(int **matrice, int nr);
void separa(int **matrice, int nr, int nc, int **vBianchi, int **vNeri, int *nb, int *nn);

int main(void) {
    //Inizializzazione variabili
    char nomeFile[MAXL];
    int **matrice, nr, nc, *vBianchi = NULL, *vNeri = NULL, nb=0, nn=0;
    //Corpo Programma
    printf("Inserisci il nome del file:");
    scanf("%s", nomeFile);
    matrice = malloc2dR(nomeFile, &nr, &nc);
    for(int i = 0; i<nr; i++){
        for(int j = 0; j<nc; j++){
            printf("%d ", (matrice[i][j]));
        }
        printf("\n");
    }
    separa(matrice, nr, nc, &vBianchi, &vNeri, &nb, &nn);
    printf("\nLe caselle nere sono:\n\t");
    for(int i = 0; i < nn; i++){
        printf("%d ",vNeri[i]);
    }
    printf("\nLe caselle bianche sono:\n\t");
    for(int i = 0; i < nb; i++){
        printf("%d ",vBianchi[i]);
    }
    printf("\n");

    //Deallocazione
    dealloca2d(matrice, nr);
    free(vNeri);
    free(vBianchi);
    return 0;
}

int **malloc2dR(char nomeFile[], int *nr, int *nc){
    //Inizializzazione variabili
    FILE* fp;
    int **matrice;
    int i, j;

    //Lettura file
    fp = fopen(nomeFile, "r");
    if (fp == NULL) {
        printf("Errore nell'apertura del file\n");
        exit(1);
    }
    if (fscanf(fp, "%d %d", nr, nc) != 2) {
        printf("Errore nella lettura di nr e nc\n");
        exit(1);
    }

    //Allocazione dinamica matrice
    //Grazie a questo tipo di allocazione posso utilizzare la notazione matriciale quando devo prendere un elemento della "matrice" (matrice[i][j])
    matrice = (int **)malloc((*nr)*sizeof(int *));
    if(matrice == NULL){
        printf("Errore nell'allocazione delle righe\n");
        exit(1);
    }
    for(i=0; i<(*nr); i++){
        matrice[i] = (int *)malloc((*nc)*sizeof(int));
        if(matrice[i] == NULL){
            printf("Errore nell'allocazione delle colonne\n");
            exit(1);
        }

        //Riempimento matrice
        for (j=0;j<(*nc);j++){
            fscanf(fp ,"%d", &(matrice[i][j]));
        }
    }

    //Chiusura file
    fclose(fp);

    return matrice;
}

void dealloca2d(int **matrice, int nr){
    for(int i = 0; i < nr; i++){
        free(matrice[i]);
    }
    free(matrice);
}

void separa(int **matrice, int nr, int nc, int **vBianchi, int **vNeri, int *pnb, int *pnn){
    //Inizializzazione variabili
    int dimensioneTot = nr*nc;
    int *pBianchi, *pNeri, nn = 0, nb = 0;

    //Allocazione dinamica vettori
    if((dimensioneTot)%2 == 0) {
        pBianchi = (int *) malloc((dimensioneTot/2)*sizeof(int));
        pNeri = (int *) malloc((dimensioneTot/2)*sizeof(int));
    }
    else{
        pBianchi = (int *) malloc((dimensioneTot/2-1)*sizeof(int));
        pNeri = (int *) malloc((dimensioneTot/2+1)*sizeof(int));
    }
    if(vBianchi == NULL || vNeri == NULL){
        printf("Errore nell'allocazione dei vettori\n");
        exit(1);
    }

    //Corpo funzione
    for(int i = 0; i<nr; i++){
        for(int j = 0; j<nc; j++){
            if (j % 2 == 0 && i % 2 == 0 || j % 2 != 0 && i % 2 != 0) { //se entrambi gli indici pari o entrambi dispari
                (pNeri)[nn++] = matrice[i][j];
            } else {
                (pBianchi)[nb++] = matrice[i][j];
            }
        }
    }

    //Ho utilizzato delle variabili temporanee per rendere più leggibile il programma, passo ai puntatori i nuovi indirizzi di memoria per il passaggio by pointer
    *pnb = nb;
    *pnn = nn;
    *vBianchi = pBianchi;
    *vNeri = pNeri;
}