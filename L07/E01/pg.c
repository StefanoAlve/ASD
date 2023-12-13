#include "pg.h"

/* lettura e scrittura su file */
int pg_read(FILE *fp, pg_t *pgp){
    if(fp != NULL) {
        if (!feof(fp)) {
            fscanf(fp, "%s %s %s ", pgp->cod, pgp->nome, pgp->classe);
            stat_read(fp, &pgp->b_stat);
            pgp->eq_stat = statInitVoid();
            pgp->equip = equipArray_init();
            return 1;
        }
        return 0;
    }
    return 0;
}
/* non essendo struct dinamica, pulisce chiamando il distruttire di equipArray */
void pg_clean(pg_t *pgp){
    equipArray_free(pgp->equip);
}

void pg_print(FILE *fp, pg_t *pgp, invArray_t invArray){
    stat_t tmpStat = pg_stat_tot(pgp);
    int tmp;
    if(fp!=NULL){
        fprintf(fp, "\nCODICE: %s; NOME: %s; CLASSE: %s\n", pgp->cod, pgp->nome, pgp->classe);
        stat_print(fp, &tmpStat,1);
        for(int i=0; i<EQUIP_SLOT; i++){
            tmp = equipArray_getEquipByIndex(pgp->equip,i);
            if(tmp!=-1){
                invArray_printByIndex(fp, invArray, tmp);
            }
        }
    }
}
/* modifica personaggio aggiungendo/togliendo un equipaggiamento selezionato da inventario:
di fatto e' sufficiente chiamare l'opportuna funzione dal modulo equipArray */
void pg_updateEquip(pg_t *pgp, invArray_t invArray){
    equipArray_update(pgp->equip, invArray);
    pgp->eq_stat = equip_value(pgp->equip, invArray);
}

stat_t pg_stat_tot(pg_t *pgp){
    stat_t statCompl;
    statCompl.hp = pgp->eq_stat.hp+pgp->b_stat.hp;
    statCompl.mp = pgp->eq_stat.mp+pgp->b_stat.mp;
    statCompl.atk = pgp->eq_stat.atk+pgp->b_stat.atk;
    statCompl.def = pgp->eq_stat.def+pgp->b_stat.def;
    statCompl.mag = pgp->eq_stat.mag+pgp->b_stat.mag;
    statCompl.spr = pgp->eq_stat.spr+pgp->b_stat.spr;

    return statCompl;
}