#include <stdio.h>
#include <stdlib.h>
#define numPietre 4

typedef struct{
    int z;
    int r;
    int t;
    int s;
}pietre_s;

pietre_s *structDaFile(pietre_s *pietre, FILE *fp, int numTest);
FILE *aperturaFile(FILE *fp);
int verificaAccettabilita(int *collana, int pos, int att);
void stampaCollana(pietre_s pietre, int maxLSol);
int generaCollana(int *val, int *sol, int pos, int k) {

    if (pos >= k) {
        return 1;
    }

    for (int i = 0; i < numPietre; i++) {
        if (val[i] > 0) {
            if (verificaAccettabilita(sol, pos, i)) {
                sol[pos] = i;
                val[i]--;

                if (generaCollana(val, sol, pos + 1, k)) {
                    return 1;
                }
                val[i]++;
            }
        }
    }
    return 0;
}

int main(){
    FILE *fp = NULL;
    int numTest;

    //Apertura file
    fp = aperturaFile(fp);
    fscanf(fp, "%d", &numTest);

    //Assegnazione di struct da file
    pietre_s *pietre = NULL;
    pietre = structDaFile(pietre, fp, numTest);

    //Chiamata a funzione ricorsiva per trovare le combinazioni di pietre
    for(int i = 0; i < numTest; i++){

        int maxLSol = pietre[i].r + pietre[i].s + pietre[i].t + pietre[i].z; // Lunghezza massima vettore soluzione

        int *sol_max = (int *) malloc(maxLSol * sizeof(int));
        int *val = (int *)malloc(numPietre * sizeof(int));
        int *sol = (int *)malloc(maxLSol * sizeof(int));

        printf("TEST %d:\n", i+1);

        int max = maxLSol, min = 0, k, pos = 0;

        while (min <= max) {
            k = min + (max - min) / 2;

            val[0] = pietre[i].z;
            val[1] = pietre[i].r;
            val[2] = pietre[i].t;
            val[3] = pietre[i].s;

            if (generaCollana(val, sol, pos, k)) {
                maxLSol = k;
                min = k + 1;
            } else {
                max = k - 1;
            }
        }

        //Stampa a video
        stampaCollana(pietre[i], maxLSol);

        //Deallocazione
        free(val);
        free(sol);
        free(sol_max);
    }

    //Chisura file
    fclose(fp);
    free(pietre);
    return 0;
}

//Funzione che prende le informazioni da file e le assegna a struct
pietre_s *structDaFile(pietre_s *pietre, FILE *fp, int numTest){

    //Allocazione memoria e gestione errori
    pietre = (pietre_s*)malloc(numTest * sizeof(pietre_s));
    if(pietre == NULL){
        printf("Errore nell'allocazione di struct!");
        exit(2);
    }

    for(int i = 0; i < numTest; i++){
        fscanf(fp, "%d %d %d %d", &pietre[i].z, &pietre[i].r, &pietre[i].t, &pietre[i].s);
    }

    return pietre;
}

//Funzione per l'apertura del file
FILE *aperturaFile(FILE *fp){
    char nomeFile[50];

    //Prendo informazione da tastiera
    printf("Inserisci il nome del file:");
    scanf("%s", nomeFile);
    printf("\n");

    //Gestione errori
    if((fp = fopen(nomeFile, "r")) == NULL){
        printf("Errore nell'apertura del file %s", nomeFile);
        exit(1);
    }

    return fp;
}

//Filtro di accettabilità
int verificaAccettabilita(int *collana, int pos, int att){
    if (pos <= 0) {
        return 1;  // La prima pietra è sempre accettabile
    }

    int prec = collana[pos - 1];

    // Regole di accettabilità
    if ((prec == 0 && (att == 0 || att == 1)) ||
        (prec == 1 && (att == 2 || att == 3)) ||
        (prec == 2 && (att == 0 || att == 1)) ||
        (prec == 3 && (att == 2 || att == 3))) {
        return 1;
    }

    return 0;
}

//Funzione di stampa della collana
void stampaCollana(pietre_s pietre, int maxLSol){

    printf("La collana aveva zaffiri = %d, rubini = %d, topazi = %d, smeraldi = %d, TOT: %d\n",
           pietre.z, pietre.r, pietre.t, pietre.s,
           pietre.z + pietre.r + pietre.t + pietre.s);
    printf("Collana massima di lunghezza %d\n", maxLSol);
}

