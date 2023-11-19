#include <stdio.h>
#include "stdlib.h"
#define filename "very_very_easy_test_set.txt"

//z deve essere seguito immediatamente da z o da r
//s deve essere seguito immediatamente da s o da t
//r deve essere seguito immediatamente da s o da t
//t deve essere seguito immediatamente da z o da r

//creare vettore mark per associazione indice - pietra, nell'indice inserisco il numero di pietre disponibili per tipo
// z = 0, r = 1, t = 2, s = 3
int perm_r(int pos, char *sol, char *dist_val, int *mark, int n, int cnt);
int leggi_file(int *mark, char *dist_val);
//all'interno di dist_val salvo le lettere che indicano le pietre

int main() {
    printf("Hello, World!\n");
    char dist_val[] = {'z', 'r', 't', 's'};
    int *mark =(int*) malloc(sizeof(int)*4), cnt;
    cnt = leggi_file(mark, dist_val);
    printf("%d", cnt);
    free(mark);
    return 0;
}

int leggi_file(int *mark, char *dist_val){
    FILE *fin = fopen(filename, "r");
    if(fin == NULL){
        printf("\n Non è stato possibile aprire il file");
        return 0;
    }
    int r = 0;//righe presenti nel file
    int i = 0, pos = 0, max_sol = 1;
    int cnt = 0;//max_sol è la dimensione massima che la soluzione può avere
    fscanf(fin, "%d", r); //leggo il numero di righe presenti nel file, il numero di set disponibili con cui fare i test
    //potrebbe essere conveniente chiamare qui la ricorsione così che alla lettura di un nuovo set presente nel file possa direttamente effettuare un test
    while( i <= r){
        fscanf(fin, "%d %d %d %d", &mark[0], &mark[1], &mark[2], &mark[3]);
        max_sol = mark[0] + mark[1] + mark[2] + mark[3];
        char *sol =(char*) malloc(sizeof(char) * max_sol); //socvralloco il vettore delle soluzioni con la dimensione massima possibile, cioè il caso in cui possa usare tutte le pietre che ho a disposizione
        cnt = perm_r(pos, sol, dist_val, mark, max_sol, cnt);
        i++;
    }
}

int perm_r(int pos, char *sol, char *dist_val, int *mark, int n, int cnt){

    if(pos>=n){
        sol[pos] = '\0';
        printf("%s\n", sol);
        return cnt+1;
    }
    for (int i = 0; i < n; ++i) {
        if(mark[i] > 0){
            mark[i]--; //in mark ho un associazione per indici al numero di pietre disponibili per pietra
            sol[pos] = dist_val[i];//in dist val salvo la lettera della pietra
            cnt = perm_r(pos+1, sol, dist_val, mark, n, cnt );
            mark[i]++; //quando ritorno dalla chiamata alla funzione reinserisco la pietra utilizzata nella "vasca" dei valori utilizzabili per la soluzione
        }
    }
}