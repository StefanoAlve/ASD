#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXC 100
#define DD 10
#define DP 20
typedef struct{
    char nome[MAXC];
    int tipologia;
    int dir_ing;
    int dir_usc;
    int req_prec;
    int req_fin;
    float valore;
    int difficolta;
}elemento_s;
typedef struct{
    char nomiElementi[5][100];
    int difDiag;
    int nElementi;
    int acrobatici[3]; //Vett di int, indica in pos 0 quanti elementi acrobatici sono presenti, in 1 quanti in avanti e in 2 quanti indietro
    int sequenza; //1 se è presente una sequenza di almeno due elementi acrobatici
    float valoreDiag;
    int bonus;
}diagonale_s;

typedef struct{
    diagonale_s diagonali[3];
    int difProg;
    int bonus;
    float punteggioProg;
}programma_s;

typedef struct node *link;
struct node{
    diagonale_s diagonale;
    link next;
};
typedef struct{
    link head;
    link tail;
    int nDiag;
}listaDiag_s;
//Funzioni

int leggiElementi(elemento_s** pVettElementi);
void sequenzaMaxGreedy(elemento_s *vettElementi, int nElem);
void mergeSort(elemento_s *vettElementi, int nElem);
void mergeSort_r(elemento_s *val, elemento_s *aus, int l, int r);
void merge(elemento_s *val, elemento_s *aus, int l, int m, int r);
void stampaMigliore(programma_s migliore);
int confrontaElem(elemento_s e1, elemento_s e2);
int main() {
    elemento_s *vettElementi;
    int nElem;
    nElem=leggiElementi(&vettElementi);
    sequenzaMaxGreedy(vettElementi, nElem);
    return 0;
}

int leggiElementi(elemento_s** pVettElementi){
    FILE *fp;
    elemento_s *vettElementi;
    int nElem, cnt=0;
    char nomeFile[MAXC];
    printf("Inserisci il nome del file da cui prelevare gli elementi:");
    scanf("%s", nomeFile);
    fp = fopen(nomeFile, "r");
    if(fp == NULL){
        printf("Errore nell'apertura del file!\n");
        exit(1);
    }
    //Leggo numero elementi
    fscanf(fp, "%d", &nElem);
    //Alloco vettElementi
    vettElementi = (elemento_s*)malloc(nElem*sizeof(*vettElementi));
    while(!feof(fp)) {
        if(fscanf(fp,"%s %d %d %d %d %d %f %d", vettElementi[cnt].nome, &vettElementi[cnt].tipologia, &vettElementi[cnt].dir_ing, &vettElementi[cnt].dir_usc, &vettElementi[cnt].req_prec, &vettElementi[cnt].req_fin, &vettElementi[cnt].valore, &vettElementi[cnt].difficolta)!=8){
            printf("Errore nell'acquisizione degli elementi!\n");
            exit(1);
        }
        cnt++;
    }
    *pVettElementi = vettElementi;
    return nElem;
}

void sequenzaMaxGreedy(elemento_s *vettElementi, int nElem){
    programma_s migliore;
    listaDiag_s listaDiag;
    stampaMigliore(migliore);
}

void mergeSort(elemento_s *vettElementi, int nElem){
    elemento_s *aus = (elemento_s*)malloc(nElem*sizeof(elemento_s));
    mergeSort_r(vettElementi, aus, 0, nElem-1);
    free(aus);
}

void mergeSort_r(elemento_s *val, elemento_s *aus, int l, int r){
    int m;
    if(l>=r){
        return;
    }
    m=(l+r)/2;
    mergeSort_r(val, aus, l, m);
    mergeSort_r(val, aus, m+1, r);
    merge(val,aus,l,m,r);
}

void merge(elemento_s *val, elemento_s *aus, int l, int m, int r){
    int i=0, j=m, k; //K scorre sul vettore ausiliario, i sul vettore sinistro e j sul destro
    for(k=l; k<=r; k++){
        if(i>m){ //Finito vettore sinistro
            aus[k] = val[j++]; //Riempo l'ausiliario con tutto il destro
        }
        if(j>r){ //Finito vettore destro
            aus[k] = val[i++]; //Riempo l'ausiliario con tutto il sinistro
        }
        if(confrontaElem(val[i], val[j]) <= 0){
            aus[k] = val[i++];
        }
        else{
            aus[k] = val[j++];
        }
    }
    for(k=0;k<=r;k++){
        val[k] = aus[k];
    }
}


void stampaMigliore(programma_s migliore){
    printf("DD = %d DP = %d\n",DD,DP);
    printf("TOT = %.3f\n", migliore.punteggioProg);
    for(int i=0; i<3; i++){
        if(i==2 && migliore.bonus == 1){
            printf("DIAG #%d > %.3f * 1.5 (BONUS)\n", i+1, (migliore.diagonali[i].valoreDiag)/1.5);
        }
        else {
            printf("DIAG #%d > %.3f\n", i + 1, migliore.diagonali[i].valoreDiag);
        }
        for(int j=0; j<migliore.diagonali[i].nElementi; j++){
            printf("%s ", migliore.diagonali[i].nomiElementi[j]);
        }
        printf("\n");
    }
}

int confrontaElem(elemento_s e1, elemento_s e2){
    float rapporto1, rapporto2;
    rapporto1 = e1.valore/((float)e1.difficolta);
    rapporto2 = e2.valore/((float)e2.difficolta);
    if(rapporto1<rapporto2)
        return -1;
    else if(rapporto1 == rapporto2)
        return 0;
    return 1;
}
