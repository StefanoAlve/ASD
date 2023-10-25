#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 30

int **malloc2dR(char NomeFile[], int *nr, int *nc);

int main() {
    char NomeFile[MAXN];
    int nr, nc, **matrice;
    printf("Inserire il nome del file:\n");
    scanf("%s",NomeFile);
    matrice = malloc2dR(NomeFile,&nr,&nc);
    return 0;
}

int **malloc2dR(char NomeFile[], int *nr, int *nc){
    FILE *fp;

    fp = fopen(NomeFile,"r");
    if (fp == NULL){
        printf("Errore nell'apertura file\n");
        exit(1);
    }
    fscanf(fp,"%d %d", nr, nc);
}
