#include <stdio.h>
#include <stdlib.h>

int majority(int *a, int N);

int main(){
    int N, *a, res;

    //Input
    printf("Inserisci il numero di dati del vettore:\n");
    scanf("%d", &N);

    //Allocazione memoria e costruisco il vettore di uno spazio in piu
    a = (int *) malloc((N+1)*sizeof(int));

    //Eventuali errori
    if(a == NULL) {
        printf("ERRORE ALLOCAZIONE VETTORE\n");
        exit(1);
    }

    //inserisco -1 come ultimo valore
    a[N] = -1;

    //Riempimento vettore
    for(int i = 0; i<N; i++){
        printf("Inserisci numeri di indice %d:", i+1);
        scanf(" %d", &a[i]);
    }

    //Funzione ricorsiva
    res = majority(a, N);

    //Output
    if(res == -1){
        printf("Nessun elemento maggioritario.\n");
    }
    else{
        //Stampa vettore
        printf("VETTORE: ");
        for(int i = 0; i < N; i++) printf("%d ",a[i]);
        printf("\n");

        printf("Elemento maggioritario: %d", res);
    }

    free(a);
    return 0;
}

//Funzione ricorsiva che controlla un vettore di numeri naturali a ogni chiamata un numero per volta
int majority(int *a, int N){
    int count = 0; // Ricorrenze all'interno del vettore

    if(N <= 0)
        return -1; // Se il vettore ha lunghezza minore o uguale a 0 errore

    //Siamo arrivati alla fine del vettore dove c'è -1
    if (a[0] < 0)
        return -1;

    //Confronto con ogni numero del vettore
    for(int i = 0; i < N; i++){

        if(a[i] < 0)
            break;

        if(a[i] == a[0])
            count++; //Trovata corrispondenza
    }

    //Condizione per numero maggioritario
    if (count > N / 2)
        return a[0];

    return majority(a + 1, N);
}
