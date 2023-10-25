#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define inFile "corse.txt"
#define maxRighe 1001
#define maxL 31

// Opzioni menù
typedef enum{
    rStampaFile = 0, rStampaVideo, rOrdinaData, rOrdinaCodice, rOrdinaPartenza, rOrdinaArrivo, rRicercaLineare,
    rRicercaDicotomica, rDate, rPartenza, rCapolinea, rRitardo, rRitardo_tot, rLeggiNuovoFile, rFine
}comando_e;

// Struct per leggere il file
typedef struct{
    char *codiceTratta, *partenza, *destinazione, *data, *oraPartenza, *oraArrivo;
    int ritardo;
}infoFile;

comando_e scegliComando();
infoFile *allocaMemoria(const int *numRighe);
infoFile *leggiFileEAssegna(int *numRighe, FILE *fin, const char *nomeFile);
void deallocaMemoria(infoFile *dati, int numRighe);
void selezionaDati();
void stampaFile(infoFile *info, int numRighe);
void stampaVideo(infoFile *info, int numRighe);
void date(infoFile *info, int numRighe);
void partenza(infoFile *dati, int numRighe);
void destinazione(infoFile *dati, int numRighe);
void ricercaDicotomica(infoFile *dati, int numRighe, char *k);
void ricercaLineare(infoFile *info, int numRighe);
void ritardo(infoFile *info, int numRighe);
void ritardo_tot(infoFile *info, int numRighe);
infoFile *copiaStruttura(infoFile *dati, int numRighe);
infoFile *sortPart(infoFile *pPartenza, int numRighe);
infoFile *sortData(infoFile *pData, int numRighe);
infoFile *sortCodice(infoFile *pCodice, int numRighe);
infoFile *sortArrivo(infoFile *pArrivo, int numRighe);

int main(){

    selezionaDati();

    return 0;
}

//Gestione menu
void selezionaDati(){
    int flag = 1, numRighe = 0;
    char k[maxL] = "\0";
    char nomeFile[maxL] = "corse.txt";
    comando_e cmd = scegliComando();
    FILE *fin = NULL;
    infoFile *dati;
    //Struttura da ordinare
    infoFile *pCodice, *pPartenza, *pArrivo, *pData;

    //Chiamo manualmente la prima lettura del file
    dati = leggiFileEAssegna(&numRighe, fin, nomeFile);
    //Allocazione e copia delle strutture create per essere ordinate
    pCodice = copiaStruttura(dati, numRighe);
    pPartenza = copiaStruttura(dati ,numRighe);
    pArrivo = copiaStruttura(dati ,numRighe);
    pData = copiaStruttura(dati ,numRighe);

    //Assegnazione della struttura infoFile

    while(flag){
        switch(cmd){
            case rLeggiNuovoFile:
                //Deallocazione
                deallocaMemoria(pCodice, numRighe);
                deallocaMemoria(pPartenza, numRighe);
                deallocaMemoria(pArrivo, numRighe);
                deallocaMemoria(pData, numRighe);
                deallocaMemoria(dati, numRighe);

                //Nome nuovo file
                printf("NOME FILE INPUT:\n");
                scanf("%s", nomeFile);

                //Assegnazione a strutture
                dati = leggiFileEAssegna(&numRighe, fin, nomeFile);
                pCodice = copiaStruttura(dati, numRighe);
                pPartenza = copiaStruttura(dati ,numRighe);
                pArrivo = copiaStruttura(dati ,numRighe);
                pData = copiaStruttura(dati ,numRighe);
                printf("Nuovo file letto!!\n");
                break;

                //STAMPA IN FILE
            case rStampaFile:
                stampaFile(dati, numRighe);
                break;

                //STAMPA A VIDEO
            case rStampaVideo:
                stampaVideo(dati, numRighe);
                break;

                //ORDINAMENTO PER CAMPO DATA
            case rOrdinaData:
                pData = sortData(pData, numRighe);
                printf("STRUTTURA ORDINATA PER DATA:\n");
                stampaVideo(pData, numRighe);
                break;

                //ORDINAMENTO PER CAMPO CODICE
            case rOrdinaCodice:
                pCodice = sortCodice(pCodice, numRighe);
                printf("STRUTTURA ORDINATA PER CODICE:\n");
                stampaVideo(pCodice, numRighe);
                break;

                //ORDINAMENTO PER CAMPO PARTENZA
            case rOrdinaPartenza:
                pPartenza = sortPart(pPartenza, numRighe);
                printf("STRUTTURA ORDINATA PER PARTENZA:\n");
                stampaVideo(pPartenza, numRighe);
                break;

                //ORDINAMENTO PER CAMPO ARRIVO
            case rOrdinaArrivo:
                pArrivo = sortArrivo(pArrivo, numRighe);
                printf("STRUTTURA ORDINATA PER ARRIVO:\n");
                stampaVideo(pArrivo, numRighe);
                break;

                //RICERCA LINEARE
            case rRicercaLineare:
                ricercaLineare(dati, numRighe);
                break;

                //RICERCA DICOTOMICA
            case rRicercaDicotomica:
                printf("Inserisci sotto stringa:\n");
                scanf("%s", k);
                pPartenza = sortPart(pPartenza, numRighe);
                ricercaDicotomica(pPartenza, numRighe, k);
                break;

            case rDate:
                date(dati, numRighe);
                break;

            case rPartenza:
                partenza(dati, numRighe);
                break;

            case rCapolinea:
                destinazione(dati, numRighe);
                break;

            case rRitardo:
                ritardo(dati, numRighe);
                break;

            case rRitardo_tot:
                ritardo_tot(dati, numRighe);
                break;

            case rFine:
                flag = 0;
                break;
            default:
                printf("COMANDO INESISTENTE, RIPROVA\n");
        }
        if(cmd != rFine) cmd = scegliComando();

        else{
            deallocaMemoria(pCodice, numRighe);
            deallocaMemoria(pPartenza, numRighe);
            deallocaMemoria(pArrivo, numRighe);
            deallocaMemoria(pData, numRighe);
            deallocaMemoria(dati, numRighe);
        }
    }
}

