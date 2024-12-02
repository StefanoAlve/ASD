#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "invArray.h"

struct invArray_s{
    inv_t *InvA;
    int n, maxn;
};

invArray_t invArray_init(){
    invArray_t p = malloc(sizeof (struct invArray_s));
    if (p == NULL){
        printf("Errore allocazione dinamica dell'inventario\n");
        return p;
    }
    p->InvA = NULL;
    p->n = p->maxn = 0;
    return p;
}

void invArray_free(invArray_t invArray){
    free(invArray->InvA);
    free(invArray);
}

void invArray_read(FILE *fp, invArray_t invArray){
    fscanf(fp, "%d", &invArray->maxn);
    invArray->InvA = malloc(invArray->maxn*sizeof (struct inv_s));
    if (invArray->InvA == NULL){
        printf("Errore allocazione dinamica inventario\n");
        return;
    }
    while(!feof(fp)){
        inv_read(fp, &invArray->InvA[invArray->n]);
        invArray->n++;
    }
}

void invArray_print(FILE *fp, invArray_t invArray){
    for (int i = 0; i < invArray->n; i++){
        inv_print(fp, &invArray->InvA[i]);
        printf("\n");
    }
}

inv_t *invArray_getByIndex(invArray_t invArray, int index){
    return &invArray->InvA[index];
}

void invArray_printByIndex(FILE *fp, invArray_t invArray, int index){
    inv_print(fp, invArray_getByIndex(invArray, index));
}

int invArray_searchByName(invArray_t invArray, char *name){
    for (int i = 0; i < invArray->n; i++){
        if (strcasecmp(name, invArray->InvA[i].nome) == 0)
            return i;
    }
    return -1;
}