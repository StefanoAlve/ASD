#include <stdio.h>
#include <string.h>

#define MAXL 100
#define MAXR 30

typedef struct{
    char codice_tratta[MAXL];
    char partenza[MAXL];
    char destinazione[MAXL];
    char data[MAXL];
    char ora_partenza[MAXL];
    char ora_arrivo[MAXL];
    int ritardo;
}sTratta;

typedef enum{r_ordina_data, r_ordina_codice, r_ordina_partenza, r_ordina_arrivo, r_ricerca_partenza_dico,
             r_fine, r_errore} comando_e;

int leggiFile(char* nomeFile, sTratta tratte[]);
comando_e leggiComando(void);
void selezionaDati(int nr, comando_e comando, sTratta tratte[MAXL],int* pfine);
void ordinaData(int nr, sTratta tratte[MAXL]);
void ordinaCodice(int nr, sTratta tratte[MAXL]);
void ordinaPartenza(int nr, sTratta tratte[MAXL]);
void ordinaArrivo(int nr, sTratta tratte[MAXL]);
void ricercaDico(int nr, sTratta tratte[MAXL]);
void stampa(int nr, sTratta tratte[MAXL]);

int main() {
    char nomefile[MAXL];
    int nr;
    sTratta tratte[MAXR];
    comando_e comando;
    int fine = 0, *pfine = NULL;

    pfine = &fine;

    printf("inserire il nome del file ");
    scanf("%s", nomefile);

    nr = leggiFile(nomefile, tratte);

    while(!fine && nr != -1) {
        //Lettura Comando
        comando = leggiComando();
        //Corpo programma
        if (comando != r_errore) {
            selezionaDati(nr, comando, tratte, pfine);
        }
    }

    return 0;
}


int leggiFile(char* nomeFile, sTratta tratte[]) {
    FILE *fp;
    int i = 0, nr = 0;

    fp = fopen(nomeFile, "r");

    if(fp != NULL){
        fscanf(fp,"%d", &nr);
        while(!feof(fp)){
            fscanf(fp, "%s %s %s", tratte[i].codice_tratta, tratte[i].partenza, tratte[i].destinazione);
            fscanf(fp, "%s", tratte[i].data);
            fscanf(fp, "%s", tratte[i].ora_partenza);
            fscanf(fp, "%s", tratte[i].ora_arrivo);
            fscanf(fp,"%d", &tratte[i].ritardo);

            i++;
        }
    }
    else{
        printf("errore nell apertura del file");
        return 1;
    }

    fclose(fp);

    return nr;
}

comando_e leggiComando(void){
    //Inizializzazione variabili
    char comando[MAXL];
    comando_e comandoE;
    //Corpo funzione
    printf("\n-------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\tLISTA COMANDI\n");
    printf("-------------------------------------------------------------------------------------------------------\n\n");
    printf("ordina_data -> ordina le corse per data, in caso di data uguale verranno ordinate per ora\n");
    printf("ordina_codice -> ordina le corse per codice\n");
    printf("ordina_partenza -> ordina le corse secondo il nome della partenza\n");
    printf("ordina_arrivo -> ordina le corse secondo il nome della destinazione\n");
    printf("ricerca_partenza_dico -> esegue la ricerca dicotomica della partenza inserita\n");
    printf("fine -> termina il programma\n\n");
    printf("-------------------------------------------------------------------------------------------------------\n\n");
    printf("Inserisci comando:");
    scanf(" %s", comando);

    if(strcmp("ordina_data", comando) == 0){
        comandoE = 0;
    }
    else if(strcmp("ordina_codice", comando) == 0){
        comandoE = 1;
    }
    else if(strcmp("ordina_partenza",comando) == 0){
        comandoE = 2;
    }
    else if(strcmp("ordina_arrivo",comando) == 0){
        comandoE = 3;
    }
    else if(strcmp("ricerca_partenza_dico",comando) == 0){
        comandoE = 4;
    }
    else if(strcmp("fine", comando) == 0){
        comandoE = 5;
    }
    else{
        printf("\nComando non riconosciuto! Riprova\n");
        comandoE = 6;
    }
    return comandoE;
}

void selezionaDati(int nr, comando_e comando, sTratta tratte[MAXL],int* pfine) {
//r_ordina_data, r_ordina_codice, r_ordina_partenza, r_ordina_arrivo, r_ricerca_partenza_dico,
//             r_fine, r_errore
    switch(comando){
        case r_ordina_data:
            ordinaData(nr, tratte);
            break;
        case r_ordina_codice:
            ordinaCodice(nr, tratte);
            break;
        case r_ordina_partenza:
            ordinaPartenza(nr, tratte);
            break;
        case r_ordina_arrivo:
            ordinaArrivo(nr, tratte);
            break;
        case r_ricerca_partenza_dico:
            ricercaDico(nr, tratte);
            break;
        case r_fine:
            *pfine = 1;
            printf("Programma terminato correttamente!\n");
            break;
    }

}
/*
 void InsertionSort(int A[], int N) {
    int i, j, l=0, r=N-1, x;
    for (i = l+1; i <= r; i++) {
        x = A[i];
        j = i - 1;
        while (j >= l && x < A[j]){
            A[j+1] = A[j];
            j--;
        }
        A[j+1] = x;
    }
 }*/
