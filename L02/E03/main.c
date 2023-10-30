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
    stampa_log, sort_data_ora, sort_codTratta, sort_partenza, sort_destinazione, search_tratta_partenza, leggi_file, fine, invalid
} comando_e;

//Funzioni
comando_e LeggiComando();
int LeggiFile(struct_tratte **v_tratte);
void StampaStruct(int i, struct_tratte *v_tratte[]);
void EseguiComando(int num_righe, struct_tratte v_tratte[], struct_Ordinamenti *p_Sorting, comando_e comando, int *p_fine);
void StampaVideo(int num_righe, struct_tratte *Vett_ordinato[]); //funzione stampa per i vettori di puntatori a struct ordinati
void StampaVideo1(int num_righe, struct_tratte v_tratte[]); //funzione stampa per solo il vettore di struct originale
void StampaFile(int num_righe, struct_tratte v_tratte[], char NomeFout[]);
void Ordinamenti(struct_Ordinamenti *p_Sorting, int num_righe, struct_tratte v_tratte[]);
void DataOraSort(int num_righe, struct_tratte *v_DataOraSort[]);
void CodTrattaSort(int num_righe, struct_tratte *v_CodTrattaSort[]);
void PartenzaSort(int num_righe, struct_tratte *v_PartenzaSort[]);
void DestinazioneSort(int num_righe, struct_tratte *v_DestinazioneSort[]);
void CercaTrattaPartenza(int num_righe, struct_tratte *v_PartenzaSort[], char stazione_partenza[], int len_partenza);
void DeallocOrdinamenti(struct_Ordinamenti *p_Sorting);
void DeallocVettTratte(struct_tratte *v_tratte);

int main() {
    int fine = 0, *p_fine=&fine;
    struct_tratte *v_tratte;
    struct_Ordinamenti Sorting;
    int num_righe;
    comando_e comando;

    num_righe = LeggiFile(&v_tratte);

    //Ordinamenti
    Ordinamenti(&Sorting,num_righe,v_tratte);

    while (!fine && num_righe != 0){
        comando = LeggiComando();
        if (comando != invalid){
            EseguiComando(num_righe,v_tratte,&Sorting,comando,p_fine);
        } else {
            printf("Comando non riconosciuto, Riprovare\n");
        }
    }
    DeallocOrdinamenti(&Sorting);
    DeallocVettTratte(v_tratte);
    printf("\nProgramma terminato Correttamente!\n");

    return 0;
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
    printf("Leggi_file: lettura dati del file in input con allocazione dinamica\n");
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
    } else if (strcmp("Cerca_tratta",comando) == 0) {
        ComandoE = 5;
    } else if (strcmp("Leggi_file",comando) == 0){
        ComandoE = 6;
    } else if (strcmp("Fine",comando) == 0){
        ComandoE = 7;
    } else {
        ComandoE = 8;
    }

    return ComandoE;
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

void StampaStruct(int i, struct_tratte *v_tratte[]) {
    printf("%s ", v_tratte[i]->codiceTratta);
    printf("%s ", v_tratte[i]->partenza);
    printf("%s ", v_tratte[i]->destinazione);
    printf("%s ", v_tratte[i]->data);
    printf("%s ", v_tratte[i]->o_partenza);
    printf("%s ", v_tratte[i]->o_arrivo);
    printf("%d\n", v_tratte[i]->ritardo);
}

