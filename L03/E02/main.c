#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXL 255

//Strutture
typedef struct{
  int *scelte;
  int nScelte;
}sAmico;
//FUNZIONI
int leggiFile(char ****Mcanzoni, sAmico **pamici); //Passo puntatore a matrice di stringhe per effettuare allocazione dinamica
void deallocaCanzoni(char ***Mcanzoni, sAmico *amici, int nr);
int* allocaVetSol(int nAmici);
void deallocaAmico(sAmico *amici, int nAmici);
int trovaCombinazioni(int pos, sAmico *amici, int *sol, int count, char ***Mcanzoni, int nAmici);
int main(void) {
    //Inizializzazione variabili
    char ***Mcanzoni; //Matrice di stringhe
    sAmico *amici;
    int pos=0, *sol, count=0, nAmici;
    //Apertura file
    nAmici=leggiFile(&Mcanzoni, &amici);
    sol=allocaVetSol(nAmici);
    //Corpo programma
    count = trovaCombinazioni(pos, amici, sol, count, Mcanzoni, nAmici);
    printf("\nTrovate %d playlist\n",count);
    //Deallocazione
    free(sol);
    deallocaCanzoni(Mcanzoni, amici, nAmici);
    deallocaAmico(amici, nAmici);
    return 0;
}

int leggiFile(char ****Mcanzoni, sAmico **pamici){
    //Inizializzazione variabili
    FILE* fp;
    char *nomeFile, tmp[MAXL], ***canzoniTmp;
    int cont=0, nr;
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
    fscanf(fp," %d", &nr);
    amici = (sAmico*)malloc((nr)*sizeof(sAmico)); //Allocazione del vettore di struct amico

    canzoniTmp = (char***)malloc(nr*sizeof(char**)); //Allocazione dinamica del vettore dei puntatori che indicano i vettori di canzoni
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
    *Mcanzoni = canzoniTmp;
    *pamici = amici;
    //Chiusura file
    fclose(fp);
    free(nomeFile);
    return nr;
}

void deallocaCanzoni(char ***Mcanzoni, sAmico *amici, int nAmici){
    for(int i = 0; i<nAmici; i++){
        for(int j = 0; j<amici[i].nScelte; j++){
            free(Mcanzoni[i][j]);
        }
        free(Mcanzoni[i]);
    }
    free(Mcanzoni);
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
int trovaCombinazioni(int pos, sAmico *amici, int *sol, int count, char ***Mcanzoni, int nAmici){
    int i;
    if(pos >= nAmici){//quando pos è uguale a nr vuol dire che sono all'ultima canzone della playlist quindi ho la condizione di terminazione
        printf("Playlist n.%d:\n", count+1);
        for(i=0; i<nAmici; i++){
            printf("%s ", Mcanzoni[i][sol[i]]); //semplifico la funzione lavorando su interi e tramite la matrice di stringhe converto il risultato nelle stringhe corrispondenti
        }
        printf("\n\n");
        return count+1;
    }
    for(i=0; i<amici[pos].nScelte; i++){ //tengo fisso un campo e scandisco quelli sotto, quando la chiamata ricorsiva restituirà allora passerò all'elemento successivo
        sol[pos] = amici[pos].scelte[i];
        count = trovaCombinazioni(pos+1, amici, sol, count, Mcanzoni, nAmici);
    }
    return count;
}