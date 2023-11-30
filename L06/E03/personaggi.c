#include "personaggi.h"

struct tabEquip_t{
    int inUso;
    int vettEq[MAXOBJ];
    int last;
};

struct tabPg_t{
    pnodoPg_t headPg;
    pnodoPg_t tailPg;
    int nPg;
};

ptabPg leggiPersonaggi(char *nomeFile) {
    //Inizializzazione variabili
    FILE *fin;
    ptabPg tabPg = (ptabPg)malloc(sizeof(*tabPg));
    struct pg_t personaggio;

    tabPg->nPg = 0;
    //Apertura file
    fin = fopen(nomeFile, "r");
    if(fin == NULL){
        printf("Errore nell'apertura del file personaggi!\n");
        exit(1);
    }
    while(!feof(fin)) {
        fscanf(fin, "%s %s %s", personaggio.codice, personaggio.nome, personaggio.classe);
        fscanf(fin, "%d %d %d %d %d %d", &personaggio.stat.hp, &personaggio.stat.mp, &personaggio.stat.atk, &personaggio.stat.def, &personaggio.stat.mag, &personaggio.stat.spr);
        personaggio.next = NULL;
        newNode(tabPg->headPg, personaggio);
        tabPg->nPg += 1;
        *tabPg->tailPg = personaggio;
    }

    //Chiusura file
    fclose(fin);
    return tabPg;
}

pnodoPg_t newNode(pnodoPg_t head, struct pg_t personaggio) {
    pnodoPg_t x;

    if(head == NULL){
        *head = personaggio;
    }
    for(x = head; x->next!=NULL; x = x->next){}
    *x->next = personaggio;

    return head;
}