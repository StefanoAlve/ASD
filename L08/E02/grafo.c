#include "grafo.h"

struct grafo_s{
    int nVertici;
    int nArchi;
    int **mAdiac;
    link *listAdiac;
    link sentinella;
    ST tabSimboli;
};

int** mInit(int n, int val); //TODO
link* listaInit(int n); //TODO
pgrafo_s grafoInit(int n){
    pgrafo_s grafo;
    grafo = (pgrafo_s)malloc(sizeof(struct grafo_s));
    grafo->mAdiac = mInit(n, 0);
    grafo->tabSimboli = STInit(n);
    grafo->nVertici = 0;
    grafo->nArchi = 0;
    return grafo;
}

void riempiGrafo(pgrafo_s pGrafo, char nomeFile[]){
    FILE *fp;
    fp=fopen(nomeFile, "r");
    char elab1[MAXC], rete1[MAXC], elab2[MAXC], rete2[MAXC];
    int flusso, iV1, iV2, iR1, iR2;
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
    fclose(fp);
}

void distruggiGrafo(pgrafo_s pGrafo){
    freeM(pGrafo->mAdiac); //TODO
    free(pGrafo->tabSimboli);
    freeL(pGrafo->listAdiac); //TODO
    free(pGrafo);
}
void elencaAlfabetico(pgrafo_s pGrafo){ //TODO

}
int verificaAdiacCoppM(pgrafo_s pGrafo, char v1[MAXC], char v2[MAXC], char v3[MAXC]){ //TODO
}
int verificaAdiacCoppL(pgrafo_s pGrafo, char v1[MAXC], char v2[MAXC], char v3[MAXC]){ //TODO

}
void generaListaAdiac(pgrafo_s pGrafo){ //TODO

}