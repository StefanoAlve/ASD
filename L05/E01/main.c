#include <stdio.h>
#include "stdlib.h"

#define filename "att.txt"

typedef struct {
    int s;
    int f;
    int d ;
} att;

void leggifile(int *N, att **attivita);
void attSel(int N, att *v);
void powerset_r(att *v, att *sol, int *sum_d, int j, int N,  int pos, int start, int *k);
int isvalid(att p, att n, int pos); //p precedente, n next
int isopt(int *sum_d, att *sol, att n, int pos);

int main() {

    att *attività;
    int N = 0;

    leggifile(&N, &attività);
    attSel(N, attività);

    free(attività);

}


void attSel(int N, att *v){
    int sum_d = 0, j, k = 0;
    att *sol = (att*) calloc(N, sizeof(att));

    for(j = 1; j<=N; j++){//j indica il numero di elementi possibili per il corrente insieme delle parti che sto considerando
        powerset_r(v, sol,&sum_d, j, N,0, 0, &k);
    }
    printf("\nI sottoinsiemi che massimizzano la somma delle durate sono %d: \n{ ", k);
    for (int i = 0; i < k; ++i) {
        printf("(%d, %d) ",sol[i].s, sol[i].f);

    }
    printf("} Somma Durate massima: %d\n", sum_d);

    free(sol);
}

void powerset_r(att *v, att *sol, int *sum_d, int j, int N,  int pos, int start, int *k){

    if(pos >= j ){
        return;
    }
    for (int i = start; i < N; ++i) {
        if(isvalid(sol[pos-1], v[i], pos)){ //passo l'elemento corrente alla verifica di validità se le attuali somme delle durate sono inferiori alla summa della durata presente, non le considero
            if(isopt(sum_d, sol, v[i], pos)){
                sol[pos] = v[i];
                *k = j;
            }
            powerset_r(v, sol, sum_d, j, N,  pos+1, i+1, k);
        }
    }
}


void leggifile(int *N, att **attività){
    FILE *fin = fopen(filename,"r" );
    att *temp;

    if(fin == NULL){
        printf("\nErrore nell'apertura del file");
        exit(1);
    }

    fscanf(fin,"%d", N); //letture del numero di attivita presenti nel file
    temp  =(att*) malloc(sizeof (att) * (*N));

    for (int i = 0; i < (*N); ++i) {
        fscanf(fin, "%d %d" ,&temp[i].s, &temp[i].f);
        temp[i].d = temp[i].f - temp[i].s; //affianco all'ora di inizio e di fine la durata dell'attività
    }

    *attività = temp;

}

int isvalid(att p, att n, int pos){
    if(pos== 0){
        return 1;
    }

    if(( p.s < n.f ) && ( n.s < p.f )){   // se l'orario di inizio dell'attività già presente è minore dell'ora di fine della successiva
                                        // e l'orario di inizio dell'attività successiva è inferiore dell'ora di fine della precedente,
                                        // le attività non sono compatibili, ritorna 0
        return 0;
    }
    return 1;
}

int isopt(int *sum_d, att *sol, att n, int pos){
    int temp = 0;

    if(pos == 0){
        if(*sum_d < n.d){
            *sum_d = n.d;
            return 1;
        }
        return 0;
    }
    for (int i = 0; i < pos; ++i) {
        temp += sol[i].d;
    }
    temp += n.d;

    if(temp > *sum_d){ //se la somma delle durate in sol con l'elemento che desidero aggiungere è minore della soluzione migliore già presente, non lo includo nella soluzione
        *sum_d = temp;
        return 1;
    }
    return 0;

}