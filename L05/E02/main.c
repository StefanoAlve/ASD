#include <stdio.h>
#include <stdlib.h>

//Struct per tessera (1 per tubo orizzontale, 2 verticale
typedef struct{
    char color1;
    int value1;
    char color2;
    int value2;
} tile;

//Struct per casella scacchiera
typedef struct{
    int tile, oriented;
} cella;

//Prototipi funzioni
int AcquisisciTessere(tile **Tiles);
cella **AcquisisciScacchiera(int *r, int *c);
void RiempiScacchiera(tile *v_tiles, int n_t, cella **m_board, int r, int c);
void ConfigScacchieraInit(int *mark, cella **m_board, int r, int c);
void DispSempliciR(cella **m_board, cella **bestB, int r, int c, int *mark, tile *v_tiles, int n_t, int *mp, int pos);
int CalcolaPunteggio(cella **m_board, int r, int c, tile *v_tiles, int n_t);
void AggiornaBestBoard(cella **m_board, cella **bestB, int r, int c);
void StampaSol(cella **bestB, int r, int c);

int main() {
    //Allocazione e riempimento delle strutture dati
    tile *Tessere;
    int n_tiles = AcquisisciTessere(&Tessere);
    int nr, nc;
    cella **Scacchiera = AcquisisciScacchiera(&nr, &nc);

    //Chiamata a funzione wrapper
    RiempiScacchiera(Tessere, n_tiles, Scacchiera, nr, nc);

    //Deallocazione memoria
    free(Tessere);
    for (int i = 0; i < nr; i++)
        free(Scacchiera[i]);
    free(Scacchiera);

    return 0;
}

//Funzione che riceve il puntatore al vettore delle tessere e lo aggancia a un suo vettore allocato e riempito, per
//ritornarlo al chiamante
int AcquisisciTessere(tile **Tiles){
    int n = 0;
    FILE *fp = fopen("tiles.txt", "r");
    if (fp == NULL){
        printf("Errore apertura file tessere\n");
        exit(1);
    }
    fscanf(fp, "%d ", &n);
    tile *v_tiles = malloc(n*sizeof *v_tiles);

    for (int i = 0; i < n; i++){
        fscanf(fp, "%c %d %c %d ", &v_tiles[i].color1, &v_tiles[i].value1, &v_tiles[i].color2, &v_tiles[i].value2);
    }

    fclose(fp);
    *Tiles = v_tiles;

    return n;
}

//Funzione che riceve i puntatori alle dimensioni della scacchiera e ritorna la scacchiera già riempita
cella **AcquisisciScacchiera(int *r, int *c){
    FILE *fp = fopen("board.txt", "r");
    if (fp == NULL){
        printf("Errore apertura file scacchiera\n");
        exit(1);
    }
    fscanf(fp, "%d %d", r, c);
    cella **m_board = malloc(*r*sizeof (cella *));
    for (int i = 0; i < *r; i++){
        m_board[i] = malloc(*c*sizeof (cella));
        for (int j = 0; j < *c; j++){
            fscanf(fp, "%d/%d", &m_board[i][j].tile, &m_board[i][j].oriented);
        }
    }

    fclose(fp);
    return m_board;
}

//La funzione riceve le strutture dati, alloca le altre strutture per le relative funzioni e dealloca
//le strutture da lui create
void RiempiScacchiera(tile *v_tiles, int n_t, cella **m_board, int r, int c){
    //Vettore mark per marcare le tessere già prese
    int *mark = calloc(n_t, sizeof *mark);
    int maxp = 0, pos = 0; //maxp punteggio massimo, pos indice ricorsione
    //Matrice bestBoard per ricordare la scacchiera a punteggio massimo
    cella **bestBoard = malloc(r*sizeof (cella *));
    for (int i = 0; i < r; i++)
        bestBoard[i] = malloc(c*sizeof (cella));

    //Marca le tessere già usate, obbligate
    ConfigScacchieraInit(mark, m_board, r, c);
    //Chiamate alle disposizioni semplici per trovare le possibili configurazioni della scacchiera
    DispSempliciR(m_board, bestBoard, r, c, mark, v_tiles, n_t, &maxp, pos);
    //Stampa della soluzione migliore
    StampaSol(bestBoard, r, c);
    printf("Punteggio : %d", maxp);

    //Deallocazione
    free(mark);
    for (int i = 0; i < r; i++)
        free(bestBoard[i]);
    free(bestBoard);

}

//Funzione che marca le tessere già usate per l'inizio del gioco
void ConfigScacchieraInit(int *mark, cella **m_board, int r, int c){
    for (int i = 0; i < r; i++){
        for (int j = 0; j < c; j++){
            if (m_board[i][j].tile != -1)
                mark[m_board[i][j].tile] = 1;
        }
    }
}

