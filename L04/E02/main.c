#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxL 50
#define numScelte 8

typedef struct{
    int gg, mm, aaaa;
}data_di_nascita;

//Struct per informazioni dal file
typedef struct{
    char codice[15]; //Formato AXXXX dove X è un numero tra 0-9
    char nome[maxL];
    char cognome[maxL];
    char via[maxL];
    char citta[maxL];
    data_di_nascita nascita;
    int cap;
}Item;

//Tipo puntatore a struct p_nodo
typedef struct p_nodo *link;

//Struct per elemento della lista
 typedef struct p_nodo{
    Item val;
    link next;
}nodo;

data_di_nascita DATAget(Item val);
data_di_nascita assegnaData(char data[]);
link newNode(Item val, link next);
link sortListIns(link head, Item val);
link assegnaDaFile(link head, char nomeFile[]);
link assegnaDaTastiera(link head);
link ricercaPerCodice(link head, char k[]);
link sortListDel(link head, char codice[]);
link cancellaTraDate(link head);
int verCancDate(link x, data_di_nascita data1, data_di_nascita data2);
int selezionaComando(char *opzioni[]);
int DATAgreater(data_di_nascita k1, data_di_nascita k2);
int CODICEgeq(char k1[], char k2[]);
Item leggiItem(FILE *fin);
Item InfDaTastiera();
void stampaLista(link head);
void stampaNodo(link x);
char *CODICEget(Item val);
FILE *stampaSuFile(link head, char nomeFile[]);

int main(){
    int flag = 1;
    data_di_nascita dataInizio, dataFine;
    link head = NULL, temp = NULL;
    FILE *fout;
    char codice[maxL], k[5], nomeFile[20], *opzioni[numScelte]= {
            "aggiungi_da_tastiera",
            "aggiungi_da_file",
            "ricerca_per_codice",
            "cancella_per_codice",
            "cancella_tra_date",
            "stampa_lista",
            "stampa_su_file",
            "uscita"
    };

    do{
        int opzione = selezionaComando(opzioni);
        switch(opzione){

            //Aggiungi elemento da tastiera
            case 1:
                head = assegnaDaTastiera(head);
                break;

            //Aggiungi elemento da file
            case 2:
                printf("Inserisci il nome del file:\n");
                scanf("%s", nomeFile);
                head = assegnaDaFile(head, nomeFile);
                break;

            //Ricerca per codice
            case 3:
                printf("Inserisci il codice da confrontare (Formato: AXXXX con X = numeri tra 0 e 9:\n");
                scanf("%s", k);
                temp = ricercaPerCodice(head,k);
                stampaNodo(temp);
                break;

            //Cancellazione per codice
            case 4:
                printf("Inserisci il codice:\n");
                scanf("%s", codice);
                head = sortListDel(head, codice);
                break;

            //Cancellazione tra date
            case 5:

                head = cancellaTraDate(head);
                stampaLista(head);
                break;

            //Stampa a video
            case 6:
                stampaLista(head);
                break;

            //Uscita
            case 7:

                //Informazioni da tastiera
                printf("Inserisci il nome del file di scrittura:");
                scanf("%s", nomeFile);

                //Scrittura file e gestione errori
                fout = stampaSuFile(head, nomeFile);

                if(fout == NULL) {
                    printf("Errore nella scrittura del file %s", nomeFile);
                    exit(2);
                }else
                    printf("File scritto con successo!\n");

                break;

            case 8:
                flag = 0;
                break;

            default:
                printf("\n\nComando errato riprova!!\n\n");

        }
    }while(flag);

    return 0;
}

//Prende le informazioni da tastiera
Item InfDaTastiera(){

    Item x;
    char data[11];

    printf("Inserisci informazioni nel seguente formato: codice, nome,"
           "cognome, citta', data, via, cap:\n");

    scanf(" %s %s %s %s %s %s %d", x.codice, x.nome, x.cognome,x.citta, data, x.via, &x.cap);
    x.nascita = assegnaData(data);

    return x;
}

//Creazione di un nuovo nodo
link newNode(Item val, link next){

    link x = (link)malloc(sizeof (struct p_nodo));
    if(x == NULL)
        return NULL;

    x->val = val;
    x->next = next;
    return x;
}

//Stampa il menu e ritorna un intero corrispondente al comando
int selezionaComando(char *opzioni[]){
    char scelta[40];
    int x = -1;

    //Stampa comandi
    printf("----------------------------------------------\n");
    printf("\t\tMENU' COMANDI\n");
    printf("----------------------------------------------\n");

    for(int i = 0; i < numScelte; i++)
        printf("-%s\n", opzioni[i]);

    //Prendo il comando scelto
    printf(":");
    scanf("%s", scelta);

    //Trovo il numero del comando corrispondente
    for(int i = 0; i < numScelte; i++)
        if(strcmp(scelta, opzioni[i]) == 0)
            x = i;

    return x + 1;
}

//Ritorna la data avendo Item
data_di_nascita DATAget(Item val){
    data_di_nascita x;

    x = val.nascita;
    return x;
}

//Restituisce un intero positivo se k1 è maggiore di k2, senno' negativo
int DATAgreater(data_di_nascita k1, data_di_nascita k2){

    if(k1.aaaa != k2.aaaa)
        return (k1.aaaa - k2.aaaa);
    if(k1.mm != k2.mm)
        return (k1.mm - k2.mm);
    if(k1.gg != k2.gg)
        return (k1.gg - k2.gg);

    return 0;
}

