#include <stdio.h>
#include "malloc.h"
int **malloc2dR(int nr,int nc){
    int **m;
    int i;
    m =malloc (nr* sizeof(int));
    for (i=0;i<nr;i++){
        m[i]=malloc(nc*sizeof(int));
    }
    return m;
}
void free2d(int **m,int nr){
    int i;
    for(i=0;i<nr;i++)
        free(m[i]);
    free(m);
}
int separa(int **mat,int nr,int nc) {
    int i, j, countW = 0,countB=0;
    int *vetW,*vetB;
    vetW = malloc(countW * sizeof(int));
    vetB = malloc(countB * sizeof(int));
    for (i = 0; i < nr; i++) {
        for (j = 0; j < nc; j++) {
            if ((i + j) % 2 == 0) {
                vetW[countW] = mat[i][j];
                countW++;
            }
            if ((i + j) % 2 != 0) {
                vetB[countB] = mat[i][j];
                countB++;
            }
        }
    }

    printf("Nel vettore bianco ci sono: \n");
    for(int k = 0;k<countW;k++){
        printf("%d",vetW[k]);
    }
    printf("\n");
    printf("Nel vettore nero ci sono: \n");
    for(int d = 0;d<countB;d++){
        printf("%d",vetB[d
        ]);
    }


    free(vetW);
    free(vetB);
}
int main() {
    int nr=3,nc=3;
    int i,j;
    int **matr;
    FILE *fin;
    fin = fopen("mat.txt","r");
    if (fin==NULL){
        printf("Errore in apertura!");
    }
    else{
        fscanf(fin,"%d %d",&nr,&nc);
    }
    matr = malloc2dR(nr,nc);
    for(i = 0;i<nr;i++){
        for(j=0;j<nr;j++){
            fscanf(fin,"%d",&matr[i][j]);
        }
    }
    separa(matr,nr,nc);
    free2d(matr,nr);
    fclose(fin);
}

