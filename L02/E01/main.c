#include <stdio.h>

int gcd(int a, int b);

int main() {

    int a , b, MCD;

    printf("inserire il primo numero\n");
    scanf("%d", &a);
    printf("inserire il secondo numero\n");
    scanf("%d", &b);

    MCD = gcd(a,b);
    printf("il massimo comune divisore e' %d", MCD);

    return 0;
}


int gcd(int a, int b) {

    if (a>b) {                            ///CASO DI A E B PARI
        if (a % 2 == 0 && b % 2 == 0) {         /// A E B PARI
            return 2 * gcd(a/2, b/2);
        }
        else if (a % 2 != 0 && b % 2 == 0){     /// A DISPARI B PARI
            return gcd(a, b/2);
        }
        else if (a % 2 == 0 && b % 2 != 0){     /// A PARI B DISPARI
            return gcd(a/2, b);
        }
        else if (a % 2 != 0 && b % 2 != 0){     /// A E B DISPARI
            return gcd((a-b)/2, b);
        }
    }
    else if (a<b) {                       ///CASO DI A E DISPARI
        if (b % 2 == 0 && a % 2 == 0) {         /// ENTRAMBI PARI
            return 2 * gcd(b/2, a/2);
        }
        else if (b % 2 != 0 && a % 2 == 0){     /// A(B) PARI E B(A) DISPARI
            return gcd(b, a/2);
        }
        else if (b % 2 == 0 && a % 2 != 0){     /// A(B) DISPARI E B(A) PARI
            return gcd(b/2, a);
        }
        else if (b % 2 != 0 && a % 2 != 0){     ///ENTRAMBI DISPARI
            return gcd((b-a)/2, a);
        }
    }
    else if(a == b)
        return a;               /// CASO TERMINATORE ( A = B )

}
/*
int gcd(int a, int b) {

    if (a>b) {                            ///CASO DI A E B PARI
        if (a % 2 == 0 && b % 2 == 0) {         /// A E B PARI
            return 2 * gcd(a/2, b/2);
        }
        else if (a % 2 != 0 && b % 2 == 0){     /// A DISPARI B PARI
            return gcd(a, b/2);
        }
        else if (a % 2 != 0 && b % 2 != 0){     /// A E B DISPARI
            return gcd((a-b)/2, b);
        }
        else if (a % 2 == 0 && b % 2 != 0){     /// A PARI B DISPARI
            if(a % b == 0)
                return b;
            else
                return 1;
        }
    }
    else if (a<b) {                       ///CASO DI A E DISPARI
        if (b % 2 == 0 && a % 2 == 0) {         /// ENTRAMBI PARI
            return 2 * gcd(b/2, a/2);
        }
        else if (b % 2 != 0 && a % 2 == 0){     /// A(B) PARI E B(A) DISPARI
            return gcd(b, a/2);
        }
        else if (b % 2 != 0 && a % 2 != 0){     ///ENTRAMBI DISPARI
            return gcd((b-a)/2, a);
        }
        else if (b % 2 == 0 && a % 2 != 0){     /// B PARI A DISPARI
            if(b % a == 0)
                return a;
            else
                return 1;
        }
    }

}*/
