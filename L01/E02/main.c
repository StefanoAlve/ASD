#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXR 1000
#define MAXN 30

typedef enum{r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_fine, err}comando_e;

typedef struct{
    char codt[MAXN];
    char partenza[MAXN];
    char destinazione[MAXN];
    char data[MAXN];
    char oraP[MAXN];
    char oraA[MAXN];
    int ritardo;
}s_tratta;

comando_e StampaMenu();
int LeggiFile(FILE *fp, s_tratta tratte[MAXN]);
void SelezionaFunzione(comando_e comando, int n, int *pfine, s_tratta Tratte[]);
void StampaCorseDate(int n, s_tratta Tratte[]);
void StampaCorsePartenza(int n, s_tratta Tratte[]);
void StampaCorseCapolinea(int n, s_tratta Tratte[]);
void StampaCorseRitardo(int n, s_tratta Tratte[]);
void StampaRitardoTot(int n, s_tratta Tratte[]);

int main(){
    FILE *fin = fopen("corse.txt", "r");
    s_tratta V_Tratte[MAXR];
    comando_e cmd;
    int N_Tratte = 0, fine = 0, *p = &fine;

    if (fin == NULL) {printf("Errore apertura file\n"); return 1;}
    N_Tratte = LeggiFile(fin, V_Tratte);
    fclose(fin);
    cmd = StampaMenu();
    while (!(*p)){
        SelezionaFunzione(cmd, N_Tratte, p, V_Tratte);
        cmd = StampaMenu();
    }

    return 0;
}

int LeggiFile(FILE *fp, s_tratta tratte[MAXN]){
    int n = 0;

    fscanf(fp, "%d", &n);

    for (int i = 0; i < n; i++){
        fscanf(fp, "%s %s %s %s %s %s %d", tratte[i].codt, tratte[i].partenza, tratte[i].destinazione, tratte[i].data, tratte[i].oraP, tratte[i].oraA, &tratte[i].ritardo);
    }

    return n;
}

comando_e StampaMenu(){
    char str[MAXN];

    // stampa menu comandi
    printf("\nMENU COMANDI\n");
    printf("Date: corse in un intervallo di date\n");
    printf("Partenza: corse partite da una fermata\n");
    printf("Capolinea: corse terminate in una fermata\n");
    printf("Ritardo: corse terminate in ritardo in un intervallo di date\n");
    printf("RitardoTot: ritardo complessivo di una determinata tratta\n");
    printf("Fine: per terminare il programma\n\n");
    printf("Inserire il comando da eseguire (Scrivere la parola come compare sul menu): ");
    scanf("%s", str);

    if (strcasecmp("Date", str) == 0) return 0;
    if (strcasecmp("Partenza", str) == 0) return 1;
    if (strcasecmp("Capolinea", str) == 0) return 2;
    if (strcasecmp("Ritardo", str) == 0) return 3;
    if (strcasecmp("RitardoTot", str) == 0) return 4;
    if (strcasecmp("Fine", str) == 0) return 5;
    return 6;

}

void SelezionaFunzione(comando_e comando, int n, int *pfine, s_tratta Tratte[]){
    switch (comando) {
        case r_date:
            StampaCorseDate(n, Tratte);
        case r_partenza:
            StampaCorsePartenza(n, Tratte);
        case r_capolinea:
            StampaCorseCapolinea(n, Tratte);
        case r_ritardo:
            StampaCorseRitardo(n, Tratte);
        case r_ritardo_tot:
            StampaRitardoTot(n, Tratte);
        case r_fine:
            *pfine = 1;
        case err:
            printf("Comando non valido\n");
    }
}