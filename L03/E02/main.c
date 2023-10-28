#include <stdio.h>
#include <stdlib.h>
#define inFIle "brani.txt"
#define MAXCANZONI 5
#define MAXTITOLI 255

//Struct per singola canzone
typedef struct{
    char titolo[MAXTITOLI];
}canzone;

//Struct per ogni persona
typedef struct{
    int numCanzoni;
    canzone canzoni[MAXCANZONI];
}amico;

void leggiFile(amico **amici, int *nAmici);
void generaPlaylist(amico *amici, int nAmici, canzone *playlist, int amicoCorrente, int playlistCorrente);

int main(){
    int nAmici;
    amico *amici;

    //Leggo file
    leggiFile(&amici, &nAmici);

    //Allocazione di un puntatore a struct
    canzone *playlistCorrente = (canzone *)malloc(sizeof(canzone) * nAmici);
    if(playlistCorrente == NULL){
        printf("ERRORE DI ALLOCAZIONE DI MEMORIA\n");
        exit(3);
    }
    //Funzione ricorsiva
    generaPlaylist(amici,nAmici, playlistCorrente, 0, 0);

    //Libero memoria e chiudo il file
    free(amici);
    free(playlistCorrente);
    return 0;
}

//Legge file di testo e ritorna ad amici il contenuto
void leggiFile(amico **amici, int *nAmici){
    FILE *fin;

    //Gestione errore file
    if((fin = fopen(inFIle, "r")) == NULL){
        printf("ERRORE APERTURA FILE %s\n", inFIle);
        exit(1);
    }

    //Prendo il numero di amici
    fscanf(fin, "%d ", nAmici);

    //Allocazione memoria per struct
    *amici = (amico *)malloc(sizeof(amico) * (*nAmici));
    if(*amici == NULL){
        printf("Errore di allocazione della memoria.\n");
        exit(2);
    }

    //Lettura dei file del numero di canzoni scelte per amico
    for(int i = 0; i < *nAmici; i++){
        fscanf(fin, "%d ", &(*amici)[i].numCanzoni);

        //Lettura dei file del titolo delle canzoni scelte da ogni amico
        for(int j = 0; j < (*amici)[i].numCanzoni; j++)
            fscanf(fin, "%s", (*amici)[i].canzoni[j].titolo);
    }
    fclose(fin);
}

//Funzione ricorsiva che cerca una playlist, e la stampa per ogni combinazione
void generaPlaylist(amico *amici, int nAmici, canzone *playlist, int amicoCorrente, int playlistCorrente){

    //Hanno scelto una canzone per ciascun amico, stampiamo la playlist
    if(amicoCorrente == nAmici){
        printf("Playlist: ");
        for (int j = 0; j < nAmici; j++) {
            printf("%s ", playlist[j].titolo);
        }
        printf("\n");
        return;
    }

    //Per ogni canzone viene richiamata la funzione stessa
    for(int i = 0; i < amici[amicoCorrente].numCanzoni; i++){
        playlist[playlistCorrente] = amici[amicoCorrente].canzoni[i];
        generaPlaylist(amici, nAmici, playlist, amicoCorrente + 1, playlistCorrente + 1);
    }
}
