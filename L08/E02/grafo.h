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
int** mInit(int n, int val);
link* listaInit(int n);
pgrafo_s grafoInit(int n);
void riempiGrafo(pgrafo_s pGrafo, char nomeFile[]);
void distruggiGrafo(pgrafo_s pGrafo);
void elencaAlfabetico(pgrafo_s pGrafo);
int verificaAdiacCoppM(pgrafo_s pGrafo, char v1[MAXC], char v2[MAXC], char v3[MAXC]); //Con matrice
int verificaAdiacCoppL(pgrafo_s pGrafo, char v1[MAXC], char v2[MAXC], char v3[MAXC]); //Con lista
void generaListaAdiac(pgrafo_s pGrafo);

#endif