// Stampa in base al codice scritto da tastiera
void ritardo_tot(infoFile *info, int numRighe){
    char codice[maxL];
    int i, ritardo = 0, controllo = 1;

    //Prendo le informazioni in input
    printf("Inserire il codice del mezzo da controllare:\n");
    scanf("%s", codice);
    printf("Ritardo totale del codice %s:", codice);

    for(i = 0; i < numRighe; i++){
        if(strcasecmp(codice, info[i].codiceTratta) == 0 && info[i].ritardo != 0){
            ritardo += info[i].ritardo;
            controllo = 0;
        }
    }
    if(controllo){
        printf("Nessuna corrispondenza trovata.\n");
    }
    printf(" %d\n", ritardo);
}

// Stampa in base alle date inserite da tastiera
void ritardo(infoFile *info, int numRighe){
    char start[maxL], end[maxL];
    int i, controllo = 1;

    // Prendo le informazioni in input
    printf("Inserire le date di inizio e fine da controllare:\n");
    scanf("%s", start);
    scanf("%s", end);

    printf("Le corse tra il %s e il %s con ritardo sono:\n", start, end);
    for (i = 0; i < numRighe; i++){

        // Se start è piu piccolo ed end è piu grande della data e ritardo è diverso da 0 si stampa la data
        if (strcasecmp(start, info[i].data) != 1 && strcasecmp(info[i].data, end) != 1 && info[i].ritardo != 0){

            printf("%s %s %s ", info[i].codiceTratta, info[i].partenza, info[i].destinazione);
            printf("%s %s %s %d\n", info[i].data, info[i].oraPartenza, info[i].oraArrivo, info[i].ritardo);
            controllo = 0;
        }
    }
    if(controllo){
        printf("Nessuna corrispondenza trovata.\n");
    }
    printf("\n");
}

