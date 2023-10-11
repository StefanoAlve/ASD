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

// Funzioni utilizzate
int LeggiFile(char *NomeFile, struct_tratte v_tratte[]);

int main() {
    // definizione e inizializzazione variabili
    char NomeFile[MAXN];
    struct_tratte v_tratte[MAXR]; // vettore di struct di ogni tratta
    int num_righe; //serve per sapere quante tratte ci sono nel file

    printf("Inserire il nome file:\n");
    scanf("%s",NomeFile);
    num_righe = LeggiFile(NomeFile,v_tratte);
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
        printf("ERRORE: Impossibile aprire il file");
    }

    fclose(fp);
    return nr;
}