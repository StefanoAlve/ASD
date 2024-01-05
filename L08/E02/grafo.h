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
void riempiGrafo(pgrafo_s pGrafo, char nomeFile[]);
void distruggiGrafo(pgrafo_s pGrafo);
void elencaAlfabetico(pgrafo_s pGrafo);
arco_s creaArco(int v1,int v2, int flusso);
void generaArchi(pgrafo_s pGrafo, arco_s *vettArchi);
link newNode(int vertice, int flusso, link next);
void generaListaAdiac(pgrafo_s pGrafo, arco_s* vettArchi);
int verificaAdiacCoppM(pgrafo_s pGrafo, char v1[MAXC], char v2[MAXC], char v3[MAXC]); //Con matrice
int verificaAdiacCoppL(pgrafo_s pGrafo, char v1[MAXC], char v2[MAXC], char v3[MAXC]); //Con lista
void freeM(int** M);
void freeL(link* head);
#endif
