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

//Funzioni
comando_e leggiComando();
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
    switch (comando){
        case (r_acquisizione):
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