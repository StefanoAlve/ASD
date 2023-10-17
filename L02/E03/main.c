// E2
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXL 30

///STRUCT
typedef struct{
    char codice_tratta[MAXL];
    char partenza[MAXL];
    char destinazione[MAXL];
    char data[MAXL];
    char ora_partenza[MAXL];
    char ora_arrivo[MAXL];
    int ritardo;
}s_tratte;

typedef struct{
    s_tratte *originale;
    s_tratte* *date_sorted;
    s_tratte* *code_sorted;
    s_tratte* *departure_sorted;
    s_tratte* *arrival_sorted;
}s_mix_tratte;

///ENUM
typedef enum{
    r_date,
    r_partenza,
    r_capolinea,
    r_ritardo,
    r_ritardo_tot,
    r_sortForDate,
    r_sortForCode,
    r_sortForDepart,
    r_sortForDestination,
    r_read,
    r_fine,
    r_error
}comando_e;
///FUNCTIONS
comando_e leggiComando(void);
void leggi_file(char *fileName, int* NR, s_mix_tratte* mix_tratte); // LEGGE E STAMPA i contenuti iniziali del log
void selezionaDati(s_mix_tratte* mix_tratte, int* NR, comando_e comando); // Funzione che processa i comandi
void check_capolineaORpartenza(s_tratte tratte[], int NR, comando_e comando, char* nome); // In questo esercizio è usata solo per la destinazione
void stampa_tratta(s_tratte tratte[], int indice); // stampa la singola tratta
void check_date_e_ritardo(s_tratte tratte[], int NR, char* date1, char* date2, comando_e cmd);
void check_ritardoXcodice(s_tratte tratte[], int NR, char* codice);
int controlla_n_caratteri(s_tratte tratte[], char* nome, int num_tratta, int desidered_equals, comando_e comando); // Sarebbe la ricerca lineare (la utilizzo nelle destinazioni)
void ricerca_dicotomica(s_tratte* *departure_sorted, int NR, char* nome, int desidered_equals); // la ricerca dicotomica, usata nella ricerca delle partenze
void stampa_tratta_pointer(s_tratte* tratte[], int NR); // stampa tutte le tratte presenti in un vettore di puntatori a struct
void sortForDate(s_mix_tratte* mix_tratte,  int NR);
void sortForCode(s_mix_tratte* mix_tratte,  int NR);
void sortForStation(s_mix_tratte* mix_tratte, int NR);


int main(void)
{
    int NR = 0;
    s_mix_tratte mix_tratte;
    comando_e cmd = 9; // comando di lettura
    while (cmd != r_fine && cmd != r_error)
    {
        // LETTURA FILE
        selezionaDati(&mix_tratte, &NR, cmd);
        cmd = leggiComando();
    }
    return cmd;
}


void leggi_file(char *fileName, int* NR, s_mix_tratte* mix_tratte)
{
    FILE* fp_in;
    s_tratte *tratte;
    int i = 0;
    fp_in = fopen(fileName, "r");
    *NR = 0;
    if(fp_in != NULL)
        fscanf(fp_in, "%d", NR);
    tratte = (s_tratte *)malloc((*NR) * sizeof(s_tratte));
    mix_tratte->originale = (s_tratte *)malloc((*NR) * sizeof(s_tratte));
    mix_tratte->code_sorted = (s_tratte **)malloc((*NR) * sizeof(s_tratte *));
    mix_tratte->date_sorted = (s_tratte **)malloc((*NR) * sizeof(s_tratte *));
    mix_tratte->arrival_sorted = (s_tratte **)malloc((*NR) * sizeof(s_tratte *));
    mix_tratte->departure_sorted = (s_tratte **)malloc((*NR) * sizeof(s_tratte *));
    if (*NR != 0){
        while(fscanf(fp_in, "%s %s %s %s %s %s %d", tratte[i].codice_tratta, tratte[i].partenza, tratte[i].destinazione,
                     tratte[i].data, tratte[i].ora_partenza, tratte[i].ora_arrivo, &tratte[i].ritardo) == 7)
        {
            mix_tratte->originale[i] = tratte[i];
            mix_tratte->code_sorted[i] = &tratte[i];
            mix_tratte->date_sorted[i] = &tratte[i];
            mix_tratte->arrival_sorted[i] = &tratte[i];
            mix_tratte->departure_sorted[i] = &tratte[i];
            stampa_tratta(tratte, i);
            i++;
        }
    }
    fclose(fp_in);
}


