#include "inv.h"

/* funzioni di input/output delle statistiche */
void stat_read(FILE *fp, stat_t *statp){
    fscanf(fp, "%d %d %d %d %d %d", &(statp->hp), &(statp->mp), &(statp->atk), &(statp->def), &(statp->mag), &(statp->spr));
}
void stat_print(FILE *fp, stat_t *statp, int soglia){
    int i;
    int stats[6];
    stats[0] = statp->hp; stats[1] = statp->mp; stats[2] = statp->atk; stats[3] = statp->def; stats[4] = statp->mag; stats[5] = statp->spr;
    for(i = 0; i< 6; i++) {
        if (stats[i] < soglia) {
            stats[i] = soglia;
        }
    }
    fprintf(fp, "HP = %d ; MP = %d ; ATK = %d ; DEF = %d ; MAG = %d ; SPR = %d", stats[0], stats[1], stats[2], stats[3], stats[4], stats[5]);
}

stat_t statInitVoid(){
    stat_t stat;
    stat.mp=stat.def=stat.spr=stat.atk=stat.mag=stat.hp=0;
    return stat;
}
/* funzioni di input/output di un oggetto dell'inventario */
void inv_read(FILE *fp, inv_t *invp){
    if(!feof(fp)){
        fscanf(fp,"%s %s ", invp->nome, invp->tipo);
        stat_read(fp, &(invp->stat));
    }
}

/* ritorna il campo stat di un oggetto dell'inventario */
void inv_print(FILE *fp, inv_t *invp){
    if(fp != NULL){
        fprintf(fp, "\n%s %s ", invp->nome, invp->tipo);
        stat_print(fp, &invp->stat, MIN_STAT);
    }
}

stat_t inv_getStat(inv_t *invp){
    return invp->stat;
}