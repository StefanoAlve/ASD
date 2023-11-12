#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXL 50

typedef struct {
    int numero[4];
}stones;


stones *leggiFile(char nomeFile[MAXL], stones *pietre, int *nr);
void collane(stones *pietre, int nr);
int maxCompl(stones *pietre, int riga);
int maxTraDue(stones *pietre, int i, int j, int riga);
void stampaPietre(stones *pietre, int riga);
void stampaCollana(int collana[4], int tot);

int main() {
    char nomeFile[MAXL];
    stones *pietre = NULL;
    int nr, i, j;

    printf("inserire nome file: \n");
    scanf("%s", nomeFile);

    pietre = leggiFile(nomeFile, pietre, &nr);

    /*for(i=0; i<nr; i++){
        printf("gruppo %d: ", i+1);
        for(j=0; j<4; j++){
            printf(" %d", pietre[i].numero[j]);
        }
        printf("\n");
    }*/

    collane(pietre, nr);

    free(pietre);

    return 0;
}


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

void collane(stones *pietre, int nr) {
    int collana[4], i, j, indexMax, flag = 1, index, z=0, r=1, t=2, s=3, cont=0;
    ///CICLO CHE DOVRA FARE LE COLLANE
    for(i=0; i<nr; i++) {
        ///INIZIALIZZO OGNI VOLTA GLI ELEMENTI DELLE COLLANE A 0
        for(j=0; j<4; j++) {
            collana[j] = 0;
        }
        ///FUNZIONE DI STAMPA PIETRE
        stampaPietre(pietre, i);
        ///ELEMENTO DA CUI PARTIRE
        indexMax = maxCompl(pietre, i);



        pietre[i].numero[indexMax] -= 1;
        collana[indexMax] += 1;
        cont++;
        index = indexMax;


        while (flag) {
            ///CASO ZAFFIRO E TOPAZIO
            if (index == z || index == t) {
                ///CONDIZIONE TERMINATRICE
                if (pietre[i].numero[z] == 0 && pietre[i].numero[r] == 0) {
                    //if (pietre[i].numero[s] == 0 || pietre[i].numero[t] == 0)
                    flag = 0;

                } else {
                    if (pietre[i].numero[s] == 0 && pietre[i].numero[t] == 0) {
                        index = z;
                        pietre[i].numero[index] -= 1;
                        collana[index] += 1;
                        cont++;
                        if (pietre[i].numero[z] == 0)
                            flag = 0;
                    } else {
                        index = maxTraDue(pietre, z, r, i);
                        pietre[i].numero[index] -= 1;
                        collana[index] += 1;
                        cont++;
                    }
                }
            }
                ///CASO SMERALDO E RUBINO
            else if (index == s || index == r) {
                ///CONDIZIONE TERMINATRICE
                if (pietre[i].numero[s] == 0 &&
                    pietre[i].numero[t] == 0 /*&& (pietre[i].numero[z] == 0 || pietre[i].numero[r] == 0)*/)
                    flag = 0;
                    ///DECREMENTO PIETRE E INCREMENTO COLLANA
                else {
                    if (pietre[i].numero[z] == 0 && pietre[i].numero[r] == 0) {
                        index = s;
                        pietre[i].numero[index] -= 1;
                        collana[index] += 1;
                        cont++;
                        if (pietre[i].numero[s] == 0)
                            flag = 0;
                    } else {
                        index = maxTraDue(pietre, s, t, i);
                        pietre[i].numero[index] -= 1;
                        collana[index] += 1;
                        cont++;
                    }

                }
            }
        }
        ///FUNZIONE DI STAMPA COLLANA
        stampaCollana(collana, cont);
        flag = 1;
        cont = 0;


    }
}

///TROVA L'INDICE CON VALORE DI GRANDEZZA MASSIMA TRA TUTTI
int maxCompl(stones *pietre, int riga) {
    int i, ind=0;

    for(i=0; i<4; i++){
        if (pietre[riga].numero[i] > pietre[riga].numero[ind]) {
            ind = i;
        }
    }

    return ind;
}

///TROVA L'INDICE CON IL VALORE MASSIMO TRA DUE
int maxTraDue(stones *pietre, int i, int j, int riga) {
    int max = i;

    if(pietre[riga].numero[j] > pietre[riga].numero[i])
        max = j;

    return max;
}

///STAMPA LA COLLANA
void stampaCollana(int collana[4], int tot) {

    printf("COLLANA MASSIMA\nzaffiro = %d, rubino = %d,  topazio = %d, smeraldo = %d, TOT COLLANA = %d\n\n", collana[0],
           collana[1], collana[2], collana[3], tot);
}

///STAMPA LE PIETRE
void stampaPietre(stones *pietre, int riga){
    int tot=pietre[riga].numero[0] + pietre[riga].numero[1] + pietre[riga].numero[2] + pietre[riga].numero[3];

    printf("TEST #%d\n", riga+1);
    printf("zaffiro = %d, rubino = %d,  topazio = %d, smeraldo = %d, TOT = %d\n", pietre[riga].numero[0], pietre[riga].numero[1],
           pietre[riga].numero[2], pietre[riga].numero[3], tot);
}