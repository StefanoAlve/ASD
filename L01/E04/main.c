#include <stdio.h>
#include <string.h>

#define MAXN 30
#define MAXR 1000

// Variabili globali
typedef struct{
    char codiceTratta[MAXN];
    char partenza[MAXN];
    char destinazione[MAXN];
    char data[MAXN];
    char o_partenza[MAXN];
    char o_arrivo[MAXN];
    int ritardo;
} struct_tratte;

typedef struct{
    struct_tratte *v_DataOraSort[MAXN];
    struct_tratte *v_CodTrattaSort[MAXN];
    struct_tratte *v_PartenzaSort[MAXN];
    struct_tratte *v_DestinazioneSort[MAXN];
} struct_Ordinamenti; // contiene i vettori di puntatori a struttura ordinati secondo il nome

typedef enum {
    stampa_log, sort_data_ora, sort_codTratta, sort_partenza, sort_destinazione, search_tratta_partenza, fine, invalid
} comando_e;

//Funzioni
comando_e LeggiComando();
int LeggiFile(char *NomeFile, struct_tratte v_tratte[]);
void StampaStruct(int i, struct_tratte v_tratte[]);
void StampaVideo(int num_righe, struct_tratte *Vett_ordinato[]); //funzione stampa per i vettori di puntatori a struct ordinati
void StampaVideo1(int num_righe, struct_tratte v_tratte[]); //funzione stampa per solo il vettore di struct originale
void StampaFile(int num_righe, struct_tratte v_tratte[], char NomeFout[]);
void Ordinamenti(struct_Ordinamenti Sorting, int num_righe, struct_tratte v_tratte[]);
void EseguiComando(int num_righe, struct_tratte v_tratte[], struct_Ordinamenti Sorting, comando_e comando, int *p_fine);
void DataOraSort(int num_righe, struct_tratte *v_DataOraSort[]);
void CodTrattaSort(int num_righe, struct_tratte *v_CodTrattaSort[]);
void PartenzaSort(int num_righe, struct_tratte *v_PartenzaSort[]);
void DestinazioneSort(int num_righe, struct_tratte *v_DestinazioneSort[]);