comando_e leggiComando(void)
{
    char comando[MAXL];
    comando_e cmd;
    printf("\nInserire il comando (date, partenza, capolinea, ritardo, ritardo_tot, ordina, leggi_file, fine): ");
    scanf("%s", comando);
    if(!strcasecmp(comando, "date"))
        cmd = 0;
    else if(!strcasecmp(comando, "partenza"))
        cmd = 1;
    else if(!strcasecmp(comando, "capolinea"))
        cmd = 2;
    else if(!strcasecmp(comando, "ritardo"))
        cmd = 3;
    else if(!strcasecmp(comando, "ritardo_tot"))
        cmd = 4;
    else if(!strcasecmp(comando, "ordina"))
    {
        printf("\nInserisci il parametro sulla base del quale ordinare (data, codice, partenza, arrivo):");
        scanf("%s", comando);
        if(!strcasecmp(comando, "data"))
            cmd = 5;
        else if(!strcasecmp(comando, "codice"))
            cmd = 6;
        else if(!strcasecmp(comando, "partenza"))
            cmd = 7;
        else if(!strcasecmp(comando, "arrivo"))
            cmd = 8;
        else
            cmd = 11;
    }
    else if(!strcasecmp(comando, "leggi_file"))
        cmd = 9;
    else if(!strcasecmp(comando, "fine"))
        cmd = 10;
    else
        cmd = 11;
    if (cmd == 11)
        printf("\nNon ho compreso il tuo comando");
    return cmd;
}


void selezionaDati(s_mix_tratte* mix_tratte, int* NR, comando_e comando)
{
    char nome_fermata[MAXL], date1[MAXL], date2[MAXL];
    switch(comando)
    {
        case r_date:
            printf("\nInserisci la prima e la seconda data nel formato aaaa/mm/gg aaaa/mm/gg: ");
            scanf("%s %s", date1, date2);
            check_date_e_ritardo(mix_tratte->originale, *NR, date1, date2, comando);
            break;
        case r_partenza:
            printf("\nInserisci il nome della fermata di partenza da ricercare:");
            scanf("%s", nome_fermata);
            printf("\nEcco le fermate richieste:");
            ricerca_dicotomica(mix_tratte->departure_sorted, *NR, nome_fermata, 4);
            break;
        case r_capolinea:
            printf("\nInserisci il nome della fermata capolinea da ricercare:");
            scanf("%s", nome_fermata);
            printf("\nEcco le fermate richieste:");
            check_capolineaORpartenza(mix_tratte->originale, *NR, comando, nome_fermata);
            break;
        case r_ritardo:
            printf("\nInserisci la prima e la seconda data nel formato aaaa/mm/gg aaaa/mm/gg: ");
            scanf("%s %s", date1, date2);
            check_date_e_ritardo(mix_tratte->originale, *NR, date1, date2, comando);
            break;
        case r_ritardo_tot:
            printf("\nInserisci il codice della tratta di cui vuoi verificare il ritardo complessivo:");
            scanf("%s", date1);
            check_ritardoXcodice(mix_tratte->originale, *NR, date1);
            break;
        case r_sortForDate:
            printf("\nEcco il contenuto del file ordinato per data:\n");
            stampa_tratta_pointer(mix_tratte->date_sorted, *NR);
            break;
        case r_sortForDepart:
            printf("\nEcco il contenuto del file ordinato per stazione di partenza:\n");
            stampa_tratta_pointer(mix_tratte->departure_sorted, *NR);
            break;
        case r_sortForDestination:
            printf("\nEcco il contenuto del file ordinato per stazione di arrivo:\n");
            stampa_tratta_pointer(mix_tratte->arrival_sorted, *NR);
            break;
        case r_sortForCode:
            printf("\nEcco il contenuto del file ordinato per codice tratta:\n");
            stampa_tratta_pointer(mix_tratte->code_sorted, *NR);
            break;
        case r_read:
            printf("\nInserisci il nome del file:");
            scanf("%s", nome_fermata);
            printf("\nEcco il contenuto del file:\n");
            if (*NR != 0)
            {
                free(mix_tratte->originale);
                free(mix_tratte->code_sorted);
                free(mix_tratte->arrival_sorted);
                free(mix_tratte->departure_sorted);
                free(mix_tratte->date_sorted);
            }
            leggi_file(nome_fermata, NR, mix_tratte);
            sortForCode(mix_tratte, *NR);
            sortForStation(mix_tratte, *NR);
            sortForDate(mix_tratte, *NR);
            break;
        case r_fine:
            printf("\nProgramma terminato, arrivederci!");
        case r_error:
            break;
    }
}


