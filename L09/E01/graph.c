#include "graph.h"


typedef struct node *link;
struct node{
    int v;
    int wt;
    link next;
};

struct graph{
    int V;
    int E;
    ST tab;
    link *ladj;
    link z;
};


static link NEW(int v, int wt, link next);
static void insertE(GRAPH G, Edge e);
static void removeE(GRAPH G, Edge e);
static Edge EdgeCreate(int v, int w, int wt);
static void dfsR(GRAPH G, Edge e, int *time, int *pre, int *post, int *st, int*flag);
static void combinazioni_sempliciR(Edge *a, Edge *solTMP, Edge *solBEST, int n, int k, int pos, int start, int *pesoMAX, int *flag, GRAPH G);
static int cont_num_vertex(int E, Edge *a);
static int calcola_peso(int E, Edge *a);

GRAPH GRAPHinit(int V)
{
    GRAPH x;
    x = (GRAPH)malloc(sizeof(*x));
    x->V = V;
    x->E = 0;
    x->tab = STinit(V);
    x->ladj = (link*)malloc(V*sizeof(link));
    x->z = NEW(-1, -1, NULL);
    for(int i = 0; i < V; i++)
        x->ladj[i] = x->z;
    return x;
}


static link NEW(int v, int wt, link next){
    link x;
    x = (link)malloc(sizeof(*x));
    x->v = v;
    x->wt = wt;
    x->next = next;
    return x;
}


GRAPH GRAPHload(FILE *fin)
{
    int V, i, id1, id2, wt;
    char tit1[MAXLEN], tit2[MAXLEN];
    GRAPH G = NULL;
    if(fin != NULL)
    {
        fscanf(fin, "%d", &V);
        G = GRAPHinit(V);
        for(i = 0; i < V; i++){
            fscanf(fin, "%s ", tit1);
            STinsert(G->tab, tit1);
        }
        while(fscanf(fin, "%s %s %d", tit1, tit2, &wt) == 3)
        {
            id1 = STgetIndex(G->tab, tit1);
            id2 = STgetIndex(G->tab, tit2);
            if(id1>=0 && id2 >= 0)
                GRAPHinsertE(G, EdgeCreate(id1, id2, wt));
        }
    }
    else
        printf("\nErrore nell'apertura del file.");
    return G;
}


static void insertE(GRAPH G, Edge e){
    int v = e.v, w = e.w, wt = e.wt;
    G->ladj[v] = NEW(w, wt, G->ladj[v]);
    G->E++;
}

static void removeE(GRAPH G, Edge e)
{
    int v = e.v, w = e.w;
    link x, p;
    for(x = G->ladj[v], p = G->z; x!= G->z; p = x, x = x->next){
        if(x->v == w)
        {
            if(x == G->ladj[v]){
                G->ladj[v] = x->next;
            }
            else{
                p->next = x->next;
            }
        }
    }
    if(x != NULL && x!= G->z)
        free(x);
    G->E--;
}

static Edge EdgeCreate(int v, int w, int wt){
    Edge E;
    E.v = v; E.w = w; E.wt = wt;
    return E;
}


void GRAPHedges(GRAPH G, Edge *a){
    int i, E = 0;
    link x;
    for(i = 0; i < G->V; i++)
    {
        for(x = G->ladj[i]; x != G->z; x = x->next){
            a[E++] = EdgeCreate(i, x->v, x->wt);
        }
    }
}


void GRAPHstore(GRAPH G, FILE *fout)
{
    int i;
    Edge *a;
    a = (Edge *)malloc(G->E * sizeof(Edge));
    GRAPHedges(G, a);
    if(fout != NULL)
    {
        fprintf(fout, "\n%d Vertici:\n", G->V);
        for(i = 0; i < G->V; i++){
            STprintName(G->tab, i);
        }
        fprintf(fout, "\n\n%d Archi:", G->E);
        for(i = 0; i < G->E; i++){
            fprintf(fout, "\n");
            STprintName(G->tab, a[i].v); STprintName(G->tab, a[i].w);
            fprintf(fout, "%d", a[i].wt);
        }
        if(fout != stdout)
            fclose(fout);
    }
    free(a);
}


void GRAPHfree(GRAPH G){
    int i;
    link x,t;
    for(i = 0; i < G->V; i++)
    {
        x = G->ladj[i];
        while(x != G->z){
            t = x->next;
            free(x);
            x = t;
        }
    }
    STfree(G->tab);
    free(G->ladj);
    free(G->z);
}

void GRAPHinsertE(GRAPH G, Edge E){
    insertE(G, E);
}
void GRAPHremoveE(GRAPH G, Edge E){
    removeE(G, E);
}


int GRAPHdfs(GRAPH G, int id)
{
    int time = 0, *pre, *post, *st;
    int flag = 0;
    pre = (int*)malloc(G->V*sizeof(int));
    post = (int*)malloc(G->V*sizeof(int));
    st = (int*)malloc(G->V*sizeof(int));
    for(int i = 0; i < G->V; i++){ //inizializzazione 0(V)
         pre[i] = post[i] = st[i] = -1;
    }
    dfsR(G, EdgeCreate(id, id, -1), &time, pre, post, st, &flag);
    // Archi cross e forward (vertici non ancora scoperti)
    for(int i = 0; i < G->V; i++){
        if(pre[i] == -1)
            dfsR(G, EdgeCreate(i, i, -1), &time, pre, post, st, &flag);
    }
    free(pre); free(post); free(st);
    return flag;
}


