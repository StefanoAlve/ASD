#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXL 255

//Strutture
typedef struct{
    int nr;
    char ***Mcanzoni; //matrice di stringhe
}sCanzoni;
typedef struct{
  int *scelte;
  int nScelte;
}sAmico;
//FUNZIONI
void leggiFile(sCanzoni *canzoni, sAmico **pamici);
void deallocaCanzoni(sCanzoni canzoni, sAmico *amici);
int* allocaVetSol(int nr);
void deallocaAmico(sAmico *amici, int nr);
int trovaCombinazioni(int pos, sAmico *amici, int *sol, int count, sCanzoni canzoni);
int main(void) {
    //Inizializzazione variabili
    sCanzoni canzoni;
    sAmico *amici;
    int pos=0, *sol, count=0, n;
    //Apertura file
    leggiFile(&canzoni, &amici);
    sol=allocaVetSol(canzoni.nr);
    //Corpo programma
    count = trovaCombinazioni(pos, amici, sol, count, canzoni);
    printf("\nTrovate %d playlist\n",count);
    //Deallocazione
    free(sol);
    n=canzoni.nr;
    deallocaCanzoni(canzoni, amici);
    deallocaAmico(amici, n);
    return 0;
}

void leggiFile(sCanzoni *canzoni, sAmico **pamici){
    //Inizializzazione variabili
    FILE* fp;
    char *nomeFile, tmp[MAXL], ***canzoniTmp;
    int cont=0;
    sAmico *amici = *pamici;
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
    fscanf(fp," %d", &canzoni->nr);

    amici = (sAmico*)malloc((canzoni->nr)*sizeof(sAmico)); //Allocazione del vettore di struct amico

    canzoniTmp = (char***)malloc(canzoni->nr*sizeof(char**)); //Allocazione dinamica del vettore dei puntatori che indicano i vettori di canzoni
    if(amici == NULL || canzoniTmp == NULL){
        exit(1);
    }

    while(!feof(fp)){

        fscanf(fp,"%d", &amici[cont].nScelte);
        amici[cont].scelte = (int*)malloc(amici[cont].nScelte*sizeof(int)); //Allocazione del vettore delle scelte
        //Riempimento del vettore delle scelte con numeri consecutivi
        for(int j=0; j<amici[cont].nScelte; j++){
            amici[cont].scelte[j] = j;
        }
        canzoniTmp[cont] = (char**)malloc((amici[cont].nScelte)*sizeof(char*)); //allocazione dei vettori di canzoni
        for(int i=0; i<(amici[cont].nScelte); i++){
            fscanf(fp,"%s", tmp);
            canzoniTmp[cont][i] = strdup(tmp); //allocazione dinamica delle stringhe
        }
        cont++;
    }
    canzoni->Mcanzoni = canzoniTmp;
    *pamici = amici;
    //Chiusura file
    fclose(fp);
    free(nomeFile);
}

void deallocaCanzoni(sCanzoni canzoni, sAmico *amici){
    for(int i = 0; i<canzoni.nr; i++){
        for(int j = 0; j<amici[i].nScelte; j++){
            free(canzoni.Mcanzoni[i][j]);
        }
        free(canzoni.Mcanzoni[i]);
    }
    free(canzoni.Mcanzoni);
}

void deallocaAmico(sAmico *amici, int nr){
    for(int i=0; i<nr; i++){
        free(amici[i].scelte);
    }
    free(amici);
}
int* allocaVetSol(int nr){
    int *sol;
    sol = (int*)malloc(nr*sizeof(int));
    for(int i=0;i<nr;i++){
        sol[i] = i;
    }
    return sol;
}
int trovaCombinazioni(int pos, sAmico *amici, int *sol, int count, sCanzoni canzoni){
    int i;
    if(pos >= canzoni.nr){//quando pos è uguale a nr vuol dire che sono all'ultima canzone della playlist quindi ho la condizione di terminazione
        printf("Playlist n.%d:\n", count+1);
        for(i=0; i<canzoni.nr; i++){
            printf("%s ", canzoni.Mcanzoni[i][sol[i]]); //semplifico la funzione lavorando su interi e tramite la matrice di stringhe converto il risultato nelle stringhe corrispondenti
        }
        printf("\n\n");
        return count+1;
    }
    for(i=0; i<amici[pos].nScelte; i++){ //tengo fisso un campo e scandisco quelli sotto, quando la chiamata ricorsiva restituirà allora passerò all'elemento successivo
        sol[pos] = amici[pos].scelte[i];
        count = trovaCombinazioni(pos+1, amici, sol, count, canzoni);
    }
    return count;
}