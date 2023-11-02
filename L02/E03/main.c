#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXL 30
//Variabili globali
typedef enum {
    r_date,
    r_partenza,
    r_capolinea,
    r_ritardo,
    r_ritardo_tot,
    r_ordina_data,
    r_ordina_codice,
    r_ordina_partenza,
    r_ordina_arrivo,
    r_ricerca_partenza_dico,
    r_nuovo_file,
    r_stampa,
    r_fine,
    r_errore
} comando_e;
typedef struct { //Struct contenente i dati relativi a ogni tratta
    char *codice_tratta;
    char *partenza;
    char *destinazione;
    char *data;
    char *ora_partenza;
    char *ora_arrivo;
    int ritardo;
} s_corsa;

typedef struct { //Struct contenente puntatori ai vettori di tratte ordinate per effettuare gli ordinamenti una singola volta e mantenerli in memoria
    s_corsa **ordinateData;
    s_corsa **ordinateCodice;
    s_corsa **ordinatePartenza;
    s_corsa **ordinateArrivo;
} s_puntaOrdinamento;

//Funzioni
comando_e leggiComando(void);

int leggiFile(s_corsa **corse);

void inizializzaSPOrdinamenti(s_puntaOrdinamento *puntaOrdinamenti, int nr, s_corsa corse[]);

void selezionaDati(int *pnr, comando_e comando, s_corsa corse[], s_puntaOrdinamento *puntaOrdinamenti, int *pfine);

void elencaCorseDate(s_corsa corse[], char datai[], char dataf[], int nr);

void elencaCorsePartenza(s_corsa corse[], char partenza[], int nr);

void elencaCorseCapolinea(s_corsa corse[], char capolinea[], int nr);

void elencaCorseRitardo(s_corsa corse[], char datai[], char dataf[], int nr);

void elencaRitardoCompl(s_corsa corse[], char codiceTratta[], int nr);

void ordinaPerData(s_corsa *pCorse[], int nr);

void ordinaPerCodice(s_corsa *pCorse[], int nr);

void ordinaPerPartenza(s_corsa *pCorse[], int nr);

void ordinaPerArrivo(s_corsa *pCorse[], int nr);

void stampaTratta(s_corsa *pCorse[], int nr);

void ricercaPerPartenzaDico(s_corsa *pCorse[], int nr, char partenza[]);

void deallocaPuntOrdinamenti(s_puntaOrdinamento *puntatoreOrdinamenti);

void deallocaTratte(s_corsa *corse, int nRighe);

void stampaCont(s_corsa *corse, int nRighe);

int main(void) {
    //Inizializzazione variabili
    comando_e comando;
    int nr, fine = 0;
    s_corsa *tratte;
    s_puntaOrdinamento ordinamenti;
    //Apertura file
    nr = leggiFile(&tratte);
    inizializzaSPOrdinamenti(&ordinamenti, nr, tratte);
    while (!fine && nr != -1) {
        //Lettura Comando
        comando = leggiComando();
        //Corpo programma
        selezionaDati(&nr, comando, tratte, &ordinamenti, &fine);
    }
    //Deallocazione
    deallocaPuntOrdinamenti(&ordinamenti);
    deallocaTratte(tratte, nr);
    return 0;
}

comando_e leggiComando(void) {
    //Inizializzazione variabili
    char comando[MAXL];
    comando_e comandoE;
    //Corpo funzione
    printf("\nScegli un comando\n");
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
    printf("inserisci un comando:");
    scanf(" %s", comando);
    if (strcmp("date", comando) == 0) {
        comandoE = 0;
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
    } else if (strcmp("ordina_arrivo", comando) == 0) {
        comandoE = 8;
    } else if (strcmp("ricerca_partenza_dico", comando) == 0) {
        comandoE = 9;
    } else if (strcmp("nuovo_file", comando) == 0) {
        comandoE = 10;
    } else if (strcmp("stampa", comando) == 0) {
        comandoE = 11;
    } else if (strcmp("fine", comando) == 0) {
        comandoE = 12;
    } else {
        printf("\nComando non riconosciuto! Riprova\n");
        comandoE = 13;
    }
    return comandoE;
}

