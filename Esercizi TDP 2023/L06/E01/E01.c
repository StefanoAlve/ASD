#include <stdio.h>
#include <string.h>
#define maxR 1000
#define maxS 30
#define nomeFile "log.txt"
typedef struct{
    char codice_tratta[maxS];
    char partenza[maxS];
    char destinazione[maxS];
    char data[maxS];
    char ora_partenza[maxS];
    char ora_arrivo[maxS];
    int ritardo;
}tratta;

typedef enum{
    r_date,r_partenza,r_capolinea,r_ritardo,r_ritardo_tot,r_fine
}comando_e;


int leggiFile(FILE *fp_read, tratta vettore_tratte[maxR]);
comando_e leggiComando();
void menuParola(tratta vettore_tratte[maxR], int dimensione, comando_e comando);
void date(tratta vettore_tratte[maxR], int dimensione);
void partenza(tratta vettore_tratte[maxR], int dimensione);
void capolinea(tratta vettore_tratte[maxR], int dimensione);
void ritardo(tratta vettore_tratte[maxR], int dimensione);
void ritardo_tot(tratta vettore_tratte[maxR], int dimensione);

int main(void) {
    //Inizializzazione variabili
    FILE *fp_read;
    tratta vettore_tratte[maxR];
    int dimensione;
    comando_e comando;
    //Assegnazione variabili
    comando = r_date;
    //Apertura file
    fp_read = fopen(nomeFile,"r");
    if (fp_read == NULL){
        printf("Errore nell'apertura del file di input!\n");
        return 1;
    }
    //Corpo programma
    dimensione=leggiFile(fp_read, vettore_tratte);
    while (comando != r_fine) {
        comando = leggiComando();
        menuParola(vettore_tratte, dimensione, comando);
    }

    //Chiusura file
    fclose(fp_read);
    return 0;
}

//Funzioni

int leggiFile(FILE *fp_read, tratta vettore_tratte[maxR]){
    //Funzione che legge il file d'input e riempe il vettore di struct di tipo tratta
    int numR;
    fscanf(fp_read,"%d",&numR);
    for(int i=0; i<numR; i++){
        fscanf(fp_read, "%s %s %s %s %s %s %d",vettore_tratte[i].codice_tratta, vettore_tratte[i].partenza, vettore_tratte[i].destinazione, vettore_tratte[i].data, vettore_tratte[i].ora_partenza, vettore_tratte[i].ora_arrivo, &vettore_tratte[i].ritardo);
    }
    return numR;
}

comando_e leggiComando(){
    //Funzione che legge un comando inserito da tastiera e lo confronta con delle parole chiave, ritorna una variabile c di tipo comando_e
    comando_e c;
    char comando[maxS];
    char parole[r_fine+1][maxS] = {
            "date","partenza", "capolinea", "ritardo", "ritardo_tot", "fine"
    };
    printf("\n=============================\n");
    printf("\tMENU' COMANDI\t\n\n");
    printf("\t<date>\n");
    printf("\t<partenza>\n");
    printf("\t<capolinea>\n");
    printf("\t<ritardo>\n");
    printf("\t<ritardo_tot>\n");
    printf("\t<fine>\n");
    printf("=============================\n\n");
    printf("Inserire comando:");
    scanf("%s", comando);

    c=r_date;
    while(c<=r_fine && strcasecmp(comando,parole[c])!=0){
        c++;
    }
    return c;
}

void menuParola(tratta vettore_tratte[maxR], int dimensione, comando_e comando){
    //Funzione che gestisce le altre sotto funzioni ponendole in uno switch
    switch(comando){
        case r_date: date(vettore_tratte,dimensione); break;
        case r_partenza: partenza(vettore_tratte,dimensione); break;
        case r_capolinea: capolinea(vettore_tratte,dimensione); break;
        case r_ritardo: ritardo(vettore_tratte,dimensione); break;
        case r_ritardo_tot: ritardo_tot(vettore_tratte,dimensione); break;
        case r_fine: printf("\nTermino il programma\n"); break;
        default: printf("Comando errato!\n"); break;
    }
}

