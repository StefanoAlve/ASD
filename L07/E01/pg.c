#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "pg.h"

int pg_read(FILE *fp, pg_t *pgp){
    int num = fscanf(fp, "%s %s %s", pgp->cod, pgp->nome, pgp->classe);
    stat_read(fp, &pgp->b_stat);
    pgp->eq_stat = pgp->b_stat;
    pgp->equip = equipArray_init();
    return num;
}

void pg_print(FILE *fp, pg_t *pgp, invArray_t invArray){
    printf("\nCodice: %s\nNome: %s\nClasse: %s\nStatistiche Personaggio:\n", pgp->cod, pgp->nome, pgp->classe);
    stat_print(fp, &pgp->b_stat, 0);
    printf("Statistiche con equipaggiamento:\n");
    stat_print(fp, &pgp->eq_stat, 1);
    printf("Oggetti equipaggiati:\n");
    equipArray_print(fp, pgp->equip, invArray);
}

void pg_clean(pg_t *pgp){
    equipArray_free(pgp->equip);
}

void pg_updateEquip(pg_t *pgp, invArray_t invArray){
    equipArray_update(pgp->equip, invArray);
    pgp->eq_stat = pgp->b_stat;
    for (int i = 0; i < EQUIP_SLOT; i++){
        int j = equipArray_getEquipByIndex(pgp->equip, i);
        if (j != -1){
            inv_t *p = invArray_getByIndex(invArray, j);
            CalcolaStat(&p->stat, &pgp->eq_stat);
        }
    }
}

void CalcolaStat(stat_t *s, stat_t *sp){
    sp->hp += s->hp;
    sp->mp += s->mp;
    sp->atk += s->atk;
    sp->def += s->def;
    sp->mag += s->mag;
    sp->spr += s->spr;
}
