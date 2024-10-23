#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void CercaCollana(int *val, int n);
int CalcolaCollana(int pos, int *val, int *sol, int *fin, int l, int start);

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
    free(pietre);

    return 0;
}

void CercaCollana(int *val, int n){
    int maxl = 0, l = 0, start = 0;
    for (int q = 0; q < n; q++) maxl += val[q];
    int *sol = malloc(maxl*sizeof (int));
    int *fin = malloc(maxl*sizeof (int));

    for (int k = 0; k < maxl; k++)
        fin[k] = -1;

    for (int h = 0; h < n; h++){
        l = CalcolaCollana(h, val, sol, fin, l, start);

        printf("\nLa collana a lunghezza massima e' lunga %d\n", l);
        l = 0; start = 0;
    }

    int i;
    for (i = 0; fin[i] != -1; i++){
        if (fin[i] == 0) printf("%c ", 'z');
        else if (fin[i] == 1) printf("%c ", 'r');
        else if (fin[i] == 2) printf("%c ", 't');
        else if (fin[i] == 3) printf("%c ", 's');
    }
    printf("\nLa collana a lunghezza massima e' lunga %d", i-1);

    free(sol);
    free(fin);

}

int CalcolaCollana(int pos, int *val, int *sol, int *fin, int l, int start){
    int l1, l2;

    if (val[pos] > 0){
        sol[start] = pos;
        val[pos]--;
        l++;

        if (pos == 0){
            l1 = CalcolaCollana(pos, val, sol, fin, l, start+1);
            l2 = CalcolaCollana(pos+1, val, sol, fin, l, start+1);
        } else if (pos == 1){
            l1 = CalcolaCollana(pos+1, val, sol, fin,  l, start+1);
            l2 = CalcolaCollana(pos+2, val, sol, fin, l, start+1);
        } else if (pos == 2){
            l1 = CalcolaCollana(pos-1, val, sol, fin, l, start+1);
            l2 = CalcolaCollana(pos-2, val, sol, fin, l, start+1);
        } else {
            l1 = CalcolaCollana(pos, val, sol, fin, l, start+1);
            l2 = CalcolaCollana(pos-1, val, sol, fin, l, start+1);
        }

        val[pos]++;
        if (l1 == 0 && l2 == 0){
            int i;
            for (i = 0; fin[i] != -1; i++);
            printf("%d\n",i);
            if (l > i)
                for (int j = 0; j < l; j++)
                    fin[j] = sol[j];
            return l;
        }
        else if (l1 > l2)
            return l1;
        return l2;
    }
    return 0;

}