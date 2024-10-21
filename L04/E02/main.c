#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXC1 50
#define MAXC2 6
#define MAXC3 11

//Item come struct di dati anagrafici
typedef struct{
    char* codice;
    char* nome;
    char* cognome;
    char* birth;
    char* via;
    char* citta;
    char* cap;
} Item;

//La chiave è anch'essa una stringa
typedef char *Key;

//puntatore a tipo struct node
typedef struct node *link;

//struttura nodo della lista
struct node{
    Item val;
    link next;
};

//Enum per la selezione a menu
typedef enum{KBInsert, FileInsert, CodSearch, ExtrCodSearch, ExtrBSearch, PrintFile, end, err} comando;

//Prototipi funzioni
void Dealloc(link h);
void ITEMshowF(Item d, FILE *fp);
void ListFilePrint(link h);
void StampaListaR(FILE *fp, link h);
Key KEYget1(Item d);
Key KEYget2(Item d);
int KEYeq(Key k1, Key k2);
int KEYgeq(Key k1, Key k2);
link newNode(Item val, link next);
comando StampaMenu();
void EseguiComando(link *ph, comando cmd, int *p_end);
void AnagScan(Item *p_anag, FILE *fp);
link InserimentoTastiera(link *ph);
link InserimentoFile(link *ph);
void RicercaCodice(link h);
link ExtrCodice(link *ph);
link ExtrBirth(link *ph);
int BirthListExtr(link *px, link *pp, link *ph, char *d1, char *d2);

int main(){
    int end = 0, *p_end = &end;
    link h = NULL; //Lista vuota
    comando cmd;
    while (!*p_end){
        cmd = StampaMenu();
        EseguiComando(&h, cmd, p_end);
    }
    Dealloc(h);
    return 0;
}

//Deallocazione lista
void Dealloc(link h){
    if (h == NULL) return;
    link t = h;
    h = h->next;
    free(t->val.codice);
    free(t->val.birth);
    free(t->val.citta);
    free(t->val.via);
    free(t->val.nome);
    free(t->val.cognome);
    free(t->val.cap);
    free(t);
    Dealloc(h);
}

//Stampa in riga il contenuto di Item sul file specificato
void ITEMshowF(Item d, FILE *fp){
    fprintf(fp, "%s %s %s %s %s %s %s\n", d.codice, d.nome, d.cognome, d.birth, d.via, d.citta, d.cap);
}

//Funzione che legge il nome del file su cui scrivere il contenuto della lista e chiama
//la funzione di stampa ricorsiva
void ListFilePrint(link h){
    FILE *fp;
    char nomef[MAXC1];
    printf("Inserire il nome del file:\n");
    scanf("%s", nomef);
    fp = fopen(nomef, "w");
    StampaListaR(fp, h); //Stampa ricorsiva della lista
    fclose(fp);
}

//Funzione ricorsiva di stampa della lista su file, ricevuti come parametro
void StampaListaR(FILE *fp, link h){
    if (h == NULL) return;
    ITEMshowF(h->val, fp);
    StampaListaR(fp, h->next);
}

//Ritorna la data di nascita
Key KEYget1(Item d){
    return d.birth;
}

//Ritorna il codice
Key KEYget2(Item d){
    return d.codice;
}

//ritorna 1 se i due codici sono uguali
int KEYeq(Key k1, Key k2){
    int eq = strcmp(k1, k2);
    if (eq == 0) return 1;
    return 0;
}

//ritorna 1 se la prima data è uguale o successiva alla seconda
int KEYgeq(Key k1, Key k2){
    int g1, m1, a1, g2, m2, a2;
    sscanf(k1, "%d/%d/%d", &g1, &m1, &a1);
    sscanf(k2, "%d/%d/%d", &g2, &m2, &a2);
    if (a1 == a2){
        if (m1 == m2){
            if (g1 >= g2) return 1;
            return 0;
        } else if (m1 >= m2) return 1;
        return 0;
    } else if (a1 >= a2) return 1;
    return 0;

}

//generazione nodo
link newNode(Item val, link next){
    link x = malloc(sizeof *x);
    if (x == NULL) return NULL;
    x->val = val;
    x->next = next;
    return x;
}

//stampa del menu e acquisizione comando
comando StampaMenu(){
    char comm[MAXC1];
    comando com;

    printf("\n____MENU____\n");
    printf("KBInsert: inserimento in lista da tastiera\n");
    printf("FileInsert: inserimento in lista da file\n");
    printf("CodSearch: ricerca per codice\n");
    printf("ExtrCodSearch: estrazione lista per codice\n");
    printf("ExtrBSearch: estrazione lista per intervallo di 2 date\n");
    printf("PrintFile: stampa lista su file\n");
    printf("Fine: termina programma\n\n");
    printf("Inserire il comando da eseguire:\n");
    scanf("%s", comm);

    if (strcasecmp("KBInsert", comm) == 0) com = 0;
    else if (strcasecmp("FileInsert", comm) == 0) com = 1;
    else if (strcasecmp("CodSearch", comm) == 0) com = 2;
    else if (strcasecmp("ExtrCodSearch", comm) == 0) com = 3;
    else if (strcasecmp("ExtrBSearch", comm) == 0) com = 4;
    else if (strcasecmp("PrintFile", comm) == 0) com = 5;
    else if (strcasecmp("Fine", comm) == 0) com = 6;
    else com = 7;

    return com;
}

