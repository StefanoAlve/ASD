#include "pgList.h"
//lista dei personaggi
struct pgList_s {
    pg_t personaggio;
    pgList_t next;
};

pgList_t pgList_init(){
    //inizializzo l'head
    pgList_t pgList = malloc(sizeof (*pgList));
    pgList = NULL;
    return pgList;
}
void pgList_free(pgList_t pgList){
    //libero tutti i campi della lista, personaggi compresi
    pgList_t x, p;
    for (x = pgList, p = x->next; p != NULL ; x = p, p = x->next){
        pg_clean(&x->personaggio);
        free(x);
    }
    pg_clean(&x->personaggio);
    free(x);

}
pgList_t pgList_read(FILE *fp, pgList_t pgList){
//    leggo da file i peronaggi e li inserisco nella lista ramite 2 funzioni
    pg_t pg;
    while(!feof(fp)) {
        pg_read(fp, &pg);
        pgList = pgList_insert(pgList, pg);
    }
    return pgList;
}
//stampa su file della lista tramite funzione in pg.c
void pgList_print(FILE *fp, pgList_t pgList, invArray_t invArray){
    pgList_t x;
    for (x = pgList; x != NULL; x = x->next) {
        pg_print(fp, &x->personaggio, invArray);
    }
}
//inserimento in coda del personaggio
pgList_t pgList_insert(pgList_t pgList, pg_t pg){
    pgList_t x, newNode = malloc(sizeof(*newNode));
    newNode->personaggio = pg;
    newNode->next = NULL;
    if(pgList == NULL){
        pgList = newNode;
    }
    else {
        for (x = pgList; x->next != NULL; x = x->next);
        x->next = newNode;
    }
    return pgList;
}
//rimozione di un personaggio dato il codice
pgList_t pgList_remove(pgList_t pgList, char *cod){
    pgList_t x, p;
    //itero fino a corrispondenza trovata
    for (x = pgList, p = NULL; x != NULL  ; p = x, x = x->next) {
        if (strcmp(x->personaggio.cod,cod) == 0) {
            if(x == pgList) //caso di lista con un elemento
                pgList = x->next;
            else
                p->next = x->next;
            pg_clean(&x->personaggio);
            free(x);
            break;
        }
    }

    return pgList;
}
//ricerca di un elemento dato un odice
pg_t *pgList_searchByCode(pgList_t pgList, char* cod){
    pgList_t x;

    for (x = pgList; x != NULL  ; x = x->next) {
        if (strcmp(x->personaggio.cod,cod) == 0) {
            return &x->personaggio;
        }
    }
    printf("non e' stato trovato l'elemento \n");
    return NULL;
}
