#include <stdio.h>

int gcd1(int x, int y) {
    if (x > y) { //se il primo numero è più grande del secondo
        if (x % 2 == 0 && y % 2 == 0) {
            return 2 * (gcd1((x / 2), (y / 2)));
        }
        else if (x % 2 != 0 && y % 2 == 0) {
            return gcd1(x, (y / 2));
        }
        else if (x % 2 != 0 && y % 2 != 0) {
            return gcd1((x - y) / 2, y);
        }
        else if(x%2 ==0 && y%2 !=0) {
            return gcd1(x / 2, y);
        }
    }
    else if (x<y) // se il primo numero è più piccolo del secondo
    {
        if (x % 2 == 0 && y % 2 == 0)
        {
            return 2 * (gcd1((y / 2), (x / 2)));
        }
        else if (x % 2 != 0 && y % 2 == 0)
        {
            return gcd1(x, y/2);
        }
        else if(x%2==0 && y%2!=0){
                return gcd1(y / 2, x);
        }
        else if (x % 2 != 0 && y % 2 != 0)
        {
            return gcd1(x , (y - x) / 2);
        }

    }
    else if(x == y)// condizione di terminazione
        return x;

}

int main() {
    int num1, num2, franco;
    printf("Digita qui in numeri di cui vuoi sapere il massimo comun divisore: ");
    scanf("%d %d", &num1, &num2);
    franco = gcd1(num1,num2);
    printf("il minimo comune multiplo tra %d e %d: \n", num1, num2);
    printf("%d", franco);
}