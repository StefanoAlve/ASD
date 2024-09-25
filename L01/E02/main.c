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
    printf("Date: corse in un intervallo di date\n");
    printf("Partenza: corse partite da una fermata\n");
    printf("Capolinea: corse terminate in una fermata\n");
    printf("Ritardo: corse terminate in ritardo in un intervallo di date\n");
    printf("RitardoTot: ritardo complessivo di una determinata tratta\n");
    printf("Fine: per terminare il programma\n\n");
    printf("Inserire il comando da eseguire (Scrivere la parola come compare sul menu): \n");
    scanf("%s", str);

    if (strcasecmp("Date", str) == 0) return 0;
    if (strcasecmp("Partenza", str) == 0) return 1;
    if (strcasecmp("Capolinea", str) == 0) return 2;
    if (strcasecmp("Ritardo", str) == 0) return 3;
    if (strcasecmp("RitardoTot", str) == 0) return 4;
    if (strcasecmp("Fine", str) == 0) return 5;
    return 6;

}

//A seconda del comando seleziona la funzione richiesta o stampa un messaggio di
//errore se il comando inserito non è tra quelli presenti nel menu
void SelezionaFunzione(comando_e comando, int n, int *pfine, s_tratta Tratte[]){
    switch (comando) {
        case r_date:
            StampaCorseDate(n, Tratte);
            break;
        case r_partenza:
            StampaCorsePartenza(n, Tratte);
            break;
        case r_capolinea:
            StampaCorseCapolinea(n, Tratte);
            break;
        case r_ritardo:
            StampaCorseRitardo(n, Tratte);
            break;
        case r_ritardo_tot:
            StampaRitardoTot(n, Tratte);
            break;
        case r_fine:
            *pfine = 1;
            break;
        case err:
            printf("Comando non valido\n");
            break;
    }
}

//Stampa le corse all'interno delle date inserite
void StampaCorseDate(int n, s_tratta Tratte[]){
    char dataI[MAXN], dataF[MAXN];
    printf("Inserire le date dell'intervallo (aaaa/mm/gg) :\n");
    scanf("%s %s", dataI, dataF);

    for (int i = 0; i < n; i++){
        if (strcmp(Tratte[i].data, dataI) >= 0 && strcmp(Tratte[i].data, dataF) <= 0)
            printf("%s %s %s %s %s %s %d\n", Tratte[i].codt, Tratte[i].partenza, Tratte[i].destinazione, Tratte[i].data, Tratte[i].oraP, Tratte[i].oraA, Tratte[i].ritardo);
    }
}

//stampa corse con fermata di partenza uguale a quella inserita
void StampaCorsePartenza(int n, s_tratta Tratte[]){
    char Partenza[MAXN];
    printf("Inserire la fermata di partenza:\n");
    scanf("%s", Partenza);

    for (int i = 0; i < n; i++){
        if (strcasecmp(Partenza, Tratte[i].partenza) == 0)
            printf("%s %s %s %s %s %s %d\n", Tratte[i].codt, Tratte[i].partenza, Tratte[i].destinazione, Tratte[i].data, Tratte[i].oraP, Tratte[i].oraA, Tratte[i].ritardo);
    }
}

//stampa corse con fermata di destinazione uguale a quella inserita
void StampaCorseCapolinea(int n, s_tratta Tratte[]){
    char Capolinea[MAXN];
    printf("Inserire la fermata di destinazione:\n");
    scanf("%s", Capolinea);

    for (int i = 0; i < n; i++){
        if (strcasecmp(Capolinea, Tratte[i].destinazione) == 0)
            printf("%s %s %s %s %s %s %d\n", Tratte[i].codt, Tratte[i].partenza, Tratte[i].destinazione, Tratte[i].data, Tratte[i].oraP, Tratte[i].oraA, Tratte[i].ritardo);
    }
}

//stampa corse in ritardo in data fra le due inserite
void StampaCorseRitardo(int n, s_tratta Tratte[]){
    char dataI[MAXN], dataF[MAXN];
    printf("Inserire le date dell'intervallo (aaaa/mm/gg) :\n");
    scanf("%s %s", dataI, dataF);

    for (int i = 0; i < n; i++){
        if (strcmp(Tratte[i].data, dataI) >= 0 && strcmp(Tratte[i].data, dataF) <= 0 && Tratte[i].ritardo > 0)
            printf("%s %s %s %s %s %s %d\n", Tratte[i].codt, Tratte[i].partenza, Tratte[i].destinazione, Tratte[i].data, Tratte[i].oraP, Tratte[i].oraA, Tratte[i].ritardo);
    }
}

//Calcola il ritardo tot accumulato dalla tratta con codice uguale a quello inserito
void StampaRitardoTot(int n, s_tratta Tratte[]){
    int ritardoTot = 0, indiceTratta;
    char codt[MAXN];
    printf("Inserire il codice della tratta:\n");
    scanf("%s", codt);

    for (int i = 0; i < n; i++){
        if (strcasecmp(codt, Tratte[i].codt) == 0) {ritardoTot += Tratte[i].ritardo; indiceTratta = i;}
    }
    printf("%s %s %s Ritardo Totale: %d min\n", Tratte[indiceTratta].codt, Tratte[indiceTratta].partenza, Tratte[indiceTratta].destinazione, ritardoTot);
}