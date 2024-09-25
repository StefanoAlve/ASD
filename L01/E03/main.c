#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXR 1000
#define MAXN 30

typedef enum{stampa, DateOrd, CodOrd, PartOrd, DestOrd, search, r_fine, err}comando_e;

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

int main(){
    FILE *fin = fopen("corse.txt", "r");
    s_tratta V_Tratte[MAXR]; //vettore delle tratte
    comando_e cmd;
    int N_Tratte = 0, fine = 0, *p = &fine;

    if (fin == NULL) {printf("Errore apertura file\n"); return 1;}
    N_Tratte = LeggiFile(fin, V_Tratte); //lettura file e riempimento vettore
    fclose(fin);
    //finchè non si è selezionato il comando fine il menu continuerà ad apparire
    while (!(*p)){
        cmd = StampaMenu(); //stampa menu e acquisizione comando
        SelezionaFunzione(cmd, N_Tratte, p, V_Tratte); //chiamata alla funzione corrispondente al comando
    }

    return 0;
}

//Lettura file e riempimento vettore di struct
int LeggiFile(FILE *fp, s_tratta tratte[MAXN]){
    int n = 0;
    fscanf(fp, "%d", &n);
    for (int i = 0; i < n; i++){
        fscanf(fp, "%s %s %s %s %s %s %d", tratte[i].codt, tratte[i].partenza, tratte[i].destinazione, tratte[i].data, tratte[i].oraP, tratte[i].oraA, &tratte[i].ritardo);
    }
    return n;
}

//stampa del menu e acquisizione del comando
comando_e StampaMenu(){
    char str[MAXN];

    // stampa menu comandi
    printf("\nMENU COMANDI\n");
    printf("Stampa: stampa contenuto file log\n");
    printf("DateOrd: ordinamento corse per data e ora\n");
    printf("CodOrd: ordinamento corse per codice tratta\n");
    printf("PartOrd: ordinamento corse per fermata di partenza\n");
    printf("DestOrd: ordinamento corse per fermata di destinazione\n");
    printf("Ricerca: ricerca tratta per stazione di partenza\n");
    printf("Fine: per terminare il programma\n\n");
    printf("Inserire il comando da eseguire (Scrivere la parola come compare sul menu): \n");
    scanf("%s", str);

    if (strcasecmp("stampa", str) == 0) return 0;
    if (strcasecmp("dateord", str) == 0) return 1;
    if (strcasecmp("codord", str) == 0) return 2;
    if (strcasecmp("partord", str) == 0) return 3;
    if (strcasecmp("destord", str) == 0) return 4;
    if (strcasecmp("ricerca", str) == 0) return 5;
    if (strcasecmp("fine", str) == 0) return 6;
    return 7;

}

void SelezionaFunzione(comando_e comando, int n, int *pfine, s_tratta Tratte[]){
    switch (comando) {
        case stampa:
            StampaCorse(n, Tratte);
            break;
        case DateOrd:
            SortPrintDate(n, Tratte);
            break;
        case CodOrd:
            SortPrintCod(n, Tratte);
            break;
        case PartOrd:
            SortPrintPart(n, Tratte);
            break;
        case DestOrd:
            SortPrintDest(n, Tratte);
            break;
        case search:
            RicercaTratta(n, Tratte);
            break;
        case r_fine:
            *pfine = 1;
            break;
        case err:
            printf("Comando non valido\n");
            break;
    }
}
