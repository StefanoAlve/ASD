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
void LeggiAnag(Item *anagrafica);
void EseguiComando(link *head, comando_e comando, int *p_fine);
int ConfrontaDate(char data1[11], char data2[11]);
link newNode(Item anagrafica, link next);
link SortListIns(link h, Item anagrafica);

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

    //Deallocazione lista

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
    printf("\n");

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



// Legge da tastiera i dati della anagrafica
void LeggiAnag(Item *anagrafica){
    Item anag;
    scanf("%s %s %s %s %s %s %d",
          anag.codice, anag.nome, anag.cognome, anag.bornDate, anag.via, anag.citta, &anag.cap);
    *anagrafica = anag;
}

void EseguiComando(link *head, comando_e comando, int *p_fine){
    link list_start = NULL;
    Item anagrafica;

    switch (comando) {
        case InsertList1:
            printf("Inserire i dati in questo ordine\n<codice> <nome> <cognome> <data_di_nascita> <via> <citta'> <cap>\n");
            LeggiAnag(&anagrafica);
            list_start = SortListIns(list_start,anagrafica);
            printf("Inserimento eseguito correttamente\n");
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

//Funzione che torna vero se la prima data viene prima della seconda
int ConfrontaDate(char data1[11], char data2[11]){
    int i;
    char gg1[3], mm1[3], anno1[5], gg2[3], mm2[3], anno2[5];

    for (i=0; i<2; i++){
        gg1[i] = data1[i];
        gg2[i] = data2[i];
    }
    for (i=2; i<4; i++){
        mm1[i-2] = data1[i];
        mm2[i-2] = data2[i];
    }
    for (i=4; i<11; i++){
        anno1[i-4] = data1[i];
        anno1[i-4] = data1[i];
    }

    if (strcmp(anno1,anno2) < 0) return 1;
    if (strcmp(mm1,mm2) < 0) return 1;
    if (strcmp(gg1,gg2) < 0) return 1;
    return 0;
}

link newNode(Item anagrafica, link next){
    link x = malloc(sizeof(*x));
    if (x==NULL) {printf("\nErrore allocazione memoria\n"); exit(1);}
    x->anag = anagrafica;
    x->next = next;
    return x;
}

link SortListIns(link h, Item anagrafica){
    link x, p;
    char chiave[11];

    strcpy(chiave,anagrafica.bornDate);
    if (h == NULL || ConfrontaDate(chiave,h->anag.bornDate))
        return newNode(anagrafica,h); //Inserimento in testa
    for (x=h->next, p=h; x!=NULL && ConfrontaDate(x->anag.bornDate,chiave); p=x, x=x->next);
    p->next = newNode(anagrafica,x);

    return h;
}
