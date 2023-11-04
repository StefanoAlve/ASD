#include <stdio.h>
#include "malloc.h"
int **malloc2dR(int nr,int nc){// funzione di allocazione di una matrice facendo uso del valore di ritorno per restituire il puntatore alla matrice al main
    int **m;
    int i;
    m =malloc (nr* sizeof(int));
    for (i=0;i<nr;i++){
        m[i]=malloc(nc*sizeof(int));
    }
    return m;
}
void free2d(int **m,int nr){ // deallocazione della matrice, prima deallocazione delle celle, e poi di tutta la matrice "vuota"
    int i;
    for(i=0;i<nr;i++)
        free(m[i]);
    free(m);
}
void separa(int **mat,int nr,int nc,int **vetW,int **vetB) { // funzione ceh separa le celle nere da quelle bianche in base alla posizione nella matrice "scacchiera"
    int i, j, countW = 0,countB=0;
    for (i = 0;i<nr;i++){
        for(j=0;j<nc;j++){
            if ((i+j)%2==0)// se è in posizione pari aumenta il contatore delle celle bianche
                countW++;
            else// se è in posizione dispari aumenta il contatore delle celle nere
                countB++;
        }
    }
    *vetW = (int*) malloc(countW * sizeof(int));
    *vetB = (int*) malloc(countB * sizeof(int));
    int B=0,W = 0;
    for (i = 0; i < nr; i++) {
        for (j = 0; j < nc; j++) {
            if ((i + j) % 2 == 0) {// se è in posizione pari è una cella bianca
                (*vetW)[W] = mat[i][j];
                W++;
            }
            if ((i + j) % 2 != 0) {// se è in posizioen dispari è una cella nera
                (*vetB)[B] = mat[i][j];
                B++;
            }
        }
    }
//stampa del vettore delle celle bianche
    printf("Nel vettore bianco ci sono: \n");
    for(int k = 0;k<countW;k++){
        printf("%d",(*vetW)[k]);
    }
    printf("\n");
    //stampa del vettore delle celle nere
    printf("Nel vettore nero ci sono: \n");
    for(int d = 0;d<countB;d++){
        printf("%d",(*vetB)[d]);
    }



}
int main() {
    int nr=3,nc=3;
    int i,j;
    int **matr;
    int *vetW,*vetB;
    FILE *fin;
    fin = fopen("mat.txt","r");// apertura del file
    if (fin==NULL){
        printf("Errore in apertura!");// controllo
    }
    else{
        fscanf(fin,"%d %d",&nr,&nc);// assunzione del numero di righe e colonne della matrice
    }
    matr = malloc2dR(nr,nc);//allocazione della matrice
    for(i = 0;i<nr;i++){
        for(j=0;j<nr;j++){
            fscanf(fin,"%d",&matr[i][j]);// inserimento nella matrice dei valori letti da file
        }
    }
    separa(matr,nr,nc,&vetW,&vetB);
    free2d(matr,nr);
    fclose(fin);
    free(vetW);//deallocazione del vettore delle celle bianche
    free(vetB);//deallocazione del vettore delle celle nere
}

