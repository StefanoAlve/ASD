#include <stdio.h>
#include <stdlib.h>

/*
 * Per creare una soluzione ricorsiva che calcoli la durata massima di attività che non si sovrappongano
 * si può usare un algoritmo simile a quello delle LIS, sostanzialmente si ricerca una sequenza di attività
 * che massimizza la durata totale di queste ultime.
 * Se abbiamo una sola attività, allora, la durata massima sarà data da quell'unica attività;
 * Se abbiamo due attività, verifichiamo che le due attività siano compatibili, se lo sono, si fa d1 + d2
 * La durata massima è data dal massimo tra la durata massima trovata in precedenza e quella data da durata max[j] + durata[i].
 * In pratica, se ordiniamo le attività in ordine di fine, possiamo costruire
 * la durata massima fino alla posizione i-esima, con 0=i<n, la quale è data dalla durata massima delle posizioni precedenti all'i-esima + l'i-esima se compatibile
 * quindi dalle j-esime con 0<=j<i;
 * VERIFICA APPLICABILITà (dimostrazione per assurdo)
 * 1) si tratta di un problema di ottimizzzione
 * 2) il problmea gode di una sottostruttura ottima, infatti:
 * SE UNA SEQUENZA è UNA SOLUZIONE OTTIMA, deve essere ottima anche la soluzione per ogni sottoproblema, altrimenti
 * si potrebbero trovare soluzioni migliori per i sottoproblemi e la soluzione della sequenza i-esima non sarebbe più ottima essendo quest'ultima dipendente dalle precedenti (ASSURDO)

 Lo schema per l'implementazione ricorsiva per il calcolo della durata è il seguente:
             { durata della prima attività (nonchè unica) se i = 0
 opt[x_i] = {
             { max(best, durata[j]+opt[X_j]  0<=j<i
 La complessità della soluzione dinamica è data dal numero di sottoproblemi (n) * il costo di ricombinazione O(n) => O(n^2)
 */


typedef struct{
    int s;
    int f;
    int d;
}att;

void MergeSortWrapper(att* attivita, int n_att);
void MergeSort(att* attivita, int l, int r, att *ausiliario);
void Merge(att* attivita, int l, int r, att* ausiliario);
void display_v_att(att* attivita, int n_att);
int LS(att* attivita, int n_att); //longest sequence wrapper
int LSR(att* attivita, int i);
int compatibile(att a1, att a2);
int max(int v1, int v2);
att* leggi_file(int* n_att);
void LSDP(att* attivita, int n_att);
void LSDP_print(att* attivita, int* P, int* D, int n_att, int last);


int main(void)
{
    int n_att;
    att* v_attivita;
    v_attivita = leggi_file(&n_att);
    MergeSortWrapper(v_attivita, n_att);
    printf("\n\nAttivita' ordinate per fine:");
    display_v_att(v_attivita, n_att);
    LS(v_attivita, n_att);
    LSDP(v_attivita, n_att);
    free(v_attivita);
}


att* leggi_file(int* n_att)
{
    FILE *fp = NULL;
    char file_name[50];
    att *v_att = NULL;
    int i = 0;
    printf("Inserisci il nome del file:");
    scanf("%s", file_name);
    fp = fopen(file_name, "r");
    if(fp != NULL)
    {
        fscanf(fp, "%d", n_att);
        v_att = (att*)malloc(*n_att * sizeof(att));
        while(fscanf(fp, "%d %d", &(v_att[i].s), &(v_att[i].f)) == 2 && i < *n_att) {
            v_att[i].d = v_att[i].f - v_att[i].s;
            printf("\nATT #%d: (%d,%d) durata:%d", i+1, v_att[i].s, v_att[i].f, v_att[i].d);
            i++;
        }
    }
    else
        printf("Errore nell'apertura del file di input");
    fclose(fp);
    return v_att;
}

int LS(att* attivita, int n_att)
{ //partiamo dall'ultima attività in modo da calcolare le soluzioni dei sottoproblemi
    int max;
    max = LSR(attivita, n_att-1);
    printf("\nIl massimo calcolato ricorsivamente e' %d\n", max);
    return max;
}


