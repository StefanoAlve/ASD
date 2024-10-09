#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 255

typedef struct{
    char *s1;
    char *s2;
    char *s3;
    char *s4;
    char *s5;
}songs;

int LeggiFile(FILE *fp, songs **vp_songs);

int main(){
    FILE *fp = fopen("brani.txt", "r");
    songs **vp_songs;
    int n_amici;

    n_amici = LeggiFile(fp, vp_songs);



    return 0;
}

int LeggiFile(FILE *fp, songs **vp_songs){
    int na;
    char song[MAXN];
    fscanf(fp, "%d", &na);
    vp_songs = malloc(na*sizeof(songs *));
    for (int i = 0; i < na; i++){
        int nc;
        vp_songs[i] = malloc(sizeof *vp_songs[i]);
        fscanf(fp, "%d", &nc);
        for (int j = 0; j < nc; j++){
            fscanf(fp, "%s", song);
            vp_songs[i]->s1 = strdup(song);

        }
    }















}