void EseguiComando(int num_righe, struct_tratte v_tratte[], struct_Ordinamenti *p_Sorting, comando_e comando, int *p_fine){
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
            StampaVideo(num_righe,p_Sorting -> v_DataOraSort);
            break;
        case sort_codTratta:
            StampaVideo(num_righe,p_Sorting -> v_CodTrattaSort);
            break;
        case sort_partenza:
            StampaVideo(num_righe,p_Sorting -> v_PartenzaSort);
            break;
        case sort_destinazione:
            StampaVideo(num_righe,p_Sorting -> v_DestinazioneSort);
            break;
        case search_tratta_partenza:
            printf("Nome stazione partenza (anche parziale): ");
            scanf(" %s",stazione_partenza);
            printf("\n");
            len_partenza = strlen(stazione_partenza);
            CercaTrattaPartenza(num_righe,p_Sorting -> v_PartenzaSort,stazione_partenza,len_partenza);
            break;
        case leggi_file:
            //Deallocazione dati
            DeallocOrdinamenti(p_Sorting);
            DeallocVettTratte(v_tratte);
            //Lettura nuovo file e nuova allocazione
            num_righe = LeggiFile(&v_tratte);
            //Ordinamenti sui nuovi dati
            Ordinamenti(p_Sorting,num_righe,v_tratte);
            break;
        case fine:
            *p_fine = 1;
            break;
    }
}

void StampaVideo1(int num_righe, struct_tratte v_tratte[]){
    for (int i= 0; i < num_righe; i++){
        printf("%s ",v_tratte[i].codiceTratta);
        printf("%s ",v_tratte[i].partenza);
        printf("%s ",v_tratte[i].destinazione);
        printf("%s ",v_tratte[i].data);
        printf("%s ",v_tratte[i].o_partenza);
        printf("%s ",v_tratte[i].o_arrivo);
        printf("%d\n",v_tratte[i].ritardo);
    }
}

