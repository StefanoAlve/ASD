#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXN 30

typedef enum{newFile, stampa, DateOrd, CodOrd, PartOrd, DestOrd, search, r_fine, err}comando_e;

typedef struct{
    char codt[MAXN];
    char partenza[MAXN];
    char destinazione[MAXN];
    char data[MAXN];
    char oraP[MAXN];
    char oraA[MAXN];
    int ritardo;
}s_tratta;

typedef struct{
    s_tratta **DataOrd;
    s_tratta **CodOrd;
    s_tratta **PartOrd;
    s_tratta **DestOrd;
}s_Sort;

int LeggiFile(char nf[MAXN], s_tratta **tratte);
void InitializeOrdinamenti(int *n, s_tratta *Tratte, s_Sort *p_ord);
void InitOrd(int *n, s_tratta *Tratte, s_tratta ***TrattaOrd);
void SortDate(int *n, s_tratta **p_Tratte);
void SortCod(int *n, s_tratta **p_Tratte);
void SortPart(int *n, s_tratta **p_Tratte);
void SortDest(int *n, s_tratta **p_Tratte);
comando_e StampaMenu();
void SelezionaFunzione(comando_e comando, int *n, int *pfine, s_tratta *Tratte, s_Sort *p_ord);
void StampaCorse(int *n, s_tratta *Tratte);
void StampaOrd(int *n, s_tratta **p_Tratte);
void RicercaTratta(int *n, s_Sort *p_ord);
void linearSearch(int *n, s_tratta **p_Tratte, char str[MAXN]);
void binarySearch(int *n, s_tratta **p_Tratte, char str[MAXN]);
void LiberaMem(s_Sort *p_ord, s_tratta *Tratte);

int main(){
    s_tratta *V_Tratte;
    s_Sort Ordinamenti;
    s_Sort *p_Ordinamenti = &Ordinamenti;
    comando_e cmd;
    int N_Tratte = 0, *pn = &N_Tratte, fine = 0, *p = &fine;
    char nomefile[MAXN] = "corse.txt";

    N_Tratte = LeggiFile(nomefile, &V_Tratte); //lettura file e riempimento vettore
    InitializeOrdinamenti(&N_Tratte, V_Tratte, p_Ordinamenti);
    //finchè non si è selezionato il comando fine il menu continuerà ad apparire
    while (!(*p)){
        cmd = StampaMenu(); //stampa menu e acquisizione comando
        SelezionaFunzione(cmd, &N_Tratte, p, V_Tratte, p_Ordinamenti); //chiamata alla funzione corrispondente al comando
    }

    return 0;
}

//Apre e legge il file, alloca il vettore delle struct
int LeggiFile(char nf[MAXN], s_tratta **tratte){
    FILE *fp = fopen(nf, "r");
    if (fp == NULL) exit(1);
    int n = 0;
    s_tratta *vt; //vettore tratte
    fscanf(fp, "%d", &n);
    vt = malloc(n*sizeof *vt);
    if (vt == NULL) exit(1);
    for (int i = 0; i < n; i++){
        fscanf(fp, "%s %s %s %s %s %s %d", vt[i].codt, vt[i].partenza, vt[i].destinazione, vt[i].data, vt[i].oraP, vt[i].oraA, &vt[i].ritardo);
    }
    fclose(fp);
    *tratte = vt;
    return n;
}

//Inizializza la struct dei vettori di puntatori, poi chiama gli ordinamenti
void InitializeOrdinamenti(int *n, s_tratta *Tratte, s_Sort *p_ord) {
    InitOrd(n, Tratte, &(p_ord->DataOrd));
    InitOrd(n, Tratte, &(p_ord ->CodOrd));
    InitOrd(n, Tratte, &(p_ord->PartOrd));
    InitOrd(n, Tratte, &(p_ord->DestOrd));
    SortDate(n, p_ord->DataOrd);
    SortCod(n, p_ord->CodOrd);
    SortPart(n, p_ord->PartOrd);
    SortDest(n, p_ord->DestOrd);
}

//Alloca il vettore di puntatori e li aggancia al vettore di struct Tratte
void InitOrd(int *n, s_tratta *Tratte, s_tratta ***TrattaOrd){
    s_tratta **vpt; //vettore puntatori tratta
    vpt = malloc(*n*sizeof (s_tratta *));
    if (vpt == NULL) exit(1);
    for (int i = 0; i < *n; i++){
        vpt[i] = &Tratte[i];
    }
    *TrattaOrd = vpt;
}