int leggiFile(s_corsa **pcorse) {
    //Inizializzazione variabili
    FILE *fp;
    int i, nr = -1;
    char nomeFile[MAXL], tmp[MAXL];
    s_corsa *corse; //Utilizzo variabile ausiliaria per rendere più leggibili le allocazioni dinamiche
    //Apertura file
    printf("Inserisci il nome del file:");
    scanf("%s", nomeFile);
    fp = fopen(nomeFile, "r");
    if (fp != NULL) {

        fscanf(fp, "%d", &nr);
        corse = (s_corsa *) malloc(nr * sizeof(s_corsa));
        if (corse == NULL) {
            printf("Errore nell'assegnazione della memoria\n");
            exit(1);
        }
        //Corpo programma
        for (i = 0; i < nr; i++) {
            //Alloco le stringhe dinamicamente utilizzando strdup, la funzione riconosce il \0 nel vettore di char statico tmp, alloca il giusto spazio di memoria per contenere la stringa, copia la stringa in quello spazio e ne restituisce il puntatore
            fscanf(fp, "%s", tmp);
            corse[i].codice_tratta = (char *) malloc(strlen(tmp) * sizeof(char) + sizeof(char));
            strcpy(corse[i].codice_tratta, tmp);
            fscanf(fp, "%s", tmp);
            corse[i].partenza = (char *) malloc(strlen(tmp) * sizeof(char) + sizeof(char));
            strcpy(corse[i].partenza, tmp);
            fscanf(fp, "%s", tmp);
            corse[i].destinazione = (char *) malloc(strlen(tmp) * sizeof(char) + sizeof(char));
            strcpy(corse[i].destinazione, tmp);
            fscanf(fp, "%s", tmp);
            corse[i].data = (char *) malloc(strlen(tmp) * sizeof(char) + sizeof(char));
            strcpy(corse[i].data, tmp);
            fscanf(fp, "%s", tmp);
            corse[i].ora_partenza = (char *) malloc(strlen(tmp) * sizeof(char) + sizeof(char));
            strcpy(corse[i].ora_partenza, tmp);
            fscanf(fp, "%s", tmp);
            corse[i].ora_arrivo = (char *) malloc(strlen(tmp) * sizeof(char) + sizeof(char));
            strcpy(corse[i].ora_arrivo, tmp);
            fscanf(fp, "%d", &corse[i].ritardo);
        }
        stampaCont(corse, nr);
        *pcorse = corse;
    } else {
        printf("Errore nell'apertura del file!\n");
        exit(1);
    }
    fclose(fp);
    return nr;
}

void inizializzaSPOrdinamenti(s_puntaOrdinamento *puntaOrdinamenti, int nr, s_corsa corse[]) {
    // Alloca memoria per gli array all'interno di puntaOrdinamenti
    puntaOrdinamenti->ordinateData = (s_corsa **) malloc(nr * sizeof(s_corsa *));
    puntaOrdinamenti->ordinateArrivo = (s_corsa **) malloc(nr * sizeof(s_corsa *));
    puntaOrdinamenti->ordinateCodice = (s_corsa **) malloc(nr * sizeof(s_corsa *));
    puntaOrdinamenti->ordinatePartenza = (s_corsa **) malloc(nr * sizeof(s_corsa *));

    if (puntaOrdinamenti->ordinateData && puntaOrdinamenti->ordinateArrivo && puntaOrdinamenti->ordinateCodice &&
        puntaOrdinamenti->ordinatePartenza) {
        for (int i = 0; i < nr; i++) {
            puntaOrdinamenti->ordinateData[i] = &corse[i];
            puntaOrdinamenti->ordinateArrivo[i] = &corse[i];
            puntaOrdinamenti->ordinateCodice[i] = &corse[i];
            puntaOrdinamenti->ordinatePartenza[i] = &corse[i];
        }
        //Inizializzo tutti gli ordinamenti
        ordinaPerData(puntaOrdinamenti->ordinateData, nr);
        ordinaPerPartenza(puntaOrdinamenti->ordinatePartenza, nr);
        ordinaPerArrivo(puntaOrdinamenti->ordinateArrivo, nr);
        ordinaPerCodice(puntaOrdinamenti->ordinateCodice, nr);
    } else {
        printf("Errore nell'allocazione della memoria\n");
        exit(1);
    }
}


