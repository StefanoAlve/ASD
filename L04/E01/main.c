#include <stdio.h>
#include <stdlib.h>

#define MAXN 50

typedef struct{
    int u;
    int v;
} arco;

//Funzioni
void LeggiFile(arco **v_archi, int **val, int *pN, int *pE);
int VertexCover(int pos, int *sol, arco *v_archi, int *val, int *pN, int *pE, int cnt);
int ValidaVertexCover(int *sol, arco *v_archi, int *pE);

int main() {
    arco *v_archi = NULL;
    int N, E, *pN = &N, *pE = &E, *sol = NULL, *val = NULL, cnt = 0, pos = 0;

    LeggiFile(&v_archi,&val,pN,pE);

    sol = (int *) malloc(*pN * sizeof(int));
    if (sol == NULL) {printf("Errore allocazione memoria"); exit(1);}

    printf("I Vertex Cover sono:\n");
    cnt = VertexCover(pos, sol, v_archi, val, pN, pE, cnt);
    if (cnt != 0) printf("Il numero di vertex cover e' %d", cnt);
    else printf("Il grafo non presenta alcun vertex cover");

    //Deallocazione vettori dinamici
    free(sol); free(val); free(v_archi);

    return 0;
}

// Leggo il file e alloco i dati nelle varie strutture
void LeggiFile(arco **v_archi, int **val, int *pN, int *pE){
    FILE *fp;
    arco *V_archi = NULL;
    char NomeFile[MAXN];
    int i = 0, N=0, E=0, *Val = NULL;

    printf("Inserire il nome del file:\n");
    scanf("%s", NomeFile);

    fp = fopen(NomeFile,"r");

    if (fp != NULL){
        fscanf(fp,"%d %d",&N,&E);

        //Allocazione vettore di struct e vettore di interi
        V_archi = (arco *) malloc(E * sizeof(arco));
        Val = (int *) malloc(N * sizeof(int));
        if (V_archi == NULL || Val == NULL) {printf("Errore allocazione memoria"); exit(1);}
        //Inizializzazione vettore dei vertici
        for (int j = 0; j<N; j++) Val[j] = j; //si utilizza val nel caso si decida un modo diverso di nominare i vertici con degli interi
        while (fscanf(fp,"%d %d",&V_archi[i].u, &V_archi[i].v) == 2 && i<E){
            i++;
        }
    } else {
        printf("Errore apertura file\n");
        exit(1);
    }
    *v_archi = V_archi; *val = Val;
    *pN = N; *pE = E;
    fclose(fp);

}

//La funzione implementa l'algoritmo della definizione dell'insieme delle
//parti di un insieme. L'insieme è quello dei vertici, e un vertex cover del
//grafo è una "parte" di quell'insieme che corrisponde alle caratteristiche del vertex cover
int VertexCover(int pos, int *sol, arco *v_archi, int *val, int *pN, int *pE, int cnt){
    //Algoritmo del powerset secondo il modello delle disposizioni ripetute

    int j;
    if (pos >= *pN){
        if (ValidaVertexCover(sol,v_archi,pE)){
            printf("{ \t");
            for (j = 0; j < *pN; j++)
                if (sol[j] != 0) printf("%d \t", val[j]);
            printf("} \t");
            printf("\n");
            return cnt+1;
        }
        return cnt;
    }

    sol[pos] = 0;
    cnt = VertexCover(pos+1, sol, v_archi, val, pN, pE, cnt);
    sol[pos] = 1;
    cnt = VertexCover(pos+1, sol, v_archi, val, pN, pE, cnt);

    return cnt;
}

//La funzione controlla che per ogni arco, e quindi per ogni coppia di vertici, nel vettore della soluzione i valori alla
//posizione data dal numero dei vertici siano entrambi 0. Ciò significa che nessuno dei 2 vertici fa parte della soluzione, ed è
//quindi impossibile che quella soluzione sia un vertex cover del grafo (ci deve almeno essere un vertice per ogni arco)
int ValidaVertexCover(int *sol, arco *v_archi, int *pE){
    int valido = 1, i;
    for (i = 0; i < *pE; i++){
        if (sol[v_archi[i].u] == 0 && sol[v_archi[i].v] == 0){
            valido = 0;
            break; //interrompo perché è sufficiente che un solo arco non abbia almeno un valore nel vertex cover
        }
    }
    return valido;
}