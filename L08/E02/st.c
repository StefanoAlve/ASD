#include "st.h"

struct symbolTable{
    char **vettElab;
    char **vettReti;
    int nVert;
    int maxElem;
};

ST STInit(int n){
    ST sTable = (ST)malloc(sizeof(struct symbolTable));
    sTable->vettElab = (char**)malloc(n*MAXC*sizeof(char));
    sTable->vettReti = (char**)malloc(n*MAXC*sizeof(char));
    sTable->nVert = 0;
    sTable->maxElem;
    return sTable;
}
void STfree(ST sTable){
    for(int i=0; i<sTable->nVert;i++){
        free(sTable->vettElab[i]);
    }
    free(sTable->vettElab);
    for(int i=0; i<sTable->nVert;i++){
        free(sTable->vettReti[i]);
    }
    free(sTable->vettReti);
    free(sTable);
}
int STcount(ST sTable){
    return sTable->nVert;
}
void STprintName(ST sTable, int index){
    printf("%s", sTable->vettElab[index]);
}
int STgetIndex(ST Stable, char *elab, char *rete){
    int i;
    int found = -1;
    for(i = 0; i < Stable->nVert && found == -1; i++)
        if(strcmp(elab, Stable->vettElab[i]) == 0 /*&& strcmp(rete, Stable->vectrete[i]) == 0*/)
            found = i;
    return found; ///Ritorna -1 se non trovato
}

int STinsert(ST Stable, char *elab, char *rete){
    int n = Stable->nVert;
    Stable->vettElab[n] = strdup(elab);
    Stable->vettReti[n] = strdup(rete);
    Stable->nVert = Stable->nVert+1;
    return Stable->nVert-1; //ritorna l'indice in cui è stato inserito
}
void STsort(ST Stable, int* vett){
    int i,j,n = Stable->nVert;
    char tmp[MAXC];
    for(i =0; i < n; i++)
        vett[i] = i;
    for(i = 1; i < n; i++)
    {
        j = i-1;
        strcpy(tmp, Stable->vettElab[i]);
        while(j>= 0 && strcmp(tmp, Stable->vettElab[vett[j]]) < 0)
        {
            vett[j+1] = vett[j];
            j--;
        }
        vett[j+1] = i;
    }
}
void STprint(ST Stable){
    int i, n = Stable->nVert;
    for(i = 0; i < n; i++)
        printf("\n%d) %s - %s", i, Stable->vettElab[i], Stable->vettReti[i]);

}