// esecuzione delle istruzioni relative al comando. Selezione su switch
void EseguiComando(link *ph, comando cmd, int *p_end){
    switch (cmd) {
        case KBInsert:
            *ph = InserimentoTastiera(ph);
            break;
        case FileInsert:
            *ph = InserimentoFile(ph);
            break;
        case CodSearch:
            RicercaCodice(*ph);
            break;
        case ExtrCodSearch:
            *ph = ExtrCodice(ph);
            break;
        case ExtrBSearch:
            *ph = ExtrBirth(ph);
            break;
        case PrintFile:
            ListFilePrint(*ph);
            break;
        case end:
            *p_end = 1;
            break;
        case err:
            printf("Comando non valido: Riprovare\n\n");
            break;
    }
}

//Lettura dell'anagrafica da file (o terminale), e conseguente
//allocazione dinamica di tutte le stringhe
void AnagScan(Item *p_anag, FILE *fp){
    char tmp[MAXC1];
    fscanf(fp, "%s", tmp);
    p_anag->codice = strdup(tmp);
    fscanf(fp, "%s", tmp);
    p_anag->nome = strdup(tmp);
    fscanf(fp, "%s", tmp);
    p_anag->cognome = strdup(tmp);
    fscanf(fp, "%s", tmp);
    p_anag->birth = strdup(tmp);
    fscanf(fp, "%s", tmp);
    p_anag->via = strdup(tmp);
    fscanf(fp, "%s", tmp);
    p_anag->citta = strdup(tmp);
    fscanf(fp, "%s", tmp);
    p_anag->cap = strdup(tmp);
}

//Inserimento ordinato in lista di Item letto da tastiera
link InserimentoTastiera(link *ph) {
    link x, p = NULL;
    Item anag;

    printf("Inserire i campi della anagrafica uno sotto l'altro nell'ordine:\n");
    printf("<codice> <nome> <cognome> <data_di_nascita> <via> <citta'> <cap>\n");
    AnagScan(&anag, stdin);

    if (*ph == NULL) return newNode(anag, NULL);
    for (x = *ph; x != NULL && KEYgeq(KEYget1(anag), KEYget1(x->val)); p = x, x = x->next);
    if (x == *ph) return newNode(anag, x); //Inserimento in testa
    else p->next = newNode(anag, x); //Inserimento fra p e x

    return *ph;
}

//Inserimento ordinato in lista di Item letti da file
link InserimentoFile(link *ph){
    FILE *fp;
    Item anag;
    link x, p = NULL;
    char nomef[MAXC1];
    printf("Inserire il nome del file:\n");
    scanf("%s", nomef);
    fp = fopen(nomef, "r");

    while (!feof(fp)){
        AnagScan(&anag, fp); //Lettura riga da file
        if (*ph == NULL) *ph = newNode(anag, NULL); //Inserimento in lista vuota
        else {
            for (x = *ph; x != NULL && KEYgeq(KEYget1(anag), KEYget1(x->val)); p = x, x = x->next);
            if (x == *ph) *ph = newNode(anag, x); //Inserimento in testa
            else p->next = newNode(anag, x); //Inserimento fra p e x
        }
    }

    fclose(fp);
    return *ph;
}

//Ricerca in lista per codice con scansione
void RicercaCodice(link h){
    char codice[MAXC2];
    printf("Inserire il codice da ricercare:\n");
    scanf("%s", codice);

    for (link x = h; x != NULL; x = x->next){
        if (KEYeq(KEYget2(x->val), codice)){
            ITEMshowF(x->val, stdout);
            break;
        }
    }
}

//Estrazione dalla lista con codice
link ExtrCodice(link *ph){
    char codice[MAXC2];
    link x, p = NULL;
    Item tmp;
    printf("Inserire il codice da ricercare:\n");
    scanf("%s", codice);

    for (x = *ph; x != NULL; p = x, x = x->next){
        if (KEYeq(KEYget2(x->val), codice)){
            tmp = x->val;
            if (x == *ph) *ph = x->next; //estrazione dalla testa
            else p->next = x->next; //estrazione interna
            free(x); //deallocazione memoria del nodo estratto
            ITEMshowF(tmp, stdout);
            break;
        }
    }
    return *ph;
}

//funzione che salva le due date e cerca il primo nodo da eliminare,
//poi chiama la funzione di estrazione vera
link ExtrBirth(link *ph){
    char d1[MAXC3], d2[MAXC3];
    int end = 0;
    link x, p = NULL;
    printf("Inserire le due date separate da spazio nel formato gg/mm/aaaa :\n");
    scanf("%s %s", d1, d2);

    //ciclo per trovare la prima anagrafica da cancellare
    for (x = *ph; x != NULL && KEYgeq(d1, KEYget1(x->val)); p = x, x = x->next);
    //fintanto che la lista è terminata oppure ho terminato gli elementi in lista da eliminare
    while (x != NULL && !end){
        end = BirthListExtr(&x, &p, ph, d1, d2); //estrazione dalla lista date due date
        x = x->next;
    }
    return *ph;
}

//Estrazione date due date, puntatore a testa della lista, puntatore a precedente e al nodo
//corrente da eliminare. Ritorna 1 se il nodo corrente non è da cancellare, cosi posso
//uscire dal while della funzione chiamante
int BirthListExtr(link *px, link *pp, link *ph, char *d1, char *d2){
    link x = *px;
    Item  tmp;

    //condizione di estrazione nodo
    if (KEYgeq(KEYget1(x->val), d1) && KEYgeq(d2, KEYget1(x->val))){
        tmp = x->val;
        if (x == *ph) *ph = x->next; //estrazione in testa
        else (*pp)->next = x->next; //estrazione in mezzo
        free(x); //deallocazione nodo cancellato
        ITEMshowF(tmp, stdout);
        return 0;
    }
    return 1;
}