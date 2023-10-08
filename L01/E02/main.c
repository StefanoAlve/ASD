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
int leggiFile(char* nomeFile, sTratta tratte[MAXR]);
int main(void) {
    //Inizializzazione variabili
    char nomeFile[MAXL];
    comando_e comando;
    int nr=0;
    sTratta tratte[MAXL];
    //Apertura file
    printf("Inserisci il nome del file:");
    scanf(" %s", nomeFile);
    nr = leggiFile(nomeFile,tratte);
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

int leggiFile(char *nomeFile, sTratta tratte[MAXR]){
    FILE* fp;
    int i = 0, nr = 0;
    fp = fopen(nomeFile, "r");
    if(fp != NULL){
        printf("Il file contiene: \n");
        fscanf(fp,"%d", &nr);
        while(!feof(fp)){
            fscanf(fp, "%s %s %s", tratte[i].codice_tratta, tratte[i].partenza, tratte[i].destinazione);
            fscanf(fp, "%d/%d/%d", &tratte[i].data[0], &tratte[i].data[1], &tratte[i].data[2]);
            fscanf(fp, "%d:%d:%d", &tratte[i].ora_partenza[0], &tratte[i].ora_partenza[1], &tratte[i].ora_partenza[2]);
            fscanf(fp, "%d:%d:%d", &tratte[i].ora_arrivo[0], &tratte[i].ora_arrivo[1], &tratte[i].ora_arrivo[2]);
            fscanf(fp,"%d", &tratte[i].ritardo);

            printf("%s %s %s ", tratte[i].codice_tratta, tratte[i].partenza, tratte[i].destinazione);
            printf("%d/%d/%d ", tratte[i].data[0], tratte[i].data[1], tratte[i].data[2]);
            printf("%d:%d:%d ", tratte[i].ora_partenza[0], tratte[i].ora_partenza[1], tratte[i].ora_partenza[2]);
            printf("%d:%d:%d ", tratte[i].ora_arrivo[0], tratte[i].ora_arrivo[1], tratte[i].ora_arrivo[2]);
            printf("%d\n", tratte[i].ritardo);
            i++;
        }
    }
    else{
        printf("Errore nell'apertura del file!\n");
    }
}