#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXL 30
//Variabili globali
typedef enum{r_date, r_partenza, r_capolinea, r_ritardo,
    r_ritardo_tot, r_ordina_data, r_ordina_codice, r_ordina_partenza, r_ordina_arrivo, r_ricerca_partenza_dico, r_nuovo_file, r_stampa, r_fine, r_errore}comando_e;
typedef struct{ //Struct contenente i dati relativi a ogni tratta
    char *codice_tratta;
    char *partenza;
    char *destinazione;
    char *data;
    char *ora_partenza;
    char *ora_arrivo;
    int ritardo;
}sTratta;

typedef struct{ //Struct contenente puntatori ai vettori di tratte ordinate per effettuare gli ordinamenti una singola volta e mantenerli in memoria
    sTratta **ordinateData;
    sTratta **ordinateCodice;
    sTratta **ordinatePartenza;
    sTratta **ordinateArrivo;
}spOrdinamenti;

//Funzioni
comando_e leggiComando(void);
int leggiFile(sTratta **tratte);
void inizializzaSPOrdinamenti(spOrdinamenti *pSPOrdinamenti, int nr, sTratta tratte[]);
void selezionaDati(int *pnr, comando_e comando, sTratta tratte[], spOrdinamenti *pSOrdinamenti, int *pfine);
void elencaCorseDate(sTratta tratte[], char datai[], char dataf[], int nr);
void elencaCorsePartenza(sTratta tratte[], char partenza[], int nr);
void elencaCorseCapolinea(sTratta tratte[], char capolinea[], int nr);
void elencaCorseRitardo(sTratta tratte[], char datai[], char dataf[], int nr);
void elencaRitardoCompl(sTratta tratte[], char codiceTratta[], int nr);
void ordinaPerData(sTratta *pTratte[], int nr);
void ordinaPerCodice(sTratta *pTratte[], int nr);
void ordinaPerPartenza(sTratta *pTratte[], int nr);
void ordinaPerArrivo(sTratta *pTratte[], int nr);
void stampaTratta(sTratta *pTratte[], int nr);
void ricercaPerPartenzaDico(sTratta *pTratte[], int nr, char partenza[]);
void deallocaOrdinamenti(spOrdinamenti *pSPOrdinamenti);
void deallocaTratte(sTratta *tratte, int nTratte);
void stampaCont(sTratta *tratte, int nr);

int main(void) {
    //Inizializzazione variabili
    comando_e comando;
    int nr, fine = 0;
    sTratta *tratte;
    spOrdinamenti ordinamenti;
    //Apertura file
    nr = leggiFile(&tratte);
    inizializzaSPOrdinamenti(&ordinamenti, nr, tratte);
    while(!fine && nr != -1) {
        //Lettura Comando
        comando = leggiComando();
        //Corpo programma
        selezionaDati(&nr, comando, tratte, &ordinamenti, &fine);
    }
    //Deallocazione
    deallocaOrdinamenti(&ordinamenti);
    deallocaTratte(tratte, nr);
    return 0;
}

comando_e leggiComando(void){
    //Inizializzazione variabili
    char comando[MAXL];
    comando_e comandoE;
    //Corpo funzione
    printf("\n-------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\tLISTA COMANDI\n");
    printf("-------------------------------------------------------------------------------------------------------\n\n");
    printf("date -> elenca corse partite tra due date\n");
    printf("partenza -> elenca corse partite dalla fermata inserita\n");
    printf("capolinea -> elenca corse che hanno il capolinea inserito\n");
    printf("ritardo -> elenca le corse che hanno effettuato un ritardo nel periodo inserito\n");
    printf("ritardo_tot -> indica il ritardo complessivo effettuato dalle corse con il codice di tratta inserito\n");
    printf("ordina_data -> ordina le corse per data, in caso di data uguale verranno ordinate per ora\n");
    printf("ordina_codice -> ordina le corse per codice\n");
    printf("ordina_partenza -> ordina le corse secondo il nome della partenza\n");
    printf("ordina_arrivo -> ordina le corse secondo il nome della destinazione\n");
    printf("ricerca_partenza_dico -> esegue la ricerca dicotomica della partenza inserita\n");
    printf("nuovo_file -> permette all'utente di aprire un nuovo file\n");
    printf("stampa -> stampa il contenuto del file\n");
    printf("fine -> termina il programma\n\n");
    printf("-------------------------------------------------------------------------------------------------------\n\n");
    printf("Inserisci comando:");
    scanf(" %s", comando);
    if(strcmp("date", comando) == 0){
        comandoE = 0;
    }
    else if(strcmp("partenza", comando) == 0){
        comandoE = 1;
    }
    else if(strcmp("capolinea", comando) == 0){
        comandoE = 2;
    }
    else if(strcmp("ritardo", comando) == 0){
        comandoE = 3;
    }
    else if(strcmp("ritardo_tot", comando) == 0){
        comandoE = 4;
    }
    else if(strcmp("ordina_data", comando) == 0){
        comandoE = 5;
    }
    else if(strcmp("ordina_codice", comando) == 0){
        comandoE = 6;
    }
    else if(strcmp("ordina_partenza",comando) == 0){
        comandoE = 7;
    }
    else if(strcmp("ordina_arrivo",comando) == 0){
        comandoE = 8;
    }
    else if(strcmp("ricerca_partenza_dico",comando) == 0){
        comandoE = 9;
    }
    else if(strcmp("nuovo_file", comando) == 0){
        comandoE = 10;
    }
    else if(strcmp("stampa", comando) == 0){
        comandoE = 11;
    }
    else if(strcmp("fine", comando) == 0){
        comandoE = 12;
    }
    else{
        printf("\nComando non riconosciuto! Riprova\n");
        comandoE = 13;
    }
    return comandoE;
}