int main() {
    char NomeFile[MAXN];
    int fine = 0, *p_fine = &fine;
    struct_tratte v_tratte[MAXR];
    struct_Ordinamenti Sorting;
    int num_righe;
    comando_e comando;

    printf("Inserire il nome file:\n");
    scanf("%s",NomeFile);
    num_righe = LeggiFile(NomeFile,v_tratte);

    //Ordinamenti
    Ordinamenti(Sorting,num_righe,v_tratte);

    while (!fine && num_righe != 0){
        comando = LeggiComando();
        if (comando != invalid){
            EseguiComando(num_righe,v_tratte,Sorting,comando,p_fine);
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
            fscanf(fp,"%s", v_tratte[i].partenza);
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
    printf("Stampa: stampare i dati a video o su file\n");
    printf("Data_sort: ordinamento corse per data (a parita di data per ora)\n");
    printf("CodTratta_sort: ordinamento corse per codice tratta\n");
    printf("Partenza_sort: ordinamento corse per stazione partenza\n");
    printf("Arrivo_sort: ordinamento corse per stazione di arrivo\n");
    printf("Cerca_tratta: cerca tratte per stazione di partenza\n");
    printf("Fine: per terminare il programma\n\n");
    printf("Inserire il comando da eseguire: ");
    scanf("%s",comando);

    if (strcmp("Stampa",comando) == 0){
        ComandoE = 0;
    } else if (strcmp("Data_sort",comando) == 0){
        ComandoE = 1;
    } else if (strcmp("CodTratta_sort",comando) == 0){
        ComandoE = 2;
    } else if (strcmp("Partenza_sort",comando) == 0){
        ComandoE = 3;
    } else if (strcmp("Arrivo_sort",comando) == 0){
        ComandoE = 4;
    } else if (strcmp("Cerca_tratta",comando) == 0){
        ComandoE = 5;
    } else if (strcmp("Fine",comando) == 0){
        ComandoE = 6;
    } else {
        ComandoE = 7;
    }

    return ComandoE;
}

void StampaStruct(int i, struct_tratte v_tratte[]){
    printf("%s ",v_tratte[i].codiceTratta);
    printf("%s ",v_tratte[i].partenza);
    printf("%s ",v_tratte[i].destinazione);
    printf("%s ",v_tratte[i].data);
    printf("%s ",v_tratte[i].o_partenza);
    printf("%s ",v_tratte[i].o_arrivo);
    printf("%d\n",v_tratte[i].ritardo);
}

void StampaVideo(int num_righe, struct_tratte *Vett_ordinato[]){
    for (int i = 0; i < num_righe; i++){
        printf("%s",Vett_ordinato[i]->codiceTratta);
        printf("%s",Vett_ordinato[i]->partenza);
        printf("%s",Vett_ordinato[i]->destinazione);
        printf("%s",Vett_ordinato[i]->data);
        printf("%s",Vett_ordinato[i]->o_partenza);
        printf("%s",Vett_ordinato[i]->o_arrivo);
        printf("%d\n",Vett_ordinato[i]->ritardo);
    }
}

void StampaVideo1(int num_righe, struct_tratte v_tratte[]){
    for (int i= 0; i < num_righe; i++){
        StampaStruct(i,v_tratte);
    }
}

void StampaFile(int num_righe, struct_tratte v_tratte[], char NomeFout[]){
    FILE *fp;
    int i = 0;
    fp = fopen(NomeFout,"w");
    if(fp != NULL){
        while (i<num_righe){
            fprintf(fp,"%s ",v_tratte[i].codiceTratta);
            fprintf(fp,"%s ",v_tratte[i].partenza);
            fprintf(fp,"%s ",v_tratte[i].destinazione);
            fprintf(fp,"%s ",v_tratte[i].data);
            fprintf(fp,"%s ",v_tratte[i].o_partenza);
            fprintf(fp,"%s ",v_tratte[i].o_arrivo);
            fprintf(fp,"%d\n", v_tratte[i].ritardo);

            i++;
        }
        printf("Stampa avvenuta con successo\n");
    } else {
        printf("ERRORE: Impossibile aprire il file\n");
    }

    fclose(fp);
}

void Ordinamenti(struct_Ordinamenti Sorting, int num_righe, struct_tratte v_tratte[]){
    for (int i = 0; i < num_righe; i++){
        // Inizializzazione dei vettori di puntatori
        Sorting.v_DataOraSort[i] = &v_tratte[i];
        Sorting.v_CodTrattaSort[i] = &v_tratte[i];
        Sorting.v_PartenzaSort[i] = &v_tratte[i];
        Sorting.v_DestinazioneSort[i] = &v_tratte[i];
    }
    DataOraSort(num_righe,Sorting.v_DataOraSort);
    CodTrattaSort(num_righe,Sorting.v_CodTrattaSort);
    PartenzaSort(num_righe,Sorting.v_PartenzaSort);
    DestinazioneSort(num_righe,Sorting.v_DestinazioneSort);
}

void EseguiComando(int num_righe, struct_tratte v_tratte[], struct_Ordinamenti Sorting, comando_e comando, int *p_fine){
    int opzione_stampa, len_partenza;
    char NomeFout[MAXN],stazione_partenza[MAXN];
    switch (comando){
        case stampa_log:
            printf("1: Stampa a video\n2: Stampa su file\nScegli un comando (1 o 2): ");
            scanf("%d", &opzione_stampa);
            if (opzione_stampa == 1){
                StampaVideo1(num_righe,v_tratte);
            } else if (opzione_stampa == 2) {
                printf("Inserire il nome file:\n");
                scanf("%s",NomeFout);
                StampaFile(num_righe,v_tratte,NomeFout);
            } else {
                printf("Opzione non valida\n");
            }
            break;
        case sort_data_ora:
            StampaVideo(num_righe,Sorting.v_DataOraSort);
            break;
        case sort_codTratta:
            StampaVideo(num_righe,Sorting.v_CodTrattaSort);
            break;
        case sort_partenza:
            StampaVideo(num_righe,Sorting.v_PartenzaSort);
            break;
        case sort_destinazione:
            StampaVideo(num_righe,Sorting.v_DestinazioneSort);
            break;
        case search_tratta_partenza:
            printf("Nome stazione partenza (anche parziale): ");
            scanf(" %s",stazione_partenza);
            len_partenza = strlen(stazione_partenza);
            //CercaTrattaPartenza(num_righe,Sorting.v_PartenzaSort,stazione_partenza,len_partenza);
            break;
        case fine:
            *p_fine = 1;
            break;
    }
}

void DataOraSort(int num_righe, struct_tratte *v_DataOraSort[]){

}








