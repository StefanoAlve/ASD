#include "graph.h"

typedef struct node *link;
static link NEW(int v, int wt, link next);
struct node
{
    int id;
    int wt;
    link next;
};


struct graph{
    int V;
    int E;
    int **mat_ad;
    ST tab;
    link* ladj;
    link z;
};


Graph GRAPHinit(int V)
{
    Graph g;
    g = (Graph)malloc(sizeof(*g));
    g->V = V;
    g->E = 0;
    g->mat_ad = (int**)calloc(V, sizeof(int*));
    g->ladj = (link*)malloc(V*sizeof(link));
    g->tab = STinit(V);
    g->z = NEW(-1, -1, NULL);
    for(int i = 0; i < V; i++){
        g->mat_ad[i] = (int*)calloc(V, sizeof(int));
        g->ladj[i] = g->z;
    }
    return g;
}

void SortVertex(Graph G)
{
    int *vett = (int*)malloc(G->V * sizeof(int)), i, j, v = G->V;
    STsort(G->tab, vett);
    for(i = 0; i < v; i++)
    {
        printf("\n\nVertice %d): ", i+1);
        STprintName(G->tab, vett[i]); printf("\n");
        for(j = 0; j < v; j++)
        {
            if(G->mat_ad[vett[i]][vett[j]] != 0)
            {
                STprintName(G->tab, vett[j]);
                printf("- ");
            }
        }
    }
    free(vett);
}

void GraphLoad(Graph G, char *filename)
{
    char id_elab1[MAXSTRLEN], id_elab2[MAXSTRLEN],id_rete1[MAXSTRLEN],id_rete2[MAXSTRLEN];
    int wt, E = 0;
    FILE *fp = fopen(filename, "r");
    if(fp != NULL)
    {
        while(fscanf(fp, "%s %s %s %s %d", id_elab1, id_rete1, id_elab2, id_rete2, &wt) == 5){
            GRAPHinsertE(G, id_elab1, id_rete1, id_elab2, id_rete2, wt);
            E++;
        }
        STprint(G->tab);
        G->E = E;
        G->V = STcount(G->tab);
    }
    else
        printf("\nErrore nella lettura del file");
    fclose(fp);
}


void GRAPHfree(Graph G)
{
    int i, v = G->V;
    link x;
    for(i = 0; i<v; i++)
        free(G->mat_ad[i]);
    free(G->mat_ad);
    i = 0;
    while(G->ladj[i] != G->z)
    {
        x = G->ladj[i];
        G->ladj[i] = G->ladj[i]->next;
        free(x);
    }
    free(G->ladj);
    STfree(G->tab);
    free(G);
}


static link NEW(int v, int wt, link next) {
    link x;
    x = (link)malloc(sizeof(*x));
    x->id = v;
    x->wt = wt;
    x->next = next;
    return x;
}


void GRAPHinsertE(Graph G, char* id_elab1, char* id_rete1, char* id_elab2, char* id_rete2, int wt)
{
    int id1, id2;
    id1 = STgetIndex(G->tab, id_elab1, id_rete1);
    id2 = STgetIndex(G->tab, id_elab2, id_rete2);
    if(id1 == -1)
        id1 = STinsert(G->tab, id_elab1, id_rete1);
    if(id2 == -1)
        id2 = STinsert(G->tab, id_elab2, id_rete2);
    if(G->mat_ad[id1][id2] == 0) G->E++; // aggiungo il nuovo arco se il peso precedente era zero nella matrice di adiacenza
    G->mat_ad[id1][id2] = wt;
    G->mat_ad[id2][id1] = wt;
}


void print_matrix(Graph G)
{
    int i, j, v = G->V;
    printf("\n");
    for(i = 0; i < v; i++)
    {
        for(j =0 ; j < v; j++)
            printf(" %d ", G->mat_ad[i][j]);
        printf("\n");
    }
}


void GRAPHloadListAdj(Graph G)
{
    int v = G->V, i, j;
    for(i = 0; i < v; i++)
    {
        for(j = 0; j < v; j++)
        {
            if(G->mat_ad[i][j]!=0){
                G->ladj[i] = NEW(j, G->mat_ad[i][j], G->ladj[i]);
            }
        }
    }

    link x;
    for(i = 0; i < v; i++)
    {
        printf("\n-Vertex %d:\n", i);
        x = G->ladj[i];
        while(x!= G->z)
            {
                printf("id: %d; w:%d - ", x->id, x->wt);
                x = x->next;
            }
    }
}

void check_adiacenza_mat(Graph G, char* str1, char* str2, char* str3)
{
    int id1, id2, id3, flag = 0;
    id1 = STgetIndex(G->tab, str1, "");
    id2 = STgetIndex(G->tab, str2, "");
    id3 = STgetIndex(G->tab, str3, "");
    if(id1 >= 0 && id2 >= 0 && id3>=0)
        if(G->mat_ad[id1][id2] != 0 && G->mat_ad[id1][id3] != 0 && G->mat_ad[id2][id3])
            flag = 1;
    if(flag)
        printf("\nI vertici %s, %s, %s formano un sottografo completo.", str1, str2, str3);
    else
        printf("\nI vertici %s, %s, %s non formano un sottografo completo.", str1, str2, str3);
}

void check_adiacenza_ladj(Graph G, char* str1, char* str2, char* str3)
{
    int id1, id2, id3, flag1 =0, flag2 = 0, flag3 = 0;
    link x, y, z;
    id1 = STgetIndex(G->tab, str1, "");
    id2 = STgetIndex(G->tab, str2, "");
    id3 = STgetIndex(G->tab, str3, "");
    if(id1 >= 0 && id2 >= 0 && id3>=0)
    {
        x = G->ladj[id1];
        y = G->ladj[id2];
        while(x!= G->z){
            if(x->id == id2)
                flag1 = 1;
            if(x->id == id3)
                flag2 = 1;
            x = x->next;
        }
        while(y != G->z && !flag3)
        {
            if(y->id == id3)
                flag3 = 1;
            y = y->next;
        }
        if(flag1*flag2*flag3 > 0)
            printf("\nI vertici %s, %s, %s formano un sottografo completo.", str1, str2, str3);
        else
            printf("\nI vertici %s, %s, %s non formano un sottografo completo.", str1, str2, str3);
    }
}