#include "GRAPH.h"
///UTILIZZO APPROCCIO CON LISTA DELLE ADIACENZE
static link newNode(int v, int peso, link next);
static arco_s EDGEcreate(int v1, int v2, int peso);

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

void listaFree(Graph grafo){ //TODO

}
Graph grafoInit(int n){
    Graph grafo = (Graph)malloc(sizeof(*grafo));
    grafo->nVert = n;
    grafo->nArchi = 0;
    grafo->z = newNode(-1,-1,NULL);
    listaInit(grafo);
    grafo->tabSimboli = STInit(n);
}
void GRAPHfree(Graph grafo){
}
void GRAPHload(FILE *fin){ //TODO

}
void GRAPHstore(Graph grafo, FILE *fout){ //TODO

}
int GRAPHgetIndex(Graph grafo, char name[]){ //TODO

}
void GRAPHinsertE(Graph grafo, int id1, int id2, int peso){ //TODO

}
void GRAPHremoveE(Graph grafo, int id1, int id2){ //TOOD

}
void GRAPHedges(Graph grafo, arco_s *archi){ //TODO

}