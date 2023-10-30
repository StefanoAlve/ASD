#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXL 100
#define MAXR 30

typedef struct{
    char *codice_tratta;
    char *partenza;
    char *destinazione;
    char *data;
    char *ora_partenza;
    char *ora_arrivo;
    int ritardo;
}sTratta;

sTratta **ordinateData;
sTratta **ordinateCodice;
sTratta **ordinatePartenza;
sTratta **ordinateArrivo;

typedef enum{r_ordina_data, r_ordina_codice, r_ordina_partenza, r_ordina_arrivo, r_ricerca_partenza_dico, r_lettura_file,
    r_fine, r_errore} comando_e;

int letturaFile(char* nomeFile, sTratta **ptratte);
comando_e leggiComando(void);
void selezionaDati(int nr, comando_e comando,int* pfine, sTratta *ordinatoTemp);
void ordinaData(int nr, sTratta *ordinatoTemp);
void ordinaCodice(int nr, sTratta *ordinatoTemp);
void ordinaPartenza(int nr, sTratta *ordinatoTemp);
void ordinaArrivo(int nr, sTratta *ordinatoTemp);
void ricercaDico(int nr, sTratta *ordinatePartenza);
void stampa(int nr, sTratta *ordinatoTemp);
void dealloca(int nr, sTratta *tratte);

int main() {
    char nomefile[MAXL];
    int nr, fine = 0, *pfine = NULL, i;
    sTratta *tratte ;
    comando_e comando;

    pfine = &fine;

    printf("inserire il nome del file\n");
    scanf("%s", nomefile);

    nr = letturaFile(nomefile, &tratte);       ///vado a riempire la struct e la variabile numero righe


    for (i = 0; i < nr; i++) {
        printf("%s %s %s ", tratte[i].codice_tratta, tratte[i].partenza,
               tratte[i].destinazione);
        printf("%s ", tratte[i].data);
        printf("%s ", tratte[i].ora_partenza);
        printf("%s ", tratte[i].ora_arrivo);
        printf("%d\n", tratte[i].ritardo);
    }
    while(!fine && nr != -1) {
        //Lettura Comando
        comando = leggiComando();       /// funzione per leggere il comando scelto in input

        //Corpo programma
        if (comando != r_errore) {
            selezionaDati(nr, comando, pfine, tratte);  /// gestione del comando
        }
    }

    dealloca(nr, tratte);

    return 0;
}

///lettura del file e scrittura delle componenti della struct
int letturaFile(char* nomeFile, sTratta **ptratte) {
    FILE *fp;
    int i = 0, nr = 0;
    sTratta *tratte;
    char tmp[MAXR];

    fp = fopen(nomeFile, "r");

    if(fp != NULL){
        fscanf(fp,"%d", &nr);
        tratte = (sTratta *)malloc(nr*sizeof(sTratta)); ///ALLOCO LA STRUCT
        if(tratte == NULL){
            printf("Errore nell'assegnazione della memoria\n");
            exit(1);
        }
        ///ALLOCO TUTTI I CAMPI DELLA STRUCT
        while(!feof(fp)){
            fscanf(fp, "%s", tmp);
            tratte[i].codice_tratta = strdup(tmp);

            fscanf(fp, "%s",  tmp);
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

            i++;
        }
    }
    else{
        printf("errore nell apertura del file");
        exit(1);
    }

    *ptratte = tratte;
    fclose(fp);

    return nr;
}

comando_e leggiComando(void){
    ///INIZIALIZZAZIONE VARIABILI
    char comando[MAXL];
    comando_e comandoE;
    //Corpo funzione
    printf("\n-------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\tLISTA COMANDI\n");
    printf("-------------------------------------------------------------------------------------------------------\n\n");
    printf("ordina_data -> ordina le corse per data, in caso di data uguale verranno ordinate per ora\n");
    printf("ordina_codice -> ordina le corse per codice\n");
    printf("ordina_partenza -> ordina le corse secondo il nome della partenza\n");
    printf("ordina_arrivo -> ordina le corse secondo il nome della destinazione\n");
    printf("ricerca_partenza_dico -> esegue la ricerca dicotomica della partenza inserita\n");
    printf("lettura_file -> legge un nuovo file\n");
    printf("fine -> termina il programma\n\n");
    printf("-------------------------------------------------------------------------------------------------------\n\n");
    printf("Inserisci comando:");
    scanf(" %s", comando);

    ///gestione del comando in base all'input

    if(strcmp("ordina_data", comando) == 0){
        comandoE = 0;
    }
    else if(strcmp("ordina_codice", comando) == 0){
        comandoE = 1;
    }
    else if(strcmp("ordina_partenza",comando) == 0){
        comandoE = 2;
    }
    else if(strcmp("ordina_arrivo",comando) == 0){
        comandoE = 3;
    }
    else if(strcmp("ricerca_partenza_dico",comando) == 0){
        comandoE = 4;
    }
    else if(strcmp("lettura_file",comando) == 0){
        comandoE = 5;
    }
    else if(strcmp("fine", comando) == 0){
        comandoE = 6;
    }
    else{
        printf("\nComando non riconosciuto! Riprova\n");
        comandoE = 7;
    }
    return comandoE;
}

