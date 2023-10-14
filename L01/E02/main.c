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
    r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_fine, invalid // in caso venga inserito un valore dal menu non valido
} comando_e; // comando_e è un tipo di dato

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