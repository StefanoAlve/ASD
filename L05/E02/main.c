#include <stdio.h>
#include <stdlib.h>

#define tilesName "tiles.txt"
#define boardName "board.txt"

typedef struct{
    char colore1, colore2;
    int val1, val2, mark;
}Tessera_s;

typedef struct{
    Tessera_s tessera;
    int rot;
    int usato;
}Casella_s;

FILE *leggiFile(char nomeFile[]);
Casella_s **assegnaMatrice(Tessera_s *tessere, int *R, int *C, FILE *fin);
Tessera_s *assegnaTessere(int *nTessere, FILE *fin);
Tessera_s ruotaTessere(Tessera_s tessera);
int contaSomme(Casella_s **matrix, int R, int C, int cnt);
int sommaC(Casella_s **matrix, int R, int C);
int sommaR(Casella_s **matrix, int R, int C);
int powerset(int pos, Casella_s **matrix, Tessera_s *tessere, int R, int C, int cnt);
void dealloca(Casella_s **matrix, Tessera_s *tessere, int C);

int main(){
    FILE *fTiles, *fBoard;
    int nTessere, R, C, punteggio;
    Tessera_s *tessere;
    Casella_s **matrix;

    //Lettura dei file
    fTiles = leggiFile(tilesName);
    fBoard = leggiFile(boardName);

    //Assegnazione da file
    tessere = assegnaTessere(&nTessere, fTiles);
    matrix = assegnaMatrice(tessere, &R, &C, fBoard);

    //Punteggio massimo
    punteggio = powerset(0, matrix, tessere, R, C, 0);
    printf("Il massimo punteggio e' %d", punteggio);

    dealloca(matrix, tessere, C);
    return 0;
}

//Funzione per aprire il file
FILE *leggiFile(char nomeFile[]){
    FILE *fin = NULL;

    if((fin = fopen(nomeFile, "r")) == NULL){
        printf("Errore nella lettura di file %s", nomeFile);
        exit(1);
    }

    return fin;
}

//Assegnazione dei valori delle tessere a un vettore di caselle
Tessera_s *assegnaTessere(int *nTessere, FILE *fin){
    Tessera_s *tessere;

    fscanf(fin,"%d\n", &(*nTessere));

    tessere=(Tessera_s*) malloc((*nTessere)*sizeof(Tessera_s));

    for(int i = 0; i<(*nTessere);i++)
        fscanf(fin, "%c %d %c %d\n", &(tessere[i].colore1), &(tessere[i].val1), &(tessere[i].colore2), &(tessere[i].val2));

    fclose(fin);
    return tessere;
}

//Assegnazione dei valori delle tessere a scacchiera
Casella_s **assegnaMatrice(Tessera_s *tessere, int *R, int *C, FILE *fin){
    Casella_s **matrix;
    int ind, rot;

    fscanf(fin, "%d %d ", &(*R), &(*C));


    //Allocazione e gestioen errori
    matrix = (Casella_s **) malloc((*R) * sizeof(Casella_s *));
    if (matrix == NULL) {
        printf("Errore nell'allocazione della scacchiera!\n");
        exit(2);
    }

    for(int i = 0; i < (*C); i++){
        matrix[i] = (Casella_s *) malloc(((*C)) * sizeof(Casella_s));
        if(matrix[i] == NULL){
            printf("Errore nell'allocazione della scacchiera!\n");
            exit(2);
        }
    }

    //Assegnazione delle tessere a scacchiera
    for(int i = 0; i < *C; i++){
        for(int j = 0; j < *R; j++){
            fscanf(fin, "%d/%d",&ind, &rot);

            //Tessera vuota
            if(ind == -1 && rot == -1){
                matrix[i][j].rot = 0;
                matrix[i][j].usato = 0;
                tessere[ind].mark = 0;
            }
                //Tessere non ruotata
            else if(rot == 0){
                matrix[i][j].tessera = tessere[ind];
                matrix[i][j].usato = 1;
                matrix[i][j].rot = 0;
                tessere[ind].mark = 1;
            }
                //Tessera ruotata
            else if(rot == 1){
                tessere[ind] = ruotaTessere(tessere[ind]);
                matrix[i][j].tessera = tessere[ind];
                matrix[i][j].usato = 1;
                matrix[i][j].rot = 0;
                tessere[ind].mark = 1;
            }
        }
    }

    fclose(fin);
    return matrix;
}

