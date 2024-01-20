#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXC 50
//Strutture dati
typedef struct {
    int v1;
    int v2;
}arco;

typedef struct{
    int *combinazione;
}partizione;
//Funzioni
void leggiFile(int *pN, int *pE, arco **pvettArchi);
void allocaValSol(int N, int **pval, int **psol);
int powerset(int *val, int n, int *sol, int j, int pos, int start, arco *vettArchi, int E);
int trovaInsieme(int *val, int n, int *sol, arco *vettArchi, int E);
int verificaVertex(int E, int pos, int *sol, arco *vettArchi);
int main() {
    //Inizializzazione variabili
    arco *vettArchi;
    int N, E, *val, *sol, count;
    //Assegnazione variabili

    //Corpo programma
    leggiFile(&N,&E, &vettArchi);
    allocaValSol(N,&val,&sol);
    count = trovaInsieme(val, N, sol, vettArchi, E);
    printf("Ho trovato %d Vertex Cover\n", count);

    //Deallocazione memoria
    free(vettArchi);
    free(val);
    free(sol);
    return 0;
}

void leggiFile(int *pN, int *pE, arco **pvettArchi){
    int N, E;
    char tmp[MAXC], *nomeFile;
    arco *vettArchi;
    FILE *fp;

    //Apertura file
    printf("Inserire il nome del file:");
    scanf("%s",tmp);
    nomeFile = strdup(tmp);
    fp=fopen(nomeFile, "r");
    if(fp == NULL){
        printf("Errore nell'apertura del file!\n");
        exit(1);
    }
    fscanf(fp,"%d %d",&N, &E);
    //Allocazione memoria dinamica
    vettArchi = (arco*)malloc(E*sizeof(arco));
    if(vettArchi == NULL){
        printf("Errore nell'allocazione del vettore di archi!\n");
        exit(1);
    }
    for(int i=0;i<E;i++){
        fscanf(fp,"%d %d", &vettArchi[i].v1,&vettArchi[i].v2);
    }
    //Punto i puntatori verso le celle di memoria contenenti le variabili temporanee utilizzate
    *pN = N;
    *pE = E;
    *pvettArchi = vettArchi;

    free(nomeFile);
    fclose(fp);
}

int powerset(int *val, int n, int *sol, int j, int pos, int start, arco *vettArchi, int E){
    int cnt = 0, i;
    if (pos >= j) { //Condizione di terminazione
        if(verificaVertex(E,pos,sol,vettArchi)){ //La funzione interna all'if restituisce 1 se è un vertexCover se no restituisce 0
            printf("Vertex Cover: { ");
            for(i=0;i<pos;i++){
                printf("%d ",sol[i]);
            }
            printf("}\n");
            return 1;
        }
        return 0;
    }
    for(i = start; i<n; i++){
        sol[pos] = val[i];
        cnt += powerset(val, n, sol, j, pos+1, i+1, vettArchi, E);
    }
    return cnt;
}

int trovaInsieme(int *val, int n, int *sol, arco *vettArchi, int E){
    ///WRAPPER DI POWERSET
    int cnt = 0, j;
    //Allocazione insieme delle parti
    for(j=1; j<=n; j++){
        cnt += powerset(val, n, sol, j, 0, 0, vettArchi, E);
    }
    return cnt;
}

void allocaValSol(int N, int **pval, int **psol){
    int *val, *sol;
    val = (int*)malloc(N*sizeof(int));
    sol = (int*)malloc(N*sizeof(int));
    if(val == NULL || sol == NULL){
        printf("Errore nell'allocazione dei vettori!\n");
        exit(1);
    }

    for(int i=0; i<N; i++){
        val[i] = i;
    }

    *pval = val;
    *psol = sol;
}

int verificaVertex(int E, int pos, int *sol, arco *vettArchi){
    int controlloVertex[E], i, k, ok=1;

    for(i=0;i<E;i++){
        controlloVertex[i] = 0;
    }
    for(i=0;i<E;i++){
        for(k=0;k<pos;k++){
            if(vettArchi[i].v1 == sol[k] || vettArchi[i].v2 == sol[k]){
                controlloVertex[i] = 1;
                break;
            }
        }
    }
    for(i=0;i<E;i++){
        if(controlloVertex[i] == 0){
            ok=0; //Se all'interno del vettore ho uno zero non è un vertexCover
        }
    }
    return ok;
}