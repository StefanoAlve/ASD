#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "personaggi.h"

#define MAXC 50

typedef enum {StorePG, StoreINV, InsertPG, DeletePG, InsertEquip, DeleteEquip, StatCalc, end} comando;

comando StampaMENU();
void EseguiComando(comando cmd, PG *p_pgs, INV *p_inv);

int main() {
    PG personaggi = NULL;
    INV inventario = NULL;
    comando cm = StampaMENU();
    while(cm != end){
        EseguiComando(cm, &personaggi, &inventario);
        cm = StampaMENU();
    }
    PGLibera(personaggi);
    INVLibera(inventario);
    return 0;
}

comando StampaMENU(){
    comando cmd;
    int scelta;
    printf("\n....MENU....\n");
    printf("1. StorePG: carica l'elenco di personaggi\n");
    printf("2. StoreINV: carica l'elenco di oggetti\n");
    printf("3. InsertPG: aggiungi un nuovo personaggio\n");
    printf("4. DeletePG: elimina un personaggio\n");
    printf("5. InsertEquip: aggiungi oggetto all'equipaggiamento di un personaggio\n");
    printf("6. DeleteEquip: rimuovi oggetto dall'equipaggiamento di un personaggio\n");
    printf("7. StatCalc: calcola statistiche personaggio con l'oggetto equipaggiato\n");
    printf("8. Fine: termina programma\n");
    printf("\nScegli il numero del comando:\n");
    scanf("%d", &scelta);
    cmd = scelta - 1;
    return cmd;
}

void EseguiComando(comando cmd, PG *p_pgs, INV *p_inv){
    char str[MAXC], str2[MAXC];
    pg_t personaggio;
    switch (cmd) {
        case StorePG:
            printf("Inserire nome file personaggi:\n");
            scanf("%s", str);
            *p_pgs = CreaListaPersonaggi(str);
            break;
        case StoreINV:
            printf("Inserire nome file inventario:\n");
            scanf("%s", str);
            *p_inv = RiempiInventario(str);
            break;
        case InsertPG:
            personaggio = PGScan();
            PGInsert(*p_pgs, personaggio);
            break;
        case DeletePG:
            printf("Inserire il codice del personaggio da cancellare:\n");
            scanf("%s", str);
            PGRemove(*p_pgs, str);
            break;
        case InsertEquip:
            printf("Inserire codice personaggio e nome oggetto da equipaggiare:\n");
            scanf("%s %s", str, str2);
            PGInsertEquip(*p_pgs, *p_inv, str, str2);
            break;
        case DeleteEquip:
            printf("Inserire codice personaggio e nome oggetto da togliere:\n");
            scanf("%s %s", str, str2);
            PGRemoveEquip(*p_pgs, *p_inv, str, str2);
            break;
        case StatCalc:
            printf("Inserire il codice del personaggio:\n");
            scanf("%s", str);
            personaggio = PGCodSearch(*p_pgs, str);
            if(!PgCheckVoid(personaggio)){
                if (personaggio.equip->inUso == -1){
                    printf("Nessun oggetto in uso\n");
                    break;
                }
                printf("Dettagli Personaggio con equipaggiamento in uso:\n");
                personaggio.stat.hp += personaggio.equip->vettEq[personaggio.equip->inUso]->stat.hp;
                if (personaggio.stat.hp < 0) personaggio.stat.hp = 0;
                personaggio.stat.spr += personaggio.equip->vettEq[personaggio.equip->inUso]->stat.spr;
                if (personaggio.stat.spr < 0) personaggio.stat.spr = 0;
                personaggio.stat.def += personaggio.equip->vettEq[personaggio.equip->inUso]->stat.def;
                if (personaggio.stat.def < 0) personaggio.stat.def = 0;
                personaggio.stat.atk += personaggio.equip->vettEq[personaggio.equip->inUso]->stat.atk;
                if (personaggio.stat.atk < 0) personaggio.stat.atk = 0;
                personaggio.stat.mp += personaggio.equip->vettEq[personaggio.equip->inUso]->stat.mp;
                if (personaggio.stat.mp < 0) personaggio.stat.mp = 0;
                personaggio.stat.mag += personaggio.equip->vettEq[personaggio.equip->inUso]->stat.mag;
                if (personaggio.stat.mag < 0) personaggio.stat.mag = 0;
                PGPrint(personaggio);
            } else printf("Codice non valido\n");
            break;
        default:
            break;
    }
}