#include <stdio.h>
#include <stdlib.h>

int **malloc2dR(int nr, int nc);
void leggi_file(char* name_file, int ***mat, int* nr, int* nc);
void stampa_mat(int **mat, int nr, int nc);
void separa(int ** mat, int nr, int nc, int **vb, int ** vn, int numB, int numN);
void conta_caselle(int nr, int nc, int *nb, int *nn);
void stampa_vet(int *vett, int n);


int main(void)
{
    int **mat, *vettB, *vettN, nr, nc, numB, numN;
    char name_file[8] = {'m','a','t','.','t','x','t', '\0'};
    leggi_file(name_file, &mat, &nr, &nc);
    stampa_mat(mat, nr, nc);
    conta_caselle(nr, nc, &numB, &numN);
    separa(mat, nr, nc, &vettB, &vettN, numB, numN);
    printf("\nIl vettore contenente gli elementi delle caselle bianche contiene: ");
    stampa_vet(vettB, numB);
    free(vettB);
    printf("\nIl vettore contenente gli elementi delle caselle nere contiene: ");
    stampa_vet(vettN, numN);
    free(vettN);
}


void leggi_file(char* name_file, int ***mat, int* nr, int* nc)
{
    int i, j;
    int **m;
    FILE* fp_in = fopen(name_file, "r");
    if (fp_in != NULL)
    {
        fscanf(fp_in, "%d %d", nr, nc);
        if (nr != NULL && nc != NULL) {
            *mat = malloc2dR(*nr, *nc);
        }
        m = *mat; // solo per rendere più leggibile nella scanf altrimenti dovrei usare &((*mat)[i][j])
        if(mat!= NULL)
        {
            for (i = 0; i < *nr; i++)
            {
                for (j = 0; j < *nc; j++)
                    fscanf(fp_in, "%d ", &m[i][j]);
            }
        }
    }
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
    int tot = 0;//                                                      b n b
    tot = nr*nc;//                                                      n b n
    if (tot % 2 != 0) // se dispari avrei una configurazione del tipo:  b n b
    {
        *nb = (int)tot/2 + 1;
        *nn = tot- *nb;
    }
    else
    {
        *nb = tot/2;
        *nn = tot/2;
    }
}

void separa(int ** mat, int nr, int nc, int **vettB, int **vettN, int numB, int numN)
{
    int i,j, contB = 0, contN = 0;
    *vettB = (int *)malloc(numB*sizeof(int));
    *vettN = (int *)malloc(numN * sizeof(int));
    for (i = 0; i < nr; i++)
    {
        for (j = 0; j < nc; j++)
        {
            if ((i+j)%2 == 0)
            {
                (*vettB)[contB] = mat[i][j];
                contB++;
            }
            else
            {
                (*vettN)[contN] = mat[i][j];
                contN++;
            }
        }
    }
}

void stampa_vet(int *vett, int n)
{
    for(int i = 0; i < n; i++)
        printf("%d ", vett[i]);
}