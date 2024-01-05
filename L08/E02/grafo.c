#include "grafo.h"

struct grafo_s{
    int nVertici;
    int nArchi;
    int **mAdiac;
    link *listAdiac;
    link sentinella;
    ST tabSimboli;
};

int** mInit(int r, int c, int val) {
    int **matrice;
    matrice = (int**)malloc(r*sizeof(int*));
    for(int i=0; i<r; i++){
        matrice[i] = (int*)malloc(c*sizeof(int));
        for(int j=0; j<c; j++){
            matrice[i][j] = val;
        }
    }
    return matrice;
}
void listaInit(int n, pgrafo_s pGrafo){
    pGrafo->listAdiac = (link*)malloc(n*sizeof(link));
    pGrafo->sentinella = newNode(-1, -1, NULL);
    for(int i=0; i<n; i++){
        pGrafo->listAdiac[i] = pGrafo->sentinella;
    }
}
pgrafo_s grafoInit(int n){
    pgrafo_s grafo;
    grafo = (pgrafo_s)malloc(sizeof(struct grafo_s));
    grafo->mAdiac = mInit(n,n, 0);
    grafo->tabSimboli = STInit(n);
    grafo->nVertici = 0;
    grafo->nArchi = n/2;
    return grafo;
}

void riempiGrafo(pgrafo_s pGrafo, char nomeFile[]){
    FILE *fp;
    fp=fopen(nomeFile, "r");
    char elab1[MAXC], rete1[MAXC], elab2[MAXC], rete2[MAXC];
    int flusso, iV1, iV2, iR1, iR2;
    arco_s *vettArchi = (arco_s*)malloc(pGrafo->nArchi*sizeof(arco_s)); //TODO deallocare
    if(fp==NULL){
        printf("Errore nell'apertura del file!\n");
        exit(1);
    }
    while(fscanf(fp, "%s %s %s %s %d", elab1,rete1,elab2,rete2,&flusso) == 5){
        iV1 = STsearchIndexElab(pGrafo->tabSimboli, elab1);
        if(iV1 == -1){
            STinsertElab(pGrafo->tabSimboli, elab1, STcount(pGrafo->tabSimboli)+1);
            iV1 = STcount(pGrafo->tabSimboli);
        }
        iV2 = STsearchIndexElab(pGrafo->tabSimboli, elab2);
        if(iV2 == -1){
            STinsertElab(pGrafo->tabSimboli, elab2, STcount(pGrafo->tabSimboli)+1);
            iV2 = STcount(pGrafo->tabSimboli);
        }
        pGrafo->mAdiac[iV1][iV2] = flusso;
        pGrafo->mAdiac[iV2][iV1] = flusso;
        iR1 = STsearchIndexReti(pGrafo->tabSimboli, rete1);
        if(iR1 == -1){
            STinsertElab(pGrafo->tabSimboli, rete1, STcount(pGrafo->tabSimboli)+1);
        }
        iR2 = STsearchIndexReti(pGrafo->tabSimboli, rete2);
        if(iR2 == -1){
            STinsertElab(pGrafo->tabSimboli, rete2, STcount(pGrafo->tabSimboli)+1);
        }
    }
    generaArchi(pGrafo,vettArchi);
    fclose(fp);
}

void distruggiGrafo(pgrafo_s pGrafo){
    freeM(pGrafo->mAdiac);
    free(pGrafo->tabSimboli);
    freeL(pGrafo->listAdiac);
    free(pGrafo);
}
void elencaAlfabetico(pgrafo_s pGrafo){ //TODO

}
int verificaAdiacCoppM(pgrafo_s pGrafo, char v1[MAXC], char v2[MAXC], char v3[MAXC]){ //TODO

}
int verificaAdiacCoppL(pgrafo_s pGrafo, char v1[MAXC], char v2[MAXC], char v3[MAXC]){ //TODO

}
link newNode(int vertice, int flusso, link next){
    link x = (link)malloc(sizeof(*x));
    x->vertice = vertice;
    x->flusso = flusso;
    x->next = next;
    return x;
}
arco_s creaArco(int v1,int v2, int flusso){
    arco_s arco;
    arco.v1=v1;
    arco.v2=v2;
    arco.flusso=flusso;
    return arco;
}
void generaArchi(pgrafo_s pGrafo, arco_s *vettArchi){
    int i, j, E=0;
    for(i=0; i<pGrafo->nVertici; i++){
        for(j=i+1;j<pGrafo->nVertici;j++){
            if(pGrafo->mAdiac[i][j] != 0){
                vettArchi[E++] = creaArco(i,j,pGrafo->mAdiac[i][j]);
            }
        }
    }
    pGrafo->nArchi = E;
}
void insertE(pgrafo_s pGrafo, arco_s arco){
    int v1=arco.v1, v2=arco.v2, flusso = arco.flusso;
    pGrafo->listAdiac[v1] = newNode(v2, flusso, pGrafo->listAdiac[v1]);
    pGrafo->listAdiac[v2] = newNode(v1, flusso, pGrafo->listAdiac[v2]);
}
void generaListaAdiac(pgrafo_s pGrafo, arco_s* vettArchi){
    listaInit(pGrafo->nVertici, pGrafo);
    for(int i=0; i<pGrafo->nArchi; i++){
        insertE(pGrafo, vettArchi[i]);
    }
}

void freeM(int** M); //TODO
void freeL(link* head); //TODO