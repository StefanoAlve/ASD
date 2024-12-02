#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "inv.h"

void inv_read(FILE *fp, inv_t *invp){
    fscanf(fp, "%s %s", invp->nome, invp->tipo);
    stat_read(fp, &invp->stat);
}

void stat_read(FILE *fp, stat_t *statp){
    fscanf(fp, "%d %d %d %d %d %d", &statp->hp, &statp->mp, &statp->atk, &statp->def, &statp->mag, &statp->spr);
}

void stat_print(FILE *fp, stat_t *statp, int soglia){
    if (soglia == 0)
        fprintf(fp,"HP: %d\nMP: %d\nATK: %d\nDEF: %d\nMAG: %d\nSPR: %d\n", statp->hp, statp->mp, statp->atk, statp->def, statp->mag, statp->spr);
    else {
        fprintf(fp, "HP: %d\n", statp->hp <= 0 ? MIN_STAT : statp->hp);
        fprintf(fp, "MP: %d\n", statp->mp <= 0 ? MIN_STAT : statp->mp);
        fprintf(fp, "ATK: %d\n", statp->atk <= 0 ? MIN_STAT : statp->atk);
        fprintf(fp, "DEF: %d\n", statp->def <= 0 ? MIN_STAT : statp->def);
        fprintf(fp, "MAG: %d\n", statp->mag <= 0 ? MIN_STAT : statp->mag);
        fprintf(fp, "SPR: %d\n", statp->spr <= 0 ? MIN_STAT : statp->spr);
    }
}

void inv_print(FILE *fp, inv_t *invp){
    fprintf(fp, "Nome: %s\nTipo: %s\n", invp->nome, invp->tipo);
    stat_print(stdout, &invp->stat, 0);
}

stat_t inv_getStat(inv_t *invp){
    return invp->stat;
}