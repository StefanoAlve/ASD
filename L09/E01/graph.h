#ifndef E01_GRAPH_H
    #define E01_GRAPH_H
    #include "ST.h"
    typedef struct{
        int v;
        int w;
        int wt;
    }Edge;
    typedef struct graph *GRAPH;
    GRAPH GRAPHinit(int V);
    GRAPH GRAPHload(FILE *fin);
    int GRAPHdfs(GRAPH G, int id); /// verifica che sia aciclico.
    void GRAPHinsertE(GRAPH G, Edge E);
    void GRAPHremoveE(GRAPH G, Edge E);
    void GRAPHstore(GRAPH G, FILE *fout);
    void GRAPHedges(GRAPH G, Edge *a);
    void GRAPHfree(GRAPH G);
    void TSdfsR(GRAPH DAG, int v, int *ts, int *pre, int *time);
    void DAGmaximumPATH(GRAPH G);
    /// EXTRA FUNCTIONS
    GRAPH searchForMinCardinality(GRAPH G);

#endif //E01_GRAPH_H
