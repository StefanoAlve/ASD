#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "pgList.h"

struct PGnode{
    pg_t val;
    link next;
};

struct pgList_s{
    link PGhead;
    int nPG;
};

link NewNode(pg_t val, link next){
    link nodePg = malloc(sizeof (*nodePg));
    nodePg->val = val;
    nodePg->next = next;
    return nodePg;
}

pgList_t pgList_init(){
    pgList_t pgL = malloc(sizeof (*pgL));
    if (pgL == NULL){
        printf("Errore allocazione dinamica personaggi\n");
        return pgL;
    }
    pgL->nPG = 0;
    pgL->PGhead = NULL;
    return pgL;
}

void pgList_free(pgList_t pgList){
    while(pgList->PGhead != NULL){
        link x = pgList->PGhead;
        pgList->PGhead = x->next;
        pg_clean(&x->val);
        free(x);
    }
    free(pgList);
}

void pgList_read(FILE *fp, pgList_t pgList){
    pg_t *pgt = NULL;
    while(pg_read(fp, pgt) == 3){
        pgList->PGhead = NewNode(*pgt, pgList->PGhead);
        pgList->nPG++;
    }
}

void pgList_print(FILE *fp, pgList_t pgList, invArray_t invArray){
    for (link x = pgList->PGhead; x != NULL; x = x->next){
        pg_print(fp, &x->val, invArray);
        printf("\n");
    }
}

void pgList_insert(pgList_t pgList, pg_t pg){
    pgList->PGhead = NewNode(pg, pgList->PGhead);
}

void pgList_remove(pgList_t pgList, char* cod){
    link p, x;
    for (p = NULL, x = pgList->PGhead; x != NULL; p = x, x = x->next){
        if (strcasecmp(cod, x->val.cod) == 0){
            p->next = x->next;
            pg_clean(&x->val);
            free(x);
            return;
        }
    }
}

pg_t *pgList_searchByCode(pgList_t pgList, char* cod){
    link x;
    for (x = pgList->PGhead; x != NULL; x = x->next){
        if (strcasecmp(cod, x->val.cod) == 0){
            return &x->val;
        }
    }
    return NULL;
}