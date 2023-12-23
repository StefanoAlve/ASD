#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXC 100
#define DD 10
#define DP 20
#define DBG 0
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
void sequenzaMax(elemento_s *vettElementi, int nElem);
listaDiag_s diagonaliPossibili(elemento_s *vettElementi, int nElem);
void nodeInsert(listaDiag_s *plistaDiag, diagonale_s diagonale);
listaDiag_s listaInit();
void stampaDiag(diagonale_s diagonale);
int diagPos_r(elemento_s sol[], elemento_s *vettElementi, int k, int n, int pos, listaDiag_s *plistaDiag, int cnt, diagonale_s diagonale);
diagonale_s creaDiag(elemento_s *vettElementi, int nElementi, diagonale_s diagonale);
int verificaElem(elemento_s *sol, elemento_s elementoIns, int pos, int dimMax);
programma_s trovaMigliore(listaDiag_s listaDiag);
void trovaMigliore_r(listaDiag_s listaDiag,link sol[],programma_s *pmigliore, int k,int pos);
int confrontaMax(link sol[], programma_s migliore);
void aggiornaMigliore(link sol[], programma_s *pmigliore);
int accettabile(link sol[]);
float calcolaPunteggioSol(link sol[]);
programma_s programmaInit();
diagonale_s diagonaleInit();
void stampaMigliore(programma_s migliore);
void deallocaLista(listaDiag_s listaDiag);
void deallocaAll(listaDiag_s listaDiag, elemento_s *vettElementi);

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
        if(fscanf(fp,"%s %d %d %d %d %d %f %d", vettElementi[cnt].nome, &vettElementi[cnt].tipologia, &vettElementi[cnt].dir_ing, &vettElementi[cnt].dir_usc, &vettElementi[cnt].req_prec, &vettElementi[cnt].req_fin, &vettElementi[cnt].valore, &vettElementi[cnt].difficolta)!=8){
            printf("Errore nell'acquisizione degli elementi!\n");
            exit(1);
        }
        cnt++;
    }
    *pVettElementi = vettElementi;
    return nElem;
}

void sequenzaMax(elemento_s *vettElementi, int nElem){
    programma_s migliore;
    listaDiag_s listaDiag;
    listaDiag = diagonaliPossibili(vettElementi,nElem);
    migliore = trovaMigliore(listaDiag);
    stampaMigliore(migliore);
    deallocaAll(listaDiag, vettElementi);
}

void deallocaAll(listaDiag_s listaDiag, elemento_s *vettElementi){
    deallocaLista(listaDiag);
    free(vettElementi);
}

listaDiag_s diagonaliPossibili(elemento_s *vettElementi, int nElem) {
    listaDiag_s listaDiag = listaInit();
    elemento_s sol[5];
    diagonale_s diagonale = diagonaleInit();
    for (int i = 1; i <= 5; i++) {
        listaDiag.nDiag = listaDiag.nDiag + diagPos_r(sol, vettElementi, i, nElem, 0, &listaDiag, 0, diagonale);
    }
    #if DBG
    printf("DIAGONALI POSSIBILI: %d\n", listaDiag.nDiag);
    #endif
    return listaDiag;
}

listaDiag_s listaInit(){
    listaDiag_s listaDiag;
    listaDiag.head = NULL;
    listaDiag.tail = NULL;
    listaDiag.nDiag = 0;
    return listaDiag;
}

diagonale_s creaDiag(elemento_s *vettElementi, int nElementi, diagonale_s diagonale){
    int count = 0; //Mi serve per identificare eventuali sequenze acrobatiche
    for(int j=0; j<3; j++){
        diagonale.acrobatici[j] = 0;
    }
    diagonale.nElementi = nElementi;
    for(int i=0;i<nElementi;i++){
        strcpy(diagonale.nomiElementi[i], vettElementi[i].nome);
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
        if(vettElementi[nElementi-1].difficolta >= 8){
            diagonale.bonus = 1;
        }
        diagonale.difDiag+=vettElementi[i].difficolta;
        diagonale.valoreDiag+=vettElementi[i].valore;
    }
    return diagonale;
}

link new_node(diagonale_s diagonale, link next){
    link node;
    node = (link)malloc(sizeof(struct node));
    node->next = next;
    node->diagonale = diagonale;
    return node;
}

void nodeInsert(listaDiag_s *plistaDiag, diagonale_s diagonale){
    link node = new_node(diagonale, NULL);
    if(plistaDiag->head == NULL){
        plistaDiag->head = node;
        plistaDiag->tail = node;
    }
    else{
        plistaDiag->tail->next = node;
        plistaDiag->tail = node;
    }
    plistaDiag->nDiag++;
}

void deallocaLista(listaDiag_s listaDiag){
    link corrente=listaDiag.head, successivo;
    while(corrente!=NULL){
        successivo = corrente->next;
        free(corrente);
        corrente = successivo;
    }
}

int diagPos_r(elemento_s sol[], elemento_s *vettElementi, int k, int n, int pos, listaDiag_s *plistaDiag, int cnt, diagonale_s diagonale){
    if(pos >= k){
        diagonale = creaDiag(sol, k, diagonale);
        if(diagonale.acrobatici[0]==0 || diagonale.difDiag > DD){
            return cnt;
        }
        #if DBG
        stampaDiag(diagonale);
        #endif
        nodeInsert(plistaDiag,diagonale);
        return cnt+1;
    }
    for(int i=0; i<n; i++){
        if(verificaElem(sol, vettElementi[i], pos, k)){
            sol[pos] = vettElementi[i];
            cnt = diagPos_r(sol, vettElementi, k, n, pos+1, plistaDiag, cnt, diagonale);
        }
    }
    return cnt;
}

