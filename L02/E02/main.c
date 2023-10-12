#include <stdio.h>
#include <stdlib.h>
#define MAXL 30

int  **malloc2dR(char nomeFile[], int *nr, int *nc);
void separa(int **pMatrice, int nr, int nc, int **vBianchi, int **vNeri, int *nb, int *nn);

int main(void) {
    //Inizializzazione variabili
    char nomeFile[MAXL];
    int **pMatrice, nr, nc, *vBianchi = NULL, *vNeri = NULL, nb=0, nn=0;

    //Corpo Programma
    printf("Inserisci il nome del file:");
    scanf("%s", nomeFile);
    pMatrice = malloc2dR(nomeFile, &nr, &nc);
    for(int i = 0; i<nr; i++){
        for(int j = 0; j<nc; j++){
            printf("%d ", (pMatrice[i][j]));
        }
        printf("\n");
    }
    separa(pMatrice, nr, nc, &vBianchi, &vNeri, &nb, &nn);
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
    for(int i=0; i<nr; i++){
        free(pMatrice[i]);
    }
    free(pMatrice);
    free(vNeri);
    free(vBianchi);
    return 0;
}

int **malloc2dR(char nomeFile[], int *nr, int *nc){
    //Inizializzazione variabili
    FILE* fp;
    int **pMatrice;
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
    pMatrice = (int **)malloc((*nr)*sizeof(int *));
    if(pMatrice == NULL){
        printf("Errore nell'allocazione delle righe\n");
        exit(1);
    }
    for(i=0; i<(*nr); i++){
        pMatrice[i] = (int *)malloc((*nc)*sizeof(int));
        if(pMatrice[i] == NULL){
            printf("Errore nell'allocazione delle colonne\n");
            exit(1);
        }

        //Riempimento matrice
        for (j=0;j<(*nc);j++){
            fscanf(fp ,"%d", &(pMatrice[i][j]));
        }
    }

    //Chiusura file
    fclose(fp);

    return pMatrice;
}

void separa(int **pMatrice, int nr, int nc, int **vBianchi, int **vNeri, int *nb, int *nn){
    //Inizializzazione variabili
    int dimensioneTot = nr*nc;

    //Allocazione dinamica vettori
    if((dimensioneTot)%2 == 0) {
        *vBianchi = (int *) malloc((dimensioneTot/2)*sizeof(int));
        *vNeri = (int *) malloc((dimensioneTot/2)*sizeof(int));
        if(vBianchi == NULL || vNeri == NULL){
            printf("Errore nell'allocazione dei vettori\n");
            exit(1);
        }
    }
    else{
        *vBianchi = (int *) malloc((dimensioneTot/2-1)*sizeof(int));
        *vNeri = (int *) malloc((dimensioneTot/2+1)*sizeof(int));
        if(vBianchi == NULL || vNeri == NULL){
            printf("Errore nell'allocazione dei vettori\n");
            exit(1);
        }
    }

    //Corpo funzione
    for(int i = 0; i<nr; i++){
        for(int j = 0; j<nc; j++){
            if (j % 2 == 0 && i % 2 == 0 || j % 2 != 0 && i % 2 != 0) {
                (*vNeri)[(*nn)++] = pMatrice[i][j];
            } else {
                (*vBianchi)[(*nb)++] = pMatrice[i][j];
            }
        }
    }
}