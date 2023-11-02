#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXC 51
//Strutture
typedef struct{
    char codice[6];
    char nome[MAXC];
    char cognome[MAXC];
    char data_di_nascita[11];
    char via[MAXC];
    char citta[MAXC];
    int cap;
}Item;

typedef struct{
    Item val;
    struct node *link;
}node, *link;

typedef enum{r_acquisizione,r_ricerca,r_cancellazione,r_stampa, r_fine, r_errore}comando_e;
typedef enum{i_file, i_tastiera, i_errore}input_e;
//Funzioni
comando_e leggiComando();
input_e leggiInput();
void sceltaComando(comando_e comando);
//newnode
int main(void) {
    //Inizializzazione variabili
    comando_e comando;
    do {
        comando = leggiComando();
        sceltaComando(comando);
    }while(comando != r_fine);
}


comando_e leggiComando(){
    //Inizializzazione variabili
    comando_e comandoE;
    char tmp[MAXC], *comando;
    //Corpo programma
    printf("Inserisci comando:");
    scanf("%s", tmp);
    comando = strdup(tmp);
    if(strcasecmp(comando,"acquisizione") == 0){
        comandoE = r_acquisizione;
    }
    else if(strcasecmp(comando, "ricerca") == 0){
        comandoE = r_ricerca;
    }
    else if(strcasecmp(comando, "cancellazione") == 0){
        comandoE = r_cancellazione;
    }
    else if(strcasecmp(comando, "stampa") == 0){
        comandoE = r_stampa;
    }
    else if(strcasecmp(comando, "fine") == 0){
        comandoE = r_fine;
    }
    else{
        printf("Comando inserito inesistente, riprova!\n");
        comandoE = r_errore;
    }
    free(comando);
    return comandoE;
}
void sceltaComando(comando_e comando){
    input_e input;
    switch (comando){
        case (r_acquisizione):
            do {
                printf("Vuoi acquisire da file o da tastiera?:");
                input = leggiInput();
            }while(input == i_errore); //Finchè l'utente non inserirà un input corretto continuerò a chiedere
            break;
        case (r_ricerca):
            break;
        case (r_cancellazione):
            break;
        case (r_stampa):
            break;
        case (r_fine):
            break;
        case (r_errore):
            break;
    }
}

input_e leggiInput(){
    input_e inputE;
    char tmp[MAXC], *input;
    scanf(" %s", tmp);
    input = strdup(tmp);

    if(strcasecmp(input, "file") == 0){
        inputE = i_file;
    }
    else if(strcasecmp(input, "tastiera") == 0){
        inputE = i_tastiera;
    }
    else{
        printf("Tipo di input inesistente, riprova!\n");
        inputE = i_errore;
    }
    return inputE;
}
    //acquisizione
        //file:
            //leggiFile
            //for
            //acquisisci
        //tastiera:
            //acquisisci
    //ricerca:
        //ricerca
    //cancella:
        //per codice:
            //elimina elemento
        //per date:
            //for
            //elimina elemento
    //stampa:
        //stampa