void selezionaDati(int nr, comando_e comando, int* pfine, sTratta *ordinatoTemp) {

///rimando alle funzioni in base alla scelta dell input

    switch(comando){
        case r_ordina_data:
            ordinaData(nr, ordinatoTemp);
            break;
        case r_ordina_codice:
            ordinaCodice(nr, ordinatoTemp);
            break;
        case r_ordina_partenza:
            ordinaPartenza(nr, ordinatoTemp);
            break;
        case r_ordina_arrivo:
            ordinaArrivo(nr, ordinatoTemp);
            break;
        case r_ricerca_partenza_dico:
            ricercaDico(nr, ordinatoTemp);
            break;
        case r_lettura_file:    ///RIMANDO AL MAIN E FACCIO ATTIVARE IL FLAG FINE DA MODO CHE A FINE RICORSIONI ESCA DAL
            main();             ///CICLO SENZA DOVER SCRIVERE FINE N-VOLTE
            dealloca(nr,ordinatoTemp);
            *pfine = 1;
            break;
        case r_fine:
            *pfine = 1;
            printf("Programma terminato correttamente!\n");
            break;
        case r_errore:
            *pfine = 1;
            printf("Errore!\n");
            exit(1);
    }

}

///ordinamento per data
void ordinaData(int nr, sTratta *ordinatoTemp){
    int i, j, l=0, r = nr-1, inverti;
    sTratta trattaTmp;

    /// INSERTION SORT
    for(i=l+1; i<=r; i++){

        trattaTmp = ordinatoTemp[i];
        j = i - 1;
        inverti = 1;

        while (j >= l && inverti ) {
            ///GESTIONE IN BASE A DATA O ORA
            if (strcmp(trattaTmp.data, ordinatoTemp[j].data) < 0) {
                ordinatoTemp[j + 1] = ordinatoTemp[j];
            }
            else if(strcmp(trattaTmp.data, ordinatoTemp[j].data) == 0 && strcmp(trattaTmp.ora_partenza, ordinatoTemp[j].ora_partenza) < 0) {
                ordinatoTemp[j + 1] = ordinatoTemp[j];
            }
            else if(strcmp(trattaTmp.data, ordinatoTemp[j].data) == 0 && strcmp(trattaTmp.ora_partenza, ordinatoTemp[j].ora_partenza) == 0 && strcmp(trattaTmp.ora_arrivo, ordinatoTemp[j].ora_arrivo) < 0) {
                ordinatoTemp[j + 1] = ordinatoTemp[j];
            }
            else
                inverti = 0; /// BOOLEANO PER CAPIRE FINO A QUANDO SCAMBIARE


            if (inverti){
                j--;
            }
        }

        ordinatoTemp[j + 1] = trattaTmp;
    }


    ordinateData = (sTratta **)malloc(nr*sizeof(sTratta*));

    for (i = 0; i < nr; i++){
        ordinateData[i] = &ordinatoTemp[i];
    }

    ///STAMPO E DEALLOCO
    stampa(nr, *ordinateData);

    free(ordinateData);
}

///FUNZIONE DI ORDINAMENTO IN BASE A CODICE TRATTA
void ordinaCodice(int nr, sTratta *ordinatoTemp){
    int i, j, l=0, r = nr-1;
    sTratta trattaTmp;

///INSERTION SORT
    for(i=l+1; i<=r; i++){
        trattaTmp = ordinatoTemp[i];
        j = i - 1;

        while (j >= l && strcmp(trattaTmp.codice_tratta, ordinatoTemp[j].codice_tratta) < 0) {
            ordinatoTemp[j + 1] = ordinatoTemp[j];
            j--;
        }

        ordinatoTemp[j + 1] = trattaTmp;
    }


    ordinateCodice = (sTratta **)malloc(nr*sizeof(sTratta *));

    for (i = 0; i < nr; i++){
        ordinateCodice[i] = &ordinatoTemp[i];
    }

    ///STAMPO E DEALLOCO
    stampa(nr, *ordinateCodice);
    free(ordinateCodice);
}

///FUNZIONE DI ORDINAMENTO IN BASE ALLA STAZIONE DI PARTENZA
void ordinaPartenza(int nr, sTratta *ordinatoTemp){
    int i, j, l=0, r = nr-1;
    sTratta trattaTmp;

    ///INSERTION SORT
    for(i=l+1; i<=r; i++){
        trattaTmp = ordinatoTemp[i];
        j = i - 1;

        while (j >= l && strcmp(trattaTmp.partenza, ordinatoTemp[j].partenza) < 0) {
            ordinatoTemp[j + 1] = ordinatoTemp[j];
            j--;
        }

        ordinatoTemp[j + 1] = trattaTmp;
    }

    ordinatePartenza = (sTratta **)malloc(nr*sizeof(sTratta *));

    for (i = 0; i < nr; i++){
        ordinatePartenza[i] = &ordinatoTemp[i];
    }
    ///STAMPO E DEALLOCO
    stampa(nr, *ordinatePartenza);
    free(ordinatePartenza);
}