//Ricerca lineare
void ricercaLineare(infoFile *info, int numRighe){
    int trovato = 0;
    char prefisso[maxL];

    //input
    printf("Inserisci il prefisso:\n");
    scanf("%s",prefisso);

    //ricerca lineare
    printf("Ecco le corrispondenza della ricerca:\n");

    for(int i = 0; i < numRighe; i++){
        if (strstr(info[i].partenza, prefisso) != NULL) {

            // La stazione di partenza contiene il prefisso
            printf("%s %s %s ", info[i].codiceTratta, info[i].partenza, info[i].destinazione);
            printf("%s %s %s %d\n", info[i].data, info[i].oraPartenza, info[i].oraArrivo, info[i].ritardo);
            trovato = 1;
        }
    }
    if(!trovato)
        printf("Nessuna corrispondenza!\n");
}

//Ordinamento per campo destinazione
infoFile *sortArrivo(infoFile *pArrivo, int numRighe){
    int i, j;
    infoFile key;

    for (i = 1; i < numRighe; i++) {
        key = pArrivo[i];
        j = i - 1;

        while (j >= 0 && strcmp(pArrivo[j].destinazione, key.destinazione) > 0) {
            pArrivo[j + 1] = pArrivo[j];
            j--;
        }
        pArrivo[j + 1] = key;
    }
    return pArrivo;
}

//Ordinamento per campo Codice
infoFile *sortCodice(infoFile *pCodice, int numRighe){
    int i, j;
    infoFile key;

    for (i = 1; i < numRighe; i++) {
        key = pCodice[i];
        j = i - 1;

        while (j >= 0 && strcmp(pCodice[j].codiceTratta, key.codiceTratta) > 0) {
            pCodice[j + 1] = pCodice[j];
            j--;
        }
        pCodice[j + 1] = key;
    }
    return pCodice;
}

//Ordinamento per campo data
infoFile *sortData(infoFile *pData, int numRighe){
    int i, j;
    infoFile key;

    for (i = 1; i < numRighe; i++) {
        key = pData[i];
        j = i - 1;

        while (j >= 0 && strcmp(pData[j].data, key.data) > 0) {
            pData[j + 1] = pData[j];
            j--;
        }
        pData[j + 1] = key;
    }
    return pData;
}

//Ordinamento per campo partenza
infoFile *sortPart(infoFile *pPartenza, int numRighe){
    int i, j;
    infoFile key;

    for (i = 1; i < numRighe; i++) {
        key = pPartenza[i];
        j = i - 1;

        while (j >= 0 && strcmp(pPartenza[j].partenza, key.partenza) > 0) {
            pPartenza[j + 1] = pPartenza[j];
            j--;
        }
        pPartenza[j + 1] = key;
    }
    return pPartenza;
}

//Copia di dati in un'altra struttura che verrà ordinata
infoFile *copiaStruttura(infoFile *dati, int numRighe){
    infoFile *doveCopiare;

    doveCopiare = allocaMemoria(&numRighe);

    for(int i = 0; i < numRighe; i++){

        //Uso strdup per non avere problemi con la deallocazione
        doveCopiare[i].partenza = strdup(dati[i].partenza);
        doveCopiare[i].codiceTratta = strdup(dati[i].codiceTratta);
        doveCopiare[i].data = strdup(dati[i].data);
        doveCopiare[i].destinazione = strdup(dati[i].destinazione);
        doveCopiare[i].oraArrivo = strdup(dati[i].oraArrivo);
        doveCopiare[i].oraPartenza = strdup(dati[i].oraPartenza);
        doveCopiare[i].ritardo = dati[i].ritardo;
    }
    return doveCopiare;
}

//Ricerca dicotomica
void ricercaDicotomica(infoFile *dati, int numRighe, char *k){
    int m, l = 0, r = numRighe - 1, found = 0;

    while(l <= r) {
        m = (l + r) / 2;

        //Se contiene la sotto stringa stampa
        if(strstr(dati[m].partenza, k) != NULL) {
            printf("%s %s %s ", dati[m].codiceTratta, dati[m].partenza, dati[m].destinazione);
            printf("%s %s %s %d\n", dati[m].data, dati[m].oraPartenza, dati[m].oraArrivo, dati[m].ritardo);
            found = 1;
        }

        //Se la sotto stringa è maggiore si sposta nel sotto vettore di destra
        if(strcasecmp(dati[m].partenza, k) < 0 || found == 1){
            l = m+1; found = 0;
        }
            //si sposta nel sotto vettore di sinistra
        else
            r = m-1;
    }
}