void check_capolineaORpartenza(s_tratte tratte[], int NR, comando_e comando, char* nome)
{
    /// UPDATE: è necessario che, come indicato nell'esercizio 3.6 siano uguali i primi x caratteri, nel caso
    /// da me implementato, mi bastano i primi 4 caratteri. Questa funzione andava bene per la ricerca lineare dei lineare delle fermati di partenza e destinazione
    int i = 0;
    printf("\n");
    while (i < NR) {
        if (controlla_n_caratteri(tratte, nome, i, 4, comando)) // avrei potuto usare anche strncmp...
            stampa_tratta(tratte, i);
        i++;
    }
}


void stampa_tratta(s_tratte tratte[], int indice)
{
    printf("- %s %s %s %s %s %s %d\n", tratte[indice].codice_tratta, tratte[indice].partenza, tratte[indice].destinazione,
           tratte[indice].data, tratte[indice].ora_partenza, tratte[indice].ora_arrivo, tratte[indice].ritardo);
}


void stampa_tratta_pointer(s_tratte* tratte[], int NR)
{
    {
        int indice;
        printf("\n");
        for (indice = 0; indice < NR; indice++)
            printf("- %s %s %s %s %s %s %d\n", tratte[indice]->codice_tratta, tratte[indice]->partenza, tratte[indice]->destinazione,
                   tratte[indice]->data, tratte[indice]->ora_partenza, tratte[indice]->ora_arrivo, tratte[indice]->ritardo);
    }
}

void check_date_e_ritardo(s_tratte *tratte, int NR, char* date1, char* date2, comando_e cmd)
{
    int i = 0, ritardi = 0;
    printf("\n");
    while (i < NR)
    {
        if (strcmp(date1, tratte[i].data) < 0 && strcmp(date2, tratte[i].data) > 0) {
            if (cmd == r_date) {
                stampa_tratta(tratte, i);
            }
            else if (cmd == r_ritardo && tratte[i].ritardo > 0) {
                printf("La corsa sottostante presenta un ritardo pari a: %d minuti\n", tratte[i].ritardo);
                stampa_tratta(tratte, i);
                ritardi = 1;
            }
        }
        i++;
    }
    if (!ritardi && cmd == r_ritardo)
        printf("Non ho trovato alcun ritardo nelle date comprese tra %s e %s", date1, date2);
}


void check_ritardoXcodice(s_tratte tratte[], int NR, char* codice)
{
    int i = 0, ritardo_tot = 0;
    while (i < NR)
    {
        if (!strcasecmp(codice, tratte[i].codice_tratta))
            ritardo_tot += tratte[i].ritardo;
        i++;
    }
    printf("\nLa tratta con codice %s ha riportato in totale un ritardo pari a %d minuti.\n", codice, ritardo_tot);
}


int controlla_n_caratteri(s_tratte tratte[], char* nome, int num_tratta, int desidered_equals, comando_e comando)
{
    int i, equals = 0, flag = 1;
    for (i = 0; i < strlen(nome) && i < desidered_equals && flag;i++)
    {
        if (comando == r_partenza)
        {
            if(tolower(tratte[num_tratta].partenza[i]) == tolower(nome[i])) // confronto i primi 'desidered_equals' caratteri ma non appena
                // se ne trova uno diverso esco dal ciclo ritornando 0, cioè falso
                equals++;
            else
                flag = 0;
        }
        else if(comando == r_capolinea)
        {
            if(tolower(tratte[num_tratta].destinazione[i]) == tolower(nome[i]))
                equals++;
            else
                flag = 0;
        }
        if(i == (desidered_equals-1) && equals == desidered_equals)
            return 1;
    }
    return 0;
}


void sortForCode(s_mix_tratte* mix_tratte,  int NR)
{
    s_tratte* tmp;
    int i,j;
    for (i = 1; i < NR; i++)
    {
        tmp = mix_tratte->code_sorted[i];
        j = i-1;
        while (j >= 0 && strcasecmp(tmp->codice_tratta, mix_tratte->code_sorted[j]->codice_tratta) < 0)
        {
            mix_tratte->code_sorted[j+1] = mix_tratte->code_sorted[j];
            j--;
        }
        mix_tratte->code_sorted[j+1] = tmp;
    }
}


