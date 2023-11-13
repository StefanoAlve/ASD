#include <stdio.h>
#include <stdlib.h>
#define file_name "test_set.txt"
#define num_pietre_distinte 4
typedef struct{
    int z;
    int val_z;
    int r;
    int val_r;
    int t;
    int val_t;
    int s;
    int val_s;
    int max_rip;
    int maxl;
}pietre;

void leggi_file(pietre* *collane, int* nTest);
void stampa_collane(pietre *collane, int nCollane);
void inizializza_mark(int* mark, pietre collana);
int disp_rip(char *val, char* sol, int mark[4], int n_pietre_tot, int n_dist, int k, int pos, int flag, int start, int max_rip);
int disp_rip_mod(pietre collana, char *val, char* sol, int mark[4], int n_pietre_tot, int n_dist, int k, int pos, int max_rip, int start, int max_val, char *soluzione_max);
int isValid(char *sol, int k, int pos, int max_rip);
int trova_val(char *sol, int k,pietre collana);
int pietre_valide(int *mark);
int riduci_pietre_non_valide(int *mark, int* k);
int where_to_start(int *mark);

int main(void)
{
    int nTest, k, n, n_dist = num_pietre_distinte, fine = 0, i, mark[num_pietre_distinte], start = 0, max_val;
    char *sol, *soluzione_max, val[4];
    pietre *collane;
    leggi_file(&collane, &nTest);
    printf("Il file contiene i seguenti %d test da effettuare:\n\n", nTest);
    stampa_collane(collane, nTest);
    val[0] = 'z'; val[1] = 'r'; val[2] = 't'; val[3] = 's';
    for (i = 0; i < nTest; i++)
    {
        fine = 0;
        max_val = 0;
        printf("TEST#%d:\n%d zaffiri[%d], %d rubini[%d], %d topazi[%d], %d smeraldi[%d]; numero pietre totali:%d; MAX_RIP: %d", i+1, collane[i].z, collane[i].val_z, collane[i].r, collane[i].val_r, collane[i].t, collane[i].val_t, collane[i].s, collane[i].val_s, collane[i].maxl, collane[i].max_rip);
        n = k = collane[i].maxl;  // il numero n di pietre totali inizialmente è uguale a k (posso disporle in k modi diversi)
        inizializza_mark(mark, collane[i]);   //mark conterrà quante volte, al massimo, posso usare le determinate pietre dell'i-esima collana
        while(!fine)
        {
            sol = (char *)malloc(k * sizeof(char) + sizeof(char));
            if (pietre_valide(mark))
            {
                start = where_to_start(mark);
                fine = disp_rip(val, sol, mark, n, n_dist, k, 0, 0, start, collane[i].max_rip);
                if (fine) {
                    if (pietre_valide(mark)) {
                        soluzione_max = (char *) malloc(k * sizeof(char) + sizeof(char));
                        max_val = disp_rip_mod(collane[i], val, sol, mark, n, n_dist, k, 0, start, collane[i].max_rip, max_val,
                                               soluzione_max);
                        printf("Composizione collana ottimale: %s\nValore massimo %d.\n", soluzione_max, max_val);
                        free(soluzione_max);
                    }
                }
                k--;
            }
            else
                riduci_pietre_non_valide(mark, &k);
            free(sol);
        }
        printf("\n");
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
        while(fscanf(fp_in, " %d %d %d %d %d %d %d %d %d", &tmp[i].z, &tmp[i].r, &tmp[i].t, &tmp[i].s, &tmp[i].val_z, &tmp[i].val_r, &tmp[i].val_t, &tmp[i].val_s, &tmp[i].max_rip) == 9)
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


int disp_rip(char *val, char* sol, int mark[4], int n_pietre_tot, int n_dist, int k, int pos, int flag, int start, int max_rip)
{
    int i;
    if(pos >= k)
    {
        printf("\nLa collana che originariamente disponeva di %d pietre, puo' essere riempita con %d pietre:\n",n_pietre_tot, k);
        flag = 1;
        return flag; // cont sarà uguale a 1; significa che ne ho trovata 1
    }
    for(i = start; i < n_dist && !flag; i++) // i partità dallo start (lo start indica che pietra prendere prima)
    {
        if(mark[i]>0)
        {
            mark[i]--;
            sol[pos] = val[i];
            if (isValid(sol, k, pos, max_rip)) // se la configurazione della soluzione (fino all'indice pos) è valida allora ricorro, altrimenti passo alla pietra successiva
            {
                flag = disp_rip(val, sol, mark, n_pietre_tot, n_dist, k, pos + 1, flag,0, max_rip);
            }
            mark[i]++;
        }
        if (flag) // è inutile continuare a ricorrere perchè ho trovato una configurazione valida
            return flag;
    }
    return flag;
}

int isValid(char *sol, int k, int pos, int max_rip)
{
    int valid = 0, equals = 0, i = pos;
    char c_pietra, p_pietra;
    if (pos == 0) // se è il primo elemento è valida qualsiasi sia la pietra
        valid =1;
    else
    {
        c_pietra = sol[pos];
        p_pietra = sol[pos-1];
        if (c_pietra == 'z') {
            if (p_pietra == 't')
                valid = 1;
            else if (p_pietra == 'z')
            {
                while (c_pietra == sol[i] && i >= 0)
                {
                    equals++;
                    i--;
                }
                if (equals <= max_rip)
                    valid = 1;
            }
        }
        else if (c_pietra == 's') {
            if (p_pietra == 'r')
                valid = 1;
            else if (p_pietra == 's' )
            {
                while (c_pietra == sol[i] && i >= 0)
                {
                    equals++;
                    i--;
                }
                if (equals <=max_rip)
                    valid = 1;
            }
        }
        else if (c_pietra == 'r' && (p_pietra == 'z' || p_pietra == 't'))
            valid = 1;
        else if (c_pietra == 't' && (p_pietra == 'r' || p_pietra == 's'))
            valid = 1;
        else
            valid = 0;
    }
    return valid;
}

void inizializza_mark(int* mark, pietre collana){
    if (collana.z>collana.s)
        collana.z = collana.s;
    mark[0] = collana.z;
    mark[1] = collana.r;
    mark[2] = collana.t;
    mark[3] = collana.s;
}

int disp_rip_mod(pietre collana, char *val, char* sol, int mark[4], int n_pietre_tot, int n_dist, int k, int pos, int start, int max_rip, int max_val, char *soluzione_max)
{
    int i, actual_val;
    if(pos >= k)
    {
        actual_val = trova_val(sol, k, collana);
        if(max_val < actual_val)
        {
            for(i = 0; i< k; i++) // copio la soluzione nella soluzione massima
                soluzione_max[i] = sol[i];
            soluzione_max[pos] = '\0';
            max_val = actual_val;
        }
        return max_val; // cont sarà uguale a 1; significa che ne ho trovata 1
    }
    for(i = 0; i < n_dist; i++) // i partità dallo start (lo start indica che pietra prendere prima)
    {
        if(mark[i]>0)
        {
            mark[i]--;
            sol[pos] = val[i];
            if (isValid(sol, k, pos, max_rip)) // se la configurazione della soluzione (fino all'indice pos) è valida allora ricorro, altrimenti passo alla pietra successiva
            {
                max_val = disp_rip_mod(collana, val, sol, mark, n_pietre_tot, n_dist, k, pos + 1,start, max_rip, max_val, soluzione_max);
            }
            mark[i]++;
        }
    }
    return max_val;
}


int trova_val(char *sol, int k,pietre collana)
{
    int z, r,t,s, i, val;
    z = r=t=s = 0;
    for (i = 0; i < k; i++)
    {
        if(sol[i] == 'z')
            z++;
        else if(sol[i] == 'r')
            r++;
        else if(sol[i] == 't')
            t++;
        else if(sol[i] == 's')
            s++;
    }
    val = z*collana.val_z+r*collana.val_r+t*collana.val_t+s*collana.val_s;
    return val;
}

int pietre_valide(int *mark)
{
    /// Una collana, per essere valida deve avere al massimo un numero di rubini che differiscono dal numero di topazi di 1
    int valido = 0;
    int r,t;
    r = mark[1]; t = mark[2];
    if (t <= 1+r && r <= t+1)
        valido = 1;
    return valido;
}


int riduci_pietre_non_valide(int *mark, int* k)
{
    /// Forzo una collana valida in modo che, se il numero di rubini supera il numero di topazi di più di uno, allora elimino i rubini in eccesso
    /// se invece il numero di topazi eccede di troppo (più di 1) il numero di rubini, elimino i topazi in eccesso
    int r,t;
    r = mark[1]; t = mark[2];
    if (r > t+1)
        r = t+1;
    if (t > 1+r)
        t = r+1;
    mark[1] = r; mark[2] = t; // aggiorno mark con le pietre che utilizzerò effettivamente
    *k = r+t+mark[0]+mark[3]; // aggirono il numero totale di pietre che utilizzerò
    return 0;
}

int where_to_start(int *mark)
{
    /// Se il numero di rubini è minore del numero di topazi, allora di sicuro la sequenza inizierà con t(topazio) e continuerà con z
    int start;
    if(mark[1]<mark[2])
        start = 2;
    else
        start = 0;
    return start;
}