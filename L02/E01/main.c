#include <stdio.h>
/// DICHIARAZIONE FUNZIONI
int gcd(int a, int b);
void swap(int* a,int* b);

int main(void)
{
    int a, b, mcd;
    printf("Inserisci i numeri a e b di cui vuoi calcolare il MCD:");
    scanf("%d %d", &a, &b);
    printf("Calcolo il massimo comune divisore tra: %d e %d\n", a,b);
    mcd = gcd(a,b);
    printf("Il massimo comune divisore tra %d e %d e': %d",a,b,mcd);
    getchar();
    return 0;
}


int gcd(int a, int b)
{
    if (b>a)
        swap(&a, &b);
    /// CONDIZIONI DI TERMINAZIONE
    if(a%b == 0)
        return b;
    /// a and b are even
    if(a % 2 == 0 && b % 2 == 0)
        return 2*gcd((int)a/2, (int)b/2);
    /// a is odd and b is even
    else if(a%2 != 0 && b%2 == 0)
        return gcd(a, (int)b/2);
    /// a is even and b is odd
    else if(a%2 == 0 && b%2 != 0)
        return gcd((int)a/2, b);
    /// a and b are odds
    else
        return gcd((int)(a-b)/2, b);
}

void swap(int* a,int* b){
    int c;
    c = *a;
    *a = *b;
    *b = c;
}