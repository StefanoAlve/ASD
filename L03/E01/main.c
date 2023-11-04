#include <stdio.h>
#include <malloc.h>
int majority(int *a,int N){// funzione ricorsiva di ricerca del numero maggioritario all interno di un vettore
    //lunghezza N
    int i,count = 0;// count ricorrenze all'interno del vettore
    // sono arrivato alla fine del vettore quindi ritorno -1
    if (a[0] < 0)
        return -1;
    for (i = 0;i<N;i++){
        if (a[i]<0)
            break;
        if (a[0] == a[i])
            count++;
    }
    if (count>N/2)//condizioene di terminazione
        return a[0];
    return majority(a+1,N);

};
int main() {
    int N,i,max;
    int *vet;
    printf("Inserisci la lunghezza del vettore:\n");
    scanf("%d",&N);
    vet = malloc((N+1)*sizeof(int));
    //inserisco -1 alla fine del vettore
    vet[N] = -1;

    for(i=0;i<N;i++){
        printf("Inserisci il valori del vettore:\n");
        scanf("%d",&(vet[i]));
    }
    max = majority(vet,N);
    printf("%d",max);
    free(vet);
}

