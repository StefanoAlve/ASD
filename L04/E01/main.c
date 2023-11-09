#include <stdio.h>
#include <stdlib.h>
#define nomeFile "grafo.txt"

typedef struct{
    int Vertice1;
    int Vertice2;
}arco;
typedef struct{int NumVertici; int NumArchi;}dimensioni;

arco *allocaArchi(arco *archi, FILE *fin, dimensioni *dimensione);
arco *assegnaArchiDaFile(arco *archi, FILE *fin, dimensioni dimensione);
int powerset(arco *archi, dimensioni dimensione, int *sol, int index, int count);
int controllaVertexCover(arco *archi, dimensioni dimensione,  int *sol);

int main() {
    arco *archi = NULL;
    dimensioni dimensione;
    FILE *fin;

    //Apertura file e gestione errori
    if((fin = fopen(nomeFile, "r")) == NULL){
        printf("ERRORE LETTURA FILE %s", nomeFile);
        exit(1);
    }

    //Allocazione dinamica vettore di struct
    archi = allocaArchi(archi, fin, &dimensione);

    int *sol = calloc(dimensione.NumVertici, sizeof (int));


    //Assegnazione valori a struct
    archi = assegnaArchiDaFile(archi, fin, dimensione);

    //Funzione ricorsiva che cerca i vertex cover attraverso le disposizioni ripetute
    int numSol = powerset(archi, dimensione, sol, 0, 0);

    if(numSol != 0) printf("Numero di soluzioni: %d", numSol);

    fclose(fin);
    free(archi);
    return 0;
}

//Allocazione dinamica vettore di struct
arco *allocaArchi(arco *archi, FILE *fin, dimensioni *dimensione){

    fscanf(fin,"%d %d", &(dimensione->NumArchi), &(dimensione->NumVertici));

    //Allocazione vettore di struct gestione di errori
    archi = (arco*) malloc(dimensione->NumVertici * sizeof (arco));
    if(archi == NULL){
        printf("Errore allocazione vettore di struct");
        exit(2);
        }

    return archi;
}

//Assegnazione dei valori dei vertici a struct
arco *assegnaArchiDaFile(arco *archi, FILE *fin, dimensioni dimensione){

    for(int i = 0; i < dimensione.NumArchi; i++)
        fscanf(fin, "%d %d", &archi[i].Vertice1, &archi[i].Vertice2);

    return archi;
}

//Funzione che
int controllaVertexCover(arco *archi, dimensioni dimensione,  int *sol){
    int flag = 1;

    for(int i=0; i<dimensione.NumArchi; i++)
        if ((sol[archi[i].Vertice1]==0) && (sol[archi[i].Vertice2]==0))
            flag = 0;

    return flag;
}

//Funzione ricorsiva che cerca tutti i vertex cover e chiama una funzione che li stampa
int powerset(arco *archi, dimensioni dimensione,  int *sol, int index, int count){

    //Caso di controllo ed eventuale stampa
    if(index >= dimensione.NumVertici){
        if(controllaVertexCover(archi, dimensione, sol) == 1){
            printf("vertex cover:{ ");

            for(int i = 0; i < dimensione.NumVertici; i++)
                if (sol[i]==1)
                    printf("%d ", i);
            printf("}\n");

            return count+1;
        }
        return count;
    }

    //Non prende l'elemento index
    sol[index] = 0;
    count = powerset(archi, dimensione, sol, index + 1, count);

    //Backtrack prendendo l'elemento index
    sol[index] = 1;
    count = powerset(archi, dimensione, sol, index + 1, count);
    return count;
}
