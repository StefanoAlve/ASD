#include "invArray.h"

struct invArray_s{
    inv_t *vettInv;
    int nInv;
};

/* creatore e disruttore */
invArray_t invArray_init(){
    invArray_t inventario;
    inventario = (invArray_t)malloc(sizeof(*inventario));
    inventario->nInv = 0;
    return inventario;
}

void invArray_free(invArray_t invArray){
    free(invArray->vettInv);
    free(invArray);
}

/* lettura e scrittura su file */
void invArray_read(FILE *fp, invArray_t invArray){
    if(!feof(fp)){
        fscanf(fp, "%d", &invArray->nInv);
        invArray->vettInv = (inv_t*)malloc(invArray->nInv*sizeof(inv_t));
        for(int i=0; i<invArray->nInv; i++){
            inv_read(fp, &invArray->vettInv[i]);
        }
    }
}
void invArray_print(FILE *fp, invArray_t invArray){
    for(int i=0; i<invArray->nInv; i++){
        inv_print(fp, &invArray->vettInv[i]);
    }
}
/* stampa un unico oggetto selezionato da indice (nel vettore) */
void invArray_printByIndex(FILE *fp, invArray_t invArray, int index){
    inv_print(fp, &invArray->vettInv[index]);
}
/* ritorna puntatore a oggetto selezionato da indice (nel vettore) */
inv_t *invArray_getByIndex(invArray_t invArray, int index){
    return &invArray->vettInv[index];
}
/* ritorna indice (nel vettore) a oggetto selezionato da nome */
int invArray_searchByName(invArray_t invArray, char *name){
    int index = -1, trovato = 0;
    for(int i=0; i<invArray->nInv && !trovato; i++){
        if(strcasecmp(name, invArray->vettInv[i].nome)){
            index = i;
            trovato = 1;
        }
    }
    if(index == -1){
        printf("\nNessun oggetto trovato con il nome inserito");
    }
    return index;
}