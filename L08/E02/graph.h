
#ifndef E02_GRAPH_H
    #define E02_GRAPH_H
    #include "st.h"
    typedef struct{int v; int w; int wt;}edge;
    typedef struct graph *Graph;
    Graph GRAPHinit(int V); // dato il num di vertici
    void GraphLoad(Graph G, char *filename);
    void print_matrix(Graph G);
    void GRAPHloadListAdj(Graph G);
    void SortVertex(Graph G);
    void GRAPHfree(Graph G);
    void GRAPHinsertE(Graph G, char* id_elab1, char* id_rete1, char* id_elab2, char* id_rete2, int wt);
    void check_adiacenza_mat(Graph G, char* str1, char* str2, char* str3);
    void check_adiacenza_ladj(Graph G, char* str1, char* str2, char* str3);
#endif //E02_GRAPH_H
