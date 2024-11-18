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

