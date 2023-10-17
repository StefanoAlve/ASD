#include <stdio.h>
#include <stdlib.h>
#define file_name "mat.txt"

int **malloc2dR(int nr, int nc); // alloca lo spazio per righe e colonne di una matrice (che viene ritornata)
void free2d(int **mat, int nr); // libera lo spazio precedentemente allocato alla matrice
int **leggi_file(char* name_file, int* nr, int* nc); // legge il file e ritorna la matrice con i valori presenti nel file
void stampa_mat(int **mat, int nr, int nc);
void separa(int ** mat, int nr, int nc, int **vettB, int **vettN, int numB, int numN);
void conta_caselle(int nr, int nc, int *nb, int *nn); // conta il numero di caselle bianche e nere
void stampa_vet(int *vett, int n);


int main(void)
{
    int **mat, *vettB, *vettN, nr, nc, numB, numN;
    mat = leggi_file(file_name, &nr, &nc);
    printf("La matrice presente nel file e' la seguente:\n");
    stampa_mat(mat, nr, nc);
    conta_caselle(nr, nc, &numB, &numN);
    separa(mat, nr, nc, &vettB, &vettN, numB, numN);
    free2d(mat, nr);
    printf("\nIl vettore contenente gli elementi delle %d caselle bianche contiene: ", numB);
    stampa_vet(vettB, numB);
    free(vettB);
    printf("\nIl vettore contenente gli elementi delle %d caselle nere contiene: ", numN);
    stampa_vet(vettN, numN);
    free(vettN);
}


int **leggi_file(char* name_file, int* nr, int* nc)
{
    int i, j;
    int **m = NULL;
    FILE* fp_in = fopen(name_file, "r");
    if (fp_in != NULL)
    {
        fscanf(fp_in, "%d %d", nr, nc);
        if (nr != NULL && nc != NULL) {
            m = malloc2dR(*nr, *nc);
        }
        if(m!= NULL)
        {
            for (i = 0; i < *nr; i++)
            {
                for (j = 0; j < *nc; j++)
                    fscanf(fp_in, "%d ", &m[i][j]);
            }
        }
    }
    return m;
}

int **malloc2dR(int nr, int nc)
{
    int **m;
    // allocazione dello spazio per le righe
    m = (int **)malloc(nr*sizeof(int *));
    // allocazione dello spazio per le colonne
    for (int i = 0; i < nr; i++)
        m[i] = (int *)malloc(nc*sizeof(int));
    return m;
}

void free2d(int **m, int nr)
{
    for(int i = 0; i < nr; i++)
        free(m[i]);
    free(m);
}

void stampa_mat(int **mat, int nr, int nc)
{
    int i,j;
    for (i = 0; i< nr; i++)
    {
        for (j = 0; j < nc; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }
}

void conta_caselle(int nr, int nc, int *nb, int *nn)
{
    int tot;//                                                           b n b
    tot = nr*nc;//                                                       n b n
    if (tot % 2 != 0){ // se dispari avrei una configurazione del tipo:  b n b
        *nb = (int)tot/2 + 1; *nn = tot- *nb;
    }
    else{
        *nb = tot/2; *nn = tot/2;
    }
}

void separa(int ** mat, int nr, int nc, int **vettB, int **vettN, int numB, int numN)
{
    int i,j, contB = 0, contN = 0;
    int *vB, *vN;
    vB = (int *)malloc(numB*sizeof(int));
    vN = (int *)malloc(numN * sizeof(int));
    for (i = 0; i < nr; i++)
    {
        for (j = 0; j < nc; j++)
        {
            if ((i+j)%2 == 0)
            {
                vB[contB] = mat[i][j];
                contB++;
            }
            else
            {
                vN[contN] = mat[i][j];
                contN++;
            }
        }
    }
    *vettB = vB;
    *vettN = vN;
}

void stampa_vet(int *vett, int n)
{
    for(int i = 0; i < n; i++)
        printf("%d ", vett[i]);
}