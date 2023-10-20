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
//definisco le variabili enum aggiornate
typedef enum {
    r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_ordina_data, r_ordina_codice,
    r_ordina_partenza, r_ordina_arrivo, r_ricerca_dicotomica, r_fine, r_errore
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

void oridinaData(corsa *pCorse[], int numRighe);

void ordinaCodice(corsa *pCorse[], int numRighe);

void ordinaPartenza(corsa *pCorse[], int numRighe);

void ordinaArrivo(corsa *pCorse[], int numRighe);

void ordinaPerPartenzaDicotomica(corsa *pCorse[], int numRighe, char *partenza);

void stampaOutput(corsa *pCorse[], int numRighe);

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
        printf("Impossibile aprire il file.\n");
        return -1;
    }
    fscanf(fp, "%d", &righe);//primo elemento del file
    printf("\nNumero di righe scansionate: %d\n", righe);
    while (!(feof(fp)) && i < righe) {//scansiono file fino a eof
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
    //Lista comandi aggiornata
    printf("\nLista comandi:");
    printf("\n\tdate-> elenca corse per intervallo di date inserito:\n");
    printf("\tpartenza-> elenca corse per fermata di partenza inserita:\n");
    printf("\tcapolinea-> corse in base a capolinea inserito:\n");
    printf("\tritardo-> corse con ritardo a capolinea in un intervallo di date inserito\n");
    printf("\tritardo_tot-> ritardo complessivo per codice di tratta inserito\n");
    printf("\tordina_data-> ordina vettore per data e in caso verra' considerata l'ora\n");
    printf("\tordina_codice-> ordina vettore per codice tratta\n");
    printf("\tordina_partenza-> ordina vettore per fermata di partenza\n");
    printf("\tordina_destinazione-> ordina vettore per fermata di destinazione\n");
    printf("\tordina_partenza_dicotomica-> ordina vettore per partenza usando algoritmo di ordinamento dicotomico\n");
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
    } else if (strcmp("ordina_data", comando) == 0) {
        comandoE = 5;
    } else if (strcmp("ordina_codice", comando) == 0) {
        comandoE = 6;
    } else if (strcmp("ordina_partenza", comando) == 0) {
        comandoE = 7;
    } else if (strcmp("ordina_destinazione", comando) == 0) {
        comandoE = 8;
    } else if (strcmp("ordina_partenza_dicotomica", comando) == 0) {
        comandoE = 9;
    } else if (strcmp("fine", comando) == 0) {
        comandoE = 10;
    } else {
        comandoE = 11;
        printf("Comando non riconosciuto.\n");
    }
    return comandoE;
}

