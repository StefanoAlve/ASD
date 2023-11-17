#include <stdio.h>
#include <stdlib.h>
#define MAXL 50

typedef struct{
    char riga;
    int valoreR;
    char colonna;
    int valoreC;
}tessera;

typedef struct{
    int indiceTessera;
    int rotazione;
}board;

typedef struct{
    char riga;
    int valoreR;
    char colonna;
    int valoreC;
    int rotazione;
}matrix;


void leggiFile(tessera **tessere, board ***tavolo, int *ntes, int *r, int *c);
void dealloca(tessera *tessere, board **tavolo, int r);
int wrap(tessera *tessere, board **tavolo, int ntes, int r, int c);
matrix **inizMatrix(tessera *tessere, board **tavolo, int ***mark, int r, int c, int ntes);
int casiR(matrix **matrice, tessera *tessere, int **mark, int r, int c, int ntes, matrix **definitiva, int sommaMax, int somma, int posR, int posC, int *proibite);
int sommaR(int somma, matrix **matrice, int r, int c);
int sommaC(int somma, matrix **matrice, int r, int c);

int main() {
    tessera *tessere;
    board **tavolo;
    int ntes, r, c, ntav, i, j, max;

    leggiFile(&tessere, &tavolo, &ntes, &r, &c);

    /*printf("tessere: \n");
    for (i=0; i<ntes; i++) {
        printf("%c, %d %c, %d\n", tessere[i].riga, tessere[i].valoreR
                , tessere[i].colonna, tessere[i].valoreC);
    }
    printf("\ntavola\n");
    for (i=0; i<r; i++){
        for(j=0; j<c; j++){
            printf("%d/%d ", tavolo[i][j].indiceTessera, tavolo[i][j].rotazione);
        }
        printf("\n");
    }*/

    max = wrap(tessere, tavolo, ntes, r, c);


    dealloca(tessere, tavolo, r);
    return 0;
}
///FUNZIONE CHE DEALLOCA LE TESSERE E IL TAVOLO
void dealloca(tessera *tessere, board **tavolo, int r){
    int i;

    free(tessere);
    for (i = 0; i < r; i++) {
        free(tavolo[i]);
    }

    free(tavolo);
}
///FUNZIONE LEGGIFILE
void leggiFile(tessera **tessere, board ***tavolo, int *ntes, int *r, int *c) {
    FILE *fp;
    char nomeFile[MAXL];
    int i, j;

    ///FILE DELLE TESSERE
    printf("inserire il nome del file delle tessere : \n");
    scanf("%s", nomeFile);

    if((fp = fopen(nomeFile, "r")) == NULL){
        printf("errore in apertura file");
        exit(1);
    }

    fscanf(fp, "%d ", ntes);

    *tessere = malloc((*ntes)*sizeof(tessera));
    if(tessere == NULL){
        printf("errore in allocazione");
        exit(1);
    }

    for(i=0; i<(*ntes); i++){
        fscanf(fp, "%c ", &(*tessere)[i].riga);
        fscanf(fp, "%d ", &(*tessere)[i].valoreR);
        fscanf(fp, "%c ", &(*tessere)[i].colonna);
        fscanf(fp, "%d ", &(*tessere)[i].valoreC);
    }

    fclose(fp);

    ///FILE DEL BOARD
    printf("inserire il nome del file della tavola : \n");
    scanf("%s", nomeFile);

    if((fp = fopen(nomeFile, "r")) == NULL){
        printf("errore in apertura file");
        exit(1);
    }

    fscanf(fp, "%d %d", r, c);


    *tavolo = malloc((*r) * sizeof(board *));
    if (*tavolo == NULL) {
        printf("errore in allocazione");
        exit(1);
    }
    for (i = 0; i < *r; i++) {
        (*tavolo)[i] = malloc((*c) * sizeof(board));
        if ((*tavolo)[i] == NULL) {
            printf("errore in allocazione");
            exit(1);
        }
    }

    for (i=0; i<(*r); i++) {
        for (j = 0; j < (*c); j++) {
            fscanf(fp, "%d/%d ", &(*tavolo)[i][j].indiceTessera, &(*tavolo)[i][j].rotazione);
        }
    }
    fclose(fp);
}
///FUNZIONE WRAP
int wrap(tessera *tessere, board **tavolo, int ntes, int r, int c) {
    int **mark, j, i, somma, proibite[ntes];
    matrix **matrice, **definitiva;


    ///matrice contenente i dati della tessere nella posizione
    matrice = inizMatrix(tessere, tavolo, &mark, r, c, ntes);




    ///INIZIALIZZO LA MATRICE DEFINITIVA
    definitiva = (matrix **)malloc(r*sizeof(matrix *));
    for(j=0; j<r; j++){
        definitiva[j] = (matrix *)malloc(c*sizeof(matrix));
    }

    ///inizializzo un vettore con i tasselli da non spostare
    for (i=0 ;i<ntes; i++){
        proibite[i] = 1;
    }
    for (i=0; i<r; i++){
        for(j=0; j<c; j++) {
            if(tavolo[i][j].indiceTessera != -1){
                proibite[tavolo[i][j].indiceTessera] = 0;
            }
        }
    }

    somma = casiR(matrice, tessere, mark, r, c, ntes, definitiva, 0, 0, 0, 0, proibite);


    printf("%d\n", somma);

    for (i=0; i<r; i++){
        for(j=0; j<c; j++){
            printf("%c ", definitiva[i][j].riga);
        }
        printf("\n");
    }


            for (i = 0; i < r; i++) {
        free(definitiva[i]);
        free(mark[i]);
        free(matrice[i]);
    }
    free(definitiva);
    free(mark);
    free(matrice);


    return somma;
}
///INIZIALIZZO LA MATRICE CON DENTRO I VALORI DA INSERIRE E INSERITI PER FACILITARE I CALCOLI
matrix **inizMatrix(tessera *tessere, board **tavolo, int ***mark, int r, int c, int ntes) {
    matrix **matrice;
    int i, j;

    ///ALLOCO LE RIGHE DELLA MATRICE
    matrice = (matrix **) malloc(r * sizeof(matrix *));
    if (matrice == NULL) {
        printf("errore in allocazione");
        exit(1);
    }
    ///ALLOCO LE COLONNE DELLA MATRICE
    for (i = 0; i < r; i++) {
        matrice[i] = (matrix *) malloc(c * sizeof(matrix));
        if (matrice[i] == NULL) {
            printf("errore in allocazione");
            exit(1);
        }
    }

    ///INIZIALIZZO LA MATRICE DEI MARK
    *mark = (int **)malloc(r*sizeof(int*));
    if (*mark == NULL) {
        printf("errore in allocazione");
        exit(1);
    }
    for (j = 0; j < r; j++) {
        (*mark)[j] = (int *)malloc(c * sizeof(int));
        if ((*mark)[j] == NULL) {
            printf("errore in allocazione");
            exit(1);
        }
    }
    for(i=0; i<r; i++){
        for(j=0; j<c; j++){
            (*mark)[i][j] = 0;
        }
    }


    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            if (tavolo[i][j].indiceTessera != -1) {
                if (tavolo[i][j].rotazione == 0) {
                    matrice[i][j].riga = tessere[tavolo[i][j].indiceTessera].riga;
                    matrice[i][j].valoreR = tessere[tavolo[i][j].indiceTessera].valoreR;
                    matrice[i][j].colonna = tessere[tavolo[i][j].indiceTessera].colonna;
                    matrice[i][j].valoreC = tessere[tavolo[i][j].indiceTessera].valoreC;
                    matrice[i][j].rotazione = 0;
                }
                else if(tavolo[i][j].rotazione == 1){
                    matrice[i][j].riga = tessere[tavolo[i][j].indiceTessera].colonna;
                    matrice[i][j].valoreR = tessere[tavolo[i][j].indiceTessera].valoreC;
                    matrice[i][j].colonna = tessere[tavolo[i][j].indiceTessera].riga;
                    matrice[i][j].valoreC = tessere[tavolo[i][j].indiceTessera].valoreR;
                    matrice[i][j].rotazione = 1;
                }
                (*mark)[i][j] = -1;
            }
        }
    }
    return matrice;
}
///funzione ricorsiva per provare tutte le combinazioni
int casiR(matrix **matrice, tessera *tessere, int **mark, int r, int c, int ntes, matrix **definitiva, int sommaMax, int somma, int posR, int posC, int *proibite) {
    int i, j, posT;

    if (posR >= r) {
        somma = 0;
        ///fa la somma degli elementi sulla riga
        somma = somma + sommaR(somma, matrice, r, c);
        ///somma colonne
        somma = somma + sommaC(somma, matrice, r, c);
        ///CONDIZIONE DI COPIA
        if (somma > sommaMax) {
            sommaMax = somma;
            for (i = 0; i < r; i++) {
                for (j = 0; j < c; j++) {
                    definitiva[i][j].riga = matrice[i][j].riga;
                    definitiva[i][j].valoreR = matrice[i][j].valoreR;
                    definitiva[i][j].colonna = matrice[i][j].colonna;
                    definitiva[i][j].valoreC = matrice[i][j].valoreC;
                    definitiva[i][j].rotazione = matrice[i][j].rotazione;
                }
            }
        }
        return sommaMax;
    }
    ///CASO IN CUI IL MARK E' DIVERSO DA -1 OVVERO CHE IL VALORE NON E' A PRIORI NELLA MATRICE
    if(mark[posR][posC] != -1) {
        for (posT = 0; posT < ntes; posT++) {
            if(mark[posR][posC] != 1 && proibite[posT]) {
                ///IN MANIERA RICORSIVA PONGO IL VALORE NELLA MATRICE
                matrice[posR][posC].riga = tessere[posT].riga;
                matrice[posR][posC].colonna = tessere[posT].colonna;
                matrice[posR][posC].valoreR = tessere[posT].valoreR;
                matrice[posR][posC].valoreC = tessere[posT].valoreC;
                if (posC < c - 1) {
                    mark[posR][posC] = mark[posR][posC] + 1;
                    sommaMax = casiR(matrice, tessere, mark, r, c, ntes, definitiva, sommaMax, somma, posR, posC + 1, proibite);
                    mark[posR][posC] = mark[posR][posC] - 1;
                } else if (posC == c - 1) {
                    mark[posR][posC] = mark[posR][posC] + 1;
                    sommaMax = casiR(matrice, tessere, mark, r, c, ntes, definitiva, sommaMax, somma, posR + 1, 0, proibite);
                    mark[posR][posC] = mark[posR][posC] - 1;
                }
                ///BACKTRACK E METTO IL VALORE RUOTATO
                matrice[posR][posC].riga = tessere[posT].colonna;
                matrice[posR][posC].colonna = tessere[posT].riga;
                matrice[posR][posC].valoreR = tessere[posT].valoreC;
                matrice[posR][posC].valoreC = tessere[posT].valoreR;
                if (posC < c - 1) {
                    mark[posR][posC] = mark[posR][posC] + 1;
                    sommaMax = casiR(matrice, tessere, mark, r, c, ntes, definitiva, sommaMax, somma, posR, posC + 1, proibite);
                    mark[posR][posC] = mark[posR][posC] - 1;
                } else if (posC == c - 1) {
                    mark[posR][posC] = mark[posR][posC] + 1;
                    sommaMax = casiR(matrice, tessere, mark, r, c, ntes, definitiva, sommaMax, somma, posR + 1, 0, proibite);
                    mark[posR][posC] = mark[posR][posC] - 1;
                }
            }
        }
    }
    ///CASO IN CUI IL VALORE E' GIA NELLA MATRICE
    else{
        if(posC < c-1){
            sommaMax = casiR(matrice, tessere, mark, r, c, ntes, definitiva, sommaMax, somma, posR, posC+1, proibite);
        }
        else if(posC == c-1){
            sommaMax = casiR(matrice, tessere, mark, r, c, ntes, definitiva, sommaMax, somma, posR+1, 0, proibite);
        }
    }


    return sommaMax;
}
///funzione che fa la somma degli elementi sulla riga
int sommaR(int somma, matrix **matrice, int r, int c) {
    int i, j, flag = 1;

    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            if (j != c-1 && matrice[i][j].riga != matrice[i][j+1].riga){
                flag = 0;
            }
        }
        if (flag){
            for (j = 0; j < c; j++) {
                somma = somma + matrice[i][j].valoreR;
            }
        }
        flag = 1;
    }
    return somma;
}
///FUNZIONE CHE FA LA SOMMA DEGLI ELEMENTI SULLE COLONNE
int sommaC(int somma, matrix **matrice, int r, int c) {
    int i, j, flag = 1;

    for (i = 0; i < c; i++) {
        for (j = 0; j < r; j++) {
            if (j != r-1 && matrice[i][j].colonna != matrice[i][j+1].colonna){
                flag = 0;
            }
        }
        if (flag){
            for (j = 0; j < r; j++) {
                somma = somma + matrice[i][j].valoreC;
            }
        }
        flag = 1;
    }
    return somma;
}
