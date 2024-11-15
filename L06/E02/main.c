#include <stdio.h>

int max(int a, int b);
int fZ(int pietre[], int l, int solZ[10][10][10][10], int solR[10][10][10][10], int solT[10][10][10][10], int solS[10][10][10][10]);
int fR(int pietre[], int l, int solZ[10][10][10][10], int solR[10][10][10][10], int solT[10][10][10][10], int solS[10][10][10][10]);
int fT(int pietre[], int l, int solZ[10][10][10][10], int solR[10][10][10][10], int solT[10][10][10][10], int solS[10][10][10][10]);
int fS(int pietre[], int l, int solZ[10][10][10][10], int solR[10][10][10][10], int solT[10][10][10][10], int solS[10][10][10][10]);


int main() {
    //Num pietre in ordine : z r t s
    int pietre[4] = {2,5,3,4};
    int solZ[10][10][10][10];
    int solR[10][10][10][10];
    int solT[10][10][10][10];
    int solS[10][10][10][10];
    int l = 0;
    printf("%d\n", fS(pietre, l, solZ, solR, solT, solS));
    return 0;
}

int max(int a, int b){
    if (a > b)
        return a;
    return b;
}

int fZ(int pietre[], int l, int solZ[10][10][10][10], int solR[10][10][10][10], int solT[10][10][10][10], int solS[10][10][10][10]){



    if (pietre[0] == 0){
        return l;
    }
    pietre[0]--; l++;
    int l1 = fZ(pietre, l, solZ, solR, solT, solS);
    int l2 = fT(pietre, l, solZ, solR, solT, solS);
    pietre[0]++;
    return max(l1, l2);
}

int fT(int pietre[], int l, int solZ[10][10][10][10], int solR[10][10][10][10], int solT[10][10][10][10], int solS[10][10][10][10]){
    if (pietre[2] == 0){
        return l;
    }
    pietre[2]--; l++;
    int l1 = fS(pietre, l, solZ, solR, solT, solS);
    int l2 = fR(pietre, l, solZ, solR, solT, solS);
    pietre[2]++;
    return max(l1, l2);
}

int fS(int pietre[], int l, int solZ[10][10][10][10], int solR[10][10][10][10], int solT[10][10][10][10], int solS[10][10][10][10]){
    if (pietre[3] == 0){
        return l;
    }
    pietre[3]--; l++;
    int l1 = fS(pietre, l, solZ, solR, solT, solS);
    int l2 = fR(pietre, l, solZ, solR, solT, solS);
    pietre[3]++;
    return max(l1, l2);
}

int fR(int pietre[], int l, int solZ[10][10][10][10], int solR[10][10][10][10], int solT[10][10][10][10], int solS[10][10][10][10]){
    if (pietre[1] == 0){
        return l;
    }
    pietre[1]--; l++;
    int l1 = fZ(pietre, l, solZ, solR, solT, solS);
    int l2 = fT(pietre, l, solZ, solR, solT, solS);
    pietre[1]++;
    return max(l1, l2);
}