#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxL 50
#define numScelte 6

//Struct per informazioni dal file
typedef struct{
    char codice[5]; //Formato AXXXX dove X è un numero tra 0-9
    char nome[maxL];
    char cognome[maxL];
    char via[maxL];
    char citta[maxL];
    int data_di_nascita;
    int cap;
}Item;

//Tipo puntatore a struct p_nodo
typedef struct p_nodo *link;

//Struct per elemento della lista
 typedef struct p_nodo{
    Item info;
    link next;
}nodo;

link newNode(Item val, link next);
int selezionaComando(char *opzioni[]);

int main(){
    int flag = 1;
    char *opzioni[numScelte]= {
            "aggiungi elemento da tastiera",
            "aggiungi elemento da file",
            "ricerca per codice",
            "cancella elemento per codice",
            "cancella elemento/i tra due date",
            "uscita"
    };

    do{
        int opzione = selezionaComando(opzioni);
        switch(opzione){
            //Aggiungi elemento da tastiera
            case 1:
                break;

            //Aggiungi elemento da file
            case 2:
                break;

            //Ricerca per codice
            case 3:
                break;

            //Cancellazione per codice
            case 4:
                break;

            //Cancellazione tra date
            case 5:
                break;

            //Uscita
            case 6:
                flag = 0;
                break;

            default:
                printf("\n\nComando errato riprova!!\n\n");

        }
    }while(flag);

    return 0;
}

//Creazione di un nuovo nodo
link newNode(Item val, link next){

    link x = (link)malloc(sizeof (struct p_nodo));
    if(x == NULL) return NULL;

    x->info = val;
    x->next = next;
    return x;
}

//Stampa il menu e ritorna un intero corrispondente al comando
int selezionaComando(char *opzioni[]){
    char scelta[20];
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