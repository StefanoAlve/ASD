#include "personaggi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

link NewNodePG(pg_t val, link next){
    link NodePG = malloc(sizeof (struct nodoPG));
    NodePG->val = val;
    NodePG->next = next;
    return NodePG;
}

pg_t VoidPg(){
    pg_t tmp;
    tmp.stat.hp = -1;
    return tmp;
}

int PgCheckVoid(pg_t tmp){
    return (tmp.stat.hp == -1);
}

void PGLiberaNode(link x){
    free(x->val.codice);
    free(x->val.nome);
    free(x->val.classe);
    free(x->val.equip);
    free(x);
}

void PGLibera(PG pg){
    link t = pg->headPG;
    while (t != NULL){
        pg->headPG = pg->headPG->next;
        PGLiberaNode(t);
        t = pg->headPG;
    }
    free(pg);
}

PG CreaListaPersonaggi(char *nomefile){
    FILE *fp = fopen(nomefile, "r");
    if (fp == NULL){
        printf("Errore apertura file inventario\n");
        return NULL;
    }
    PG wpPG = malloc(sizeof (struct wrapperPG));
    wpPG->nPG = 0;
    wpPG->headPG = wpPG->tailPG = NULL;

    pg_t pg;
    char codice[MAXC], nome[MAXC], classe[MAXC];
    while(fscanf(fp, "%s %s %s %d %d %d %d %d %d", codice, nome, classe, &pg.stat.hp, &pg.stat.mp, &pg.stat.atk, &pg.stat.def, &pg.stat.mag, &pg.stat.spr) == 9){
        pg.codice = strdup(codice);
        pg.nome = strdup(nome);
        pg.classe = strdup(classe);
        pg.equip = malloc(sizeof (struct Equip_t));
        pg.equip->inUso = -1;
        for (int i = 0; i < MAXEquip; i++)
            pg.equip->vettEq[i] = NULL;

        wpPG->headPG = NewNodePG(pg, wpPG->headPG);
        if (wpPG->nPG == 0) wpPG->tailPG = wpPG->headPG;
        wpPG->nPG++;
    }
    return wpPG;
}

pg_t PGScan(){
    pg_t tmp;
    char codice[MAXC], nome[MAXC], classe[MAXC];
    printf("Inserire i campi del personaggio nel formato:\n");
    printf("<codice> <nome> <classe> <hp> <mp> <atk> <def> <mag> <spr>\n");
    fscanf(stdin, "%s %s %s %d %d %d %d %d %d", codice, nome, classe, &tmp.stat.hp, &tmp.stat.mp, &tmp.stat.atk, &tmp.stat.def, &tmp.stat.mag, &tmp.stat.spr);
    tmp.codice = strdup(codice);
    tmp.nome = strdup(nome);
    tmp.classe = strdup(classe);
    tmp.equip = malloc(sizeof (struct Equip_t));
    tmp.equip->inUso = -1;
    for (int i = 0; i < MAXEquip; i++)
        tmp.equip->vettEq[i] = NULL;
    return tmp;
}

void PGInsert(PG pg, pg_t val){
    pg->headPG = NewNodePG(val, pg->headPG);
    pg->nPG++;
}

void PGRemove(PG pg, char *codice){
    link t, p;
    for(p = NULL, t = pg->headPG; t != NULL && strcasecmp(t->val.codice, codice) != 0; p = t, t = t->next);
    if (t != NULL){
        p->next = p->next->next;
        PGLiberaNode(t);
    }
}

pg_t PGCodSearch(PG pg, char *codice){
    link t;
    for(t = pg->headPG; t != NULL && strcasecmp(t->val.codice, codice) != 0; t = t->next);
    if (t != NULL){
        return t->val;
    }
    return VoidPg();
}

void PGPrint(pg_t tmp){
    if (!PgCheckVoid(tmp)){
        printf("Codice: %s\nNome: %s\nClasse: %s\nEquipaggiamento:\n", tmp.codice, tmp.nome, tmp.classe);
        printf("Oggetto in uso:\n");
        if (tmp.equip->inUso == -1) printf("Nessun oggetto in uso\n");
        else INVPrint(*(tmp.equip->vettEq[tmp.equip->inUso]));
        printf("\nOggetti equipaggiati:\n");
        int i = 0;
        while(tmp.equip->vettEq[i] != NULL){
            if (i != tmp.equip->inUso){
                INVPrint(*(tmp.equip->vettEq[i]));
                i++;
            }
        }
        if (i == 0) printf("Nessun altro oggetto equipaggiato\n");
    } else {
        printf("Personaggio non esistente\n");
    }
}

void PGInsertEquip(PG pg, INV inv, char *codice, char *nome){
    link x;
    int j;
    for (j = 0; strcasecmp(inv->vettINV[j].nome, nome) != 0 && j < inv->nINV; j++);
    if (j == inv->nINV){
        printf("Oggetto inesistente\n");
        return;
    }
    for (x = pg->headPG; strcasecmp(x->val.codice, codice) != 0 && x != NULL; x = x->next);
    if (x == NULL){
        printf("Personaggio inesistente\n");
        return;
    }
    int i = 0;
    while (x->val.equip->vettEq[i] != NULL)
        i++;
    x->val.equip->vettEq[i] = &(inv->vettINV[j]);
}

void PGRemoveEquip(PG pg, INV inv, char *codice, char *nome){
    link x;
    int j;
    for (j = 0; strcasecmp(inv->vettINV[j].nome, nome) != 0 && j < inv->nINV; j++);
    if (j == inv->nINV){
        printf("Oggetto inesistente\n");
        return;
    }
    for (x = pg->headPG; strcasecmp(x->val.codice, codice) != 0 && x != NULL; x = x->next);
    if (x == NULL){
        printf("Personaggio inesistente\n");
        return;
    }
    int i;
    for (i = 0; i < MAXEquip; i++){
        if (x->val.equip->vettEq[i] != NULL && strcasecmp(x->val.equip->vettEq[i]->nome, nome) == 0){
            x->val.equip->vettEq[i] = NULL;
            break;
        }
    }
    if (i == MAXEquip) printf("Oggetto non equipaggiato a %s (%s)\n", x->val.nome, x->val.codice);
}















