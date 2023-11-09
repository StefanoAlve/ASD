#include <stdio.h>
#include <stdlib.h>

#define file_name "grafo.txt"
typedef struct{
    int u;
    int v;
}arco;

void riempi_vett_archi(FILE *fp_in, arco* *vet_archi, int* N, int* E);
void stampa_vett_archi(arco *vet_archi, int E);
int* vet_vertici(int N);
int powerset_mod(int pos, int *val, int *sol, int k, int count, int *vertex_cover, arco *archi, int E);
int check_vertex_cover(int *vertex_cover, arco *archi, int N, int E, int count);

int main()
{
    arco *vet_archi;
    int *sol, *vertex_cover;
    int cont = 0;
    int N, E, *vertici = NULL;
    FILE *fp_in = fopen(file_name, "r");
    riempi_vett_archi(fp_in, &vet_archi, &N, &E);
    stampa_vett_archi(vet_archi, E);
    vertici = vet_vertici(N);
    sol = (int*)malloc(N*sizeof(int));
    vertex_cover = (int*)malloc(N * sizeof(int));
    printf("\n");
    cont = powerset_mod(0, vertici, sol, N, cont, vertex_cover, vet_archi, E);
    if (cont)
        printf("\nIn totale ci sono %d vertex cover.", cont);
    else
        printf("\nNon ho trovato alcun vertex cover.");
    free(vet_archi);
    free(sol);
    free(vertex_cover);
    free(vertici);
    fclose(fp_in);
    return 0;
}


void riempi_vett_archi(FILE *fp_in, arco* *vet_archi, int* N, int* E)
{
    int n_vertici, n_archi, i = 0;
    arco *vet_archi_t = NULL;
    fscanf(fp_in, "%d %d", &n_vertici, &n_archi);
    vet_archi_t = (arco*)malloc(n_archi*sizeof(arco));
    while(fscanf(fp_in, "%d %d", &(vet_archi_t[i].u), &(vet_archi_t[i].v)) == 2)
        i++;
    *N = n_vertici;
    *vet_archi = vet_archi_t;
    *E = n_archi;
}

void stampa_vett_archi(arco *vet_archi, int E)
{
    int i;
    printf("\nHo trovato i seguenti archi:");
    for(i = 0; i < E; i++){
        printf(" (%d-%d)", vet_archi[i].u, vet_archi[i].v);
    }
}

int* vet_vertici(int N)
{
    int *vertici = (int*)malloc(N*sizeof(int));
    int i;
    printf("\n\nI vertici del grafo sono:\n");
    for (i = 0; i < N; i++){
        vertici[i] = i;
    }
    for(i = 0; i < N; i++)
        printf("%d ", vertici[i]);
    printf("\n");
    return vertici;
}

int powerset_mod(int pos, int *val, int *sol, int k, int count, int *vertex_cover, arco *archi, int E)
{
    int i;
    if (pos >= k)
    {
        for(i = 0; i < k; i++)
        {
            if (sol[i] != 0)
                vertex_cover[i] = val[i];
            else
                vertex_cover[i] = -1;
        }
        count += check_vertex_cover(vertex_cover, archi, k, E, count);
        return count;
    }
    sol[pos] = 0;
    count = powerset_mod(pos+1, val, sol, k, count, vertex_cover, archi, E);
    sol[pos] = 1;
    count = powerset_mod(pos+1, val, sol, k, count, vertex_cover, archi, E);
    return count;
}


int check_vertex_cover(int *vertex_cover, arco *archi, int n, int e, int count)
{
    int i, j, u, v, flag1 = 0, flag2 = 1, valore;
    for (i = 0; i < e; i++)
    {
        flag1 = 0;
        u = archi[i].u;
        v = archi[i].v;
        for (j = 0; (j < n) & !flag1; j++)
        {
            if (vertex_cover[j] != -1)
            {
                valore = vertex_cover[j];
                if (valore >= 0 && (valore == u || valore == v))
                    flag1 = 1; // ho trovato un vertice che incide su uno dei due vertici dell'arco (u,v)
                else
                    flag1 = 0;
            }
        }
        if(flag1 == 0)
            flag2 = 0;
    }
    if(flag2)
    {
        printf("Vertex cover %d:\n", count+1);
        for(i = 0; i < n; i++)
            if(vertex_cover[i] != -1)
                printf("%d\t", vertex_cover[i]);
        printf("\n");
    }
    return flag2;
}