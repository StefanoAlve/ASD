#include "graph.h"

int main(void)
{
    FILE *fp;
    GRAPH G;
    GRAPH DAG;
    fp = fopen("grafo4.txt", "r");
    G = GRAPHload(fp);
    GRAPHstore(G, stdout);
    DAG = searchForMinCardinality(G);
    GRAPHstore(DAG, stdout);
    DAGmaximumPATH(DAG);
    GRAPHfree(DAG);
    return 0;
}