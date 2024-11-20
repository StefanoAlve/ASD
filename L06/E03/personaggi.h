#ifndef E03_PERSONAGGI_H
#define E03_PERSONAGGI_H

#include "inventario.h"
#define MAXEquip 8

typedef struct wrapperPG *PG;
typedef struct nodoPG *link;
typedef struct Equip_t *p_equip;

typedef struct{
    char *codice, *nome, *classe;
    p_equip equip;
    stat_t stat;
} pg_t;

struct Equip_t{
    int inUso;
    inv_t *vettEq[MAXEquip];
};

struct nodoPG{
    pg_t val;
    link next;
};

struct wrapperPG{
    link headPG, tailPG;
    int nPG;
};

link NewNodePG(pg_t val, link next);
pg_t VoidPg();
int PgCheckVoid(pg_t tmp);
void PGLiberaNode(link x);
void PGLibera(PG pg);
PG CreaListaPersonaggi(char *nomefile);
pg_t PGScan();
void PGInsert(PG pg, pg_t val);
void PGRemove(PG pg, char *codice);
pg_t PGCodSearch(PG pg, char *codice);
void PGPrint(pg_t tmp);
void PGInsertEquip(PG pg, INV inv, char *codice, char *nome);
void PGRemoveEquip(PG pg, INV inv, char *codice, char *nome);


#endif //E03_PERSONAGGI_H
