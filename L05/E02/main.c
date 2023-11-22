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
    int ntes, r, c, max;

    leggiFile(&tessere, &tavolo, &ntes, &r, &c);

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


    ///matrice contenente i dati della tessere nella posizione sarà utilizzata come matrice temporanea nella ricorsiva
    matrice = inizMatrix(tessere, tavolo, &mark, r, c, ntes);

    ///INIZIALIZZO LA MATRICE DEFINITIVA CHE CONTERRA I VALORI DELLA MATRICE CON SOMMA MASSIMA
    definitiva = (matrix **)malloc(r*sizeof(matrix *));
    for(j=0; j<r; j++){
        definitiva[j] = (matrix *)malloc(c*sizeof(matrix));
    }

    ///inizializzo un vettore con i tasselli da non usare
    for (i=0 ;i<ntes; i++){
        proibite[i] = 1;
    }
    for (i=0; i<r; i++){
        for(j=0; j<c; j++) {
            ///inserisco i tasselli che a priori sono nella matrice
            if(tavolo[i][j].indiceTessera != -1){
                proibite[tavolo[i][j].indiceTessera] = 0;
            }
        }
    }
    ///FUNZIONE RICORSIVA CHE TROVA LA SOMMA MASSIMA E LA MATRICE DEFINITIVA
    somma = casiR(matrice, tessere, mark, r, c, ntes, definitiva, 0, 0, 0, 0, proibite);

    ///VARI PRINT
    printf("la somma di tutti gli elementi validi: %d\nmatrice:\n", somma);
    for (i=0; i<r; i++){
        for(j=0; j<c; j++){
            printf("%c%d %c%d |", definitiva[i][j].riga,definitiva[i][j].valoreR, definitiva[i][j].colonna, definitiva[i][j].valoreC);
        }
        printf("\n");
    }


    ///DEALLICAZIONE DI VARIE MATRICI USATE
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

    ///INIZIALIZZO LA MATRICE DEI MARK CHE SERVE PER VEDERE LE POSIZIONI DELLA MATRICE IN CUI è GIA PRESENTE UN TASSELLO
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
    ///LO INIZIALIZZO A 0
    for(i=0; i<r; i++){
        for(j=0; j<c; j++){
            (*mark)[i][j] = 0;
        }
    }

    ///COPIO NELLA MATRICE TEMPORANEA I VALORI CHE NON DEVONO ESSERE TOCCATI
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
                ///POSIZIONI DELLA MATRICE CHE NON DEVONO ESSERE USATE CORRISPONDENTI AI TASSELLI FISSI
                (*mark)[i][j] = -1;
            }
        }
    }
    return matrice;
}
///funzione ricorsiva per provare tutte le combinazioni
int casiR(matrix **matrice, tessera *tessere, int **mark, int r, int c, int ntes, matrix **definitiva, int sommaMax, int somma, int posR, int posC, int *proibite) {
    int i, j, posT;

    ///TERMINAZIONE
    if (posR >= r) {
        somma = 0;
        ///fa la somma degli elementi sulla riga
        somma = sommaR(somma, matrice, r, c);
        ///somma colonne
        somma = sommaC(somma, matrice, r, c);
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
        ///ITERO OGNI VOLTA SU TUTTI I TASSELLI
        for (posT = 0; posT < ntes; posT++) {
            ///CONTROLLO SE IL TASSELLO è UTILIZZABILE (NON USATO GIA')
            if(proibite[posT]) {
                ///IN MANIERA RICORSIVA PONGO IL VALORE NELLA MATRICE
                matrice[posR][posC].riga = tessere[posT].riga;
                matrice[posR][posC].colonna = tessere[posT].colonna;
                matrice[posR][posC].valoreR = tessere[posT].valoreR;
                matrice[posR][posC].valoreC = tessere[posT].valoreC;
                ///CASO IN CUI MI TROVO NON ALLA FINE DELLA COLONNA (AUMENTO LA COLONNA)
                if (posC < c - 1) {
                    ///PROIBISCO L'UTILIZZO DELLA TESSERA ALLE PROSSIME ITERAZIONI RICORSIVE
                    proibite[posT] = 0;
                    sommaMax = casiR(matrice, tessere, mark, r, c, ntes, definitiva, sommaMax, somma, posR, posC + 1, proibite);
                    ///LA RENDO RIUTILIZZABILE
                    proibite[posT] = 1;

                }
                ///CASO IN CUI MI TROVO ALLA FINE DELLA COLONNA (AUMENTO LA RIGA E AZZERO LA COLONNA)
                else if (posC == c - 1) {

                    proibite[posT] = 0;
                    sommaMax = casiR(matrice, tessere, mark, r, c, ntes, definitiva, sommaMax, somma, posR + 1, 0, proibite);
                    proibite[posT] = 1;

                }
                ///BACKTRACK E METTO IL VALORE RUOTATO
                matrice[posR][posC].riga = tessere[posT].colonna;
                matrice[posR][posC].colonna = tessere[posT].riga;
                matrice[posR][posC].valoreR = tessere[posT].valoreC;
                matrice[posR][posC].valoreC = tessere[posT].valoreR;
                ///CASO IN CUI MI TROVO NON ALLA FINE DELLA COLONNA (AUMENTO LA COLONNA)
                if (posC < c - 1) {

                    proibite[posT] = 0;
                    sommaMax = casiR(matrice, tessere, mark, r, c, ntes, definitiva, sommaMax, somma, posR, posC + 1, proibite);
                    proibite[posT] = 1;

                }
                ///CASO IN CUI MI TROVO ALLA FINE DELLA COLONNA (AUMENTO LA RIGA E AZZERO LA COLONNA)
                else if (posC == c - 1) {

                    proibite[posT] = 0;
                    sommaMax = casiR(matrice, tessere, mark, r, c, ntes, definitiva, sommaMax, somma, posR + 1, 0, proibite);
                    proibite[posT] = 1;

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
            ///CONIDZIONE PER VEDERE CHE I CARATTERI SONO UGUALI E CONSECUTIVI
            if (j != c-1 && matrice[i][j].riga != matrice[i][j+1].riga){
                flag = 0;
                break;
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

    for (j = 0; j < c; j++) {
        for (i = 0; i < r; i++) {
            ///CONIDZIONE PER VEDERE CHE I CARATTERI SONO UGUALI E CONSECUTIVI
            if (i != r-1 && matrice[i][j].colonna != matrice[i+1][j].colonna){
                flag = 0;
                break;
            }
        }
        if (flag){
            for (i = 0; i < r; i++) {
                somma = somma + matrice[i][j].valoreC;
            }
        }
        flag = 1;
    }
    return somma;
}
