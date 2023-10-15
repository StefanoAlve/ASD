#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Variabili globali
#define MAXN 30
#define MAXR 1000 // num massimo di tratte possibili

typedef struct{
    char codiceTratta[MAXN];
    char partenza[MAXN];
    char destinazione[MAXN];
    char data[MAXN];
    char o_partenza[MAXN];
    char o_arrivo[MAXN];
    int ritardo;
} struct_tratte;

typedef enum {
    r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_fine, invalid // in caso venga inserito un comando dal menu non valido
} comando_e;

// Funzioni utilizzate
comando_e LeggiComando();
int LeggiFile(char *NomeFile, struct_tratte v_tratte[]);
void selezionaDati(int num_righe, struct_tratte v_tratte[], comando_e comando, int *p_fine);

int main() {
    // definizione e inizializzazione variabili
    char NomeFile[MAXN];
    int fine = 0, *p_fine = &fine; // fine mi dice se dal menu comando è stato scelto di terminare il programma, il puntatore per passarne il valore alle funzioni
    struct_tratte v_tratte[MAXR]; // vettore di struct di ogni tratta
    int num_righe = 0; //serve per sapere quante tratte ci sono nel file
    comando_e comando;

    printf("Inserire il nome file:\n");
    scanf("%s",NomeFile);
    num_righe = LeggiFile(NomeFile,v_tratte);
    while (!fine && num_righe != 0){
        comando = LeggiComando();
        if (comando != invalid){
            selezionaDati(num_righe,v_tratte,comando,p_fine);
        } else {
            printf("Comando non riconosciuto, Riprovare\n");
        }
    }

    return 0;
}

int LeggiFile(char *NomeFile, struct_tratte v_tratte[]){
    FILE *fp;
    int nr = 0;
    int i = 0;

    // lettura del file con allocazione dati in strutture
    fp = fopen(NomeFile,"r");
    if (fp != NULL){ // condizione per verificare la corretta apertura del file
        fscanf(fp,"%d",&nr);
        while (!feof(fp)){ // finchè non arrivo a fine file...
            fscanf(fp,"%s", v_tratte[i].codiceTratta);
            fscanf(fp,"%s", v_tratte[i].partenza);
            fscanf(fp,"%s", v_tratte[i].destinazione);
            fscanf(fp,"%s", v_tratte[i].data);
            fscanf(fp,"%s", v_tratte[i].o_partenza);
            fscanf(fp,"%s", v_tratte[i].o_arrivo);
            i++;
        }
    } else {
        printf("ERRORE: Impossibile aprire il file\n");
    }

    fclose(fp);
    return nr;
}

comando_e LeggiComando(){
    char comando[MAXN];
    comando_e ComandoE;

    // stampa menu comandi
    printf("\nMENU COMANDI\n");
    printf("Date: corse in un intervallo di date\n");
    printf("Partenza: corse partite da una fermata\n");
    printf("Capolinea: corse terminate in una fermata\n");
    printf("Ritardo: corse terminate in ritardo in un intervallo di date\n");
    printf("Ritardo_tot: ritardo complessivo di una determinata tratta\n");
    printf("Fine: per terminare il programma\n\n");
    printf("Inserire il comando da eseguire: ");
    scanf("%s",comando);

    if (strcmp("Date",comando) == 0){
        ComandoE = 0;
    } else if (strcmp("Partenza",comando) == 0){
        ComandoE = 1;
    } else if (strcmp("Capolinea",comando) == 0){
        ComandoE = 2;
    } else if (strcmp("Ritardo",comando) == 0){
        ComandoE = 3;
    } else if (strcmp("Ritardo_tot",comando) == 0){
        ComandoE = 4;
    } else if (strcmp("Fine",comando) == 0){
        ComandoE = 5;
    } else {
        ComandoE = 6;
    }

    return ComandoE;
}

void selezionaDati(int num_righe, struct_tratte v_tratte[], comando_e comando, int *p_fine){
    char data1[MAXN], data2[MAXN], partenza[MAXN], capolinea[MAXN];

    switch (comando){
        case r_date:
            break;
        case r_partenza:
            break;
        case r_capolinea:
            break;
        case r_ritardo:
            break;
        case r_ritardo_tot:
            break;
        case r_fine:
            break;
    }
}


















