#include "invArray.h"

struct invArray_s{
    inv_t *inv;
    int nInv;
    int maxInv;
};

//alloco la struct inventario
invArray_t invArray_init(){
    invArray_t invArray = malloc(sizeof(*invArray));
    return invArray;
}
//dealloco la struct inventario
void invArray_free(invArray_t invArray){
    int i;

    for (i=0; i<invArray->nInv; i++) {
        free(invArray->inv);
    }
    free(invArray);
}
//leggo da file l'inventario
void invArray_read(FILE *fp, invArray_t invArray){
    int i;

    invArray->maxInv = MAXOBJ;
    fscanf(fp, "%d", &invArray->nInv);
    invArray->inv = malloc((invArray->nInv)*sizeof(* invArray->inv));

    for (i=0; i<invArray->nInv; i++) {
        inv_read(fp, &invArray->inv[i]);
    }

}
//printa su file gli oggetti
void invArray_print(FILE *fp, invArray_t invArray){
    int i;
    for (i=0; i<invArray->nInv; i++) {
        inv_print(fp, &invArray->inv[i]);
    }
}
//printa un campo degli oggetti dato un indice
void invArray_printByIndex(FILE *fp, invArray_t invArray, int index){
    if(index < invArray->nInv) {
        inv_print(fp, &invArray->inv[index]);
    }
    else
        printf("non è presente nessun oggetto in quella posizione\n");
}
//cerca l'oggetto dato l'index
inv_t *invArray_getByIndex(invArray_t invArray, int index){
    return &invArray->inv[index];
}
//cerca l'index dato il nome dell'oggetto
int invArray_searchByName(invArray_t invArray, char *name){
    int i;
    for (i=0; i < invArray->nInv; i++) {
        if(inv_compareName(&invArray->inv[i], name) == 0) {
            return i;
        }
    }
    printf("non e' stato trovato l'oggetto con questo nome\n");
    return -1;
}
//stampa tutto l'inventario a video
void invArray_printVideo(invArray_t invArray) {
    int i;
    for (i=0; i<invArray->nInv; i++) {
        printf("%d\t", i);
        inv_printVideo(&invArray->inv[i]);
    }
}
//modifica le stat dei puntatori con i valori dell'oggetto
void invArray_stat(int *hp, int *mp, int *atk, int *def, int *mag, int *spr, int index, invArray_t invArray){
    *hp += invArray->inv[index].stat.hp;
    *mp += invArray->inv[index].stat.mp;
    *atk += invArray->inv[index].stat.atk;
    *def += invArray->inv[index].stat.def;
    *mag += invArray->inv[index].stat.mag;
    *spr += invArray->inv[index].stat.spr;
}