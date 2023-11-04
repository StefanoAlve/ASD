#include <stdio.h>
#include <stdlib.h>
#define lmax 255
#define canzoni_max 5
typedef struct{
    char titolo[lmax];
}s_canzone;
typedef struct {
    int num_canzoni;
    s_canzone canzoni[canzoni_max]
}s_amico;
void leggi_File(s_amico **amico,int *n_amici);
void crea_playlist(s_amico *amico, int n_amici, s_canzone *playlist,int amico_scelto, int playlist_scelta);

int main() {
    int n_amici;
    s_amico *amico;
    leggi_File(&amico,&n_amici);
    s_canzone *playlist_scelta  = (s_canzone*) malloc(n_amici*sizeof(s_canzone));
    crea_playlist(amico,n_amici,playlist_scelta,0,0);
    //liberola struct amico e la playlist
    free(amico);
    free(playlist_scelta);
}
void leggi_File(s_amico **amico,int *n_amici){
    FILE *fin;
    int j;
    //lettura del file e controllo
    if((fin = fopen("brani.txt","r"))==NULL){
        printf("errore di apertura!");
        exit(-1);
    }
    fscanf(fin,"%d",n_amici);

    *amico = (s_amico *) malloc((*n_amici) * sizeof(s_amico));
    for (int i = 0;i < *n_amici;i++){
        fscanf(fin,"%d",&(*amico)[i].num_canzoni);
        printf("%d",(*amico)[i].num_canzoni);
        for( j =0;j < (*amico)[i].num_canzoni;j++)
            fscanf(fin,"%s",(*amico)[i].canzoni[j].titolo);
    }
    fclose(fin);
}
void crea_playlist(s_amico *amico, int n_amici, s_canzone *playlist,int amico_scelto, int playlist_scelta){
    // dopo aver scelto una sola canzone a testa, creo la playlist
    if(amico_scelto==n_amici){
        printf("La playlist e':");
        for(int i = 0;i<n_amici;i++){
            printf("%s\n",playlist[i].titolo);
        }
        printf("\n");

    }
    // funzione ricorsiva per ogni canzone
    for (int k = 0;k<amico[amico_scelto].num_canzoni;k++){
        playlist[playlist_scelta] = amico[amico_scelto].canzoni[k];
        crea_playlist(amico,n_amici,playlist,amico_scelto+1,playlist_scelta+1);
    }
}
