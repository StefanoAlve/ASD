// E2
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXL 30
#define MAXNR 1000
#define name_file "corse.txt"
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
    r_fine,
    r_error
}comando_e;
///FUNCTIONS
comando_e leggiComando(void);
void leggi_file(char *fileName, int* NR, s_tratte tratte[]); // LEGGE E STAMPA i contenuti iniziali del log
void selezionaDati(s_tratte tratte[], int NR, comando_e comando);
void check_capolineaORpartenza(s_tratte tratte[], int NR, comando_e comando, char* nome); // In questo esercizio è usata solo per la destinazione
void stampa_tratta(s_tratte tratte[], int indice); // stampa la singola tratta
void check_date_e_ritardo(s_tratte tratte[], int NR, char* date1, char* date2, comando_e cmd);
void check_ritardoXcodice(s_tratte tratte[], int NR, char* codice);
int controlla_n_caratteri(s_tratte tratte[], char* nome, int num_tratta, int desidered_equals, comando_e comando); // Sarebbe la ricerca lineare (la utilizzo nelle destinazioni)
void ricerca_dicotomica(s_tratte tratte[], int NR, char* nome, int desidered_equals); // la ricerca dicotomica, usata nella ricerca delle partenze
void stampa_tratta_pointer(s_tratte* tratte[], int NR); // stampa tutte le tratte presenti in un vettore di puntatori a struct
void sortForDate(s_tratte tratte[], int NR);
void sortForCode(s_tratte tratte[], int NR);
void sortForStation(s_tratte tratte[], int NR, comando_e comando);


int main(void)
{
    int NR = 0, error = 0;
    s_tratte tratte[MAXNR];
    comando_e cmd = 0;
    // LETTURA FILE
    printf("Il file %s contiene i seguenti dati:\n\n", name_file);
    leggi_file(name_file, &NR, tratte);
    while (cmd != r_fine && error == 0)
    {
        cmd = leggiComando();
        if (cmd != r_error)
            selezionaDati(tratte, NR, cmd);
        else
            error = 1;
    }
    return error;
}


