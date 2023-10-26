#include <stdio.h>
#include <string.h>
#include<stdlib.h>

#define MAXL 100
#define MAXR 30

typedef struct{
    char codice_tratta[MAXL];
    char partenza[MAXL];
    char destinazione[MAXL];
    char data[MAXL];
    char ora_partenza[MAXL];
    char ora_arrivo[MAXL];
    int ritardo;
}sTratta;

sTratta *ordinateData[MAXR];
sTratta *ordinateCodice[MAXR];
sTratta *ordinatePartenza[MAXR];
sTratta *ordinateArrivo[MAXR];

typedef enum{r_ordina_data, r_ordina_codice, r_ordina_partenza, r_ordina_arrivo, r_ricerca_partenza_dico,
    r_fine, r_errore} comando_e;

int leggiFile(char* nomeFile, sTratta tratte[]);
comando_e leggiComando(void);
void selezionaDati(int nr, comando_e comando,int* pfine, sTratta *ordinatoTemp[]);
void ordinaData(int nr, sTratta *ordinatoTemp[MAXR]);
void ordinaCodice(int nr, sTratta *ordinatoTemp[MAXR]);
void ordinaPartenza(int nr, sTratta *ordinatoTemp[MAXR]);
void ordinaArrivo(int nr, sTratta *ordinatoTemp[MAXR]);
void ricercaDico(int nr, sTratta *ordinatePartenza[MAXR]);
void stampa(int nr, sTratta *ordinatoTemp[MAXR]);

int main() {
    char nomefile[MAXL];
    int nr, fine = 0, *pfine = NULL, i;
    sTratta tratte[MAXR], *ordinatoTemp[MAXR];
    comando_e comando;

    pfine = &fine;

    printf("inserire il nome del file ");
    scanf("%s", nomefile);

    nr = leggiFile(nomefile, tratte);       ///vado a riempire la struct e la variabile numero righe


    for (i = 0; i < nr; i++){
        ordinatoTemp[i] = &tratte[i];
    }

    while(!fine && nr != -1) {
        //Lettura Comando
        comando = leggiComando();       /// funzione per leggere il comando scelto in input

        //Corpo programma
        if (comando != r_errore) {
            selezionaDati(nr, comando, pfine, ordinatoTemp);  /// gestione del comando
        }
    }

    return 0;
}

///lettura del file e scrittura delle componenti della struct
int leggiFile(char* nomeFile, sTratta tratte[MAXR]) {
    FILE *fp;
    int i = 0, nr = 0;

    fp = fopen(nomeFile, "r");

    if(fp != NULL){
        fscanf(fp,"%d", &nr);
        while(!feof(fp)){
            fscanf(fp, "%s %s %s", tratte[i].codice_tratta, tratte[i].partenza, tratte[i].destinazione);
            fscanf(fp, "%s", tratte[i].data);
            fscanf(fp, "%s", tratte[i].ora_partenza);
            fscanf(fp, "%s", tratte[i].ora_arrivo);
            fscanf(fp,"%d", &tratte[i].ritardo);

            i++;
        }
    }
    else{
        printf("errore nell apertura del file");
        return 1;
    }

    fclose(fp);

    return nr;
}

comando_e leggiComando(void){
    //Inizializzazione variabili
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
    else if(strcmp("fine", comando) == 0){
        comandoE = 5;
    }
    else{
        printf("\nComando non riconosciuto! Riprova\n");
        comandoE = 6;
    }
    return comandoE;
}

void selezionaDati(int nr, comando_e comando, int* pfine, sTratta *ordinatoTemp[MAXR]) {

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
        case r_fine:
            *pfine = 1;
            printf("Programma terminato correttamente!\n");
            break;
    }

}