void selezionaDati(int *pnr, comando_e comando, s_corsa corse[], s_puntaOrdinamento *puntaOrdinamenti, int *pfine) {
    //Inizializzazione variabili
    char partenza[MAXL], capolinea[MAXL], codiceTratta[MAXL], datai[MAXL], dataf[MAXL], partenza1[MAXL];
    int nr = *pnr;
    s_corsa *pTratte[nr];
    for (int i = 0; i < nr; i++) {
        pTratte[i] = &corse[i];
    }
    switch (comando) {
        case r_date:
            printf("\nInserisci la data da cui iniziare la ricerca nel formato aaaa/mm/gg: ");
            scanf("%s", datai);
            printf("\nInserisci la data in cui terminare la ricerca nel formato aaaa/mm/gg: ");
            scanf("%s", dataf);
            elencaCorseDate(corse, datai, dataf, nr);
            break;
        case r_partenza:
            printf("\nInserire nome fermata di partenza: ");
            scanf("%s", partenza);
            elencaCorsePartenza(corse, partenza, nr);
            break;
        case r_capolinea:
            printf("\nInserire nome capolinea: ");
            scanf("%s", capolinea);
            elencaCorseCapolinea(corse, capolinea, nr);
            break;
        case r_ritardo:
            printf("\nInserisci la data da cui iniziare la ricerca nel formato aaaa/mm/gg: ");
            scanf("%s", datai);
            printf("\nInserisci la data in cui terminare la ricerca nel formato aaaa/mm/gg: ");
            scanf("%s", dataf);
            elencaCorseRitardo(corse, datai, dataf, nr);
            break;
        case r_ritardo_tot:
            printf("\nInserire codice di tratta: ");
            scanf("%s", codiceTratta);
            elencaRitardoCompl(corse, codiceTratta, nr);
            break;
        case r_ordina_data:
            printf("Le corse ordinate per data risultano:\n");
            stampaTratta(puntaOrdinamenti->ordinateData, nr);
            break;
        case r_ordina_codice:
            printf("Le corse ordinate per codice risultano:\n");
            stampaTratta(puntaOrdinamenti->ordinateCodice, nr);
            break;
        case r_ordina_partenza:
            printf("Le corse ordinate per partenza risultano:\n");
            stampaTratta(puntaOrdinamenti->ordinatePartenza, nr);
            break;
        case r_ordina_arrivo:
            printf("Le corse ordinate per destinazione risultano:\n");
            stampaTratta(puntaOrdinamenti->ordinateArrivo, nr);
            break;
        case r_ricerca_partenza_dico:
            printf("Inserisci partenza da ricercare: ");
            scanf("%s", partenza1);
            ricercaPerPartenzaDico(pTratte, nr, partenza1);
            break;
        case r_nuovo_file:

            deallocaPuntOrdinamenti(puntaOrdinamenti);
            deallocaTratte(corse, nr);
            nr = leggiFile(&corse);
            *pnr = nr;
            inizializzaSPOrdinamenti(puntaOrdinamenti, nr, corse);
            break;
        case r_stampa:
            stampaCont(corse, nr);
            break;
        case r_fine:
            *pfine = 1;
            printf("Programma terminato senza errori.\n");
            break;
        case r_errore:
            break;
    }
}


void elencaRitardoCompl(s_corsa corse[], char codiceTratta[], int nr) {
    int ritardo_tot = 0, flag = 0;
    for (int i = 0; i < nr; i++) {
        if (strcasecmp(corse[i].codice_tratta, codiceTratta) == 0) {
            ritardo_tot += corse[i].ritardo;
            flag = 1;
        }
    }
    if (!flag) {
        printf("\nNon sono presenti corse aventi tale codice di tratta.\n");
    } else {
        printf("\nIl ritardo complessivo delle corse con codice di tratta %s vale: %d minuti\n", codiceTratta,
               ritardo_tot);
    }
}

void elencaCorseCapolinea(s_corsa corse[], char capolinea[], int nr) {
    int flag = 0;
    printf("\nLe corse che hanno come capolinea %s sono:\n", capolinea);
    for (int i = 0; i < nr; i++) {
        if (strncasecmp(corse[i].destinazione, capolinea, strlen(capolinea)) == 0) {
            printf("%s - %s del %s partito alle ore %s\n", corse[i].partenza, corse[i].destinazione, corse[i].data,
                   corse[i].ora_partenza);
            flag = 1;
        }
    }
    if (!flag) {
        printf("\nNon sono presenti corse aventi tale capolinea.\n");
    }

}