void date(tratta vettore_tratte[maxR], int dimensione){
    //Sottofunzione di menuParola, stampa le corse comprese tra due date inserite da tastiera
    int comp_in, comp_fin,trovate=0;
    char data_inizio[maxS], data_fine[maxS];
    printf("\nInserire data di inizio nel formato AAAA/MM/GG:");
    scanf("%s", data_inizio);
    printf("\nInserire data di fine nel formato AAAA/MM/GG:");
    scanf("%s", data_fine);
    for(int l=0; l<dimensione; l++){
        comp_in=strcmp(data_inizio, vettore_tratte[l].data);
        comp_fin=strcmp(data_fine, vettore_tratte[l].data);
        if(comp_in <= 0 && comp_fin >= 0){
            printf("\nLa corsa con codice: %s che parte dalla fermata %s alle ore %s al capolinea %s alle ore %s del %s e' compresa tra le date inserite\n", vettore_tratte[l].codice_tratta,vettore_tratte[l].partenza,vettore_tratte[l].ora_partenza,vettore_tratte[l].destinazione,vettore_tratte[l].ora_arrivo,vettore_tratte[l].data);
            trovate+=1;
        }
    }
    if(trovate==0){
        printf("\nNon sono state trovate corse nel periodo di tempo inserito\n");
    }
}
void partenza(tratta vettore_tratte[maxR],int dimensione){
    //Sottofunzione di menuParola, stampa le corse partite da una fermata inserita da tastiera
    int trovate=0;
    char part[maxS];
    printf("\nInserire fermata di partenza cercata:");
    scanf("%s", part);
    for(int v=0; v<dimensione; v++){
        if(strcasecmp(vettore_tratte[v].partenza, part)==0){
            printf("\nLa tratta con codice: %s delle ore %s del giorno %s parte dalla fermata inserita e ha come capolinea %s\n", vettore_tratte[v].codice_tratta, vettore_tratte[v].ora_partenza, vettore_tratte[v].data,vettore_tratte[v].destinazione);
            trovate+=1;
        }
    }
    if(trovate==0){
        printf("\nNon sono state trovate corse aventi come fermata di partenza %s\n",part);
    }

}
void capolinea(tratta vettore_tratte[maxR],int dimensione){
    //Sottofunzione di menuParola, stampa le corse che hanno come capolinea una fermata inserita da tastiera
    int trovate=0;
    char cap[maxS];
    printf("\nInserire fermata di capolinea cercata:");
    scanf("%s", cap);
    for(int k=0; k<dimensione; k++) {
        if (strcasecmp(vettore_tratte[k].destinazione, cap) == 0) {
            printf("\nLa tratta con codice: %s delle ore %s del giorno %s ha come capolinea la fermata inserita\n", vettore_tratte[k].codice_tratta, vettore_tratte[k].ora_partenza, vettore_tratte[k].data);
            trovate+=1;
        }
    }
    if(trovate==0){
        printf("\nNon sono state trovate corse aventi come capolinea %s\n",cap);
    }
}
void ritardo(tratta vettore_tratte[maxR],int dimensione){
    //Sottofunzione di menuParola, stampa le corse partite che hanno avuto ritardo tra due date inserite da tastiera
    int comp_in, comp_fin,trovate=0;
    char data_inizio[maxS], data_fine[maxS];
    printf("\nInserire data di inizio nel formato AAAA/MM/GG:");
    scanf("%s", data_inizio);
    printf("\nInserire data di fine nel formato AAAA/MM/GG:");
    scanf("%s", data_fine);
    for(int l=0; l<dimensione; l++){
        comp_in=strcmp(data_inizio, vettore_tratte[l].data);
        comp_fin=strcmp(data_fine, vettore_tratte[l].data);
        if(comp_in <= 0 && comp_fin >= 0 && vettore_tratte[l].ritardo != 0){
            printf("\nLa corsa con codice: %s e' compresa tra le date inserite e ha raggiunto la destinazione con un ritardo di %d minuti\n", vettore_tratte[l].codice_tratta, vettore_tratte[l].ritardo);
            trovate+=1;
        }
    }
    if(trovate==0){
        printf("\nNon sono state trovate corse arrivate al capolinea in ritardo nell'intervallo di tempo inserito\n");
    }
}
void ritardo_tot(tratta vettore_tratte[maxR],int dimensione){
    //Sottofunzione di menuParola, stampa le corse aventi codice di tratta uguale a quello inserito da tastiera e indica il ritardo totale
    char codice[maxS];
    int ritTot=0,trovate=0;
    printf("\nInserire codice della tratta:");
    scanf("%s", codice);
    for(int n=0;n<dimensione; n++){
        if(strcasecmp(codice,vettore_tratte[n].codice_tratta)==0){
            printf("\nLa tratta che parte da %s alle ore %s con capolinea a %s alle ore %s del %s ha un ritardo di %d minuti\n", vettore_tratte[n].partenza, vettore_tratte[n].ora_partenza, vettore_tratte[n].destinazione, vettore_tratte[n].ora_arrivo, vettore_tratte[n].data, vettore_tratte[n].ritardo);
            ritTot+= vettore_tratte[n].ritardo;
            trovate+=1;
        }
    }
    if(trovate!=0) {
        printf("\nIl ritardo totale delle tratte aventi codice %s e' di %d minuti\n", codice, ritTot);
    }
    else{
        printf("\nNon sono state trovate corse aventi il codice inserito!\n");
    }
}

