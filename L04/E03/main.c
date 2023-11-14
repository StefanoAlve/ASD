#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXL 50
#define numPietre 4
typedef struct {
    int numero[numPietre];
}stones;


stones *leggiFile(char nomeFile[MAXL], stones *pietre, int *nr);
void stampaPietre(stones *pietre, int riga);
void stampaCollana(char *collana, int dimensione);
void preparativo(int nr, stones *pietre);
void rimanenti(int riman[numPietre], stones pietre);
int trovaDimensione(int riman[numPietre], int dimensione);
int formaCollana(int riman[numPietre], int dimensione, char *collana, int bool, int pos);
int condizione(char *collana, int pos);

int main() {
    char nomeFile[MAXL];
    stones *pietre = NULL;
    int nr;

    printf("inserire nome file: \n");
    scanf("%s", nomeFile);

    pietre = leggiFile(nomeFile, pietre, &nr);
    preparativo(nr, pietre);

    free(pietre);

    return 0;
}
///funzione che legge il file
stones *leggiFile(char nomeFile[MAXL], stones *pietre, int *nr) {
    FILE *fp;
    int i, j;

    if((fp = fopen(nomeFile, "r")) == NULL) {
        printf("errore in apertura file");
        exit(1);
    }

    fscanf(fp,"%d", nr);
    ///ALLOCO DINAMICAMENTE LA STRUCT PER CONTENERE TUTTE LE RIGHE DEL FILE
    pietre = (stones *)malloc((*nr)*sizeof(stones ));
    if(pietre == NULL){
        printf("errore nell'allocazione");
        exit(1);
    }

    for(i=0; i<(*nr); i++) {
        for(j=0; j<4; j++) {
            fscanf(fp, "%d", &pietre[i].numero[j]);
        }
    }


    fclose(fp);
    return pietre;
}
///STAMPA LA COLLANA
void stampaCollana(char *collana, int dimensione) {
    int i;
    for(i=0; i<dimensione; i++){
        printf("%c ", collana[i]);
    }
    printf("\n\n");
}
///STAMPA LE PIETRE
void stampaPietre(stones *pietre, int riga){
    int tot=pietre[riga].numero[0] + pietre[riga].numero[1] + pietre[riga].numero[2] + pietre[riga].numero[3];

    printf("TEST #%d\n", riga+1);
    printf("zaffiro = %d, rubino = %d,  topazio = %d, smeraldo = %d, TOT = %d\n", pietre[riga].numero[0], pietre[riga].numero[1],
           pietre[riga].numero[2], pietre[riga].numero[3], tot);
}
///vettore temporaneo collana
void rimanenti(int riman[numPietre], stones pietre){
    riman[0] = pietre.numero[0];
    riman[1] = pietre.numero[1];
    riman[2] = pietre.numero[2];
    riman[3] = pietre.numero[3];
}
///dimensione delle soluzioni
int trovaDimensione(int riman[numPietre], int dim) {
    int dimensione;
    if(riman[1] > riman[2])
        dimensione = riman[0] + riman[3] + (riman[1] + riman[2]) - (riman[1] - riman[2]) + 1;
    else if(riman[1] < riman[2])
        dimensione = riman[0] + riman[3] + (riman[2] + riman[1]) - (riman[2] - riman[1]) + 1;
    else
        dimensione = dim;

    return dimensione;
}
///FUNZIONE WRAP CHE RACCOGLIE LA MAGGIOR PARTE DELLE OPERAZIONI PER FARE LA COLLANA
void preparativo(int nr, stones *pietre){
    int riman[numPietre], bool=0, i, dimensione, dimensioneMAX;
    char *collana;

    for(i=0; i<nr; i++) {
        stampaPietre(pietre, i);
        rimanenti(riman, pietre[i]);
        dimensioneMAX = riman[0] + riman[1] + riman[2] + riman[3];
        dimensione = trovaDimensione(riman, dimensioneMAX);
        ///ALLOCO OGNI VOLTA LA COLLANA DELLA LUNGHEZZA CHE MI SERVE
        collana = malloc(dimensione*sizeof(char));
        if(collana == NULL){
            printf("errore nell'allocazione");
            exit(1);
        }

        formaCollana(riman, dimensione, collana, bool, 0);
    }

    free(collana);
}
///FUNZIONE CHE FORMA LA COLLANA IN MANIERA RICORSIVA
int formaCollana(int riman[numPietre], int dimensione, char *collana, int bool, int pos) {
    int i;

    ///CONDIZIONE DI TERMINAZIONE
    if(pos >= dimensione) {
        printf("La collana e' lunga %d pietre :\n", dimensione);
        stampaCollana(collana, dimensione);
        bool = 1;
        return bool;
    }
    ///PASSO SU OGNI PIETRA PARTENDO DALLA PRIMA FINCHE NON TROVO QUELLA APPARTENENTE ALLA CATENA GIUSTA
    for(i=0; i<numPietre; i++){
        if(riman[i] > 0){
            riman[i]--;
            ///RIEMPIO LA COLLANA
            if(i == 0){
                collana[pos] = 'z';
            }
            else if(i == 1){
                collana[pos] = 'r';
            }
            else if(i == 2){
                collana[pos] = 't';
            }
            else if(i == 3){
                collana[pos] = 's';
            }
            ///CONTROLLO CHE LA COLLANA RISPETTI LE REGOLE
            if(condizione(collana, pos)){
                bool = formaCollana(riman, dimensione, collana, bool, pos+1);
            }
            riman[i]++;
            if(bool){
                return bool;
            }
        }
    }
    return bool;

}
///CONTROLLA CHE LA LEGGE DI FORMAZIONE DELLA COLLANA SIA RISPETTATA
int condizione(char *collana, int pos) {
    int val = 1;

    if (pos == 0)
        return val;
    if(collana[pos -1] == 'z')
        if(collana[pos] == 'z' || collana[pos] == 'r')
            return val;
    if(collana[pos -1] == 'r')
        if(collana[pos] == 's' || collana[pos] == 't')
            return val;
    if(collana[pos -1] == 't')
        if(collana[pos] == 'z' || collana[pos] == 'r')
            return val;
    if(collana[pos -1] == 's')
        if(collana[pos] == 's' || collana[pos] == 't')
            return val;

    val = 0;
    return val;
}