#include <stdio.h>
#include "stdlib.h"
FILE* apri_file_lettura(char *nome_file);
int **malloc2dR(int nr, int nc, FILE* fin); //allocazione della matrice
void freemalloc2d(int **m, int nr); //deallocazione della matrice
int *mallocVett(int dim); //allocazione di vettori di dimensione data (dim)
void contacaselleBW(int nr, int nc, int *nBlack, int *nWhite);
void separa(int **m, int nr, int nc, int *vettB, int *vettW) ;
void stampa_vettore(int  *v, int dim); //stampa vettore data dimensione;


int main() {
    FILE* fin = apri_file_lettura("C:\\Users\\calve\\OneDrive\\Desktop\\primo semestre\\Algoritmi\\laboratorio\\lab02\\es02\\mat.txt");
    int nr, nc, nBlack, nWhite, **m, *vettB, *vettW;

    fscanf(fin, "%d %d", &nr, &nc);
    contacaselleBW(nr, nc, &nBlack, &nWhite); //inserisce all'interno dei valori passati con puntatori il valore da utilizzare come nBlack e nWhite

    m = malloc2dR(nr, nc, fin); //allocazione matrice e lettura dei dati da file con inserimento nella matrice
    vettB = mallocVett(nBlack); //allocazione vettore delle caselle nere
    vettW = mallocVett(nWhite);//allocazione vettore delle caselle bianche
    separa(m, nr, nc, vettB, vettW);
    printf("\necco la stampa del vettore delle caselle bianche: ");
    stampa_vettore(vettW, nWhite);
    printf("\necco la stampa del vettore delle caselle nere: ");
    stampa_vettore(vettB, nBlack);
    free(vettB);
    free(vettW);

    return 0;
}

FILE* apri_file_lettura(char *nome_file){
    FILE* fin;
    fin = fopen(nome_file, "r");
    if(fin == NULL){
        printf("\n errore nell'apertura del file");
        return NULL;
    }
    return fin;
}

int **malloc2dR(int nr, int nc, FILE* fin){ //restituisce un puntatore a un vettore di puntatori, una matrice
    int **m;
    m = (int **) malloc(nr * sizeof (int*) ); //m è un vettore di puntatori alle righe della matrice

    for(int i = 0; i < nr; i++){ //alloco un vettore per ogni riga
        m[i] = (int *) malloc(nc * sizeof(int)); //per ogni riga alloco un vettore di nc interi
    }

    for(int i = 0; i < nr; i++){
        for(int j = 0; j < nc; j++){
            fscanf(fin, "%d ", &m[i][j]);
        }
    }

    return m; //ritorno il puntatore ai puntatori, cioè indirizzo di inizio matrice
}

void freemalloc2d(int **m, int nr){
    for(int i = 0; i< nr; i++){
        free(m[i]);
    }
    free(m);
}

void contacaselleBW(int nr, int nc, int *nBlack, int *nWhite){

    if( (nr*nc)%2 != 0) { //se il totale delle caselle è dispari
        *nBlack = (nr*nc) / 2;
        *nWhite = ((nr*nc) / 2 )+1;

    }
    else{
        *nBlack = (nr*nc) / 2;
        *nWhite = (nr*nc) / 2 ;
    }
}
int *mallocVett(int dim){ // allocazione di un vettore
    int *vett;
    vett = (int *) malloc(dim*sizeof(int));
    return vett;
}
void separa(int **m, int nr, int nc, int *vettB, int *vettW){
    int iB = 0, iW = 0; //iB indice vettore nere, iW indice vettore bianche

    for(int i = 0; i < nr; i++){
        for(int j = 0; j < nc; j++){

            if((i+j) % 2 == 0) {  vettW[iW] = m[i][j]; iW++; }
            else { vettB[iB] = m[i][j]; iB++; }
        }
    }
    freemalloc2d(m, nr); //deallocazione della matrice al termine della separazione nei due vettori dei valori
}

void stampa_vettore(int  *v, int dim){
    for(int i = 0; i< dim; i++){
        printf("%d ", v[i]);
    }
}