///ordinamento per data
void ordinaData(int nr, sTratta *ordinatoTemp[MAXR]){
    int i, j, l=0, r = nr-1, inverti;
    sTratta *trattaTmp;

    /// INSERTION SORT
    for(i=l+1; i<=r; i++){

        trattaTmp = ordinatoTemp[i];
        j = i - 1;
        inverti = 1;

        while (j >= l && inverti ) {
            ///GESTIONE IN BASE A DATA O ORA
            if (strcmp(trattaTmp->data, ordinatoTemp[j]->data) < 0) {
                ordinatoTemp[j + 1] = ordinatoTemp[j];
            }
            else if(strcmp(trattaTmp->data, ordinatoTemp[j]->data) == 0 && strcmp(trattaTmp->ora_partenza, ordinatoTemp[j]->ora_partenza) < 0) {
                ordinatoTemp[j + 1] = ordinatoTemp[j];
            }
            else if(strcmp(trattaTmp->data, ordinatoTemp[j]->data) == 0 && strcmp(trattaTmp->ora_partenza, ordinatoTemp[j]->ora_partenza) == 0 && strcmp(trattaTmp->ora_arrivo, ordinatoTemp[j]->ora_arrivo) < 0) {
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

    for (i = 0; i < nr; i++){
        ordinateData[i] = ordinatoTemp[i];
    }

    stampa(nr, ordinateData);
}

///FUNZIONE DI ORDINAMENTO IN BASE A CODICE TRATTA
void ordinaCodice(int nr, sTratta *ordinatoTemp[MAXR]){
    int i, j, l=0, r = nr-1;
    sTratta *trattaTmp;

///INSERTION SORT
    for(i=l+1; i<=r; i++){
        trattaTmp = ordinatoTemp[i];
        j = i - 1;

        while (j >= l && strcmp(trattaTmp->codice_tratta, ordinatoTemp[j]->codice_tratta) < 0) {
            ordinatoTemp[j + 1] = ordinatoTemp[j];
            j--;
        }

        ordinatoTemp[j + 1] = trattaTmp;
    }

    for (i = 0; i < nr; i++){
        ordinateCodice[i] = ordinatoTemp[i];
    }

    stampa(nr, ordinateCodice);
}

///FUNZIONE DI ORDINAMENTO IN BASE ALLA STAZIONE DI PARTENZA
void ordinaPartenza(int nr, sTratta *ordinatoTemp[MAXR]){
    int i, j, l=0, r = nr-1;
    sTratta *trattaTmp;

    ///INSERTION SORT
    for(i=l+1; i<=r; i++){
        trattaTmp = ordinatoTemp[i];
        j = i - 1;

        while (j >= l && strcmp(trattaTmp->partenza, ordinatoTemp[j]->partenza) < 0) {
            ordinatoTemp[j + 1] = ordinatoTemp[j];
            j--;
        }

        ordinatoTemp[j + 1] = trattaTmp;
    }

    for (i = 0; i < nr; i++){
        ordinatePartenza[i] = ordinatoTemp[i];
    }

    stampa(nr, ordinatePartenza);
}

/// FUNZIONE DI ORDINAMENTO IN BASE ALLA STAZIONE DI DESTINAZIONE
void ordinaArrivo(int nr, sTratta *ordinatoTemp[]){
    int i, j, l=0, r = nr-1;
    sTratta *trattaTmp;

    ///INSERTION SORT
    for(i=l+1; i<=r; i++){
        trattaTmp = ordinatoTemp[i];
        j = i - 1;

        while (j >= l && strcmp(trattaTmp->destinazione, ordinatoTemp[j]->destinazione) < 0) {
            ordinatoTemp[j + 1] = ordinatoTemp[j];
            j--;
        }

        ordinatoTemp[j + 1] = trattaTmp;
    }

    for (i = 0; i < nr; i++){
        ordinateArrivo[i] = ordinatoTemp[i];
    }
    stampa(nr, ordinateArrivo);
}

///FUNZIONE DI RICERCA DICOTOMICA IN BASE ALLE PARTENZE
void ricercaDico(int nr, sTratta *ordinatoTemp[MAXR]) {

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
void stampa(int nr, sTratta *ordinatoTemp[MAXR]) {
    int i;
    char str[MAXR];
    FILE *fps;

    printf("vuoi stampare a video o in un file? ");
    scanf("%s", str);

    ///STAMPA A FILE
    if(strcasecmp(str, "file") == 0){
        fps = fopen("corseScritte.txt", "w");

        for (i = 0; i < nr; i++){
            fprintf(fps,"%s %s %s ", ordinatoTemp[i]->codice_tratta, ordinatoTemp[i]->partenza, ordinatoTemp[i]->destinazione);
            fprintf(fps,"%s ", ordinatoTemp[i]->data);
            fprintf(fps, "%s ", ordinatoTemp[i]->ora_partenza);
            fprintf(fps,"%s ", ordinatoTemp[i]->ora_arrivo);
            fprintf(fps, "%d\n", ordinatoTemp[i]->ritardo);

        }
        fclose(fps);
    }
        ///STAMA A VIDEO
    else if(strcasecmp(str, "video") == 0) {
        for (i = 0; i < nr; i++) {
            printf("%s %s %s ", ordinatoTemp[i]->codice_tratta, ordinatoTemp[i]->partenza, ordinatoTemp[i]->destinazione);
            printf("%s ", ordinatoTemp[i]->data);
            printf("%s ", ordinatoTemp[i]->ora_partenza);
            printf("%s ", ordinatoTemp[i]->ora_arrivo);
            printf("%d\n", ordinatoTemp[i]->ritardo);
        }
    }
    else
        printf("errore di comando");
}
