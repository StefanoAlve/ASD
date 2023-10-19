#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXL 255

//Strutture
typedef struct{
    int nr;
    int *nCanzoni;
}sDimensioni;

//FUNZIONI
void leggiFile(char ****canzoni, sDimensioni *dimensioni); //canzoni è il puntatore a una matrice di stringhe
void deallocaCanzoni(char ***canzoni, sDimensioni dimensioni);
int main(void) {
    //Inizializzazione variabili
    char ***canzoni; //matrice di stringhe
    sDimensioni dimensioni;
    //Apertura file
    leggiFile(&canzoni, &dimensioni);
    //Corpo programma
    //Deallocazione
    deallocaCanzoni(canzoni, dimensioni);
    return 0;
}

void leggiFile(char ****canzoni, sDimensioni *dimensioni){
    //Inizializzazione variabili
    FILE* fp;
    char *nomeFile, tmp[MAXL], ***canzoniTmp;
    int nr, nCanzoni, cont=0;

    //Richiesta del nome del file
    printf("Inserire il nome del file:");
    scanf("%s", tmp);
    nomeFile = strdup(tmp);

    //Apertura file
    fp= fopen(nomeFile, "r");
    if(fp == NULL){
        printf("Errore nell'apertura del file!\n");
        exit(1);
    }
    //Lettura del file e salvataggio dati
    scanf("%d", &dimensioni->nr);

    canzoniTmp = (char***)malloc(dimensioni->nr*sizeof(char**)); //Allocazione dinamica del vettore dei puntatori che indicano i vettori di canzoni
    dimensioni->nCanzoni = (int*)malloc(dimensioni->nr*sizeof(int));
    while(!feof(fp)){
        scanf("%d", &dimensioni->nCanzoni[cont]);
        for(int i=0; i<dimensioni->nCanzoni[cont]; i++){
            scanf("%s", tmp);
            canzoniTmp[cont][i] = strdup(tmp);
        }
        cont++;
    }
    *canzoni = canzoniTmp;

    //Chiusura file
    fclose(fp);
}

void deallocaCanzoni(char ***canzoni, sDimensioni dimensioni){
    for(int i = 0; i<dimensioni.nr; i++){
        free(canzoni[])
    }
}