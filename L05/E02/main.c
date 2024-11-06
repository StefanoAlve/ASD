#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char color1;
    int value1;
    char color2;
    int value2;
} tile;

typedef struct{
    int tile, oriented;
} cella;

int AcquisisciTessere(tile **Tiles);
cella **AcquisisciScacchiera(int *r, int *c);
void RiempiScacchiera(tile *v_tiles, int n_t, cella **m_board, int r, int c);
void ConfigScacchieraInit(int *mark, cella **m_board, int r, int c);
void DispSempliciR(cella **m_board, int r, int c, int *mark, tile *v_tiles, int n_t, int *mp, int pos);
int CalcolaPunteggio(cella **m_board, int r, int c, tile *v_tiles, int n_t);
void StampaBoard(cella **m_board, int r, int c);

int main() {
    tile *Tessere;
    int n_tiles = AcquisisciTessere(&Tessere);
    int nr, nc;
    cella **Scacchiera = AcquisisciScacchiera(&nr, &nc);

    RiempiScacchiera(Tessere, n_tiles, Scacchiera, nr, nc);


    return 0;
}

int AcquisisciTessere(tile **Tiles){
    int n = 0;
    FILE *fp = fopen("tiles.txt", "r");
    if (fp == NULL){
        printf("Errore apertura file tessere\n");
        exit(1);
    }
    fscanf(fp, "%d", &n);
    tile *v_tiles = malloc(n*sizeof *v_tiles);

    for (int i = 0; i < n; i++){
        fscanf(fp, "%c %d %c %d", &v_tiles[i].color1, &v_tiles[i].value1, &v_tiles[i].color2, &v_tiles[i].value2);
    }

    fclose(fp);
    *Tiles = v_tiles;

    return n;
}

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

void RiempiScacchiera(tile *v_tiles, int n_t, cella **m_board, int r, int c){
    int *mark = calloc(n_t, sizeof *mark);
    int maxp = 0, pos = 0;
    ConfigScacchieraInit(mark, m_board, r, c);

    DispSempliciR(m_board, r, c, mark, v_tiles, n_t, &maxp, pos);

}

void ConfigScacchieraInit(int *mark, cella **m_board, int r, int c){
    for (int i = 0; i < r; i++){
        for (int j = 0; j < c; j++){
            if (m_board[i][j].tile != -1)
                mark[m_board[i][j].tile] = 1;
        }
    }
}

void DispSempliciR(cella **m_board, int r, int c, int *mark, tile *v_tiles, int n_t, int *mp, int pos){
    if (pos >= r*c){
        int pt = CalcolaPunteggio(m_board, r, c, v_tiles, n_t);
        if (pt > *mp){
            StampaBoard(m_board, r, c);
            printf("......%d\n", pt);
            *mp = pt;
        }
        return;
    }
    int i_r = pos/c, i_c = pos%c;
    if (m_board[i_r][i_c].tile == -1){
        for (int i = 0; i < n_t; i++){
            if (mark[i] == 0){
                m_board[i_r][i_c].tile = i;
                m_board[i_r][i_c].oriented = 0;
                mark[i] = 1;
                DispSempliciR(m_board, r, c, mark, v_tiles, n_t, mp, pos+1);
                m_board[i_r][i_c].oriented = 1;
                DispSempliciR(m_board, r, c, mark, v_tiles, n_t, mp, pos+1);
                m_board[i_r][i_c].tile =-1;
                m_board[i_r][i_c].oriented = -1;
                mark[i] = 0;
            }
        }
    } else {
        DispSempliciR(m_board, r, c, mark, v_tiles, n_t, mp, pos+1);
    }

}

int CalcolaPunteggio(cella **m_board, int r, int c, tile *v_tiles, int n_t){
    char cl;
    int sumT = 0, sumC = 0;
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
                    sumC = 0;
                    break;
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

void StampaBoard(cella **m_board, int r, int c){
    for (int i = 0; i < r; i++){
        for (int j = 0; j < c; j++){
            printf("%d/%d ", m_board[i][j].tile, m_board[i][j].oriented);
        }
        printf("\n");
    }

    printf("\n\n\n\n");
}


