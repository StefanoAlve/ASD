#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXC 100
typedef struct{
    char lettera;
    int valore;
}s_tubo;

typedef struct{
    s_tubo tuboO;
    s_tubo tuboV;
}s_tessera;

s_tessera* acquisisciTessere(int* numTessere);
s_tessera** leggiScacchiera(int* NR, int* NC, s_tessera *vettTessere, int* mark);
s_tessera swap(s_tessera t);
s_tessera tesseraVuota(void);
/// STAMPA DEL RISULTATO
void stampaScacchiera(s_tessera **scacchiera, int NR, int NC);
void stampaScacchiera1(s_tessera **scacchiera, int i, int NC);
void stampaScacchiera2(s_tessera **scacchiera, int i, int NC);
void costruisciScacchieraTmp(s_tessera** destinazione, s_tessera**partenza, s_tessera* v, int NR, int NC);
void stampaScacchiera3(s_tessera **scacchiera,int i, int NC);
/// Soluzione effettiva
void wrapperTrovaSol(s_tessera** scacchiera, s_tessera* vettTessere, int *mark, int nTessere, int NR, int NC);
int trovaSol(s_tessera** scacchiera, s_tessera* vettTessere, s_tessera* sol, s_tessera** migliore, int *mark, int NR, int NC, int pos, int n, int k, int* maxP);
int calcolaPunteggio(s_tessera** scacchiera, s_tessera* sol, int NR, int NC);
void freeALL(s_tessera** scacchiera, s_tessera* vettTessere, int*mark, int NR);

int main(void){
    //Inizializzazione variabili
    s_tessera* vettTessere = NULL;
    s_tessera** scacchiera = NULL;
    int nTessere, NR, NC;
    int* mark = NULL;
    //Corpo programma
    vettTessere = acquisisciTessere(&nTessere);
    mark = calloc(nTessere, sizeof(int));
    scacchiera = leggiScacchiera(&NR, &NC, vettTessere, mark);
    stampaScacchiera(scacchiera, NR, NC);
    wrapperTrovaSol(scacchiera, vettTessere, mark, nTessere, NR, NC);
    //Deallocazione
    freeALL(scacchiera, vettTessere, mark, NR);
}


s_tessera* acquisisciTessere(int* numTessere){
    //Inizializzazione variabili
    int nT = 0, i = 0;
    char letteraO, letteraV, tmp[MAXC], *nomeFile;
    int valoreO, valoreV;
    s_tessera* vettTessere;
    //Lettura file
    printf("Inserire il nome del file da cui prendere le tessere:");
    scanf("%s", tmp);
    nomeFile = strdup(tmp);
    FILE* fp = fopen(nomeFile, "r");
    if(fp != NULL){
        fscanf(fp, "%d", &nT);
        *numTessere = nT;
        vettTessere = (s_tessera*)malloc(nT*sizeof(s_tessera));
        if (vettTessere == NULL)
            exit(-1);
        printf("\nSi dispone delle seguenti %d tessere:", nT);
        while(fscanf(fp, " %c %d %c %d", &letteraO, &valoreO, &letteraV, &valoreV) == 4 && i < nT){
            printf("\n\nTessera #%d:\nTubo orizzontale con colore %c e valore %d\nTubo verticale con colore %c e valore %d.", i+1, letteraO,valoreO,letteraV,valoreV);
            vettTessere[i].tuboO.lettera = letteraO;
            vettTessere[i].tuboO.valore = valoreO;
            vettTessere[i].tuboV.lettera = letteraV;
            vettTessere[i].tuboV.valore = valoreV;
            i++;
        }
    }
    else{
        printf("\nErrore nell'apertura del file contenente le tessere.");
        exit(-1);
    }
    printf("\n");
    fclose(fp);
    free(nomeFile);
    return vettTessere;
}

s_tessera swap(s_tessera t){
    s_tessera new;
    new.tuboO = t.tuboV;
    new.tuboV = t.tuboO;
    return new;
}