//ordinamento tramite insertion sort rispetto alla data e ora
void SortDate(int *n, s_tratta **p_Tratte){
    for (int i = 1; i < *n; i++){
        s_tratta *x = p_Tratte[i];
        int k = i-1;
        while(k >= 0 && (strcmp(x->data, p_Tratte[k]->data) < 0 || (strcmp(x->data, p_Tratte[k]->data) == 0 && strcmp(x->oraP, p_Tratte[k]->oraP) < 0))){
            p_Tratte[k+1] = p_Tratte[k];
            k--;
        }
        p_Tratte[k+1] = x;
    }
}

//..... rispetto al codice
void SortCod(int *n, s_tratta **p_Tratte){
    for (int i = 1; i < *n; i++){
        s_tratta *x = p_Tratte[i];
        int k = i-1;
        while(k >= 0 && strcmp(x->codt, p_Tratte[k]->codt) < 0){
            p_Tratte[k+1] = p_Tratte[k];
            k--;
        }
        p_Tratte[k+1] = x;
    }
}

//..... Rispetto alla stazione di partenza
void SortPart(int *n, s_tratta **p_Tratte){
    for (int i = 1; i < *n; i++){
        s_tratta *x = p_Tratte[i];
        int k = i-1;
        while(k >= 0 && strcmp(x->partenza, p_Tratte[k]->partenza) < 0){
            p_Tratte[k+1] = p_Tratte[k];
            k--;
        }
        p_Tratte[k+1] = x;
    }
}

//..... Rispetto alla stazione di destinazione
void SortDest(int *n, s_tratta **p_Tratte){
    for (int i = 1; i < *n; i++){
        s_tratta *x = p_Tratte[i];
        int k = i-1;
        while(k >= 0 && strcmp(x->destinazione, p_Tratte[k]->destinazione) < 0){
            p_Tratte[k+1] = p_Tratte[k];
            k--;
        }
        p_Tratte[k+1] = x;
    }
}

//stampa del menu e acquisizione del comando
comando_e StampaMenu(){
    char str[MAXN];

    // stampa menu comandi
    printf("\nMENU COMANDI\n");
    printf("NewFile: acquisizione dati da file\n");
    printf("Stampa: stampa contenuto file log\n");
    printf("DateOrd: ordinamento corse per data e ora\n");
    printf("CodOrd: ordinamento corse per codice tratta\n");
    printf("PartOrd: ordinamento corse per fermata di partenza\n");
    printf("DestOrd: ordinamento corse per fermata di destinazione\n");
    printf("Ricerca: ricerca tratta per stazione di partenza\n");
    printf("Fine: per terminare il programma\n\n");
    printf("Inserire il comando da eseguire (Scrivere la parola come compare sul menu): \n");
    scanf("%s", str);

    if (strcasecmp("newfile", str) == 0) return 0;
    if (strcasecmp("stampa", str) == 0) return 1;
    if (strcasecmp("dateord", str) == 0) return 2;
    if (strcasecmp("codord", str) == 0) return 3;
    if (strcasecmp("partord", str) == 0) return 4;
    if (strcasecmp("destord", str) == 0) return 5;
    if (strcasecmp("ricerca", str) == 0) return 6;
    if (strcasecmp("fine", str) == 0) return 7;
    return 8;

}

//seleziona la funzione a seconda del comando
void SelezionaFunzione(comando_e comando, int *n, int *pfine, s_tratta *Tratte, s_Sort *p_ord){
    char nomef[MAXN];
    switch (comando) {
        case newFile:
            LiberaMem(p_ord, Tratte);
            printf("Nome file sorgente:\n");
            scanf("%s", nomef);
            *n = LeggiFile(nomef, &Tratte);
            InitializeOrdinamenti(n, Tratte, p_ord);
            break;
        case stampa:
            StampaCorse(n, Tratte);
            break;
        case DateOrd:
            StampaOrd(n, p_ord->DataOrd);
            break;
        case CodOrd:
            StampaOrd(n, p_ord->CodOrd);
            break;
        case PartOrd:
            StampaOrd(n, p_ord->PartOrd);
            break;
        case DestOrd:
            StampaOrd(n, p_ord->DestOrd);
            break;
        case search:
            RicercaTratta(n, p_ord);
            break;
        case r_fine:
            LiberaMem(p_ord, Tratte);
            *pfine = 1;
            break;
        case err:
            printf("Comando non valido\n");
            break;
    }
}

