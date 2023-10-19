#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXR 1000
#define MAXL 30
//struct che definisce la singola corsa
typedef struct {
    char codice_tratta[MAXL];
    char partenza[MAXL];
    char destinazione[MAXL];
    char data[MAXL];
    char ora_partenza[MAXL];
    char ora_arrivo[MAXL];
    int ritardo;
} corsa;
//definisco le variabili enum
typedef enum {
    r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_fine, r_errore
} comando_e;

//definisco i prototipi delle funzioni da utilizzare
comando_e leggiComando(void);

void selezionaDati(corsa vettore_corse[], comando_e comando, int numRighe, int *pFine);

void stampaCorseIntervallo(corsa vettore_corse[], char *dataIn, char *dataFin, int numRighe);

void stampaCorseFermata(corsa vettore_corse[], char *fermataPartenza, int numRighe);

void stampaCorseCapolinea(corsa vettore_corse[], char *fermataCapolinea, int numRighe);

void stampaCorseRitardoPerIntervallo(corsa vettore_corse[], char *dataIn, char *dataFin, char *capolinea, int numRighe);

void stampaCorseRitardoPerCodice(corsa vettore_corse[], char *codiceTratta, int numRighe);

int leggiFile(char *nomeFile, corsa vettore_corse[]);//funzione che apre file, lo legge e riempie la struct

int main(void) {
    int nRighe, *pFine = NULL, fine = 0;
    comando_e comando;
    char nomeFile[MAXR];
    corsa vettore_corse[MAXL];
    pFine = &fine;
    printf("Inserire il nome del file da aprire seguito da .txt:");
    scanf("%s", nomeFile);
    printf("Aprendo il file %s...\n", nomeFile);
    nRighe = leggiFile(nomeFile, vettore_corse);
    //chiedo al'utente cosa vuole fare se non ho un file senza righe (non avrebbe senso) e fino a quando non inserisce la fine
    while (!fine && nRighe > 0) {
        comando = leggiComando();
        if (comando != r_errore) {
            selezionaDati(vettore_corse, comando, nRighe, pFine);
        }
    }
    return 0;
}

int leggiFile(char *nomeFile, corsa vettore_corse[]) {//implemento la funzione
    int righe, i = 0;
    FILE *fp;//puntatore a file
    fp = fopen(nomeFile, "r");
    if (fp == NULL) {
        printf("Impossibile aprire il file.");
        return 1;
    }
    fscanf(fp, "%d", &righe);//primo elemento del file
    printf("Numero di righe scansionate: %d\n", righe);
    while (!(feof(fp))) {//scansiono file fino a eof
        //leggo le colonne e le inserisco nel vettore di tipo corsa
        fscanf(fp, "%s", vettore_corse[i].codice_tratta);
        fscanf(fp, "%s", vettore_corse[i].partenza);
        fscanf(fp, "%s", vettore_corse[i].destinazione);
        fscanf(fp, "%s", vettore_corse[i].data);
        fscanf(fp, "%s", vettore_corse[i].ora_partenza);
        fscanf(fp, "%s", vettore_corse[i].ora_arrivo);
        fscanf(fp, "%d", &vettore_corse[i].ritardo);
        //stampo i contenuti delle righe lette da file
        printf("Riga numero %d:\n", i + 1);
        printf("Codice tratta: %s\t", vettore_corse[i].codice_tratta);
        printf("Partenza: %s\t", vettore_corse[i].partenza);
        printf("Destinazione: %s\t", vettore_corse[i].destinazione);
        printf("Data: %s\t", vettore_corse[i].data);
        printf("Ora partenza: %s\t", vettore_corse[i].ora_partenza);
        printf("Ora arrivo: %s\t", vettore_corse[i].ora_arrivo);
        printf("Ritardo: %d\n\n", vettore_corse[i].ritardo);
        i++;//incremento l'indice della riga i-esima
    }
    fclose(fp);//chiudo file
    return righe;
}

