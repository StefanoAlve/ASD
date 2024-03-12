#include "st.h"

struct symboltable{
    char **vectelab;
    char **vectrete;
    int N;
    int maxN;
};

ST STinit(int N)
{
    ST Stable = (ST)malloc(sizeof(*Stable));
    Stable->vectelab = (char**)malloc(N * sizeof(char*));
    Stable->vectrete = (char**)malloc(N * sizeof(char*));
    Stable->N = 0;
    Stable->maxN = N;
    return Stable;
}

void STfree(ST Stable)
{
    for(int i = 0; i < Stable->N; i++)
    {
        free(Stable->vectelab[i]);
        free(Stable->vectrete[i]);
    }
    free(Stable);
}


int STcount(ST Stable){
    return Stable->N;
}

void STprintName(ST Stable,  int index){
    printf("%s ", Stable->vectelab[index]);
}

int STgetIndex(ST Stable, char *elab, char *rete)
{
    int i;
    int found = -1;
    for(i = 0; i < Stable->N && found == -1; i++)
        if(strcmp(elab, Stable->vectelab[i]) == 0 /*&& strcmp(rete, Stable->vectrete[i]) == 0*/)
            found = i;
    return found; ///Ritorna -1 se non trovato
}

int STinsert(ST Stable, char *elab, char *rete)
{
    int n = Stable->N;
    Stable->vectelab[n] = strdup(elab);
    Stable->vectrete[n] = strdup(rete);
    Stable->N = Stable->N+1;
    return Stable->N-1; //ritorna l'indice in cui è stato inserito
}


void STprint(ST Stable)
{
    int i, n = Stable->N;
    for(i = 0; i < n; i++)
        printf("\n%d) %s - %s", i, Stable->vectelab[i], Stable->vectrete[i]);

}


void STsort(ST Stable, int* vett)
{
    int i,j,n = Stable->N;
    char tmp[MAXSTRLEN];
    for(i =0; i < n; i++)
        vett[i] = i;
    for(i = 1; i < n; i++)
    {
        j = i-1;
        strcpy(tmp, Stable->vectelab[i]);
        while(j>= 0 && strcmp(tmp, Stable->vectelab[vett[j]]) < 0)
        {
            vett[j+1] = vett[j];
            j--;
        }
        vett[j+1] = i;
    }
    /*for(i = 0; i<n; i++)
        printf("%d ", vett[i]);*/
}