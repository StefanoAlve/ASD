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
        printf("Errore apertura file personaggi\n");
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
        if (p == NULL) pg->headPG = pg->headPG->next;
        else p->next = p->next->next;
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
        printf("\nCodice: %s\nNome: %s\nClasse: %s\nStatistiche Personaggio:\n", tmp.codice, tmp.nome, tmp.classe);
        printf("HP: %d\nMP: %d\nATK: %d\nDEF: %d\nMAG: %d\nSPR: %d\n", tmp.stat.hp, tmp.stat.mp, tmp.stat.atk, tmp.stat.def, tmp.stat.mag, tmp.stat.spr);
        printf("Equipaggiamento:\n");
        printf("Oggetto in uso:\n");
        if (tmp.equip->inUso == -1) printf("Nessun oggetto in uso\n");
        else INVPrint(*(tmp.equip->vettEq[tmp.equip->inUso]));
        printf("\nOggetti equipaggiati:\n");
        int i = 0;
        while(tmp.equip->vettEq[i] != NULL){
            if (i != tmp.equip->inUso)
                INVPrint(*(tmp.equip->vettEq[i]));
            i++;
        }
    } else {
        printf("Personaggio non esistente\n");
    }
}

void PGInsertEquip(PG pg, INV inv, char *codice, char *nome){
    link x;
    int j;
    for (j = 0; j < inv->nINV && strcasecmp(inv->vettINV[j].nome, nome) != 0; j++);
    if (j == inv->nINV){
        printf("Oggetto inesistente\n");
        return;
    }
    for (x = pg->headPG; x != NULL && strcasecmp(x->val.codice, codice) != 0; x = x->next);
    if (x == NULL){
        printf("Personaggio inesistente\n");
        return;
    }
    int i = 0;
    while (i < MAXEquip && x->val.equip->vettEq[i] != NULL)
        i++;
    if (i == MAXEquip) printf("Capienza equipaggiamenti raggiunta\n");
    else {
        x->val.equip->vettEq[i] = &(inv->vettINV[j]);
        printf("Vuoi equipaggiare %s con %s? (y,n)\n", x->val.nome, inv->vettINV[j].nome);
        char c;
        scanf(" %c", &c);
        if (c == 'y' || c == 'Y') x->val.equip->inUso = i;
        PGPrint(x->val);
    }
}

void PGRemoveEquip(PG pg, INV inv, char *codice, char *nome){
    link x;
    int j;
    for (j = 0;j < inv->nINV && strcasecmp(inv->vettINV[j].nome, nome) != 0; j++);
    if (j == inv->nINV){
        printf("Oggetto inesistente\n");
        return;
    }
    for (x = pg->headPG;x != NULL && strcasecmp(x->val.codice, codice) != 0; x = x->next);
    if (x == NULL){
        printf("Personaggio inesistente\n");
        return;
    }
    int i;
    for (i = 0; i < MAXEquip; i++){
        if (x->val.equip->vettEq[i] != NULL && strcasecmp(x->val.equip->vettEq[i]->nome, nome) == 0){
            x->val.equip->vettEq[i] = NULL;
            if (i == x->val.equip->inUso) x->val.equip->inUso = -1;
            break;
        }
    }
    if (i == MAXEquip) printf("Oggetto non equipaggiato a %s (%s)\n", x->val.nome, x->val.codice);
    else PGPrint(x->val);
}















