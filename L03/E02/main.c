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

int LeggiFile(FILE *fp, s_CanzoniAmico **p_v_CA, char **Canzoni);
void StampaPlaylist(s_CanzoniAmico *v_CA, int n, char **Canzoni);
void Dealloc(s_CanzoniAmico *v_CA, int n, char **Canzoni);

int main(){
    FILE *fp = fopen("brani.txt", "r");
    s_CanzoniAmico *v_CA; //vettore di struct
    int n_amici;
    char *Canzoni[MAXC]; //vettore statico di puntatori a char, ovvero le canzoni, allocate dinamicamente dopo
    n_amici = LeggiFile(fp, &v_CA, Canzoni);
    StampaPlaylist(v_CA, n_amici, Canzoni);
    Dealloc(v_CA, n_amici, Canzoni);


    return 0;
}

//La funzione riceve come parametri il vettore delle canzoni da riempire,
//allocando dinamicamente le singole canzoni e un puntatore al vettore di struct per
//ritornare by pointer il vettore delle struct completo. La funzione
//legge il file e alloca dinamicamente il vettore delle struct e le canzoni
int LeggiFile(FILE *fp, s_CanzoniAmico **p_v_CA, char **Canzoni){
    s_CanzoniAmico *vca; //vettore di struct interno
    char song[MAXN]; //canzone letta da file
    int t = 0, numS; //t usato come indice nel vettore delle canzoni, numS è il numero di amici
    fscanf(fp, "%d", &numS);
    vca = malloc(numS*sizeof *vca); //allocazione vettore di struct
    for (int i = 0; i < numS; i++) {
        int nc;
        fscanf(fp, "%d", &nc);
        vca[i].numCanzoni = nc;
        vca[i].IndiciCanzoni = malloc(nc * sizeof(int)); //allocazione vettore di interi, indici di riferimento alle canzoni
        for (int j = 0; j < nc; j++) {
            fscanf(fp, "%s", song);
            Canzoni[t++] = strdup(song); //allocazione dimanica singole canzoni
            vca[i].IndiciCanzoni[j] = t; //inserimento nel vettore di interi dell'indice in cui la canzone si trova la canzone nel vettore con tutte le altre
        }
    }

    *p_v_CA = vca; //aggancio del puntatore al vettore di struct per ritornarlo al main

    return numS;
}

void StampaPlaylist(s_CanzoniAmico *v_CA, int n, char **Canzoni){



















}