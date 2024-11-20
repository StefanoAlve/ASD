#include "inventario.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

inv_t VoidInv_t(){
    inv_t tmp;
    tmp.stat.hp = -1;
    return tmp;
}

int Inv_tCheckVoid(inv_t tmp){
    return (tmp.stat.hp == -1);
}

void INVLibera(INV inv){
    for (int i = 0; i < inv->maxINV; i++){
        free(inv->vettINV[i].nome);
        free(inv->vettINV[i].tipo);
    }
    free(inv->vettINV);
    free(inv);
}

INV RiempiInventario(char *nomefile){
    FILE *fp = fopen(nomefile, "r");
    if (fp == NULL){
        printf("Errore apertura file inventario\n");
        return NULL;
    }
    INV wpInv = malloc(sizeof (struct wrapperINV));
    wpInv->nINV = 0;
    fscanf(fp, "%d ", &wpInv->maxINV);
    wpInv->vettINV = malloc(wpInv->maxINV*sizeof (inv_t));
    char nome[MAXC], tipo[MAXC];
    while(fscanf(fp, "%s %s %d %d %d %d %d %d ", nome, tipo, &wpInv->vettINV[wpInv->nINV].stat.hp, &wpInv->vettINV[wpInv->nINV].stat.mp, &wpInv->vettINV[wpInv->nINV].stat.atk, &wpInv->vettINV[wpInv->nINV].stat.def,&wpInv->vettINV[wpInv->nINV].stat.mag, &wpInv->vettINV[wpInv->nINV].stat.spr) == 8){
        wpInv->vettINV[wpInv->nINV].nome = strdup(nome);
        wpInv->vettINV[wpInv->nINV].tipo = strdup(tipo);
        wpInv->nINV++;
    }
    fclose(fp);
    return wpInv;
}

inv_t INVNameSrc(INV inv, char *nome){
    for (int i = 0; i < inv->nINV; i++){
        if (strcasecmp(nome, inv->vettINV[i].nome) == 0){
            return inv->vettINV[i];
        }
    }
    return VoidInv_t();
}

void INVPrint(inv_t tmp){
    if (!Inv_tCheckVoid(tmp)){
        printf("Nome: %s\nTipo: %s\nStatistiche:\n", tmp.nome, tmp.tipo);
        printf("HP: %d\nMP: %d\nATK: %d\nDEF: %d\nMAG: %d\nSPR: %d\n", tmp.stat.hp, tmp.stat.mp, tmp.stat.atk, tmp.stat.def, tmp.stat.mag, tmp.stat.spr);
    } else {
        printf("Oggetto non esistente\n");
    }
}