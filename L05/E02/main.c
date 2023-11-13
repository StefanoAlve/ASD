#include <stdio.h>
#include <stdlib.h>

#define file_tessere "tiles.txt"
#define file_board "board.txt"

typedef struct{
    char colore;
    int valore;
}tubo;

typedef struct{
    tubo orizzontale;
    tubo verticale;
}tessera;

tessera* acquisisci_tessere(int* num_tessere);
tessera** leggi_board(int* NR, int* NC, tessera *vet_tessere, int* mark);
tessera swap(tessera t);
tessera tessera_vuota(void);
/// STAMPA DEL RISULTATO
void stampa_superficie(tessera **superficie, int NR, int NC);
void stampa_superficie1(tessera **superficie,int i, int NC);
void stampa_superficie2(tessera **superficie,int i, int NC);
void costruisci_superficie_tmp(tessera** s1,tessera**s2, tessera* v, int NR, int NC);
void stampa_superficie3(tessera **superficie,int i, int NC);
/// Soluzione effettiva
void disp_semplici_wrapper(tessera** superficie, tessera* vet_tesssere, int *mark, int num_tessere, int NR, int NC);
int disp_sempliciR(tessera** superficie, tessera*vet_tessere, tessera* sol, tessera**bestSol, int *mark, int NR, int NC, int pos, int n, int k, int* maxP);
int calcola_punteggio(tessera** superficie, tessera* sol, int NR, int NC);
void freeALL(tessera** superficie, tessera* vet_tessere, int*mark, int NR);

int main(void){
    tessera* vet_tessere = NULL;
    tessera** superficie = NULL;
    int num_tessere, NR, NC;
    int* mark = NULL;

    vet_tessere = acquisisci_tessere(&num_tessere);
    mark = calloc(num_tessere, sizeof(int));
    superficie = leggi_board(&NR, &NC, vet_tessere, mark);
    stampa_superficie(superficie, NR, NC);
    disp_semplici_wrapper(superficie, vet_tessere, mark, num_tessere, NR, NC);
    freeALL(superficie, vet_tessere, mark, NR);
}


tessera* acquisisci_tessere(int* num_tessere){
    int nT = 0, i = 0;
    char colore_o, colore_v;
    int valore_o, valore_v;
    tessera* vett_tessere;
    FILE* fp_in = fopen(file_tessere, "r");
    if(fp_in != NULL){
        fscanf(fp_in, "%d", &nT);
        *num_tessere = nT;
        vett_tessere = (tessera*)malloc(nT*sizeof(tessera));
        if (vett_tessere == NULL)
            exit(-1);
        printf("\nSi dispone delle seguenti %d tessere:", nT);
        while(fscanf(fp_in, " %c %d %c %d", &colore_o, &valore_o, &colore_v, &valore_v) == 4 && i < nT){
            printf("\n\nTessera #%d:\nTubo orizzontale con colore %c e valore %d\nTubo verticale con colore %c e valore %d.", i+1, colore_o,valore_o,colore_v,valore_v);
            vett_tessere[i].orizzontale.colore = colore_o;
            vett_tessere[i].orizzontale.valore = valore_o;
            vett_tessere[i].verticale.colore = colore_v;
            vett_tessere[i].verticale.valore = valore_v;
            i++;
        }
    }
    else{
        printf("\nErrore nell'apertura del file contenente le tessere.");
        exit(-1);
    }
    printf("\n");
    fclose(fp_in);
    return vett_tessere;
}

tessera swap(tessera t){
    tessera new;
    new.orizzontale = t.verticale;
    new.verticale = t.orizzontale;
    return new;
}

tessera tessera_vuota(void){
    tessera t;
    t.orizzontale.valore = t.verticale.valore = 0;
    t.orizzontale.colore = t.verticale.colore = '\0';
    return t;
}

tessera** leggi_board(int* NR, int* NC, tessera* vet_tessere, int*mark){
    FILE *fp_in = fopen(file_board, "r");
    int nr, nc, i, j, num_tessera, codice = 0;
    tessera** superficie;
    if (fp_in != NULL){
        fscanf(fp_in, "%d %d", &nr, &nc);
        *NR = nr; *NC = nc;
        superficie = (tessera**)malloc(nr * sizeof(tessera*));
        for(i = 0; i < nr; i++){
            superficie[i] = (tessera*)malloc(nc*sizeof(tessera));
            for(j = 0; j < nc; j++){
                fscanf(fp_in, "%d/%d", &num_tessera, &codice);
                if(codice == 0){
                    superficie[i][j] = vet_tessere[num_tessera];
                    mark[num_tessera] = 1; //significa che la tessera è stata presa
                }
                else if(codice == -1)
                    superficie[i][j] = tessera_vuota(); // mark in quella posizione è già 0 perchè non ho usato quella determinata tessera
                else if(codice == 1){
                    superficie[i][j] = swap(vet_tessere[num_tessera]);
                    mark[num_tessera] = 1;
                }
            }
        }
    }
    else{
        printf("\nErrore nell'apertura del file contenente la board.");
        exit(-1);
    }
    fclose(fp_in);
    return superficie;
}

