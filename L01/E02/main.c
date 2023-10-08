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
    char data[MAXL];
    char ora_partenza[MAXL];
    char ora_arrivo[MAXL];
    int ritardo;
}sTratta;

//Funzioni
comando_e leggiComando(void);
int leggiFile(char* nomeFile, sTratta tratte[MAXR]);
void selezionaDati(int nr, comando_e comando, sTratta tratte[MAXR], int *pfine);
void elencaCorseDate(sTratta tratte[MAXR], char datai[MAXL], char dataf[MAXL], int nr);
void elencaCorsePartenza(sTratta tratte[MAXR], char partenza[MAXL], int nr);
void elencaCorseCapolinea(sTratta tratte[MAXR], char capolinea[MAXL], int nr);
void elencaRitardoCompl(sTratta tratte[MAXR], char codiceTratta[MAXL], int nr);
int main(void) {
    //Inizializzazione variabili
    char nomeFile[MAXL];
    comando_e comando;
    int nr, *pfine = NULL, fine = 0;
    sTratta tratte[MAXL];
    pfine = &fine;
    //Apertura file
    printf("Inserisci il nome del file:");
    scanf(" %s", nomeFile);
    nr = leggiFile(nomeFile,tratte);

    while(!fine) {
        //Lettura Comando
        comando = leggiComando();
        printf("Il comando vale: %d", comando);
        //Corpo programma
        if (comando != r_errore) {
            selezionaDati(nr, comando, tratte, pfine);
        } else {
            return 1;
        }
    }
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
            fscanf(fp, "%s", tratte[i].data);
            fscanf(fp, "%s", tratte[i].ora_partenza);
            fscanf(fp, "%s", tratte[i].ora_arrivo);
            fscanf(fp,"%d", &tratte[i].ritardo);

            printf("%s %s %s ", tratte[i].codice_tratta, tratte[i].partenza, tratte[i].destinazione);
            printf("%d/%d/%d ", tratte[i].data[0], tratte[i].data[1], tratte[i].data[2]);
            printf("%d:%d:%d ", tratte[i].ora_partenza[0], tratte[i].ora_partenza[1], tratte[i].ora_partenza[2]);
            printf("%d:%d:%d ", tratte[i].ora_arrivo[0], tratte[i].ora_arrivo[1], tratte[i].ora_arrivo[2]);
            printf("%d\n", tratte[i].ritardo);
            i++;
        }
        //Chiusura file
        fclose(fp);
    }
    else{
        printf("Errore nell'apertura del file!\n");
    }
    return nr;
}

void selezionaDati(int nr, comando_e comando, sTratta tratte[MAXR], int *pfine){
    //Inizializzazione variabili
    char partenza[MAXL], capolinea[MAXL], codiceTratta[MAXL], datai[MAXL], dataf[MAXL];
    switch(comando){
        case r_date:
            printf("\nInserisci la data da cui iniziare la ricerca nel formato aaaa/mm/gg: ");
            scanf("%s", datai);
            printf("\nInserisci la data in cui terminare la ricerca nel formato aaaa/mm/gg: ");
            scanf("%s", dataf);
            elencaCorseDate(tratte, datai, dataf, nr);
            break;
        case r_partenza:
            printf("\nInserire nome fermata di partenza: ");
            scanf("%s",partenza);
            elencaCorsePartenza(tratte, partenza, nr);
            break;
        case r_capolinea:
            printf("\nInserire nome capolinea: ");
            scanf("%s",capolinea);
            elencaCorseCapolinea(tratte, capolinea, nr);
            break;
        case r_ritardo:
            printf("\nInserisci la data da cui iniziare la ricerca nel formato aaaa/mm/gg: ");
            scanf("%s", datai);
            printf("\nInserisci la data in cui terminare la ricerca nel formato aaaa/mm/gg: ");
            scanf("%s", dataf);
            elencaCorseRitardo(tratte, datai, dataf, nr);
            break;
        case r_ritardo_tot:
            printf("\nInserire codice di tratta: ");
            scanf("%s", codiceTratta);
            elencaRitardoCompl(tratte, codiceTratta, nr);
            break;
        case r_fine:
            *pfine = 1;
            break;
    }
}


void elencaRitardoCompl(sTratta tratte[MAXR], char codiceTratta[MAXL], int nr){
    int ritardo_tot = 0;
    for(int i = 0; i < nr; i++){
        if(strcmp(tratte[i].codice_tratta, codiceTratta) == 0){
            ritardo_tot += tratte[i].ritardo;
        }
    }
    printf("Il ritardo complessivo delle corse con codice di tratta %s vale: %d minuti\n", codiceTratta,ritardo_tot);
}

void elencaCorseCapolinea(sTratta tratte[MAXR], char capolinea[MAXL], int nr){
    printf("Le tratte che hanno come capolinea %s sono:\n", capolinea);
    for(int i = 0; i < nr; i++){
        if(strcmp(tratte[i].destinazione, capolinea) == 0){
            printf("%s - %s\n", tratte[i].partenza, tratte[i].destinazione);
        }
    }
}

void elencaCorsePartenza(sTratta tratte[MAXR], char partenza[MAXL], int nr){
    printf("Le tratte che sono partite da %s sono:\n", partenza);
    for(int i = 0; i < nr; i++){
        if(strcmp(tratte[i].partenza, partenza) == 0){
            printf("%s - %s\n", tratte[i].partenza, tratte[i].destinazione);
        }
    }
}

void elencaCorseDate(sTratta tratte[MAXR], char datai[MAXL], char dataf[MAXL], int nr){
    printf("Le tratte che sono partite tra il %s e il %s sono:\n",datai,dataf);
    for(int i = 0; i < nr; i++){
        if(strcmp(tratte[i].data,datai) >= 0 || strcmp(tratte[i].data, dataf) <= 0){
            printf("%s - %s\n", tratte[i].partenza, tratte[i].destinazione);
        }
    }
}