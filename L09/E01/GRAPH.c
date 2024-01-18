#include "GRAPH.h"
///UTILIZZO APPROCCIO CON LISTA DELLE ADIACENZE
static link newNode(int v, int peso, link next);
static arco_s EDGEcreate(int v1, int v2, int peso);
static void insertE(Graph grafo, arco_s arco);
static void removeE(Graph grafo, arco_s arco);
static void dfsR(Graph grafo, arco_s arco, int *time, int *pre, int *post, int *st, int *flag);
static void combSempl(arco_s *vettArchi, arco_s *solTMP, arco_s *solBEST, int n, int k, int pos, int start, int *pesoMAX, int *flag, Graph grafo);
static int contaPeso(int E, arco_s *vettArchi);
static void TSdfsR(Graph dag, int v, int *ts, int *pre, int *time);

struct grafo_s{
    int nVert;
    int nArchi;
    link *ladj;
    ST tabSimboli;
    link z;
};

static link newNode(int v, int peso, link next){
    link x = (link)malloc(sizeof(*x));
    x->vertice = v;
    x->peso = peso;
    x->next = next;
    return x;
}

static arco_s EDGEcreate(int v1, int v2, int peso){
    arco_s arco;
    arco.v1 = v1;
    arco.v2 = v2;
    arco.peso = peso;
    return arco;
}

void listaInit(Graph grafo){
    grafo->ladj = (link*)malloc(grafo->nVert*sizeof(link)); //vettore di liste
    for(int i=0; i<grafo->nVert; i++){
        grafo->ladj[i] = grafo->z;
    }
}

void listaFree(Graph grafo){
    link x, successivo;
    for(int i=0; i<grafo->nVert; i++){
        x=grafo->ladj[i];
        while(x!=grafo->z){
            successivo = x->next;
            free(x);
            x = successivo;
        }
    }
    free(grafo->ladj);
}
Graph GRAPHInit(int n){
    Graph grafo = (Graph)malloc(sizeof(*grafo));
    grafo->nVert = n;
    grafo->nArchi = 0;
    grafo->z = newNode(-1,-1,NULL);
    listaInit(grafo);
    grafo->tabSimboli = STInit(n);
    return grafo;
}
void GRAPHfree(Graph grafo){
    STfree(grafo->tabSimboli);
    listaFree(grafo);
    free(grafo->z);
    free(grafo);
}
Graph GRAPHload(FILE *fin){
    int nVert, peso, id1, id2;
    char name1[MAXC], name2[MAXC];
    Graph grafo;
    fscanf(fin, "%d", &nVert);
    grafo = GRAPHInit(nVert);
    for(int i=0; i<nVert; i++){
        fscanf(fin,"%s", name1);
        STinsert(grafo->tabSimboli, name1);
    }
    while(fscanf(fin, "%s %s %d", name1,name2,&peso) == 3){
        id1 = STgetIndex(grafo->tabSimboli, name1);
        id2 = STgetIndex(grafo->tabSimboli, name2);
        if(id1 >= 0 && id2 >= 0){
            GRAPHinsertE(grafo, id1, id2, peso);
        }
    }
    return grafo;
}

void GRAPHstore(Graph grafo, FILE *fout){
    int i;
    arco_s *vettArchi;

    vettArchi = (arco_s*)malloc(grafo->nArchi * sizeof(*vettArchi));

    GRAPHedges(grafo,vettArchi);
    fprintf(fout, "\nNumero di vertici: %d\n", grafo->nVert);
    for(i=0; i < grafo->nVert; i++){
        fprintf(fout, "%s\n", STsearchByIndex(grafo->tabSimboli, i));
    }
    fprintf(fout, "\nNumero di archi: %d\n", grafo->nArchi);
    for(i=0; i<grafo->nArchi; i++){
        fprintf(fout, "%s %s %d\n", STsearchByIndex(grafo->tabSimboli, vettArchi[i].v1), STsearchByIndex(grafo->tabSimboli, vettArchi[i].v2), vettArchi[i].peso);
    }
}

