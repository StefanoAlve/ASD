#ifndef E01_GRAPH_H
#define E01_GRAPH_H
#include "ST.h"
typedef struct grafo_s *Graph;
typedef struct node *link;
typedef struct {int v1; int v2; int peso;}arco_s;
struct node{
    int vertice;
    int peso;
    link next;
};

void listaInit(Graph grafo);
void listaFree(Graph grafo);
Graph GRAPHInit(int n);
void GRAPHfree(Graph grafo);
Graph GRAPHload(FILE *fin);
void GRAPHstore(Graph grafo, FILE *fout);
int GRAPHgetIndex(Graph grafo, char name[]);
void GRAPHinsertE(Graph grafo, int id1, int id2, int peso);
void GRAPHremoveE(Graph grafo, int id1, int id2);
void GRAPHedges(Graph grafo, arco_s *archi);
#endif //E01_GRAPH_H
