#include "graph.h"
int main(void)
{
    FILE *fp;
    Graph G;
    Graph DAG;
    fp = fopen("grafo4.txt", "r");
    G = GRAPHload(fp);
    GRAPHstore(G, stdout);
    DAG = searchForMinCardinality(G);
    printf("\n\nContenuto del DAG:\n");
    GRAPHstore(DAG, stdout);
    GRAPHcamminoMax(DAG);
    GRAPHfree(G);
    return 0;
}