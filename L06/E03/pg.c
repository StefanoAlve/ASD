#include "pg.h"
#include <limits.h>
struct tabEquip_t {
    int inUso;
    int vettEq[max_oggetti];
    int usati;
};

struct tabPg_t{
    nodoPg_t headPg;
    nodoPg_t tailPg;
    int nPg;
};

ptabPg inizializza_personaggi(void)
{
    ptabPg lista_pg = (ptabPg)malloc(sizeof(*lista_pg));
    lista_pg->nPg = 0;
    lista_pg->headPg = lista_pg->tailPg = NULL;
    return lista_pg;
}
ptabPg leggi_pg(ptabPg lista_pg, char *file_name)
{
    struct pg_t tmp;
    int n_pg_da_inserire = INT_MAX;
    FILE *fp;
    if(!strcasecmp(file_name, "tastiera")){
        fp = stdin;
        printf("\nQuanti personaggi vuoi inserire?");
        scanf("%d", &n_pg_da_inserire);
    }
    else
        fp = fopen(file_name, "r");
    if(fp != NULL)
    {
        while(n_pg_da_inserire > 0 && fscanf(fp, "%s %s %s %d %d %d %d %d %d", tmp.codice, tmp.nome, tmp.classe, &tmp.stats.hp, &tmp.stats.mp, &tmp.stats.atk, &tmp.stats.def, &tmp.stats.mag, &tmp.stats.spr) == 9)
        {
            lista_pg->nPg++;
            lista_pg = insert_node(lista_pg, tmp);
            n_pg_da_inserire--;
        }
    }
    else{
        printf("\nErrore nell'acquisizione del nuovo personaggio'");
    }
    if(fp != stdin)
        fclose(fp);
    return lista_pg;
}


nodoPg_t new_node(nodoPg_t next, struct pg_t personaggio)
{
    nodoPg_t nodoPg= (nodoPg_t)malloc(sizeof(struct pg_t));
    strcpy(nodoPg->nome, personaggio.nome);
    strcpy(nodoPg->codice, personaggio.codice);
    strcpy(nodoPg->classe, personaggio.classe);
    nodoPg->stats = personaggio.stats;
    nodoPg->equip = personaggio.equip;
    nodoPg->next = next;
    nodoPg->equip = (pTabEquip)malloc(sizeof(*nodoPg->equip));
    nodoPg->equip->inUso = -1;
    for(int i = 0; i< max_oggetti; i++)
        nodoPg->equip->vettEq[i] = -1;
    nodoPg->equip->usati = 0;
    return nodoPg;
}
ptabPg insert_node(ptabPg tabPg, struct pg_t personaggio) // inserzione in coda
{
    if(tabPg->headPg == NULL){
        tabPg->headPg = new_node(tabPg->tailPg, personaggio);
        tabPg->tailPg = tabPg->headPg;
    }
    else{
        tabPg->tailPg->next = new_node(tabPg->tailPg->next, personaggio);
        tabPg->tailPg = tabPg->tailPg->next;
    }
    return tabPg;
}
nodoPg_t ricerca_x_code(ptabPg tabPg, char codice[]) // se non trova nessun personaggio con quel codice ritorna NULL
{
    nodoPg_t found = NULL;
    nodoPg_t x;
    for(x = tabPg->headPg; x != NULL; x = x->next){
        if(!strcasecmp(x->codice, codice))
        {
            found = x;
            return found;
        }
    }
    if(found == NULL)
        printf("\nPersonaggio non trovato.");
    return found;
}

void stampa_tutti_pg(ptabPg personaggi)
{
    int n_pg = 1;
    nodoPg_t tmp = NULL;
    for(tmp = personaggi->headPg; tmp != NULL; tmp = tmp->next) {
        printf("\n\nPG #%d:\nCodice:%s\nNome:%s\nClasse:%s\nSTATS:\nHP:%d MP:%d ATK:%d DEF:%d MAG:%d SPR:%d", n_pg,
               tmp->codice, tmp->nome, tmp->classe, tmp->stats.hp, tmp->stats.mp, tmp->stats.atk, tmp->stats.def,
               tmp->stats.mag, tmp->stats.spr);
        n_pg++;
    }
}
ptabPg cancella_personaggio(ptabPg tabPg, nodoPg_t pg_da_cancellare)
{
    nodoPg_t c,p;
    int found = 0;
    if(pg_da_cancellare != NULL)
    {
        if(strcasecmp(tabPg->headPg->codice, pg_da_cancellare->codice) == 0)
        {
            found = 1;
            c = tabPg->headPg;
            tabPg->headPg = tabPg->headPg->next;
            free(c->equip);
            free(c);
        }
        else
        {
            p = tabPg->headPg;
            for(c = tabPg->headPg->next; c != NULL && !found; p = c, c = c->next)
            {
                if(strcasecmp(c->codice, pg_da_cancellare->codice) == 0)
                {
                    p->next = c->next;
                    found = 1;
                    tabPg->nPg--;
                    free(c->equip);
                    free(c);
                }
            }
        }
        if (found)
            printf("\nPersonaggio eliminato.");
        else
            printf("\nNon sono riuscito a eliminare il personaggio.");
    }
    else
        printf("\nPersonaggio non presente.");

    return tabPg;
}
void stampa_pg_compreso_stats_oggetti(ptabInv inventario, nodoPg_t nodoPg)
{
    stat_t tmp;
    int stats[6];
    stampa_pg_codice(nodoPg);
    stampa_pg_nome(nodoPg);
    stampa_pg_classe(nodoPg);
    if(nodoPg->equip->inUso==-1)
        stampa_pg_stats(nodoPg);
    else{
        tmp = restituisci_stats_oggetto(inventario, nodoPg->equip->inUso);
        stats[0] = nodoPg->stats.hp + tmp.hp;
        stats[1] = nodoPg->stats.mp + tmp.mp;
        stats[2] = nodoPg->stats.atk + tmp.atk;
        stats[3] = nodoPg->stats.def + tmp.def;
        stats[4] = nodoPg->stats.mag + tmp.mag;
        stats[5]= nodoPg->stats.spr + tmp.spr;
        for(int i = 0; i< 6; i++){
            if(stats[i]<0)
                stats[i] = 0;
        }
        printf("\nHP: %d", stats[0]); printf("\nMP: %d", stats[1]); printf("\nATK: %d", stats[2]); printf("\nDEF: %d", stats[3]); printf("\nMAG: %d", stats[4]); printf("\nSPR: %d", stats[5]);
    }
}
void stampa_pg_nome(nodoPg_t nodoPg){
    printf("\nNome: %s", nodoPg->nome);
}
void stampa_pg_codice(nodoPg_t nodoPg){
    printf("\nCodice: %s", nodoPg->codice);
}
void stampa_pg_classe(nodoPg_t nodoPg){
    printf("\nClasse: %s", nodoPg->classe);
}
void stampa_pg_stats(nodoPg_t nodoPg){
    printf("\nHP: %d", nodoPg->stats.hp);
    printf("\nMP: %d", nodoPg->stats.mp);
    printf("\nATK: %d", nodoPg->stats.atk);
    printf("\nDEF: %d", nodoPg->stats.def);
    printf("\nMAG: %d", nodoPg->stats.mag);
    printf("\nSPR: %d", nodoPg->stats.spr);
}


