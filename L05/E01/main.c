#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int start;
    int fine;
}att;

att* leggi_file(int* n_attivita);
void attSel(int N, att *v);
int comb_semplici_mod(att *v, att*sol, int pos, int n, int k, int start, int max_lenght, att* solMAX);
int calcola_lunghezza(att* v, int num_att);
int calcola_durata(att attivita);
int check_intersezioni(att *v, int num_att);

int main (void)
{
    int n_attivita = 0;
    att *v;
    v = leggi_file(&n_attivita);
    attSel(n_attivita, v);
    free(v);
}


att* leggi_file(int* n_attivita)
{
    char file_name[64];
    att *v;
    FILE* fp_in = NULL;
    int n, i = 0, start, fine;
    printf("Inserire il nome del file di input:");
    scanf("%s", file_name);
    fp_in = fopen(file_name, "r");
    if (fp_in != NULL)
    {
        fscanf(fp_in, "%d", &n);
        printf("Il file %s contiene %d attivita':", file_name, n);
        *n_attivita = n;
        v = (att *)malloc(n * sizeof(att));
        while(fscanf(fp_in, "%d %d", &start, &fine) == 2 && i < n)
        {
            printf("\nATT #%d: (%d, %d)", i+1, start, fine);
            v[i].start = start;
            v[i].fine = fine;
            i++;
        }
    }
    else {
        printf("\nErrore nell'apertura del file");
        exit(-1);
    }
    fclose(fp_in);
    return v;
}



void attSel(int N, att *v)
{
    int k = N, flag = 0, lenght = 0, max_lenght = 0, i;
    att *sol, *solMAX;
    solMAX = (att*)malloc(k*sizeof(att));
    // in realtà è il wrapper di un powerset usando le combinazioni semplici
    while(k >= 1)
    {
        sol = calloc(k, sizeof(att));
        printf("\nPartizioni in %d blocchi:\n", k);
        lenght = comb_semplici_mod(v, sol, 0, N, k, 0, max_lenght, solMAX);
        printf("\n");
        if(lenght> max_lenght)
        {
            max_lenght = lenght;
            flag = k;
        }
        k--;
        free(sol);
    }
    printf("\n%d attivita compatibili che massimizzano la somma delle durate trovate:\n{ ", flag);
    for (i = 0; i < flag; i++)
        printf("(%d, %d) ", solMAX[i].start, solMAX[i].fine);
    printf("}\n");
    printf("Durata complessiva: %d\n", max_lenght);
    free(solMAX);

}


int comb_semplici_mod(att *v, att*sol, int pos, int n, int k, int start, int max_lenght, att *solMAX)
{
    int lenght = 0, i;
    if(pos >= k)
    {
        printf("\n{ ");
        for(i = 0; i < pos; i++)
        {
            printf("(%d, %d) ", sol[i].start, sol[i].fine);
        }
        printf("}");
        if(!check_intersezioni(sol,k))
        {
            lenght = calcola_lunghezza(sol, k);
            if (lenght >= max_lenght)
            {
                max_lenght = lenght;
                for(i = 0; i < k; i++)
                    solMAX[i] = sol[i];
            }
        }
        return max_lenght;
    }
    for(i = start; i < n; i++)
    {
        sol[pos] = v[i];
        // pruning
        if(!check_intersezioni(sol, pos+1)){ //passo pos+1 perchè ci sono pos+1 attività nella soluzione
            max_lenght = comb_semplici_mod(v, sol, pos + 1, n, k, i + 1, max_lenght, solMAX);
        }
    }

    return max_lenght;
}


int calcola_durata(att attivita)
{
    int durata;
    durata = attivita.fine-attivita.start;
    return durata;
}

int check_intersezioni(att *v, int num_att)
{
    int flag = 0, i;
    att p, c;
    if (num_att > 0)
        for(i = 1; i < num_att && !flag; i++)
        {
            c = v[i];
            p = v[i-1];
            if ((c.start >= p.start && c.start < p.fine) || (p.fine > c.start && p.fine < c.fine) || (c.start == p.start && p.fine == c.fine))      // se l'inizio dell'attività corrente è compresa nell'attività precedente allora si sovrappongono
                flag = 1;
        }
    return flag;
}


int calcola_lunghezza(att* v, int num_att)
{
    int i, lenght = 0;
    for(i = 0; i < num_att; i++){
        lenght+= calcola_durata(v[i]);
    }
    return lenght;
}