void elencaCorsePartenza(s_corsa corse[], char partenza[], int nr) {
    int flag = 0;
    printf("\nLe corse che sono partite da %s sono:\n", partenza);
    for (int i = 0; i < nr; i++) {
        if (strncasecmp(corse[i].partenza, partenza, strlen(partenza)) == 0) {
            printf("%s - %s del %s partito alle ore %s\n", corse[i].partenza, corse[i].destinazione, corse[i].data,
                   corse[i].ora_partenza);
            flag = 1;
        }
    }
    if (!flag) {
        printf("\nNon sono presenti corse aventi tale fermata di partenza.\n");
    }
}

void elencaCorseDate(s_corsa tratte[], char datai[], char dataf[], int nr) {
    int flag = 0;
    printf("\nLe tratte che sono partite tra il %s e il %s sono:\n", datai, dataf);
    for (int i = 0; i < nr; i++) {
        if (strcmp(tratte[i].data, datai) >= 0 && strcmp(tratte[i].data, dataf) <= 0) {
            printf("%s - %s del %s partito alle ore %s\n", tratte[i].partenza, tratte[i].destinazione, tratte[i].data,
                   tratte[i].ora_partenza);
            flag = 1;
        }
    }
    if (!flag) {
        printf("\nNon sono presenti corse nell'intervallo richiesto.\n");
    }
}

void elencaCorseRitardo(s_corsa corse[], char datai[], char dataf[], int nr) {
    int flag = 0;
    printf("\nLe corse partite in ritardo tra il %s e il %s sono:\n", datai, dataf);
    for (int i = 0; i < nr; i++) {
        if (strcmp(corse[i].data, datai) >= 0 && strcmp(corse[i].data, dataf) <= 0) {
            if (corse[i].ritardo > 0) {
                printf("%s - %s del %s partito alle ore %s con un ritardo di %d\n", corse[i].partenza,
                       corse[i].destinazione, corse[i].data, corse[i].ora_partenza, corse[i].ritardo);
                flag = 1;
            }
        }
    }
    if (!flag) {
        printf("\nNon sono presenti corse nell'intervallo richiesto.\n");
    }
}

void ordinaPerData(s_corsa *pCorse[], int nr) {
    //Insertion sort
    int i, j, swap;
    s_corsa *key;
    for (i = 1; i < nr; i++) {
        key = pCorse[i];
        j = i - 1;
        swap = 1;
        while (j >= 0 && swap) {
            if (strcmp(key->data, pCorse[j]->data) < 0) {
                pCorse[j + 1] = pCorse[j];
            } else if (strcmp(key->data, pCorse[j]->data) == 0 &&
                       strcmp(key->ora_partenza, pCorse[j]->ora_partenza) < 0) {
                pCorse[j + 1] = pCorse[j];
            } else if (strcmp(key->data, pCorse[j]->data) == 0 &&
                       strcmp(key->ora_partenza, pCorse[j]->ora_partenza) == 0 &&
                       strcmp(key->ora_arrivo, pCorse[j]->ora_arrivo) < 0) {
                pCorse[j + 1] = pCorse[j];
            } else {
                swap = 0;
            }
            if (swap) {
                j--;
            }
        }
        pCorse[j + 1] = key;
    }
}

void ordinaPerPartenza(s_corsa *pCorse[], int nr) {
    //Insertion sort
    int i, j;
    s_corsa *key;

    for (i = 1; i < nr; i++) {
        key = pCorse[i];
        j = i - 1;
        while (j >= 0 && strcmp(key->partenza, pCorse[j]->partenza) < 0) {
            pCorse[j + 1] = pCorse[j];
            j--;
        }
        pCorse[j + 1] = key;
    }
}

void ordinaPerArrivo(s_corsa *pCorse[], int nr) {
    //Insertion sort
    int i, j;
    s_corsa *key;

    for (i = 1; i < nr; i++) {
        key = pCorse[i];
        j = i - 1;
        while (j >= 0 && strcmp(key->destinazione, pCorse[j]->destinazione) < 0) {
            pCorse[j + 1] = pCorse[j];
            j--;
        }
        pCorse[j + 1] = key;
    }
}

