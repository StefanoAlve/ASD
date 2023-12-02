#include "pgList.h"

typedef struct nodo *link;
struct nodo{
    pg_t pg;
    link next;
};

struct pgList_s
{
    link head;
    link tail;
    int n_pg;
};

/* creatore e distruttore */
pgList_t pgList_init(){
    pgList_t personaggi;
    personaggi = (pgList_t)malloc(sizeof(*personaggi));
    personaggi->head = personaggi->tail = NULL;
    personaggi->n_pg = 0;
    return personaggi;
}
void pgList_free(pgList_t pgList)
{
    link x = pgList->head;
    for(; x != NULL; x = x->next)
    {
        x = pgList->head->next;
        pg_clean(&pgList->head->pg);
        pgList->head = x;
    }
}
link new_node(link next, pg_t personaggio)
{
    link node = (link)malloc(sizeof(*node));
    node->next = next;
    node->pg = personaggio;
    node->pg.equip = equipArray_init();
    return node;
}
/* lettura e scrittura su file */
void pgList_read(FILE *fp, pgList_t pgList)
{
    pg_t tmp;
    while(!feof(fp))
    {
        if(!feof(fp)){
            pg_read(fp, &tmp);
            pgList_insert(pgList, tmp);
        }
    }
}
void pgList_print(FILE *fp, pgList_t pgList, invArray_t invArray)
{
    link x;
    for(x = pgList->head; x != NULL; x = x->next){
        pg_print(fp, &(x->pg), invArray);
        printf("\n");
    }
}
/* inserimento di un nuovo personaggio */
void pgList_insert(pgList_t pgList, pg_t pg)
{
    if(pgList->head == NULL){
        pgList->head = new_node(pgList->head, pg);
        pgList->tail = pgList->head;
    }
    else{
        pgList->tail->next = new_node(pgList->tail->next, pg);
        pgList->tail = pgList->tail->next;
    }
    pgList->n_pg++;
}
/* cancellazione con rimozione */
void pgList_remove(pgList_t pgList, char* cod)
{
    link p = pgList->head,x;
    int trovato = 0;
    pg_t *tmp = pgList_searchByCode(pgList, cod);
    pg_clean(tmp);
    if(&(p->pg) == tmp){
        pgList->head = pgList->head->next;
        free(p);
    }
    for(x = pgList->head->next; !trovato && x != NULL;p=x, x = x->next){
        if(&(x->pg) == tmp)
        {
            p->next = x->next;
            free(x);
            trovato = 1;
        }
    }
}
/* ricerca per codice, ritornando il puntatore */
pg_t *pgList_searchByCode(pgList_t pgList, char* cod)
{
    link x;
    int found;
    for(x = pgList->head; x != NULL; x=x->next)
    {
        if(!strcasecmp(x->pg.cod, cod))
        {
            found = 1;
            return &(x->pg);
        }
    }
    return NULL;
}
