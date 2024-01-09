#ifndef E02_GRAFO_H
#define E02_GRAFO_H
#include "st.h"
typedef struct grafo_s *pgrafo_s;
typedef struct node *link;
struct node{
    int vertice;
    int flusso;
    link next;
};
typedef struct{
    int v1;
    int v2;
    int flusso;
}arco_s;
int** mInit(int r, int c, int val);
void listaInit(int n, pgrafo_s pGrafo);
pgrafo_s grafoInit(int n);
void GRAPHinsertE(pgrafo_s G, char* id_elab1, char* id_rete1, char* id_elab2, char* id_rete2, int wt);
void GraphLoad(pgrafo_s G, char *filename);
void distruggiGrafo(pgrafo_s pGrafo, int flag);
void elencaAlfabetico(pgrafo_s pGrafo);
link newNode(int vertice, int flusso, link next);
void GRAPHloadListAdj(pgrafo_s G);
void verificaAdiacCoppM(pgrafo_s pGrafo, char v1[MAXC], char v2[MAXC], char v3[MAXC]); //Con matrice
void verificaAdiacCoppL(pgrafo_s pGrafo, char v1[MAXC], char v2[MAXC], char v3[MAXC]); //Con lista
void print_matrix(pgrafo_s G);
void freeM(pgrafo_s pGrafo);
void freeL(pgrafo_s pGrafo);
#endif
