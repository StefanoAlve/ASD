#include <stdio.h>
#include <stdlib.h>
#define file_name "easy_test_set.txt"
#define num_pietre_distinte 4

typedef struct{
    int z;
    int s;
    int r;
    int t;
    int len_max;
} pietre;


void leggi_file(int *num_collane, pietre **collane);
void stampa_test(pietre collana, int i);
void riempi_mark(int *mark, pietre collana);
int disp_rip(int pos, char *val, char *sol, int *mark, int n_dist, int n, int k, int flag, int start);
int verifica_valori(int pos,int k, char sol, char val);

int main(){
    pietre *collane;
    int num_collane, mark[num_pietre_distinte], n_dist = num_pietre_distinte, fine = 0, n, k ;
    char *val = (char*) malloc(sizeof(char)*num_pietre_distinte), *sol;
    val [0] = 'z'; val [1] = 's'; val[2] = 'r'; val[3] = 't';

    leggi_file(&num_collane, &collane);//acquisizione dei dati su cui operare

    for (int i = 0; i < num_collane; ++i) {

        stampa_test(collane[i], i+1);
        n = k = collane[i].len_max;
        fine = 0;
        riempi_mark(mark, collane[i]);

        while(!fine) {
            sol = (char*) malloc(sizeof(char) * k);

            fine  = disp_rip(0, val, sol, mark, n_dist, n, k, fine, 0);
            if(fine){
                printf("\nfine");
            }
            k--;
            free(sol);
        }
    }

    free(collane);
    free(val);

}



int disp_rip(int pos, char *val, char *sol, int *mark, int n_dist, int n, int k, int flag, int start){

    if(pos >= k){
        printf("\n");
        printf("\nCon le %d pietre a disposizione, la collana puo' essere riempita con %d pietre:\n",n, k);

        for (int i = 0; i < k; ++i) {
            printf("%c", sol[i]);
        }
        printf("\n");
        flag = 1;
        return flag;
    }

    for (int i = 0; i < n_dist && !flag; ++i) {
        if(mark[i] > 0 ) {
            mark[i]--;

            if (verifica_valori(pos, k, sol[pos - 1], val[i])){
                sol[pos] = val[i];
                flag = disp_rip(pos + 1, val, sol, mark, n_dist, n, k, flag, 0);
            }

            mark[i]++;
        }
        if(flag){
            return flag;
        }
    }
    return flag;
}

int verifica_valori(int pos, int k, char sol, char val) {

    if (pos == 0) {
        return 1;
    } else if(pos>0 && pos < k) {
        if (sol == 'z' && (val == 'z' || val == 'r')) {
            return 1;
        } else if (sol == 's' && (val == 's' || val == 't')) {
            return 1;
        } else if (sol == 'r' && (val == 's' || val == 't')) {
            return 1;
        } else if (sol == 't' && (val == 'z' || val == 'r')) {
            return 1;
        } else {
            return 0;
        }
    }
    else{
        return 0;
    }

}




void leggi_file(int *num_collane, pietre **collane){ //leggo dal file le i dati e li alloco nella struct collane
    FILE *fin = fopen(file_name, "r");
    if(fin == NULL){
        printf("\nNon è stato possibile aprire il file");
        return;
    }
    fscanf(fin, "%d ", num_collane);

    pietre *collane_temp = (pietre*) malloc(*num_collane * sizeof(pietre));
    int i = 0;

    while(i < *num_collane){ //leggo dal file in input tutte le varie possibili per creare collane
        fscanf(fin, "%d %d %d %d", &collane_temp[i].z , &collane_temp[i].s, &collane_temp[i].r, &collane_temp[i].t );
        collane_temp[i].len_max = collane_temp[i].z + collane_temp[i].s + collane_temp[i].r + collane_temp[i].t;
        i++;
    }
    *collane = collane_temp;
    fclose(fin);

}


void stampa_test(pietre collana, int i){
    printf("\n TEST #%d:\nzaffiro = %d, smeraldo = %d, rubino = %d, topazio = %d, TOT = %d ", i, collana.z, collana.s, collana.r, collana.t, collana.len_max);
    return;
}

void riempi_mark(int *mark, pietre collana){
    mark[0] = collana.z;
    mark[1] = collana.s;
    mark[2] = collana.r;
    mark[3] = collana.t;

}