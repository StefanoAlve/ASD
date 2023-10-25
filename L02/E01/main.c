#include <stdio.h>

int GCD(int a, int b);

int main() {
    int a=0,b=0,gcd,tmp;
    printf("Inserire 2 numeri interi separati da spazio: ");
    scanf("%d%d",&a,&b);
    if (b>a){
        tmp = a; a = b; b = tmp;
    }
    gcd = GCD(a,b);
    printf("MCD:\n%d",gcd);

    return 0;
}

int GCD(int a, int b){
    int tmp;
    if (b == 0){
        return a;
    }
    if (b>a){
        tmp = a; a = b; b = tmp;
    }
    if (a%2 == 0 && b%2 == 0){
        return 2*GCD(a/2,b/2);
    } else if (a%2 != 0 && b%2 == 0){
        return GCD(a,b/2);
    } else if (a%2 != 0 && b%2 != 0){
        return GCD((a-b)/2,b);
    } else if (a%2 == 0 && b%2 != 0){
        return GCD(a/2,b);
    }
}