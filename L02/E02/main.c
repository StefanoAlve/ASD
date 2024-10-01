#include <stdio.h>
#include <stdlib.h>

int **ReadAlloc(FILE *fin, int nr, int nc);
void separa(int **mat, int nr, int nc, int **vn, int **vb);

int main(){
    //Apertura e controllo del file
    FILE *fp = fopen("mat.txt", "r");
    if (fp == NULL) return 1;
    int **m, *c_nere, *c_bianche, nr, nc;
    //lettura dimensioni matrice
    fscanf(fp, "%d%d", &nr, &nc);
    m = ReadAlloc(fp, nr, nc); //chiamata a funzione
    //Stampa matrice
    printf("Matrice:\n");
    for (int i = 0; i < nr; i++){
        for (int j = 0; j < nc; j++){
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
    //chiusura file
    fclose(fp);
    separa(m, nr, nc, &c_nere, &c_bianche); //chiamata a funzione

    //stampa vettori delle celle nere e bianche
    printf("Celle nere: ");
    for(int i = 0; i < (nr*nc)/2; i++)
        printf("%d ", c_nere[i]);
    printf("\nCelle bianche: ");
    for(int i = 0; i < (nr*nc)/2; i++)
        printf("%d ", c_bianche[i]);

    //deallocazione memoria
    for(int i = 0; i < nr; i++) free(m[i]);
    free(m);
    free(c_nere);
    free(c_bianche);
}

//Funzione che legge e inserisce nella matrice allocata dinamicamente
//i valori del file. Ritorna la matrice stessa
int **ReadAlloc(FILE *fin, int nr, int nc){
    int **mat;
    mat = malloc(nr*sizeof *mat);
    if (mat == NULL) exit(1);
    for (int i = 0; i < nr; i++){
        mat[i] = malloc(nc*sizeof *mat[i]);
        if (mat[i] == NULL) exit(1);
        for(int j = 0; j < nc; j++)
            fscanf(fin, "%d", &mat[i][j]);
    }
    return mat;
}

//Funzione che alloca i due vettori di dimensione ricavata dalle dim della
//matrice, e per ogni elemento della stessa inserisce l'elemento nel
//vettore corrispondente. I due vettori sono ritornati by pointer
void separa(int **mat, int nr, int nc, int **vn, int **vb){
    int *nere, *bianche, N = (nr*nc)/2, nn = 0, nb = 0;

    nere = malloc(N*sizeof *nere);
    bianche = malloc(N*sizeof *bianche);
    if (nere == NULL || bianche == NULL) exit(1);
    for (int i = 0; i < nr; i++){
        for (int j = 0; j < nc; j++){
            //Se la somma degli indici è pari, allora è una cella nera, bianca altrimenti
            if ((i+j)%2 == 0)
                nere[nn++] = mat[i][j];
            else
                bianche[nb++] = mat[i][j];
        }
    }
    //aggancio dei puntatori ai vettori per il ritorno by pointer al main
    *vn = nere; *vb = bianche;
}