#include <stdio.h>
#include <math.h>
#include <ctype.h>

int gcd(int a, int b);

int main() {
    //inizializzo numeri
    int mcd, a, b, temp;
    printf("Inserire due numeri interi positivi:");
    printf("\n\t_inserisci il primo numero->");
    if (scanf("%d", &a) != 1) {
        printf("\nErrore.Dato non consistente.");
        return 1;
    }
    printf("\t    _inserisci il secondo numero->");
    if (scanf("%d", &b) != 1) {
        printf("\nErrore.Dato non consistente.");
        return 1;
    }
    //scambio valori nel caso a<b
    if (b > a) {
        temp = a;
        a = b;
        b = temp;
    }
    printf("\nCalcolo del MCD ricorsivamente.\na=%d\nb=%d",a,b);
    mcd = gcd(a, b);
    printf("\nIl massimo comune divisore tra %d e %d e': %d", a, b, mcd);
    return 0;
}

int gcd(int a, int b) {
    if (a % b == 0) {//cond terminazione
        return b;
    }
    if(a%2==0 && b%2==0){//a,b pari
        return 2*gcd(a/2,b/2);
    }else if(a%2!=0 && b%2==0){//a dispari,b pari
        return gcd(a,b/2);
    }
    else if(a%2!=0 && b%2!=0){//a,b dispari
        return gcd(((a-b)/2),b);
    }else{//a pari, b dispari
        return gcd(a/2,b);
    }
}
