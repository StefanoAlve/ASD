#include "pg.h"



/* lettura e scrittura su file */
int pg_read(FILE *fp, pg_t *pgp)
{
    if(fp != NULL)
    {
        if(!feof(fp))
        {
            fscanf(fp, "%s %s %s ", pgp->cod, pgp->nome, pgp->classe);
            stat_read(fp, &(pgp->b_stat));
            pgp->equip = (equipArray_t)invArray_init();
            return 1;
        }
        return 0;
    }
    return 0;
}
/* non essendo struct dinamica, pulisce chiamando il distruttore di equipArray */
void pg_clean(pg_t *pgp){
    equipArray_free(pgp->equip);
}

void pg_print(FILE *fp, pg_t *pgp, invArray_t invArray){
    if(fp != NULL)
    {
        if(!feof(fp))
        {
            fprintf(fp, "%s %s %s", pgp->cod, pgp->nome, pgp->classe);
            pg_updateStats(invArray, pgp);
            stat_print(fp, &(pgp->eq_stat), MIN_STAT);
        }
    }
}
/* modifica personaggio aggiungendo/togliendo un equipaggiamento selezionato da inventario:
di fatto e' sufficiente chiamare l'opportuna funzione dal modulo equipArray */
void pg_updateEquip(pg_t *pgp, invArray_t invArray){
    equipArray_update(pgp->equip, invArray);
    pg_updateStats(invArray, pgp);
}


void pg_updateStats(invArray_t invArray, pg_t *pgp){
    stat_t current_stats = pgp->b_stat;
    stat_t equipment_stats = equipArray_value(invArray, pgp->equip);
    pgp->eq_stat.hp = current_stats.hp + equipment_stats.hp;
    pgp->eq_stat.mp = current_stats.mp + equipment_stats.mp;
    pgp->eq_stat.atk = current_stats.atk + equipment_stats.atk;
    pgp->eq_stat.def = current_stats.def + equipment_stats.def;
    pgp->eq_stat.mag = current_stats.mag + equipment_stats.mag;
    pgp->eq_stat.spr = current_stats.spr + equipment_stats.spr;
}