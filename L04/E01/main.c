#include <stdio.h>
#include "stdlib.h"
#define DBG 0
#define MAXL 255

typedef struct{
    int vertice1;

    int vertice2;
} arco;

FILE* aperturaFileLettura();
void letturaEallocazione(FILE* fin, int **sol, int **val, int *n, int *e, arco **parchi);
void freeSD(int *val, int *sol, arco *archi);
int powerset(int pos, int *sol, int *val, int n, int start, int cnt, int e, arco *archi);
int verifica_vertex_cover(int pos, int *sol, int e, arco *archi);


int main() {
    FILE *fin = aperturaFileLettura();
    int start = 0, cnt = 0, *sol, *val, n = 0, e = 0, pos = 0;
    arco *archi;

    letturaEallocazione(fin, &sol, &val, &n, &e, &archi);

    powerset(pos, sol, val, n, start, cnt , e, archi);

    fclose(fin);
    freeSD(val, sol, archi);
    return 0;
}

FILE* aperturaFileLettura(){
    FILE *fin;
    char filename[] = {"C:\\Users\\calve\\OneDrive\\Desktop\\primo semestre\\Algoritmi\\laboratorio\\L04\\E01\\grafo.txt"};

   // printf("\nInserisci il nome del file da aprire: ");
   //scanf("%s", filename);

    fin = fopen(filename, "r");

    if(fin == NULL){
        printf("\nErrore nell'apertura del file");
        exit(1);
    }
    return fin;
}

void letturaEallocazione(FILE* fin, int **sol, int **val, int *n, int *e, arco **parchi){
    int i = 0 , *valtemp, *soltemp;
    arco *architemp;
    fscanf(fin, "%d %d", n, e);

    valtemp =(int*) malloc(*n * sizeof(int));
    for (int i = 0; i < *n; ++i) { //nella posizione i-esima l'i-esimo arco
        valtemp[i] = i;
    }
    architemp =(arco*) malloc(*e * sizeof(arco)); //allocazione della struct per salvare gli archi

    soltemp = (int*) malloc(*n * sizeof(int)); //allocazione del vettore delle soluzioni

    while(!feof(fin)){
        fscanf(fin,"%d %d", &architemp[i].vertice1, &architemp[i].vertice2);
        i++;
    }
    *val = valtemp;
    *sol = soltemp;
    *parchi = architemp;
}

void freeSD(int *val, int *sol, arco *archi){
    free(val);
    free(sol);
    free(archi);
}

int powerset(int pos, int *sol, int *val, int n, int start, int cnt, int e, arco *archi ) {
    if (start >= n) {
        if (verifica_vertex_cover(pos, sol, e, archi)){
            printf("vertex cover : { ");
            for (int i = 0; i < pos; ++i) {
                printf("%d ", sol[i]);
            }
            printf("}\n");
            return cnt + 1;
        }
        return cnt;
    }
    for (int i = start; i < n; ++i) {
        sol[pos] = val[i];
        cnt = powerset(pos + 1, sol, val, n, i + 1, cnt, e, archi);
    }
    cnt = powerset(pos, sol, val, n, n, cnt, e, archi);
    return cnt;
}

int verifica_vertex_cover(int pos, int *sol, int e, arco *archi){
    int *verificavertex;
    verificavertex =(int*) malloc(e*sizeof (int));

    if (pos<2){return 0;}
    for (int i = 0; i < pos; ++i) {
        verificavertex[i] = 0;
    }

    for (int i = 0; i < e; ++i) {
        for (int j = 0; j < pos ; ++j) {
            if(sol[j] == archi[i].vertice1 || sol[j] == archi[i].vertice2){
                verificavertex[i] = 1; //in verifica vertex ho l'indice esterno perchè altrimenti in caso di break aggiornerei in alcune situazioni l'indice sbagliato generando risultati errati
                break;
            }
        }
    }
    for (int i = 0; i < pos; ++i) {
        if(verificavertex[i] == 0){
            free(verificavertex);
            return 0; //se almeno un elemento della soluzione non è presente fra i vertici degli archi, ritorna 0, non è un vertex cover
        }

    }
    free(verificavertex);
    return 1; //se tutti gli elementi di sol sono presenti negli archi, ho un vertex cover, ritorno e permetto la stampa
}