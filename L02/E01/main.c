#include <stdio.h>

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
    printf("\nCalcolo del MCD ricorsivamente.\na=%d\nb=%d", a, b);
    mcd = gcd(a, b);
    printf("\nIl massimo comune divisore tra %d e %d e': %d", a, b, mcd);
    return 0;
}

int gcd(int a, int b) {
    if (a % b == 0) {// cond terminazione
        return b;
    } else if (a % 2 == 0 && b % 2 == 0) { //a e b  pari
        return 2 * gcd(a / 2, b / 2);
    } else if (a % 2 != 0 && b % 2 == 0) { //a dispari e b pari
        return gcd(a, b / 2);
    } else if (a % 2 == 0 && b % 2 != 0) { //a pari e b dispari
        return gcd(a / 2, b);
    } else { //a,b disp
        return gcd((a - b) / 2, a);
    }
}
