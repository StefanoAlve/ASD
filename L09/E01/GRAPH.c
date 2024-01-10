#include "GRAPH.h"
///UTILIZZO APPROCCIO CON LISTA DELLE ADIACENZE
static link newNode(int v, int peso, link next);
static arco_s EDGEcreate(int v1, int v2, int peso);
static void insertE(Graph grafo, arco_s arco);
static void removeE(Graph grafo, arco_s arco);

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
        while(x!=NULL){
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
    fprintf(fout, "%d\n", grafo->nVert);
    for(i=0; i < grafo->nVert; i++){
        fprintf(fout, "%s\n", STsearchByIndex(grafo->tabSimboli, i));
    }
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
    link x,p;
    int v1 = arco.v1, v2 = arco.v2;
    for(x=grafo->ladj[v1], p = NULL; x != grafo->z; p=x, x=x->next){
        if(x->vertice == v2){
            if(x == grafo->ladj[v1])
                grafo->ladj[v1] = x->next;
            else
                p->next = x->next;
            break;
        }
    }
    free(x);
    grafo->nArchi--;
}