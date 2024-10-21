#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void CercaCollana(int *val, int n);
int CalcolaCollana(int pos, int *val, int *sol, int maxl, int n, int l);

int main(){

    int n = 4;
    int *pietre = malloc(n*sizeof (int));
    if (pietre == NULL) exit(1);

    printf("Inserire il numero delle pietre preziose uno sotto l'altro:\n");
    printf("<zaffiri> <rubini> <topazi> <smeraldi>\n");
    for (int i = 0; i < n; i++){
        scanf("%d", &pietre[i]);
    }

    CercaCollana(pietre, n);

    return 0;
}

void CercaCollana(int *val, int n){
    int maxl = 0, pos = 0, l = 0;
    for (int q = 0; q < n; q++) maxl += val[q];
    int *sol = malloc(maxl*sizeof (int));

    l = CalcolaCollana(pos, val, sol, maxl, n, l);
    printf("La collana a lunghezza massima è lunga %d", l);

}

int CalcolaCollana(int pos, int *val, int *sol, int maxl, int n, int l){















    return l;
}