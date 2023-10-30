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
void separa(int **mat,int nr,int nc,int **vetW,int **vetB) {
    int i, j, countW = 0,countB=0;
    for (i = 0;i<nr;i++){
        for(j=0;j<nc;j++){
            if ((i+j)%2==0)
                countW++;
            else
                countB++;
        }
    }
    *vetW = (int*) malloc(countW * sizeof(int));
    *vetB = (int*) malloc(countB * sizeof(int));
    int B=0,W = 0;
    for (i = 0; i < nr; i++) {
        for (j = 0; j < nc; j++) {
            if ((i + j) % 2 == 0) {
                (*vetW)[W] = mat[i][j];
                W++;
            }
            if ((i + j) % 2 != 0) {
                (*vetB)[B] = mat[i][j];
                B++;
            }
        }
    }

    printf("Nel vettore bianco ci sono: \n");
    for(int k = 0;k<countW;k++){
        printf("%d",(*vetW)[k]);
    }
    printf("\n");
    printf("Nel vettore nero ci sono: \n");
    for(int d = 0;d<countB;d++){
        printf("%d",(*vetB)[d]);
    }



}
int main() {
    int nr=3,nc=3;
    int i,j;
    int **matr;
    int *vetW,*vetB;
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
    separa(matr,nr,nc,&vetW,&vetB);
    free2d(matr,nr);
    fclose(fin);
    free(vetW);
    free(vetB);
}

