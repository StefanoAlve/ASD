#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "equipArray.h"

struct equipArray_s{
    int inUso;
    int vettEq[EQUIP_SLOT];
};

equipArray_t equipArray_init(){
    equipArray_t p = malloc(sizeof *p);
    if (p == NULL){
        printf("Errore allocazione dinamica degli equipaggiamenti\n");
        return p;
    }
    p->inUso = 0;
    for (int i = 0; i < EQUIP_SLOT; i++)
        p->vettEq[i] = -1;
    return p;
}

void equipArray_free(equipArray_t equipArray){
    free(equipArray);
}

int equipArray_inUse(equipArray_t equipArray){
    return equipArray->inUso;
}

void equipArray_print(FILE *fp, equipArray_t equipArray, invArray_t invArray){
    int n = equipArray_inUse(equipArray);
    if (n == 0){
        printf("Nessun oggetto equipaggiato\n");
        return;
    }
    for (int i = 0; i < EQUIP_SLOT; i++){
        if (equipArray->vettEq[i] != -1){
            invArray_printByIndex(fp, invArray, equipArray->vettEq[i]);
            printf("\n");
        }
    }
}

void equipArray_update(equipArray_t equipArray, invArray_t invArray){
    char nome[LEN];
    int scelta, indice;
    printf("Inserire nome oggetto:\n");
    scanf("%s", nome);
    indice = invArray_searchByName(invArray, nome);
    printf("Vuoi equipaggiare l'oggetto (1) o toglierlo (0) ?\n");
    scanf("%d", &scelta);
    if (scelta){
        if (equipArray->inUso < EQUIP_SLOT){
            int i;
            for (i = 0; i < EQUIP_SLOT && equipArray->vettEq[i] != -1; i++);
            equipArray->vettEq[i] = indice;
            equipArray->inUso++;
        }
        else printf("Capienza equipaggiamenti massima raggiunta\n");
    } else {
        int i;
        for (i = 0; i < EQUIP_SLOT && equipArray->vettEq[i] != indice; i++);
        if (i >= EQUIP_SLOT) printf("Errore: oggetto non equipaggiato\n");
        else {
            equipArray->vettEq[i] = -1;
            equipArray->inUso--;
        }
    }
}

int equipArray_getEquipByIndex(equipArray_t equipArray, int index){
    return equipArray->vettEq[index];
}