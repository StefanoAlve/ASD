#include "ST.h"

struct ST_S{
    char **vett;
    int nVert;
};

ST STInit(int n){
    ST sTable = (ST)malloc(sizeof(*sTable));
    sTable->vett = (char**)malloc(n*sizeof(char*));
    sTable->nVert = 0;
    return sTable;
}
void STfree(ST sTable){ //TODO
    for(int i=0; i<sTable->nVert;i++){
        free(sTable->vett[i]);
    }
    free(sTable->vett);
    free(sTable);
}
int STcount(ST sTable){ //TODO
    return sTable->nVert;
}
void STprint(ST sTable, int index){ //TODO
    printf("%s", sTable->vett[index]);
}
int STgetIndex(ST sTable, char name[MAXC]){ //TODO
    int i;
    for(i=0; i< sTable->nVert; i++){
        if(strcmp(name, sTable->vett[i]) == 0){
            return i;
        }
    }
    return -1;
}
int STinsert(ST sTable, char name[MAXC]){ //TODO
    int n = sTable->nVert;
    sTable->vett[n] = strdup(name);
}
