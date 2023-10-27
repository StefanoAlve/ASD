#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 30

int **malloc2dR(char NomeFile[], int *nr, int *nc);
void separa(int **mat, int *vBianchi, int *vNeri, int nr, int nc, int *nB, int *nN);

int main() {
    char NomeFile[MAXN];
    int i, nr, nc, nB=0, nN=0, **matrice, *vBianchi=NULL, *vNeri=NULL;
    printf("Inserire il nome del file:\n");
    scanf("%s",NomeFile);
    matrice = malloc2dR(NomeFile,&nr,&nc);

    //Stampa a video della matrice
    printf("La matrice del file e':\n");
    for (i = 0; i < nr; i++){
        for(int j = 0; j < nc; j++){
            printf("%d ", matrice[i][j]);
        }
        printf("\n");
    }

    separa(matrice,vBianchi,vNeri,nr,nc,&nB,&nN);

    return 0;
}

int **malloc2dR(char NomeFile[], int *nr, int *nc){
    FILE *fp;
    int **mat;
    int i,j;

    fp = fopen(NomeFile,"r");
    if (fp == NULL){
        printf("Errore nell'apertura file\n");
        exit(1);
    }
    fscanf(fp,"%d %d", nr, nc);

    //Allocazione dinamica matrice e riempimento matrice
    mat = (int **)malloc((*nr)*(sizeof(int *))); //Allocazione vettore di puntatori
    if (mat == NULL) exit(1);
    for (i = 0; i < *nr; i++){
        mat[i] = (int *)malloc((*nc)* sizeof(int)); //Allocazione vettori di interi
        if (mat[i] == NULL) exit(1);
        for (j = 0; j < *nc; j++){
            if (!feof(fp)) fscanf(fp,"%d",&mat[i][j]);
        }
    }
    fclose(fp);
    return mat;
}

void separa(int **mat, int *vBianchi, int *vNeri, int nr, int nc, int *nB, int *nN){
    int i,j;
    int DimTotMat = nr*nc;

    //Allocazione dinamica vettori di interi a seconda della dimensione totale della matrice
    if (DimTotMat%2 == 0){
        vBianchi = (int *) malloc((DimTotMat/2)* sizeof(int));
        vNeri = (int *) malloc((DimTotMat/2)* sizeof(int));
    } else {
        vBianchi = (int *) malloc(((DimTotMat/2)+1) * sizeof(int));
        vNeri = (int *) malloc((DimTotMat/2) * sizeof(int));
    }
    if (vBianchi == NULL || vNeri == NULL) exit(1);

    //Inserimento valori della matrice nei 2 vettori
    for (i=0;i<nr;i++){
        for (j=0;j<nc;j++){
            if((i+j)%2 == 0){
                //Si decide che la scacchiera comicia con i bianchi
                vBianchi[*nB] = mat[i][j];
                (*nB)++;
            } else {
                vNeri[*nN] = mat[i][j];
                (*nN)++;
            }
        }
    }

    //Stampa a video dei vettori
    printf("Numeri nelle celle bianche:\n");
    for (i = 0; i < *nB; i++){
        printf("%d ",vBianchi[i]);
    }

    printf("\nNumeri nelle celle nere:\n");
    for (i = 0; i < *nN; i++){
        printf("%d ",vNeri[i]);
    }

    //Deallocazione memoria
    for(i = 0; i < nr; i++){
        free(mat[i]);
    }
    free(mat);
    free(vNeri);
    free(vBianchi);

}