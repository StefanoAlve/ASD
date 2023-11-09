#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define numPietre 4
#define MAXC 100
typedef struct{
    int z;
    int r;
    int t;
    int s;
}pietre;

int leggiFile(pietre **pCollane);
void stampaCollana(char *sequenza, int n);
void stampa_collane(pietre *collane, int nCollane);
void inizializzaRimanenti(int rimanenti[numPietre], pietre collana);
void wrapperTrovaComb(int nCollane, pietre *collane);
int trovaComb(char *val, char *sol, int rimanenti[numPietre], int n_dist, int dimSol, int pos, int flag);
int controlloValidita(char *sol, int pos);

int main(void) {
    //Inizializzazione variabili
    int nCollane;
    pietre *collane;
    //Corpo programma
    nCollane = leggiFile(&collane);
    stampa_collane(collane,nCollane);
    wrapperTrovaComb(nCollane, collane);
    return 0;
}

int leggiFile(pietre **pCollane){
    //Inizializzazione variabili
    int nCollane, i;
    pietre *collane;
    FILE *fp;
    char *nomeFile, tmp[MAXC];

    //Corpo funzione
    printf("Inserire il nome del file:");
    scanf("%s", tmp);
    nomeFile = strdup(tmp);
    //Apertura file
    fp = fopen(nomeFile, "r");
    if(fp == NULL){
        printf("Errore nella lettura del file!\n");
        exit(1);
    }

    fscanf(fp,"%d", &nCollane); //Trovo il numero di collane

    //Allocazione vett collane
    collane = (pietre*)malloc(nCollane*sizeof(pietre));
    if(collane == NULL){
        printf("Errore nell'allozazione del vettore di collane!\n");
        exit(1);
    }
    for(i=0; i<nCollane; i++){
        fscanf(fp,"%d %d %d %d", &collane[i].z, &collane[i].r, &collane[i].t, &collane[i].s);
    }
    *pCollane = collane;

    //Chiusura file
    fclose(fp);
    //Deallocazione
    free(nomeFile);
    return nCollane;
}


void stampaCollana(char *sequenza, int n){
    for(int i=0; i<n; i++){
        printf("%c ",sequenza[i]);
    }
    printf("\n");
}

void stampa_collane(pietre *collane, int nCollane){
    for(int i = 0; i<nCollane; i++){
        printf("Test n.%d: %d zaffiri, %d rubini, %d topazi, %d smeraldi\n", i+1, collane[i].z, collane[i].r, collane[i].t,collane[i].s);
        printf("Numero pietre totali: %d\n", collane[i].z+collane[i].r+collane[i].t+collane[i].s);
    }
}

void inizializzaRimanenti(int rimanenti[4], pietre collana){
    rimanenti[0] = collana.z;
    rimanenti[1] = collana.r;
    rimanenti[2] = collana.t;
    rimanenti[3] = collana.s;
}

int trovaComb(char *val, char *sol, int rimanenti[4], int n_dist, int dimSol, int pos, int flag){
    int i;
    if(pos>=dimSol){
        printf("La collana piu' lunga puo' essere riempita con %d pietre:\n", dimSol);
        stampaCollana(sol, dimSol);
        flag = 1;
        return flag;
    }
    for(i=0; i<n_dist; i++){
        if(rimanenti[i] > 0){
            rimanenti[i]--;
            sol[pos] = val[i];
            if(controlloValidita(sol, pos)){
                flag = trovaComb(val, sol, rimanenti, n_dist, dimSol, pos+1, flag);
            }
            rimanenti[i]++;
            if(flag){
                return flag;
            }
        }
    }
    return flag;
}

int controlloValidita(char *sol, int pos){
    char precedente = sol[pos-1], valido = 0;
    if(pos == 0){
        valido = 1;
    }
    else{
        switch(precedente){
            case 'z':
                if(sol[pos] == 'z' || sol[pos] == 'r')
                    valido = 1;
                break;
            case 'r':
                if(sol[pos] == 's' || sol[pos] == 't')
                    valido = 1;
                break;
            case 't':
                if(sol[pos] == 'z' || sol[pos] == 'r')
                    valido = 1;
                break;
            case 's':
                if(sol[pos] == 's' || sol[pos] == 't')
                    valido = 1;
                break;
            default:
                break;
        }
    }
    return valido;
}

void wrapperTrovaComb(int nCollane, pietre *collane){
    int flag,rimanenti[numPietre],dimSol, pos = 0;
    char val[4] = {'z','r','t','s'}, *sol;
    float inizio, tempo;
    //Corpo funzione
    for(int i = 0; i<nCollane; i++){
        inizio = clock();
        printf("\nTest n.%d:\n", i+1);
        inizializzaRimanenti(rimanenti, collane[i]);
        dimSol = rimanenti[0]+rimanenti[1]+rimanenti[2]+rimanenti[3];
        flag = 0;
        while(!flag){
            sol = (char*)malloc(dimSol*sizeof(char));
            flag = trovaComb(val,sol,rimanenti,4,dimSol,pos,flag);
            dimSol--;
            free(sol);
        }
        tempo = clock()-inizio;
        printf("Tempo impiegato: %.3f secondi\n",(tempo/1000));
    }
    free(collane);
}