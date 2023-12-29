#include "st.h"

struct symbolTable{
    char **vettElab;
    char **vettReti;
    int nVert;
    int nReti;
    int maxElem;
};

ST STInit(int n){
    ST sTable = (ST)malloc(sizeof(struct symbolTable));
    sTable->vettElab = (char**)malloc(n*MAXC*sizeof(char));
    sTable->vettReti = (char**)malloc(n*MAXC*sizeof(char));
    sTable->nVert = 0;
    sTable->nReti = 0;
    sTable->maxElem;
    return sTable;
}
void STfree(ST sTable){
    free(sTable->vettElab);
    free(sTable->vettReti);
    free(sTable);
}
int STcount(ST sTable){
    return sTable->nVert;
}
void STprintName(ST sTable, int index){
    printf("%s\n", sTable->vettReti[index]);
}
int STsearchIndexElab(ST sTable, char name[MAXC]){
    int i;
    for(i=0; strcasecmp((sTable->vettElab[i]),name) != 0 && i<sTable->nVert; i++);
    if(i==sTable->nVert){
        return -1;
    }
    return i;
}
int STsearchIndexReti(ST sTable, char name[MAXC]){
    int i;
    for(i=0; strcasecmp((sTable->vettReti[i]),name) != 0 && i<sTable->nVert; i++);
    if(i==sTable->nVert){
        return -1;
    }
    return i;
}
void STinsertElab(ST sTable, char name[MAXC], int i){
    strcpy(sTable->vettElab[i], name);
    sTable->nVert++;
}
void STinsertRete(ST sTable, char name[MAXC], int i){
    strcpy(sTable->vettReti[i], name);
    sTable->nReti++;
}