//Funzione che ruota un tessera
Tessera_s ruotaTessere(Tessera_s tessera){
    Tessera_s temp = tessera;
    int val;
    char Col;

    Col = temp.colore2;
    temp.colore2 = temp.colore1;
    temp.colore1 = Col;

    val = temp.val2;
    temp.val2 = temp.val1;
    temp.val1 = val;

    return temp;
}

//Somma dei valori nelle righe
int sommaR(Casella_s **matrix, int R, int C){
    int flag = 0, orizz = 0, totOrizz = 0;
    char colore;

    //Somma righe
    for(int i = 0; i < R; i++){
        flag = 1;
        orizz = 0;

        if (matrix[i][0].rot == 0)
            colore = matrix[i][0].tessera.colore1;
        else
            colore = matrix[i][0].tessera.colore2;

        for (int j = 0; j < C; j++) {
            if (matrix[i][j].tessera.colore1 == colore && matrix[i][j].rot == 0 && flag == 1)
                orizz = orizz + matrix[i][j].tessera.val1;

            else if (matrix[i][j].tessera.colore2 == colore && matrix[i][j].rot == 1 && flag == 1)
                orizz = orizz + matrix[i][j].tessera.val2;

            else {
                orizz = 0;
                flag = 0;
            }
        }
        totOrizz = totOrizz + orizz;
    }
    return totOrizz;
}

//Somma dei valori nelle colonne
int sommaC(Casella_s **matrix, int R, int C){
    int flag = 0, vert = 0, totVert = 0;
    char colore;

    //Somma colonne
    for (int j = 0; j < C; j++) {
        flag = 1;
        vert = 0;

        if (matrix[0][j].rot == 0)
            colore = matrix[0][j].tessera.colore2;
        else
            colore = matrix[0][j].tessera.colore1;

        for (int i = 0; i < R; i++) {

            if (colore == matrix[i][j].tessera.colore2 && matrix[i][j].rot == 0 && flag == 1)
                vert = vert + matrix[i][j].tessera.val2;

            else if (colore == matrix[i][j].tessera.colore1 && matrix[i][j].rot == 1 && flag == 1)
                vert = vert + matrix[i][j].tessera.val1;

            else {
                vert = 0;
                flag = 0;
            }
        }
        totVert = totVert + vert;
    }
    return totVert;
}

//Funziona che ritorna la somma delle righe e delle colonne
int contaSomme(Casella_s **matrix, int R, int C, int cnt){
    int flag, orizz = 0, vert = 0, totVert = 0, totOrizz = 0;
    char colore;

    totOrizz = sommaR(matrix, R, C);

    totVert = sommaC(matrix, R, C);

    if((totOrizz + totVert) > cnt){
        cnt = totOrizz + totVert;
    }

    return cnt;
}

//Funzione ricorsiva che trova la combinazione migliore di assegnazione delle tessere
int powerset(int pos, Casella_s **matrix, Tessera_s *tessere, int R, int C, int cnt){
    int i, j, k;

    if(pos >= (R*C)){
        cnt = contaSomme(matrix, R, C, cnt);
        return cnt;
    }

    i=pos/R; //Indice riga
    j=pos%R; //Indice colonna

    if(matrix[i][j].usato != 0){
        cnt = powerset(pos+1,matrix,tessere,R,C,cnt);
        return cnt;
    }

    for(k=0; k < (R*C); k++){
        if(!(tessere[k].mark)){

            matrix[i][j].usato = 1;
            matrix[i][j].tessera = tessere[k];
            tessere[k].mark = 1;

            matrix[i][j].rot=0;
            cnt = powerset(pos+1, matrix, tessere, R, C, cnt);

            matrix[i][j].rot = 1;
            cnt = powerset(pos+1, matrix, tessere, R, C, cnt);

            matrix[i][j].usato = 0;
            tessere[k].mark = 0;
        }
    }
    return cnt;
}

//Deallocazione
void dealloca(Casella_s **matrix, Tessera_s *tessere, int C){

    for(int i = 0; i < C; i++)
        free(matrix[i]);

    free(matrix);
    free(tessere);
}
