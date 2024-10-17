#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXC1 50
#define MAXC2 6
#define MAXC3 11

typedef struct{
    char* codice;
    char* nome;
    char* cognome;
    char* birth;
    char* via;
    char* citta;
    char* cap;
} Item;

typedef char *Key;

typedef struct node *link;

struct node{
    Item val;
    link next;
};

typedef enum{KBInsert, FileInsert, CodSearch, ExtrCodSearch, ExtrBSearch, PrintFile, end, err} comando;

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



int main(){
    int end = 0, *p_end = &end;
    link h = NULL;
    comando cmd;
    while (!*p_end){
        cmd = StampaMenu();
        EseguiComando(&h, cmd, p_end);
    }
    return 0;
}

void ITEMshowF(Item d, FILE *fp){
    fprintf(fp, "%s %s %s %s %s %s %s\n", d.codice, d.nome, d.cognome, d.birth, d.via, d.citta, d.cap);
}

void ListFilePrint(link h){
    FILE *fp;
    char nomef[MAXC1];
    printf("Inserire il nome del file:\n");
    scanf("%s", nomef);
    fp = fopen(nomef, "w");
    StampaListaR(fp, h);
    fclose(fp);
}

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

link newNode(Item val, link next){
    link x = malloc(sizeof *x);
    if (x == NULL) return NULL;
    x->val = val;
    x->next = next;
    return x;
}

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

void EseguiComando(link *ph, comando cmd, int *p_end){
    switch (cmd) {
        case KBInsert:
            *ph = InserimentoTastiera(ph);
            break;
        case FileInsert:
            *ph = InserimentoFile(ph);
            break;
        case CodSearch:
            break;
        case ExtrCodSearch:
            break;
        case ExtrBSearch:
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

link InserimentoTastiera(link *ph) {
    link x, p = NULL;
    Item anag;

    printf("Inserire i campi della anagrafica uno sotto l'altro nell'ordine:\n");
    printf("<codice> <nome> <cognome> <data_di_nascita> <via> <citta'> <cap>\n");
    AnagScan(&anag, stdin);

    if (*ph == NULL) return newNode(anag, NULL);
    for (x = *ph; x != NULL && KEYgeq(KEYget1(anag), KEYget1(x->val)); p = x, x = x->next);
    if (x == *ph) return newNode(anag, x);
    else p->next = newNode(anag, x);

    return *ph;
}

link InserimentoFile(link *ph){
    FILE *fp;
    Item anag;
    link x, p = NULL;
    char nomef[MAXC1];
    printf("Inserire il nome del file:\n");
    scanf("%s", nomef);
    fp = fopen(nomef, "r");

    while (!feof(fp)){
        AnagScan(&anag, fp);
        if (*ph == NULL) *ph = newNode(anag, NULL);
        else {
            for (x = *ph; x != NULL && KEYgeq(KEYget1(anag), KEYget1(x->val)); p = x, x = x->next);
            if (x == *ph) *ph = newNode(anag, x);
            else p->next = newNode(anag, x);
        }
    }

    fclose(fp);
    return *ph;
}