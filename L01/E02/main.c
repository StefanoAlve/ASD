// E2
#include <stdio.h>
#include <string.h>

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
    r_fine,
    r_error
}comando_e;
///FUNCTIONS
comando_e leggiComando(void);
void leggi_file(char *fileName, int* NR, s_tratte tratte[MAXNR]);
void selezionaDati(s_tratte tratte[MAXNR], int NR, comando_e comando);
void check_capolineaORpartenza(s_tratte tratte[MAXNR], int NR, comando_e comando, char* nome);
void stampa_tratta(s_tratte tratte[MAXNR], int indice);
void check_date_e_ritardo(s_tratte tratte[MAXNR], int NR, char* date1, char* date2, comando_e cmd);
void check_ritardoXcodice(s_tratte tratte[MAXNR], int NR, char* codice);

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


void leggi_file(char *fileName, int* NR, s_tratte tratte[MAXNR])
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
    printf("\nInserire il comando (date, partenza, capolinea, ritardo, ritardo_tot, fine): ");
    scanf("%s", comando);
    if(!strcmp(comando, "date"))
        cmd = 0;
    else if(!strcmp(comando, "partenza"))
        cmd = 1;
    else if(!strcmp(comando, "capolinea"))
        cmd = 2;
    else if(!strcmp(comando, "ritardo"))
        cmd = 3;
    else if(!strcmp(comando, "ritardo_tot"))
        cmd = 4;
    else if(!strcmp(comando, "fine"))
        cmd = 5;
    else{
        printf("\nNon ho compreso il tuo comando");
        cmd = 6;
    }
    return cmd;
}


void selezionaDati(s_tratte tratte[MAXNR], int NR, comando_e comando)
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
        case r_capolinea:
            if (comando == r_capolinea)
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
        case r_fine:
            printf("\nProgramma terminato, arrivederci!");
        case r_error:
            break;
    }
}


void check_capolineaORpartenza(s_tratte tratte[MAXNR], int NR, comando_e comando, char* nome)
{
    int i = 0;
    printf("\n");
    while (i < NR) {
        if (comando == r_partenza)
        {
            if (!strcmp(nome, tratte[i].partenza))
                stampa_tratta(tratte, i);
        }
        else if (comando == r_capolinea){
            if (!strcmp(nome, tratte[i].destinazione))
                stampa_tratta(tratte, i);
        }
        i++;
    }
}


void stampa_tratta(s_tratte tratte[MAXNR], int indice)
{
    printf("- %s %s %s %s %s %s %d\n", tratte[indice].codice_tratta, tratte[indice].partenza, tratte[indice].destinazione,
           tratte[indice].data, tratte[indice].ora_partenza, tratte[indice].ora_arrivo, tratte[indice].ritardo);
}


void check_date_e_ritardo(s_tratte tratte[MAXNR], int NR, char* date1, char* date2, comando_e cmd)
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


void check_ritardoXcodice(s_tratte tratte[MAXNR], int NR, char* codice)
{
    int i = 0, ritardo_tot = 0;
    printf("\n");
    while (i < NR)
    {
        if (!strcmp(codice, tratte[i].codice_tratta))
            ritardo_tot += tratte[i].ritardo;
        i++;
    }
    printf("\nLa tratta con codice %s ha riportato in totale un ritardo pari a %d minuti.", codice, ritardo_tot);
}
