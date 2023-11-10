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
enum comando_e {r_ricercaCodice, r_cancellazioneCodice, r_cancellazioneDate};
int leggiComando();
link letturaAnagrafica(int scelta, int *terminazione, link h);
FILE *apertura_file();
link newNode(Item *persona, link next);//funzione per la creazione di un nuovo nodo della lista
link SortListIns(link h, Item *persona); //funzione per inserimento in lista di un Item
int VerificaData(data_di_nascita data1, data_di_nascita data2); //funzione per effettuare un confronto fra date, se la prima data risulta maggiore della seconda ritorna 1, altrimenti ritorna 0
link allocaItem(FILE *fin); //funzione per leggere un nuovo elemento da inserire nella lista

int main() {

    int terminazione = 0, scelta;
 //se desidero terminare l'inserimento di elementi nella lista inserisci assume valore 0

    link h = NULL ;

    while (!terminazione){
        scelta = leggiComando(); //leggo il comando selezionato e lo passo
        h = letturaAnagrafica(scelta, &terminazione, h);
    }


    return 0;
}

int leggiComando(){ //funzione che legge il comando da eseguire
    char *option;
    int scelta , flag_scelta = 1;
    while(flag_scelta) {
        printf("\nScegli se leggere da file o da tastiera");
        scanf("%s", option);

        if(strcasecmp(option,"tastiera") == 0)     { return scelta = 0;}

        else if(strcasecmp(option,"file") == 0)     { return scelta = 1;}
    }
}

link letturaAnagrafica(int scelta, int *terminazione, link h){
    Item *persona;
    FILE* fin;
    link p = NULL; //puntatore a predecessore, in un ciclo salvo qui ciò che è puntato dall'elemento precedente in coda
    switch (scelta) {
        case r_tastiera:
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
            return h;

        case r_file:
            fin = apertura_file();
            while(!feof(fin)){
                persona = (Item*) malloc(sizeof (Item));
                fscanf(fin,"%s", persona->codice);
                fscanf(fin,"%s", persona->nome);
                fscanf(fin,"%s", persona->cognome);
                fscanf(fin,"%d/%d/%d", persona->data.giorno, persona->data.mese, persona->data.anno);
                fscanf(fin,"%s", persona->via);
                fscanf(fin,"%s", persona->citta);
                fscanf(fin,"%d", &persona->cap);

                h = SortListIns(h, persona);
                free(persona);
                fclose(fin);

                return h;
            }



    }


}

FILE *apertura_file(){
    char *nome_file;
    FILE *fin;
    printf("\nInserisci il nome del file da aprire: ");
    scanf("%s", nome_file);
    fin = fopen(nome_file, "r");
    return fin;
}

int VerificaData(data_di_nascita data1, data_di_nascita data2){ //se la prima data risulta maggiore della seconda ritorna 1, altrimenti ritorna 0
    int maggiore = 0;
    if(data1.anno < data2.anno){ //la prima data risulta maggiore rispetto alla seconda
        return 1;
    }
    else if(data1.anno > data2.anno){//la prima data risulta inferiore rispetto alla seconda
        return 0;
    }
    else if(data1.mese < data2.mese){
        return 1;
    }
    else if(data1.mese > data2.mese){
        return 0;
    }
    else if(data1.giorno < data2.giorno){
        return 1;
    }
    else if(data1.giorno > data2.giorno){
        return 0;
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


link allocaItem(FILE *fin){

}


link SortListIns(link h, Item *persona){
    link x, p; //x elemento successivo, p predecessore (sono entrambi puntatori a struct node
    int flag_minore = 0; //quando viene trovato un elemento minore rispetto ad un altro inserisco l'elemento subito prima

    if(h == NULL || VerificaData(h->persona->data, persona->data)){
        return newNode(persona, h);//non ho una testa della lista quindi ritorno direttamente un nuovo nodo che sarà la mia nuova testa
    }
    for (x = h->next, p = h; x!=NULL && !VerificaData(persona->data, x->persona->data); x = x->next);  //ciclo che mi permette di avanzare nella lista finchè persona.data è maggiore di h->persona->data
                                                                                                                  //cioè finchè non trovo un elemento maggiore di quello che voglio inserire
    p->next = newNode(persona, x);//quando termino il ciclo di avanzamento nella lista significa che l'elemento trovato nella lista risulta maggiore di quello che voglio inserire
                                        //in questo caso ci inserisco sopra l'elemento minore
                                        //poiche ricerco un ordinamento crescente
    return h;//ritorno la testa della lista
}