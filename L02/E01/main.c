#include <stdio.h>
#include <math.h>

int gcd(int n1, int n2);
int main(void) {
    //Inizializzazione variabili
    int n1, n2, mcd;
    //Corpo programma
    printf("Inserisci primo numero (intero):");
    scanf("%d",&n1);
    printf("Inserisci secondo numero (intero):");
    scanf("%d", &n2);
    if(n1 < 0 || n2 < 0){
        n1 = abs(n1);
        n2 = abs(n2);
        printf("Dato che sono presenti numeri negativi ne eseguo il modulo: n1 = %d, n2 = %d\n\n",n1,n2);
    }
    mcd = gcd(n1,n2);
    printf("Il Massimo Comune Divisore vale: %d\n", mcd);
    if(mcd == 1){
        printf("I due numeri inseriti sono primi tra loro.\n");
    }
    return 0;
}

int gcd(int n1, int n2){
    //Funzione ricorsiva che trova massimo comune divisore

    //Inizializzazione variabili
    int scambio;
    //Corpo funzione
    if(n1 < n2){ //Se il secondo numero fosse più grande del primo li scambio
        scambio = n1;
        n1 = n2;
        n2 = scambio;
    }
    if(n1%n2==0){ //Condizione di terminazione (il primo numero è divisibile per il secondo)
        return n2;
    }
    else if(n1 % 2 == 0 && n2 % 2 == 0){ //primo e secondo numero entrambi pari
        return 2*gcd(n1/2, n2/2);
    }
    else if(n1 % 2 != 0 && n2 % 2 == 0){ //primo numero dispari e secondo pari
        return gcd(n1, n2/2);
    }
    else if(n1 % 2 == 0 && n2 % 2 != 0){ //primo numero pari e secondo dispari
        return gcd(n1/2, n2);
    }
    else{ //entrambi i numeri dispari
        return gcd((n1-n2)/2, n2);
    }
}
