#include "equipArray.h"

struct equipArray_s {
    int equipaggiamento[EQUIP_SLOT];
    int inUso;
};

equipArray_t equipArray_init(){
    int i;
    equipArray_t equipArray = (equipArray_t)malloc(sizeof(*equipArray));
    equipArray->inUso = 0;
    for (i = 0; i < EQUIP_SLOT; i++) {
        equipArray->equipaggiamento[i] = -1;
    }
    return equipArray;
}

void equipArray_free(equipArray_t equipArray){
    free(equipArray);
}

int equipArray_inUse(equipArray_t equipArray){
    return equipArray->inUso;
}

void equipArray_print(FILE *fp, equipArray_t equipArray, invArray_t invArray){
    int i;
    fprintf(fp, " equip( ");
    for(i=0; i<equipArray->inUso; i++){
        invArray_printByIndex(fp, invArray, equipArray->equipaggiamento[i]);
    }
    fprintf(fp, ")");
}
//rimuove o aggiunge un oggetto
void equipArray_update(equipArray_t equipArray, invArray_t invArray){
    int index, i, bool=0;
    char scelta[11];

    printf("vuoi 'aggiungere' o 'rimuovere' un oggetto\n");
    scanf("%s", scelta);
    //caso di aggiunta
    if(strcasecmp("aggiungere", scelta)==0) {
        //controllo del vettore
        if (equipArray_inUse(equipArray) >= EQUIP_SLOT) {
            printf("l'equipaggiamento e' pieno\n");
        }
        else {
            //aggiunta affettiva dell'oggetto
            printf("scegli l'indice dell'oggetto che vuoi aggiungere tra i seguenti:\n");
            invArray_printVideo(invArray);
            scanf("%d", &index);
            equipArray->equipaggiamento[equipArray_inUse(equipArray)] = index;
            equipArray->inUso += 1; //aumento gli oggetti in uso

        }
    }
        //caso di rimozione
    else if(strcasecmp("rimuovere", scelta)==0) {
        //controllo che non sia vuoto
        if (equipArray_inUse(equipArray) == 0) {
            printf("l'equipaggiamento e' vuoto\n");
        }
        else {
            //scelta rimozione
            printf("scegli l'indice dell'oggetto che vuoi rimuovere tra i seguenti:\n");
            for(i=0; i < equipArray_inUse(equipArray); i++) {
                printf("%d\n", equipArray->equipaggiamento[i]);
            }
            scanf("%d", &index);
            //rimozione effettiva
            for(i=0; i < equipArray_inUse(equipArray); i++){
                //controllo che sia il valore
                if(index == equipArray->equipaggiamento[i] || bool) {
                    //aggiorno la lista per far si che tutti i valori siano di fila
                    if(i == EQUIP_SLOT-1) {
                        equipArray->equipaggiamento[i] = equipArray->equipaggiamento[i + 1];
                        bool = 1;
                    }
                    else {
                        equipArray->equipaggiamento[i] = -1;
                    }
                }
            }
            equipArray->inUso -= 1;
        }
    }
}

int equipArray_getEquipByIndex(equipArray_t equipArray, int index){
    return equipArray->equipaggiamento[index];
}

void ritornoStat(int *hp, int *mp, int *atk, int *def, int *mag, int *spr, equipArray_t equipArray, invArray_t invArray){
    int i;
    for (i=0; i < equipArray_inUse(equipArray); i++) {
        invArray_stat(hp, mp, atk, def, mag, spr, equipArray->equipaggiamento[i], invArray);
    }
}