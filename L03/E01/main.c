#include <stdio.h>
#include <malloc.h>
int majority(int *a,int N){
    int i,count = 0;

    if (a[0] < 0)
        return -1;
    for (i = 0;i<N;i++){
        if (a[0] == a[i])
            count++;
    }
    if (count>N/2)
        return a[0];
    return majority(a+1,N);

};
int main() {
    int N,i,max;
    int *vet;
    printf("Inserisci la lunghezza del vettore:\n");
    scanf("%d",&N);
    vet = malloc((N+1)*sizeof(int));
    vet[N] = -1;
    for(i=0;i<N;i++){
        printf("Inserisci il valori del vettore:\n");
        scanf("%d",&(vet[i]));
    }
    max = majority(vet,N);
    printf("%d",max);
    free(vet);
}