int isNotVoid(tessera t){
    return t.orizzontale.valore;
}
void stampa_superficie1(tessera **superficie,int i, int NC)
{
    int j;
    for (j = 0; j < NC; j++) {
        if (isNotVoid(superficie[i][j]))
            printf("| %c |", superficie[i][j].verticale.colore);
        else
            printf("|   |");
    }
}
void stampa_superficie2(tessera **superficie,int i, int NC){
    int j;
    for (j = 0; j < NC; j++) {
        if (isNotVoid(superficie[i][j]))
            printf("|%c %d|", superficie[i][j].orizzontale.colore, superficie[i][j].orizzontale.valore);
        else
            printf("|   |");
    }
}
void stampa_superficie3(tessera **superficie,int i, int NC) {
    int j;
    for (j = 0; j < NC; j++){
        if (isNotVoid(superficie[i][j]))
            printf("| %d |", superficie[i][j].verticale.valore);
        else
            printf("|   |");
    }
}
void stampa_superficie(tessera** superficie, int NR, int NC)
{
    int i, j;
    printf("\nLa tessera e' al momento cosi' composta:\n\n");
    for (j = 0; j < 5*NC; j++)
        printf("-");
    printf("\n");
    for(i = 0; i < NR; i++){
        stampa_superficie1(superficie, i, NC);
        printf("\n");
        stampa_superficie2(superficie, i, NC);
        printf("\n");
        stampa_superficie3(superficie, i, NC);
        printf("\n");
        for (j = 0; j < 5*NC; j++)
            printf("-");
        printf("\n");
    }
}


void disp_semplici_wrapper(tessera** superficie, tessera* vet_tesssere, int *mark, int num_tessere, int NR, int NC){
    tessera** bestSol, *sol;
    int k = 0, i, maxP = 0;
    bestSol = (tessera**)malloc(NR*sizeof(tessera*));
    for(i = 0; i < NR; i++)
        bestSol[i] = (tessera*)malloc(NC*sizeof(tessera));
    // calcolo della dimensione raggruppamenti da fare:
    for(i = 0; i < num_tessere; i++)
        if(mark[i] == 0)
            k++;
    sol = (tessera*)malloc(k*sizeof(tessera)); // sol conterrà le disposizioni a k a k delle tessere inutilizzate
    disp_sempliciR(superficie, vet_tesssere, sol, bestSol, mark, NR, NC, 0, num_tessere, k, &maxP);
    if(maxP != 0)
    {
        printf("\nSoluzione migliore ottenibile con punteggio pari a: %d", maxP);
        stampa_superficie(bestSol, NR, NC);
    }
    for(i = 0; i < NR; i++)
        free(bestSol[i]);
    free(bestSol);
    free(sol);
}

void costruisci_superficie_tmp(tessera** s1,tessera**s2, tessera* v, int NR, int NC) // s1 è la matrice di destinazione, s2 quella di partenza, v tendenzialmente contiene le tessere mancanti
{
    int h = 0;
    for(int i = 0; i < NR; i++)
        for(int j = 0; j < NC; j++){
            if(isNotVoid(s2[i][j]))
                s1[i][j] = s2[i][j];
            else
                s1[i][j] = v[h++];
        }
}
int disp_sempliciR(tessera** superficie, tessera* vet_tessere, tessera* sol, tessera**bestSol, int *mark, int NR, int NC, int pos, int n, int k, int* maxP)
{
    int punteggio;
    if(pos >= k){
        punteggio = calcola_punteggio(superficie, sol, NR, NC);
        if(punteggio > *maxP){
            *maxP = punteggio;
            costruisci_superficie_tmp(bestSol,superficie,sol, NR, NC);// ricopiatura risultato
        }
        return punteggio;
    }
    for(int i = 0; i < n; i++){
        if(mark[i] == 0){
            mark[i] = 1; //segno di aver preso la tessera i-esima
            sol[pos] = vet_tessere[i];
            disp_sempliciR(superficie, vet_tessere, sol, bestSol, mark, NR, NC, pos+1, n, k, maxP);
            sol[pos] = swap(vet_tessere[i]);
            disp_sempliciR(superficie, vet_tessere, sol, bestSol, mark, NR, NC, pos+1, n, k, maxP);
            mark[i] = 0; //backtrack
        }
    }
    return 0;
}

int calcola_punteggio(tessera** superficie, tessera* sol, int NR, int NC)
{
    int i, j, score = 0, equal_color;
    tessera** tmp;
    char colore;
    tmp = (tessera**)malloc(NR*sizeof(tessera*));
    for(i = 0; i < NR;i++)
        tmp[i] = (tessera*)malloc(NC*sizeof(tessera));
    ///mi servo di una matrice di tessere tmp per calcolare più agevolmente il punteggio
    costruisci_superficie_tmp(tmp, superficie, sol, NR, NC);
    // calcolo per orizzontali
    for(i = 0; i < NR; i++){
        equal_color = 0;
        colore = tmp[i][0].orizzontale.colore;
        for (j = 0; j < NC && tmp[i][j].orizzontale.colore == colore; j++)
            equal_color++;
        if(equal_color == NC)
            for (j = 0; j < NC; j++)
                score+=tmp[i][j].orizzontale.valore;
    }
    for(j = 0; j < NC; j++){
        equal_color = 0;
        colore = tmp[0][j].verticale.colore;
        for(i = 0; i < NR && tmp[i][j].verticale.colore == colore; i++)
            equal_color++;
        if(equal_color == NR)
            for(i = 0; i < NR; i++)
                score+= tmp[i][j].verticale.valore;
    }
    for(i = 0; i< NR; i++)
        free(tmp[i]);
    free(tmp);
    return score;
}


void freeALL(tessera** superficie, tessera* vet_tessere, int*mark, int NR){
    int i;
    for(i = 0; i< NR; i++)
        free(superficie[i]);
    free(superficie);
    free(vet_tessere);
    free(mark);
}