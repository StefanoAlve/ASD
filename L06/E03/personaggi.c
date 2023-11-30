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
    tabPg->headPg = NULL;
    tabPg->tailPg = NULL;

    //Apertura file
    fin = fopen(nomeFile, "r");
    if(fin == NULL){
        printf("Errore nell'apertura del file personaggi!\n");
        exit(1);
    }
    //continua per tutto il file
    while(!feof(fin)) {
        fscanf(fin, "%s %s %s", personaggio.codice, personaggio.nome, personaggio.classe);
        fscanf(fin, "%d %d %d %d %d %d", &personaggio.stat.hp, &personaggio.stat.mp, &personaggio.stat.atk, &personaggio.stat.def, &personaggio.stat.mag, &personaggio.stat.spr);
        personaggio.next = NULL;
        tabPg->headPg = newNode(tabPg->headPg, personaggio);
        tabPg->nPg += 1;        //aumenta il numero di personaggi
        tabPg->tailPg = &personaggio;
    }

    //Chiusura file
    fclose(fin);
    return tabPg;
}
//funzione che genera un nuovo nodo nella lista di personaggi
pnodoPg_t newNode(pnodoPg_t head, struct pg_t personaggio) {
    pnodoPg_t x, newNode = malloc(sizeof( *newNode));
    //creo newnode per far si che non si creino problemi con la variabile personaggio
    *newNode = personaggio;
    newNode->next = NULL;

    if(head == NULL){
        head = newNode;     //inserimento in testa
    }
    else {
        for (x = head; x->next != NULL; x = x->next) {}
        x->next = newNode;
    }
    return head;
}
//funzione che inserisce un personaggio preso da tastiera
ptabPg inserisciPg(ptabPg tabPg, struct pg_t personaggio) {
    personaggio.next = NULL;
    tabPg->headPg = newNode(tabPg->headPg, personaggio);
    tabPg->nPg += 1;
    return tabPg;
}
//funzione che cancella un personaggio
ptabPg cancellaPg(ptabPg tabPg, pnodoPg_t personaggio) {
    pnodoPg_t x, p;
    for (x = tabPg->headPg, p=NULL; x != NULL ; p=x, x = x->next) {
        if(strcmp(personaggio->codice, x->codice)==0){
            if(x == tabPg->headPg){
                tabPg->headPg = tabPg->headPg->next;
            }
            else {
                p->next = x->next;
            }
            free(x);
            break;
        }
    }

    return tabPg;
}
//funzione che ricerca per codice
pnodoPg_t ricercaCodice(ptabPg tabPg, char nome[]) {
    pnodoPg_t x;
    for (x = tabPg->headPg; x != NULL; x = x->next) {
        if (strcmp(nome, x->codice) == 0) {
            return x;
        }
    }
    return NULL;
}
void stampaPgCode(pnodoPg_t personaggio){
    printf("%s\t", personaggio->codice);
}
void stampaPgNome(pnodoPg_t personaggio){
    printf("%s\t", personaggio->nome);
}
void stampaPgClasse(pnodoPg_t personaggio){
    printf("%s\t", personaggio->classe);
}
void stampaPgEquip(pnodoPg_t personaggio, ptabInv tabInv) {
    int i;
    printf("equipaggiamento: ");
    for(i=0; i<MAXOBJ; i++){
        if(personaggio->equip->vettEq[i] == -1){
            break;
        }
        else{
            stampaObjNome(tabInv, personaggio->equip->vettEq[i]);
        }
    }
}
void stampaPgStat(pnodoPg_t personaggio) {
    printf("%d, %d, %d, %d, %d, %d\n\n", personaggio->stat.hp, personaggio->stat.mp, personaggio->stat.atk, personaggio->stat.def, personaggio->stat.mag, personaggio->stat.spr);
}
//stampa personaggio
void stampaPg(pnodoPg_t personaggio, ptabInv tabInv){

}