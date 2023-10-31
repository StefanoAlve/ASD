#include <stdio.h>
#include <stdlib.h>

int **malloc2dR(char *nomeFile, int *nr, int *nc);

void separa(int **mat, int *nr, int *nc, int **vB, int **vN);

void free_mat2dR(int **mat, int *nr);

int main() {
    int **mat = NULL, nr, nc, *vB = NULL, *vN = NULL;
    char nomeFile[30];
    printf("\nInserire il nome del file da aprire: ");
    scanf("%s", nomeFile);
    mat = malloc2dR(nomeFile, &nr, &nc);
    printf("\nSeparando i contenuti delle celle..");
    separa(mat,&nr,&nc,&vB,&vN);
    free_mat2dR(mat, &nr);
    free(vB);
    free(vN);
    return 0;
}

int **malloc2dR(char *nomeFile, int *nr, int *nc) {
    int **mat;
    int i, j;
    FILE *fp;
    if ((fp = fopen(nomeFile, "r")) == NULL) {
        printf("\nErrore. Impossibile aprire il file");
        exit(1);
    }
    printf("\nFile aperto.");
    fscanf(fp, "%d %d", nr, nc);
    printf("\nLeggendoed allocando da %s una matrice di %d righe e %d colonne.\n", nomeFile, *nr, *nc);
    mat = (int **) malloc((*nr) * (sizeof(int *)));
    if (mat == NULL) exit(1);
    for (i = 0; i < (*nr); i++) {
        mat[i] = (int *) malloc((*nc) * sizeof(int *));
        if (mat[i] == NULL) exit(3);
    }
    for (i = 0; i < (*nr); i++) {
        for (j = 0; j < (*nc); j++) {
            fscanf(fp, "%d", &mat[i][j]);
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
    return mat;
}
void separa(int **mat,int *nr,int *nc,int **vB,int **vN){

}
void free_mat2dR(int **mat,int *nr){
    for(int i=0;i<(*nr);i++){
        free(mat[i]);
    }
    free(mat);
}