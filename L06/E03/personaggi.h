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
PG CreaListaPersonaggi(char *nomefile);




#endif //E03_PERSONAGGI_H
