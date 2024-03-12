#include "title.h"

struct titolo_s{
    char *titolo;
};


pTitle title_init(){
    pTitle x;
    x = (pTitle)malloc(sizeof(*x));
    return x;
}

pTitle title_cpy(char* name){
    pTitle x = title_init();
    x->titolo = strdup(name);
    return x;
}

pTitle leggi_titolo(FILE *fp){
    pTitle x;
    char tmp[MAXLEN];
    fscanf(fp, "%s", tmp);
    x = title_cpy(tmp);
    return x;
}

void title_free(pTitle x){
    free(x->titolo);
    free(x);
}


int title_cmp(pTitle t1, pTitle t2){
    return(strcmp(t1->titolo, t2->titolo));
}

void title_print(pTitle x)
{
    printf("%s", x->titolo);
}