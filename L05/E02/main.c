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


void leggiFile(tessera **tessere, board **tavolo, int *ntes, int *r, int *c, int *ntav);

int main() {
    tessera *tessere;
    board *tavolo;
    int ntes, r, c, ntav, i, j;

    leggiFile(&tessere, &tavolo, &ntes, &r, &c, &ntav);

    /*printf("tessere: \n");
    for (i=0; i<ntes; i++) {
        printf("%c, %d %c, %d\n", tessere[i].riga, tessere[i].valoreR
                , tessere[i].colonna, tessere[i].valoreC);
    }
    printf("\ntavola\n");
    for (i=0; i<r; i++){
        for(j=0; j<c; j++){
            printf("%d/%d ", tavolo[(i*3)+j].indiceTessera, tavolo[(i*3)+j].rotazione);
        }
        printf("\n");
    }*/

    free(tessere);
    free(tavolo);
    return 0;
}

void leggiFile(tessera **tessere, board **tavolo, int *ntes, int *r, int *c, int *ntav) {
    FILE *fp;
    char nomeFile[MAXL];
    int i;

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
        //fscanf(fp, "%c %d %c %d", &(*tessere)[i].riga, &(*tessere)[i].valoreR, &(*tessere)[i].colonna, &(*tessere)[i].valoreC );

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
    *ntav = (*r)*(*c);

    *tavolo = malloc((*ntav)*sizeof(board));
    if(tavolo == NULL){
        printf("errore in allocazione");
        exit(1);
    }

    for (i=0; i<(*ntav); i++) {
        fscanf(fp, "%d/%d ", &(*tavolo)[i].indiceTessera, &(*tavolo)[i].rotazione);
    }

    fclose(fp);
}