int verificaElem(elemento_s *sol, elemento_s elementoIns, int pos, int dimMax) {
    if (pos == 0) {
        if (elementoIns.dir_ing != 1 || elementoIns.req_prec != 0 || (elementoIns.req_fin != 0 && dimMax > 1)) {
            return 0;
        }
    } else if (pos == dimMax-1) {
        if (elementoIns.dir_ing != sol[pos - 1].dir_usc) {
            return 0;
        }
    } else {
        if (sol[pos - 1].dir_usc != elementoIns.dir_ing || elementoIns.req_fin == 1) {
            return 0;
        }
    }
    return 1;
}

programma_s trovaMigliore(listaDiag_s listaDiag){
    programma_s migliore = programmaInit();
    link sol[3];
    trovaMigliore_r(listaDiag,sol,&migliore,3,0);
    return migliore;
}

void trovaMigliore_r(listaDiag_s listaDiag,link sol[],programma_s *pmigliore, int k,int pos){
    link corrente;
    int diffTot=0;
    if(pos>=k){
        if(accettabile(sol)) {
            if (confrontaMax(sol, *pmigliore)) {
                aggiornaMigliore(sol, pmigliore);
            }
        }
        return;
    }
    for(corrente = listaDiag.head; corrente != NULL; corrente = corrente->next){
        for(int i=0; i<pos; i++){
            diffTot+=sol[i]->diagonale.difDiag;
        }
        if(diffTot+corrente->diagonale.difDiag <= DP) {
            sol[pos] = corrente;
            trovaMigliore_r(listaDiag, sol, pmigliore, k, pos + 1);
        }
        diffTot = 0;
    }
}

int confrontaMax(link sol[], programma_s migliore){
    float punteggioSol;
    punteggioSol = calcolaPunteggioSol(sol);
    if(punteggioSol<migliore.punteggioProg){
        return 0;
    }
    return 1;
}
void aggiornaMigliore(link sol[], programma_s *pmigliore){
    pmigliore->difProg = sol[0]->diagonale.difDiag+sol[1]->diagonale.difDiag+sol[2]->diagonale.difDiag;
    pmigliore->diagonali[0] = sol[0]->diagonale;
    pmigliore->diagonali[1] = sol[1]->diagonale;
    pmigliore->diagonali[2] = sol[2]->diagonale;
    pmigliore->punteggioProg=sol[0]->diagonale.valoreDiag+sol[1]->diagonale.valoreDiag;
    if(pmigliore->diagonali[2].bonus == 1){
        pmigliore->punteggioProg+=(float)((sol[2]->diagonale.valoreDiag)*1.5);
        pmigliore->bonus = 1;
    }
    else {
        pmigliore->punteggioProg += sol[2]->diagonale.valoreDiag;
    }
}
int accettabile(link sol[]){
    int acrobatici = 0, avanti = 0, indietro = 0, flagDueAcrob=0;
    for(int i=0; i<3; i++){
        acrobatici += sol[i]->diagonale.acrobatici[0];
        if(sol[i]->diagonale.sequenza == 1){
            flagDueAcrob = 1;
        }
        avanti += sol[i]->diagonale.acrobatici[1];
        indietro += sol[i]->diagonale.acrobatici[2];
    }
    if(flagDueAcrob == 1 && avanti >= 1 && indietro >= 1 && acrobatici >= 3){
        return 1;
    }
    return 0;
}
float calcolaPunteggioSol(link sol[]){
    float punteggio;
    punteggio = sol[0]->diagonale.valoreDiag + sol[1]->diagonale.valoreDiag;
    if(sol[2]->diagonale.bonus == 1){
        punteggio += (float)((sol[2]->diagonale.valoreDiag) * 1.5);
    }
    else{
        punteggio+= sol[2]->diagonale.valoreDiag;
    }
    return punteggio;
}

programma_s programmaInit(){
    programma_s programma;
    programma.punteggioProg = 0;
    programma.bonus = 0;
    programma.difProg = 0;
    return programma;
}

diagonale_s diagonaleInit(){
    diagonale_s diagonale;
    diagonale.valoreDiag=0;
    diagonale.acrobatici[0]= diagonale.acrobatici[1]=diagonale.acrobatici[2]=0;
    diagonale.difDiag=0;
    diagonale.nElementi=0;
    diagonale.sequenza=0;
    diagonale.bonus = 0;
    return diagonale;
}

void stampaMigliore(programma_s migliore){
    printf("DD = %d DP = %d\n",DD,DP);
    printf("TOT = %.3f\n", migliore.punteggioProg);
    for(int i=0; i<3; i++){
        if(i==2 && migliore.bonus == 1){
            printf("DIAG #%d > %.3f * 1.5 (BONUS)\n", i+1, migliore.diagonali[i].valoreDiag);
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

void stampaDiag(diagonale_s diagonale){
    printf("Esercizi: ");
    for(int i=0; i<diagonale.nElementi; i++){
        printf("%s ", diagonale.nomiElementi[i]);
    }
    printf("\n");
    printf("DIFFICOLTA': %d\n",diagonale.difDiag);
    printf("NUMERO ACROBATICI: %d, AVANTI: %d, INDIETRO: %d\n", diagonale.acrobatici[0],diagonale.acrobatici[1], diagonale.acrobatici[2]);
    printf("SEQUENZA: %d\n", diagonale.sequenza);
    printf("VALORE: %.2f\n", diagonale.valoreDiag);
    printf("BONUS: %d\n\n", diagonale.bonus);
}