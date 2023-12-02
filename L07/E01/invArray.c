#include "invArray.h"

/* ADT di prima classe collezione di oggetti di inventario */
struct invArray_s{
    inv_t *vettInv;
    int nInv;
};

/* creatore e disruttore */
invArray_t invArray_init()
{
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
    int n_ogg;
    if(fp != NULL)
    {
        fscanf(fp, "%d ", &n_ogg);
        invArray->vettInv = (inv_t*)malloc(n_ogg*sizeof(inv_t));
        invArray->nInv = n_ogg;
        for(int i =0 ; i < n_ogg; i++)
            inv_read(fp, &invArray->vettInv[i]);
    }
}
void invArray_print(FILE *fp, invArray_t invArray){
    int i, n_ogg = invArray->nInv;
    for(i = 0; i < n_ogg; i++)
        inv_print(fp, invArray_getByIndex(invArray, i));
}
/* stampa un unico oggetto selezionato da indice (nel vettore) */
void invArray_printByIndex(FILE *fp, invArray_t invArray, int index){
    inv_print(fp, invArray_getByIndex(invArray, index));
}
/* ritorna puntatore a oggetto selezionato da indice (nel vettore) */
inv_t *invArray_getByIndex(invArray_t invArray, int index){
    return &(invArray->vettInv[index]);
}
/* ritorna indice (nel vettore) a oggetto selezionato da nome */
int invArray_searchByName(invArray_t invArray, char *name){
    int index = -1, i, flag = 0;
    int n_oggetti = invArray->nInv;
    for(i = 0; i < n_oggetti && !flag; i++)
    {
        if(!strcasecmp(name, invArray->vettInv[i].nome)){
            index = i;
            flag = 1;
        }
    }
    if(index < 0)
        printf("\nNessun oggetto trovato con il nome '%s'", name);
    return index; // se non trova, ritorna -1
}