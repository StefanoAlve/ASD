#include <stdio.h>
#include "stdlib.h"
#include "string.h"

typedef struct{ //struct per conservare le date di nascita
    int giorno;
    int mese;
    int anno;
} data_di_nascita;

typedef struct { // struct Item in cui conservo le informazioni delle anagrafiche delle singole persone
    char codice[5];
    char nome[50];
    char cognome[50];
    data_di_nascita data;
    char via[50];
    char citta[50];
    int cap;
} Item;

typedef struct node *link; //definisco una struct node e le assegno il tipo puntatore, ma la struct non è definita, la struct node è definita da link

struct node{ // definisco la struct node, al cui interno ho il puntatore a un'altra struct node
    Item *persona;
    link next;
};
//per dichiarare una struct node utilizzo il tipo link

enum input_e {r_tastiera, r_file} scelta_input;
enum comando_e {r_ricercaCodice, r_cancellazioneCodice, r_cancellazioneDate, r_StampaFile};
int leggiComandoAcquisizione();
int leggiComandoOperazione();
int leggiTerminazione();
int VerificaData(data_di_nascita *data1, data_di_nascita *data2); //funzione per effettuare un confronto fra date, se la prima data risulta minore della seconda ritorna 1, altrimenti ritorna 0
void StampaRisultato(Item *persona);
void StampaFile(link h);
link letturaAnagrafica(int scelta, int *terminazione, link h);
link OperaSuLista(int scelta, int *terminazione, link h);
link InserisciItem(link h, int flag_file); //funzione per leggere un nuovo elemento da inserire nella lista
link newNode(Item *persona, link next);//funzione per la creazione di un nuovo nodo della lista
link SortListIns(link h, Item *persona); //funzione per inserimento in lista di un Item
link EliminaCodice(link h, char *codice, Item **Pestratto);
link EliminaDate(link h, data_di_nascita *data1, data_di_nascita *data2, Item **Pestratto);
FILE *apertura_file_lettura();
FILE *apertura_file_scrittura();
Item *RicercaCodice(link h, char *codice);




int main() {

    int terminazione1 = 0, terminazione2 = 0, scelta;
 //se desidero terminare l'inserimento di elementi nella lista inserisci assume valore 0

    link h = NULL ;

    while (!terminazione1){
        scelta = leggiComandoAcquisizione(); //leggo il comando selezionato per l'acquisizione delle informazioni e lo passo
        h = letturaAnagrafica(scelta, &terminazione1, h);
    }

    while(!terminazione2){
        scelta = leggiComandoOperazione();
        h = OperaSuLista(scelta, &terminazione2, h);
    }
    return 0;
}



int leggiComandoAcquisizione(){ //funzione che legge il comando da eseguire
    char *option;
    int scelta , flag_scelta = 1;
    while(flag_scelta) {
        printf("\nScegli se leggere da file o da tastiera");
        scanf("%s", option);

        if(strcasecmp(option,"tastiera") == 0)     { return scelta = 0;}

        else if(strcasecmp(option,"file") == 0)     { return scelta = 1;}
    }
}
int leggiComandoOperazione(){
    char *option;
    int scelta , flag_scelta = 1;
    while(flag_scelta) {
        printf("\nScegli quale operazione effettuare:"
               "\n\t-RicercaCodice; \n\t-EliminaCodice;\n\t-EliminaDate;\n\t-StampaFile;\n");
        scanf("%s", option);

        if(strcasecmp(option,"RicercaCodice") == 0)     { return scelta = 0;}

        else if(strcasecmp(option,"EliminaCodice") == 0)     { return scelta = 1;}

        else if(strcasecmp(option,"EliminaDate") == 0)     { return scelta = 2;}

        else if(strcasecmp(option,"StampaFile") == 0)     { return scelta = 3;}

    }
}


int leggiTerminazione(){
    char *option;
    int scelta , flag_scelta = 1;
    while(flag_scelta) {
        printf("\nVuoi terminare questo processo? ");
        scanf("%s", option);

        if(strcasecmp(option,"si") == 0)     { return scelta = 0;}

        else if(strcasecmp(option,"no") == 0)     { return scelta = 1;}
    }
}

link letturaAnagrafica(int scelta, int *terminazione, link h){

    switch (scelta) {
        case r_tastiera:
            h = InserisciItem(h, 0);
            *terminazione = leggiTerminazione();
            return h;

        case r_file:
                h = InserisciItem(h, 1);
                *terminazione = leggiTerminazione();
                return h;
            }
    }

