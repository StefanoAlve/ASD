#include <stdio.h>
#include <stdlib.h>
#define file_name "easy_test_set.txt"
#define num_pietre_distinte 4
typedef struct{
    int z;
    int r;
    int t;
    int s;
    int maxl;
}pietre;

void leggi_file(pietre* *collane, int* nTest);
void stampa_collane(pietre *collane, int nCollane);
void inizializza_mark(int* mark, pietre collana);
int disp_rip(char *val, char* sol, int mark[4], int n_pietre_tot, int n_dist, int k, int pos, int flag, int start);
int isValid(char *sol, int k, int pos);

int main(void)
{
    int nTest, k, n, n_dist = num_pietre_distinte, fine = 0, i, mark[num_pietre_distinte], start = 0;
    char *sol, val[4];
    pietre *collane;
    leggi_file(&collane, &nTest);
    printf("Il file contiene i seguenti %d test da effettuare:\n\n", nTest);
    stampa_collane(collane, nTest);
    val[0] = 'z'; val[1] = 'r'; val[2] = 't'; val[3] = 's';
    for (i = 0; i < nTest; i++)
    {
        fine = 0;
        printf("TEST#%d:", i+1);
        n = k = collane[i].maxl;  // il numero n di pietre totali inizialmente è uguale a k (posso disporle in k modi diversi)
        inizializza_mark(mark, collane[i]);   //mark conterrà quante volte, al massimo, posso usare le determinate pietre dell'i-esima collana
        printf("\n");
        while(!fine)
        {
            sol = (char *)malloc(k * sizeof(char));
            fine = disp_rip(val, sol, mark, n, n_dist, k, 0, 0, start);
            if(fine)
                printf("Sono stati usati %d zaffiri, %d rubini, %d topazi, %d smeraldi\n\n", mark[0], mark[1], mark[2], mark[3]);
            k--;
            free(sol);
        }

    }
    return 0;
}


void leggi_file(pietre* *collane, int* nTest)
{
    FILE* fp_in = fopen(file_name, "r");
    pietre *tmp = NULL;
    int i = 0;
    if(fp_in != NULL)
    {
        fscanf(fp_in, "%d",  nTest);
        tmp = (pietre *)malloc(*nTest * sizeof(pietre));
        while(fscanf(fp_in, " %d %d %d %d", &tmp[i].z, &tmp[i].r, &tmp[i].t, &tmp[i].s) == 4)
        {
            tmp[i].maxl = tmp[i].z+tmp[i].r+tmp[i].t+tmp[i].s;
            i++;
        }
    }
    else
        printf("Errore nell'apertura del file di input.\n");
    fclose(fp_in);
    *collane = tmp;
}

void stampa_collane(pietre *collane, int nCollane)
{
    int i;
    for (i = 0; i < nCollane; i++){
        printf("TEST #%d: %d zaffiri, %d rubini, %d topazi, %d smeraldi\nNumero pietre totali:%d\n", i+1, collane[i].z, collane[i].r, collane[i].t, collane[i].s, collane[i].maxl);
    }
}


int disp_rip(char *val, char* sol, int mark[4], int n_pietre_tot, int n_dist, int k, int pos, int flag, int start)
{
    int i;
    if(pos >= k)
    {
        printf("\nLa collana che originariamente disponeva di %d pietre, puo' essere riempita con %d pietre:\n",n_pietre_tot, k);

        for(i = 0; i < k; i++)
        {
            printf("%c", sol[i]);
        }
        printf("\n");
        flag = 1;
        return flag; // cont sarà uguale a 1; significa che ne ho trovata 1
    }
    for(i = start; i < n_dist && !flag; i++) // i partità dallo start (lo start indica che pietra prendere prima)
    {
        if(mark[i]>0)
        {
            mark[i]--;
            sol[pos] = val[i];
            if (isValid(sol, k, pos)) // se la configurazione della soluzione (fino all'indice pos) è valida allora ricorro, altrimenti passo alla pietra successiva
            {
                flag = disp_rip(val, sol, mark, n_pietre_tot, n_dist, k, pos + 1, flag, 0);
            }
            mark[i]++;
        }
        if (flag) // è inutile continuare a ricorrere perchè ho trovato una configurazione valida
            return flag;
    }
    return flag;
}

int isValid(char *sol, int k, int pos)
{
    int valid = 0;
    char c_pietra, p_pietra;
    if (pos == 0) // se è il primo elemento è valida qualsiasi sia la pietra
        valid =1;
    else if(pos>0 && pos < k) /// se invece non è il primo elemento della soluzione confronto con il precedente e verifico validità:
    {
        c_pietra = sol[pos];
        p_pietra = sol[pos - 1];
        if(c_pietra == 'z' && (p_pietra == 'z' || p_pietra == 't'))
            valid = 1;
        else if(c_pietra == 's' && (p_pietra == 's' || p_pietra == 'r'))
            valid = 1;
        else if(c_pietra == 'r' && (p_pietra == 'z' || p_pietra == 't'))
            valid = 1;
        else if(c_pietra == 't' && (p_pietra == 'r' || p_pietra == 's'))
            valid = 1;
        else
            valid = 0;
    }
    return valid;
}

void inizializza_mark(int* mark, pietre collana){
    mark[0] = collana.z;
    mark[1] = collana.r;
    mark[2] = collana.t;
    mark[3] = collana.s;
}