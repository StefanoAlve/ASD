#include<stdlib.h>
#include<stdio.h>

#define N 4
#define FILENAME "hard_test_set.txt"


int fZ(int ****Z, int ****R, int ****T, int ****S, int z, int r, int t, int s);
int fR(int ****Z, int ****R, int ****T, int ****S, int z, int r, int t, int s);
int fT(int ****Z, int ****R, int ****T, int ****S, int z, int r, int t, int s);
int fS(int ****Z, int ****R, int ****T, int ****S, int z, int r, int t, int s);

int max (int a, int b) {
    if (a > b)
        return a;
    return b;
}

int ****alloca4d(int *numGemme, int init) {
    int i, j, k, l;
    int ****f;
    f = malloc((1+numGemme[0]) * sizeof(int***));
    for(i=0;i<=numGemme[0];i++) {
        f[i] = malloc((1+numGemme[1]) * sizeof(int**));
        for(j=0;j<=numGemme[1];j++) {
            f[i][j] = malloc((1+numGemme[2]) * sizeof(int*));
            for(k=0;k<=numGemme[2];k++) {
                f[i][j][k] = malloc((1+numGemme[3]) * sizeof(int));
                for(l=0;l<=numGemme[3];l++) {
                    f[i][j][k][l] = init;
                }
            }
        }
    }
    return f;
}

int fZ(int ****Z, int ****R, int ****T, int ****S, int z, int r, int t, int s) {
    int nextZ, nextR;
    if (z <= 0)
        return 0;
    if (Z[z][r][t][s] != -1)
        return Z[z][r][t][s];
    /* Z seguito da Z o R */
    nextZ = fZ(Z,R,T,S,z-1,r,t,s);
    nextR = fR(Z,R,T,S,z-1,r,t,s);
    Z[z][r][t][s] = 1+max(nextZ,nextR);
    return Z[z][r][t][s];
}

int fR(int ****Z, int ****R, int ****T, int ****S, int z, int r, int t, int s) {
    int nextS, nextT;
    if (r <= 0)
        return 0;
    if (R[z][r][t][s] != -1)
        return R[z][r][t][s];
    /* R seguito da S o T */
    nextS = fS(Z,R,T,S,z,r-1,t,s);
    nextT = fT(Z,R,T,S,z,r-1,t,s);
    R[z][r][t][s] = 1+max(nextS,nextT);
    return R[z][r][t][s];
}

int fT(int ****Z, int ****R, int ****T, int ****S, int z, int r, int t, int s) {
    int nextZ, nextR;
    if (t <= 0)
        return 0;
    if (T[z][r][t][s] != -1)
        return T[z][r][t][s];
    /* T seguito da Z o R */
    nextZ = fZ(Z,R,T,S,z,r,t-1,s);
    nextR = fR(Z,R,T,S,z,r,t-1,s);
    T[z][r][t][s] = 1+max(nextZ,nextR);
    return T[z][r][t][s];
}

int fS(int ****Z, int ****R, int ****T, int ****S, int z, int r, int t, int s) {
    int nextS, nextT;
    if (s <= 0)
        return 0;
    if (S[z][r][t][s] != -1)
        return S[z][r][t][s];
    /* S seguito da S o T */
    nextS = fS(Z,R,T,S,z,r,t,s-1);
    nextT = fT(Z,R,T,S,z,r,t,s-1);
    S[z][r][t][s] = 1+max(nextS,nextT);
    return S[z][r][t][s];
}


void solveM(char *gemme, int *numGemme, int maxlun) {
    int maxZ, maxR, maxT, maxS;
    int ****Z, ****R, ****S, ****T;
    int ris, z=numGemme[0], r=numGemme[1], t=numGemme[2], s=numGemme[3];
    printf("zaffiri=%d rubini=%d topazi=%d smeraldi=%d\n",z,r,t,s);

    /* Allocazione delle matrici per memoization */
    /* Ogni matrice memorizza la collana pi� lunga iniziante rispettivamente con uno Z, R, T o S a fronte di [i][j][k][l] gemme disponibili per tipo */
    Z = alloca4d(numGemme, -1);
    R = alloca4d(numGemme, -1);
    T = alloca4d(numGemme, -1);
    S = alloca4d(numGemme, -1);

    maxZ = fZ(Z, R, T, S, z, r, t, s);
    maxR = fR(Z, R, T, S, z, r, t, s);
    maxT = fT(Z, R, T, S, z, r, t, s);
    maxS = fS(Z, R, T, S, z, r, t, s);

    ris = max(maxZ, max(maxR, max(maxT, maxS)));
    printf("Collana massima di lunghezza %d\n", ris);
}

int main(void){
    int  i, s, numGemme[N], maxlun, numtestset;
    char gemme[N] = {'Z', 'R', 'T', 'S'};
    FILE *in = fopen(FILENAME, "r");
    if (in == NULL)
        return 0;

    fscanf(in, "%d", &numtestset);
    for (s=0; s<numtestset; s++) {
        printf("Test set #%d\n", s+1);
        maxlun = 0;
        for (i=0; i<N; i++) {
            fscanf(in, "%d", &numGemme[i]);
            maxlun += numGemme[i];
        }
        printf("massima lunghezza possibile %d\n",maxlun);
        solveM(gemme, numGemme, maxlun);

    }
    fclose(in);
    return 0;
}
