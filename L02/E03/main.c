#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAXL 30 //indica lunghezza massima della string
//struct che definisce la singola corsa
typedef struct {
    char *codice_tratta;
    char *partenza;
    char *destinazione;
    char *data;
    char *ora_partenza;
    char *ora_arrivo;
    int ritardo;
} corsa;

//struct che contiene puntatori ai vettori di corsa
typedef struct {
    corsa **ordinatoPerCodice;
    corsa **ordinatoPerData;
    corsa **ordinatoPerPartenza;
    corsa **ordinatoPerArrivo;
} pOrdinato;

//definisco le variabili enum aggiornate
typedef enum {
    r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_ordina_data, r_ordina_codice,
    r_ordina_partenza, r_ordina_arrivo, r_ricerca_dicotomica, r_fine, r_errore
} comando_e;

//definisco i prototipi delle funzioni da utilizzare
comando_e leggiComando(void);

void selezionaDati(corsa vettore_corse[], comando_e comando, int numRighe, int *pFine, pOrdinato *pOrdinamento);

void stampaCorseIntervallo(corsa vettore_corse[], char *dataIn, char *dataFin, int numRighe);

void stampaCorseFermata(corsa vettore_corse[], char *fermataPartenza, int numRighe);

void stampaCorseCapolinea(corsa vettore_corse[], char *fermataCapolinea, int numRighe);

void stampaCorseRitardoPerIntervallo(corsa vettore_corse[], char *dataIn, char *dataFin, char *capolinea, int numRighe);

void stampaCorseRitardoPerCodice(corsa vettore_corse[], char *codiceTratta, int numRighe);

int leggiFile(corsa **vettore_corse);//funzione che apre file, lo legge e riempie la struct

void ordinaData(corsa *pCorse[], int numRighe);

void ordinaCodice(corsa *pCorse[], int numRighe);

void ordinaPartenza(corsa *pCorse[], int numRighe);

void ordinaArrivo(corsa *pCorse[], int numRighe);

void ordinaPerPartenzaDicotomica(corsa *pCorse[], int numRighe, char *partenza);

void stampaOutput(corsa *pCorse[], int numRighe);

void inizializzaPuntatoreTratte(pOrdinato *pOrdinamento, int numRighe, corsa vett_corse[]);

void freePuntatoreTratte(pOrdinato *pOrdinamento);

void freeTratte(int numRighe, corsa *vett_corse);

void stampaLog(int numRighe, corsa **vett_corse);

int main(void) {
    int nRighe, *pFine = NULL, fine = 0;
    comando_e comando;
    pOrdinato ordinamenti;
    corsa *vettore_corse;
    pFine = &fine;
    nRighe = leggiFile(&vettore_corse);
    inizializzaPuntatoreTratte(&ordinamenti, nRighe, vettore_corse);
    while (!fine && nRighe != 0) {
        comando = leggiComando();
        selezionaDati(vettore_corse, comando, nRighe, pFine, &ordinamenti);

    }
    freePuntatoreTratte(&ordinamenti);
    freeTratte(nRighe, vettore_corse);

    return 0;
}