s_tessera tesseraVuota(void){
    s_tessera t;
    t.tuboO.valore = t.tuboV.valore = 0;
    t.tuboO.lettera = t.tuboV.lettera = '\0';
    return t;
}

s_tessera** leggiScacchiera(int* NR, int* NC, s_tessera *vettTessere, int* mark){
    char tmp[MAXC],*nomeFile;
    int nr, nc, i, j, nTessere, codice = 0;
    s_tessera** scacchiera;

    printf("Inserire il nome del file contenente la scacchiera iniziale:");
    scanf("%s", tmp);
    nomeFile = strdup(tmp);
    FILE *fp = fopen(nomeFile, "r");
    if (fp != NULL){
        fscanf(fp, "%d %d", &nr, &nc);
        *NR = nr; *NC = nc;
        scacchiera = (s_tessera**)malloc(nr * sizeof(s_tessera*));
        for(i = 0; i < nr; i++){
            scacchiera[i] = (s_tessera*)malloc(nc*sizeof(s_tessera));
            for(j = 0; j < nc; j++){
                fscanf(fp, "%d/%d", &nTessere, &codice);
                if(codice == 0){
                    scacchiera[i][j] = vettTessere[nTessere];
                    mark[nTessere] = 1; //significa che la tessera è stata presa
                }
                else if(codice == -1)
                    scacchiera[i][j] = tesseraVuota(); // mark in quella posizione è già 0 perchè non ho usato quella determinata tessera
                else if(codice == 1){
                    scacchiera[i][j] = swap(vettTessere[nTessere]);
                    mark[nTessere] = 1;
                }
            }
        }
    }
    else{
        printf("\nErrore nell'apertura del file contenente la board.");
        exit(-1);
    }
    fclose(fp);
    free(nomeFile);
    return scacchiera;
}

int isNotVoid(s_tessera t){
    return t.tuboO.valore;
}
void stampaScacchiera1(s_tessera **scacchiera, int i, int NC){
    int j;
    for (j = 0; j < NC; j++) {
        if (isNotVoid(scacchiera[i][j]))
            printf("| %c |", scacchiera[i][j].tuboV.lettera);
        else
            printf("|   |");
    }
}
void stampaScacchiera2(s_tessera **scacchiera, int i, int NC){
    int j;
    for (j = 0; j < NC; j++) {
        if (isNotVoid(scacchiera[i][j]))
            printf("|%c %d|", scacchiera[i][j].tuboO.lettera, scacchiera[i][j].tuboO.valore);
        else
            printf("|   |");
    }
}
void stampaScacchiera3(s_tessera **scacchiera,int i, int NC){
    int j;
    for (j = 0; j < NC; j++){
        if (isNotVoid(scacchiera[i][j]))
            printf("| %d |", scacchiera[i][j].tuboV.valore);
        else
            printf("|   |");
    }
}
void stampaScacchiera(s_tessera **scacchiera, int NR, int NC){
    int i, j;
    printf("\nLa tessera e' al momento cosi' composta:\n\n");
    for (j = 0; j < 5*NC; j++)
        printf("-");
    printf("\n");
    for(i = 0; i < NR; i++){
        stampaScacchiera1(scacchiera, i, NC);
        printf("\n");
        stampaScacchiera2(scacchiera, i, NC);
        printf("\n");
        stampaScacchiera3(scacchiera, i, NC);
        printf("\n");
        for (j = 0; j < 5*NC; j++)
            printf("-");
        printf("\n");
    }
}


void wrapperTrovaSol(s_tessera** scacchiera, s_tessera* vettTessere, int *mark, int nTessere, int NR, int NC){
    s_tessera** migliore, *sol;
    int k = 0, i, maxP = 0;

    migliore = (s_tessera**)malloc(NR*sizeof(s_tessera*));
    for(i = 0; i < NR; i++)
        migliore[i] = (s_tessera*)malloc(NC*sizeof(s_tessera));

    // calcolo della dimensione di sol
    for(i = 0; i < nTessere; i++)
        if(mark[i] == 0) //Sol avrà dimensione pari al numero di caselle vuote nella scacchiera iniziale
            k++;

    sol = (s_tessera*)malloc(k*sizeof(s_tessera));
    trovaSol(scacchiera, vettTessere, sol, migliore, mark, NR, NC, 0, nTessere, k, &maxP);
    if(maxP != 0)
    {
        printf("\nSoluzione migliore ottenibile con punteggio pari a: %d", maxP);
        stampaScacchiera(migliore, NR, NC);
    }
    for(i = 0; i < NR; i++)
        free(migliore[i]);
    free(migliore);
    free(sol);
}

