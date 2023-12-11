#include "equipArray.h"

struct equipArray_s{
    int vettEq[EQUIP_SLOT];
    int usati;
};
/* creatore e disruttore */
equipArray_t equipArray_init(){
    equipArray_t equipaggiamento;
    equipaggiamento = (equipArray_t)malloc(sizeof(*equipaggiamento));
    equipaggiamento->usati = 0;
    for(int i=0; i< EQUIP_SLOT; i++){
        equipaggiamento->vettEq[i] = -1;
    }
    return equipaggiamento;
}
void equipArray_free(equipArray_t equipArray){
    free(equipArray);
}

/* quanti equipaggiamenti sono in uso */
int equipArray_inUse(equipArray_t equipArray){
    return equipArray->usati;
}

/* scrittura su file */
void equipArray_print(FILE *fp, equipArray_t equipArray, invArray_t invArray){
    for(int i=0; i<EQUIP_SLOT; i++){
        if(i != -1){
            invArray_printByIndex(fp, invArray, i);
        }
    }
}
/* modifica equipaggiamento scegliendo un oggetto da inventario */
void equipArray_update(equipArray_t equipArray, invArray_t invArray){
    char nome[LEN];
    int usati = equipArray_inUse(equipArray), index = -1, comando;
    printf("\nCosa vuoi fare?\n1)Aggiungere equipaggiamento;\n2)Rimuovere equipaggiamento\nScelta:");
    scanf("%d", &comando);
    if(comando == 1){
        if(usati < EQUIP_SLOT){
            printf("Inserisci il nome dell'oggetto da inserire nell'equipaggiamento:");
            scanf("%s", nome);
            index = invArray_searchByName(invArray, nome);
            if(index >= 0){
                for(int i=0; i<EQUIP_SLOT; i++){
                    if(equipArray->vettEq[i] == -1){
                        equipArray->vettEq[i] = index;
                        equipArray->usati++;
                        printf("\nOggetto inserito!\n");
                        break;
                    }
                }
            }
        }
        else{
            printf("Equipaggiamento pieno!\n");
        }
    }
    else if(comando == 2){
        if(usati > 0){
            printf("Inserisci il nome dell'oggetto da rimuovere:");
            scanf("%s",nome);
            index = invArray_searchByName(invArray, nome);
            if(index != -1){
                equipArray->vettEq[index] = -1;
                equipArray->usati--;
            }
        }
        else{
            printf("\nNon sono presenti oggetti nell'equipaggiamento!\n");
        }
    }
    else{
        printf("Comando inesistente!\n");
    }
}
/* torna indice (nel vettore inventario) dell'oggetto in posizione index (0..EQUIP_SLOT-1) di equipArray */
int equipArray_getEquipByIndex(equipArray_t equipArray, int index){
    return equipArray->vettEq[index];
}