//funzione che gestisce gli inserimenti a seconda della scelta del comando e chiama le relative funzioni
void selezionaDati(corsa vettore_corse[], comando_e comando, int numRighe, int *pFine) {
    char dataIn[MAXL], dataFin[MAXL], partenza[MAXL], capolinea[MAXL], codiceTratta[MAXL];
    corsa *pCorse[MAXR];//puntatore alla struct
    for (int i = 0; i < numRighe; ++i) {
        pCorse[i] = &vettore_corse[i];
    }

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
        case r_ordina_data:
            oridinaData(pCorse, numRighe);
            break;
        case r_ordina_codice:
            ordinaCodice(pCorse, numRighe);
            break;
        case r_ordina_partenza:
            ordinaPartenza(pCorse, numRighe);
            break;
        case r_ordina_arrivo:
            ordinaArrivo(pCorse, numRighe);
            break;
        case r_ricerca_dicotomica:
            printf("\nInserisci la stazione di partenza:");
            scanf("%s", partenza);
            ordinaPerPartenzaDicotomica(pCorse, numRighe, partenza);
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

void stampaOutput(corsa *pCorse[], int numRighe) {
    for (int i = 0; i < numRighe; ++i) {
        printf("\n%s %s %s %s %s %s %d", pCorse[i]->codice_tratta, pCorse[i]->partenza, pCorse[i]->destinazione,
               pCorse[i]->data, pCorse[i]->ora_partenza, pCorse[i]->ora_arrivo, pCorse[i]->ritardo);
    }
}

//utilizzzo insertion sort andando a verificare che se le date sono uguali allora confronto le ore di partenza ed in caso analogo conronto sull'orario di arrivo
void oridinaData(corsa *pCorse[], int numRighe) {
    int i, j, flag;
    corsa *temp;
    for (i = 1; i < numRighe; ++i) {
        temp = pCorse[i];
        j = i - 1;
        flag = 1;
        while (j >= 0 && flag) {
            if (strcmp(temp->data, pCorse[j]->data) < 0) {
                pCorse[j + 1] = pCorse[j];
            } else if (strcmp(temp->data, pCorse[j]->data) == 0 &&
                       strcmp(temp->ora_partenza, pCorse[j]->ora_partenza) < 0) {
                pCorse[j + 1] = pCorse[j];
            } else if (strcmp(temp->data, pCorse[j]->data) == 0 &&
                       strcmp(temp->ora_partenza, pCorse[j]->ora_partenza) == 0 &&
                       strcmp(temp->ora_arrivo, pCorse[j]->ora_arrivo) < 0) {
                pCorse[j + 1] = pCorse[j];
            } else {
                flag = 0;
            }
            if (flag) {
                j--;
            }
        }
        pCorse[j + 1] = temp;
    }
    printf("\nCorse ordinate per data/orari:");
    stampaOutput(pCorse, numRighe);
}

void ordinaCodice(corsa *pCorse[], int numRighe) {
    int i, j;
    corsa *temp;
    for (i = 1; i < numRighe; i++) {
        temp = pCorse[i];
        j = i - 1;
        while (j >= 0 && strcmp(temp->codice_tratta, pCorse[j]->codice_tratta) < 0) {
            pCorse[j + 1] = pCorse[j];
            j--;
        }
        pCorse[j + 1] = temp;
    }
    printf("\nTratte ordinate per codice:\n");
    stampaOutput(pCorse, numRighe);
}

void ordinaPartenza(corsa *pCorse[], int numRighe) {
    int i, j;
    corsa *temp;
    for (i = 1; i < numRighe; i++) {
        temp = pCorse[i];
        j = i - 1;
        while (j >= 0 && strcmp(temp->partenza, pCorse[j]->partenza) < 0) {
            pCorse[j + 1] = pCorse[j];
            j--;
        }
        pCorse[j + 1] = temp;
    }
    printf("\nTratte ordinate per partenza:\n");
    stampaOutput(pCorse, numRighe);
}

void ordinaArrivo(corsa *pCorse[], int numRighe) {
    int i, j;
    corsa *temp;
    for (i = 1; i < numRighe; i++) {
        temp = pCorse[i];
        j = i - 1;
        while (j >= 0 && strcmp(temp->destinazione, pCorse[j]->destinazione) < 0) {
            pCorse[j + 1] = pCorse[j];
            j--;
        }
        pCorse[j + 1] = temp;
    }
    printf("\nCorse ordinate per fermata di arrivo:\n");
    stampaOutput(pCorse, numRighe);
}
//ho scelto di utilizzare un ciclo do-while in quanto la mininma esecuzione è una ed implemento l'algoritmo di ricerca binaria
void ordinaPerPartenzaDicotomica(corsa *pCorse[], int numRighe, char *partenza) {
    ordinaPartenza(pCorse,numRighe);//ordino per partenze per usare la ricerca dicotomica
    int i, j, flag = 0, xm;
    i=0;
    j= numRighe - 1;
    fflush(stdin);
    fflush(stdout);
    printf("\n\nLe corse trovate sono:\n");
    do{
        xm = (i + j) / 2;
        if(strncasecmp(partenza, pCorse[xm]->partenza, 3) < 0){
            j = xm - 1;//mi sposto a sinistra di xm
        }
        else if(strncasecmp(partenza, pCorse[xm]->partenza, 3) > 0){
            i = xm + 1;//mi sposto a destra di
        }
        //stampo i valori se trovo la chiave su xm oppure sugli indici adiacenti ad xm
        else if(strncasecmp(partenza, pCorse[xm]->partenza, 3) == 0){
            printf("%s %s %s %s %s %s %d\n", pCorse[xm] -> codice_tratta, pCorse[xm] -> partenza, pCorse[xm] -> destinazione, pCorse[xm] -> data, pCorse[xm] -> ora_partenza, pCorse[xm] -> ora_arrivo, pCorse[xm] -> ritardo);
            if (xm + 1 < numRighe && strncasecmp(partenza, pCorse[xm + 1]->partenza, 3) == 0)
                printf("%s %s %s %s %s %s %d\n", pCorse[xm + 1]->codice_tratta, pCorse[xm + 1]->partenza, pCorse[xm + 1]->destinazione, pCorse[xm + 1]->data, pCorse[xm + 1]->ora_partenza, pCorse[xm + 1]->ora_arrivo, pCorse[xm + 1]->ritardo);
            if (xm - 1 > 0 && strncasecmp(partenza, pCorse[xm - 1]->partenza, 3) == 0)
                printf("%s %s %s %s %s %s %d\n", pCorse[xm - 1]->codice_tratta, pCorse[xm - 1]->partenza, pCorse[xm - 1]->destinazione, pCorse[xm - 1]->data, pCorse[xm - 1]->ora_partenza, pCorse[xm - 1]->ora_arrivo, pCorse[xm - 1]->ritardo);
            flag = 1;//condizione di terminazione forzata perchè ho trovato la chiave
        }
    }while(!flag && i<=j);
}