comando_e leggiComando(void) {
    comando_e comandoE;
    char comando[MAXL];
    //Lista comandi
    printf("\nLista comandi:");
    printf("\tdate-> elenca corse per intervallo di date inserito:\n");
    printf("\tpartenza-> elenca corse per fermata di partenza inserita:\n");
    printf("\tcapolinea-> corse in base a capolinea inserito:\n");
    printf("\tritardo-> corse con ritardo a capolinea in un intervallo di date inserito\n");
    printf("\tritardo_tot-> ritardo complessivo per codice di tratta inserito\n");
    printf("\tfine-> termina il programma\n");
    printf("\nInserisci un comando:");
    scanf("%s", comando);
    if (strcmp("date", comando) == 0) {
        comandoE = 0;//assegno il valore ad enum
    } else if (strcmp("partenza", comando) == 0) {
        comandoE = 1;
    } else if (strcmp("capolinea", comando) == 0) {
        comandoE = 2;
    } else if (strcmp("ritardo", comando) == 0) {
        comandoE = 3;
    } else if (strcmp("ritardo_tot", comando) == 0) {
        comandoE = 4;
    } else if (strcmp("fine", comando) == 0) {
        comandoE = 5;
    } else {
        comandoE = 6;
        printf("Comando non riconosciuto.\n");
    }
    return comandoE;
}

//funzione che gestisce gli inserimenti a seconda della scelta del comando e chiama le relative funzioni
void selezionaDati(corsa vettore_corse[], comando_e comando, int numRighe, int *pFine) {
    char dataIn[MAXL], dataFin[MAXL], partenza[MAXL], capolinea[MAXL], codiceTratta[MAXL];
    //gestisco gli input e le chiamate a funzioni di stampa
    switch (comando) {
        case r_date:
            printf("\nInserisci la data iniziale del tipo aaaa/mm/gg:");
            scanf("%s", dataIn);
            printf("\nInserisci la data finale nel formato aaaa/mm/gg:");
            scanf("%s", dataFin);
            printf("\nRicerco corse partite dal %s al %s", dataIn, dataFin);
            stampaCorseIntervallo(vettore_corse, dataIn, dataFin, numRighe);//chiama funzione di stampa
            break;
        case r_partenza:
            printf("\nInserire la fermata di partenza:");
            scanf("%s", partenza);
            stampaCorseFermata(vettore_corse, partenza, numRighe);//chiama funzione di stampa
            break;
        case r_capolinea:
            printf("\nInserire il capolinea:");
            scanf("%s", capolinea);
            stampaCorseCapolinea(vettore_corse, capolinea, numRighe);//chiama funzione di stampa
            break;
        case r_ritardo:
            printf("\nInserire la destinazione:");
            scanf("%s", capolinea);
            printf("\nInserire la data iniziale:");
            scanf("%s", dataIn);
            printf("\nInserire la data finale:");
            scanf("%s", dataFin);
            stampaCorseRitardoPerIntervallo(vettore_corse, dataIn, dataFin, capolinea,
                                            numRighe);//chiama funzione di stampa
            break;
        case r_ritardo_tot:
            printf("\nInserire codice tratta per ritardo:");
            scanf("%s", codiceTratta);
            stampaCorseRitardoPerCodice(vettore_corse, codiceTratta, numRighe);//chiama funzione di stampa
            break;
        case r_fine:
            *pFine = 1;//aggiorno condizione di terminazione
            printf("Fine programma.");
            break;
    }
}

