#include <stdio.h>
#define maxN 20
void trovaMatrice(int coordinate[3], int dim, int M[maxN][maxN], int i, int j);
int main(void) {
    //Inizializzazione variabili
    FILE *fp_read;
    int nr, nc, M[maxN][maxN], dim, coordinate[3],countC, countR;
    char filein[maxN];
    //Assegnazioni variabili
    dim = 1;
    countC = 0;
    countR = 0;
    coordinate[0] = -100000;
    //Apertura file
    printf("Inserire nome file:");
    scanf("%s",filein);
    fp_read = fopen(filein,"r");
    if(fp_read == NULL){
        printf("Errore nell'apertura del file!\n");
        return 1;
    }
    //Corpo programma
    if (fscanf(fp_read, "%d %d ", &nr, &nc) == 2) {
        while (countR < nr) {
            fscanf(fp_read, "%d", &M[countR][countC]);
            printf("%d ", M[countR][countC]);
            if (countC == (nc - 1)) {
                countC = 0;
                countR++;
                printf("\n");
            }
            else{
                countC++;
            }
            if (countR == nr+1){
                printf("\nLa matrice ha dimensioni maggiori di quelle dichiarate\n");
                return 2;
            }
        }
        if(countC != 0){
            printf("\nMancano valori nella matrice inserita!\n");
            return 3;
        }
        while (dim > 0 && dim <= nc && dim <= nr) {
            printf("Inserire dimensione delle sottomatrici quadrate ricercate (numeri <= 0 o numeri maggiori di nc o nr per terminare):");
            if(scanf(" %d", &dim)!=1){
                printf("Valore inserito non valido!\n");
                return 4;
            }
            else {
                if (dim > 0 && (dim <= nc && dim <= nr)){
                    printf("\nLe sottomatrici quadrate di dimensione %d sono:\n", dim);
                    for (int i = 0; i <= nr - dim; i++) {
                        for (int j = 0; j <= nc - dim; j++) {
                            trovaMatrice(coordinate,dim,M,i,j);
                        }

                    }
                    printf("La sottomatrice con la somma massima (%d) e':\n", coordinate[0]);
                    for (int c = 0; c < dim; c++) {
                        for (int v = 0; v < dim; v++) {
                            printf("%d ", M[coordinate[1] + c][coordinate[2] + v]);
                        }
                        printf("\n");
                    }
                    coordinate[0] = -10000;
                }
            }
        }
    }
    else{
        printf("Errore nel contenuto del file!\n");
        return 4;
    }
    //Chiusura file
    fclose(fp_read);
    return 0;
}
//funzioni

void trovaMatrice(int coordinate[3], int dim, int M[maxN][maxN], int i, int j) {
    int somma;
    somma=0;
    for (int k = 0; k < dim; k++) {
        for (int h = 0; h < dim; h++) {
            printf("%d ", M[i + k][j + h]);
            somma += M[i + k][j + h];
        }
        printf("\n");
    }
    printf("\n");
    if (somma > coordinate[0]) {
        coordinate[0] = somma;
        coordinate[1] = i;
        coordinate[2] = j;
    }
    somma = 0;
}