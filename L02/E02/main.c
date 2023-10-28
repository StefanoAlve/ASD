#include <stdio.h>
#include <stdlib.h>
#define nomeFile "mat.txt"

int **malloc2dR(int nr, int nc, FILE *inFile);
void deAlloca(int **matrice, int nr);
void separa(int **matrix, int nr, int nc, int **Vbianche, int *dimBianche, int **Vnere, int *dimNere);
void stampaArray(int *array, int dimArray);

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

    //Caselle bianche e nere
    int *VBianche, *VNere, dimNere, dimBianche;

    separa(matrix, nr, nc, &VBianche, &dimBianche, &VNere, &dimNere);

    printf("VETTORE CELLE NERE: ");
    stampaArray(VNere, dimNere);

    printf("VETTORE CELLE BIANCHE: ");
    stampaArray(VBianche, dimBianche);



    //Deallocazione e chiusura file
    fclose(inFile);
    free(VNere);
    free(VBianche);
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
        exit(2);
    }

    //Allocazione righe
    for (int i = 0; i < nr; i++) {
        matrix[i] = (int *)malloc(nc * sizeof(int));
        if(matrix[i] == NULL){
            printf("Errore nell'allocazione delle righe\n");
            exit(3);
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

//Separa celle bianche e nere della matrice in due vettori
void separa(int **matrix, int nr, int nc, int **Vbianche, int *dimBianche, int **Vnere, int *dimNere){
    // Contatori per tenere traccia delle dimensioni dei vettori
    int countB = 0;
    int countN = 0;

    // Scansione della matrice e conteggio delle caselle bianche e nere
    for(int i = 0; i < nr; i++){
        for(int j = 0; j < nc; j++){

            // Determina se la cella è bianca o nera in base a riga/colonna pari/dispari
            if((i + j) % 2 == 0) countB++;

            else countN++;
        }
    }

    // Alloca dinamicamente i vettori per le caselle bianche e nere
    *Vbianche = (int *)malloc(countB * sizeof(int));
    *Vnere = (int *)malloc(countN * sizeof(int));

    // Indici dei vettori
    int indB = 0;
    int indN = 0;

    // Riempimento dei vettori con i dati delle caselle bianche e nere
    for(int i = 0; i < nr; i++){
        for(int j = 0; j < nc; j++){
            if((i + j) % 2 == 0){
                (*Vbianche)[indB] = matrix[i][j];
                indB++;
            }
            else{
                (*Vnere)[indN] = matrix[i][j];
                indN++;
            }
        }
    }

    // Imposta le dimensioni dei vettori di caselle bianche e nere
    *dimBianche = countB;
    *dimNere = countN;
}

//Stampa vettore
void stampaArray(int *array, int dimArray){

    for(int i = 0; i < dimArray; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
}