void sortForStation(s_mix_tratte* mix_tratte, int NR)
{
    s_tratte *tmp;
    int i, j;

    for(i = 1; i < NR; i++)
    {
        tmp = mix_tratte->departure_sorted[i];
        j = i-1;
        while (j >= 0 && strcasecmp(tmp->destinazione, mix_tratte->arrival_sorted[j]->destinazione) < 0)
        {
            mix_tratte->arrival_sorted[j+1] = mix_tratte->arrival_sorted[j];
            j--;
        }
        mix_tratte->arrival_sorted[j+1] = tmp;
        j = i-1;
        while (j >= 0 && strcasecmp(tmp->partenza, mix_tratte->departure_sorted[j]->partenza) < 0)
        {
            mix_tratte->departure_sorted[j+1] = mix_tratte->departure_sorted[j];
            j--;
        }
        mix_tratte->departure_sorted[j+1] = tmp;
    }
}


void sortForDate(s_mix_tratte* mix_tratte,  int NR)
{
    s_tratte *tmp;
    int i,j, swap;

    for(i = 1; i < NR; i++)
    {
        tmp = mix_tratte->date_sorted[i];
        j = i-1;
        swap = 1;
        while (j >= 0 && swap)
        {
            if(strcmp(tmp->data, mix_tratte->date_sorted[j]->data) < 0)
                mix_tratte->date_sorted[j+1] = mix_tratte->date_sorted[j];
            else if(strcmp(tmp->data, mix_tratte->date_sorted[j]->data) == 0 && strcmp(tmp->ora_partenza, mix_tratte->date_sorted[j]->ora_partenza) < 0)
                mix_tratte->date_sorted[j+1] = mix_tratte->date_sorted[j];
            else if(!strcmp(tmp->data, mix_tratte->date_sorted[j]->data) && !strcmp(tmp->ora_partenza, mix_tratte->date_sorted[j]->ora_partenza) && strcmp(tmp->ora_arrivo, mix_tratte->date_sorted[j]->ora_arrivo) < 0)
                mix_tratte->date_sorted[j+1] = mix_tratte->date_sorted[j];
            else
                swap = 0;
            if (swap)
                j--;
        }
        mix_tratte->date_sorted[j+1] = tmp;
    }
}


void ricerca_dicotomica(s_tratte* *departure_sorted, int NR, char* nome, int desidered_equals)
{
    int l = 0,r = NR - 1, cont = 0, pm;
    printf("\n");
    while(l <= r && !cont)
    {
        pm = (l+r)/2; // nel caso di più occorrenze?
        if (strncasecmp(nome, departure_sorted[pm]->partenza, desidered_equals) < 0)
            r = pm - 1;
        else if (strncasecmp(nome, departure_sorted[pm]->partenza, desidered_equals) > 0)
            l = pm + 1;
        else if (strncasecmp(nome, departure_sorted[pm]->partenza, desidered_equals) == 0) {
            printf("- %s %s %s %s %s %s %d\n", departure_sorted[pm]->codice_tratta, departure_sorted[pm]->partenza, departure_sorted[pm]->destinazione,
                   departure_sorted[pm]->data, departure_sorted[pm]->ora_partenza, departure_sorted[pm]->ora_arrivo, departure_sorted[pm]->ritardo);
            if (pm+1 < NR && strncasecmp(nome, departure_sorted[pm+1]->partenza, desidered_equals) == 0)
                printf("- %s %s %s %s %s %s %d\n", departure_sorted[pm+1]->codice_tratta, departure_sorted[pm+1]->partenza, departure_sorted[pm+1]->destinazione, departure_sorted[pm+1]->data, departure_sorted[pm+1]->ora_partenza, departure_sorted[pm+1]->ora_arrivo, departure_sorted[pm+1]->ritardo);
            if (pm -1 > 0 && strncasecmp(nome, departure_sorted[pm-1]->partenza, desidered_equals) == 0)
                printf("- %s %s %s %s %s %s %d\n", departure_sorted[pm-1]->codice_tratta, departure_sorted[pm-1]->partenza, departure_sorted[pm-1]->destinazione, departure_sorted[pm-1]->data, departure_sorted[pm-1]->ora_partenza, departure_sorted[pm-1]->ora_arrivo, departure_sorted[pm-1]->ritardo);
            cont = 1;
        }
    }
}