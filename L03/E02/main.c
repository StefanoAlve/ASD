#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXL 255
#define MAXR 50

char ***leggiFile(char nomeFile[], int *persone, int **braniPP);
int combinazioni(char ***matrice, int persone, int *braniPP, int k, int l, char **playlist);

int main() {
    int persone, *braniPerPersona = NULL, i, j, k=0, l=0;
    char nomeFile[MAXR], ***matr = NULL, **playlist=NULL;

    printf("come si chiama il file?\n");
    scanf("%s", nomeFile);

    matr = leggiFile(nomeFile, &persone, &braniPerPersona);


    for (i = 0; i< persone; i++){
        printf("il numero di brani per questo personaggio sono %d\n ", braniPerPersona[i]);
        for (j=0; j<braniPerPersona[i]; j++){

            printf("    brano : %s\n", matr[i][j]);
        }
    }




    playlist = (char **)malloc(persone*sizeof(char *));
    if(playlist == NULL){
        printf("errore in allocazione di memoria");
        exit(1);
    }
    for (i = 0; i< persone; i++){
        playlist[i] = (char *)malloc(MAXL*sizeof(char));
        if(playlist[i] == NULL){
            printf("errore in allocazione di memoria");
            exit(1);
        }
    }


    printf("\n\n\n\n\n");
    combinazioni(matr, persone, braniPerPersona, k , l, playlist);


    ///DEALLOCAZIONE DI MEMORIA
    for (i = 0; i< persone; i++){
        for (j=0; j<braniPerPersona[i]; j++) {
            free(matr[i][j]);
        }
        free(matr[i]);
    }
    free(matr);
    free(braniPerPersona);
    for (i = 0; i< persone; i++){
        free(playlist[i]);
    }
    free(playlist);


    return 0;
}

char ***leggiFile(char nomeFile[], int *persone, int **braniPP) {
    FILE *fp;
    int i, j, *tempBra;
    char ***matr;

    if((fp = fopen(nomeFile,"r"))==NULL){
        printf("errore in apertura file");
        exit(1);
    }
    fscanf(fp,"%d", persone);

    ///ALLOCO LE PERSONE
    matr = (char ***)malloc((*persone)*sizeof(char **));
    if (matr == NULL) {
        printf("errore in allocazione righe");
        exit(1);
    }

    ///ALLOCO I BRANI PER PERSONA
    *braniPP = (int *)malloc((*persone)*sizeof(int ));
    if (braniPP == NULL) {
        printf("errore in allocazione righe");
        exit(1);
    }
    tempBra = (int *)malloc((*persone)*sizeof(int ));
    if (tempBra == NULL) {
        printf("errore in allocazione righe");
        exit(1);
    }

    ///ALLOCO I BRANI PER PERSONA E LI RIEMPIO
    for(i=0; i<(*persone); i++) {

        ///RIEMPIO IL VETTORE CHE CONTIENE I NUMERI DEI BRANI PER PERSONA
        fscanf(fp,"%d", &tempBra[i]);
        (*braniPP)[i] = tempBra[i];

        ///ALLOCO I BRANI
        matr[i] = (char **)malloc(tempBra[i]*sizeof(char *));
        if (matr[i] == NULL) {
            printf("errore in allocazione righe");
            exit(1);
        }

        ///ALLOCO I SINGOLI BRANI
        for(j=0; j < tempBra[i]; j++) {

            matr[i][j] = (char *)malloc(MAXL*sizeof(char));
            if (matr[i] == NULL) {
                printf("errore in allocazione righe");
                exit(1);
            }
            ///PRENDO I SINGOLI BRANI E LI METTO NELLA MATRICE
            fscanf(fp, "%s", matr[i][j]);
        }
    }


    fclose(fp);
    return matr;
}

int combinazioni(char ***matrice, int persone, int *braniPP, int k, int l, char **playlist) {
    int i, j;

    for (l=0; l<braniPP[k]; l++) {
        strcpy(playlist[k], matrice[k][l]);
        if(k != persone - 1) {
            j=k+1;
            combinazioni(matrice, persone, braniPP, j, l, playlist);
        }
        else{
            printf("playlist:\n");
            for (i = 0; i < persone; i++) {
                printf("%s ", playlist[i]);
            }
            printf("\n");
        }


    }

}