void stampa_equip(ptabInv inventario, nodoPg_t nodoPg)
{
    int i;
    if(nodoPg != NULL) {
        if (nodoPg->equip->inUso == -1)
            printf("\nNessun equipaggiamento attualmente in uso.");
        else {
            printf("\nOggetto attualmente in uso:");
            stampa_oggetto(inventario, nodoPg->equip->inUso);
        }
        if (nodoPg->equip->usati <= 0)
            printf("\nNessun oggetto disponibile nell'equipaggiamento del personaggio selezionato.");
        else {
            printf("\nOggetti disponibili nell'equipaggiamento:");
            for (i = 0; i < max_oggetti; i++)
                if (nodoPg->equip->vettEq[i] != -1)
                    stampa_oggetto(inventario, nodoPg->equip->vettEq[i]);
        }
    }
}
void aggiungi_equip(nodoPg_t nodoPg, ptabInv inventario, char nome_equip[max_strlen])
{
    int index, aggiungibile = 1;

    if(nodoPg->equip->usati < max_oggetti){ // altrimenti significa che è pieno
        index = trova_oggetto(inventario, nome_equip);
        for(int i = 0; i < max_oggetti; i++)
            if(nodoPg->equip->vettEq[i] == index)
                aggiungibile = 0;
        if(aggiungibile)
            for(int i=0; i< max_oggetti; i++)
                if(nodoPg->equip->vettEq[i] == -1)
                {
                    nodoPg->equip->vettEq[i] = index;
                    nodoPg->equip->usati = nodoPg->equip->usati+1;
                    printf("\nOggetto aggiunto correttamente all'equipaggiamento del personaggio scelto.");
                    break;
                }
    }
    else
        printf("\nInventario pieno.");

}
void scegli_equip_in_uso(nodoPg_t nodoPg, ptabInv inventario, char nome_equip[max_code_lenght]){
    int index, trovato = 0;
    index = trova_oggetto(inventario, nome_equip);
    for(int i = 0; i < max_oggetti; i++)
    {
        if(nodoPg->equip->vettEq[i] == index) // allora significa che avevo già nell'equipaggiamento disponibile per il personaggio l'oggetto e posso metterlo in uso.
        {
            nodoPg->equip->inUso = index;
            trovato = 1;
            printf("\nOggetto correttamente equipaggiato.");
        }
    }
    if(!trovato)
        printf("\nPrima di poter utilizzare un oggetto devi inserirlo nell'equipaggiamento!");
}
void rimuovi_equip(nodoPg_t nodoPg, ptabInv inventario, char nome_equip[max_code_lenght]) //TODO
{
    int index, trovato = 0;
    index = trova_oggetto(inventario, nome_equip);
    for(int i = 0; i < max_oggetti; i++)
    {
        if(nodoPg->equip->vettEq[i] == index) // allora significa che avevo già nell'equipaggiamento disponibile per il personaggio l'oggetto e posso metterlo in uso.
        {
            nodoPg->equip->vettEq[i] = -1;
            nodoPg->equip->usati = nodoPg->equip->usati -1;
            trovato = 1;
            printf("\nL'oggetto e' stato correttamente rimosso.");
        }
    }
    if(!trovato)
        printf("\nPrima di poter utilizzare un oggetto devi inserirlo nell'equipaggiamento!");
}


void freeALL(ptabPg lista_pg)
{
    int i = 0, n_pg;
    nodoPg_t tmp = NULL;
    n_pg = lista_pg->nPg;
    while(i < n_pg || lista_pg->headPg != NULL)
    {
        tmp =lista_pg->headPg;
        lista_pg->headPg = lista_pg->headPg->next;
        free(tmp->equip);
        free(tmp);
        i++;
    }
}
