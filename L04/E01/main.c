#include <stdio.h>
#include <stdlib.h>
typedef struct{// struct per gli archi del grafo
    int u;
    int v;
}arco;
int powerset(int pos,int *tmp,int e,arco *pArchi,int cnt);// funzione che cerca tutti i vertex cover
int controllo_vertex(int *tmp ,arco *pArchi,int num_archi);// controllo tutti i vertex cover possibili


int main() {
    FILE *fin;
    int N,E,i,cnt=0;
    int *nodi,*sol;
    arco *pArchi;
// leggo il file
    if((fin = fopen("grafo.txt","r"))==NULL){
        printf("Errore di apertura file.");
        return -1;
    }
    // se va bene inserisco gli archi nella struct
    else{
        fscanf(fin,"%d %d",&N,&E);// leggo il numero di nodi e il numero di archi
        pArchi = (arco*) malloc(E*sizeof(arco));
        for(i = 0;i<E;i++){
            // inserimento degli archi nella struct
            fscanf(fin,"%d %d",&pArchi[i].u, &pArchi[i].v);
           // printf("%d %d\n",pArchi[i].u,pArchi[i].v);

        }
         nodi = malloc(N*sizeof(int));
        sol = calloc(N, sizeof(int)); // vettore indici te
        for (i=0;i<N;i++){
            nodi[i] = i;
        }
        for(i =0 ;i<N ;i++)
        {
            sol[i]=0;
        }

        cnt = powerset(0, sol, E, pArchi, cnt);
        printf("%d",cnt);
    }


    free(nodi);
    free(sol);
}
int powerset(int pos,int *tmp,int e,arco *pArchi,int cnt) {
    int j;
    if (pos >= e) {
        if(controllo_vertex(tmp,pArchi,e)==1){
            printf("vertex cover: { ");
            for (j = 0; j < e; j++){
                if (tmp[j] ==1){
                    printf("%d ", j);
                }
            }
            printf(" } \n");
            return cnt+1;
        }
        return cnt;
    }
    // escludo l' elemento pos
    tmp[pos] = 0;
    cnt = powerset(pos + 1, tmp, e, pArchi,cnt);
    // faccio backtrack e riprendo l'elemento in pos
    tmp[pos] = 1;
    cnt = powerset(pos + 1, tmp, e, pArchi,cnt);
    return cnt;
}
// funzione che controlla i vertex cover
int controllo_vertex(int *tmp ,arco *pArchi,int num_archi){
    int flag = 1;

    for(int i=0; i<num_archi; i++)
        if ((tmp[pArchi[i].u]==0) && (tmp[pArchi[i].v]==0))
            flag = 0;

    return flag;

}
