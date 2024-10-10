#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXC 100
#define MAXN 255

//Struct che contiene un vettore di interi che si riferiscono
//agli indici del vettore di tutte le canzoni, per capire quali
//canzoni sono di quale amico, e la dimensione del suddetto vettore
typedef struct{
    int *IndiciCanzoni;
    int numCanzoni;
}s_CanzoniAmico;

int LeggiFile(FILE *fp, s_CanzoniAmico **p_v_CA, char **Canzoni, int *pt);
void StampaPlaylist(s_CanzoniAmico *v_CA, int n, char **Canzoni);
int princMolt(s_CanzoniAmico *v_CA, int n, char **Canzoni, int *sol, int pos, int cnt);
void Dealloc(s_CanzoniAmico *v_CA, int n, char **Canzoni, int t);

int main(){
    FILE *fp = fopen("brani.txt", "r");
    s_CanzoniAmico *v_CA; //vettore di struct
    int n_amici, t = 0; //t conta il numero totale delle canzoni
    char *Canzoni[MAXC]; //vettore statico di puntatori a char, ovvero le canzoni, allocate dinamicamente dopo
    n_amici = LeggiFile(fp, &v_CA, Canzoni, &t);
    StampaPlaylist(v_CA, n_amici, Canzoni);
    Dealloc(v_CA, n_amici, Canzoni, t);

    return 0;
}

//La funzione riceve come parametri il vettore delle canzoni da riempire,
//allocando dinamicamente le singole canzoni e un puntatore al vettore di struct per
//ritornare by pointer il vettore delle struct completo. La funzione
//legge il file e alloca dinamicamente il vettore delle struct e le canzoni
int LeggiFile(FILE *fp, s_CanzoniAmico **p_v_CA, char **Canzoni, int *pt){
    s_CanzoniAmico *vca; //vettore di struct interno
    char song[MAXN]; //canzone letta da file
    int numA; //t usato come indice nel vettore delle canzoni, numS è il numero di amici
    fscanf(fp, "%d", &numA);
    vca = malloc(numA*sizeof *vca); //allocazione vettore di struct
    for (int i = 0; i < numA; i++) {
        int nc;
        fscanf(fp, "%d", &nc);
        vca[i].numCanzoni = nc;
        vca[i].IndiciCanzoni = malloc(nc * sizeof(int)); //allocazione vettore di interi, indici di riferimento alle canzoni
        for (int j = 0; j < nc; j++) {
            fscanf(fp, "%s", song);
            Canzoni[*pt] = strdup(song); //allocazione dimanica singole canzoni
            vca[i].IndiciCanzoni[j] = (*pt)++; //inserimento nel vettore di interi dell'indice in cui la canzone si trova la canzone nel vettore con tutte le altre
        }
    }

    *p_v_CA = vca; //aggancio del puntatore al vettore di struct per ritornarlo al main

    return numA;
}

//Funzione wrapper per l'applicazione del principio della moltiplicazione
//per trovare le playlist. Si occupa di allocare e deallocare il vettore delle soluzioni
void StampaPlaylist(s_CanzoniAmico *v_CA, int n, char **Canzoni){
    //vettore di interi/playlist trovata, pos indica a quale amico ci stiamo riferendo
    //cnt conta il numero di playlist trovate
    int *sol, pos = 0, cnt = 0;

    sol = malloc(n*sizeof *sol);
    cnt = princMolt(v_CA, n, Canzoni, sol, pos, cnt);
    printf("Numero playlist trovate: %d", cnt);
    free(sol);

}

//Funzione ricorsiva che stampa le playlist: a ogni chiamata ricorsiva
//aggiungo alla soluzione una canzone presa dall'amico successivo, e
//stampo la playlist quando pos raggiunge il numero degli amici. Il flag
//serve per non stampare la soluzione se non è stata modificata dopo l'ultima ricorsione
int princMolt(s_CanzoniAmico *v_CA, int n, char **Canzoni, int *sol, int pos, int cnt){
    if (pos >= n){ //condizione di terminazione
        for (int i = 0; i < pos; i++)
            printf("%s\n", Canzoni[sol[i]]); //sol[i] contiene l'indice della canzone in Canzoni
        printf("\n");
        return cnt+1; //soluzione trovata, incremento il contatore
    }

    for (int j = 0; j < v_CA[pos].numCanzoni; j++){
        sol[pos] = v_CA[pos].IndiciCanzoni[j]; //Aggiungo alla soluzione una nuova canzone
        cnt = princMolt(v_CA, n, Canzoni, sol, pos+1, cnt);
    }

    return cnt;

}

//Funzione di deallocazione memoria del vettore di struct e del vettore delle canzoni
void Dealloc(s_CanzoniAmico *v_CA, int n, char **Canzoni, int t){
    //dealloc Canzoni
    for (int i = 0; i < t; i++)
        free(Canzoni[i]);

    //dealloc v_CA
    for (int i = 0; i < n; i++)
        free(v_CA[i].IndiciCanzoni);
    free(v_CA);
}