void stampaCorseFermata(corsa vettore_corse[], char *fermataPartenza, int numRighe) {
    int flag = 0;
    printf("\nLe tratte partite dalla fermata %s\n", fermataPartenza);
    for (int i = 0; i < numRighe; i++) {
        if (strcasecmp(vettore_corse[i].partenza, fermataPartenza) ==
            0) {//confronto le due stringhe con funzione senza case-sensitive
            printf("\n%s - %s partito alle ore %s della data %s\n", vettore_corse[i].partenza,
                   vettore_corse[i].destinazione, vettore_corse[i].ora_partenza, vettore_corse[i].data);
            //incremento l'indice della riga i-esima
            flag++;
        }
    }
    if (flag == 0) {
        printf("\nNon sono state trovate tratte per la fermata %s", fermataPartenza);
    }
}

void stampaCorseRitardoPerCodice(corsa vettore_corse[], char *codiceTratta, int numRighe) {
    int ritardoComplessivo = 0, flag = 0;
    for (int i = 0; i < numRighe; ++i) {
        if (strcasecmp(vettore_corse[i].codice_tratta, codiceTratta) ==
            0) {//confronto le due stringhe con funzione senza case-sensitive
            ritardoComplessivo += vettore_corse[i].ritardo;
            flag++;
        }
    }
    if (flag == 0) {//se non ho minuti accumulati
        printf("\n non e' presente la tratta %s", codiceTratta);
    } else {
        printf("\nIl ritardo complessivo per la tratta %s e' %d minuti:\n", codiceTratta, ritardoComplessivo);
    }
}

void stampaCorseCapolinea(corsa vettore_corse[], char *fermataCapolinea, int numRighe) {
    int flag = 0;
    printf("\nLe corse per la fermata %s\n", fermataCapolinea);
    for (int i = 0; i < numRighe; ++i) {
        if (strcasecmp(vettore_corse[i].destinazione, fermataCapolinea) ==
            0) {//confronto le due stringhe con funzione senza case-sensitive
            flag++;
            printf("\n%s - %s arrivato alle ore %s del %s", vettore_corse[i].partenza, vettore_corse[i].destinazione,
                   vettore_corse[i].ora_arrivo, vettore_corse[i].data);
        }
    }
    if (flag == 0) {
        printf("\nNon sono presenti corse per la fermata %s", fermataCapolinea);
    }
}

void stampaCorseIntervallo(corsa vettore_corse[], char *dataIn, char *dataFin, int numRighe) {
    int flag = 0;
    printf("\nLe corse partite dal %s al %s", dataIn, dataFin);
    for (int i = 0; i < numRighe; ++i) {
        if (strcasecmp(vettore_corse[i].data, dataIn) >= 0 &&
            strcasecmp(vettore_corse[i].data, dataFin)) {//controllo se la data sta nell'intervallo
            flag++;
            printf("\nCodice %s da %s a %s in data %s", vettore_corse[i].codice_tratta, vettore_corse[i].partenza,
                   vettore_corse[i].destinazione, vettore_corse[i].data);
        }
    }
    if (flag == 0) {
        printf("\nNon sono presenti corse nel periodo dal %s al %s", dataIn, dataFin);
    }
}

void
stampaCorseRitardoPerIntervallo(corsa vettore_corse[], char *dataIn, char *dataFin, char *capolinea, int numRighe) {
    int flag = 0;
    printf("\nLe tratte che sono partite in ritardo tra il %s e il %s sono:\n", dataIn, dataFin);
    for (int i = 0; i < numRighe; i++) {
        if (strcmp(vettore_corse[i].data, dataIn) >= 0 &&
            strcmp(vettore_corse[i].data, dataFin) <= 0) {//controllo se la data sta nell'intervallo
            if (vettore_corse[i].ritardo > 0) {
                printf("\n%s - %s del %s partito alle ore %s con un ritardo di %d\n", vettore_corse[i].partenza,
                       vettore_corse[i].destinazione, vettore_corse[i].data, vettore_corse[i].ora_partenza,
                       vettore_corse[i].ritardo);
                flag = 1;
            }
        }
    }
    if (flag == 0) {
        printf("\nNon sono presenti tratte arrivate al capolinea %s in ritardo dal %s al %s.\n", capolinea, dataIn,
               dataFin);
    }
}