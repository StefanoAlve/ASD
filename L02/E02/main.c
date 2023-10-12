#include <stdio.h>
#include <stdlib.h>
#define MAXL 30
int  **malloc2dR(char nomeFile[], int *nr, int *nc);
int main(void) {
    //Inizializzazione variabili
    char nomeFile[MAXL];
    int **pMatrice, nr, nc;
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
    //Deallocazione
    for(int i=0; i<nr; i++){
        free(pMatrice[i]);
    }
    free(pMatrice);
    return 0;
}

int **malloc2dR(char nomeFile[], int *nr, int *nc){
    //Inizializzazione variabili
    FILE* fp;
    int **pRighe;
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
    pRighe = (int **)malloc((*nr)*sizeof(int *));
    if(pRighe == NULL){
        printf("Errore nell'allocazione delle righe\n");
        exit(1);
    }
    for(i=0; i<(*nr); i++){
        pRighe[i] = (int *)malloc((*nc)*sizeof(int));
        if(pRighe[i] == NULL){
            printf("Errore nell'allocazione delle colonne\n");
            exit(1);
        }
        for (j=0;j<(*nc);j++){
            fscanf(fp ,"%d", &(pRighe[i][j]));
        }
    }
    //Chiusura file
    fclose(fp);

    return pRighe;
}