link OperaSuLista(int scelta, int *terminazione, link h){
    char codice[5];
    Item *elemento_estratto = malloc(sizeof(Item));
    switch (scelta) {
        case r_ricercaCodice:
            printf("Inserisci il codice con cui fare la ricerca nel formato AXXXX dove X è un numero tra 0 e 9: ");
            scanf("%s", codice);
            StampaRisultato(RicercaCodice(h,codice));
            *terminazione = leggiTerminazione();
            return h;

        case r_cancellazioneCodice:

            printf("Inserisci il codice dell'elemento da eliminare dalla lista nel formato AXXXX dove X è un numero tra 0 e 9:  ");

            scanf("%s", codice);



            h = EliminaCodice(h, codice, &elemento_estratto);

            StampaRisultato(elemento_estratto);

            free(elemento_estratto);
            *terminazione = leggiTerminazione();
            return h;

        case r_cancellazioneDate:
            printf("Inserisci la prima delle due date dell'intervallo per cui eliminare gli elementi nel formato gg/mm/aaaa: ");
            data_di_nascita *data1 = malloc(sizeof(data_di_nascita)), *data2 = malloc(sizeof(data_di_nascita));
            scanf("%d/%d/%d",&data1->giorno, &data1->mese, &data1->anno );
            printf("Inserisci la seconda delle due date dell'intervallo per cui eliminare gli elementi nel formato gg/mm/aaaa: ");
            scanf("%d/%d/%d",&data2->giorno, &data2->mese, &data2->anno );

            h =  EliminaDate(h, data1, data2, &elemento_estratto);

            free(data1);
            free(data2);
            free(elemento_estratto);
            *terminazione = leggiTerminazione();
            return h;

        case r_StampaFile:
            StampaFile(h);
            *terminazione = leggiTerminazione();
            return h;
    }
}




int VerificaData(data_di_nascita *data1, data_di_nascita *data2){ //se la prima data risulta minore della seconda ritorna 1, altrimenti ritorna 0

    if(data1->anno < data2->anno){
        return 1;
    }
    else if(data1->anno > data2->anno){
        return 0;
    }
    else if(data1->mese < data2->mese){
        return 1;
    }
    else if(data1->mese > data2->mese){
        return 0;
    }
    else if(data1->giorno < data2->giorno){
        return 1;
    }
    else if(data1->giorno > data2->giorno){
        return 0;
    }
}

void StampaRisultato(Item *persona){
    if(persona != NULL){
        printf("\n%s %s %s %d/%d/%d %s %s %d",persona->codice, persona->nome, persona->cognome, persona->data.giorno,
               persona->data.mese, persona->data.anno,persona->via, persona->citta, persona->cap);
    }
    else{
        printf("\nNon è stato trovata una corrispondenza");
    }

}

void StampaFile(link h){
    FILE *fout =apertura_file_scrittura();
    link x;
    for(x = h; x!=NULL; x = x->next){
        if(x != NULL){
            fprintf(fout,"\n%s %s %s %d/%d/%d %s %s %d",x->persona->codice, x->persona->nome, x->persona->cognome, x->persona->data.giorno,
                    x->persona->data.mese, x->persona->data.anno, x->persona->via, x->persona->citta, x->persona->cap);
        }
        else{
            printf("\nNon è stato possibile effettuare la stampa su file");
        }
    }


}

link newNode(Item *persona, link next) {//passo alla funzione newnode l'elemento di tipo item da aggiungere nella lista e un puntatore next
    //in questo modo aggiungo in coda alla testa
    link x = malloc(sizeof(struct node)); //allocazione di un nodo

    if(x == NULL){
        return NULL;
    }else{
        x->persona = persona; //assegno al puntatore x->persona il puntatore alla struct persona
        x->next = next;
    }
    return x;
}


link InserisciItem(link h, int flag_file){
    Item *persona;
    link p = NULL; //puntatore a predecessore, in un ciclo salvo qui ciò che è puntato dall'elemento precedente in coda
    if(flag_file) {
        FILE *fin = apertura_file_lettura();
        while (!feof(fin)) {
            persona = (Item *) malloc(sizeof(Item));
            fscanf(fin, "%s", persona->codice);
            fscanf(fin, "%s", persona->nome);
            fscanf(fin, "%s", persona->cognome);
            fscanf(fin, "%d/%d/%d", &persona->data.giorno, &persona->data.mese, &persona->data.anno);
            fscanf(fin, "%s", persona->via);
            fscanf(fin, "%s", persona->citta);
            fscanf(fin, "%d", &persona->cap);

            h = SortListIns(h, persona);
            free(persona);
            fclose(fin);
        }
    }
    else if (!flag_file){
        persona =(Item*) malloc(sizeof (Item));
        printf("\nInserisci il codice nella forma AXXXX (dove X rappresenta una cifra nell'intervallo 0-9):  ");
        scanf("%s", persona->codice);
        printf("\nInserisci nome: ");
        scanf("%s", persona->nome);
        printf("\nInserisci cognome: ");
        scanf("%s", persona->cognome);
        printf("\nInserisci la data di nascita nel formato gg/mm/aaaa: ");
        scanf("%d/%d/%d", persona->data.giorno, persona->data.mese, persona->data.anno);
        printf("\nInserisci la via di residenza (es:ViaMarcoPolo) : ");
        scanf("%s", persona->via);
        printf("\nInserisci la città di residenza: ");
        scanf("%s", persona->citta);
        printf("\nInserisci il cap: ");
        scanf("%d", &persona->cap);

        h = SortListIns(h, persona);
        free(persona);
    }
    return h;
}

