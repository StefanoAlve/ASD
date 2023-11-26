#include <stdio.h>
#include <stdlib.h>

#define tilesName "tiles.txt"
#define boardName "board.txt"

typedef struct{
    char coloreV, coloreO;
    int vert, oriz, mark;
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
int powerset(int pos, Casella_s **matrix, Tessera_s *tessere, int R, int C, int cnt, Casella_s ***sol);
int controllapunteggio(Casella_s **board,int R,int C,Tessera_s *tessere, int maxpunti, Casella_s ****sol){
    int i,j;
    int orizzontale,verticale,totaleorizzontale=0,totaleverticale=0;
    char checkcolor;
    int flag;
    for(i=0;i<R;i++){

        if(board[i][0].rot==0) checkcolor=board[i][0].tessera.coloreO;
        else checkcolor=board[i][0].tessera.coloreV;
        flag=1;
        orizzontale=0;
        for(j=0;j<R;j++){
            if(board[i][j].rot==0 && checkcolor==board[i][j].tessera.coloreO && flag==1){
                orizzontale=orizzontale+board[i][j].tessera.oriz;
            }else if(board[i][j].rot==1 && checkcolor==board[i][j].tessera.coloreV && flag==1){
                orizzontale=orizzontale+board[i][j].tessera.vert;
            }else{
                orizzontale=0;
                flag=0;
            }
        }
        totaleorizzontale=totaleorizzontale+orizzontale;
        //printf("%d ",orizzontale);
    }
    //printf("\n");

    for(j=0;j<C;j++){

        if(board[0][j].rot==0) checkcolor=board[0][j].tessera.coloreV;
        else checkcolor=board[0][j].tessera.coloreO;
        flag=1;
        verticale=0;
        for(i=0;i<R;i++){
            if(board[i][j].rot==0 && checkcolor==board[i][j].tessera.coloreV && flag==1){
                verticale=verticale+board[i][j].tessera.vert;
            }else if(board[i][j].rot==1 && checkcolor==board[i][j].tessera.coloreO && flag==1){
                verticale=verticale+board[i][j].tessera.oriz;
            }else{
                verticale=0;
                flag=0;
            }
        }
        totaleverticale=totaleverticale+verticale;
        //printf("%d ",verticale);
    }
    //printf("\n");
    //stampa(board,R,C);
    if((totaleorizzontale+totaleverticale)>maxpunti){
        maxpunti=totaleverticale+totaleorizzontale;
        for(i=0;i<R;i++) for(j=0;j<C;j++) (**sol)[i][j]=board[i][j];
        return maxpunti;
    }
    return maxpunti;
}

int main(){
    FILE *fTiles, *fBoard;
    int nTessere, R, C, punteggio;
    Tessera_s *tessere;
    Casella_s **matrix, **sol;

    //Lettura dei file
    fTiles = leggiFile(tilesName);
    fBoard = leggiFile(boardName);

    //Assegnazione da file
    tessere = assegnaTessere(&nTessere, fTiles);
    matrix = assegnaMatrice(tessere, &R, &C, fBoard);

    //Allocazione della matrice soluzione e gestione errori
    sol = (Casella_s**) malloc(R * sizeof (Casella_s *));
    if(sol == NULL){
        printf("Errore allocazione matrice soluzione!\n");
        exit(3);
    }
    for(int i = 0; i < C; i++){
        sol[i] = (Casella_s *) malloc(C * sizeof (Casella_s));
        if(sol[i] == NULL){
            printf("Errore allocazione matrice soluzione!\n");
            exit(3);
        }
    }

    punteggio = powerset(0, matrix, tessere, R, C, 0, &sol);
    printf("%d", punteggio);

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
        fscanf(fin,"%c %d %c %d\n",&(tessere[i].coloreV),&(tessere[i].vert),&(tessere[i].coloreO),&(tessere[i].oriz));

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
                matrix[i][j].rot = 1;
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

    Col = temp.coloreO;
    temp.coloreO = temp.coloreV;
    temp.coloreV = Col;

    val = temp.oriz;
    temp.oriz = temp.vert;
    temp.vert = val;

    return temp;
}

//
int powerset(int pos, Casella_s **matrix, Tessera_s *tessere, int R, int C, int cnt, Casella_s ***sol){
    int i,j,k;

    if(pos>=(R*C)){
        cnt = controllapunteggio(matrix, R, C, tessere, cnt, &sol);
        return cnt;
    }

    i=pos/R; //Indice riga
    j=pos%R; //Indice colonna

    if(matrix[i][j].usato != 0){
        cnt=powerset(pos+1,matrix,tessere,R,C,cnt,sol);
        return cnt;
    }

    for(k=0; k < (R*C); k++){
        if(!(tessere[k].mark)){

            matrix[i][j].usato = 1;
            matrix[i][j].tessera = tessere[k];
            tessere[k].mark = 1;

            matrix[i][j].rot=0;
            cnt = powerset(pos+1, matrix, tessere, R, C, cnt, sol);

            matrix[i][j].rot = 1;
            cnt = powerset(pos+1, matrix, tessere, R, C, cnt, sol);
            matrix[i][j].usato = 0;
            tessere[k].mark = 0;
        }
    }
    return cnt;
}
