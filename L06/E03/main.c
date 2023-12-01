#include "pg.h"
typedef enum{r_stampaObj, r_stampaObjS, r_stampaObjT, r_stampaInv, r_erroreInv}comandiInv_e;
typedef enum{r_inserisciPg, r_cancellaPg, r_stampaPg, r_stampaPgN, r_stampaPgCl, r_stampaPgS, r_stampaPgEq, r_stampaObjInUso, r_aggiungiObj, r_rimuoviObj, r_scegliInUso, r_stampaListaPg, r_errorePg}comandiPg_e;


int menuComandi(ptabInv inventario, ptabPg listaPersonaggi);
comandiInv_e leggiComandoInv();
void eseguiCmdInv(ptabInv inventario, comandiInv_e comandoInvE);
comandiPg_e leggiComandoPg();
void eseguiCmdPg(ptabPg listaPersonaggi, comandiPg_e comandoPgE, ptabInv inventario);

int main() {
    //Inizializzazione variabili
    ptabInv inventario;
    ptabPg listaPersonaggi;
    int fine;
    char nomeFile[MAXC];
    //Corpo programma
    printf("\n------------------\n");
    printf("  GIOCO DI RUOLO\n");
    printf("------------------\n\n");
    printf("Da quale file vuoi che estragga l'inventario:");
    scanf("%s", nomeFile);
    inventario = leggiInventario(nomeFile);
    printf("Da quale file vuoi che estragga i personaggi:");
    scanf("%s", nomeFile);
    listaPersonaggi = leggiPersonaggi(nomeFile);
    stampaInv(inventario);
    stampaListaPg(listaPersonaggi, inventario);
    do{
       fine  = menuComandi(inventario, listaPersonaggi);
    }while(!fine);
    distruggiInventario(inventario);
    distruggiListaPersonaggi(listaPersonaggi);
    return 0;
}

int menuComandi(ptabInv inventario, ptabPg listaPersonaggi){
    char comando[MAXC];
    comandiInv_e comandoInvE;
    comandiPg_e comandoPgE;
    int fine = 0;
    printf("\nVuoi accedere all'<inventario> o ai <personaggi> (<fine> per terminare)?:");
    scanf("%s", comando);
    if(strcasecmp("inventario", comando) == 0){
        comandoInvE = leggiComandoInv();
        eseguiCmdInv(inventario, comandoInvE);
    }
    else if(strcasecmp("personaggi", comando)==0){
        comandoPgE = leggiComandoPg();
        eseguiCmdPg(listaPersonaggi, comandoPgE, inventario);
    }
    else if(strcasecmp("fine", comando) == 0) {
        fine = 1;
    }
    else{
        printf("Comando inesistente!\n");
    }
    return fine;
}

