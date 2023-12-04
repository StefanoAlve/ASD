#include "pg.h"

//legge e inizializza un personaggio
int pg_read(FILE *fp, pg_t *pgp){
    fscanf(fp, "%s %s %s", pgp->cod, pgp->nome, pgp->classe);
    fscanf(fp, "%d %d %d %d %d %d", &pgp->b_stat.hp, &pgp->b_stat.mp, &pgp->b_stat.atk, &pgp->b_stat.def, &pgp->b_stat.mag, &pgp->b_stat.spr);
    pgp->eq_stat.hp = 0;
    pgp->eq_stat.mp = 0;
    pgp->eq_stat.atk = 0;
    pgp->eq_stat.def = 0;
    pgp->eq_stat.mag = 0;
    pgp->eq_stat.spr = 0;
    pgp->equip = equipArray_init();
    return 1;
}
//printa il personaggio
void pg_print(FILE *fp, pg_t *pgp, invArray_t invArray){
    fprintf(fp, "%s %s %s stat( ", pgp->cod, pgp->nome, pgp->classe);
    printaStat(pgp->b_stat.hp, pgp->eq_stat.hp, fp);
    printaStat(pgp->b_stat.mp, pgp->eq_stat.mp, fp);
    printaStat(pgp->b_stat.atk, pgp->eq_stat.atk, fp);
    printaStat(pgp->b_stat.def, pgp->eq_stat.def, fp);
    printaStat(pgp->b_stat.mag, pgp->eq_stat.mag, fp);
    printaStat(pgp->b_stat.spr, pgp->eq_stat.spr, fp);
    fprintf(fp, ")");
    equipArray_print(fp, pgp->equip, invArray);
    fprintf(fp,"\n");
}
//vede se le stat sono <1 e printa di conseguenza
void printaStat(int val, int eq, FILE *fp){
    if(val + eq < 1)
        fprintf(fp, "%d ", 1);
    else
        fprintf(fp, "%d ", val + eq);

}

void pg_clean(pg_t *pgp){
    equipArray_free(pgp->equip);
}



void pg_updateEquip(pg_t *pgp, invArray_t invArray){
    equipArray_update(pgp->equip, invArray);
    pgp->eq_stat.hp = 0;
    pgp->eq_stat.mp = 0;
    pgp->eq_stat.atk = 0;
    pgp->eq_stat.def = 0;
    pgp->eq_stat.mag = 0;
    pgp->eq_stat.spr = 0;
    ritornoStat(&pgp->eq_stat.hp, &pgp->eq_stat.mp, &pgp->eq_stat.atk, &pgp->eq_stat.def, &pgp->eq_stat.mag, &pgp->eq_stat.spr, pgp->equip, invArray);

}

