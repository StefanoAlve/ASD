#include <stdio.h>
#include <stdlib.h>
#include "inventario.h"
#define maxL 50

//Funzione per caricare oggetti da file
oggetti_s *caricaOggetti(char nomeFile[], int *numOggetti){
    FILE *fin;
    oggetti_s *v;

    //Apertura file e gestione errori
    if((fin = fopen(nomeFile, "r")) == NULL){
        printf("Errore in apertura del file %s\n", nomeFile);
        exit(1);
    }

    //Prendo il numero di oggetti da file
    if(fscanf(fin, "%d", numOggetti) != 1){
        printf("Errore nella lettura del numero di oggetti!\n");
        exit(1);
    }

    //Allocazione vettore di struct
    v = (oggetti_s *)malloc((*numOggetti) * sizeof (oggetti_s));
    if(v == NULL){
        printf("Errore nell'allocazione del vettore di oggetti!\n");
        exit(1);
    }

    //Assegnazione valori da file
    for(int i = 0; i < *numOggetti; i++){
        fscanf(fin, "%s %s", v[i].nome, v[i].tipologia);
        fscanf(fin, "%d %d %d %d %d %d",
               &v[i].stat.hp, &v->stat.mp, &v[i].stat.atk, &v[i].stat.def, &v[i].stat.mag, &v[i].stat.spr);
    }

    fclose(fin);
    return v;
}

//Funzione per la deallocazione
void deallocaOggetti(oggetti_s *v){
    free(v);
}

//Stampa oggetti
void stampaOggetti(oggetti_s *v, int numOggetti){

    //Stampa oggetti
    for(int i = 0; i < numOggetti; i++){
    printf("Oggetto %s %s, ", v->nome, v->tipologia);
    printf("statistiche: HP %d, MP %d, ATK %d, DEF %d, MAG %d, SPR %d",
           v->stat.hp, v->stat.mp, v->stat.atk, v->stat.def, v->stat.mag, v->stat.spr);
    }
}