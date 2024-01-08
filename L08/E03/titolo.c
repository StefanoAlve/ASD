#include "titolo.h"
struct titolo_s{
    char *t;
};

pTitolo titoloInit(){
    pTitolo titolo = (pTitolo)malloc(sizeof(*titolo));
    titolo->t = NULL;
    return titolo;
}
pTitolo leggiTitolo(FILE *fp){
    char tmp[MAXC];
    pTitolo titolo;
    fscanf(fp, "%s",tmp);
    titolo = titoloInit();
    titolo->t = strdup(tmp);
    return titolo;
}

int confrontaTitoli(pTitolo t1, pTitolo t2){
    return(strcasecmp(t1->t, t2->t));
}

void distruggiTitolo(pTitolo titolo){
    free(titolo->t);
    free(titolo);
}

pTitolo creaTitolo(char* tmp){
    pTitolo titolo = titoloInit();
    titolo->t = strdup(tmp);
    return titolo;
}