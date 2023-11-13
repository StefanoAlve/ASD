#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXC 100
typedef struct{
   int si;
   int fi;
}s_att;

typedef struct{
    int *dimVet;
    s_att **mat;
}s_max;
int leggiFile(s_att **pvettAtt);
void attSel(int N, s_att *v);
int verificaAtt(s_att *sol, int N);
void powerset(s_att *vettAtt, int n, s_att *sol, s_att *max, int durataPrec, int dimSol, int pos, int start);
void deallocaMax(s_max max, int N);
int calcolaDurata(s_att *sol, int dimSol);
int trovaSol(s_max max,int N);
int main(void){
    //Inizializzazione variabili
    s_att *vettAtt;
    int nAtt;
    //Corpo programma
    nAtt = leggiFile(&vettAtt);
    attSel(nAtt, vettAtt);
    //Deallocazione memoria
    free(vettAtt);
    return 0;
}

int leggiFile(s_att **pvettAtt){
    s_att *vettAtt;
    FILE *fp;
    int nAtt;
    char tmp[MAXC], *nomeFile;
    //Apertura file
    printf("Inserire il nome del file:");
    scanf("%s", tmp);
    nomeFile = strdup(tmp);
    fp = fopen(nomeFile,"r");
    if(fp == NULL){
        printf("Errore nell'apertura del file!\n");
        exit(1);
    }
    free(nomeFile);

    //Allocazione vettAtt
    fscanf(fp,"%d", &nAtt);
    vettAtt = (s_att*)malloc(nAtt* sizeof(s_att));

    //Corpo programma
    for(int i=0; i<nAtt; i++){
        fscanf(fp, "%d %d", &vettAtt[i].si, &vettAtt[i].fi);
    }
    *pvettAtt = vettAtt;
    return nAtt;
}

void attSel(int N, s_att *v){
    s_att *sol;
    s_max max;
    int durataPrec=0,pos=0,start=0,i,indiceSol;

    //Allocazione dinamica
    sol = (s_att *)malloc(N*sizeof(s_att));
    max.mat = (s_att **) malloc(N * sizeof(s_att *));
    max.dimVet = (int*) malloc(N*sizeof(int));
    for(i=0; i<N; i++){
        max.dimVet[i] = i+1;
        max.mat[i] = (s_att*) malloc((max.dimVet[i])*sizeof(s_att));
    }
    for(i=1; i<=N; i++){
        powerset(v, N, sol, max.mat[i-1], durataPrec, i, pos, start);
    }

    indiceSol = trovaSol(max, N);

    printf("L'attivita' che massimizza la somma e': ");
    for(i=0;i<max.dimVet[indiceSol];i++){
        printf("(%d,%d) ", (max.mat[indiceSol][i]).si, (max.mat[indiceSol][i]).fi);
    }
    printf("\n");

    free(sol);
    deallocaMax(max,N);
}

void powerset(s_att *vettAtt, int n, s_att *sol, s_att *max, int durataPrec, int dimSol, int pos, int start){
    int i, durataSol;
    if(pos >= dimSol){
        durataSol = calcolaDurata(sol, dimSol);
        if(durataSol >= durataPrec){
            for(i=0; i<pos; i++){
                max[i] = sol[i];
            }
        }
        return;
    }
    for(i=start; i<n; i++){
        sol[pos] = vettAtt[i];
        if(verificaAtt(sol, pos+1)){
            powerset(vettAtt, n, sol, max, durataPrec, dimSol, pos+1, i+1);
        }
    }
}

void deallocaMax(s_max max, int N){
    int i;
    for(i=0; i<N;i++){
        free(max.mat[i]);
    }
    free(max.mat);
    free(max.dimVet);
}

int calcolaDurata(s_att *sol, int dimSol){
    int durataTot=0;

    for(int i=0; i<dimSol;i++){
        durataTot += sol[i].fi - sol[i].si;
    }
    return durataTot;
}

int trovaSol(s_max max,int N){
    int indiceSol=0;
    for(int i = 1; i<N; i++){
        if(calcolaDurata(max.mat[i], N) > calcolaDurata(max.mat[i-1],N)){
            indiceSol = i;
        }
    }
    return indiceSol;
}

int verificaAtt(s_att *sol, int N){
    int flag = 1;
    s_att precedente, attuale;
    if(N > 0){
        for(int i = 1; i<N && flag; i++) {
            attuale = sol[i];
            precedente = sol[i - 1];
            if ((attuale.si >= precedente.si && attuale.si < precedente.fi) ||
                (precedente.fi > attuale.si && precedente.si < attuale.fi) ||
                (attuale.si == precedente.si && precedente.fi == attuale.fi)) {
                flag = 0;
            }
        }
    return flag;
    }
}