comandiInv_e leggiComandoInv(){
    char comando[MAXC];
    comandiInv_e comandoInvE;
    printf("\n-------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\tLISTA COMANDI INVENTARIO\n");
    printf("-------------------------------------------------------------------------------------------------------\n\n");
    printf("stampaObjTot -> stampa l'oggetto per intero\n");
    printf("stampaObjStats -> stampa le statistiche relative all'oggetto\n");
    printf("stampaObjTipo -> stampa il tipo dell'oggetto\n");
    printf("stampaInv -> stampa l'intero inventario\n");
    printf("-------------------------------------------------------------------------------------------------------\n\n");
    printf("Inserisci comando:");
    scanf(" %s", comando);
    if(strcasecmp("stampaObjTot", comando) == 0){
        comandoInvE = 0;
    }
    else if(strcasecmp("stampaObjStats", comando) == 0){
        comandoInvE = 1;
    }
    else if(strcasecmp("stampaObjTipo", comando) == 0){
        comandoInvE = 2;
    }
    else if(strcasecmp("stampaInv", comando) == 0){
        comandoInvE = 3;
    }
    else{
        comandoInvE = 4;
    }
    return comandoInvE;
}
void eseguiCmdInv(ptabInv inventario, comandiInv_e comandoInvE){
    char obj[MAXC];
    int index;
    switch(comandoInvE){
        case r_stampaObj:
            printf("Inserisci il nome dell'oggetto:");
            scanf("%s", obj);
            index = ricercaObjN(inventario, obj);
            if(index != -1){
                stampaObj(inventario, index);
            }
            else{
                printf("Oggetto non presente nell'inventario!\n");
            }
            break;
        case r_stampaObjS:
            printf("Inserisci il nome dell'oggetto:");
            scanf("%s", obj);
            index = ricercaObjN(inventario, obj);
            if(index != -1){
                stampaObjStats(inventario, index);
            }
            else{
                printf("Oggetto non presente nell'inventario!\n");
            }
            break;
        case r_stampaObjT:
            printf("Inserisci il nome dell'oggetto:");
            scanf("%s", obj);
            index = ricercaObjN(inventario, obj);
            if(index != -1){
                stampaObjTipo(inventario, index);
            }
            else{
                printf("Oggetto non presente nell'inventario!\n");
            }
            break;
        case r_stampaInv:
            stampaInv(inventario);
            break;
        case r_erroreInv:
            printf("Comando inesistente!\n");
            break;
    }
}
comandiPg_e leggiComandoPg(){
    char comando[MAXC];
    comandiPg_e comandoPgE;
    //TODO formattazione testi
    printf("\n-------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\tLISTA COMANDI PERSONAGGI\n");
    printf("-------------------------------------------------------------------------------------------------------\n\n");
    printf("inserisciPg -> inserisci un personaggio nella lista\n");
    printf("cancellaPg -> rimuovi un personaggio dalla lista\n");
    printf("stampaPgTot -> stampa il personaggio per intero\n");
    printf("stampaPgNome -> stampa il nome del personaggio\n");
    printf("stampaPgClasse -> stampa la classe del personaggio\n");
    printf("stampaPgStats -> stampa le statistiche del personaggio\n");
    printf("stampaPgEquip -> stampa l'equipaggiamento del personaggio\n");
    printf("stampaObjInUso -> stampa l'oggetto utilizzato dal personaggio\n");
    printf("aggiungiObj -> inserimento di un oggetto nell'equipaggiamento\n");
    printf("rimuoviObj -> rimozione di un oggetto dall'equipaggiamento\n");
    printf("scegliInUso -> scelta dell'oggetto equipaggiato da utilizzare\n");
    printf("stampaListaPg -> stampa la lista dei personaggi\n");
    printf("-------------------------------------------------------------------------------------------------------\n\n");
    printf("Inserisci comando:");
    scanf(" %s", comando);
    if(strcasecmp("inserisciPg", comando)==0){
        comandoPgE = 0;
    }
    else if(strcasecmp("cancellaPg", comando) == 0){
        comandoPgE = 1;
    }
    else if(strcasecmp("stampaPgTot", comando) == 0){
        comandoPgE = 2;
    }
    else if(strcasecmp("stampaPgNome", comando) == 0){
        comandoPgE = 3;
    }
    else if(strcasecmp("stampaPgClasse", comando) == 0){
        comandoPgE = 4;
    }
    else if(strcasecmp("stampaPgStats", comando) == 0){
        comandoPgE = 5;
    }
    else if(strcasecmp("stampaPgEquip", comando) == 0){
        comandoPgE = 6;
    }
    else if(strcasecmp("stampaObjInUso", comando) == 0){
        comandoPgE = 7;
    }
    else if(strcasecmp("aggiungiObj", comando) == 0){
        comandoPgE = 8;
    }
    else if(strcasecmp("rimuoviObj", comando) == 0){
        comandoPgE = 9;
    }
    else if(strcasecmp("scegliInUso", comando) == 0){
        comandoPgE = 10;
    }
    else if(strcasecmp("stampaListaPg", comando) == 0){
        comandoPgE = 11;
    }
    else{
        comandoPgE = 12;
    }
    return comandoPgE;
}
void eseguiCmdPg(ptabPg listaPersonaggi, comandiPg_e comandoPgE, ptabInv inventario){
    char codice[MAXCODE], obj[MAXC];
    pnodoPg_t personaggio;
    switch (comandoPgE){
        case r_inserisciPg:
            listaPersonaggi = inserisciPg(listaPersonaggi, creaPersonaggio());
            break;
        case r_cancellaPg:
            printf("Inserisci il codice del personaggio che vuoi eliminare:");
            scanf("%s", codice);
            personaggio = ricercaCodice(listaPersonaggi, codice);
            if(personaggio == NULL){
                printf("Personaggio inesistente!\n");
                return;
            }
            listaPersonaggi = cancellaPg(listaPersonaggi, personaggio);
            break;
        case r_stampaPg:
            printf("Inserisci il codice del personaggio che vuoi stampare:");
            scanf("%s", codice);
            personaggio = ricercaCodice(listaPersonaggi, codice);
            if(personaggio == NULL){
                printf("Personaggio inesistente!\n");
                return;
            }
            stampaPg(personaggio, inventario);
            break;
        case r_stampaPgN:
            printf("Inserisci il codice del personaggio di cui vuoi stampare il nome:");
            scanf("%s", codice);
            personaggio = ricercaCodice(listaPersonaggi, codice);
            if(personaggio == NULL){
                printf("Personaggio inesistente!\n");
                return;
            }
            stampaPgNome(personaggio);
            break;
        case r_stampaPgCl:
            printf("Inserisci il codice del personaggio di cui vuoi stampare la classe:");
            scanf("%s", codice);
            personaggio = ricercaCodice(listaPersonaggi, codice);
            if(personaggio == NULL){
                printf("Personaggio inesistente!\n");
                return;
            }
            stampaPgClasse(personaggio);
            break;
        case r_stampaPgS:
            printf("Inserisci il codice del personaggio di cui vuoi stampare le statistiche:");
            scanf("%s", codice);
            personaggio = ricercaCodice(listaPersonaggi, codice);
            if(personaggio == NULL){
                printf("Personaggio inesistente!\n");
                return;
            }
            stampaPgStat(personaggio, inventario);
            break;
        case r_stampaPgEq:
            printf("Inserisci il codice del personaggio di cui vuoi stampare l'equipaggiamento:");
            scanf("%s", codice);
            personaggio = ricercaCodice(listaPersonaggi, codice);
            if(personaggio == NULL){
                printf("Personaggio inesistente!\n");
                return;
            }
            stampaPgEquip(personaggio, inventario);
            break;
        case r_stampaObjInUso:
            printf("Inserisci il codice del personaggio di cui vuoi stampare l'equipaggiamento:");
            scanf("%s", codice);
            personaggio = ricercaCodice(listaPersonaggi, codice);
            if(personaggio == NULL){
                printf("Personaggio inesistente!\n");
                return;
            }
            stampaInUso(personaggio, inventario);
            break;
        case r_aggiungiObj:
            printf("Inserisci il codice del personaggio a cui vuoi aggiungere l'oggetto:");
            scanf("%s",codice);
            personaggio = ricercaCodice(listaPersonaggi,codice);
            if(personaggio == NULL){
                printf("Personaggio inesistente!\n");
                return;
            }
            printf("Inserisci il nome dell'oggetto che vuoi aggiungere all'equipaggiamento:");
            scanf("%s", obj);
            aggiungiObj(personaggio, inventario, obj);
            break;
        case r_rimuoviObj:
            printf("Inserisci il codice del personaggio a cui vuoi togliere l'oggetto:");
            scanf("%s",codice);
            personaggio = ricercaCodice(listaPersonaggi,codice);
            if(personaggio == NULL){
                printf("Personaggio inesistente!\n");
                return;
            }
            printf("Inserisci il nome dell'oggetto che vuoi rimuovere all'equipaggiamento:");
            scanf("%s", obj);
            rimuoviObj(personaggio, inventario, obj);
            break;
        case r_scegliInUso:
            printf("Inserisci il codice del personaggio a cui vuoi cambiare l'oggetto in uso:");
            scanf("%s",codice);
            personaggio = ricercaCodice(listaPersonaggi,codice);
            if(personaggio == NULL){
                printf("Personaggio inesistente!\n");
                return;
            }
            printf("\nQual e' il nome dell'oggetto che il personaggio deve utilizzare:");
            scanf("%s", obj);
            scegliInUso(personaggio, inventario, obj);
            break;
        case r_stampaListaPg:
            stampaListaPg(listaPersonaggi, inventario);
            break;
        case r_errorePg:
            printf("Comando inesistente!\n");
            break;
    }
}