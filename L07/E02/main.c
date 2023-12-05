#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXC 100

typedef struct{
    char nome[MAXC];
    int tipologia;
    int dirIng;
    int dirUsc;
    int reqDiPrec;
    int finale;
    float valore;
    int difficolta;
}elementi_s;

int leggiFile(char nomeFile[MAXC], elementi_s **elementi);
void wrapper(elementi_s *elementi, int nr);

int main() {
    char nomeFile[MAXC] = "elementi.txt";
    int nr;
    elementi_s *elementi;

    nr = leggiFile(nomeFile, &elementi);
    wrapper(elementi, nr);
    return 0;
}

int leggiFile(char nomeFile[MAXC], elementi_s **elementi) {
    int nr, i;
    FILE *fp = fopen(nomeFile, "r");

    if(fp == NULL) {
        printf("errore in apertura file");
        exit(1);
    }

    fscanf(fp, "%d", &nr);

    *elementi = malloc(nr*sizeof(elementi));
    if((*elementi) == NULL) {
        printf("errore in allocazione di memoria");
        exit(1);
    }

    for (i=0; i < nr; i++) {
        fscanf(fp,"%s ", (*elementi)[i].nome);
        printf("%s\n", (*elementi)[i].nome);
        fscanf(fp,"%d", &(*elementi)[i].tipologia);
        fscanf(fp,"%d",  &(*elementi)[i].dirIng);
        fscanf(fp,"%d", &(*elementi)[i].dirUsc);
        fscanf(fp,"%d", &(*elementi)[i].reqDiPrec);
        fscanf(fp,"%d", &(*elementi)[i].finale);
        fscanf(fp,"%f", &(*elementi)[i].valore);
        fscanf(fp,"%d", &(*elementi)[i].difficolta);
    }

    return nr;
}

void wrapper(elementi_s *elementi, int nr) {
    int DD, DP, nrSet, bool=1, i, index;
    char decisione[MAXC];
    elementi_s set[nr];

    while(bool) {
        printf("\n\n\n decidi quanti elementi vuoi nel set(max %d)\n", nr);
        scanf("%d", &nrSet);
        printf("scegli gli indici degli elementi fra questi:\n");
        for (i=0; i<nr; i++){
            printf("%d\t%s\n", i, elementi[i].nome);
        }
        printf("inserisci un valore per volta \n");
        for (i=0; i<nrSet; i++) {
            scanf("%d", &index);
            strcpy(set[i].nome, elementi[index].nome);
            set[i].tipologia = elementi[index].tipologia;
            set[i].dirIng = elementi[index].dirIng;
            set[i].dirUsc = elementi[index].dirUsc;
            set[i].reqDiPrec = elementi[index].tipologia;
            set[i].finale = elementi[index].finale;
            set[i].valore = elementi[index].valore;
            set[i].difficolta = elementi[index].difficolta;
        }
        printf("scegli il limite di difficolta' di diagonale e di programma\n");
        scanf("%d %d", &DD, &DP);






        printf("vuoi continuare si o no?");
        scanf("%s", decisione);
        if(strcasecmp("no", decisione) == 0){
            bool = 0;
        }
    }
}