//Funzione che inserisce il nodo in ordine per data
link sortListIns(link head, Item val){
    link x, p;
    data_di_nascita k = DATAget(val);

    //Inserimento in testa
    if (head == NULL || (DATAgreater(DATAget(head->val), k) < 0) )
        return newNode(val, head);

    //Attraversamento per ricerca della giusta posizione
    for(x=head->next, p=head;
        x!=NULL && (DATAgreater(DATAget(x->val), k) > 0 );
        p=x, x = x->next);

    p->next = newNode(val, x);
    return head;
}

//Dal formato GG/MM/AAAA assegna ad Item
data_di_nascita assegnaData(char data[]){
    data_di_nascita temp;

    sscanf(data, "%d/%d/%d", &temp.gg, &temp.mm, &temp.aaaa);

    return temp;
}

//Legge item da file
Item leggiItem(FILE *fin){
    Item temp;
    char data[11];

    fscanf(fin, "%s %s %s %s %s %s %d", temp.codice, temp.nome, temp.cognome, data, temp.via, temp.citta, &temp.cap);

    temp.nascita = assegnaData(data);
    return temp;
}

//Creazione di un nodo a seguito d'informazioni da tastiera
link assegnaDaTastiera(link head){
    Item temp;

    temp = InfDaTastiera();
    head = sortListIns(head, temp);

    return head;
}

//Assegnazione delle informazioni nella lista da file
link assegnaDaFile(link head, char nomeFile[]){
    FILE *fin = fopen(nomeFile, "r");
    Item temp;

    if(fin == NULL)
        exit(1);

    while(!feof(fin)){
        temp = leggiItem(fin);
        head = sortListIns(head, temp);
    }
    fclose(fin);
    return head;
}

//Stampa un nodo
void stampaNodo(link x){
    printf(" %s %s %s %02d/%02d/%02d %s %s %05d\n", x->val.codice, x->val.nome, x->val.cognome,
           x->val.nascita.gg, x->val.nascita.mm, x->val.nascita.aaaa, x->val.via, x->val.citta, x->val.cap);
}

//Stampa la lista intera
void stampaLista(link head){
    link x = head;

    printf("Lista:\n");
    while(x != NULL){
        stampaNodo(x);
        x = x->next;
    }
}

//Dato item torna il codice
char *CODICEget(Item val){
    char *x = val.codice;

    return x;
}

//La funzione ritorna 1 se k1 e' maggiore uguale a k2, sennò 0
int CODICEgeq(char k1[], char k2[]){
    int flag = 0;

    if(strcmp(k1,k2) >= 0)
        flag = 1;

    return flag;
}

//La funzione ritorna 1 se sono uguali, sennò ritorna 0
int CODICEeq(char k1[], char k2[]){
    int flag = 0;

    if(strcmp(k1, k2) == 0)
        flag = 1;

    return flag;
}

//La funzione fa una ricerca per codice
link ricercaPerCodice(link head, char k[]){
    link x;
    int flag = 0;

    for (x = head; x != NULL && CODICEgeq(CODICEget(x->val), k); x = x->next)
        if (CODICEeq(CODICEget(x->val), k)){
            flag = 1;
            break;
        }

    if(flag)
        return x;

    else{
        printf("\nCORRISPONDENZA NON TROVATA!!!\n");
        return NULL;
    }
}

//Cancellazione per codice
link sortListDel(link head, char codice[]){
    link x, p;

    //Caso in cui la lista è vuota
    if (head == NULL)
        return NULL;

    //Cancellazione per codice
    for (x=head, p=NULL; x!=NULL && CODICEgeq(codice, CODICEget(x->val));
         p=x, x=x->next){
        if (CODICEeq(CODICEget(x->val),codice)){
            if (x==head)
                head = x->next;
            else
                p->next = x->next;
            stampaNodo(x);
            free(x);
            break;
        }
    }
    return head;
}

//Funzione principale per la cancellazione dei nodi che rientrano tra data1 e data2
link cancellaTraDate(link head){
    link x, p, temp;
    data_di_nascita data1, data2;

    //Informazioni da tastiera
    printf("\nInserisci la prima data nel formato GG/MM/AAAA:");
    scanf("%d/%d/%d", &data1.gg, &data1.mm, &data1.aaaa);
    printf("\nInserisci la seconda data nel formato GG/MM/AAAA:");
    scanf("%d/%d/%d", &data2.gg, &data2.mm, &data2.aaaa);

    //Estrazione e cancellazione delle date trovate
    for(x = head, p = NULL; x != NULL; p = x, x = x->next){
        if(verCancDate(x, data1, data2)){
            temp = x;

            if(x == head)
                head = x->next;
            else
                p->next = x->next;

            printf("Nodo da cancellare: ");
            stampaNodo(x);
            printf("\n");
            free(temp);
        }
    }

    return head;
}

//Iterazione sulla lista per la ricerca di una data compresa tra data1 e data2, ritorno del puntatore all'elemento desiderato
int verCancDate(link x, data_di_nascita data1, data_di_nascita data2){
    int flag = 0;

    if(DATAgreater(DATAget(x->val), data1) >= 0 && DATAgreater(DATAget(x->val), data2) <= 0){
        flag = 1;
    }

    return flag;
}

//Stampa su file
FILE *stampaSuFile(link head, char nomeFile[]){
    link x;
    FILE *fout;

    fout = fopen(nomeFile, "w");

    //Iterazione sulla lista
    for(x = head; x != NULL; x = x->next){
        Item item = x->val;

        //Stampa su file
        fprintf(fout, "%s %s %s", item.codice, item.nome, item.cognome);
        fprintf(fout," %d/%d/%d", item.nascita.gg, item.nascita.mm, item.nascita.aaaa);
        fprintf(fout, " %s %s %d\n", item.via, item. citta, item.cap);
    }

    return fout;
}
