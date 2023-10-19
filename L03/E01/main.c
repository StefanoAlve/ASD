#include <stdio.h>
#include <stdlib.h>

int majority(int *a, int N);

int main(void) {
    //Inizializzazione variabili
    int mag, *a, N;
    //Corpo programma
    printf("Inserisci numero di elementi:");
    scanf("%d", &N);
    //Allocazione dinamica del vettore
    a = (int*)malloc(N*sizeof(int));

    for(int i = 0; i<N; i++){
        printf("Inserisci valore della cella %d:", i+1);
        scanf("%d", &a[i]);
    }
    mag = majority(a, N);
    if(mag >= 0){
        printf("\nL'elemento maggioritario vale: %d\n", mag);
    }
    else{
        printf("\nNon esiste un elemento maggioritario\n");
    }
    //Deallocazione vettore
    free(a);
    return 0;
}

int majority(int *a, int N){
    int m = N/2, lMajority, rMajority, leftCount = 0, rightCount = 0;

    if(N==0){
        //Il caso in cui la dimensione del vettore fosse 0 non esiste maggioritario
        return -1;
    }

    if(N==1){
        //Caso limite, sottovettori di dimensione 1 il maggioritario è per forza il numero
        return a[0];
    }

    //Spezzo il vettore in due sottovettori
    lMajority = majority(a, m);
    rMajority = majority(a+m, N-m);

    if(lMajority == rMajority){
        //se il maggioritario di entrambi i sottovettori è lo stesso allora sarà il maggioritario del vettore intero
        return lMajority;
    }
    else{
        //Nel caso in cui fossero diversi vado a cercare nel vettore quale dei due compare più volte
        for(int i = 0; i<N && N > 2; i++){ //Si può notare che se l'array ha dimensione 2 e gli elementi sono diversi non sarà mai presente un maggioritario quindi aggiungo la condizione N>2 per saltare il ciclo
            if(a[i] == lMajority){
                leftCount++;
            }
            else if(a[i] == rMajority){
                rightCount++;
            }
        }
        //Nel caso in cui si satasse il ciclo lefC e rightC saranno 0 quindi restituisco -1
        if(leftCount > m){
            //Se lMajority compare più volte del valore della metà del vettore allora lo restituisco
            return lMajority;
        }

        if(rightCount > m){
            //Se rMajority compare più volte del valore della metà del vettore allora lo restituisco
            return rMajority;
        }

        //Se non trovo un maggioritario ritorno -1
        return -1;
    }


}