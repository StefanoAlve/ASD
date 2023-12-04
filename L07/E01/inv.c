#include "inv.h"

//legge da file le stat dell'oggetto
void stat_read(FILE *fp, stat_t *statp){
    fscanf(fp, "%d %d %d %d %d %d", &statp->hp, &statp->mp, &statp->atk, &statp->def, &statp->mag, &statp->spr );
}
//printa su file le stat di un oggetto
void stat_print(FILE *fp, stat_t *statp, int soglia) {
    //stampo le stat dell'oggetto

    fprintf(fp, "%d ", statp->hp);
    fprintf(fp, "%d ", statp->mp);
    fprintf(fp, "%d ", statp->atk);
    fprintf(fp, "%d ", statp->def);
    fprintf(fp, "%d ", statp->mag);
    fprintf(fp, "%d ", statp->spr);
}
//legge da file un oggetto
void inv_read(FILE *fp, inv_t *invp){
    fscanf(fp, "%s %s ", invp->nome, invp->tipo);
    stat_read(fp, &invp->stat);
}
//printa su file un oggeto
void inv_print(FILE *fp, inv_t *invp){
    fprintf(fp, "%s %s, ", invp->nome, invp->tipo);
    stat_print(fp, &invp->stat , MIN_STAT);
    fprintf(fp, "\n");

}
//ritorna al chiamante il campo stat dell' oggetto
stat_t inv_getStat(inv_t *invp){
    return invp->stat;
}
//compara il nome dell'oggetto con un nome dato in input
int inv_compareName(inv_t *invp, char *name) {
    return strcasecmp(invp->nome, name);
}
//funzione che stampa a video
void inv_printVideo(inv_t *invp) {
    printf("%s\n", invp->nome   );
}