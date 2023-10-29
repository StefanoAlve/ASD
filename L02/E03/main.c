#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 30

//Variabili globlali

typedef struct{
    char *codiceTratta;
    char *partenza;
    char *destinazione;
    char *data;
    char *o_partenza;
    char *o_arrivo;
    int ritardo;
} struct_tratte;

typedef struct{
    struct_tratte **v_DataOraSort;
    struct_tratte **v_CodTrattaSort;
    struct_tratte **v_PartenzaSort;
    struct_tratte **v_DestinazioneSort;
} struct_Ordinamenti; // contiene i vettori di puntatori a struttura ordinati secondo il nome

typedef enum {
    stampa_log, sort_data_ora, sort_codTratta, sort_partenza, sort_destinazione, search_tratta_partenza, fine, invalid
} comando_e;

//Funzioni
int LeggiFile(struct_tratte **v_tratte);

int main() {
    int fine = 0, *p_fine=&fine;
    struct_tratte *v_tratte;
    struct_Ordinamenti Sorting;
    int num_righe;
    comando_e comando;

    num_righe = LeggiFile(&v_tratte);

    //Ordinamenti
    //Ordinamenti(&Sorting,num_righe,v_tratte);

    return 0;
}

int LeggiFile(struct_tratte **v_tratte){
    FILE *fp;
    char NomeFile[MAXN], temp[MAXN];
    struct_tratte *Tratte;
    int nr = 0;
    int i = 0;

    printf("Inserire il nome file:\n");
    scanf("%s",NomeFile);

    // lettura del file con allocazione dati in strutture
    fp = fopen(NomeFile,"r");

    if (fp != NULL){ // condizione per verificare la corretta apertura del file
        fscanf(fp,"%d",&nr);

        //Allocazione dinamica vettore di struct
        Tratte = (struct_tratte *)malloc(nr * sizeof(struct_tratte));
        if (v_tratte == NULL) exit(1);

        while (!feof(fp)){ // finchè non arrivo a fine file...
            //strdup copia la stringa e restituisce il puntatore allocandola dinamicamente
            fscanf(fp,"%s", temp); Tratte[i].codiceTratta = strdup(temp);
            fscanf(fp,"%s", temp); Tratte[i].partenza = strdup(temp);
            fscanf(fp,"%s", temp); Tratte[i].destinazione = strdup(temp);
            fscanf(fp,"%s", temp); Tratte[i].data = strdup(temp);
            fscanf(fp,"%s", temp); Tratte[i].o_partenza = strdup(temp);
            fscanf(fp,"%s", temp); Tratte[i].o_arrivo = strdup(temp);
            fscanf(fp,"%d",&Tratte[i].ritardo);

            i++;
        }
        *v_tratte = Tratte; //copia del vettore di struct in v_tratte, così da poterlo usare al di fuori della funzione
    } else {
        printf("ERRORE: Impossibile aprire il file\n");
    }

    fclose(fp);
    return nr;
}
