#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXL 50

typedef enum {
    singolo_aq,
    multiplo_aqFile,
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
link listInsOrd (link head, Item val);
int confrontoDataGrande(Item val1, Item val2);
void dealloca(link head);
comando_e scelta();
link filtroDati(comando_e comando, link head);
void stampaLista(link head);
void stampaSingolo(link nodo);
link inputElemento(link head);
link ricercaCodice(link head);
link ricercaCodiceRiallaccio(link head);
link ricercaData(link head, char iniziale[11]);
void cancelloData(link x, char dataFinale[11]);



int main() {
    link head = NULL;
    comando_e comando = -1;

    while(comando != fine) {
        ///LETTURA COMANDO
        comando = scelta();
        ///SELEZIONE IN BASE AL COMANDO
        head = filtroDati(comando, head);
    }

    dealloca(head);
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
    ///CONTINUA A AGGIUNGERE COSE FINO ALLA FINE DEL FILE
    while(!feof(fp)){
        fscanf(fp, "%s %s %s %s %s %s %d", tmp.codice, tmp.nome, tmp.cognome, data, tmp.via, tmp.citta, &tmp.cap);
        sscanf(data, "%d/%d/%d", &tmp.data.giorno, &tmp.data.mese, &tmp.data.anno);
        head = listInsOrd(head, tmp);
    }


    fclose(fp);
    return head;
}

///CREA UN NUOVO NODO
link newNode(Item val, link next) {
    ///CREO UN TIPO LINK TEMPORANEO E LO RIEMPIO
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
link listInsOrd (link head, Item val) {
    link x, p;
    ///CASO DI INSERZIONE IN TESTA
    if (head == NULL || confrontoDataGrande(val, head->val))
        return head = newNode(val, head);
    ///ITERA FINO A TROVARE IL PUNTO DOVE INSERIRE
    for (x=head->next, p=head; x != NULL && confrontoDataGrande(x->val, val); p=x, x=x->next);
    p->next = newNode(val, x);
    return head;
}

///FUNZIONE CHE CONFRONTA QUALE VALORE DI DATA E' MAGGIORE, SE IL PRIMO TORNA 1 SENNO 0
int confrontoDataGrande(Item val1, Item val2){
    int bool = 0;
    ///SEMPLICE CONFONTO DI DATE
    if (val1.data.anno > val2.data.anno) {
        bool = 1;
        return bool;
    }
    else if(val1.data.anno == val2.data.anno){
        if(val1.data.mese > val2.data.mese){
            bool = 1;
            return bool;
        }
        else if(val1.data.mese == val2.data.mese) {
            if(val1.data.giorno >= val2.data.giorno){
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

///FUNZIONE CHE DEALLOCA
void dealloca(link head){
    link succ;
    while (head != NULL){
        succ = head->next;
        free(head);
        head = succ;
    }
}

///FUNZIONE PER LA SCELTA DELL'OUTPUT
comando_e scelta(){
    char comando[MAXL];
    comando_e comandoE;
    printf("\n-------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\tLISTA COMANDI\n");
    printf("-------------------------------------------------------------------------------------------------------\n\n");
    printf("singolo_aq -> acquisizione di un valore da tastiera ed inserimento nella lista ordinata\n");
    printf("multiplo_aqFile -> acquisizione di piu' di un valore da un file ed inserimento nella lista ordinat\n");
    printf("ricerca_per_codice -> ricerca di un elemento in base al codice identificativo\n");
    printf("codice_cancellazione -> cancellazione di un elemento in base al codice identificativo\n");
    printf("date_comprese_cancellazione -> cancellazione di elementi con data compresa tra due prese in input\n");
    printf("stampa -> stampa la lista\n");
    printf("fine -> uscita dal programma\n\n");
    printf("-------------------------------------------------------------------------------------------------------\n\n");

    printf("Inserisci comando:\n");
    scanf(" %s", comando);

    ///TROVO IL COMPANDO DI ENUM CORRISPONDENTE
    if(strcmp("singolo_aq", comando) == 0){
        comandoE = 0;
    }
    else if(strcmp("multiplo_aqFile", comando) == 0){
        comandoE = 1;
    }
    else if(strcmp("ricerca_per_codice", comando) == 0){
        comandoE = 2;
    }
    else if(strcmp("codice_cancellazione", comando) == 0){
        comandoE = 3;
    }
    else if(strcmp("date_comprese_cancellazione", comando) == 0){
        comandoE = 4;
    }
    else if(strcmp("stampa", comando) == 0){
        comandoE = 5;
    }
    else if(strcmp("fine", comando) == 0){
        comandoE = 6;
    }
    else{
        printf("errore nel comando");
        exit(1);
    }

    return comandoE;
}

///FUNZIONE PER FILTRARE I DATI
link filtroDati(comando_e comando, link head){
    char nomeFile[MAXL], data1[11], data2[11];
    int giorno, mese, anno, i;
    link x, y, z;

    ///GESTISCO OGNI CASISTICA
    switch (comando) {

        case singolo_aq:
            head = inputElemento(head);
            break;

        case multiplo_aqFile:
            printf("inserisci il nome del file\n");
            scanf("%s", nomeFile);
            head = leggiFile(nomeFile, head);
            break;

        case ricerca_per_codice:
            x = ricercaCodice(head);
            if(x != NULL)
                stampaSingolo(x);
            else
                printf("Codice non trovato");
            break;

        case codice_cancellazione:
            x = ricercaCodiceRiallaccio(head);
            if(x != NULL) {
                stampaSingolo(x);
                free(x);  /// LIBERO IL VALORE
            }
            else
                printf("Codice non trovato");
            break;

        case date_comprese_cancellazione:
            printf("inserire la data di inizio gg/mm/aaaa :");
            scanf("%s", data1);
            printf("inserire la data di fine gg/mm/aaaa :");
            scanf("%s", data2);

            x = ricercaData(head, data1);
            if(x != NULL) {
                cancelloData(x, data2);
            }
            else
                printf("non sono stati trovati valori tra queste date");

            break;

        case stampa:
            stampaLista(head);
            break;
        case fine:
            break;
    }
    return head;
}

///FUNZIONE CHE STAMPA LA LISTA
void stampaLista(link head) {
    link x;
    ///CICLO ITERATIVO SU TUTTA LA LISTA
    for (x=head; x!=NULL; x=x->next){
        printf("%s %s %s %02d/%02d/%02d %s %s %05d\n", x->val.codice, x->val.nome, x->val.cognome,
               x->val.data.giorno, x->val.data.mese, x->val.data.anno, x->val.via, x->val.citta, x->val.cap);
    }
}

///FUNZIONE CHE STAMPA IL SINGOLO NODO
void stampaSingolo(link nodo) {
    printf("\n%s %s %s %02d/%02d/%02d %s %s %05d\n", nodo->val.codice, nodo->val.nome, nodo->val.cognome,
           nodo->val.data.giorno, nodo->val.data.mese, nodo->val.data.anno, nodo->val.via, nodo->val.citta, nodo->val.cap);
}

///FUNZIONE PER AGGIUNGERE UN ELEMENTO DELLA LISTA DA TASTIERA
link inputElemento(link head) {
    Item tmp;
    char data[11];
    printf("INSERIMENTO DA TASTIERA\n");
    printf("Inserire il codice:"); scanf("%s ", tmp.codice); printf("\n");
    printf("Inserire il nome:"); scanf("%s", tmp.nome); printf("\n");
    printf("Inserire il cognome:"); scanf("%s", tmp.cognome); printf("\n");

    printf("Inserire la data gg/mm/aaaa:"); scanf("%s", data);
    sscanf(data, "%d/%d/%d", &tmp.data.giorno, &tmp.data.mese, &tmp.data.anno); printf("\n");

    printf("Inserire la via:"); scanf("%s", tmp.via); printf("\n");
    printf("Inserire la citta:"); scanf("%s", tmp.citta); printf("\n");
    printf("Inserire il CAP:"); scanf("%d", &tmp.cap); printf("\n");

    head = listInsOrd(head, tmp);

    return head;
}

///FUNZIONE CHE RICERCA IN BASE AL CODICE RICHIESTO
link ricercaCodice(link head) {
    link x;
    char codice[6];

    printf("inserire il codice da cercare del tipo AXXXX : ");
    scanf("%5s", codice);

    ///CICLO ITERATIVO SULLA LISTA FINO AL RAGGIUNGIMENTO DEL CAMPO VOLUTO O FINO ALLA FINE
    if (head == NULL)
        return NULL;
    for (x=head; x!=NULL && strcmp(x->val.codice, codice)!=0; x=x->next){}

    return x;
}

///FUNZIONE DI RICERCA IN CASO DI CANCELLAZIONE PER EVITARE DI LASCIARE STACCATA LA LISTA
link ricercaCodiceRiallaccio(link head){
    link x, p;
    char codice[6];

    printf("inserire il codice da cercare del tipo AXXXX : ");
    scanf("%5s", codice);

    if (head == NULL)
        return NULL;
    for (x=head, p=NULL; x!=NULL; p=x, x=x->next) {
        if (strcmp(x->val.codice, codice) == 0) {
            if (x == head)
                head = x->next;
            else
                p->next = x->next;
            return x;
        }
    }
    return x;
}

///FUNZIONE PER CERCARE VALORE CON DATA CORRISPONDENTE
link ricercaData(link head, char iniziale[11]) {
    link x = NULL, p;
    int giorno, mese, anno;

    ///SEPARO LA STRNGA
    sscanf(iniziale,"%d/%d/%d", &giorno, &mese, &anno);

    ///CICLO ITERATIVO SULLA LISTA FINO AL RAGGIUNGIMENTO DEL CAMPO VOLUTO O FINO ALLA FINE
    if (head == NULL)
        return NULL;
    for (x=head, p=NULL; x!=NULL; p=x, x=x->next){
        if (x->val.data.anno > anno) {
            return p;
        }
        else if(x->val.data.anno == anno){
            if(x->val.data.mese > mese){
                return p;
            }
            else if(x->val.data.mese == mese) {
                if(x->val.data.giorno >= giorno){
                    return p;
                }
            }
        }
    }

    return x;
}

void cancelloData(link x, char dataFinale[11]) {
    int giorno, mese, anno;
    link y;

    sscanf(dataFinale,"%d/%d/%d", &giorno, &mese, &anno);
    for(y=x->next; y->next != NULL; y=x->next) {
        if (y->val.data.anno <= anno) {
            x->next = y->next;
            stampaSingolo(y);
            free(y);
        } else if (y->val.data.anno == anno) {
            if (y->val.data.mese < mese) {
                x->next = y->next;
                stampaSingolo(y);
                free(y);
            } else if (y->val.data.mese == mese) {
                if (y->val.data.giorno <= giorno) {
                    x->next = y->next;
                    stampaSingolo(y);
                    free(y);
                }
            }
        }
    }


}