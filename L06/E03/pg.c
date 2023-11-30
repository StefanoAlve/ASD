#include "pg.h"

struct tabEquip_t{
    int inUso;
    int vettEq[MAXOBJ];
    int usati;
};

struct tabPg_t{
    pnodoPg_t headPg;
    pnodoPg_t tailPg;
    int nPg;
};

ptabPg leggiPersonaggi(char *nomeFile){
    //Inizializzazione variabili
    FILE *fin;
    ptabPg listaPg = (ptabPg)malloc(sizeof(*listaPg));
    struct pg_t tmpPg;
    //Apertura file
    fin = fopen(nomeFile, "r");
    if(fin == NULL){
        printf("Errore nell'apertura del file inventario!\n");
        exit(1);
    }
    while(fscanf(fin, "%s %s %s %d %d %d %d %d %d", tmpPg.codice, tmpPg.nome, tmpPg.classe, &tmpPg.stat.hp, &tmpPg.stat.mp, &tmpPg.stat.atk, &tmpPg.stat.def, &tmpPg.stat.mag, &tmpPg.stat.spr) == 9){
        listaPg = inserisciPg(listaPg, tmpPg);
        listaPg->nPg++;
    }
    //Chiusura file
    fclose(fin);
    return listaPg;
}
pnodoPg_t newNode(pnodoPg_t next, struct pg_t personaggio){
    pnodoPg_t nodoPg = (pnodoPg_t)malloc(sizeof(struct pg_t));
    strcpy(nodoPg->codice, personaggio.codice);
    strcpy(nodoPg->nome, personaggio.nome);
    strcpy(nodoPg->classe, personaggio.classe);
    nodoPg->stat = personaggio.stat;
    nodoPg->next = next;
    for(int i=0; i<MAXOBJ; i++){
        nodoPg->equip->vettEq[i] = -1;
    }
    nodoPg->equip->inUso = -1;
    nodoPg->equip->usati = 0;
    return nodoPg;
}
ptabPg inserisciPg(ptabPg tabPg, struct pg_t personaggio){
    if(tabPg->headPg == NULL){
        tabPg->headPg = newNode(tabPg->tailPg, personaggio);
        tabPg->tailPg = tabPg->headPg;
    }
    else{
        tabPg->tailPg->next = newNode(NULL, personaggio);
        tabPg->tailPg = tabPg->tailPg->next;
    }
    return tabPg;
}
pnodoPg_t ricercaCodice(ptabPg tabPg, char codice[]){
    pnodoPg_t attuale;
    int i;
    for(attuale = tabPg->headPg; attuale != NULL; attuale = attuale->next){
        if(strcasecmp(attuale->codice, codice) == 0){
            return attuale;
        }
    }
    return NULL;
}
ptabPg cancellaPg(ptabPg tabPg, pnodoPg_t personaggio){
    pnodoPg_t attuale, precedente;
    int trovato = 0;
    if(personaggio != NULL){
        if(strcasecmp(personaggio->codice, tabPg->headPg->codice) == 0){
            attuale = tabPg->headPg;
            tabPg->headPg = tabPg->headPg->next;
            trovato = 1;
            free(attuale);
        }
        else{
            for(attuale = tabPg->headPg->next, precedente = tabPg->headPg; attuale != NULL && !trovato; precedente = attuale, attuale = attuale->next){
                if(strcasecmp(attuale->codice, personaggio->codice) == 0){
                    precedente->next = attuale->next;
                    trovato = 1;
                    free(attuale);
                }
            }
        }
        if(trovato){
            printf("\nPersonaggio %s eliminato con successo!\n", personaggio->codice);
        }
        else{
            printf("\nIl personaggio %s non è stato trovato nella lista dei personaggi!\n", personaggio->codice);
        }
    }
    else{
        printf("Il personaggio inserito non è esistente!\n");
    }
    return tabPg;
}
void stampaPg(pnodoPg_t personaggio, ptabInv inventario){
    stampaPgCode(personaggio);
    stampaPgNome(personaggio);
    stampaPgClasse(personaggio);
    stampaPgEquip(personaggio, inventario);
    stampaPgStat(personaggio);
}
void stampaPgCode(pnodoPg_t personaggio){
    printf("Il codice del personaggio e': %s\n", personaggio->codice);
}
void stampaPgNome(pnodoPg_t personaggio){
    printf("Il nome del personaggio e': %s\n", personaggio->nome);
}
void stampaPgClasse(pnodoPg_t personaggio){
    printf("Il classe del personaggio e': %s\n", personaggio->classe);
}
void stampaPgEquip(pnodoPg_t personaggio, ptabInv inventario){
    for(int i=0; i<MAXOBJ; i++){
        if(personaggio->equip->vettEq[i] != -1){
            stampaObj(inventario, personaggio->equip->vettEq[i]);
        }
    }
}
void stampaPgStat(pnodoPg_t personaggio){
    printf("Le statistiche del personaggio sono:\n");
    printf("hp:%d\n",personaggio->stat.hp);
    printf("mp:%d\n",personaggio->stat.mp);
    printf("atk:%d\n",personaggio->stat.atk);
    printf("def:%d\n",personaggio->stat.def);
    printf("mag:%d\n",personaggio->stat.mag);
    printf("spr:%d\n",personaggio->stat.spr);
}

