#include "pgList.h"

struct node{
    pg_t pg;
    link next;
};

struct pgList_s{
    link head;
    link tail;
    int nPg;
};

/* creatore e distruttore */
pgList_t pgList_init(){
    pgList_t pgList;
    pgList = (pgList_t)malloc(sizeof(*pgList));
    pgList->head=pgList->tail=NULL;
    pgList->nPg=0;
    return pgList;
}
void pgList_free(pgList_t pgList){
    link corrente=pgList->head, successivo;
    while(corrente != NULL){
        successivo = corrente->next;
        pg_clean(&corrente->pg);
        free(corrente);
        corrente = successivo;
    }
}

/* lettura e scrittura su file */
void pgList_read(FILE *fp, pgList_t pgList){
    pg_t pg;
    if(fp != NULL){
        //Inizializzo lista
        while(!feof(fp)){
            //Leggo il personaggio
            if (pg_read(fp, &pg) == 1) {
                //Inserisco il nuovo personaggio in lista
                pgList_insert(pgList, pg);
            } else {
                printf("Errore nella lettura del personaggio!\n");
                exit(1);
            }
        }
    }
}
void pgList_print(FILE *fp, pgList_t pgList, invArray_t invArray){
    link x;
    for(x=pgList->head; x!=NULL; x=x->next){
        pg_print(fp, &x->pg, invArray);
    }
}

/* inserimento di un nuovo personaggio */
void pgList_insert(pgList_t pgList, pg_t pg){
    if(pgList->head == NULL){
        //Inserisco il nuovo nodo
        pgList->head = new_node(pg, pgList->tail);
        //Aggiorno anche la coda essendo l'unico elemento
        pgList->tail = pgList->head;
    }
    else{
        //Aggiungo il nuovo elemento in coda
        pgList->tail->next = new_node(pg, NULL);
        //Aggiorno la coda
        pgList->tail = pgList->tail->next;
    }
    pgList->nPg++;
}
/* cancellazione con rimozione */
void pgList_remove(pgList_t pgList, char* cod){
    link corrente, precedente;
    if(pgList->head == NULL){
        printf("Lista vuota!\n");
        return;
    }
    for(precedente = NULL, corrente = pgList->head; corrente!=NULL; precedente=corrente, corrente = corrente->next) {
        if (strcmp(corrente->pg.cod, cod) == 0) {
            if(corrente == pgList->head){ //Se sono sulla head
                pgList->head = corrente->next;
            }
            else{
                precedente->next = corrente->next;
            }
            pg_clean(&corrente->pg);
            free(corrente);
            return;
        }
    }
    printf("Codice inesistente!\n");
}
/* ricerca per codice, ritornando il puntatore */
pg_t *pgList_searchByCode(pgList_t pgList, char* cod){
    link x;
    for(x=pgList->head; x!=NULL; x=x->next){
        if(strcasecmp(x->pg.cod,cod) == 0){
            return &x->pg;
        }
    }
    return NULL;
}

link new_node(pg_t pg, link next){
    link node = (link)malloc(sizeof(struct node));
    strcpy(node->pg.nome, pg.nome);
    strcpy(node->pg.classe, pg.classe);
    strcpy(node->pg.cod, pg.cod);
    node->pg.equip = pg.equip;
    node->pg.b_stat = pg.b_stat;
    node->pg.eq_stat = pg.eq_stat;
    node->next=next;
    return node;
}