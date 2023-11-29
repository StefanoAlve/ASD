#include "pg.h"

struct tabEquip_t{
    int inUso;
    int vettEq[MAXOBJ];
    int last;
};

struct tabPg_t{
    nodoPg_t headPg;
    nodoPg_t tailPg;
    int nPg;
};