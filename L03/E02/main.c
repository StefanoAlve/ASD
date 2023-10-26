#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXL 255
//Strutture
typedef struct{ //struct contenente una matrice di caratteri (vettore di canzoni) per rendere più leggibile il codice
    char **canzoniAmico;
}sCanzoni;
typedef struct{
    int *scelte;
    int nScelte;
}sAmico;
//FUNZIONI
int leggiFile(sCanzoni **canzoni, sAmico **pamici);
void deallocaCanzoni(sCanzoni *canzoni, sAmico *amici, int nAmici);
int* allocaVetSol(int nAmici);
void deallocaAmico(sAmico *amici, int nAmici);
int trovaCombinazioni(int pos, sAmico *amici, int *sol, int count, sCanzoni *canzoni, int nAmici);

int main(void) {
    //Inizializzazione variabili
    sCanzoni *canzoni; //Vettore di struct contenente vettori di canzoni
    sAmico *amici;
    int pos=0, *sol, count=0, nAmici;
    //Apertura file
    nAmici=leggiFile(&canzoni, &amici);
    sol=allocaVetSol(nAmici); //Vettore di interi contenente gli indici delle soluzioni
    //Corpo programma
    count = trovaCombinazioni(pos, amici, sol, count, canzoni, nAmici);
    printf("\nTrovate %d playlist\n",count);
    //Deallocazione
    free(sol);
    deallocaCanzoni(canzoni, amici, nAmici);
    deallocaAmico(amici, nAmici);
    return 0;
}

int leggiFile(sCanzoni **pCanzoni, sAmico **pamici){
    /* La seguente funzione legge il file e alloca dinamicamente il vettore di struct amico e il vettore di struct canzoni.
     * Il primo contiene n (dove n è il numero di amici) struct contenenti il numero di canzoni scelte dall'amico in questione e un vettore di interi che vanno da 0 a nScelte.
     * Il secondo invece contiene n struct contenenti ognuna il vettore di canzoni relative all'amico (utilizzato poi per la conversione nella stampa dei risultati).
     */
    //Inizializzazione variabili
    FILE* fp;
    char *nomeFile, tmp[MAXL];
    sCanzoni *canzoniTmp;
    int cont=0, nr;
    sAmico *amici;
    //Richiesta del nome del file
    printf("Inserire il nome del file:");
    scanf(" %s", tmp);
    nomeFile = strdup(tmp);

    //Apertura file
    fp = fopen(nomeFile, "r");
    if(fp == NULL){
        printf("Errore nell'apertura del file!\n");
        exit(1);
    }
    //Lettura del file e salvataggio dati
    fscanf(fp," %d", &nr);
    amici = (sAmico*)malloc((nr)*sizeof(sAmico)); //Allocazione del vettore di struct amico
    canzoniTmp = (sCanzoni*)malloc(nr*sizeof(sCanzoni)); //Allocazione dinamica del vettore di struct canzoni
    if(amici == NULL || canzoniTmp == NULL){
        exit(1);
    }

    while(!feof(fp)){

        fscanf(fp,"%d", &amici[cont].nScelte);
        amici[cont].scelte = (int*)malloc(amici[cont].nScelte*sizeof(int)); //Allocazione del vettore delle scelte
        canzoniTmp[cont].canzoniAmico = (char**)malloc((amici[cont].nScelte)*sizeof(char*)); //allocazione dei vettori di canzoni
        for(int i=0; i<(amici[cont].nScelte); i++){
            fscanf(fp,"%s", tmp);
            canzoniTmp[cont].canzoniAmico[i] = strdup(tmp); //allocazione dinamica delle stringhe
            amici[cont].scelte[i] = i; //Riempimento del vettore delle scelte con numeri consecutivi
        }
        cont++;
    }
    *pCanzoni = canzoniTmp;
    *pamici = amici;
    //Chiusura file
    fclose(fp);
    free(nomeFile);
    return nr;
}

void deallocaCanzoni(sCanzoni *canzoni, sAmico *amici, int nAmici){
    for(int i = 0; i<nAmici; i++){
        for(int j = 0; j<amici[i].nScelte; j++){
            free(canzoni[i].canzoniAmico[j]);
        }
        free(canzoni[i].canzoniAmico);
    }
    free(canzoni);
}

void deallocaAmico(sAmico *amici, int nAmici){
    for(int i=0; i<nAmici; i++){
        free(amici[i].scelte);
    }
    free(amici);
}
int* allocaVetSol(int nAmici){
    int *sol;
    sol = (int*)malloc(nAmici*sizeof(int));
    for(int i=0;i<nAmici;i++){
        sol[i] = i;
    }
    return sol;
}
int trovaCombinazioni(int pos, sAmico *amici, int *sol, int count, sCanzoni *canzoni, int nAmici){
    int i;
    if(pos >= nAmici){//quando pos è uguale a nr vuol dire che sono all'ultima canzone della playlist quindi ho la condizione di terminazione
        printf("Playlist n.%d:\n", count+1);
        for(i=0; i<nAmici; i++){
            printf("%s ", canzoni[i].canzoniAmico[sol[i]]); //semplifico la funzione lavorando su interi e tramite la matrice di stringhe converto il risultato nelle stringhe corrispondenti
        }
        printf("\n\n");
        return count+1;
    }
    for(i=0; i<amici[pos].nScelte; i++){ //tengo fisso un campo e scandisco quelli sotto, quando la chiamata ricorsiva restituirà allora passerò all'elemento successivo
        sol[pos] = amici[pos].scelte[i];
        count = trovaCombinazioni(pos+1, amici, sol, count, canzoni, nAmici);
    }
    return count;
}