void ordinaData(int nr, sTratta tratte[MAXL]){
    int i, j, l=0, r = nr-1, inverti;
    sTratta trattaTmp;

    for(i=l+1; i<=r; i++){
        trattaTmp = tratte[i];
        j = i - 1;
        inverti = 1;
        while (j >= l && inverti ) {
            if (strcmp(trattaTmp.data, tratte[j].data) < 0) {
                tratte[j + 1] = tratte[j];
            }
            else if(strcmp(trattaTmp.data, tratte[j].data) == 0 && strcmp(trattaTmp.ora_partenza, tratte[j].ora_partenza) < 0) {
                tratte[j + 1] = tratte[j];
            }
            else if(strcmp(trattaTmp.data, tratte[j].data) == 0 && strcmp(trattaTmp.ora_partenza, tratte[j].ora_partenza) == 0 && strcmp(trattaTmp.ora_arrivo, tratte[j].ora_arrivo) < 0) {
                tratte[j + 1] = tratte[j];
            }
            else
                inverti = 0;


            if (inverti){
                j--;
            }
        }

        tratte[j + 1] = trattaTmp;
    }

    stampa(nr, tratte);
}

void ordinaCodice(int nr, sTratta tratte[MAXL]){
    int i, j, l=0, r = nr-1;
    sTratta trattaTmp;

    for(i=l+1; i<=r; i++){
        trattaTmp = tratte[i];
        j = i - 1;

        while (j >= l && strcmp(trattaTmp.codice_tratta, tratte[j].codice_tratta) < 0) {
                tratte[j + 1] = tratte[j];
                j--;
        }

        tratte[j + 1] = trattaTmp;
    }

    stampa(nr, tratte);
}

void ordinaPartenza(int nr, sTratta tratte[MAXL]){
    int i, j, l=0, r = nr-1;
    sTratta trattaTmp;

    for(i=l+1; i<=r; i++){
        trattaTmp = tratte[i];
        j = i - 1;

        while (j >= l && strcmp(trattaTmp.partenza, tratte[j].partenza) < 0) {
            tratte[j + 1] = tratte[j];
            j--;
        }

        tratte[j + 1] = trattaTmp;
    }

    stampa(nr, tratte);
}

void ordinaArrivo(int nr, sTratta tratte[MAXL]){
    int i, j, l=0, r = nr-1;
    sTratta trattaTmp;

    for(i=l+1; i<=r; i++){
        trattaTmp = tratte[i];
        j = i - 1;

        while (j >= l && strcmp(trattaTmp.destinazione, tratte[j].destinazione) < 0) {
            tratte[j + 1] = tratte[j];
            j--;
        }

        tratte[j + 1] = trattaTmp;
    }

    stampa(nr, tratte);
}

void ricercaDico(int nr, sTratta tratte[MAXL]) {
    ordinaPartenza(nr, tratte);
    int l = 0, r = nr - 1, m, flag = 1, i, j;
    char prtnz[MAXR],str[MAXR];
    FILE *fps;

    printf("scegli la stazione da cercare\n");
    scanf("%s", prtnz);

    while (l <= r && flag && flag != 2) {

        m = (r+l)/2;
        if(strcasecmp(tratte[m].partenza, prtnz) == 0){
            flag = 0;
        }
        else if(strcasecmp(tratte[m].partenza, prtnz) < 0){
            l = m + 1;
        }
        else if(strcasecmp(tratte[m].partenza, prtnz) > 0){
            r = m - 1;
        }
        else{
            printf("errore nella ricerca\n");
            flag = 2;
        }
    }
    if (!flag && m != 0) {
        while (strcasecmp(tratte[m-1].partenza, prtnz) == 0) {
            m--;
        }
    }

    while (strcasecmp(tratte[m].partenza, prtnz) == 0) {
        printf("vuoi stampare a video o in un file? ");
        scanf("%s", str);

        if(strcasecmp(str, "file") == 0){
            fps = fopen("corseScritte.txt", "w");
            while (strcasecmp(tratte[m].partenza, prtnz) == 0) {
                fprintf(fps, "%s %s %s ", tratte[m].codice_tratta, tratte[m].partenza, tratte[m].destinazione);
                fprintf(fps, "%s ", tratte[m].data);
                fprintf(fps, "%s ", tratte[m].ora_partenza);
                fprintf(fps, "%s ", tratte[m].ora_arrivo);
                fprintf(fps, "%d\n", tratte[m].ritardo);
                m++;
            }
            fclose(fps);
        }
        else if(strcasecmp(str, "video") == 0) {
            printf("%s %s %s ", tratte[m].codice_tratta, tratte[m].partenza, tratte[m].destinazione);
            printf("%s ", tratte[m].data);
            printf("%s ", tratte[m].ora_partenza);
            printf("%s ", tratte[m].ora_arrivo);
            printf("%d\n", tratte[m].ritardo);
        }
        else
            printf("errore di comando\n");

        m++;
    }

}


void stampa(int nr, sTratta tratte[MAXL]) {
    int i;
    char str[MAXR];
    FILE *fps;

    printf("vuoi stampare a video o in un file? ");
    scanf("%s", str);

    if(strcasecmp(str, "file") == 0){
        fps = fopen("corseScritte.txt", "w");

        for (i = 0; i < nr; i++){
            fprintf(fps,"%s %s %s ", tratte[i].codice_tratta, tratte[i].partenza, tratte[i].destinazione);
            fprintf(fps,"%s ", tratte[i].data);
            fprintf(fps, "%s ", tratte[i].ora_partenza);
            fprintf(fps,"%s ", tratte[i].ora_arrivo);
            fprintf(fps, "%d\n", tratte[i].ritardo);

        }
        fclose(fps);
    }
    else if(strcasecmp(str, "video") == 0) {
        for (i = 0; i < nr; i++) {
            printf("\n\n%s %s %s ", tratte[i].codice_tratta, tratte[i].partenza, tratte[i].destinazione);
            printf("%s ", tratte[i].data);
            printf("%s ", tratte[i].ora_partenza);
            printf("%s ", tratte[i].ora_arrivo);
            printf("%d\n", tratte[i].ritardo);
        }
    }
    else
        printf("errore di comando");
}