static void dfsR(GRAPH G, Edge e, int *time, int *pre, int *post, int *st, int *flag)
{
    link t;
    int v, w = e.w; // con cosa è connesso v
    st[e.w] = e.v; // il padre di w è v
    pre[w] = (*time)++;
    for(t = G->ladj[w]; t!=G->z && !(*flag); t = t->next)
    {
        if (pre[t->v] == -1)
            dfsR(G, EdgeCreate(w, t->v, -1), time, pre, post, st, flag);
        else
        {
            v = t->v;
            if(post[v] == -1){
                *flag = 1;
            }
        }
    }
    post[w] = (*time)++;
}


GRAPH searchForMinCardinality(GRAPH G)
{
    int i, E = G->E, flag = 0, peso = 0, rimossi = 0;
    GRAPH DAG = NULL;
    Edge *a = (Edge *)malloc(E * sizeof(Edge)), *solBEST, *solTMP;
    GRAPHedges(G, a);
    solBEST = (Edge *)malloc(E * sizeof(Edge));
    solTMP = (Edge *)malloc(E * sizeof(Edge));
    printf("\n\n\nInsieme degli archi a cardinalita' minima la cui rimozione rende il grafo originale un DAG:\n");
    combinazioni_sempliciR(a, solTMP, solBEST, E, 0, 0,  0, &peso, &flag, G);
    for(i = 1; i <E && !flag; i++){
        combinazioni_sempliciR(a, solTMP, solBEST, E, i, 0,  0, &peso, &flag, G);
        rimossi++;
    }
    if(flag)
    {
        DAG = G;
        if(rimossi == 0){
            printf("\nIl grafo era gia' un DAG.");
        }
        else if(rimossi > 0)
        {
            for(i = 0; i < rimossi; i++){
                GRAPHremoveE(DAG, solBEST[i]);
            }
            printf("\n\nArchi di cardinalita' minima con peso massimo pari a %d:\n", peso);
            for(i = 0; i < rimossi; i++){
                printf("( ");
                STprintName(G->tab, solBEST[i].v);
                STprintName(G->tab, solBEST[i].w);
                printf(")");
            }
        }
    }
    else
        printf("\n\nImpossibile creare un DAG.");
    free(a);
    free(solBEST);
    free(solTMP);
    return DAG;
}


static void combinazioni_sempliciR(Edge *a, Edge *solTMP, Edge *solBEST, int n, int k, int pos, int start, int *pesoMAX, int *flag, GRAPH G)
{
    int i, peso;
    if(pos>=k){
        for(i=0; i<k; i++){
            GRAPHremoveE(G, solTMP[i]);
        }
        if(!GRAPHdfs(G, 0)){
            for(i=0; i<k;i++){
                printf("( ");
                STprintName(G->tab, solTMP[i].v);
                printf(" ");
                STprintName(G->tab, solTMP[i].w);
                printf(" ) ");
            }
            printf("\n");
            *flag = 1;
            peso = calcola_peso(k, solTMP);
            if(peso > *pesoMAX){
                *pesoMAX = peso;
                for(i=0;i<k;i++){
                    solBEST[i] = solTMP[i];
                }
            }
        }
        for(i=0;i<k;i++){
            GRAPHinsertE(G, solTMP[i]);
        }
        return;
    }
    for(i=start;i<n;i++){
        solTMP[pos] = a[i];
        combinazioni_sempliciR(a, solTMP, solBEST, n, k, pos+1, i+1, pesoMAX, flag, G);
    }
}



static int calcola_peso(int E, Edge *a){
    int i, peso = 0;
    for(i = 0; i < E; i++)
        peso+=a[i].wt;
    return peso;
}



void TSdfsR(GRAPH DAG, int v, int *ts, int *pre, int *time)
{
    link t; pre[v] = 0;
    for(t = DAG->ladj[v]; t != DAG->z; t = t->next)
    {
        if(pre[t->v] == -1)
            TSdfsR(DAG, t->v, ts, pre, time);
    }
    ts[(*time)++] = v;
}
void DAGmaximumPATH(GRAPH G) {
    int v, time = 0, *pre, *ts, *maximumPaths, sorgente = 0;
    link t;
    pre = malloc(G->V * sizeof(int));
    ts = malloc(G->V * sizeof(int));
    maximumPaths = malloc(G->V * sizeof(int));

    for (v=0; v < G->V; v++){
        pre[v] = -1; ts[v] = -1; maximumPaths[v] = 0;
    }
        // ordinamento dei vertici in ordine topologico
    for (v=0; v < G->V; v++)
        if (pre[v]== -1)
            TSdfsR(G, v, ts, pre, &time);
    // calcolo dei cammini massimo attraverso relaxation inversa
    for (v=G->V - 1; v >= 0; v--) {
        for (t = G->ladj[ts[v]]; t != NULL; t = t->next) {
            if(maximumPaths[ts[v]] + t->wt > maximumPaths[t->v])
                maximumPaths[t->v] = maximumPaths[ts[v]] + t->wt;
        }
    }
    printf("\n\n\nNodi in ordine topologico:\n");
    for (v=G->V - 1; v >= 0; v--)
        STprintName(G->tab, ts[v]);

    printf("\n\nCammini massimi a partire dalla sorgente:\n");
    for (v=G->V - 1; v >= 0; v--) {
        printf("Nodo: ");
        STprintName(G->tab, ts[v]);
        if(maximumPaths[ts[v]] == 0)
            printf("  sorgente\n");
        else
            printf("   %3d\n",maximumPaths[ts[v]]);
    }
    free(pre);
    free(ts);
    free(maximumPaths);
}