#include <stdio.h>
#include "stdlib.h"
#include "string.h"
#define MAXL 256
typedef struct{
    char **canzoni; //puntatore a vettore di stringhe
}sCanzoni;

typedef struct {
    int *enum_canzoni;
    int num_canzoni_scelte;//numero di canzoni per amico
} sAmico; //creo un vettore di structAmico per contenere i dati relativi ad ogni amico

//pos identifica il livello della ricorsione e serve per decidere quali caselle di scelta usare o soluzione riempire
//num amici indicano la dimensione del problema e della soluzione cercata, le scelte possibili sono memorizzate
// in un vettore Amici di dimensione numamici di strutture sAmico;
// ogni struttura è un intero per il numero di scelte per quel livello
//num_canzoni_scelte e il vettore enum_canzoni di interi di dimensione num_canzoni_scelte per le scelte
//la soluzione è memorizzata in un vettore di interi sol di dimensione n

int CombinazioniSemplici(int pos, sAmico *Amici, sCanzoni *Canzoni_amico, int *sol, int numamici, int count);//nel vettore sol inserisco le combinazioni delle soluzioni
FILE* aperturafilelettura();//funzione per apertura file
int letturaEallocazione(FILE* fin, sAmico **Amici, sCanzoni **Canzoni_amici); //funzione che legge ed alloca un vettore di sAmico
void FreeStruttureDati(sAmico *Amici,sCanzoni *Canzoni_amico,int *sol,  int numamici);//funzione che si occupa di liberare la memoria allocata per la struttura dati
int *inizializzavettoresoluzione(int *sol, int numamici);


int main() {
    int numamici, num_playlist = 0, *soluzione; //count = 0, numero di soluzioni iniziali
    sAmico *Amici;
    sCanzoni *Canzoni_amico;
    FILE* fin= aperturafilelettura();

    numamici = letturaEallocazione(fin,&Amici, &Canzoni_amico);
    soluzione = inizializzavettoresoluzione(soluzione, numamici);
    num_playlist = CombinazioniSemplici(0, Amici, Canzoni_amico, soluzione, numamici, num_playlist);
    printf("\nHo trovato %d playlist possibili", num_playlist);
    FreeStruttureDati(Amici,Canzoni_amico,soluzione, numamici);

    return 0;
}


FILE* aperturafilelettura(){
    char nome_file[MAXL] , *tmp;
    printf("\nInserisci nome file da aprire: ");
    scanf(" %s", nome_file);
    FILE* fin = fopen(nome_file, "r");
    if(fin==NULL){
        printf("\nerrore nell apertura del file");
        return NULL;
    }

    return fin;
}

int letturaEallocazione(FILE* fin, sAmico **Amici, sCanzoni **Canzoni_amico){
    char temp[MAXL];
    sAmico *tempAmici;
    sCanzoni *tempCanzoni_amico;
    int num_amici, conta_canzoni = 0;
    int i = 0; //in int num_canzoni_amico conservo il numero di canzoni per amico
    // che indica il numero di puntatori contenuti per riga, lo conservo per poi successivamente deallocare la matrice

    fscanf(fin," %d", &num_amici);

    tempAmici =(sAmico*) malloc(num_amici * sizeof(sAmico));//Amici è un vettore di struct contenente il numero di canzoni per l'i-esimo amico e la lista di canzoni
    tempCanzoni_amico =  (sCanzoni*) malloc(num_amici * sizeof(sCanzoni));

    while(!feof(fin)){

        fscanf(fin," %d", &tempAmici[i].num_canzoni_scelte);
        tempAmici[i].enum_canzoni =(int*) malloc(tempAmici[i].num_canzoni_scelte * sizeof(int));
        tempCanzoni_amico[i].canzoni = (char**) malloc(tempAmici[i].num_canzoni_scelte * sizeof(char*));
        for (int j = 0; j < tempAmici[i].num_canzoni_scelte; j++) {
            fscanf(fin,"%s", temp);
            tempCanzoni_amico[i].canzoni[j] = strdup(temp); //alloco in maniera dinamica le stringhe
            tempAmici[i].enum_canzoni[j] =  j; //enumerazione dei brani
        }
        i++;
    }
    *Amici = tempAmici;
    *Canzoni_amico = tempCanzoni_amico;
    fclose(fin);
    return num_amici;
}
int *inizializzavettoresoluzione(int *sol, int numamici){
    sol = (int*) malloc(numamici*sizeof (int));
    for (int i = 0; i < numamici; ++i) {
        sol[i] = i;
    }
    return sol;
}

int CombinazioniSemplici(int pos, sAmico *Amici, sCanzoni *Canzoni_amico, int *sol, int numamici, int count){
    int i;
    if(pos >= numamici){
        printf("\nPlaylist #%d:\n", count+1);
        for(i = 0; i < numamici; i++){
            printf("\t%s", Canzoni_amico[i].canzoni[sol[i]]);
        }
        return count+1;
    }

    for(i = 0; i < Amici[pos].num_canzoni_scelte; i++){
        sol[pos] = Amici[pos].enum_canzoni[i];
        count = CombinazioniSemplici(pos+1, Amici, Canzoni_amico, sol, numamici, count);
    }
    return count;
}

void FreeStruttureDati(sAmico *Amici,sCanzoni *Canzoni_amico, int *sol, int numamici){
    for (int i = 0; i < numamici; i++){
        for (int j = 0; j < Amici[i].num_canzoni_scelte; ++j) {
            free(Canzoni_amico[i].canzoni[j]);
            //dealloco i puntatori alle stringhe
        }
        free(Canzoni_amico[i].canzoni); //dealloco il puntatore alla lista di canzoni
        free(Amici[i].enum_canzoni); //dealloco il puntatore dove ho enumerato le canzoni disponibili

    }
    free(Canzoni_amico);
    free(Amici);
    free(sol);
}