int GRAPHgetIndex(Graph grafo, char name[]){
    return STgetIndex(grafo->tabSimboli,name);
}
void GRAPHinsertE(Graph grafo, int id1, int id2, int peso){
    insertE(grafo, EDGEcreate(id1, id2, peso));
}
void GRAPHremoveE(Graph grafo, int id1, int id2){
    removeE(grafo, EDGEcreate(id1, id2, -1));
}
void GRAPHedges(Graph grafo, arco_s *archi){
    int i, nArchi = 0;
    link t;
    for(i=0; i<grafo->nVert; i++){
        for(t=grafo->ladj[i]; t!=grafo->z; t=t->next){
            archi[nArchi++] = EDGEcreate(i, t->vertice, t->peso);
        }
    }
}

static void insertE(Graph grafo, arco_s arco){
    int v1 = arco.v1, v2 = arco.v2, peso = arco.peso;
    grafo->ladj[v1] = newNode(v2,peso,grafo->ladj[v1]);
    grafo->nArchi++;
}
static void removeE(Graph grafo, arco_s arco){
    int v = arco.v1, w = arco.v2;
    link x, p;
    for(x=grafo->ladj[v], p=NULL; x!=grafo->z; p=x, x=x->next){
        if(x->vertice == w) {
            if (x == grafo->ladj[v]) {
                grafo->ladj[v] = x->next;
            } else {
                p->next = x->next;
            }
        }
    }
    if(x!=NULL && x!=grafo->z){
        free(x);
    }
    grafo->nArchi--;
}

int GRAPHdfs(Graph grafo, int id){
    int time = 0, *pre, *post, *st;
    int flag = 0;
    pre = (int*)malloc(grafo->nVert*sizeof(int));
    post = (int*)malloc(grafo->nVert*sizeof(int));
    st = (int*)malloc(grafo->nVert*sizeof(int));
    for(int i = 0; i < grafo->nVert; i++){ //inizializzazione 0(V)
        pre[i] = post[i] = st[i] = -1;
    }
    dfsR(grafo, EDGEcreate(id, id, -1), &time, pre, post, st, &flag);
    // Archi cross e forward (vertici non ancora scoperti)
    for(int i = 0; i < grafo->nVert; i++){
        if(pre[i] == -1)
            dfsR(grafo, EDGEcreate(i, i, -1), &time, pre, post, st, &flag);
    }
    free(pre); free(post); free(st);
    return flag;
}


static void dfsR(Graph grafo, arco_s arco, int *time, int *pre, int *post, int *st, int *flag){
    link t;
    int v, v2 = arco.v2; // con cosa è connesso v
    st[arco.v2] = arco.v1; // il padre di w è v
    pre[v2] = (*time)++;
    for(t = grafo->ladj[v2]; t!=grafo->z && !(*flag); t = t->next)
    {
        if (pre[t->vertice] == -1)
            dfsR(grafo, EDGEcreate(v2, t->vertice, -1), time, pre, post, st, flag);
        else
        {
            v = t->vertice;
            if(post[v] == -1)
            {
                //printf("\nARCO BACK TROVATO TRA %d e %d", w, v);
                *flag = 1;
            }
        }
    }
    post[v2] = (*time)++;
}


Graph searchForMinCardinality(Graph grafo){
    arco_s *vettArchi = (arco_s*)malloc(grafo->nArchi * sizeof(arco_s)), *solBEST, *solTMP;
    solBEST = (arco_s*)malloc((grafo->nArchi)*sizeof(arco_s));
    solTMP =  (arco_s*)malloc((grafo->nArchi)*sizeof(arco_s));
    Graph DAG;
    int peso=0, flag=0,i, rimossi;
    GRAPHedges(grafo, vettArchi);
    printf("\nGli insiemi di cardinalita' minima la cui rimozione renda il grafo un DAG sono:\n");
    for(i = 0; i<grafo->nArchi && !flag; i++){
        combSempl(vettArchi, solTMP, solBEST, grafo->nArchi, i, 0, 0, &peso, &flag, grafo);
        rimossi=i;
    }
    if(rimossi == 0 && flag){
        printf("\nIl grafo risulta gia' un DAG\n");
        return grafo;
    }
    else if(rimossi>0 && flag) {
        printf("\nL'insieme a peso massimo pari a %d e cardinalita' minima che se rimosso genera un DAG risulta:\n",
               contaPeso(rimossi, solBEST));
        for (i = 0; i < rimossi; i++) {
            printf("( ");
            STprint(grafo->tabSimboli, solBEST[i].v1);
            printf(" ");
            STprint(grafo->tabSimboli, solBEST[i].v2);
            printf(" ) ");
        }
        DAG = grafo;
        for(i=0;i<rimossi; i++){
            GRAPHremoveE(DAG,solBEST[i].v1,solBEST[i].v2);
        }
        return DAG;
    }else{
        printf("\nNon è possibile generare un DAG\n");
    }
    free(solBEST);
    free(vettArchi);
    return NULL;
}

