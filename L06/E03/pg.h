#ifndef E03_PG_H
#define E03_PG_H
#include "inv.h"
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
pnodoPg_t newNode(pnodoPg_t next, struct pg_t personaggio);
ptabPg inserisciPg(ptabPg tabPg, struct pg_t personaggio);
pnodoPg_t ricercaCodice(ptabPg tabPg, char codice[]);
ptabPg cancellaPg(ptabPg tapPg, pnodoPg_t personaggio);
void stampaPg(pnodoPg_t personaggio, ptabInv inventario);
void stampaPgCode(pnodoPg_t personaggio);
void stampaPgNome(pnodoPg_t personaggio);
void stampaPgClasse(pnodoPg_t personaggio);
void stampaPgEquip(pnodoPg_t personaggio, ptabInv inventario);
void stampaPgStat(pnodoPg_t personaggio);
void aggiungiObj(pnodoPg_t personaggio, ptabInv inventario, char obj[]);
void rimuoviObj(pnodoPg_t personaggio, ptabInv inventario, char obj[]);
void scegliInUso(pnodoPg_t personaggio, ptabInv inventario, char obj[]);
void distruggiListaPersonaggi(ptabPg listaPers);
#endif //E03_PG_H