void StampaVideo(int num_righe, struct_tratte *Vett_ordinato[]){
    for (int i = 0; i < num_righe; i++){
        printf("%s %s %s %s %s %s %d\n", Vett_ordinato[i] -> codiceTratta, Vett_ordinato[i] -> partenza, Vett_ordinato[i] -> destinazione, Vett_ordinato[i] -> data, Vett_ordinato[i] -> o_partenza, Vett_ordinato[i] -> o_arrivo, Vett_ordinato[i] -> ritardo);
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

void Ordinamenti(struct_Ordinamenti *p_Sorting, int num_righe, struct_tratte v_tratte[]) {
    //Allocazione dinamica vettori di puntatori a struct per gli ordinamenti
    p_Sorting->v_DataOraSort = (struct_tratte **) malloc(num_righe * sizeof(struct_tratte *));
    p_Sorting->v_CodTrattaSort = (struct_tratte **) malloc(num_righe * sizeof(struct_tratte *));
    p_Sorting->v_PartenzaSort = (struct_tratte **) malloc(num_righe * sizeof(struct_tratte *));
    p_Sorting->v_DestinazioneSort = (struct_tratte **) malloc(num_righe * sizeof(struct_tratte *));

    if (p_Sorting->v_DataOraSort == NULL && p_Sorting->v_CodTrattaSort == NULL && p_Sorting->v_PartenzaSort == NULL &&
        p_Sorting->v_DestinazioneSort == NULL)
        exit(1);
    for (int i = 0; i < num_righe; i++){
        // Inizializzazione dei vettori di puntatori
        p_Sorting -> v_DataOraSort[i] = &v_tratte[i];
        p_Sorting -> v_CodTrattaSort[i] = &v_tratte[i];
        p_Sorting -> v_PartenzaSort[i] = &v_tratte[i];
        p_Sorting -> v_DestinazioneSort[i] = &v_tratte[i];
    }

    DataOraSort(num_righe,p_Sorting -> v_DataOraSort);
    CodTrattaSort(num_righe,p_Sorting -> v_CodTrattaSort);
    PartenzaSort(num_righe,p_Sorting -> v_PartenzaSort);
    DestinazioneSort(num_righe,p_Sorting -> v_DestinazioneSort);
}

void DataOraSort(int num_righe, struct_tratte *v_DataOraSort[]){
    int i,j;
    struct_tratte *p_tratta;

    for (i = 1; i < num_righe; i++){
        p_tratta = v_DataOraSort[i];
        j = i - 1;

        while (j >= 0 && (
                strcmp(p_tratta->data, v_DataOraSort[j]->data) < 0 ||
                (strcmp(p_tratta->data, v_DataOraSort[j]->data) == 0 && strcmp(p_tratta->o_partenza, v_DataOraSort[j]->o_partenza) < 0))) {
            v_DataOraSort[j + 1] = v_DataOraSort[j];
            j--;
        }
        v_DataOraSort[j + 1] = p_tratta;
    }

}

void CodTrattaSort(int num_righe, struct_tratte *v_CodTrattaSort[]){
    int i,j;
    struct_tratte *p_tratta;

    for (i = 1; i < num_righe; i++) {
        p_tratta = v_CodTrattaSort[i];
        j = i - 1;

        while (j >= 0 && strcasecmp(p_tratta -> codiceTratta, v_CodTrattaSort[j] -> codiceTratta) < 0) {
            v_CodTrattaSort[j + 1] = v_CodTrattaSort[j];
            j--;
        }
        v_CodTrattaSort[j + 1] = p_tratta;
    }
}

void PartenzaSort(int num_righe, struct_tratte *v_PartenzaSort[]){
    int i,j;
    struct_tratte *p_tratta;

    for (i = 1; i < num_righe; i++) {
        p_tratta = v_PartenzaSort[i];
        j = i - 1;

        while (j >= 0 && strcasecmp(p_tratta -> partenza, v_PartenzaSort[j] -> partenza) < 0) {
            v_PartenzaSort[j + 1] = v_PartenzaSort[j];
            j--;
        }
        v_PartenzaSort[j + 1] = p_tratta;
    }
}

void DestinazioneSort(int num_righe, struct_tratte *v_DestinazioneSort[]){
    int i,j;
    struct_tratte *p_tratta;

    for (i = 1; i < num_righe; i++) {
        p_tratta = v_DestinazioneSort[i];
        j = i - 1;

        while (j >= 0 && strcasecmp(p_tratta -> destinazione, v_DestinazioneSort[j] -> destinazione) < 0) {
            v_DestinazioneSort[j + 1] = v_DestinazioneSort[j];
            j--;
        }
        v_DestinazioneSort[j + 1] = p_tratta;
    }
}

void CercaTrattaPartenza(int num_righe, struct_tratte *v_PartenzaSort[], char stazione_partenza[], int len_partenza){
    int trovato = 0, l = 0, r = num_righe-1, m;

    while (l <= r && !trovato){
        m = (l+r)/2;
        if(strncasecmp(v_PartenzaSort[m] -> partenza,stazione_partenza,len_partenza) == 0){
            trovato = 1;
        } else if (strncasecmp(v_PartenzaSort[m] -> partenza,stazione_partenza,len_partenza) < 0){
            l = m+1;
        } else {
            r = m-1;
        }
    }
    if (trovato == 0){
        printf("Nessuna corsa trovata\n");
    } else {
        StampaStruct(m,v_PartenzaSort);
    }
    //Ricerca lineare nei due sottovettori per ulteriori corrispondenze
    int i = m-1;
    while (i >= 0 && (strncasecmp(v_PartenzaSort[i] -> partenza,stazione_partenza,len_partenza) == 0)){
        StampaStruct(i,v_PartenzaSort);
        i--;
    }
    i = m+1;
    while (i < num_righe && (strncasecmp(v_PartenzaSort[i] -> partenza,stazione_partenza,len_partenza) == 0)){
        StampaStruct(i,v_PartenzaSort);
        i++;
    }
}

void DeallocOrdinamenti(struct_Ordinamenti *p_Sorting){
    if (p_Sorting != NULL){
        free(p_Sorting ->v_DataOraSort);
        free(p_Sorting ->v_CodTrattaSort);
        free(p_Sorting ->v_PartenzaSort);
        free(p_Sorting ->v_DestinazioneSort);
    }
}

void DeallocVettTratte(struct_tratte *v_tratte){
    free(v_tratte->codiceTratta);
    free(v_tratte->partenza);
    free(v_tratte->destinazione);
    free(v_tratte->data);
    free(v_tratte->o_partenza);
    free(v_tratte->o_arrivo);
    free(v_tratte);
}