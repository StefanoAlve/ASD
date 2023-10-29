#include <stdio.h>

int gcd(int a, int b);
void swap(int* a,int* b);

int main() {
    int a = 600, b = 54, mcd = 0;
    //printf("Inserisci i due numeri a e b di cui vuoi calcolare l'MCD:");
    //scanf("%d, %d");
    mcd = gcd(a,b);
    printf("ecco l'MCD di %d e %d : %d",a,b,mcd);
    return 0;
}

int gcd(int a, int b){

    if(a<b){
        swap(&a, &b);
    }
    if (a % b == 0){
        return b;
    }
    if(a % 2 == 0 && b % 2 == 0){
        return 2*gcd(a/2, b/2);
    }
    else if(a % 2 != 0 && b % 2 == 0) {
        return gcd(a, b / 2);
    }
    else if (a % 2 == 0 && b % 2 != 0){
        return gcd(a/2, b);
    }
    else if (a % 2 != 0 && b % 2 != 0){
        return gcd((a-b)/2, b);
    }
}

void swap(int* a,int* b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}