// Stampa a seconda del capolinea scritto da tastiera
void destinazione(infoFile *dati, int numRighe){
    char arrivo[maxL];
    int i, controllo = 1;

    // Prendo la destinazione di arrivo in input
    printf("Inserire la destinazione di arrivo:\n");
    scanf("%s", arrivo);
    printf("Le fermate con destinazione %s sono:\n", arrivo);

    for(i = 0; i < numRighe; i++){
        if(strcasecmp(arrivo, dati[i].destinazione) == 0){
            printf("%s %s %s ", dati[i].codiceTratta, dati[i].partenza, dati[i].destinazione);
            printf("%s %s %s %d\n", dati[i].data, dati[i].oraPartenza, dati[i].oraArrivo, dati[i].ritardo);
            controllo = 0;
        }
    }
    if(controllo) {
        printf("Nessuna corrispondenza trovata.\n");
    }
    printf("\n");
}

// Stampa in base alla partenza scritta da tastiera
void partenza(infoFile *dati, int numRighe){
    char partenza[maxL];
    int i, controllo = 1;

    // Prendo la destinazione di partenza in input
    printf("Inserire la destinazione di partenza:\n");
    scanf("%s", partenza);
    printf("Le fermate con partenza %s sono:\n", partenza);

    for(i = 0; i < numRighe; i++){
        if(strcasecmp(partenza, dati[i].partenza) == 0){
            printf("%s %s %s ", dati[i].codiceTratta, dati[i].partenza, dati[i].destinazione);
            printf("%s %s %s %d\n", dati[i].data, dati[i].oraPartenza, dati[i].oraArrivo, dati[i].ritardo);
            controllo = 0;
        }
    }
    if(controllo){
        printf("Nessuna corrispondenza trovata.\n");
    }
    printf("\n");
}

//Visualizzazione tra due date
void date(infoFile *info, int numRighe){
    char start[maxL], end[maxL];
    int i, controllo = 1;

    // Prendo le informazioni scritte in input
    printf("Inserisci la data di inizio e di fine da controllare:\n");
    scanf("%s %s", start, end);

    printf("Le corse tra il %s e il %s sono:\n", start, end);
    for (i = 0; i < numRighe; i++){

        // Se start è piu piccolo ed end è piu grande della data si stampa la data
        if (strcasecmp(start, info[i].data) != 1 && strcasecmp(info[i].data, end) != 1){
            printf("%s %s %s ", info[i].codiceTratta, info[i].partenza, info[i].destinazione);
            printf("%s %s %s %d\n", info[i].data, info[i].oraPartenza, info[i].oraArrivo, info[i].ritardo);
            controllo = 0;
        }
    }
    if(controllo){
        printf("Nessuna corrispondenza trovata.");
    }
    printf("\n");
}

//Stampa a video del file
void stampaVideo(infoFile *info, int numRighe){

    for(int i = 0; i < numRighe; i++){
        printf("%s %s %s ", info[i].codiceTratta, info[i].partenza, info[i].destinazione);
        printf("%s %s %s %d\n", info[i].data, info[i].oraPartenza, info[i].oraArrivo, info[i].ritardo);
    }
}

//Stampa dati salvati in file
void stampaFile(infoFile *info, int numRighe){
    char nomeFile[maxL];
    FILE *fout;

    //nome file
    printf("Inserisci nome del file dove viene scritto il log:\n");
    scanf("%s", nomeFile);

    //apertura file di scrittura
    fout = fopen(nomeFile, "w");

    //stampa nel file
    for(int i = 0; i < numRighe; i++){
        fprintf(fout,"%s %s %s", info[i].codiceTratta, info[i].partenza, info[i].destinazione);
        fprintf(fout," %s %s %s %d\n", info[i].data, info[i].oraPartenza, info[i].oraArrivo, info[i].ritardo);
    }

    fclose(fout);
    printf("Log scritto con successo!\n");
}