void aggiungiObj(pnodoPg_t personaggio, ptabInv inventario, char obj[]){
    int index,i;
    if(personaggio->equip->usati != MAXOBJ) {
        index = ricercaObjN(inventario, obj);
        for(i=0;i<MAXOBJ && i!= index; i++);
        if(i!=MAXOBJ-1){
            printf("L'oggetto è gia' presente nell'inventario!\n");
            return;
        }
        for(i=0;i<MAXOBJ;i++){
            if(personaggio->equip->vettEq[i] == -1){
                personaggio->equip->vettEq[i] = index;
                personaggio->equip->vettEq[i]++;
            }
        }
        printf("Oggetto inserito nell'equipaggiamento!\n");
    }
    else{
        printf("Il personaggio ha già raggiunto la capienza massima per l'equipaggiamento\n");
        printf("Cancella uno o più oggetti per inserirne altri\n");
    }
}
void rimuoviObj(pnodoPg_t personaggio, ptabInv inventario, char obj[]){
    int index,i;
    if(personaggio->equip->usati != 0){
        index = ricercaObjN(inventario, obj);
        for(i=0;i<MAXOBJ;i++){
            if(personaggio->equip->vettEq[i] == index){
                personaggio->equip->vettEq[i] = -1;
                personaggio->equip->vettEq[i]--;
            }
        }
        printf("Oggetto rimosso dall'equipaggiamento!\n");
    }
    else{
        printf("Il personaggio non ha oggetti equipaggiati\n");
    }
}
void scegliInUso(pnodoPg_t personaggio, ptabInv inventario, char obj[]){
    int index, i;
    if(personaggio->equip->usati != 0){
        index = ricercaObjN(inventario, obj);
        for(i=0;i<MAXOBJ && i!=index; i++);
        if(i!=MAXOBJ-1){
            personaggio->equip->inUso = index;
            printf("L'oggetto è ora in uso!\n");
        }
        else{
            printf("L'oggetto richiesto non è presente nell'equipaggiamento!\n");
        }
    }
}

void distruggiListaPersonaggi(ptabPg listaPers){
    pnodoPg_t corrente = listaPers->headPg, successivo;
    struct pg_t personaggio;
    while(corrente!=NULL){
        successivo = corrente->next;
        free(personaggio.codice);
        free(personaggio.nome);
        free(personaggio.classe);
        free(personaggio.equip);
        free(corrente);
        corrente = successivo;
    }
}