int leggiFile(sTratta **ptratte){
    //Inizializzazione variabili
    FILE* fp;
    int i, nr = -1;
    char nomeFile[MAXL], tmp[MAXL];
    sTratta *tratte; //Utilizzo variabile ausiliaria per rendere più leggibili le allocazioni dinamiche
    //Apertura file
    printf("Inserisci il nome del file:");
    scanf("%s", nomeFile);
    fp = fopen(nomeFile, "r");
    if(fp != NULL){

        fscanf(fp,"%d", &nr);
        tratte = (sTratta*)malloc(nr*sizeof(sTratta));
        if(tratte == NULL){
            printf("Errore nell'assegnazione della memoria\n");
            exit(1);
        }
        //Corpo programma
        for(i=0; i<nr; i++){
            //Alloco le stringhe dinamicamente utilizzando strdup, la funzione riconosce il \0 nel vettore di char statico tmp, alloca il giusto spazio di memoria per contenere la stringa, copia la stringa in quello spazio e ne restituisce il puntatore
            fscanf(fp, "%s", tmp);
            tratte[i].codice_tratta = strdup(tmp);
            fscanf(fp, "%s", tmp);
            tratte[i].partenza = strdup(tmp);
            fscanf(fp, "%s", tmp);
            tratte[i].destinazione = strdup(tmp);
            fscanf(fp, "%s", tmp);
            tratte[i].data = strdup(tmp);
            fscanf(fp, "%s", tmp);
            tratte[i].ora_partenza = strdup(tmp);
            fscanf(fp, "%s", tmp);
            tratte[i].ora_arrivo = strdup(tmp);
            fscanf(fp,"%d", &tratte[i].ritardo);
        }
        stampaCont(tratte,nr);
        *ptratte = tratte;
    }
    else{
        printf("Errore nell'apertura del file!\n");
        exit(1);
    }
    //Chiusura file
    fclose(fp);
    return nr;
}

void inizializzaSPOrdinamenti(spOrdinamenti *pSPOrdinamenti, int nr, sTratta tratte[]) {
    // Alloca memoria per gli array all'interno di pSPOrdinamenti
    pSPOrdinamenti->ordinateData = (sTratta**)malloc(nr * sizeof(sTratta*));
    pSPOrdinamenti->ordinateArrivo = (sTratta**)malloc(nr * sizeof(sTratta*));
    pSPOrdinamenti->ordinateCodice = (sTratta**)malloc(nr * sizeof(sTratta*));
    pSPOrdinamenti->ordinatePartenza = (sTratta**)malloc(nr * sizeof(sTratta*));
    //Se tutte le malloc sono diverse da null
    if (pSPOrdinamenti->ordinateData && pSPOrdinamenti->ordinateArrivo && pSPOrdinamenti->ordinateCodice && pSPOrdinamenti->ordinatePartenza) {
        for (int i = 0; i < nr; i++) {
            pSPOrdinamenti->ordinateData[i] = &tratte[i];
            pSPOrdinamenti->ordinateArrivo[i] = &tratte[i];
            pSPOrdinamenti->ordinateCodice[i] = &tratte[i];
            pSPOrdinamenti->ordinatePartenza[i] = &tratte[i];
        }
        //Inizializzo tutti gli ordinamenti
        ordinaPerData(pSPOrdinamenti->ordinateData, nr);
        ordinaPerPartenza(pSPOrdinamenti->ordinatePartenza, nr);
        ordinaPerArrivo(pSPOrdinamenti->ordinateArrivo, nr);
        ordinaPerCodice(pSPOrdinamenti->ordinateCodice, nr);
    } else {
        // Gestione dell'errore di allocazione di memoria
        printf("Errore nell'allocazione della memoria\n");
        exit(1);
    }
}


