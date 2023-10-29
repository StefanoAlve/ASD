#include <stdio.h>
#include <stdlib.h>
#define MAXN 50
int majority( int *a, int N);

int bool = 1;

int main() {
    int *vet, nn, tmp, i, magg, lunghezzaVett=0;

    ///POPOLO IL VETTORE
    printf("di quanti numeri e' il vettore?");
    scanf("%d", &nn);

    ///LO ALLOCO DINAMICAMENTE
    vet = (int *)malloc((nn+1)*sizeof(int));
    if (vet == NULL) {
        /// GESTIONE ERRORE IN ALLOCAZIONE
        return 1;
    }

    for(i = 0; i < nn; i++){
        printf("inserire il numero (%d rimanenti)", nn - i);
        scanf("%d", &tmp);
        vet[i] = tmp;
    }
    ///NUMERO DI CONTROLLO
    vet[nn]=-1;

    for(i = 0; i < nn; i++){
        printf("%d ", vet[i]);
    }

    /*for (i = 0; vet[i] != -1; i++, lunghezzaVett++){}
    printf("\nla lunghezza del vettore e' %d", lunghezzaVett);*/


    magg = majority(vet, nn);
    printf("\n\nil numero maggioritario e' %d", magg);

    free(vet);

    return 0;
}


int majority( int *a, int N) {
    int magg, i, cont = 1, lunghezzaVett=0;
    magg = a[N-1];

    ///CONTO LA LUNGHEZZA DEL VETTORE
    for (i = 0; a[i] != -1; i++, lunghezzaVett++){}

    ///CONDIZIONE DI TERMINAZIONE
    if (N < lunghezzaVett/2){
        return -1;
    }

    for (i = 2; i <= N; i++){
        if (a[N-i] == magg)
            cont++;
    }

    if (cont > lunghezzaVett/2) {
        return magg;
    }
    else
        majority(a,N-1);

}