/// FUNZIONE DI ORDINAMENTO IN BASE ALLA STAZIONE DI DESTINAZIONE
void ordinaArrivo(int nr, sTratta *ordinatoTemp){
    int i, j, l=0, r = nr-1;
    sTratta trattaTmp;

    ///INSERTION SORT
    for(i=l+1; i<=r; i++){
        trattaTmp = ordinatoTemp[i];
        j = i - 1;

        while (j >= l && strcmp(trattaTmp.destinazione, ordinatoTemp[j].destinazione) < 0) {
            ordinatoTemp[j + 1] = ordinatoTemp[j];
            j--;
        }

        ordinatoTemp[j + 1] = trattaTmp;
    }

    ordinateArrivo = (sTratta **)malloc(nr*sizeof(sTratta *));

    for (i = 0; i < nr; i++){
        ordinateArrivo[i] = &ordinatoTemp[i];
    }
    ///STAMPO E DEALLOCO
    stampa(nr, *ordinateArrivo);
    free(ordinateArrivo);
}

///FUNZIONE DI RICERCA DICOTOMICA IN BASE ALLE PARTENZE
void ricercaDico(int nr, sTratta *ordinatoTemp) {

    ordinaPartenza(nr, ordinatoTemp);   /// ALGORITMO CHE FUNZIONA APOSTERIORI DELL'ORDINAMENTO DELLA STRUCT, CHIEDE DI STAMPARE LA FUNZIONE ORDINATA

    int l = 0, r = nr - 1, m, flag = 1;
    char prtnz[MAXR];


    printf("scegli la stazione da cercare\n");
    scanf("%s", prtnz);

    while (l <= r && flag && flag != 2) {

        m = (r+l)/2;
        if(strcasecmp(ordinatePartenza[m]->partenza, prtnz) == 0){     ///CASO DI CORRISPONDENZA
            flag = 0;
        }
        else if(strcasecmp(ordinatePartenza[m]->partenza, prtnz) < 0){    ///CASO SOTTOVETTORE DESTRO
            l = m + 1;
        }
        else if(strcasecmp(ordinatePartenza[m]->partenza, prtnz) > 0){  /// CASO SOTTOVETTORE SINISTRO
            r = m - 1;
        }
        else{
            printf("errore nella ricerca\n");       /// GESTIONE ERRORE IN INPUT O GENERICO
            flag = 2;
        }
    }
    /// CONTROLLO SE DIETRO L'INDICE DI CORRISPONDEZA VI SIANO PRESENTI ALTRE CORRISPONDENZE
    if (!flag && m != 0) {
        while (strcasecmp(ordinatePartenza[m - 1]->partenza, prtnz) == 0) {
            m--;
        }
    }

    ///PRINTAGGIO DELLE CORRISPONDENZE

    while (m < nr) {
        if(strcasecmp(ordinatePartenza[m]->partenza, prtnz) == 0) {
            printf("%s %s %s ", ordinatePartenza[m]->codice_tratta, ordinatePartenza[m]->partenza,
                   ordinatePartenza[m]->destinazione);
            printf("%s ", ordinatePartenza[m]->data);
            printf("%s ", ordinatePartenza[m]->ora_partenza);
            printf("%s ", ordinatePartenza[m]->ora_arrivo);
            printf("%d\n", ordinatePartenza[m]->ritardo);
        }
        m++;
    }

}

/// FUNZIONE DI STAMPA DELLA STRUCT ORDINATA
void stampa(int nr, sTratta *ordinatoTemp) {
    int i;
    char str[MAXR];

    ///STAMA A VIDEO
    for (i = 0; i < nr; i++) {
        printf("%s %s %s ", ordinatoTemp[i].codice_tratta, ordinatoTemp[i].partenza, ordinatoTemp[i].destinazione);
        printf("%s ", ordinatoTemp[i].data);
        printf("%s ", ordinatoTemp[i].ora_partenza);
        printf("%s ", ordinatoTemp[i].ora_arrivo);
        printf("%d\n", ordinatoTemp[i].ritardo);
    }

}

///DELLOCO TUTTA LA STRUCT
void dealloca(int nr, sTratta *tratte) {
    int i;

    for(i=0; i<nr; i++){
        free(tratte[i].partenza);
        free(tratte[i].data);
        free(tratte[i].destinazione);
        free(tratte[i].ora_partenza);
        free(tratte[i].ora_arrivo);
        free(tratte[i].codice_tratta);
    }
    free(tratte);
}