void selezionaDati(int *pnr, comando_e comando, sTratta tratte[], spOrdinamenti *pSOrdinamenti, int *pfine){
    //Inizializzazione variabili
    char partenza[MAXL], capolinea[MAXL], codiceTratta[MAXL], datai[MAXL], dataf[MAXL],partenza1[MAXL];
    int nr = *pnr;
    sTratta *pTratte[nr];
    for(int i = 0; i < nr; i++){
        pTratte[i] = &tratte[i];
    }
    switch(comando){
        case r_date:
            printf("\nInserisci la data da cui iniziare la ricerca nel formato aaaa/mm/gg: ");
            scanf("%s", datai);
            printf("\nInserisci la data in cui terminare la ricerca nel formato aaaa/mm/gg: ");
            scanf("%s", dataf);
            elencaCorseDate(tratte, datai, dataf, nr);
            break;
        case r_partenza:
            printf("\nInserire nome fermata di partenza: ");
            scanf("%s",partenza);
            elencaCorsePartenza(tratte, partenza, nr);
            break;
        case r_capolinea:
            printf("\nInserire nome capolinea: ");
            scanf("%s",capolinea);
            elencaCorseCapolinea(tratte, capolinea, nr);
            break;
        case r_ritardo:
            printf("\nInserisci la data da cui iniziare la ricerca nel formato aaaa/mm/gg: ");
            scanf("%s", datai);
            printf("\nInserisci la data in cui terminare la ricerca nel formato aaaa/mm/gg: ");
            scanf("%s", dataf);
            elencaCorseRitardo(tratte, datai, dataf, nr);
            break;
        case r_ritardo_tot:
            printf("\nInserire codice di tratta: ");
            scanf("%s", codiceTratta);
            elencaRitardoCompl(tratte, codiceTratta, nr);
            break;
        case r_ordina_data:
            printf("Le corse ordinate per data risultano:\n");
            stampaTratta(pSOrdinamenti->ordinateData,nr);
            break;
        case r_ordina_codice:
            printf("Le corse ordinate per codice risultano:\n");
            stampaTratta(pSOrdinamenti->ordinateCodice,nr);
            break;
        case r_ordina_partenza:
            printf("Le corse ordinate per partenza risultano:\n");
            stampaTratta(pSOrdinamenti->ordinatePartenza,nr);
            break;
        case r_ordina_arrivo:
            printf("Le corse ordinate per destinazione risultano:\n");
            stampaTratta(pSOrdinamenti->ordinateArrivo,nr);
            break;
        case r_ricerca_partenza_dico:
            printf("Inserisci partenza da ricercare: ");
            scanf("%s", partenza1);
            ricercaPerPartenzaDico(pTratte, nr, partenza1);
            break;
        case r_nuovo_file:
            //Dealloco ordinamenti precedenti e il vettore di struct tratte
            deallocaOrdinamenti(pSOrdinamenti);
            deallocaTratte(tratte, nr);
            //Realloco entrambi con i nuovi dati contenuti nel nuovo file
            nr = leggiFile(&tratte);
            *pnr = nr;
            inizializzaSPOrdinamenti(pSOrdinamenti, nr, tratte);
            break;
        case r_stampa:
            stampaCont(tratte,nr);
            break;
        case r_fine:
            *pfine = 1;
            printf("Programma terminato correttamente!\n");
            break;
        case r_errore:
            break;
    }
}


void elencaRitardoCompl(sTratta tratte[], char codiceTratta[], int nr){
    int ritardo_tot = 0, flag = 0;
    for(int i = 0; i < nr; i++){
        if(strcasecmp(tratte[i].codice_tratta, codiceTratta) == 0){
            ritardo_tot += tratte[i].ritardo;
            flag = 1;
        }
    }
    if(!flag){
        printf("\nNon sono presenti tratte aventi tale codice di tratta.\n");
    }
    else {
        printf("\nIl ritardo complessivo delle corse con codice di tratta %s vale: %d minuti\n", codiceTratta,
               ritardo_tot);
    }
}

