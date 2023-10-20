#include <stdio.h>
#include <string.h>
#include <ctype.h>

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

typedef enum {
    stampa_log, sort_data_ora, sort_codTratta, sort_partenza, sort_destinazione, search_tratta_partenza, fine, invalid
} comando_e;

// Funzioni
comando_e LeggiComando();
int LeggiFile(char *NomeFile, struct_tratte v_tratte[]);
void StampaStruct(int i, struct_tratte v_tratte[]);
void StampaVideo(int num_righe, struct_tratte v_tratte[]);
void StampaFile(int num_righe, struct_tratte v_tratte[], char NomeFout[]);
void EseguiComando(int num_righe, struct_tratte v_tratte[], comando_e comando, int *p_fine);
void DataOraSort(int num_righe, struct_tratte v_tratte[]);
void CodTrattaSort(int num_righe, struct_tratte v_tratte[]);
void PartenzaSort(int num_righe, struct_tratte v_tratte[]);
void DestinazioneSort(int num_righe, struct_tratte v_tratte[]);
void CercaTrattaPartenza(int num_righe, struct_tratte v_tratte[], char stazione_partenza[], int len_partenza);

int main() {
    char NomeFile[MAXN];
    int fine = 0, *p_fine = &fine;
    struct_tratte v_tratte[MAXR];
    int num_righe;
    comando_e comando;

    printf("Inserire il nome file:\n");
    scanf("%s",NomeFile);
    num_righe = LeggiFile(NomeFile,v_tratte);
    while (!fine && num_righe != 0){
        comando = LeggiComando();
        if (comando != invalid){
            EseguiComando(num_righe,v_tratte,comando,p_fine);
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

void EseguiComando(int num_righe, struct_tratte v_tratte[], comando_e comando, int *p_fine){
    int opzione_stampa, len_partenza;
    char NomeFout[MAXN],stazione_partenza[MAXN];
    switch (comando){
        case stampa_log:
            printf("1: Stampa a video\n2: Stampa su file\nScegli un comando (1 o 2): ");
            scanf("%d", &opzione_stampa);
            if (opzione_stampa == 1){
                StampaVideo(num_righe,v_tratte);
            } else if (opzione_stampa == 2) {
                printf("Inserire il nome file:\n");
                scanf("%s",NomeFout);
                StampaFile(num_righe,v_tratte,NomeFout);
            } else {
                printf("Opzione non valida\n");
            }
            break;
        case sort_data_ora:
            DataOraSort(num_righe,v_tratte);
            StampaVideo(num_righe,v_tratte);
            break;
        case sort_codTratta:
            CodTrattaSort(num_righe,v_tratte);
            StampaVideo(num_righe,v_tratte);
            break;
        case sort_partenza:
            PartenzaSort(num_righe,v_tratte);
            StampaVideo(num_righe,v_tratte);
            break;
        case sort_destinazione:
            DestinazioneSort(num_righe,v_tratte);
            StampaVideo(num_righe,v_tratte);
            break;
        case search_tratta_partenza:
            printf("Nome stazione partenza (anche parziale): ");
            scanf(" %s",stazione_partenza);
            len_partenza = strlen(stazione_partenza);
            CercaTrattaPartenza(num_righe,v_tratte,stazione_partenza,len_partenza);
            break;
        case fine:
            *p_fine = 1;
            break;
    }
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

void StampaVideo(int num_righe, struct_tratte v_tratte[]){
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

void DataOraSort(int num_righe, struct_tratte v_tratte[]){
    // Algoritmo di ordinamento: Insertion sort
    int i,j;
    struct_tratte tratta;

    for (i = 1; i < num_righe; i++) {
        tratta = v_tratte[i];
        j = i - 1;

        while (j >= 0 && strcmp(tratta.data, v_tratte[j].data) < 0) {
            v_tratte[j + 1] = v_tratte[j];
            j--;
        }
        if (strcmp(tratta.data, v_tratte[j].data) == 0){
            while (j >= 0 && strcmp(tratta.o_partenza, v_tratte[j].o_partenza) < 0) {
                v_tratte[j + 1] = v_tratte[j];
                j--;
            }
        }
        v_tratte[j + 1] = tratta;
    }
}

void CodTrattaSort(int num_righe, struct_tratte v_tratte[]){
    // Algoritmo di ordinamento: Insertion sort
    int i,j;
    struct_tratte tratta;

    for (i = 1; i < num_righe; i++) {
        tratta = v_tratte[i];
        j = i - 1;

        while (j >= 0 && strcmp(tratta.codiceTratta, v_tratte[j].codiceTratta) < 0) {
            v_tratte[j + 1] = v_tratte[j];
            j--;
        }
        v_tratte[j + 1] = tratta;
    }
}

void PartenzaSort(int num_righe, struct_tratte v_tratte[]){
    // Algoritmo di ordinamento: Insertion sort
    int i,j;
    struct_tratte tratta;

    for (i = 1; i < num_righe; i++) {
        tratta = v_tratte[i];
        j = i - 1;

        while (j >= 0 && strcmp(tratta.partenza, v_tratte[j].partenza) < 0) {
            v_tratte[j + 1] = v_tratte[j];
            j--;
        }
        v_tratte[j + 1] = tratta;
    }
}

void DestinazioneSort(int num_righe, struct_tratte v_tratte[]){
    // Algoritmo di ordinamento: Insertion sort
    int i,j;
    struct_tratte tratta;

    for (i = 1; i < num_righe; i++) {
        tratta = v_tratte[i];
        j = i - 1;

        while (j >= 0 && strcmp(tratta.destinazione, v_tratte[j].destinazione) < 0) {
            v_tratte[j + 1] = v_tratte[j];
            j--;
        }
        v_tratte[j + 1] = tratta;
    }
}

void CercaTrattaPartenza(int num_righe, struct_tratte v_tratte[], char stazione_partenza[], int len_partenza){
    //Ricerca binaria dicotomica
    int trovato = 0, l = 0, r = num_righe-1, m;

    PartenzaSort(num_righe,v_tratte);
    while (l <= r && !trovato){
        m = (l+r)/2;
        if(strncasecmp(v_tratte[m].partenza,stazione_partenza,len_partenza) == 0){
            trovato = 1;
        } else if (strncasecmp(v_tratte[m].partenza,stazione_partenza,len_partenza) < 0){
            l = m+1;
        } else {
            r = m-1;
        }
    }
    if (trovato == 0){
        printf("Nessuna corsa trovata\n");
    } else {
        StampaStruct(m,v_tratte);
    }
    //Ricerca lineare nei due sottovettori per ulteriori corrispondenze

    while (l >= 0 && (strncasecmp(v_tratte[l].partenza,stazione_partenza,len_partenza) == 0)){
        StampaStruct(l,v_tratte);
        l--;
    }

    while (r < num_righe && (strncasecmp(v_tratte[r].partenza,stazione_partenza,len_partenza) == 0)){
        StampaStruct(r,v_tratte);
        r++;
    }
}
