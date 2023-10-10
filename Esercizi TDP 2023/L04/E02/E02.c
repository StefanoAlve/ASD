#include <stdio.h>
#include <math.h>
#define maxN 30

void ruota(int v[maxN], int N, int P, int dir);
int main(void) {
    //Inizializzazione variabili
    int N, v[maxN], P, dir,count;
    //Assegnazione variabili
    count = 0;
    P=1;
    //Corpo programma
    printf("\nInserire lunghezza vettore (minore di %d):",maxN);
    if (scanf(" %d",&N) != 1){
        printf("Valore inserito non valido!\n");
        return 1;
    }
    else if(N<=maxN){
        while(count<N){
            printf("\nInserire numero: ");
            if(scanf(" %d",&v[count]) == 1){
                count++;
            }
            else{
                printf("Valore inserito non valido!\n");
                return 2;
            }
        }
        printf("Il vettore da te scritto risulta:\n(");
        for (int i = 0; i < N; i++) {
            printf("%d ", v[i]);
        }
        printf(")\n");
        while(P!=0){
           printf("\nDi quante posizioni vuoi ruotare?(0 per terminare):");
            if (scanf(" %d",&P) != 1) {
                printf("Valore inserito non valido!\n");
                return 3;
            }
            else if(P!=0){
                printf("In che direzione vuoi ruotare?(-1=destra, 1=sinistra):");
                if (scanf(" %d", &dir) != 1 || (dir != 1 && dir != -1)) {
                    printf("\nValore inserito non valido!\n");
                    return 4;
                }
                else{
                    ruota(v,N,P,dir);
                    printf("\nIl vettore ruotato risulta:\n( ");
                    for (int i = 0; i < N; i++) {
                        printf("%d ", v[i]);
                    }
                    printf(")\n");
                }
            }
        }
    }
    else{
        printf("Lunghezza del vettore maggiore del massimo consentito (%d)",maxN);
        return 2;
    }
    return 0;
}

//funzioni

void ruota(int v[maxN], int N, int P, int dir){
    //Funzione che ruota di P posizioni nella direzione dir il vettore inserito
    //Inizializzazione variabili
    int ruotato[N], spostamento;
    //Assegnazione variabili
    P = P%N;
    //Corpo programma
    if(dir==-1){
        for(int j=0; j<N; j++) {
            spostamento = j+P;
            if(spostamento<N) {
                ruotato[spostamento] = v[j];
            }
            else{
                ruotato[abs(spostamento-N)] = v[j];
            }
        }
    }
    else{
        for(int j=0; j<N; j++){
            spostamento = j-P;
            if(spostamento>=0) {
                ruotato[(spostamento)] = v[j];
            }
            else{
                ruotato[abs(spostamento+N)] = v[j];
            }
        }
    }
    for(int i=0;i<N;i++){
        v[i] = ruotato[i];
    }
}