void ordinaPerCodice(s_corsa *pCorse[], int nr) {
    //Insertion sort
    int i, j;
    s_corsa *key;

    for (i = 1; i < nr; i++) {
        key = pCorse[i];
        j = i - 1;
        while (j >= 0 && strcmp(key->codice_tratta, pCorse[j]->codice_tratta) < 0) {
            pCorse[j + 1] = pCorse[j];
            j--;
        }
        pCorse[j + 1] = key;
    }
}

void ricercaPerPartenzaDico(s_corsa *pCorse[], int nr, char partenza[]) {
    //Ricerca dicotomica basata sul confronto delle partenze
    ordinaPerPartenza(pCorse, nr);
    int l, r, cont = 0, pm, flag = 0;
    l = 0;
    r = nr - 1;
    printf("Le corse trovate sono:\n");
    while (l <= r && !cont) {
        pm = (l + r) / 2;
        if (strncasecmp(partenza, pCorse[pm]->partenza, strlen(partenza)) <
            0) {
            r = pm - 1;
        } else if (strncasecmp(partenza, pCorse[pm]->partenza, strlen(partenza)) >
                   0) {
            l = pm + 1;
        } else if (strncasecmp(partenza, pCorse[pm]->partenza, strlen(partenza)) == 0) {
            printf("%s %s %s %s %s %s %d\n", pCorse[pm]->codice_tratta, pCorse[pm]->partenza,
                   pCorse[pm]->destinazione, pCorse[pm]->data, pCorse[pm]->ora_partenza, pCorse[pm]->ora_arrivo,
                   pCorse[pm]->ritardo);
            flag = 1;
            //Controllo i vicini dato
            if (pm + 1 < nr && strncasecmp(partenza, pCorse[pm + 1]->partenza, strlen(partenza)) == 0)
                printf("%s %s %s %s %s %s %d\n", pCorse[pm + 1]->codice_tratta, pCorse[pm + 1]->partenza,
                       pCorse[pm + 1]->destinazione, pCorse[pm + 1]->data, pCorse[pm + 1]->ora_partenza,
                       pCorse[pm + 1]->ora_arrivo, pCorse[pm + 1]->ritardo);
            if (pm - 1 >= 0 && strncasecmp(partenza, pCorse[pm - 1]->partenza, strlen(partenza)) == 0)
                printf("%s %s %s %s %s %s %d\n", pCorse[pm - 1]->codice_tratta, pCorse[pm - 1]->partenza,
                       pCorse[pm - 1]->destinazione, pCorse[pm - 1]->data, pCorse[pm - 1]->ora_partenza,
                       pCorse[pm - 1]->ora_arrivo, pCorse[pm - 1]->ritardo);
            cont = 1;
        }
    }
    if (!flag) {
        printf("\nNon sono presenti tratte aventi tale fermata di partenza.\n");
    }
}

void stampaTratta(s_corsa *pCorse[], int nr) {
    for (int i = 0; i < nr; i++) {
        printf("%s %s %s %s %s %s %d\n", pCorse[i]->codice_tratta, pCorse[i]->partenza, pCorse[i]->destinazione,
               pCorse[i]->data, pCorse[i]->ora_partenza, pCorse[i]->ora_arrivo, pCorse[i]->ritardo);
    }
    printf("\n");
}

void stampaCont(s_corsa *corse, int nRighe) {
    printf("Il file contiene: \n");
    for (int i = 0; i < nRighe; i++) {
        printf("%s %s %s ", corse[i].codice_tratta, corse[i].partenza, corse[i].destinazione);
        printf("%s ", corse[i].data);
        printf("%s ", corse[i].ora_partenza);
        printf("%s ", corse[i].ora_arrivo);
        printf("%d\n", corse[i].ritardo);
    }
}

void deallocaPuntOrdinamenti(s_puntaOrdinamento *puntatoreOrdinamenti) {
    if (puntatoreOrdinamenti != NULL) {
        free(puntatoreOrdinamenti->ordinateData);
        free(puntatoreOrdinamenti->ordinateArrivo);
        free(puntatoreOrdinamenti->ordinateCodice);
        free(puntatoreOrdinamenti->ordinatePartenza);
    }
}

void deallocaTratte(s_corsa *tratte, int nRighe) {
    for (int i = 0; i < nRighe; i++) {
        free(tratte[i].data);
        free(tratte[i].partenza);
        free(tratte[i].ora_partenza);
        free(tratte[i].destinazione);
        free(tratte[i].codice_tratta);
        free(tratte[i].ora_arrivo);
    }
    free(tratte);
}