void elencaCorseCapolinea(sTratta tratte[], char capolinea[], int nr){
    int flag = 0;
    printf("\nLe tratte che hanno come capolinea %s sono:\n", capolinea);
    for(int i = 0; i < nr; i++){
        if(strncasecmp(tratte[i].destinazione, capolinea, strlen(capolinea)) == 0){
            printf("%s - %s del %s partito alle ore %s\n", tratte[i].partenza, tratte[i].destinazione, tratte[i].data, tratte[i].ora_partenza);
            flag = 1;
        }
    }
    if(!flag){
        printf("\nNon sono presenti tratte aventi tale capolinea.\n");
    }

}

void elencaCorsePartenza(sTratta tratte[], char partenza[], int nr){
    int flag = 0;
    printf("\nLe tratte che sono partite da %s sono:\n", partenza);
    for(int i = 0; i < nr; i++){
        if(strncasecmp(tratte[i].partenza, partenza, strlen(partenza)) == 0){
            printf("%s - %s del %s partito alle ore %s\n", tratte[i].partenza, tratte[i].destinazione, tratte[i].data, tratte[i].ora_partenza);
            flag =1;
        }
    }
    if(!flag){
        printf("\nNon sono presenti tratte aventi tale fermata di partenza.\n");
    }
}

void elencaCorseDate(sTratta tratte[], char datai[], char dataf[], int nr){
    int flag = 0;
    printf("\nLe tratte che sono partite tra il %s e il %s sono:\n",datai,dataf);
    for(int i = 0; i < nr; i++){
        if(strcmp(tratte[i].data,datai) >= 0 && strcmp(tratte[i].data, dataf) <= 0){
            printf("%s - %s del %s partito alle ore %s\n", tratte[i].partenza, tratte[i].destinazione, tratte[i].data, tratte[i].ora_partenza);
            flag =1;
        }
    }
    if(!flag){
        printf("\nNon sono presenti tratte partite nell'intervallo richiesto.\n");
    }
}

void elencaCorseRitardo(sTratta tratte[], char datai[], char dataf[], int nr){
    int flag = 0;
    printf("\nLe tratte che sono partite in ritardo tra il %s e il %s sono:\n",datai,dataf);
    for(int i = 0; i < nr; i++){
        if(strcmp(tratte[i].data,datai) >= 0 && strcmp(tratte[i].data, dataf) <= 0){
            if(tratte[i].ritardo > 0){
                printf("%s - %s del %s partito alle ore %s con un ritardo di %d\n", tratte[i].partenza, tratte[i].destinazione, tratte[i].data, tratte[i].ora_partenza, tratte[i].ritardo);
                flag =1;
            }
        }
    }
    if(!flag){
        printf("\nNon sono presenti tratte arrivate al capolinea in ritardo nell'intervallo richiesto.\n");
    }
}

void ordinaPerData(sTratta *pTratte[], int nr){
    //Insertion sort
    int i, j, swap;
    sTratta *key;
    for(i = 1; i < nr; i++){
        key = pTratte[i];
        j=i-1;
        swap = 1;
        while(j >= 0 && swap){
            if(strcmp(key->data, pTratte[j]->data) < 0){
                pTratte[j + 1] = pTratte[j];
            }
            else if(strcmp(key->data, pTratte[j]->data) == 0 && strcmp(key->ora_partenza, pTratte[j]->ora_partenza) < 0) {
                pTratte[j + 1] = pTratte[j];
            }
            else if(strcmp(key->data, pTratte[j]->data) == 0 && strcmp(key->ora_partenza, pTratte[j]->ora_partenza) == 0 && strcmp(key->ora_arrivo, pTratte[j]->ora_arrivo) < 0) {
                pTratte[j + 1] = pTratte[j];
            }
            else {
                swap = 0;
            }
            if (swap) {
                j--;
            }
        }
        pTratte[j+1] = key;
    }
}

void ordinaPerPartenza(sTratta *pTratte[], int nr){
    //Insertion sort
    int i, j;
    sTratta *key;

    for(i=1; i<nr; i++){
        key = pTratte[i];
        j = i-1;
        while(j >= 0 && strcmp(key -> partenza, pTratte[j] -> partenza) < 0){
            pTratte[j+1] = pTratte[j];
            j--;
        }
        pTratte[j+1] = key;
    }
}

void ordinaPerArrivo(sTratta *pTratte[], int nr){
    //Insertion sort
    int i, j;
    sTratta *key;

    for(i=1; i<nr; i++){
        key = pTratte[i];
        j = i-1;
        while(j >= 0 && strcmp(key -> destinazione, pTratte[j] -> destinazione) < 0){
            pTratte[j+1] = pTratte[j];
            j--;
        }
        pTratte[j+1] = key;
    }
}

