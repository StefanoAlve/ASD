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
    grafo->sentinella = newNode(-1, -1, NULL);
    grafo->nVertici = 0;
    grafo->nArchi = n/2;
    return grafo;
}

void GraphLoad(pgrafo_s G, char *filename){
    char id_elab1[MAXC], id_elab2[MAXC],id_rete1[MAXC],id_rete2[MAXC];
    int wt, E = 0;
    FILE *fp = fopen(filename, "r");
    if(fp != NULL)
    {
        while(fscanf(fp, "%s %s %s %s %d", id_elab1, id_rete1, id_elab2, id_rete2, &wt) == 5){
            GRAPHinsertE(G, id_elab1, id_rete1, id_elab2, id_rete2, wt);
            E++;
        }
        STprint(G->tabSimboli);
        G->nArchi = E;
        G->nVertici = STcount(G->tabSimboli);
    }
    else
        printf("\nErrore nella lettura del file");
    fclose(fp);
}


void distruggiGrafo(pgrafo_s pGrafo, int flag){
    freeM(pGrafo);
    if(flag) {
        freeL(pGrafo);
    }
    STfree(pGrafo->tabSimboli);
    free(pGrafo);
}
void elencaAlfabetico(pgrafo_s pGrafo){
    int *vett = (int*)malloc(pGrafo->nVertici * sizeof(int)), i, j, v = pGrafo->nVertici;
    STsort(pGrafo->tabSimboli, vett);
    for(i = 0; i < v; i++)
    {
        printf("\n\nVertice %d): ", i+1);
        STprintName(pGrafo->tabSimboli, vett[i]); printf("\n");
        for(j = 0; j < v; j++)
        {
            if(pGrafo->mAdiac[vett[i]][vett[j]] != 0)
            {
                STprintName(pGrafo->tabSimboli, vett[j]);
                printf("- ");
            }
        }
    }
    free(vett);
}

void GRAPHinsertE(pgrafo_s G, char* id_elab1, char* id_rete1, char* id_elab2, char* id_rete2, int wt)
{
    int id1, id2;
    id1 = STgetIndex(G->tabSimboli, id_elab1, id_rete1);
    id2 = STgetIndex(G->tabSimboli, id_elab2, id_rete2);
    if(id1 == -1)
        id1 = STinsert(G->tabSimboli, id_elab1, id_rete1);
    if(id2 == -1)
        id2 = STinsert(G->tabSimboli, id_elab2, id_rete2);
    if(G->mAdiac[id1][id2] == 0) G->nArchi++; // aggiungo il nuovo arco se il peso precedente era zero nella matrice di adiacenza
    G->mAdiac[id1][id2] = wt;
    G->mAdiac[id2][id1] = wt;
}

void verificaAdiacCoppM(pgrafo_s pGrafo, char v1[MAXC], char v2[MAXC], char v3[MAXC]){
    int id1, id2, id3, flag = 0;
    id1 = STgetIndex(pGrafo->tabSimboli,v1,"");
    id2 = STgetIndex(pGrafo->tabSimboli,v2,"");
    id3 = STgetIndex(pGrafo->tabSimboli,v3,"");
    if(id1 >= 0 && id2 >= 0 && id3>=0)
        if(pGrafo->mAdiac[id1][id2] != 0 && pGrafo->mAdiac[id1][id3] != 0 && pGrafo->mAdiac[id2][id3] != 0)
            flag = 1;
    if(flag)
        printf("\nI vertici %s, %s, %s formano un sottografo completo.\n", v1, v2, v3);
    else
        printf("\nI vertici %s, %s, %s non formano un sottografo completo.\n", v1, v2, v3);
}

void verificaAdiacCoppL(pgrafo_s pGrafo, char v1[MAXC], char v2[MAXC], char v3[MAXC]){
    int id1, id2, id3, flag1 =0, flag2 = 0, flag3 = 0;
    link x, y, z;
    id1 = STgetIndex(pGrafo->tabSimboli, v1, "");
    id2 = STgetIndex(pGrafo->tabSimboli, v2, "");
    id3 = STgetIndex(pGrafo->tabSimboli, v3, "");
    if(id1 >= 0 && id2 >= 0 && id3>=0)
    {
        x = pGrafo->listAdiac[id1];
        y = pGrafo->listAdiac[id2];
        while(x!= pGrafo->sentinella){
            if(x->vertice == id2)
                flag1 = 1;
            if(x->vertice == id3)
                flag2 = 1;
            x = x->next;
        }
        while(y != pGrafo->sentinella && !flag3)
        {
            if(y->vertice == id3)
                flag3 = 1;
            y = y->next;
        }
        if(flag1*flag2*flag3 > 0)
            printf("\nI vertici %s, %s, %s formano un sottografo completo.\n", v1, v2, v3);
        else
            printf("\nI vertici %s, %s, %s non formano un sottografo completo.\n", v1, v2, v3);
    }
}

link newNode(int vertice, int flusso, link next){
    link x = (link)malloc(sizeof(*x));
    x->vertice = vertice;
    x->flusso = flusso;
    x->next = next;
    return x;
}
void print_matrix(pgrafo_s G){
    int i, j, v = G->nVertici;
    printf("\n");
    for(i = 0; i < v; i++)
    {
        for(j =0 ; j < v; j++)
            printf(" %d ", G->mAdiac[i][j]);
        printf("\n");
    }
}
void freeM(pgrafo_s pGrafo){
    for(int i = 0; i<pGrafo->nVertici; i++)
        free(pGrafo->mAdiac[i]);
    free(pGrafo->mAdiac);
}
void freeL(pgrafo_s pGrafo){
    link x;
    for(int i=0; i<pGrafo->nVertici; i++) {
        while (pGrafo->listAdiac[i] != pGrafo->sentinella) {
            x = pGrafo->listAdiac[i];
            pGrafo->listAdiac[i] = pGrafo->listAdiac[i]->next;
            free(x);
        }
    }
    free(pGrafo->listAdiac);
}

void GRAPHloadListAdj(pgrafo_s G){
    int v = G->nVertici, i, j;
    listaInit(G->nVertici,G);
    for(i = 0; i < v; i++)
    {
        for(j = 0; j < v; j++)
        {
            if(G->mAdiac[i][j]!=0){
                G->listAdiac[i] = newNode(j, G->mAdiac[i][j], G->listAdiac[i]);
            }
        }
    }

    link x;
    for(i = 0; i < v; i++)
    {
        printf("\n-Vertex %d:\n", i);
        x = G->listAdiac[i];
        while(x!= G->sentinella)
        {
            printf("id: %d; w:%d - ", x->vertice, x->flusso);
            x = x->next;
        }
    }
    printf("\n");
}
