#include <stdio.h>
#include <stdlib.h>

#define MAXN 50

typedef struct{
    int u;
    int v;
} arco;

void LeggiFile(arco *v_archi, int *val, int *pN, int *pE);
int VertexCover(int *sol, arco *v_archi, int *val, int *pN, int *pE, int cnt);

int main() {
    arco *v_archi = NULL;
    int N, E, *pN = &N, *pE = &E, *sol = NULL, *val = NULL, cnt = 0;

    LeggiFile(v_archi,val,pN,pE);

    sol = (int *) malloc(*pN * sizeof(int));
    cnt = VertexCover(sol, v_archi, val, pN, pE, cnt);

    return 0;
}

// Leggo il file e alloco i dati nelle varie strutture
void LeggiFile(arco *v_archi, int *val, int *pN, int *pE){
    FILE *fp;
    char NomeFile[MAXN];
    int i = 0;

    printf("Inserire il nome del file:\n");
    scanf("%s", NomeFile);

    fp = fopen(NomeFile,"r");

    if (fp != NULL){
        fscanf(fp,"%d %d",pN,pE);

        //Allocazione vettore di struct e vettore di interi
        v_archi = (arco *) malloc(*pE * sizeof(arco));
        val = (int *) malloc(*pN * sizeof(int));
        //Inizializzazione vettore dei vertici
        for (int j = 0; j<*pN; j++) val[j] = j;

        while (fscanf(fp,"%d %d",&v_archi[i].u, &v_archi[i].v) == 2 && i<*pE){
            i++;
        }
    } else {
        printf("Errore apertura file\n");
        exit(1);
    }

}

//La funzione implementa l'algoritmo della definizione dell'insieme delle
//parti di un insieme. L'insieme è quello dei vertici, e un vertex cover del
//grafo è una "parte" di quell'insieme che corrisponde alle caratteristiche del vertex cover
int VertexCover(int *sol, arco *v_archi, int *val, int *pN, int *pE, int cnt){
    //Algoritmo powerset secondo il modello delle disposizioni ripetute
}