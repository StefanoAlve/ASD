#include <stdio.h>
#include <stdlib.h>
#define nomeFile "mat.txt"

int **malloc2dR(int nr, int nc, FILE *inFile);
void deAlloca(int **matrice, int nr);

int main() {
    int nr, nc, **matrix;
    FILE *inFile;

    //Apertura file
    if((inFile = fopen(nomeFile, "r")) == NULL){
        printf("Errore nell'apertura del file.\n");
        exit(1);
    }

    //Dimensione matrice
    fscanf(inFile, "%d %d", &nr, &nc);

    //Allocazione e riempimento matrice
    matrix = malloc2dR(nr, nc, inFile);

    fclose(inFile);
    deAlloca(matrix, nr);

    return 0;
}

//Allocazione e riempimento matrice
int **malloc2dR(int nr, int nc, FILE *inFIle){
    int **matrix;

    //Allocazione colonne
    matrix = (int **)malloc(nr * sizeof(int *));
    if(matrix == NULL){
        printf("Errore nell'allocazione delle colonne\n");
        exit(1);
    }
    //Allocazione righe
    for (int i = 0; i < nr; i++) {
        matrix[i] = (int *)malloc(nc * sizeof(int));
        if(matrix[i] == NULL){
            printf("Errore nell'allocazione delle righe\n");
            exit(1);
        }
    }

    //Riempimento matrice
    for(int i = 0; i < nr; i++){
        for(int j = 0; j < nc; j++){
            fscanf(inFIle, "%d ", &matrix[i][j]);
        }
    }

    return matrix;
}

//Dealloca la matrice
void deAlloca(int **matrice, int nr){

    for(int i = 0; i < nr; i++) free(matrice[i]);

    free(matrice);
}

