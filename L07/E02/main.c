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
    int rec_fin;
    float valore;
    int difficolta;
}elemento_s;
typedef struct{
    elemento_s *elementi;
    int difDiag;
    int nElementi;
    int acrobatici[3]; //Vett di int, indica in pos 0 quanti elementi acrobatici sono presenti, in 1 quanti in avanti e in 2 quanti indietro
    int sequenza; //1 se è presente una sequenza di almeno due elementi acrobatici
    float valoreDiag;
}diagonale_s;

typedef struct{
    diagonale_s *diagonali[3];
    int difProg;
    int accettabile;
    int bonus;
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
void sequenzaMax(elemento_s *vettElementi, int nElem);
listaDiag_s diagonaliPossibili(elemento_s *vettElementi, int nElem);
void deallocaAll(programma_s programma);
void nodeInsert(listaDiag_s listaDiag, diagonale_s diagonale);
void deallocaLista(listaDiag_s listaDiag);
listaDiag_s listaInit();
int diagPos_r(elemento_s sol[], elemento_s *vettElementi, int k, int n, int pos, listaDiag_s listaDiag, int cnt);
diagonale_s creaDiag(elemento_s *vettElementi, int nElementi);


int main() {
    elemento_s *vettElementi;
    int nElem;
    nElem=leggiElementi(&vettElementi);
    sequenzaMax(vettElementi, nElem);
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
        if(fscanf(fp,"%s %d %d %d %d %d %f %d", vettElementi[cnt].nome, &vettElementi[cnt].tipologia, &vettElementi[cnt].dir_ing, &vettElementi[cnt].dir_usc, &vettElementi[cnt].req_prec, &vettElementi[cnt].rec_fin, &vettElementi[cnt].valore, &vettElementi[cnt].difficolta)!=8){
            printf("Errore nell'acquisizione degli elementi!\n");
            exit(1);
        }
        cnt++;
    }
    *pVettElementi = vettElementi;
    return nElem;
}

void sequenzaMax(elemento_s *vettElementi, int nElem){
    //tutte le diagonali possibili (disp_rep) //TODO
    diagonaliPossibili(vettElementi,nElem);
    //trova programma massimo accettabile (comb_rep) //TODO
}

void deallocaAll(programma_s programma){ //TODO
    //Dealloca elementi
}

listaDiag_s diagonaliPossibili(elemento_s *vettElementi, int nElem){
    listaDiag_s listaDiag = listaInit();
    elemento_s sol[5];
    for(int i = 1; i <= 5; i++){
        listaDiag.nDiag += diagPos_r(sol, vettElementi, i, nElem, 0, listaDiag, 0);
    }
    return listaDiag;
}

listaDiag_s listaInit(){
    listaDiag_s listaDiag;
    listaDiag.head = NULL;
    listaDiag.tail = NULL;
    listaDiag.nDiag = 0;
    return listaDiag;
}

diagonale_s creaDiag(elemento_s *vettElementi, int nElementi){
    int count; //Mi serve per identificare eventuali sequenze acrobatiche
    diagonale_s diagonale;
    diagonale.elementi = (elemento_s*)malloc(nElementi*sizeof(elemento_s));
    diagonale.nElementi = nElementi;
    for(int i=0;i<nElementi;i++){
        diagonale.elementi[i] = vettElementi[i];
        if(vettElementi[i].tipologia == 2){
            diagonale.acrobatici[0]++;
            diagonale.acrobatici[1]++;
            count++;
        }
        else if(vettElementi[i].tipologia == 1) {
            diagonale.acrobatici[0]++;
            diagonale.acrobatici[2]++;
            count++;
        }
        if(count == 2){
            diagonale.sequenza = 1;
        }
        diagonale.difDiag+=vettElementi[i].difficolta;
        diagonale.valoreDiag+=vettElementi[i].valore;
    }
}

link new_node(diagonale_s diagonale, link next){
    link node;
    node = (link)malloc(sizeof(*node));
    node->next = next;
    node->diagonale = diagonale;
    return node;
}

void nodeInsert(listaDiag_s listaDiag, diagonale_s diagonale){
    link node = new_node(diagonale, NULL);
    if(listaDiag.head == NULL){
        listaDiag.head = node;
        listaDiag.tail = node;
    }
    else{
        listaDiag.tail->next = node;
        listaDiag.tail = node;
    }
    listaDiag.nDiag++;
}

void deallocaLista(listaDiag_s listaDiag){
    link corrente=listaDiag.head, successivo;
    while(corrente!=NULL){
        successivo = corrente->next;
        free(corrente->diagonale.elementi);
        free(corrente);
        corrente = successivo;
    }
}

int diagPos_r(elemento_s sol[], elemento_s *vettElementi, int k, int n, int pos, listaDiag_s listaDiag, int cnt){
    if(pos >= k){
        diagonale_s diagonale = creaDiag(sol, k); //TODO
        //creaDiagonale
        nodeInsert(listaDiag,diagonale);
        return cnt+1;
    }
    for(int i=0; i<n; i++){
        if(accettabile(sol[pos-1], vettElementi[i])){ //TODO
            sol[pos] = vettElementi[i];
            cnt = diagPos_r(sol, vettElementi, k, n, pos+1, listaDiag, cnt);
        }
    }
    return cnt;
}