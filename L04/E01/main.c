#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int v1;
    int v2;
} s_arco;

void CercaVertexCover(s_arco *archi, int n_a, int n_v);
void SetValidPartitions(s_arco *archi, int *sol, int n_a, int n_v, int pos, int k, int start);
int PartizioneValida(s_arco *archi, int *sol, int n_a, int k);

int main(){
    //Lettura da file e salvataggio dati
    FILE *fp = fopen("grafo.txt", "r");
    int n_v, n_a;
    fscanf(fp, "%d %d", &n_v, &n_a);
    s_arco *archi = malloc(n_a*sizeof *archi);
    for (int i = 0; i < n_v; i++)
        fscanf(fp, "%d %d", &archi[i].v1, &archi[i].v2);
    fclose(fp);

    CercaVertexCover(archi, n_a, n_v);

    return 0;
}

//La funzione alloca il vettore delle soluzioni e chiama la funzione ricorsiva
//tante volte quante sono le dimensioni possibili dei sottoinsiemi dei vertici (1 ... n_v)
void CercaVertexCover(s_arco *archi, int n_a, int n_v){
    int pos = 0, k, start = 0;
    int *sol = malloc(n_v*sizeof *sol);

    printf("Vertex Cover:\n");
    for (k = 1; k <= n_v; k++)
        SetValidPartitions(archi, sol, n_a, n_v, pos, k, start);
}

//La funzione usa il metodo delle combinazioni semplici per calcolare i
//sottoinsiemi di vertici di grandezza 1 ... n_v. Trovato un sottoinsieme
//verifica che sia un vertex Cover prima di stamparlo
void SetValidPartitions(s_arco *archi, int *sol, int n_a, int n_v, int pos, int k, int start){
    int i;

    if (pos >= k){
        if (PartizioneValida(archi, sol, n_a, k)){
            printf("{ ");
            for (i = 0; i < k; i++)
                printf("%d ", sol[i]);
            printf("}\n");
        }
        return;
    }

    for (i = start; i < n_v; i++){
        sol[pos] = i;
        SetValidPartitions(archi, sol, n_a, n_v, pos+1, k, i+1);
    }

}

//La funzione verifica che il sottoinsiemi di vertici sia un vertex cover:
//se in almeno un arco nessuno dei vertici è presente, allora non è vertex cover
int PartizioneValida(s_arco *archi, int *sol, int n_a, int k){
    int p, h;

    for (p = 0; p < n_a; p++){
        for (h = 0; h < k; h++){ //k è la dim attuale di sol
            if (sol[h] == archi[p].v1 || sol[h] == archi[p].v2)
                break; //Uscita anticipata: quell'arco ha almeno un vertice nel sottoinsieme

        }
        if (h == k) return 0; //nessun vertice è presente in quell'arco, no vertex cover
    }

    return 1;
}