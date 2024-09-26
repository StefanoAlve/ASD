#include <stdio.h>

int gcd(int a, int b);

int main(){
    int a, b, temp, GCD;

    printf("Inserire due numeri interi positivi: \n");
    scanf("%d%d", &a, &b);

    if (a<b) {temp = a; a = b; b = temp;} //scambio a e b se b > a
    GCD = gcd(a,b);

    printf("Il gcd di a e b e': %d", GCD);

    return 0;
}

int gcd(int a, int b){
    int temp;
    if (a<b) {temp = a; a = b; b = temp;}
    if (a%b == 0) return b; //condizione di terminazione: a è divisibile per b, ritorno b
    if (a%2 == 0 && b%2 == 0) return 2*gcd(a/2, b/2);
    if (a%2 != 0 && b%2 == 0) return gcd(a, b/2);
    if (a%2 != 0 && b%2 != 0) return gcd((a-b)/2, b);
    return gcd(a/2, b); //ultimo caso se a è pari e b è dispari
}