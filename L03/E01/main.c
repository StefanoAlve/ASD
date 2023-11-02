#include <stdio.h>
int majority( int *a, int N);


int main() {
    int a [] = {3,3,9,4,3,5,3};
    int N =7, result = 0;
    result = majority(a,N);
    printf("result: %d", result);

    return 0;
}


int majority( int *a, int N){
    int mid = N/2, l = 0;
    int leftmajority = 0, rightmajority = 0, countL =0, countR = 0;

    if(N == 1){
        return a[0]; //se ho N = 1 l'unico elemento del vettore è sicuramente maggioritario
    }

    leftmajority = majority(a, mid);
    rightmajority = majority(a+mid, N-mid);

    if(leftmajority == rightmajority){
        return rightmajority;
    }
    else{
        for (int i = 0; i < N ; ++i) {
            if(a[i] == leftmajority){
                countL++;
            }
            else if(a[i] == rightmajority) {
                countR++;
            }
        }
        if(countL > mid){
            return leftmajority;
        }
        else if (countR > mid){
            return rightmajority;
        }

    }
    return -1;
}