void leggi_file(char *fileName, int* NR, s_tratte tratte[])
{
    FILE* fp_in;
    int i = 0;
    fp_in = fopen(fileName, "r");
    *NR = 0;
    if(fp_in != NULL)
        fscanf(fp_in, "%d", NR);
    if (*NR != 0){
        while(fscanf(fp_in, "%s %s %s %s %s %s %d", tratte[i].codice_tratta, tratte[i].partenza, tratte[i].destinazione,
                     tratte[i].data, tratte[i].ora_partenza, tratte[i].ora_arrivo, &tratte[i].ritardo) == 7)
        {
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
    printf("\nInserire il comando (date, partenza, capolinea, ritardo, ritardo_tot, ordina, fine): ");
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
            cmd = 10;
    }
    else if(!strcasecmp(comando, "fine"))
        cmd = 9;
    else
        cmd = 10;
    if (cmd == 10)
        printf("\nNon ho compreso il tuo comando");
    return cmd;
}


void selezionaDati(s_tratte tratte[], int NR, comando_e comando)
{
    char nome_fermata[MAXL], date1[MAXL], date2[MAXL];
    switch(comando)
    {
        case r_date:
            printf("\nInserisci la prima e la seconda data nel formato aaaa/mm/gg aaaa/mm/gg: ");
            scanf("%s %s", date1, date2);
            check_date_e_ritardo(tratte, NR, date1, date2, comando);
            break;
        case r_partenza:
            printf("\nInserisci il nome della fermata di partenza da ricercare:");
            scanf("%s", nome_fermata);
            printf("\nEcco le fermate richieste:");
            ricerca_dicotomica(tratte, NR, nome_fermata, 4);
            break;
        case r_capolinea:
            printf("\nInserisci il nome della fermata capolinea da ricercare:");
            scanf("%s", nome_fermata);
            printf("\nEcco le fermate richieste:");
            check_capolineaORpartenza(tratte, NR, comando, nome_fermata);
            break;
        case r_ritardo:
            printf("\nInserisci la prima e la seconda data nel formato aaaa/mm/gg aaaa/mm/gg: ");
            scanf("%s %s", date1, date2);
            check_date_e_ritardo(tratte, NR, date1, date2, comando);
            break;
        case r_ritardo_tot:
            printf("\nInserisci il codice della tratta di cui vuoi verificare il ritardo complessivo:");
            scanf("%s", date1);
            check_ritardoXcodice(tratte, NR, date1);
            break;
        case r_sortForDate:
            printf("\nEcco il contenuto del file ordinato per data:\n");
            sortForDate(tratte, NR);
            break;
        case r_sortForDepart:
            printf("\nEcco il contenuto del file ordinato per stazione di partenza:\n");
            sortForStation(tratte, NR, comando);
            break;
        case r_sortForDestination:
            printf("\nEcco il contenuto del file ordinato per stazione di arrivo:\n");
            sortForStation(tratte, NR, comando);
            break;
        case r_sortForCode:
            printf("\nEcco il contenuto del file ordinato per codice tratta:\n");
            sortForCode(tratte, NR);
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

void check_date_e_ritardo(s_tratte tratte[], int NR, char* date1, char* date2, comando_e cmd)
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
    printf("\n");
    while (i < NR)
    {
        if (!strcasecmp(codice, tratte[i].codice_tratta))
            ritardo_tot += tratte[i].ritardo;
        i++;
    }
    printf("\nLa tratta con codice %s ha riportato in totale un ritardo pari a %d minuti.", codice, ritardo_tot);
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


void sortForCode(s_tratte tratte[], int NR)
{
    s_tratte* pTratte[NR];
    s_tratte* tmp;
    int i,j;
    for(i = 0; i < NR; i++)
        pTratte[i] = &tratte[i];
    for (i = 1; i < NR; i++)
    {
        tmp = pTratte[i];
        j = i-1;
        while (j >= 0 && strcasecmp(tmp->codice_tratta, pTratte[j]->codice_tratta) < 0)
        {
            pTratte[j+1] = pTratte[j];
            j--;
        }
        pTratte[j+1] = tmp;
    }
    stampa_tratta_pointer(pTratte, NR);
}


void sortForStation(s_tratte tratte[], int NR, comando_e comando)
{
    s_tratte* pTratte[NR], *tmp;
    int i, j;
    for (i = 0; i < NR; i++)
        pTratte[i] = &tratte[i]; // copia in un vettore di puntatori
    for(i = 1; i < NR; i++)
    {
        tmp = pTratte[i];
        j = i-1;
        if (comando == r_sortForDestination)
            while (j >= 0 && strcasecmp(tmp->destinazione, pTratte[j]->destinazione) < 0)
            {
                pTratte[j+1] = pTratte[j];
                j--;
            }
        else if(comando == r_sortForDepart)
            while (j >= 0 && strcasecmp(tmp->partenza, pTratte[j]->partenza) < 0)
            {
                pTratte[j+1] = pTratte[j];
                j--;
            }
        pTratte[j+1] = tmp;
    }
    stampa_tratta_pointer(pTratte, NR);
}

void sortForDate(s_tratte tratte[], int NR)
{
    s_tratte* pTratte[NR], *tmp;
    int i,j, swap;
    for (i = 0; i < NR; i++)
        pTratte[i] = &tratte[i];
    for(i = 1; i < NR; i++)
    {
        tmp = pTratte[i];
        j = i-1;
        swap = 1;
        while (j >= 0 && swap)
        {
            if(strcmp(tmp->data, pTratte[j]->data) < 0)
                pTratte[j+1] = pTratte[j];
            else if(strcmp(tmp->data, pTratte[j]->data) == 0 && strcmp(tmp->ora_partenza, pTratte[j]->ora_partenza) < 0)
                pTratte[j+1] = pTratte[j];
            else if(!strcmp(tmp->data, pTratte[j]->data) && !strcmp(tmp->ora_partenza, pTratte[j]->ora_partenza) && strcmp(tmp->ora_arrivo, pTratte[j]->ora_arrivo) < 0)
                pTratte[j+1] = pTratte[j];
            else
                swap = 0;
            if (swap)
                j--;
        }
        pTratte[j+1] = tmp;
    }
    stampa_tratta_pointer(pTratte, NR);
}


void ricerca_dicotomica(s_tratte tratte[], int NR, char* nome, int desidered_equals)
{
    s_tratte* pTratte[NR], *tmp;
    int i, j, l = 0,r = NR - 1, cont = 0, pm;

    printf("\nEffettuero' la ricerca dicotomica sulle seguenti tratte ordinate per stazione di partenza:\n");
    // rieffettuo l'inserction sort perchè avrei dovuto passare alla funzione sortForCode il vettore di puntatori a struct per evitare di riordinare il vettore in questa funzione
    for (i = 0; i < NR; i++)
        pTratte[i] = &tratte[i];
    // sort for departure
    for (i = 1; i < NR; i++)
    {
        j = i-1;
        tmp = &tratte[i];
        while(j>=0 && strcasecmp(tmp->partenza, pTratte[j]->partenza) < 0)
        {
            pTratte[j+1] = pTratte[j];
            j--;
        }
        pTratte[j+1] = tmp;
    }
    while(l <= r && !cont)
    {
        pm = (l+r)/2; // nel caso di più occorrenze?
        if (strncasecmp(nome, pTratte[pm]->partenza, desidered_equals) < 0)
            r = pm - 1;
        else if (strncasecmp(nome, pTratte[pm]->partenza, desidered_equals) > 0)
            l = pm + 1;
        else if (strncasecmp(nome, pTratte[pm]->partenza, desidered_equals) == 0) {
            printf("--- %s %s %s %s %s %s %d\n", pTratte[pm]->codice_tratta, pTratte[pm]->partenza, pTratte[pm]->destinazione,
                   pTratte[pm]->data, pTratte[pm]->ora_partenza, pTratte[pm]->ora_arrivo, pTratte[pm]->ritardo);
            if (pm+1 < NR && strncasecmp(nome, pTratte[pm+1]->partenza, desidered_equals) == 0)
                printf("--- %s %s %s %s %s %s %d\n", pTratte[pm+1]->codice_tratta, pTratte[pm+1]->partenza, pTratte[pm+1]->destinazione, pTratte[pm+1]->data, pTratte[pm+1]->ora_partenza, pTratte[pm+1]->ora_arrivo, pTratte[pm+1]->ritardo);
            if (pm -1 > 0 && strncasecmp(nome, pTratte[pm-1]->partenza, desidered_equals) == 0)
                printf("--- %s %s %s %s %s %s %d\n", pTratte[pm-1]->codice_tratta, pTratte[pm-1]->partenza, pTratte[pm-1]->destinazione, pTratte[pm-1]->data, pTratte[pm-1]->ora_partenza, pTratte[pm-1]->ora_arrivo, pTratte[pm-1]->ritardo);
            cont = 1;
        }
    }
}