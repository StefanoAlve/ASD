#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXC 100

//Applicabilità
/* Problema di ottimizzazione
 * Procedendo per assurdo, prendendo una soluzione ottima, se non fosse ottima la soluzione al problema per ogni sottosequenza
 * se ne potrebbe trovare una migliore e di conseguenza la soluzione ottima non sarebbe tale.
 */

/*La soluzione dinamica è conveniente
 * il numero di sottoproblemi indipendenti è polinomiale O(N) nella dimensione dei dati di ingresso
 * la soluzione di ciascun sottoproblema è O(N)
 * la soluzione dinamica ha quindi complessità O(N^2)
 */


typedef struct{
    int si;
    int fi;
}s_att;

int leggiFile(s_att **pvettAtt);
void stampaR(s_att *vettAtt, int collegamenti[], int i);
int trovaMaxR(s_att *vettAtt, int i);
void trovaMax(s_att *vettAtt, int N);
void attSel(int N, s_att *v);
int compatibile(s_att attuale, s_att precedente);
void mergeSort(s_att *vettAtt, s_att *aus, int N);
void merge(s_att *vettAtt, s_att *aus, int l, int q, int r);
void mergeSortR(s_att *vettAtt, s_att *aus, int l, int r);
int max(int n1, int n2);

int main() {
    //Inizializzazione variabili
    s_att *vettAtt;
    int nAtt;
    //Corpo programma
    nAtt = leggiFile(&vettAtt);
    s_att aus[nAtt];
    mergeSort(vettAtt, aus, nAtt);
    trovaMax(vettAtt, nAtt);
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
    if(vettAtt==NULL){
        printf("Errore nell'allocazione della memoria!\n");
        exit(1);
    }
    //Corpo programma
    for(int i=0; i<nAtt; i++){
        fscanf(fp, "%d %d", &vettAtt[i].si, &vettAtt[i].fi);
    }
    *pvettAtt = vettAtt;

    //Chiusura file
    fclose(fp);
    return nAtt;
}

void attSel(int N, s_att *v){
    int i, j, collegamenti[N], durate[N], codaMax = 0, durMax;
    durate[0] = durMax = v[0].fi-v[0].si; //Sottosequenza unitaria
    collegamenti[0] = -1;
    //Fisso un elemento del vettore creando una sottosequenza
    for(i=1; i<N; i++){
        collegamenti[i] = -1;
        durate[i] = v[i].fi-v[i].si;
        //Analizzo la massima durata per la sottosequenza
        for(j=0;j<i;j++){
            if(compatibile(v[i], v[j]) && durate[i] < v[i].fi-v[i].si+durate[j]){
                //Essendo in un ciclo sto controllando quale attività j consente di massimizzare la durata
                collegamenti[i] = j;
                durate[i] = v[i].fi-v[i].si+durate[j];
            }
        }
        //Se la durata attuale è maggiore o uguale di quella massima aggiorno
        if(durMax<=durate[i]){
            durMax = durate[i];
            codaMax = i;
        }
    }
    printf("L'attivita' che massimizza la durata e': ");
    stampaR(v, collegamenti, codaMax);
    printf("\nCon una durata complessiva di %d\n", durMax);
}

void stampaR(s_att *v, int collegamenti[], int i){
    ///Funzione di stampa ricorsiva
    if(collegamenti[i] == -1){
        printf("(%d,%d) ", v[i].si, v[i].fi);
        return;
    }
    stampaR(v, collegamenti, collegamenti[i]);
    printf("(%d,%d) ", v[i].si, v[i].fi);

}

int compatibile(s_att attuale, s_att precedente){
    if ((attuale.si >= precedente.si && attuale.si < precedente.fi) ||
        (precedente.fi > attuale.si && precedente.si < attuale.fi) ||
        (attuale.si == precedente.si && precedente.fi == attuale.fi)) {
        return 0;
    }
    return 1;
}

void mergeSort(s_att *vettAtt, s_att *aus, int N){
    int l=0, r=N-1;
    mergeSortR(vettAtt, aus, l, r);
}

void mergeSortR(s_att *vettAtt, s_att *aus, int l, int r){
    int q;
    if(l>=r) //Condizione di terminazione, ho letto tutto il vettore
        return;
    q=(l+r)/2;
    mergeSortR(vettAtt, aus, l, q);
    mergeSortR(vettAtt, aus, q+1, r);
    merge(vettAtt, aus, l, q, r);
}

void merge(s_att *vettAtt, s_att *aus, int l, int q, int r){
    int i,j,k;
    i=l;
    j=q+1;
    for(k=l; k<=r; k++){
        if(i>q)
            aus[k] = vettAtt[j++];
        else if(j>r)
            aus[k] = vettAtt[i++];
        else if(vettAtt[i].fi <= vettAtt[j].fi)
            aus[k] = vettAtt[i++];
        else
            aus[k] = vettAtt[j++];
    }
    for(k=l; k<=r; k++)
        vettAtt[k] = aus[k];
}

int trovaMaxR(s_att *vettAtt, int i){
    int j, ris;
    if(i==0)
        return vettAtt[i].fi-vettAtt[i].si;
    ris = vettAtt[i].fi-vettAtt[i].si;
    for(j=0; j<i; j++){
        if(compatibile(vettAtt[j], vettAtt[i]))
            ris = max(ris, vettAtt[i].fi-vettAtt[i].si+trovaMaxR(vettAtt, j));
        else
            ris = max(ris, trovaMaxR(vettAtt, j));
    }
    return ris;
}

int max(int n1, int n2){
    if(n1>n2)
        return n1;
    return n2;
}

void trovaMax(s_att *vettAtt, int N){
    int max;
    max = trovaMaxR(vettAtt, N-1);
    printf("La durata massima vale: %d\n", max);
}