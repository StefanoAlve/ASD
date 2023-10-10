#include <stdio.h>
#define maxN 30
int sottoSequenze(int V[], int N);
int main(void) {
    //inizializzazione variabili
    int V[maxN],count,N;
    //assegnazione variabili
    count = 0;
    //corpo programma
    printf("Quanti numeri vuoi inserire? (max 30):");
    if(scanf(" %d",&N)!=1){
        printf("Valore inserito non valido\n");
        return 1;
    }
    else if(N<=maxN) {
        while (count < N) {
            printf("\nInserire nuovo numero (numero: %d):",count+1);
            if (scanf(" %d", &V[count]) == 1) {
                count++;
            } else {
                printf("Valore inserito non valido\n");
                return 2;
            }
        }
        printf("Il vettore da te creato e':\n( ");
        for (int i = 0; i < count; i++) {
            printf("%d ", V[i]);
        }
        printf(")\n");
        sottoSequenze(V, count);
    }
    else{
        printf("Numero di valori maggiore di quello massimo consentito (%d)\n",maxN);
        return 3;
    }
    return 0;
}

//funzioni

int sottoSequenze(int V[], int N){
    int count, max;
    count=0;
    for(int i=0; i<N; i++){
        if(V[i] != 0){
            count++;
            if (count > max){
               max = count;
            }
        }
        else{
            count=0;
        }
    }
    count=0;
    printf("I sottovettori di dimensione massima (%d) sono:\n",max);
    for(int i=0; i<N; i++){
        if(V[i] != 0){
            count++;
            if (count == max){
                printf("( ");
                for(int j=i-(max-1); j<(count+(i-(max-1))); j++){
                    printf("%d ",V[j]);
                }
                printf(") ");
            }
        }
        else{
            count=0;
        }
    }
    printf("\n");
    return 0;
}