//La funzione implementa il modello delle disposizioni semplici per trovare tutte le possibili configurazioni
//della scacchiera date le tessere. Trovata una configurazione, ne calcola il punteggio e aggiorna nel caso la bestBoard
void DispSempliciR(cella **m_board, cella **bestB, int r, int c, int *mark, tile *v_tiles, int n_t, int *mp, int pos){
    if (pos >= r*c){ //Terminazione (ho riempito la scacchiera)
        int pt = CalcolaPunteggio(m_board, r, c, v_tiles, n_t);
        if (pt > *mp){
            AggiornaBestBoard(m_board, bestB, r, c);
            *mp = pt; //Aggiorno punteggio massimo
        }
        return;
    }
    //Poichè pos incrementa da 0 a r*c, devo calcolare ogni volta gli indici di riga e colonna della casella su cui mi trovo
    int i_r = pos/c, i_c = pos%c;
    if (m_board[i_r][i_c].tile == -1){ //Se la casella è libera, ciclo sulle tessere
        for (int i = 0; i < n_t; i++){
            if (mark[i] == 0){ //Se la tessera è disponibile
                //Inserimento tessera non orientata e marco
                m_board[i_r][i_c].tile = i;
                m_board[i_r][i_c].oriented = 0;
                mark[i] = 1;
                DispSempliciR(m_board, bestB, r, c, mark, v_tiles, n_t, mp, pos+1); //Ricorro
                m_board[i_r][i_c].oriented = 1; //Cambio orientamento della tessera
                DispSempliciR(m_board, bestB, r, c, mark, v_tiles, n_t, mp, pos+1); //Ricorro
                //tolgo la tessera e smarco
                m_board[i_r][i_c].tile =-1;
                m_board[i_r][i_c].oriented = -1;
                mark[i] = 0;
            }
        }
    } else { //Casella occupata, ricorro sulla casella successiva
        DispSempliciR(m_board, bestB, r, c, mark, v_tiles, n_t, mp, pos+1);
    }

}

//Funzione che calcola il punteggio complessivo della scacchiera. Eseguo 2 cicli annidati 2 volte per calcolare prima
//la somma sui tubi orizzontali, poi su quelli verticali
int CalcolaPunteggio(cella **m_board, int r, int c, tile *v_tiles, int n_t){
    char cl;
    int sumT = 0, sumC = 0; //sommaTotale e sommaCorrente per tubo
    //somma sui tubi orizzontali
    for (int i = 0; i < r; i++){
        if (m_board[i][0].oriented == 0){
            cl = v_tiles[m_board[i][0].tile].color1;
            sumC += v_tiles[m_board[i][0].tile].value1;
        } else {
            cl = v_tiles[m_board[i][0].tile].color2;
            sumC += v_tiles[m_board[i][0].tile].value2;
        }

        for (int j = 1; j < c; j++){
            if (m_board[i][j].oriented == 0){
                if (v_tiles[m_board[i][j].tile].color1 != cl){
                    sumC = 0; //Se la casella corrente ha un colore diverso dalla prima (inizio tubo) allora il tubo ha valore 0
                    break; //esco dal ciclo (passo al prossimo tubo orizzontale)
                } else {
                    sumC += v_tiles[m_board[i][j].tile].value1;
                }
            } else {
                if (v_tiles[m_board[i][j].tile].color2 != cl){
                    sumC = 0;
                    break;
                } else {
                    sumC += v_tiles[m_board[i][j].tile].value2;
                }
            }
        }

        sumT += sumC;
        sumC = 0;
    }

    //somma sui tubi verticali
    for (int i = 0; i < c; i++){
        if (m_board[0][i].oriented == 0){
            cl = v_tiles[m_board[0][i].tile].color2;
            sumC += v_tiles[m_board[0][i].tile].value2;
        } else {
            cl = v_tiles[m_board[0][i].tile].color1;
            sumC += v_tiles[m_board[0][i].tile].value1;
        }

        for (int j = 1; j < r; j++){
            if (m_board[j][i].oriented == 0){
                if (v_tiles[m_board[j][i].tile].color2 != cl){
                    sumC = 0;
                    break;
                } else {
                    sumC += v_tiles[m_board[j][i].tile].value2;
                }
            } else {
                if (v_tiles[m_board[j][i].tile].color1 != cl){
                    sumC = 0;
                    break;
                } else {
                    sumC += v_tiles[m_board[j][i].tile].value1;
                }
            }
        }

        sumT += sumC;
        sumC = 0;
    }

    return sumT;
}

//funzione di salvataggio della scacchiera a punteggio massimo
void AggiornaBestBoard(cella **m_board, cella **bestB, int r, int c){
    for (int i = 0; i < r; i++){
        for (int j = 0; j < c; j++){
            bestB[i][j].tile = m_board[i][j].tile;
            bestB[i][j].oriented = m_board[i][j].oriented;
        }
    }
}

//Stampa della scacchiera
void StampaSol(cella **bestB, int r, int c){
    for (int i = 0; i < r; i++){
        for (int j = 0; j < c; j++){
            printf("%d/%d ", bestB[i][j].tile, bestB[i][j].oriented);
        }
        printf("\n");
    }
}