link SortListIns(link h, Item *persona){
    link x, p; //x elemento successivo, p predecessore (sono entrambi puntatori a struct node
    int flag_minore = 0; //quando viene trovato un elemento minore rispetto ad un altro inserisco l'elemento subito prima

    if(h == NULL || VerificaData(&h->persona->data, &persona->data)){
        return newNode(persona, h);//non ho una testa della lista quindi ritorno direttamente un nuovo nodo che sarà la mia nuova testa
    }
    for (x = h->next, p = h; x!=NULL && !VerificaData(&persona->data, &x->persona->data); x = x->next);  //ciclo che mi permette di avanzare nella lista finchè persona.data è maggiore di h->persona->data
                                                                                                                  //cioè finchè non trovo un elemento maggiore di quello che voglio inserire
    p->next = newNode(persona, x);//quando termino il ciclo di avanzamento nella lista significa che l'elemento trovato nella lista risulta maggiore di quello che voglio inserire
                                        //in questo caso ci inserisco sopra l'elemento minore
                                        //poiche ricerco un ordinamento crescente
    return h;//ritorno la testa della lista
}

link EliminaCodice(link h, char *codice, Item **Pestratto){
    link x, p;
    Item *temp = NULL;
    if(h == NULL){
        printf("\nLista Vuota");
        return NULL;
    }
    for(x = h, p = NULL; x!=NULL; p = x, x = x->next){
        if(strcasecmp(codice, h->persona->codice) == 0){
            if(x == h){
                h = x->next;//se la chiave di ricerca è nel primo nodo della lista, escludo il nodo assegnando alla testa il puntatore al nodo successivo
                temp = x->persona;
            }
            else{
                p->next = x->next; //bypass di x; collego al precedente di x il successivo di x così da non rendere visibile x nella lista
                temp = x->persona;
            }
            free(x);//libero il puntatore a x
            break;
        }
    }
    *Pestratto = temp;//passo by pointer il puntatatore alla struct persona che ho eliminato dalla lista per estrarre l'elemento eliminato dalla lista
    return h;
}

link EliminaDate(link h, data_di_nascita *data1, data_di_nascita *data2, Item **Pestratto){
    link x, p, t;
    int primo_elemento = 1;
    Item *temp = NULL;

    if(h == NULL){
        printf("\nLista Vuota");
        return NULL;
    }
    for(x = h, p = NULL; x!=NULL; p = t, x = t->next){
        if(VerificaData(data1,&x->persona->data) && VerificaData(&x->persona->data, data2)){
            if(x==h){
                h= x->next;
                if(primo_elemento){
                    temp = x->persona;
                    primo_elemento = 0;
                }
                StampaRisultato(x->persona);
            }
            else{
                if(primo_elemento){
                    temp = x->persona;
                    primo_elemento = 0;
                }
                p->next = x->next;
                StampaRisultato(x->persona);
            }
            t = x;
            free(x);
        }
    }
    *Pestratto = temp;//passo by pointer il puntatatore alla struct persona che ho eliminato dalla lista per estrarre l'elemento eliminato dalla lista
    return h;
}

Item *RicercaCodice(link h, char *codice){ //funzione che ritorna il puntatore all'item corrispondente
    link x;
    for(x = h; x!=NULL && strcasecmp(codice, h->persona->codice) != 0; x = x->next){
        if(strcasecmp(codice, h->persona->codice) == 0){
            return x->persona;
        }
    }
    return NULL;
}

FILE *apertura_file_lettura(){
    char *nome_file;
    FILE *fin;
    printf("\nInserisci il nome del file da aprire: ");
    scanf("%s", nome_file);
    fin = fopen(nome_file, "r");
    return fin;
}
FILE *apertura_file_scrittura(){
    char *nome_file;
    FILE *fout;
    printf("\nInserisci il nome del file da aprire: ");
    scanf("%s", nome_file);
    fout = fopen(nome_file, "w");
    return fout;
}