int LSR(att* attivita, int i)
{
    int j, res;
    if(i == 0)
        return attivita[i].d; // di sicuro la durata minima se ho una sola attività è la durata dell'attività stessa
    res = attivita[i].d; // la durata di sicuro è almeno pari alla singola prima attività per ogni caso.
    for(j = 0; j<i; j++)
    {
        if(compatibile(attivita[j], attivita[i])) // se posso concatenare le due attivita'
        {
            res = max(res, attivita[i].d + LSR(attivita, j)); //opt[i] = max...a
        }
        else
            res = max(res, LSR(attivita, j));
    }
    return res;
}


int compatibile(att a1, att a2)
{ // se lo start della seconda è compreso tra lo start della prima e la fine della prima
    if( (a2.s >=a1.s && a2.s < a1.f) || (a1.f>a2.s && a1.f < a2.f) || (a2.s == a1.s && a2.f == a1.f))
        return 0;
    else
        return 1;
}

int max(int v1, int v2){
    if (v1>v2)
        return v1;
    else
        return v2;
}

void LSDP(att* attivita, int n_att)
{
    int max_lenght = 0, last = n_att, i, j;
    int P[n_att], D[n_att]; // vettore delle posizioni, vettore durate
    P[0] = -1; D[0] = attivita[0].d;
    for(i = 1; i < n_att; i++) //inizializzazione dei vettori della durata e delle posizioni
    {
        P[i] = -1;
        D[i] = attivita[i].d;
    }
    for(i = 1; i < n_att; i++)
    {
        for(j = 0; j < i; j++)
        {
            if(compatibile(attivita[j], attivita[i]) && D[i] < attivita[i].d+D[j])
            {
                D[i] = attivita[i].d+D[j];
                P[i] = j;
            }
        }
        if(D[i] >= max_lenght)
        {
            max_lenght = D[i];
            last = i;
        }
    }
    printf("\nUna delle sequenze che massimizzano la durata pari a %d e':\n", max_lenght);
    LSDP_print(attivita, P, D, n_att, last);
}


void LSDP_print(att* attivita, int* P, int* D, int n_att, int last)
{
    if(P[last] == -1){
        printf("(%d,%d)", attivita[last].s, attivita[last].f);
        return;
    }
    LSDP_print(attivita, P, D, n_att, P[last]);
    printf("(%d,%d)", attivita[last].s, attivita[last].f);
}

void MergeSortWrapper(att* attivita, int n_att)
{
    int l = 0,r = n_att-1;
    att *ausiliario = (att *)malloc(n_att*sizeof(att));
    MergeSort(attivita, l, r, ausiliario);
    free(ausiliario);
}

void MergeSort(att* attivita, int l, int r, att *ausiliario)
{
    int p;
    if(l >= r) // allora avrei un vettore unitario (ordinato)
        return;
    p = (l+r)/2;
    // riordino sottovettore sx
    MergeSort(attivita, l, p, ausiliario);
    // riordino sottovettore dx
    MergeSort(attivita, p+1, r, ausiliario);
    // merge
    Merge(attivita, l, r, ausiliario);
}


void Merge(att* attivita, int l, int r, att* ausiliario)
{
    int pm = (l+r)/2;
    int i = l, j = pm+1, k;
    for(k = l; k <= r; k++)
    {
        if(i>pm) // esaurito il sottovettore sx
            ausiliario[k] = attivita[j++];
        else if(j > r) // esaurito il sottovettore dx
            ausiliario[k] = attivita[i++];
        else if(attivita[i].f <= attivita[j].f) // se l'elemento del sottovettore sx precede quello del sottovettore dx
            ausiliario[k] = attivita[i++];
        else
            ausiliario[k] = attivita[j++];
    }
    // ricopiatura
    for(k = l; k <= r; k++){
        attivita[k] = ausiliario[k];
    }
}

void display_v_att(att* attivita, int n_att)
{
    for(int i = 0; i < n_att; i++)
        printf("\nATT #%d: (%d,%d) durata:%d", i+1, attivita[i].s, attivita[i].f, attivita[i].d);
}