#include <stdio.h>
#include <string.h>
#define MAXL 30
#define MAXR 1000
//Variabili globali
typedef enum{r_date, r_partenza, r_capolinea, r_ritardo,
             r_ritardo_tot, r_fine, r_errore}comando_e;
typedef struct{
    char codice_tratta[MAXL];
    char partenza[MAXL];
    char destinazione[MAXL];
    int data[3];
    int ora_partenza[3];
    int ora_arrivo[3];
    int ritardo;
}sTratta;

//Funzioni
comando_e leggiComando(void);
int leggiFile(char *nomeFile, sTratta tratte[MAXR]);
int main(void) {
    //Inizializzazione variabili
    comando_e comando;
    int nr=0;
    sTratta tratte[MAXL];
    char nomeFile[MAXR];
    //Apertura file
    printf("Inserisci il nome del file:");
    scanf(" %s", nomeFile);
    //nr = leggiFile(nomeFile, tratte);
    //Lettura Comando
    comando = leggiComando();
    printf("Il comando vale: %d", comando);
    //Corpo programma
    //Chiusura file
    return 0;
}

comando_e leggiComando(void){
    //Inizializzazione variabili
    char comando[MAXL];
    comando_e comandoE;

    //Corpo funzione
    printf("Inserisci comando:");
    scanf(" %s", comando);
    //r_date, r_partenza, r_capolinea, r_ritardo,
    //             r_ritardo_tot, r_fine, r_errore
    if(strcmp("date", comando) == 0){
        comandoE = 0;
    }
    else if(strcmp("partenza", comando) == 0){
        comandoE = 1;
    }
    else if(strcmp("capolinea", comando) == 0){
        comandoE = 2;
    }
    else if(strcmp("ritardo", comando) == 0){
        comandoE = 3;
    }
    else if(strcmp("ritardo_tot", comando) == 0){
        comandoE = 4;
    }
    else if(strcmp("fine", comando) == 0){
        comandoE = 5;
    }
    else{
        printf("\nComando non riconosciuto!\n");
        comandoE = 6;
    }
    return comandoE;
}

