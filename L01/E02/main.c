#include <stdio.h>
#include <string.h>

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

// Funzioni utilizzateEseguiComando(
comando_e LeggiComando();
int LeggiFile(char *NomeFile, struct_tratte v_tratte[]);
void selezionaDati(int num_righe, struct_tratte v_tratte[], comando_e comando, int *p_fine);
void ElencaCorsePerDate(char data1[], char data2[], int num_righe, struct_tratte v_tratte[]);
void ElencaCorsePerPartenza(char partenza[], int num_righe, struct_tratte v_tratte[]);
void ElencaCorsePerCapolinea(char capolinea[], int num_righe, struct_tratte v_tratte[]);
void ElencaCorseRitardoPerDate(char data1[], char data2[], int num_righe, struct_tratte v_tratte[]);
void CalcoloRitardoTot(char codTratta[], int num_righe, struct_tratte v_tratte[]);

int main() {
    // definizione e inizializzazione variabili
    char NomeFile[MAXN];
    int fine = 0, *p_fine = &fine; // fine mi dice se dal menu comando è stato scelto di terminare il programma, il puntatore per passarne il valore alle funzioni
    struct_tratte v_tratte[MAXR]; // vettore di struct di ogni tratta
    int num_righe; //serve per sapere quante tratte ci sono nel file
    comando_e comando;

    printf("Inserire il nome file:\n"); fflush(stdout);
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
    printf("\nProgramma terminato Correttamente!\n");

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
            fscanf(fp,"%s",v_tratte[i].partenza);
            fscanf(fp,"%s", v_tratte[i].destinazione);
            fscanf(fp,"%s", v_tratte[i].data);
            fscanf(fp,"%s", v_tratte[i].o_partenza);
            fscanf(fp,"%s", v_tratte[i].o_arrivo);
            fscanf(fp,"%d", &v_tratte[i].ritardo);

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
    printf("Inserire il comando da eseguire (Scrivere la parola come compare sul menu): ");
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
    char data1[MAXN], data2[MAXN], partenza[MAXN], capolinea[MAXN], codTratta[MAXN];

    switch (comando){
        case r_date:
            printf("Inserire la prima data (aaaa/mm/gg) :\n");
            scanf("%s", data1);
            printf("Inserire la seconda data (aaaa/mm/gg) :\n");
            scanf("%s", data2);
            ElencaCorsePerDate(data1,data2,num_righe,v_tratte);
            break;
        case r_partenza:
            printf("Inserire la fermata di partenza:\n");
            scanf("%s",partenza);
            ElencaCorsePerPartenza(partenza,num_righe,v_tratte);
            break;
        case r_capolinea:
            printf("Inserire la fermata capolinea:\n");
            scanf("%s",capolinea);
            ElencaCorsePerCapolinea(capolinea,num_righe,v_tratte);
            break;
        case r_ritardo:
            printf("Inserire la prima data (aaaa/mm/gg) :\n");
            scanf("%s", data1);
            printf("Inserire la seconda data (aaaa/mm/gg) :\n");
            scanf("%s", data2);
            ElencaCorseRitardoPerDate(data1,data2,num_righe,v_tratte);
            break;
        case r_ritardo_tot:
            printf("Inserire il codice della tratta:\n");
            scanf("%s",codTratta);
            CalcoloRitardoTot(codTratta,num_righe,v_tratte);
            break;
        case r_fine:
            *p_fine = 1;
            break;
    }
}

void ElencaCorsePerDate(char data1[], char data2[], int num_righe, struct_tratte v_tratte[]){
    int i, no_corse = 1;
    printf("\nCorse avvenute tra %s e %s\n", data1,data2);
    for (i = 0; i < num_righe; i++){
        if (strcmp(v_tratte[i].data,data1) >= 0 && strcmp(v_tratte[i].data,data2) <= 0){
            printf("%s %s %s del %s; partenza: %s , arrivo: %s\n",v_tratte[i].codiceTratta,v_tratte[i].partenza,v_tratte[i].destinazione,v_tratte[i].data,v_tratte[i].o_partenza,v_tratte[i].o_arrivo);
            no_corse = 0;
        }
    }
    if (no_corse){
        printf("Non ci sono corse corrispondenti\n");
    }
}

void ElencaCorsePerPartenza(char partenza[], int num_righe, struct_tratte v_tratte[]){
    int i, no_corse = 1;
    printf("Corse partite da %s:\n",partenza);
    for (i = 0; i < num_righe; i++){
        if (strcasecmp(v_tratte[i].partenza,partenza) == 0){
            printf("%s da %s a %s del %s\n",v_tratte[i].codiceTratta,v_tratte[i].partenza,v_tratte[i].destinazione,v_tratte[i].data);
            no_corse = 0;
        }
    }
    if (no_corse){
        printf("Non ci sono corse corrispondenti\n");
    }
}

void ElencaCorsePerCapolinea(char capolinea[], int num_righe, struct_tratte v_tratte[]){
    int i, no_corse = 1;
    printf("Corse terminate a %s:\n",capolinea);
    for (i = 0; i < num_righe; i++){
        if (strcasecmp(v_tratte[i].destinazione,capolinea) == 0){
            printf("%s da %s a %s del %s\n",v_tratte[i].codiceTratta,v_tratte[i].partenza,v_tratte[i].destinazione,v_tratte[i].data);
            no_corse = 0;
        }
    }
    if (no_corse){
        printf("Non ci sono corse corrispondenti\n");
    }
}

void ElencaCorseRitardoPerDate(char data1[], char data2[], int num_righe, struct_tratte v_tratte[]){
    int i, no_corse = 1;
    printf("\nCorse con ritardo avvenute tra %s e %s\n", data1,data2);
    for (i = 0; i < num_righe; i++){
        if (strcmp(v_tratte[i].data,data1) >= 0 && strcmp(v_tratte[i].data,data2) <= 0 && v_tratte[i].ritardo != 0){
            printf("%s %s %s del %s; partenza: %s , arrivo: %s , ritardo: %d\n",v_tratte[i].codiceTratta,v_tratte[i].partenza,v_tratte[i].destinazione,v_tratte[i].data,v_tratte[i].o_partenza,v_tratte[i].o_arrivo,v_tratte[i].ritardo);
            no_corse = 0;
        }
    }
    if (no_corse){
        printf("Non ci sono corse corrispondenti\n");
    }
}

void CalcoloRitardoTot(char codTratta[], int num_righe, struct_tratte v_tratte[]){
    int i, no_corse = 1, ritardo_tot = 0;
    printf("Ritardo accumulato dalla tratta %s:\n",codTratta);
    for (i = 0; i < num_righe; i++){
        if (strcmp(v_tratte[i].codiceTratta,codTratta) == 0 && v_tratte[i].ritardo != 0 != 0){
            ritardo_tot = ritardo_tot + v_tratte[i].ritardo;
            no_corse = 0;
        }
    }
    if (no_corse){
        printf("Non ci sono corse corrispondenti\n");
    } else {
        printf("%d",ritardo_tot);
    }
}










