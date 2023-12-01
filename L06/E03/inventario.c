#include "inventario.h"

//Funzione che carica gli oggetti da file a vettore di struct
oggetti_s *caricaOggetti(char nomeFile[], int *numOggetti){
    FILE *fin;
    oggetti_s *v;

    //Apertura file e gestione errori
    if((fin = fopen(nomeFile, "r")) == NULL){
        printf("Errore in apertura del file!\n");
        exit(1);
    }

    //Numero oggetti da file
    if((fscanf(fin, "%d", numOggetti)) != 1){
        printf("Errore nella lettura del numero di oggetti!\n");
        exit(1);
    }

    v = (oggetti_s *) malloc((*numOggetti) * sizeof (oggetti_s));
    if(v == NULL){
        printf("Errore nella allocazione dinamica del vettore di struct!");
        exit(2);
    }

    //Assegno valori da file a vettore di strut
    for(int i = 0; i < *numOggetti; i++){
        fscanf(fin, "%s %s", v[i].nome, v[i].tipologia);
        fscanf(fin, "%d %d %d %d %d %d",
               &v[i].stat.hp, &v[i].stat.mp, &v[i].stat.atk, &v[i].stat.def, &v[i].stat.mag, &v[i].stat.spr);
    }
    return v;
}

//Vettore che dealloca il vettore di struct
void deallocaOggetti(oggetti_s *v){
    free(v);
}

//Funzione che stampa gli oggetti
void stampaOggetti(oggetti_s *v, int numOggetti){
    //Stampa oggetti
    for(int i = 0; i < numOggetti; i++){
        printf("Nome: %s, tipologia %s ", v[i].nome, v[i].tipologia);
        printf(", statistiche: HP %d, MP %d, ATK %d, DEF %d, MAG %d, SPR %d",
               v[i].stat.hp, v[i].stat.mp, v[i].stat.atk, v[i].stat.def, v[i].stat.mag, v[i].stat.spr);
    }
}