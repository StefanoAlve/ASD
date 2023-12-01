#include <stdio.h>
#include <stdlib.h>
#define maxL 50
#define DBG 0

typedef struct {
    int S, F;
} Att;

int compare(Att *a, Att *b);
Att *leggiFile(int *n);
void attSel(int n, Att *v);

int main() {
    Att *att;
    int n;

    // Prendo informazioni da file
    att = leggiFile(&n);

    // Funzione wrapper
    attSel(n, att);

    free(att);
    return 0;
}

int compare(Att *a, Att *b){
    int diff = (a->F - b->F);

    if(diff < 0)
        return -1;
    else if(diff > 0)
        return 1;
    else
        return 0;
}


//Leggi informazioni da file
Att *leggiFile(int *n){
    Att *att;
    FILE *fin;
    char nomeFile[maxL];

    //Nome del file da tastiera
    printf("Inserisci il nome del file:\n");
    scanf(" %s", nomeFile);

    //Apertura file e gestione errori
    if((fin = fopen(nomeFile, "r")) == NULL){
        printf("Errore lettura file %s", nomeFile);
        exit(1);
    }

    //Assegnazione valori da file
    fscanf(fin, "%d", n);
    att = calloc(*n, sizeof(Att));

    for(int i = 0; i < *n; i++){
        fscanf(fin, "%d %d", &att[i].S, &att[i].F);
    }

    fclose(fin);
    return att;
}

// Funzione wrapper
void attSel(int n, Att *v){
    int diffMax = 0, *sol = NULL;

#if DBG
    for(int i = 0; i<n;i++)
        printf("(%d %d)", v[i].S, v[i].F);
    printf("\n");
#endif
    //Ordinamento delle attività in base all'estremità finale
    qsort(v, n, sizeof(Att), (int (*)(const void *, const void *)) compare);
#if DBG
    for(int i = 0; i<n;i++)
        printf("(%d %d)", v[i].S, v[i].F);
    printf("\n");
#endif

    //Allocazione di un array per memorizzare la soluzione
    sol = (int *)malloc(n * sizeof(int));

    //Inizializza il caso base
    sol[0] = v[0].F - v[0].S;

    //Calcola i valori ottimi utilizzando un approccio bottom-up
    for(int i = 1; i < n; i++){
        sol[i] = sol[i - 1];
        for(int j = i - 1; j >= 0; j--){
            //Se non c'è sovrapposizione
            if(v[j].F <= v[i].S){
                //Se migliora la soluzione
                if (sol[j] + v[i].F - v[i].S > sol[i]) {
                    sol[i] = sol[j] + v[i].F - v[i].S;
                }
                break;
            }
        }
    }

    //Calcola il valore ottimo
    diffMax = sol[n - 1];

    //Stampa soluzione ottima
    printf("Il sottoinsieme e':\n");

    for(int i = n - 1; i >= 0; i--){
        if(sol[i] == diffMax){
            printf("(%d,%d) ", v[i].S, v[i].F);
            diffMax -= (v[i].F - v[i].S);
        }
    }

    // Deallocazione
    free(sol);
}
