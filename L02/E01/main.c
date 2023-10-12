#include <stdio.h>
int gcd(int n1, int n2);
int main(void) {
    //Inizializzazione variabili
    int n1, n2, mcd;
    //Corpo programma
    printf("Inserisci primo numero (intero):");
    scanf("%d",&n1);
    printf("Inserisci secondo numero (intero):");
    scanf("%d", &n2);

    mcd = gcd(n1,n2);
    printf("Il Massimo Comune Divisore vale: %d\n", mcd);
    if(mcd == 1){
        printf("I due numeri inseriti sono primi tra loro.\n");
    }
    return 0;
}

int gcd(int n1, int n2){
    //Inizializzazione variabili
    int scambio;
    //Corpo funzione
    if(n1 < n2){
        scambio = n1;
        n1 = n2;
        n2 = scambio;
    }
    if(n2 == 0){
        return n1;
    }
    else if(n1 % 2 == 0 && n2 % 2 == 0){
        return 2*gcd(n1/2, n2/2);
    }
    else if(n1 % 2 != 0 && n2 % 2 == 0){
        return gcd(n1, n2/2);
    }
    else if(n1 % 2 == 0 && n2 % 2 != 0){
        return gcd(n1/2, n2);
    }
    else{
        return gcd((n1-n2)/2, n2);
    }
}
