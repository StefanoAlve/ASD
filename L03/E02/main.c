#include <stdio.h>
#include <stdlib.h>
#define MAXL 255
#define MAXR 50

char ***leggiFile(char nomeFile[], int *persone, int **braniPP);


int main() {
    int persone, *braniPerPersona = NULL, i, j;
    char nomeFile[MAXR], ***matr = NULL;

    printf("come si chiama il file?\n");
    scanf("%s", nomeFile);

    matr = leggiFile(nomeFile, &persone, &braniPerPersona);




    ///DEALLOCAZIONE DI MEMORIA
    for (i = 0; i< persone; i++){
        for (j=0; j<braniPerPersona[i]; j++) {
            free(matr[i][j]);
        }
        free(matr[i]);
    }
    free(matr);
    free(braniPerPersona);

    return 0;
}

char ***leggiFile(char nomeFile[], int *persone, int **braniPP) {
    FILE *fp;
    int i, j;
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
    braniPP = (int **)malloc((*persone)*sizeof(int *));
    if (braniPP == NULL) {
        printf("errore in allocazione righe");
        exit(1);
    }

    ///ALLOCO I BRANI PER PERSONA E LI RIEMPIO
    for(i=0; i<(*persone); i++) {

        ///RIEMPIO IL VETTORE CHE CONTIENE I NUMERI DEI BRANI PER PERSONA
        fscanf(fp,"%d", braniPP[i]);

        ///ALLOCO I BRANI
        matr[i] = (char **)malloc((*braniPP[i])*sizeof(char *));
        if (matr[i] == NULL) {
            printf("errore in allocazione righe");
            exit(1);
        }

        ///ALLOCO I SINGOLI BRANI
        for(j=0; j<(*braniPP[i]); j++) {

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