static void combSempl(arco_s *vettArchi, arco_s *solTMP, arco_s *solBEST, int n, int k, int pos, int start, int *pesoMAX, int *flag, Graph grafo){
    int i, peso;
    if(pos>=k){
        for(i=0; i<k; i++){
            GRAPHremoveE(grafo, solTMP[i].v1, solTMP[i].v2);
        }
        if(!GRAPHdfs(grafo, 0)){
            for(i=0; i<k;i++){
                printf("( ");
                STprint(grafo->tabSimboli, solTMP[i].v1);
                printf(" ");
                STprint(grafo->tabSimboli, solTMP[i].v2);
                printf(" ) ");
            }
            printf("\n");
            *flag = 1;
            peso = contaPeso(k, solTMP);
            if(peso > *pesoMAX){
                *pesoMAX = peso;
                for(i=0;i<k;i++){
                    solBEST[i] = solTMP[i];
                }
            }
        }
        for(i=0;i<k;i++){
            GRAPHinsertE(grafo, solTMP[i].v1, solTMP[i].v2, solTMP[i].peso);
        }
        return;
    }
    for(i=start;i<n;i++){
        solTMP[pos] = vettArchi[i];
        combSempl(vettArchi, solTMP, solBEST, n, k, pos+1, i+1, pesoMAX, flag, grafo);
    }
}

static int contaPeso(int E, arco_s *vettArchi){
    int i, pesoTot=0 ;
    for(i=0; i<E; i++){
        pesoTot += vettArchi[i].peso;
    }
    return pesoTot;
}

static void TSdfsR(Graph dag, int v, int *ts, int *pre, int *time){
    link t; pre[v] = 0;
    for(t=dag->ladj[v]; t!=dag->z; t=t->next){
        if(pre[t->vertice] == -1){
            TSdfsR(dag, t->vertice, ts, pre, time);
        }
    }
    ts[(*time)++] = v;
}

void GRAPHcamminoMax(Graph G){
    int v, time = 0, *pre, *ts, *maximumPaths;
    link t;
    pre = malloc(G->nVert * sizeof(int));
    ts = malloc(G->nVert * sizeof(int));
    maximumPaths = malloc(G->nVert * sizeof(int));
    for (v=0; v < G->nVert; v++) { pre[v] = -1; ts[v] = -1; maximumPaths[v] = 0;}
    // ordinamento dei vertici in ordine topologico
    for (v=0; v < G->nVert; v++)
        if (pre[v]== -1) TSdfsR(G, v, ts, pre, &time);
    // calcolo dei cammini massimo attraverso relaxation inversa
    for (v=G->nVert - 1; v >= 0; v--) {
        for (t = G->ladj[ts[v]]; t != NULL; t = t->next) {
            if(maximumPaths[ts[v]] + t->peso > maximumPaths[t->vertice])
                maximumPaths[t->vertice] = maximumPaths[ts[v]] + t->peso;
        }
    }
    printf("\n\n\nNodi in ordine topologico:\n");
    for (v=G->nVert - 1; v >= 0; v--) {
        STprint(G->tabSimboli, ts[v]);
        printf(" ");
    }


    printf("\n\nCammini massimi a partire dalle sorgenti:\n");
    for (v=G->nVert - 1; v >= 0; v--) {
        printf("Nodo: ");
        STprint(G->tabSimboli, ts[v]);
        if(maximumPaths[ts[v]] == 0)
            printf("  sorgente\n");
        else
            printf("   %3d\n",maximumPaths[ts[v]]);
    }
    free(pre);
    free(ts);
    free(maximumPaths);
}