//Deallocazione memoria
void deallocaMemoria(infoFile *dati, int numRighe){
    for(int i = 0; i < numRighe; i++){
        free(dati[i].oraPartenza);
        free(dati[i].data);
        free(dati[i].oraArrivo);
        free(dati[i].codiceTratta);
        free(dati[i].partenza);
        free(dati[i].destinazione);
    }
    free(dati);
}

//Allocazione dinamica
infoFile *allocaMemoria(const int *numRighe){

    infoFile *dati;

    //Alloco *dati
    dati = (infoFile *)malloc(*numRighe * sizeof(infoFile));
    //Gestione errori
    if(dati == NULL){
        printf("ERRORE ALLOCAZIONE MEMORIA\n");
        exit(1);
    }
    //Allocazione campi di *dati per ogni riga
    for(int i = 0; i < *numRighe; i++){
        dati[i].destinazione = (char *)malloc(maxL * sizeof (char));
        dati[i].partenza = (char *)malloc(maxL * sizeof (char));
        dati[i].codiceTratta = (char *)malloc(maxL * sizeof (char));
        dati[i].data = (char *)malloc(maxL * sizeof (char));
        dati[i].oraArrivo = (char *)malloc(maxL * sizeof (char));
        dati[i].oraPartenza = (char *)malloc(maxL * sizeof (char));

        //Gestione errori
        if(dati[i].destinazione == NULL || dati[i].partenza == NULL ||
           dati[i].codiceTratta == NULL || dati[i].data == NULL ||
           dati[i].oraArrivo == NULL || dati[i].oraPartenza == NULL){

            printf("ERRORE ALLOCAZIONE MEMORIA\n");
            exit(2);
        }
    }
    return dati;
}

//Lettura file e lettura prima riga del file
infoFile *leggiFileEAssegna(int *numRighe, FILE *fin, const char *nomeFile){

    infoFile *dati;

    if((fin = fopen(nomeFile, "r")) == NULL){
        printf("ERRORE APERTURA FILE %s", nomeFile);
        exit(3);
    }
    fscanf(fin, "%d", numRighe);

    //Allocazione Memoria
    dati = allocaMemoria(numRighe);

    //Assegnazione informazioni
    for(int i = 0; i < *numRighe; i++) {
        fscanf(fin, "%s%s%s", dati[i].codiceTratta, dati[i].partenza, dati[i].destinazione);
        fscanf(fin, "%s%s%s%d", dati[i].data, dati[i].oraArrivo, dati[i].oraPartenza, &dati[i].ritardo);
    }

    fclose(fin);
    return dati;
}

// Riceve da tastiera il comando e ritorna il numero corrispondente al comando
comando_e scegliComando(){
    comando_e comando;
    char scelta[maxL];

    // Tabella per il confronto con l'input da tastiera
    char comandi[15][maxL] = {"stampa_file", "stampa_video", "ordina_data", "ordina_codice",
                              "ordina_partenza","ordina_arrivo","ricerca_lineare","ricerca_dicotomica",
                              "date", "partenza","capolinea", "ritardo",
                              "ritardo_tot", "leggi_nuovo_file", "fine"};

    //input da tastiera
    printf("------------------------------------------------------------------\n");
    printf("\t\t\tINSERISCI COMANDO\n");
    printf("------------------------------------------------------------------\n");
    printf("-stampa_file \n-stampa_video \n-ordina_data \n-ordina_codice"
           "\n-ordina_partenza \n-ordina_arrivo \n-ricerca_lineare \n-ricerca_dicotomica \n-date \n-partenza"
           "\n-capolinea \n-ritardo \n-ritardo_tot \n-leggi_nuovo_file \n-fine:\n");
    scanf("%s", scelta);
    strlwr(scelta);

    // Confronto tra scelta e i comandi preimpostati, ritorno del comando selezionato (un numero)
    comando = 0;
    while(comando < 15 && strcmp(scelta, comandi[comando]) != 0){
        comando++;
    }

    return comando;
}
