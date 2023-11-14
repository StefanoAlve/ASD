#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Definizione variabili globali
#define MAXN 51

typedef struct{
    char codice[6];
    char nome[MAXN];
    char cognome[MAXN];
    char bornDate[11];
    char via[MAXN];
    char citta[MAXN];
    int cap;
} Item;

typedef struct node node_t, *link;
struct node{
    Item anag;
    link next;
};

typedef enum{
    InsertList1, InsertList2, cod_search, ExtrListCod, ExtrListDates, ListPrintFile, end, invalid
} comando_e;

//Funzioni
comando_e LeggiComando();
void EseguiComando(link *head, comando_e comando, int *p_fine);

int main() {
    int fine = 0, *p_fine = &fine;
    comando_e comando;
    link head = NULL; //Inizializzazione lista vuota

    while(!fine){
        comando = LeggiComando();
        if (comando != invalid){
            EseguiComando(&head,comando,p_fine);
        } else {
            printf("Comando non riconosciuto, Riprovare\n");
        }
    }
    return 0;
}

comando_e LeggiComando(){
    char comando[MAXN];
    comando_e Comando;

    //Stampa menu comandi
    printf("\nMENU COMANDI\n");
    printf("InsertList1: acquisizione ed inserimento ordinato di un nuovo elemento in lista (da tastiera)\n");
    printf("InsertList2: acquisizione ed inserimento ordinato di nuovi elementi in lista (da file)\n");
    printf("Cod_search: ricerca, per codice, di un elemento\n");
    printf("ExtrListCod: cancellazione (con estrazione del dato) di un elemento dalla lista, previa ricerca per codice\n");
    printf("ExtrListDates: cancellazione (con estrazione del dato) di tutti gli elementi con date comprese tra 2 date lette da tastiera\n");
    printf("ListPrintFile: stampa della lista su file\n");
    printf("Fine: per terminare il programma\n\n");
    printf("Inserire il comando da eseguire:");
    scanf("\t%s",comando);

    if (strcasecmp("InsertList1",comando) == 0){
        Comando = 0;
    } else if (strcasecmp("InsertList2",comando) == 0){
        Comando = 1;
    } else if (strcasecmp("Cod_search",comando) == 0){
        Comando = 2;
    } else if (strcasecmp("ExtrListCod",comando) == 0){
        Comando = 3;
    } else if (strcasecmp("ExtrListDates",comando) == 0){
        Comando = 4;
    } else if (strcasecmp("ListPrintFile",comando) == 0) {
        Comando = 5;
    } else if (strcasecmp("Fine",comando) == 0) {
        Comando = 6;
    } else Comando = 7;

    return Comando;

}

void EseguiComando(link *head, comando_e comando, int *p_fine){
    link list_start = NULL;
    switch (comando) {
        case InsertList1:
            break;
        case InsertList2:
            break;
        case cod_search:
            break;
        case ExtrListCod:
            break;
        case ExtrListDates:
            break;
        case ListPrintFile:
            break;
        case end:
            *p_fine = 1;
            break;
    }
    *head = list_start;
}
