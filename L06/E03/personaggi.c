#include "personaggi.h"
#include "inventario.c"
struct tabEquip_t{
    int vettEq[MAXOBJ];
};

struct tabPg_t{
    pnodoPg_t headPg;
    int nPg;
};
//LEGGO IL FILE
ptabPg leggiPersonaggi(char *nomeFile) {
    //Inizializzazione variabili
    FILE *fin;
    ptabPg tabPg = (ptabPg)malloc(sizeof(*tabPg));
    struct pg_t personaggio;
    ptabEquip_t tabEquip;
    pnodoPg_t x;
    int i, j;

    tabPg->nPg = 0;
    tabPg->headPg = NULL;

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
    }
    //VETTORE DI STRUCT ALLOCATO CONTENENTE TUTTI I DATI RELATIVI AGLI OGGETTI
    tabEquip = malloc((tabPg->nPg)*sizeof(*tabEquip));
    for (i=0, x = tabPg->headPg ; i<tabPg->nPg; i++, x = x -> next) {
        x->equip = &tabEquip[i];
        for (j=0; j<MAXOBJ; j++) {
            tabEquip[i].vettEq[j] = -1;
        }
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
    //LO CERCA CON DUE PUNTATORI E POI LO ELIMINA DA MODO CHE NON SI ROMPA LA LISTA
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
//FIUNZIONI DI STAMPA SPECIFICA PER IL PERSONAGGIO
void stampaPgCode(pnodoPg_t personaggio){
    printf("%s ", personaggio->codice);
}
void stampaPgNome(pnodoPg_t personaggio){
    printf("%s ", personaggio->nome);
}
void stampaPgClasse(pnodoPg_t personaggio){
    printf("%s ", personaggio->classe);
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
    printf("stat: %d, %d, %d, %d, %d, %d\n\n", personaggio->stat.hp, personaggio->stat.mp, personaggio->stat.atk, personaggio->stat.def, personaggio->stat.mag, personaggio->stat.spr);
}
//stampa personaggio
void stampaPg(pnodoPg_t personaggio, ptabInv tabInv){
    stampaPgCode(personaggio);
    stampaPgNome(personaggio);
    stampaPgClasse(personaggio);
    stampaPgEquip(personaggio, tabInv);
    stampaPgStat(personaggio);
}

//FUNZIONI PER LA MODIFICA DELL'EQUIPAGGIAMENTO
void modificaEquip(pnodoPg_t personaggio, ptabInv tabInv){
    char scelta[MAXC], obj[MAXC];
    int i, bool=1, nObj;
    printf("vuoi 'aggiungere' o 'rimuovere' un oggetto?\n");
    scanf("%s", scelta);
    //CASO DI AGGIUNTA OGGETTO
    if(strcasecmp(scelta, "aggiungere")==0){
        //CONTROLLO CHE NON ABBIA L'INVENTARIO PIENO
        for(i=0; i<MAXOBJ; i++){
            if(personaggio->equip->vettEq[i]==-1){
                bool = 0;
                break;
            }
        }
        if(!bool) {
            //SCELGO E INSERISCO L'OGGETTO
            printf("scegli l'indice dell'oggetto che vuoi aggiungere:\n");
            for (i = 0; i < tabInv->nInv; i++) {
                printf("%d: ", i);
                stampaObj(tabInv, i);
                printf("\n");
            }
            scanf("%d", &nObj);
            strcpy(obj,tabInv->vettInv[nObj].nome);
            aggiungiObj(personaggio->equip, tabInv, obj);
        }
        else
            printf("il personaggio ha gia' %d oggetti equipaggiati\n", MAXOBJ);
    }
    //CASO DI RIMOZIONE OGGETTO MOLTO SIMILE A AGGIUNTA
    else if(strcasecmp(scelta, "rimuovere")==0){
        for(i=0; i<MAXOBJ; i++){
            if(personaggio->equip->vettEq[i]!=-1){
                bool = 0;
                break;
            }
        }
        if(!bool){
            printf("scegli l'indice dell'oggetto che vuoi rimuovere tra i seguenti:\n");
            for (i = 0; i < MAXOBJ && personaggio->equip->vettEq[i]!=-1; i++) {
                printf("numero %d, %s\n", personaggio->equip->vettEq[i], tabInv->vettInv[personaggio->equip->vettEq[i]].nome);
            }
            scanf("%d", &nObj);
            strcpy(obj,tabInv->vettInv[nObj].nome);
            rimuoviObj(personaggio->equip, tabInv, obj);
        }
        else
            printf("il personaggio non ha oggetti equipaggiati");
    }
    else{
        printf("comando errato");
        exit(1);
    }
}
//AGGIUNGO OGGETTO
void aggiungiObj(ptabEquip_t equip, ptabInv tabInv, char obj[]){
    int i, j;
    //CERCO PRIMA UN POSTO LIBERO NELL EQUIP E POI L'INDICE DELL OGGETTO CORISPONDENTE A QUELLO CERCATO
    for(i=0; i<MAXOBJ; i++){
        if(equip->vettEq[i]==-1){

            j = ricercaObjN(tabInv, obj);
            equip->vettEq[i]=j;
            break;


        }
    }
}
//RIMUOVO OGGETTO
void rimuoviObj(ptabEquip_t equip, ptabInv tabInv, char obj[]) {
    int j, index = ricercaObjN(tabInv, obj);

    for(j=0; j<MAXOBJ; j++) {
        if(index == equip->vettEq[j]){
            equip->vettEq[j] = -1;
            break;
        }
    }
}
//CALCOLO DI TUTTE LE STATISTICHE DEL PERSONAGGIO SCELTO
void calcoloStat(pnodoPg_t personaggio, ptabInv tabInv) {
    int i, a=personaggio->stat.hp, b=personaggio->stat.mp, c=personaggio->stat.atk,
            d=personaggio->stat.def, f=personaggio->stat.mag, g=personaggio->stat.spr;

    for (i=0; i<MAXOBJ && personaggio->equip->vettEq[i]!=-1; i++){
        a = a + tabInv->vettInv[personaggio->equip->vettEq[i]].stat.hp;
        b = b + tabInv->vettInv[personaggio->equip->vettEq[i]].stat.mp;
        c = c + tabInv->vettInv[personaggio->equip->vettEq[i]].stat.atk;
        d = d + tabInv->vettInv[personaggio->equip->vettEq[i]].stat.def;
        f = f + tabInv->vettInv[personaggio->equip->vettEq[i]].stat.mag;
        g = g + tabInv->vettInv[personaggio->equip->vettEq[i]].stat.spr;
    }
    if (a<0)
        a=0;
    if (b<0)
        b=0;
    if (c<0)
        c=0;
    if (d<0)
        d=0;
    if (f<0)
        f=0;
    if (g<0)
        g=0;
    printf("le statistiche sono: %d %d %d %d %d %d\n", a, b, c, d, f, g);
}
//DEALLOCAZIONE
void distruggiPersonaggi(ptabPg tabPg){
    pnodoPg_t x, p;
    for (x = tabPg->headPg, p = x->next; p != NULL ; x = p, p = x->next){
        free(x);
    }
    free(x);
    free(tabPg);
}