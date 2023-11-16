#include <stdio.h>
#include <stdlib.h>
#define MAXL 50
typedef struct {
    int inizio;
    int fine;
}att;

void attSel(int N, att *v);
int attSelR(int d,int N, att *v, int max, int *index, int *tmp, int l, int pos);
int leggiFile(att **v, int nr);

int main() {
    att *v;
    int nr=0, i;

    nr = leggiFile(&v, nr);

    /*for(i=0; i<nr; i++){
        printf("%d %d\n", v[i].inizio, v[i].fine);
    }*/

    attSel(nr, v);


    free(v);
    return 0;
}

int leggiFile(att **v, int nr) {
    FILE *fp;
    char nomeFile[MAXL];
    int i;

    printf("inserire il nome del file: \n");
    scanf("%s", nomeFile);

    if((fp = fopen(nomeFile, "r")) == NULL){
        printf("errore in apertura del file");
        exit(1);
    }
    fscanf(fp, "%d", &nr);

    *v = malloc(nr*sizeof(att));

    for (i=0; i<nr; i++){
        fscanf(fp, "%d %d", &(*v)[i].inizio, &(*v)[i].fine);
    }

    fclose(fp);
    return nr;
}

///WRAPPER DELLA FUNZIONE DI SELEZIONE
void attSel(int N, att *v){
    int index[N], tmp[N], i, max;

    for (i=0; i<N; i++){
        index[i] = -1;
        tmp[i] = -1;
    }

    max = attSelR(0, N, v, 0, index, tmp, 0, 0);

    printf("%d\n", max);

    for (i=0; index[i] != -1; i++){
        printf("%d %d, ", v[index[i]].inizio, v[index[i]].fine);
    }

}
///FUNZIONE DI SELEZIONE RICORSIVA
int attSelR(int d, int N, att *v, int max, int *index, int *tmp, int l, int pos){
    int i;

    for(i=l; i<=N; i++){
        ///CONDIZIONE DI FINE
        if(i==N) {
            if (d >= max) {
                max = d;
                for (i = 0; i < N; i++) {
                    index[i] = tmp[i];
                }
            }
            return max;
        }

        if(pos==0 || v[i].inizio >= v[tmp[pos-1]].fine) {
            tmp[pos] = i;
            d = d + (v[i].fine - v[i].inizio);

            max = attSelR(d, N, v, max, index, tmp, i+1, pos+1);

            d = d - (v[i].fine - v[i].inizio);
            tmp[pos] = -1;
        }
    }

    return max;
}