void ordinaPerCodice(sTratta *pTratte[], int nr){
    //Insertion sort
    int i, j;
    sTratta *key;

    for(i=1; i<nr; i++){
        key = pTratte[i];
        j = i-1;
        while(j >= 0 && strcmp(key -> codice_tratta, pTratte[j] -> codice_tratta) < 0){
            pTratte[j+1] = pTratte[j];
            j--;
        }
        pTratte[j+1] = key;
    }
}

void ricercaPerPartenzaDico(sTratta *pTratte[], int nr, char partenza[]){
    //Ricerca dicotomica basata sul confronto delle partenze
    ordinaPerPartenza(pTratte,nr);
    int l, r, cont = 0, pm, flag = 0;
    l=0;
    r=nr-1;
    printf("Le corse trovate sono:\n");
    while(l<=r && !cont){
        pm = (l+r)/2;
        if(strncasecmp(partenza, pTratte[pm]->partenza, strlen(partenza)) < 0){ //Se la partenza inserita viene prima della partenza della struct a metà vettore allora analizzo il sotto vettore sinistro
            r = pm -1;
        }
        else if(strncasecmp(partenza, pTratte[pm]->partenza, strlen(partenza)) > 0){ //Se la partenza inserita viene dopo la partenza della struct a metà vettore allora analizzo il sotto vettore destro
            l = pm + 1;
        }
        else if(strncasecmp(partenza, pTratte[pm]->partenza, strlen(partenza)) == 0){ //Se le partenze corrispondono
            printf("%s %s %s %s %s %s %d\n", pTratte[pm] -> codice_tratta, pTratte[pm] -> partenza, pTratte[pm] -> destinazione, pTratte[pm] -> data, pTratte[pm] -> ora_partenza, pTratte[pm] -> ora_arrivo, pTratte[pm] -> ritardo);
            flag = 1;
            //Controllo i vicini dato che mi trovo in un vettore ordinato
            if (pm+1 < nr && strncasecmp(partenza, pTratte[pm+1]->partenza, strlen(partenza)) == 0)
                printf("%s %s %s %s %s %s %d\n", pTratte[pm+1]->codice_tratta, pTratte[pm+1]->partenza, pTratte[pm+1]->destinazione, pTratte[pm+1]->data, pTratte[pm+1]->ora_partenza, pTratte[pm+1]->ora_arrivo, pTratte[pm+1]->ritardo);
            if (pm -1 >= 0 && strncasecmp(partenza, pTratte[pm-1]->partenza, strlen(partenza)) == 0)
                printf("%s %s %s %s %s %s %d\n", pTratte[pm-1]->codice_tratta, pTratte[pm-1]->partenza, pTratte[pm-1]->destinazione, pTratte[pm-1]->data, pTratte[pm-1]->ora_partenza, pTratte[pm-1]->ora_arrivo, pTratte[pm-1]->ritardo);
            cont = 1;
        }
    }
    if(!flag){
        printf("\nNon sono presenti tratte aventi tale fermata di partenza.\n");
    }
}

void stampaTratta(sTratta *pTratte[], int nr){
    for(int i=0; i<nr; i++){
        printf("%s %s %s %s %s %s %d\n", pTratte[i] -> codice_tratta, pTratte[i] -> partenza, pTratte[i] -> destinazione, pTratte[i] -> data, pTratte[i] -> ora_partenza, pTratte[i] -> ora_arrivo, pTratte[i] -> ritardo);
    }
    printf("\n");
}
void stampaCont(sTratta *tratte, int nr){
    printf("Il file contiene: \n");
    for(int i=0;i<nr;i++){
        printf("%s %s %s ", tratte[i].codice_tratta, tratte[i].partenza, tratte[i].destinazione);
        printf("%s ", tratte[i].data);
        printf("%s ", tratte[i].ora_partenza);
        printf("%s ", tratte[i].ora_arrivo);
        printf("%d\n", tratte[i].ritardo);
    }
}
void deallocaOrdinamenti(spOrdinamenti *pSPOrdinamenti){
    if (pSPOrdinamenti != NULL) {
        free(pSPOrdinamenti->ordinateData);
        free(pSPOrdinamenti->ordinateArrivo);
        free(pSPOrdinamenti->ordinateCodice);
        free(pSPOrdinamenti->ordinatePartenza);
    }
}

void deallocaTratte(sTratta *tratte, int nTratte){
    for(int i=0; i<nTratte; i++){
        free(tratte[i].data);
        free(tratte[i].partenza);
        free(tratte[i].ora_partenza);
        free(tratte[i].destinazione);
        free(tratte[i].codice_tratta);
        free(tratte[i].ora_arrivo);
    }
    free(tratte);
}