void costruisciScacchieraTmp(s_tessera** destinazione, s_tessera** partenza, s_tessera* v, int NR, int NC) // s1 è la matrice di destinazione, s2 quella di partenza, v tendenzialmente contiene le tessere mancanti
{
    int h = 0;
    for(int i = 0; i < NR; i++)
        for(int j = 0; j < NC; j++){
            if(isNotVoid(partenza[i][j]))
                destinazione[i][j] = partenza[i][j];
            else
                destinazione[i][j] = v[h++];
        }
}
int trovaSol(s_tessera** scacchiera, s_tessera* vettTessere, s_tessera* sol, s_tessera** migliore, int *mark, int NR, int NC, int pos, int n, int k, int* maxP){
    ///Modello delle disposizioni semplici
    int punteggio;
    if(pos >= k){
        punteggio = calcolaPunteggio(scacchiera, sol, NR, NC);
        if(punteggio > *maxP){
            *maxP = punteggio;
            costruisciScacchieraTmp(migliore,scacchiera,sol, NR, NC);// ricopiatura risultato
        }
        return punteggio;
    }
    for(int i = 0; i < n; i++){
        if(mark[i] == 0){
            mark[i] = 1; //segno di aver preso la tessera i-esima
            sol[pos] = vettTessere[i];
            trovaSol(scacchiera, vettTessere, sol, migliore, mark, NR, NC, pos+1, n, k, maxP); //tentativo con tessera non swappata
            sol[pos] = swap(vettTessere[i]);
            trovaSol(scacchiera, vettTessere, sol, migliore, mark, NR, NC, pos+1, n, k, maxP); //tentativo con tessera swappata
            mark[i] = 0; //backtrack
        }
    }
    return 0;
}

int calcolaPunteggio(s_tessera** scacchiera, s_tessera* sol, int NR, int NC){
    int i, j, score = 0, stessaLettera;
    s_tessera** tmp;
    char lettera;
    tmp = (s_tessera**)malloc(NR*sizeof(s_tessera*));
    for(i = 0; i < NR;i++)
        tmp[i] = (s_tessera*)malloc(NC*sizeof(s_tessera));
    //utilizzo una matrice di tessere per calcolare più velocemente il punteggio
    costruisciScacchieraTmp(tmp, scacchiera, sol, NR, NC);
    // calcolo per orizzontali
    for(i = 0; i < NR; i++){
        stessaLettera = 0;
        lettera = tmp[i][0].tuboO.lettera;
        for (j = 0; j < NC && tmp[i][j].tuboO.lettera == lettera; j++)
            stessaLettera++;
        if(stessaLettera == NC)
            for (j = 0; j < NC; j++)
                score+=tmp[i][j].tuboO.valore;
    }
    //calcolo per verticali
    for(j = 0; j < NC; j++){
        stessaLettera = 0;
        lettera = tmp[0][j].tuboV.lettera;
        for(i = 0; i < NR && tmp[i][j].tuboV.lettera == lettera; i++)
            stessaLettera++;
        if(stessaLettera == NR)
            for(i = 0; i < NR; i++)
                score+= tmp[i][j].tuboV.valore;
    }
    for(i = 0; i< NR; i++)
        free(tmp[i]);
    free(tmp);
    return score;
}


void freeALL(s_tessera** scacchiera, s_tessera* vettTessere, int*mark, int NR){
    int i;
    for(i = 0; i< NR; i++)
        free(scacchiera[i]);
    free(scacchiera);
    free(vettTessere);
    free(mark);
}