//stampa del contenuto del file a video o su un nuovo file
void StampaCorse(int *n, s_tratta *Tratte){
    FILE *fp = NULL;
    int scelta;
    char nomefile[MAXN];
    printf("Stampare a video (0) o su file (1)?\n");
    scanf("%d", &scelta);
    if (scelta){
        printf("Inserire nome file:\n");
        scanf("%s", nomefile);
        fp = fopen(nomefile, "w");
        for (int i = 0; i < *n; i++){
            fprintf(fp, "%s %s %s %s %s %s %d\n", Tratte[i].codt, Tratte[i].partenza, Tratte[i].destinazione, Tratte[i].data, Tratte[i].oraP, Tratte[i].oraA, Tratte[i].ritardo);
        }
        fclose(fp);
    } else {
        for (int i = 0; i < *n; i++){
            printf("%s %s %s %s %s %s %d\n", Tratte[i].codt, Tratte[i].partenza, Tratte[i].destinazione, Tratte[i].data, Tratte[i].oraP, Tratte[i].oraA, Tratte[i].ritardo);
        }
    }
}

//stampa il vettore di puntatori ordinato
void StampaOrd(int *n, s_tratta **p_Tratte){
    for (int i = 0; i < *n; i++){
        printf("%s %s %s %s %s %s %d\n", p_Tratte[i]->codt, p_Tratte[i]->partenza, p_Tratte[i]->destinazione, p_Tratte[i]->data, p_Tratte[i]->oraP, p_Tratte[i]->oraA, p_Tratte[i]->ritardo);
    }
}


//funzione che chiama la ricerca lineare o dicotomica a seconda di come specificato
void RicercaTratta(int *n, s_Sort *p_ord){
    int scelta;
    char partenza[MAXN];
    printf("Inserire la stazione di partenza per la ricerca (in minuscolo):\n");
    scanf("%s", partenza);
    printf("Ricerca dicotomica (0) o lineare (1):\n");
    scanf("%d", &scelta);
    if (scelta){
        linearSearch(n, p_ord->PartOrd, partenza);
    } else {
        binarySearch(n, p_ord->PartOrd, partenza);
    }
}

//ricerca lineare delle tratte con partenza uguale a str: si mette a minuscolo
//la fermata presente in Tratte[i].partenza per usare str
void linearSearch(int *n, s_tratta **p_Tratte, char str[MAXN]){
    char min[MAXN];
    int j;
    for (int i = 0; i < *n; i++){

        for (j = 0; j < strlen(p_Tratte[i]->partenza); j++){
            min[j] = tolower(p_Tratte[i]->partenza[j]);
        }
        min[j] = '\0';

        if (strstr(min, str) != NULL)
            printf("%s %s %s %s %s %s %d\n", p_Tratte[i]->codt, p_Tratte[i]->partenza, p_Tratte[i]->destinazione, p_Tratte[i]->data, p_Tratte[i]->oraP, p_Tratte[i]->oraA, p_Tratte[i]->ritardo);
    }
}

//ricerca dicotomica ......
void binarySearch(int *n, s_tratta **p_Tratte, char str[MAXN]){
    int l = 0, r = *n-1, find = 0;
    while(l <= r && !find){
        int m = (l+r)/2;
        if (strncasecmp(str, p_Tratte[m]->partenza, strlen(str)) < 0) r = m-1;
        else if (strncasecmp(str, p_Tratte[m]->partenza, strlen(str)) > 0) l = m+1;
        else if (strncasecmp(str, p_Tratte[m]->partenza, strlen(str)) == 0) {
            printf("%s %s %s %s %s %s %d\n", p_Tratte[m]->codt, p_Tratte[m]->partenza, p_Tratte[m]->destinazione, p_Tratte[m]->data, p_Tratte[m]->oraP, p_Tratte[m]->oraA, p_Tratte[m]->ritardo);
            find = 1;
        }
    }
}

//Libera tutte le strutture dati dinamiche
void LiberaMem(s_Sort *p_ord, s_tratta *Tratte){
    free(p_ord->PartOrd);
    free(p_ord->DestOrd);
    free(p_ord->DataOrd);
    free(p_ord->CodOrd);
    free(Tratte);
}