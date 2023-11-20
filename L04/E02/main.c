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
    int SetVoid; //Usato da ItemSetVoid: impostato a 1 se una funzione di ricerca deve tornare un Item vuoto
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
void StampaListaF(link h);
int ConfrontaDate(char data1[11], char data2[11]);
int DateBetween(char ref[11], char data1[11], char data2[11]);
Item CodSearchList(link h);
Item ExtrList_Cod(link *head);
Item CercaPrimo(link *head, char data1[11], char data2[11]);
Item ItemSetVoid();
link newNode(Item anagrafica, link next);
link SortListIns(link h, Item anagrafica);
link SortListInsF(link h);



int main() {
    int fine = 0, *p_fine = &fine;
    comando_e comando;
    link head = NULL, x, t; //Inizializzazione lista vuota

    while(!fine){
        comando = LeggiComando();
        if (comando != invalid){
            EseguiComando(&head,comando,p_fine);
        } else {
            printf("Comando non riconosciuto, Riprovare\n");
        }
    }

    //Deallocazione lista
    x = head;
    while (x!=NULL){
        t = x->next;
        free(x);
        x = t;
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
    scanf("%s",comando);
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
    link list_start = *head;
    Item anagrafica;
    char data1[11], data2[11];
    int presente = 1;

    switch (comando) {
        case InsertList1:
            printf("\nInserire i dati in questo ordine\n<codice> <nome> <cognome> <data_di_nascita> <via> <citta'> <cap>\n");
            LeggiAnag(&anagrafica);
            list_start = SortListIns(list_start,anagrafica);
            printf("\nInserimento eseguito correttamente\n");
            break;
        case InsertList2:
            list_start = SortListInsF(list_start);
            printf("\nInserimento eseguito correttamente\n");
            break;
        case cod_search:
            anagrafica = CodSearchList(list_start);
            if (anagrafica.SetVoid == 1){
                printf("Nessun elemento trovato\n");
            } else printf("%s %s %s %s %s %s %d\n", anagrafica.codice, anagrafica.nome, anagrafica.cognome, anagrafica.bornDate, anagrafica.via, anagrafica.citta, anagrafica.cap);
            break;
        case ExtrListCod:
            anagrafica = ExtrList_Cod(&list_start);
            if (anagrafica.SetVoid == 1){
                printf("Nessun elemento trovato\n");
            } else {
                printf("%s %s %s %s %s %s %d\n", anagrafica.codice, anagrafica.nome, anagrafica.cognome, anagrafica.bornDate, anagrafica.via, anagrafica.citta, anagrafica.cap);
                printf("Anagrafica eliminata correttamente\n");
            }
            break;
        case ExtrListDates:
            printf("Inserire le date nel formato gg/mm/aaaa separate da uno spazio:\n");
            scanf("%s %s", data1, data2);

            anagrafica = CercaPrimo(&list_start,data1,data2);
            if (anagrafica.SetVoid == 1) {
                printf("Nessun elemento trovato\n");
                presente = 0;
            } else {
                printf("%s %s %s %s %s %s %d\n", anagrafica.codice, anagrafica.nome, anagrafica.cognome, anagrafica.bornDate, anagrafica.via, anagrafica.citta, anagrafica.cap);
                printf("Anagrafica eliminata correttamente\n");
            }
            //Se presente = 1, allora ci potrebbero essere altre anagrafiche da eliminare
            while (presente){
                anagrafica = CercaPrimo(&list_start,data1,data2);
                if (anagrafica.SetVoid == 1)
                    presente = 0;
                else {
                    printf("%s %s %s %s %s %s %d\n", anagrafica.codice, anagrafica.nome, anagrafica.cognome, anagrafica.bornDate, anagrafica.via, anagrafica.citta, anagrafica.cap);
                    printf("Anagrafica eliminata correttamente\n");
                }
            }
            break;
        case ListPrintFile:
            if (list_start == NULL) printf("La lista e' vuota, necessario riempirla\n");
            else {
                StampaListaF(list_start);
                printf("\nStampa avvenuta con successo\n");
            }
            break;
        case end:
            *p_fine = 1;
            break;
    }
    *head = list_start;
}

void StampaListaF(link h){
    FILE *fp;
    link x;
    char NomeFile[MAXN];

    printf("Inserire il nome del file:\n");
    scanf("%s", NomeFile);

    fp = fopen(NomeFile,"w");
    if (fp != NULL){
        //Stampa della lista su file
        for (x=h; x!=NULL; x=x->next){
            fprintf(fp,"%s %s %s %s %s %s %d\n",
                    x->anag.codice,x->anag.nome,x->anag.cognome,x->anag.bornDate,x->anag.via,x->anag.citta,x->anag.cap);
        }
    } else printf("\nImpossibile aprire il file\n");
    fclose(fp);
}

//Funzione che ritorna un Item vuoto: imposta ad 1 il campo SetVoid della struct e
//la funzione chiamante controllerà attraverso questo campo se in una ricerca non è stata trovata alcuna corrispondenza
Item ItemSetVoid(){
    Item Void;
    Void.SetVoid = 1;
    return Void;
}

Item CodSearchList(link h){
    link x;
    char codice[6];

    printf("Inserire il codice da cercare:");
    scanf("%s", codice);

    for (x=h; x!=NULL && strcmp(codice,x->anag.codice) != 0; x=x->next);
    if (x!=NULL){
        x->anag.SetVoid = 0;
        return x->anag;
    } else {
        return ItemSetVoid();
    }
}

Item ExtrList_Cod(link *head){
    Item anagrafica = ItemSetVoid();
    link *xp, t;
    char codice[6];

    printf("Inserire il codice da cercare:");
    scanf("%s", codice);

    for (xp=head; (*xp)!=NULL; xp = &((*xp)->next)){
        if (strcasecmp(codice,(*xp)->anag.codice) == 0){
            t = *xp;
            *xp = (*xp)->next;
            anagrafica = t->anag;
            free(t);
            break;
        }
    }
    return anagrafica;
}

//Funzione che cerca la prima anagrafica con data compresa fra le due date
//Cancella il nodo e restituisce la anagrafica corrispondente
Item CercaPrimo(link *head, char data1[11], char data2[11]){
    Item anagrafica = ItemSetVoid();
    link *xp, t;

    for(xp=head; (*xp)!=NULL && DateBetween((*xp)->anag.bornDate,data1,data2) == 0; xp = &((*xp)->next));
    if ((*xp)!=NULL){
        t = *xp;
        *xp = (*xp)->next;
        anagrafica = t->anag;
        free(t);
    }
    return anagrafica;
}

//Funzione che torna vero se la prima data viene prima della seconda
int ConfrontaDate(char data1[11], char data2[11]){
    int i;
    char gg1[3], mm1[3], anno1[5], gg2[3], mm2[3], anno2[5];

    for (i=0; i<2; i++){
        gg1[i] = data1[i];
        gg2[i] = data2[i];
    }
    for (i=3; i<5; i++){
        mm1[i-3] = data1[i];
        mm2[i-3] = data2[i];
    }
    for (i=6; i<10; i++){
        anno1[i-6] = data1[i];
        anno2[i-6] = data2[i];
    }

    if (strcmp(anno1,anno2) < 0) return 1;
    else if (strcmp(anno1,anno2) > 0) return 0;
    else {
        if (strcmp(mm1,mm2) < 0) return 1;
        else if (strcmp(mm1,mm2) > 0) return 0;
        else {
            if (strcmp(gg1,gg2) > 0) return 0;
            else return 1;
        }
    }
}

//Funzione che torna vero = 1 se la data di riferimento è compresa tra le 2 date
int DateBetween(char ref[11], char data1[11], char data2[11]){
    int vero = 0;

    if (ConfrontaDate(data1,ref) && ConfrontaDate(ref,data2)) vero = 1;
    return vero;
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

    if (h == NULL || ConfrontaDate(anagrafica.bornDate,h->anag.bornDate))
        return newNode(anagrafica,h); //Inserimento in testa
    for (x=h->next, p=h; x!=NULL && ConfrontaDate(x->anag.bornDate,anagrafica.bornDate); p=x, x=x->next);
    p->next = newNode(anagrafica,x);

    return h;
}

link SortListInsF(link h){
    FILE *fp;
    char NomeFile[MAXN];
    Item anagrafica;

    printf("\nInserire il nome del file:\n");
    scanf("%s", NomeFile);

    fp = fopen(NomeFile,"r");
    if (fp != NULL){
        while (fscanf(fp,"%s %s %s %s %s %s %d",
                      anagrafica.codice, anagrafica.nome, anagrafica.cognome, anagrafica.bornDate, anagrafica.via, anagrafica.citta, &anagrafica.cap) == 7){
            h = SortListIns(h,anagrafica);
        }
    } else printf("\nImpossibile aprire il file\n");
    fclose(fp);

    return h;
}


