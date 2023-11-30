//
// Created by Gabriele on 30/11/2023.
//

#ifndef E03_PERSONAGGI_H
#define E03_PERSONAGGI_H
#ifndef E03_INVENTARIO_H
#include "inventario.h"
#endif //E03_INVENTARIO_H
#define MAXCODE 7

typedef struct tabEquip_t *ptabEquip_t;
typedef struct pg_t *pnodoPg_t;
struct pg_t{
    char codice[MAXCODE];
    char nome[MAXC];
    char classe[MAXC];
    ptabEquip_t equip;
    stat_t stat;
    pnodoPg_t next;
};
typedef struct tabPg_t *ptabPg;
ptabPg leggiPersonaggi(char *nomeFile);
pnodoPg_t newNode(pnodoPg_t head, struct pg_t personaggio);
ptabPg inserisciPg(ptabPg tabPg, struct pg_t personaggio);
pnodoPg_t ricercaCodice(ptabPg tabPg, char nome[]);
ptabPg cancellaPg(ptabPg tapPg, pnodoPg_t personaggio);
void stampaPg(pnodoPg_t personaggio);
void stampaPgCode(pnodoPg_t personaggio);
void stampaPgNome(pnodoPg_t personaggio);
void stampaPgClasse(pnodoPg_t personaggio);
void stampaPgEquip(pnodoPg_t personaggio);
void stampaPgStat(pnodoPg_t personaggio);
void modificaEquip(pnodoPg_t personaggio, ptabInv inventario);
void aggiungiObj(ptabEquip_t equip, ptabInv inventario, char obj[]);
void rimuoviObj(ptabEquip_t equip, ptabInv inventario, char obj[]);
void scegliInUso(pnodoPg_t personaggio, char obj[]);


#endif //E03_PERSONAGGI_H
