#include <stdio.h>
#include <string.h>
#define MAXL 30
#define MAXR 1000
//Variabili globali
typedef enum{r_date, r_partenza, r_capolinea, r_ritardo,
             r_ritardo_tot, r_ordina_data, r_ordina_codice, r_ordina_partenza, r_ordina_arrivo, r_ricerca_partenza_dico, r_stampa, r_fine, r_errore}comando_e;
typedef struct{
    char codice_tratta[MAXL];
    char partenza[MAXL];
    char destinazione[MAXL];
    char data[MAXL];
    char ora_partenza[MAXL];
    char ora_arrivo[MAXL];
    int ritardo;
}sTratta;

//Funzioni
comando_e leggiComando(void);
int leggiFile(char* nomeFile, sTratta tratte[]);
void selezionaDati(int nr, comando_e comando, sTratta tratte[], int *pfine);
void elencaCorseDate(sTratta tratte[], char datai[], char dataf[], int nr);
void elencaCorsePartenza(sTratta tratte[], char partenza[], int nr);
void elencaCorseCapolinea(sTratta tratte[], char capolinea[], int nr);
void elencaCorseRitardo(sTratta tratte[], char datai[], char dataf[], int nr);
void elencaRitardoCompl(sTratta tratte[], char codiceTratta[], int nr);
void ordinaPerData(sTratta *pTratte[], int nr);
void ordinaPerCodice(sTratta *pTratte[], int nr);
void ordinaPerPartenza(sTratta *pTratte[], int nr);
void ordinaPerArrivo(sTratta *pTratte[], int nr);
void stampa(sTratta *pTratte[], int nr);
void ricercaPerPartenzaDico(sTratta *pTratte[], int nr, char partenza[]);
void stampaCont(sTratta tratte[], int nr);

int main(void) {
    //Inizializzazione variabili
    char nomeFile[MAXL];
    comando_e comando;
    int nr, *pfine = NULL, fine = 0;
    sTratta tratte[MAXR];
    pfine = &fine;
    //Apertura file
    printf("Inserisci il nome del file:");
    scanf(" %s", nomeFile);
    nr = leggiFile(nomeFile,tratte);

    while(!fine && nr != -1) {
        //Lettura Comando
        comando = leggiComando();
        //Corpo programma
        if (comando != r_errore) {
            selezionaDati(nr, comando, tratte, pfine);
        }
    }
    //Chiusura file
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
    else if(strcmp("stampa", comando) == 0){
        comandoE = 10;
    }
    else if(strcmp("fine", comando) == 0){
        comandoE = 11;
    }
    else{
        printf("\nComando non riconosciuto! Riprova\n");
        comandoE = 12;
    }
    return comandoE;
}

int leggiFile(char *nomeFile, sTratta tratte[]){
    FILE* fp;
    int i = 0, nr = -1;
    //Apertura file
    fp = fopen(nomeFile, "r");
    if(fp != NULL){
        printf("Il file contiene: \n");
        /// CORPO FUNZIONE
        fscanf(fp,"%d", &nr);
        while(!feof(fp)){
            fscanf(fp, "%s %s %s", tratte[i].codice_tratta, tratte[i].partenza, tratte[i].destinazione);
            fscanf(fp, "%s", tratte[i].data);
            fscanf(fp, "%s", tratte[i].ora_partenza);
            fscanf(fp, "%s", tratte[i].ora_arrivo);
            fscanf(fp,"%d", &tratte[i].ritardo);

            printf("%s %s %s ", tratte[i].codice_tratta, tratte[i].partenza, tratte[i].destinazione);
            printf("%s ", tratte[i].data);
            printf("%s ", tratte[i].ora_partenza);
            printf("%s ", tratte[i].ora_arrivo);
            printf("%d\n", tratte[i].ritardo);
            i++;
        }
    }
    else{
        printf("Errore nell'apertura del file!\n");
    }
    //Chiusura file
    fclose(fp);
    return nr;
}

void selezionaDati(int nr, comando_e comando, sTratta tratte[], int *pfine){
    //Inizializzazione variabili
    char partenza[MAXL], capolinea[MAXL], codiceTratta[MAXL], datai[MAXL], dataf[MAXL],partenza1[MAXL];
    sTratta *pTratte[nr];
    for(int i = 0; i < nr; i++){
        pTratte[i] = &tratte[i];
    }
    switch(comando){ //Grazie all'utilizzo dell'enum posso utilizzare uno switch per i vari comandi
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
            ordinaPerData(pTratte, nr);
            break;
        case r_ordina_codice:
            ordinaPerCodice(pTratte, nr);
            break;
        case r_ordina_partenza:
            ordinaPerPartenza(pTratte, nr);
            break;
        case r_ordina_arrivo:
            ordinaPerArrivo(pTratte, nr);
            break;
        case r_ricerca_partenza_dico:
            printf("Inserisci partenza da ricercare: ");
            scanf("%s", partenza1);
            ricercaPerPartenzaDico(pTratte, nr, partenza1);
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
    printf("Ecco le corse ordinate per data:\n");
    stampa(pTratte, nr);
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
    printf("Ecco le corse ordinate per partenza:\n");
    stampa(pTratte, nr);
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
    printf("Ecco le corse ordinate per destinazione:\n");
    stampa(pTratte, nr);
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
    printf("Ecco le corse ordinate per codice:\n");
    stampa(pTratte, nr);
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

void stampa(sTratta *pTratte[], int nr){
    for(int i=0; i<nr; i++){
        printf("%s %s %s %s %s %s %d\n", pTratte[i] -> codice_tratta, pTratte[i] -> partenza, pTratte[i] -> destinazione, pTratte[i] -> data, pTratte[i] -> ora_partenza, pTratte[i] -> ora_arrivo, pTratte[i] -> ritardo);
    }
    printf("\n");
}

void stampaCont(sTratta tratte[], int nr){
    printf("Il file contiene: \n");
    for(int i=0;i<nr;i++){
        printf("%s %s %s ", tratte[i].codice_tratta, tratte[i].partenza, tratte[i].destinazione);
        printf("%s ", tratte[i].data);
        printf("%s ", tratte[i].ora_partenza);
        printf("%s ", tratte[i].ora_arrivo);
        printf("%d\n", tratte[i].ritardo);
    }
}