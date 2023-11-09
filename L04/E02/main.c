#include <stdio.h>
#include <stdlib.h>
#define MAXL 50

typedef enum {
    singolo_aqInsOrd,
    multiplo_aqInsOrd,
    ricerca_per_codice,
    codice_cancellazione,
    date_comprese_cancellazione,
    stampa,
    fine
}comando_e;

typedef struct{
    int anno;
    int mese;
    int giorno;
}dataDiNascita;

typedef struct{
    char codice[6];
    char nome[MAXL];
    char cognome [MAXL];
    dataDiNascita data;
    char via[MAXL];
    char citta[MAXL];
    int cap;
}Item;

typedef struct node *link;

struct node{
    Item val;
    link next;
};

link leggiFile(char nomeFile[MAXL], link head);
link newNode(Item val, link next);
link listInsOrd (link h, Item val);
int confrontoDataGrande(Item val1, Item val2);



int main() {
    link head = NULL;
    char nomeFile[MAXL];

    printf("inserisci il nome del file\n");
    scanf("%s", nomeFile);

    head = leggiFile(nomeFile, head);
    return 0;
}
///LETTURA FILE
link leggiFile(char nomeFile[MAXL], link head) {
    FILE *fp;
    Item tmp;
    char data[11];

    if((fp = fopen(nomeFile, "r")) == NULL){
        printf("errore in apertura file");
        exit(1);
    }

    while(!feof(fp)){
        fscanf(fp, "%s %s %s %s %s %s %d", tmp.codice, tmp.nome, tmp.cognome, data, tmp.via, tmp.citta, &tmp.cap);
        sscanf(data, "%d/%d/%d", &tmp.data.giorno, &tmp.data.mese, &tmp.data.anno);
    }


    fclose(fp);
    return head;
}

///CREA UN NUOVO NODO
link newNode(Item val, link next) {
    link x = malloc(sizeof *x);
    if (x==NULL)
        return NULL;
    else {
        x->val = val;
        x->next = next;
    }
    return x;
}
/// INSERIMENTO ORDINATO
link listInsOrd (link h, Item val) {
    link x, p;
    if (h == NULL || confrontoDataGrande(val, h->val))
        return h = newNode(val,h);
    ///ITERA FINO A TROVARE IL PUNTO DOVE INSERIRE
    for (x=h->next, p=h;x!=NULL && confrontoDataGrande(x->val,val); p=x, x=x->next);
    p->next = newNode(val, x);
    return h;
}

///FUNZIONE CHE CONFRONTA QUALE VALORE DI DATA E' MAGGIORE, SE IL PRIMO TORNA 1 SENNO 0
int confrontoDataGrande(Item val1, Item val2){
    int bool = 0;
    if (val1.data.anno < val2.data.anno) {
        bool = 1;
        return bool;
    }
    else if(val1.data.anno == val2.data.anno){
        if(val1.data.mese < val2.data.mese){
            bool = 1;
            return bool;
        }
        else if(val1.data.mese == val2.data.mese) {
            if(val1.data.giorno <= val2.data.giorno){
                bool = 1;
                return bool;
            }
            else
                return bool;
        }
        else
            return bool;
    }
    else
        return bool;
}