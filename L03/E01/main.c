#include <stdio.h>
#include <stdlib.h>
/// IN FONDO è PRESENTE L'analisi della complessità:
int majority_divide(int *a, int N);
int majority_decrease(int *a, int N);
int *riempi_vet(int* N);
void stampa_vet(int *vett, int N);


int main(void)
{
    int *v, N, maggioritario1 = 0, maggioritario2;
    v = riempi_vet(&N);
    stampa_vet(v, N);
    maggioritario1 = majority_divide(v, N);
    maggioritario2 = majority_decrease(v, N);

    if (maggioritario1 != -1)
    {
        printf("\nL'elemento maggioritario con la metodologia divide e' il numero: %d", maggioritario1);
        printf("\nL'elemento maggioritario con la metodologia decrease e' il numero: %d", maggioritario2);
    }
    else
        printf("\nNon ho trovato alcun elemento maggioritario");
    return 0;
}

int *riempi_vet(int* N)
{
    int *ausiliario, i;
    printf("Quanti numeri vuoi inserire?");
    scanf("%d", N);
    ausiliario = (int *)malloc(*N*sizeof(int));
    printf("Inserisci i numeri separati da uno spazio (eg. 2 3 4 5 1):");
    for(i = 0; i < *N; i++)
        scanf("%d", &(ausiliario[i]));
    return ausiliario;
}


void stampa_vet(int *vett, int N)
{
    int i;
    printf("\nIl seguente vettore contiene:\n");
    for (i = 0; i<N; i++)
        printf("%d ", vett[i]);
    printf("\n");
}


int majority_divide(int *a, int N)
{
    int left, right, i, pm = N/2, l, contL = 0, contR = 0;
    // condizioni di terminazione
    if (N==1)
        return a[0];
    // assegnazione estremi
    l = pm;
    left = majority_divide(a, l);
    right = majority_divide(a + l, N-l);
    if (left == right) // se il maggioritario dei sotto vettori è uguale
        return left;
    else // se il maggioritario degli elementi è diverso
    {
        for (i = 0; i < N; i++) {
            if (a[i] == left)
                contL++;
            else if (a[i] == right)
                contR++;
        }
        if (contL > pm)
            return left;
        else if (contR > pm)
            return right;
    }
    // se non trovo un elemento maggioritario in uno dei sottovettori ritorno -1 o a left o a right
    return -1;
}


int majority_decrease(int *a, int N)
{
    int i, cont1 = 0, cont2 = 0;
    if(N == 1)
        return *a;
    majority_decrease(a+1, N-1);
    if(*a == a[N-1])
        return *a;
    else if(*a != a[N-1])
    {
        for (i = 0; i < N; i++) {
            if (a[i] == a[N - 1])
                cont1++;
            else if(a[i] == *a)
                cont2++;
        }
        if (cont1 > N / 2)
            return a[N - 1];
        else if(cont2 > N/2)
            return *a;
    }
    // se non trovo un elemento maggioritario nel sottovettore ritorno -1
    return -1;
}

/// PREMESSE
// Assumerò che il costo della ricombinazione in entrambi i casi sia O(n) in quanto, nel caso peggiore il for dovrebbe fare n iterazioni per decretare il maggioritario
// e che il costo della divisione D(n) = O(1) assumento la divisione una operazione di complessità unitaria da cui O(1) + O(n) = O(n)
/// DIVIDE
/* T(n) = D(n) + a*T(n/b)+C(n)     dove a = num.sottoproblemi = 2 e b=fattore di divisione = 2
 * T(n) = O(1) + 2T(n/2) + O(n)     = 2T(n/2) + n ===> T(n) = n+ 2(n/2) + 4(n/4) + 8(n/8) +16T(n/16)
 * T(n/2) = 2T(n/4) + n/2 = n/2 + 2(n/4) + 4(n/8) + 8T(n/16)
 * T(n/4) = 2T(n/8) + n/4 = n/4 + 2(n/8) + 4T(n/16)
 * T(n/8) = 2T(n/16) + n/8
 * T(n) = sommatoria che va da i = 0 a i = log2(n) (poichè si fanno 2^i passi per arrivare a terminazione) di n e quindi T(n) = O(nlogn)
*/
/// DECREASE
/* T(n) = D(n) + T(n-k) + C(n)     dove k = fattore di decremento =1
 * T(n) = T(n-1) + n = n + (n-1)+ (n-2) + T(n-3)  = n + (n-1) + (n-2) +...+3+2+1 = (n+1) + (n+1) + (n+1) +...
 * T(n-1) = T(n-2) + n-1 = T(n-3) + (n-2) + (n-1)
 * T(n-2) = T(n-3) + n-2
 * T(n) = sommatoria che va da i=0 a i = (n-1) (n+1) = O(n^2)
*/

/// Complessivamente la divide è più efficiente della decrease.