int leggiFile(corsa **vettore_corse) {//implemento la funzione
    int righe, i = 0;
    FILE *fp_in;//puntatore a file
    char nomeFile[MAXL], sTemp[MAXL];
    corsa *corse;
    printf("Inserire il nome del file da aprire seguito da .txt:");
    scanf("%s", nomeFile);
    printf("Aprendo il file %s...\n", nomeFile);
    fp_in = fopen(nomeFile, "r");
    if (fp_in != NULL) {
        fscanf(fp_in, "%d", &righe);
        corse = (corsa *) malloc(righe * sizeof(corsa));
        if (corse == NULL) {
            printf("\nErrore assegnazione memoria");
            exit(2);
        }
        for (int i = 0; i < righe; i++) {
            fscanf(fp_in, "%s", sTemp);
            corse[i].codice_tratta = strdup(sTemp);
            fscanf(fp_in, "%s", sTemp);
            corse[i].partenza = strdup(sTemp);
            fscanf(fp_in, "%s", sTemp);
            corse[i].destinazione = strdup(sTemp);
            fscanf(fp_in, "%s", sTemp);
            corse[i].data = strdup(sTemp);
            fscanf(fp_in, "%s", sTemp);
            corse[i].ora_partenza = strdup(sTemp);
            fscanf(fp_in, "%s", sTemp);
            corse[i].ora_arrivo = strdup(sTemp);
            fscanf(fp_in, "%d", &corse[i].ritardo);
        }
        *vettore_corse = corse;
        stampaLog(righe, vettore_corse);
    } else {
        printf("\nErrore nell'apertura del file.");
        exit(1);
    }
    fclose(fp_in);
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
void selezionaDati(corsa vettore_corse[], comando_e comando, int numRighe, int *pFine, pOrdinato *pOrdinamento) {
    char dataIn[MAXL], dataFin[MAXL], partenza[MAXL], capolinea[MAXL], codiceTratta[MAXL];
    corsa *pCorse[numRighe];//puntatore alla struct
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
            stampaOutput(pOrdinamento->ordinatoPerData, numRighe);
            break;
        case r_ordina_codice:
            stampaOutput(pOrdinamento->ordinatoPerCodice, numRighe);
            break;
        case r_ordina_partenza:
            stampaOutput(pOrdinamento->ordinatoPerPartenza, numRighe);
            break;
        case r_ordina_arrivo:
            stampaOutput(pOrdinamento->ordinatoPerArrivo, numRighe);
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
        case r_errore:
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
void ordinaData(corsa *pCorse[], int numRighe) {
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
}

//ho scelto di utilizzare un ciclo do-while in quanto la mininma esecuzione è una ed implemento l'algoritmo di ricerca binaria
void ordinaPerPartenzaDicotomica(corsa *pCorse[], int numRighe, char *partenza) {
    ordinaPartenza(pCorse, numRighe);//ordino per partenze per usare la ricerca dicotomica
    int i, j, flag = 0, xm;
    i = 0;
    j = numRighe - 1;
    fflush(stdin);
    fflush(stdout);
    printf("\n\nLe corse trovate sono:\n");
    do {
        xm = (i + j) / 2;
        if (strncasecmp(partenza, pCorse[xm]->partenza, 3) < 0) {
            j = xm - 1;//mi sposto a sinistra di xm
        } else if (strncasecmp(partenza, pCorse[xm]->partenza, 3) > 0) {
            i = xm + 1;//mi sposto a destra di
        }
            //stampo i valori se trovo la chiave su xm oppure sugli indici adiacenti ad xm
        else if (strncasecmp(partenza, pCorse[xm]->partenza, 3) == 0) {
            printf("%s %s %s %s %s %s %d\n", pCorse[xm]->codice_tratta, pCorse[xm]->partenza, pCorse[xm]->destinazione,
                   pCorse[xm]->data, pCorse[xm]->ora_partenza, pCorse[xm]->ora_arrivo, pCorse[xm]->ritardo);
            if (xm + 1 < numRighe && strncasecmp(partenza, pCorse[xm + 1]->partenza, 3) == 0)
                printf("%s %s %s %s %s %s %d\n", pCorse[xm + 1]->codice_tratta, pCorse[xm + 1]->partenza,
                       pCorse[xm + 1]->destinazione, pCorse[xm + 1]->data, pCorse[xm + 1]->ora_partenza,
                       pCorse[xm + 1]->ora_arrivo, pCorse[xm + 1]->ritardo);
            if (xm - 1 > 0 && strncasecmp(partenza, pCorse[xm - 1]->partenza, 3) == 0)
                printf("%s %s %s %s %s %s %d\n", pCorse[xm - 1]->codice_tratta, pCorse[xm - 1]->partenza,
                       pCorse[xm - 1]->destinazione, pCorse[xm - 1]->data, pCorse[xm - 1]->ora_partenza,
                       pCorse[xm - 1]->ora_arrivo, pCorse[xm - 1]->ritardo);
            flag = 1;//condizione di terminazione forzata perchè ho trovato la chiave
        }
    } while (!flag && i <= j);
}

void inizializzaPuntatoreTratte(pOrdinato *pOrdinamento, int numRighe, corsa vett_corse[]) {
    pOrdinamento->ordinatoPerCodice = (corsa **) malloc(numRighe * sizeof(corsa *));
    pOrdinamento->ordinatoPerData = (corsa **) malloc(numRighe * sizeof(corsa *));
    pOrdinamento->ordinatoPerPartenza = (corsa **) malloc(numRighe * sizeof(corsa *));
    pOrdinamento->ordinatoPerArrivo = (corsa **) malloc(numRighe * sizeof(corsa *));
    if (pOrdinamento->ordinatoPerArrivo && pOrdinamento->ordinatoPerPartenza &&
        pOrdinamento->ordinatoPerData && pOrdinamento->ordinatoPerCodice) {
        for (int i = 0; i < numRighe; i++) {
            pOrdinamento->ordinatoPerCodice[i] = &vett_corse[i];
            pOrdinamento->ordinatoPerData[i] = &vett_corse[i];
            pOrdinamento->ordinatoPerPartenza[i] = &vett_corse[i];
            pOrdinamento->ordinatoPerArrivo[i] = &vett_corse[i];
        }
        //li ordino
        ordinaPartenza(pOrdinamento->ordinatoPerPartenza, numRighe);
        ordinaArrivo(pOrdinamento->ordinatoPerArrivo, numRighe);
        ordinaData(pOrdinamento->ordinatoPerData, numRighe);
        ordinaCodice(pOrdinamento->ordinatoPerCodice, numRighe);
    } else {
        printf("\nErrore nell'allocazione della memoria dinamica.");
        exit(-2);
    }


}

void freePuntatoreTratte(pOrdinato *pOrdinamento) {
    free(pOrdinamento->ordinatoPerArrivo);
    free(pOrdinamento->ordinatoPerPartenza);
    free(pOrdinamento->ordinatoPerCodice);
    free(pOrdinamento->ordinatoPerData);
}

void freeTratte(int numRighe, corsa *vett_corse) {
    for (int i = 0; i < numRighe; i++) {
        free(vett_corse[i].data);
        free(vett_corse[i].partenza);
        free(vett_corse[i].destinazione);
        free(vett_corse[i].ora_partenza);
        free(vett_corse[i].ora_arrivo);
    }
    free(vett_corse);
}

void stampaLog(int numRighe, corsa **vett_corse) {
    FILE *fpout;
    fpout = fopen("log.txt", "w");
    if (fpout == NULL) {
        printf("\nErrore. Impossibile aprire il file.");
        exit(-1);
    }
    fprintf(fpout, "Numero di righe scansionate: %d\n", numRighe);
    for (int i = 0; i < numRighe; i++) {
        //stampo i contenuti delle righe lette da file
        fprintf(fpout, "\nRiga numero %d:\n", i + 1);
        fprintf(fpout, "Codice tratta: %s\t", vett_corse[i]->codice_tratta);
        fprintf(fpout, "Partenza: %s\t", vett_corse[i]->partenza);
        fprintf(fpout, "Destinazione: %s\t", vett_corse[i]->destinazione);
        fprintf(fpout, "Data: %s\t", vett_corse[i]->data);
        fprintf(fpout, "Ora partenza: %s\t", vett_corse[i]->ora_partenza);
        fprintf(fpout, "Ora arrivo: %s\t", vett_corse[i]->ora_arrivo);
        fprintf(fpout, "Ritardo: %d\n\n", vett_corse[i]->ritardo);
    }
    fclose(fpout);

}