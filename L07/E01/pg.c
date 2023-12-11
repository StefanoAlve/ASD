#include "pg.h"

//TODO implementare pg.c

/* lettura e scrittura su file */
int pg_read(FILE *fp, pg_t *pgp){
    if(fp != NULL) {
        if (!feof(fp)) {
            fscanf(fp, "%s %s %s ", pgp->cod, pgp->nome, pgp->classe);
            stat_read(fp, &pgp->b_stat);
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

void pg_print(FILE *fp, pg_t *pgp, invArray_t invArray){//TODO
}
/* modifica personaggio aggiungendo/togliendo un equipaggiamento selezionato da inventario:
di fatto e' sufficiente chiamare l'opportuna funzione dal modulo equipArray */
void pg_updateEquip(pg_t *pgp, invArray_t invArray){
    equipArray_update(pgp->equip, invArray);
    //TODO FINIRE FUNZIONE MANCA AGGIORNAMENTO STATISTICHE PERSONAGGIO
}