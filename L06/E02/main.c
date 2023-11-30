#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXL 50
#define numPietre 4
typedef struct {
    int numero[numPietre];
}stones;


stones *leggiFile(char nomeFile[MAXL], stones *pietre, int *nr);
void preparativo(int nr, stones *pietre);
void rimanenti(int riman[numPietre], stones pietre);
int fZ(int riman[numPietre], int lunghezza, int lmax);
int fR(int riman[numPietre], int lunghezza, int lmax);
int fT(int riman[numPietre], int lunghezza, int lmax);
int fS(int riman[numPietre], int lunghezza, int lmax);

int main() {
    char nomeFile[MAXL];
    stones *pietre = NULL;
    int nr;

    printf("inserire nome file: \n");
    scanf("%s", nomeFile);

    pietre = leggiFile(nomeFile, pietre, &nr);
    preparativo(nr, pietre);

    free(pietre);

    return 0;
}
///funzione che legge il file
stones *leggiFile(char nomeFile[MAXL], stones *pietre, int *nr) {
    FILE *fp;
    int i, j;

    if((fp = fopen(nomeFile, "r")) == NULL) {
        printf("errore in apertura file");
        exit(1);
    }

    fscanf(fp,"%d", nr);
    ///ALLOCO DINAMICAMENTE LA STRUCT PER CONTENERE TUTTE LE RIGHE DEL FILE
    pietre = (stones *)malloc((*nr)*sizeof(stones ));
    if(pietre == NULL){
        printf("errore nell'allocazione");
        exit(1);
    }

    for(i=0; i<(*nr); i++) {
        for(j=0; j<4; j++) {
            fscanf(fp, "%d", &pietre[i].numero[j]);
        }
    }


    fclose(fp);
    return pietre;
}

///vettore temporaneo collana
void rimanenti(int riman[numPietre], stones pietre){
    riman[0] = pietre.numero[0];
    riman[1] = pietre.numero[1];
    riman[2] = pietre.numero[2];
    riman[3] = pietre.numero[3];
}

///FUNZIONE WRAP CHE RACCOGLIE LA MAGGIOR PARTE DELLE OPERAZIONI PER FARE LA COLLANA
void preparativo(int nr, stones *pietre){
    int riman[numPietre], i, lung;

    for(i=0; i<nr; i++) {
        lung = 0;

        rimanenti(riman, pietre[i]);
        lung = fZ(riman, 0, lung);

        rimanenti(riman, pietre[i]);
        lung = fR(riman, 0, lung);

        rimanenti(riman, pietre[i]);
        lung = fT(riman, 0, lung);

        rimanenti(riman, pietre[i]);
        lung = fS(riman, 0, lung);

        printf("la lunghezza massima della collana numero %d e' di : (%d)\n", i, lung);
    }

}

int fZ(int riman[numPietre], int lunghezza, int lmax){
    int z=0;

    if (riman[z] == 0){
        if(lunghezza >= lmax) {
            lmax = lunghezza;
        }
        return lmax;
    }

    riman[z] -= 1;
    lunghezza += 1;

    lmax = fZ(riman, lunghezza, lmax);
    lmax = fR(riman, lunghezza, lmax);

    riman[z] += 1;
    lunghezza -= 1;

    return lmax;

}
int fR(int riman[numPietre], int lunghezza, int lmax) {
    int r=1;

    if (riman[r] == 0){
        if(lunghezza >= lmax) {
            lmax = lunghezza;
        }
        return lmax;
    }

    riman[r] -= 1;
    lunghezza += 1;

    lmax = fS(riman, lunghezza, lmax);
    lmax = fT(riman, lunghezza, lmax);

    riman[r] += 1;
    lunghezza -= 1;

    return lmax;

}
int fT(int riman[numPietre], int lunghezza, int lmax) {
    int t=2;

    if (riman[t] == 0){
        if(lunghezza >= lmax) {
            lmax = lunghezza;
        }
        return lmax;
    }

    riman[t] -= 1;
    lunghezza += 1;

    lmax = fZ(riman, lunghezza, lmax);
    lmax = fR(riman, lunghezza, lmax);

    riman[t] += 1;
    lunghezza -= 1;

    return lmax;

}
int fS(int riman[numPietre], int lunghezza, int lmax) {
    int s=3;

    if (riman[s] == 0){
        if(lunghezza >= lmax) {
            lmax = lunghezza;
        }
        return lmax;
    }

    riman[s] -= 1;
    lunghezza += 1;

    lmax = fS(riman, lunghezza, lmax);
    lmax = fT(riman, lunghezza, lmax);

    riman[s] += 1;
    lunghezza -= 1;


    return lmax;

}