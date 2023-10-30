#include <stdio.h>
#include <stdlib.h>

#define MAXR 50

int **malloc2dR(char file[], int *nr, int *nc);
void separa(int **mat, int nr, int nc, int **vBianco, int **vNero, int *bia, int *ner);

int main() {
    int **mat, nr, nc, i, j, *vBianco = NULL, *vNero = NULL, bia = 0, ner = 0;
    char file[MAXR];

    printf("inserire nome file:\n");
    scanf("%s", file);

    mat = malloc2dR(file, &nr, &nc);

    for(i=0; i<nr; i++){
        for(j=0; j<nc; j++){
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }

    separa(mat, nr, nc, &vBianco, &vNero, &bia, &ner);

    ///STAMPO I VETTORI
    for(i=0; i< bia; i++){
        printf("%d ", vBianco[i]);
    }
    printf("\n");
    for(i=0; i < ner; i++){
        printf("%d ", vNero[i]);
    }

    ///DEALLOCO
    for(i=0; i<nr; i++){
        free(mat[i]);
    }
    free(mat);
    free(vBianco);
    free(vNero);


    return 0;
}

int **malloc2dR(char file[], int *nr, int *nc) {
    int **mat, i, j;
    FILE *fp;

    ///APRO IL FILE E LEGGO IL NUMERO RIGHE E COLONNE DELLA MATRICE
    fp = fopen(file,"r");
    if (fp==NULL){
        printf("errore in apertura file");
        exit(1);
    }

    if (fscanf(fp, "%d %d", nr, nc) != 2) {
        printf("errore nella lettura di nr e nc\n");
        exit(1);
    }
    printf("%d %d\n", *nr, *nc);

    ///ALLOCAZIONE RIGHE
    mat = (int **)malloc((*nr)*(sizeof(int *)));
    if (mat == NULL) {
        printf("errore in allocazione righe");
        exit(1);
    }
    for (i=0; i<(*nr); i++) {
        mat[i] = (int *)malloc((*nc)*(sizeof(int)));            ///ALLOCAZIONE COLONNE
        if (mat[i] == NULL) {
            printf("errore in allocazione colonne");
            exit(1);
        }

        for (j = 0; j < (*nc); j++) {
            fscanf(fp,"%d", &mat[i][j]);
        }
    }


    fclose(fp);

    return mat;
}

void separa(int **mat, int nr, int nc, int **vBianco, int **vNero, int *bia, int *ner) {
    int i, j, cambio=1, *pBianco, *pNero, contb=0, contn=0;

    ///INSERISCO LA DIMENSIONE DEI DUE PUNTATORI A I VETTORI
    if(nr*nc % 2 == 0){
        pBianco = (int*)malloc(((nr*nc)/2)*sizeof(int));
        pNero = (int*)malloc(((nr*nc)/2)*sizeof(int));
    }
    else{
        pBianco = (int*)malloc((((nr*nc)/2) + 1)*sizeof(int));
        pNero = (int*)malloc((((nr*nc)/2) - 1)*sizeof(int));
    }

    ///RIEMPIMENTO DEI PUNTATORI A VETTORE
    for(i=0; i<nr; i++){
        for(j=0; j<nc; j++){
            if (cambio){

                pBianco[contb] = mat[i][j];
                cambio = 0;
                contb++;
            }
            else {

                pNero[contn] = mat[i][j];
                cambio = 1;
                contn++;
            }
        }
    }


    printf("%d %d\n", contb, contn);

    ///RIMANDO AL MAIN I VETTORI E LE LUNGHEZZE DEGLI STESSI
    *vBianco = pBianco;
    *vNero = pNero;
    *bia=contb;
    *ner=contn;

}