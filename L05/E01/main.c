#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXC 100
typedef struct{
   int si;
   int fi;
}s_att;

typedef struct{
    int dimVet;
    s_att *vet;
    int durata;
}s_max;
int leggiFile(s_att **pvettAtt);
void attSel(int N, s_att *v);
int verificaAtt(s_att *sol, int N);
void powerset(s_att *vettAtt, int n, s_att *sol, s_max *max, int dimSol, int pos, int start);
int calcolaDurata(s_att *sol, int dimSol);
void stampa(s_max max);
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
    int pos=0,start=0,i;

    //Allocazione dinamica
    sol = (s_att *)malloc(N*sizeof(s_att));
    max.vet = (s_att *) malloc(N * sizeof(s_att));

    //Inizializzazione di max
    max.dimVet = 0;
    max.durata = 0;
    for(i=1; i<=N; i++){
        powerset(v, N, sol, &max, i, pos, start);
    }

    stampa(max);

    free(sol);
    free(max.vet);
}

void powerset(s_att *vettAtt, int n, s_att *sol, s_max *max, int dimSol, int pos, int start){
    int i, durataSol;
    if(pos >= dimSol){
        durataSol = calcolaDurata(sol, dimSol);
        if(durataSol >= max->durata){
            for(i=0; i<pos; i++){
                max->vet[i] = sol[i];
            }
            max->dimVet = dimSol;
            max->durata = durataSol;
        }
        return;
    }
    for(i=start; i<n; i++){
        sol[pos] = vettAtt[i];
        if(verificaAtt(sol, pos+1)){
            powerset(vettAtt, n, sol, max, dimSol, pos+1, i+1);
        }
    }
}

int calcolaDurata(s_att *sol, int dimSol){
    int durataTot=0;

    for(int i=0; i<dimSol;i++){
        durataTot += sol[i].fi - sol[i].si;
    }
    return durataTot;
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
    }
    return flag;
}

void stampa(s_max max){
    printf("L'attivita' che massimizza la somma e': ");
    for(int i=0;i<max.dimVet;i++){
        printf("(%d,%d) ", (max.vet[i]).si, (max.vet[i]).fi);
    }
    printf("\n");
}