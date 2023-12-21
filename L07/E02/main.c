#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXC 100
#define MAXELEM 5

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

typedef struct {
    int nDiag;
    int nGiri;
    int acrobatico;
    int acrAvan;
    int acrInd;
    int acrDiFila;
    int moltiplicatore;
    int diffTot;
    int diffDiag;
}regole_s;

int leggiFile(char nomeFile[MAXC], elementi_s **elementi);
void wrapper(elementi_s *elementi, int nr);
elementi_s diagonaliR(int DD, int DP, int nrSet, elementi_s *set, elementi_s *definitivo, elementi_s *tmp, regole_s regole, int pos);
elementi_s copia(elementi_s primo, elementi_s secondo);
regole_s aggiornaRegole(regole_s regole, elementi_s tmp);

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
    elementi_s set[nr], definitivo[nr], tmp[nr];
    regole_s regole;

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

        regole.nDiag = 0;
        regole.nGiri = 0;
        regole.acrobatico = 0;
        regole.acrAvan = 0;
        regole.acrInd = 0;
        regole.acrDiFila = 0;
        regole.moltiplicatore = 0;
        regole.diffTot = 0;
        regole.diffDiag = 0;

        printf("vuoi continuare si o no?");
        scanf("%s", decisione);
        if(strcasecmp("no", decisione) == 0){
            bool = 0;
        }
    }
}


elementi_s diagonaliR(int DD, int DP, int nrSet, elementi_s *set, elementi_s *definitivo, elementi_s *tmp, regole_s regole, int pos) {
    int i;

    for(i=0; i<nrSet; i++) {
        if(regole.nDiag == 0){
            if(set[i].reqDiPrec == 0 && set[i].difficolta <= DD && (set[i].difficolta + regole.diffTot) <= DP){

                tmp[pos] = copia(tmp[pos], set[i]);

                definitivo = diagonaliR(DD, DP)
            }
        }


    }


}

regole_s aggiornaRegole(regole_s regole, elementi_s tmp){
    regole.nDiag += 1;
    if (tmp.tipologia != 0){
        regole
    }
}

elementi_s copia(elementi_s primo, elementi_s secondo) {
    strcpy(primo.nome, secondo.nome);
    primo.tipologia = secondo.tipologia;
    primo.dirIng = secondo.dirIng;
    primo.dirUsc = secondo.dirUsc;
    primo.reqDiPrec = secondo.tipologia;
    primo.finale = secondo.finale;
    primo.valore = secondo.valore;
    primo.difficolta = secondo.difficolta;
    return primo;
}
