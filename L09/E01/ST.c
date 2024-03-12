
#include "ST.h"


struct st{
    char **id;
    int N;
    int maxN;
};


ST STinit(int N){
    ST Stable = (ST)malloc(sizeof(*Stable));
    Stable->id = (char**)malloc(N * sizeof(char*));
    Stable->id = (char**)malloc(N * sizeof(char*));
    Stable->N = 0;
    Stable->maxN = N;
    return Stable;
}

void STfree(ST Stable){
    for(int i = 0; i < Stable->N; i++)
        free(Stable->id[i]);
    free(Stable);
}


int STcount(ST Stable){
    return Stable->N;
}

void STprintName(ST Stable,  int index){
    printf("%s ", Stable->id[index]);
}

int STgetIndex(ST Stable, char *identificatore){
    int i;
    int found = -1;
    for(i = 0; i < Stable->N && found == -1; i++)
        if(strcmp(identificatore, Stable->id[i]) == 0)
            found = i;
    return found; ///Ritorna -1 se non trovato
}

int STinsert(ST Stable, char *id){
    int n = Stable->N;
    Stable->id[n] = strdup(id);
    Stable->N = Stable->N+1;
    return Stable->N-1; //ritorna l'indice in cui è stato inserito
}


void STprint(ST Stable){
    int i, n = Stable->N;
    for(i = 0; i < n; i++)
        printf("\n%d) %s", i, Stable->id[i]);
}
