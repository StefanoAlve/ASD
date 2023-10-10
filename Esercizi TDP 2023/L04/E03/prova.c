#include <stdio.h>
#define maxN 20
int main() {
    //Inizializzazione variabili
    FILE *fp_read;
    int nr, nc, M[maxN][maxN], dim, min, sommaMax, posX, posY, somma, countC, countR;
    char filein[maxN];
    //Assegnazioni variabili
    dim = 1;
    countC = 0;
    countR = 0;
    sommaMax = -10000;
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
        while (!feof(fp_read) && countR < nr) {
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
            if (countR == nr){
                printf("\nLa matrice ha dimensioni maggiori di quelle dichiarate\n");
                return 2;
            }
        }
        if(countC != 0){
            printf("\nMancano valori nella matrice inserita!\n");
            return 3;
        }
        while (dim > 0 && dim <= nc && dim <= nr) {
            printf("Inserire dimensione delle sottomatrici quadrate ricercate:");
            scanf(" %d", &dim);
            if (dim > 0 && dim <= min) {
                printf("\nLe sottomatrici quadrate di dimensione %d sono:\n", dim);
                for (int i = 0; i <= nr - dim; i++) {
                    for (int j = 0; j <= nc - dim; j++) {
                        for (int k = 0; k < dim; k++) {
                            for (int h = 0; h < dim; h++) {
                                printf("%d ", M[i + k][j + h]);
                                somma += M[i + k][j + h];
                            }
                            printf("\n");
                        }
                        printf("\n");
                        if (somma > sommaMax) {
                            sommaMax = somma;
                            posX = i;
                            posY = j;
                        }
                        somma = 0;
                    }

                }
            }
            printf("La sottomatrice con la somma massima (%d) e':\n", sommaMax);
            for (int c = 0; c < dim; c++) {
                for (int v = 0; v < dim; v++) {
                    printf("%d ", M[posX + c][posY + v]);
                }
                printf("\n");
            }
        }
    }
    //Chiusura file
    fclose(fp_read);
    return 0;
}
