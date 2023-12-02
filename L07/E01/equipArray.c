#include "equipArray.h"

struct equipArray_s {
    int vettEq[EQUIP_SLOT];
    int usati;
};



/* creatore e disruttore */
equipArray_t equipArray_init(){
    equipArray_t equipaggiamento;
    equipaggiamento = (equipArray_t)malloc(sizeof(*equipaggiamento));
    equipaggiamento->usati = 0;
    for(int i = 0; i < EQUIP_SLOT; i++)
        equipaggiamento->vettEq[i] = -1;
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
void equipArray_print(FILE *fp, equipArray_t equipArray, invArray_t invArray)
{
    int i, index = -1;
    for(i = 0; i < EQUIP_SLOT; i++) {
        index = equipArray_getEquipByIndex(equipArray, i);
        if (index >= 0)
            invArray_printByIndex(fp, invArray, index);
    }
}
/* modifica equipaggiamento scegliendo un oggetto da inventario */
void equipArray_update(equipArray_t equipArray, invArray_t invArray)
{
    char name[LEN];
    int used = equipArray_inUse(equipArray), index = -1, cmd;
    printf("\nCosa vuoi fare?\n1)Aggiungere equipaggiamento;\n2)Rimuovere equipaggiamento\nScelta:");
    scanf("%d", &cmd);
    if(cmd == 1)
    {
        if(used < EQUIP_SLOT) {
            printf("\nInserisci il nome dell'oggetto da inserire nell'equipaggiamento:");
            scanf("%s", name);
            index = invArray_searchByName(invArray, name);
            if(index >= 0){
                for(int i = 0; i < EQUIP_SLOT; i++)
                    if(equipArray->vettEq[i] == -1)
                    {
                        equipArray->vettEq[i] = index;
                        equipArray->usati++;
                        printf("\nOggetto inserito correttamente!");
                        break;
                    }
            }
        }
        else
            printf("\nL'equipaggiamento per questo personaggio è pieno.");
    }
    else if(cmd == 2)
    {
        if(used > 0)
        {
            printf("\nInserisci il nome dell'oggetto da rimuovere dall'equipaggiamento:");
            scanf("%s", name);
            index = invArray_searchByName(invArray, name);
            if(index >= 0){
                equipArray->vettEq[index] = -1;
                equipArray->usati = equipArray->usati-1;
            }
        }
        else
            printf("\nL'equipaggiamento di questo personaggio è vuoto.");
    }
    else
        printf("\nNon ho compreso il tuo comando");
}
/* torna indice (nel vettore inventario) dell'oggetto in posizione index (0..EQUIP_SLOT-1) di equipArray */
int equipArray_getEquipByIndex(equipArray_t equipArray, int index){
    return equipArray->vettEq[index];
}

stat_t equipArray_value(invArray_t invArray, equipArray_t equipArray)
{
    stat_t total_value;
    total_value.hp = total_value.mp = total_value.atk = total_value.def = total_value.mag = total_value.spr = 0;
    stat_t current_stats;
    inv_t* poggetto;
    for(int i= 0; i < EQUIP_SLOT; i++)
    {
        if(equipArray->vettEq[i] != -1)
        {
            poggetto = invArray_getByIndex(invArray, equipArray->vettEq[i]);
            current_stats = inv_getStat(poggetto);
            total_value.hp += current_stats.hp;
            total_value.mp += current_stats.mp;
            total_value.atk += current_stats.atk;
            total_value.def += current_stats.def;
            total_value.mag += current_stats.mag;
            total_value.spr += current_stats.spr;
        }
    }
    return total_value;
}
