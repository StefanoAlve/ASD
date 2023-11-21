#include <stdio.h>
#include <stdlib.h>
#define lmax 50
typedef struct{
    int Si;
    int Fi;
}att;
att *leggi_file(FILE *file, int n);// funzione che legge file e riempie il vettore di struct
void attSel(int N, att *v);// Funzione wrapper
void powerset(int pos, att *v, int n,int *sol, int *sol_best,int diff,int *diff_max);// funzione ricorsiva che ricerca il sotto_insieme di durata massima
int verificaAtt(int pos,att *v,int *sol);// funzione che verica la compatibilità di due sotto_insiemi
int main(){
    att *p_att;
    FILE *fin;
    int n;
    char nome_file[lmax];
    printf("Inserisci il nome del file da cui vuoi leggere: \n");
    scanf("%s",nome_file);
    if((fin = fopen(nome_file,"r"))==NULL){
        printf("Errore");
    }
    else{
        fscanf(fin,"%d",&n);
        //printf("%d\n",n);
        p_att = leggi_file(fin,n);
    }
    attSel(n,p_att);// funzione wrapper

}

void attSel(int N, att *v){// funzione wrapper

    int *sol, *sol_best, cnt = 0, diff = 0, diff_max = 0;
    sol = calloc(N ,sizeof(int));
    sol_best = calloc(cnt, sizeof (int));

    powerset(0,v,N,sol, sol_best,diff,&diff_max);// funzione di ricerca sotto_insieme
// stampa dei sotto-insiemi di durata massima
    for(int i = 0;i<N;i++){
        if (sol_best[i]==1)
            printf("%d %d\n",v[i].Si,v[i].Fi);
    }
    free(sol);
    free(sol_best);
}
// Funzione che legge il file e riempi il vettore di struct
att *leggi_file(FILE *file, int n){
    att *x;
    x = malloc(n*sizeof (att));
    //printf("%d",num_righe);
    for(int i =0;i<n;i++){
        fscanf(file,"%d %d",&(x[i].Si),&(x[i].Fi));
    }
    fclose(file);
    return x;
}
// Funzione che genere tutti i sotto-insiemi e ricerca quelli con durata massima
void powerset(int pos, att *v, int n,int *sol, int *sol_best, int diff, int *diff_max){

    if (pos>= n){
        if(*diff_max < diff){
            *diff_max = diff;
            for(int i = 0;i<n;i++)
                sol_best[i]= sol[i];
        }
        return;
    }
            sol[pos]= 0;
            powerset(pos+1, v, n,sol, sol_best,diff, diff_max);

    if(!verificaAtt(pos,v,sol)){

        sol[pos] = 1;
        diff+=v[pos].Fi-v[pos].Si;
        powerset(pos+1, v, n, sol, sol_best,diff, diff_max);
    }
    return;
}
// funzione che verifica tutte le attività se sono compatibili
int verificaAtt(int pos,att *v,int *sol){
    for(int i = 0;i<pos;i++){
        if (sol[i]!=0){
            if(v[i].Si<v[pos].Fi && v[pos].Si<v[i].Fi)
                return 1;
        }
    }
    return 0;
}