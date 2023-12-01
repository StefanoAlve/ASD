#include <stdio.h>
#include <stdlib.h>
#define maxL 50

typedef struct{
    int S;
    int F;
}Att;

Att *leggiFile(int *n);
void attSel(int N, Att *v);
int verifica(int n, Att *v, int *sol, int pos);
void powerset(int pos, int n, Att *v, int *sol, int *solBest, int diff, int *diffMax);

int main(){
    Att *att;
    FILE *fin;
    int n;

    //Prendo informazioni da file
    att = leggiFile(&n);

    //Funzione wrapper
    attSel(n,att);

    free(att);
    return 0;
}

//Funzione wrapper
void attSel(int n, Att *v) {
    int pos = 0, diff = 0, diffMax = 0;

    //Allocazioni vettori e verifica errori
    int *sol = (int *) malloc(n * sizeof(int));
    int *sol_best = (int *) malloc(n * sizeof(int));

    if (sol == NULL || sol_best == NULL) {
        printf("Errore di allocazione dinamica!");
        exit(2);
    }

    //Chiamata ricorsiva che scrive la soluzione in sol_best
    powerset(pos, n, v, sol, sol_best, diff, &diffMax);

    //Stampa soluzione
    printf("Il sottoinsieme e':\n");
    for (int j = 0; j < n; j++){
        if(sol_best[j] == 1) {
            printf("(%d,%d) ", v[j].S, v[j].F);
        }
    }
    printf("di lunghezza: %d", diffMax);

    //Deallocazione
    free(sol);
    free(sol_best);

}

//Funzione per assegnare da file le informazioni a vettore di struct
Att *leggiFile(int *n){
    Att *att;
    FILE *fin;
    char nomeFile[maxL];

    //nome del file
    printf("Inserisci il nome del file:\n");
    scanf(" %s",nomeFile);

    //Apertura file e gestione errori
    if((fin = fopen(nomeFile,"r"))==NULL){
        printf("Errore lettura file %s", nomeFile);
        exit(1);
    }

    //Assegnazione valori da file
    fscanf(fin, "%d", n);
    att = (Att *)malloc(*n * sizeof (Att));

    for(int i = 0; i < *n; i++){
        fscanf(fin, "%d %d", &att[i].S, &att[i].F);
    }

    fclose(fin);
    return att;
}

//Funzione che serve da filtro per la funzione ricorsiva
int verifica(int n, Att *v, int *sol, int pos){

    for(int i = 0; i < pos; i++){
        if(sol[i] != 0){
            if(v[i].S < v[pos].F && v[pos].S < v[i].F)
                return 1;
        }
    }
    return 0;
}

//Funzione ricorsiva che trova il migliore sotto-insieme con la distanza maggiore
void powerset(int pos, int n, Att *v, int *sol, int *solBest, int diff, int *diffMax){
    int i;
    //Condizione di terminazione
    if (pos >= n) {
        if (*diffMax < diff) {
            *diffMax = diff;
            for (i=0; i<n; i++)
                solBest[i] = sol[i];
        }
        return;
    }

    //Non prendo l'elemento pos-esimo
    sol[pos] = 0;
    powerset(pos + 1, n, v, sol, solBest, diff, diffMax);

    //Se l'elemento pos-esimo rispetta la verifica lo prendo
    if(!verifica(n, v, sol, pos)){
        sol[pos] = 1;
        diff += v[pos].F - v[pos].S; //aumento la distanza
        powerset(pos + 1, n, v, sol, solBest, diff, diffMax);
    }
}
