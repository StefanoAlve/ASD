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
void InitializeOrdinamenti(int n, s_tratta Tratte[], s_Sort *p_ord);
void InitOrd(int n, s_tratta *Tratte, s_tratta ***TrattaOrd);

int main(){
    s_tratta *V_Tratte;
    s_Sort Ordinamenti;
    s_Sort *p_Ordinamenti = &Ordinamenti;
    comando_e cmd;
    int N_Tratte = 0, fine = 0, *p = &fine;
    char nomefile[MAXN] = "corse.txt";

    N_Tratte = LeggiFile(nomefile, &V_Tratte); //lettura file e riempimento vettore
    InitializeOrdinamenti(N_Tratte, V_Tratte, p_Ordinamenti);
    //finchè non si è selezionato il comando fine il menu continuerà ad apparire
    while (!(*p)){
        cmd = StampaMenu(); //stampa menu e acquisizione comando
        SelezionaFunzione(cmd, N_Tratte, p, V_Tratte, p_Ordinamenti); //chiamata alla funzione corrispondente al comando
    }

    return 0;
}

int LeggiFile(char nf[MAXN], s_tratta **tratte){
    FILE *fp = fopen(nf, "r");
    if (fp == NULL) exit(1);
    int n = 0;
    s_tratta *vt; //vettore tratte
    fscanf(fp, "%d", &n);
    vt = malloc(n*sizeof *vt);
    for (int i = 0; i < n; i++){
        fscanf(fp, "%s %s %s %s %s %s %d", vt[i].codt, vt[i].partenza, vt[i].destinazione, vt[i].data, vt[i].oraP, vt[i].oraA, &vt[i].ritardo);
    }
    fclose(fp);
    *tratte = vt;
    return n;
}

void InitializeOrdinamenti(int n, s_tratta *Tratte, s_Sort *p_ord) {
    InitOrd(n, Tratte, &(p_ord->DataOrd));
    InitOrd(n, Tratte, &(p_ord ->CodOrd));
    InitOrd(n, Tratte, &(p_ord->PartOrd));
    InitOrd(n, Tratte, &(p_ord->DestOrd));
    SortDate(n, p_ord->DataOrd);
    SortCod(n, p_ord->CodOrd);
    SortPart(n, p_ord->PartOrd);
    SortDest(n, p_ord->DestOrd);
}

void InitOrd(int n, s_tratta *Tratte, s_tratta ***TrattaOrd){
    s_tratta **vpt; //vettore puntatori tratta
    vpt = malloc(n*sizeof (s_tratta *));
    for (int i = 0; i < n; i++){
        vpt[i] = &Tratte[i];
    }
    *TrattaOrd = vpt;
}
