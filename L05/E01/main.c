#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int start, end;
} att;

int LeggiAttivita(char *nomefile, att **pv);
void attSel(int n, att *v);
void QuickSort(att *v, int l, int r);
void CombRip(att *v, int *sol, int n, int pos, int start, int *maxS);
void CR_r(att *v, int *sol, int k, int n, int pos, int start, int *maxS);
int ValidaSol(att *v, int *sol, int k, int *maxS);
int partition(att *v, int l, int r);
void Swap(att *v, int n1, int n2);

int main() {
    att *v = NULL;
    //Lettura file è riempiemnto vettore delle attività
    int n = LeggiAttivita("att1.txt", &v);
    //Chiamata a funzione per rilevare le attività compatibili
    attSel(n, v);
    free(v); //Deallocazione vettore attività

    return 0;
}

//La funzione si occupa di aprire il file e allocare il vettore delle
//attività, riempiendolo con i dati del file. Ritorna il numero di
//attività lette
int LeggiAttivita(char *nomefile, att **pv){
    FILE *fp = fopen(nomefile, "r");
    int n = 0;
    if (fp == NULL){
        printf("Errore apertura file\n");
        exit(1);
    }
    fscanf(fp, "%d", &n);
    att *vt = malloc(n*sizeof *vt);
    if (vt == NULL){
        printf("Errore allocazione vettore delle attività\n");
        exit(1);
    }

    for (int i = 0; i < n; i++)
        fscanf(fp, "%d %d", &vt[i].start, &vt[i].end);

    *pv = vt;
    fclose(fp);

    return n;
}

//La funzione esegue dapprima un ordinamento del vettore per tempi di inizio crescenti, per
//semplificare la procedura di controllo per compatibilità delle attività; poi alloca
//il vettore delle soluzioni (interi perchè si memorizza l'indice dell'attività nel vettore)
//e chiama un algortimo di powerset basato sulle combinazioni semplici. Dealloca infine il vettore sol
void attSel(int n, att *v){
    //pos è il livello ricorsivo, start da dove prendo nel vettore delle scelte mentre maxS
    //la somma massima della durata delle attività compatibili
    int l = 0, r = n-1, pos = 0, start = 0, maxS = 0;
    QuickSort(v, l, r);

    int *sol = malloc(n*sizeof *sol);
    if (sol == NULL){
        printf("Errore allocazione vettore delle soluzioni\n");
        exit(1);
    }

    CombRip(v, sol, n, pos, start, &maxS);

    free(sol);
}

//Algoritmo di ordinamento ricorsivo
void QuickSort(att *v, int l, int r){
    int q;
    if (l >= r) return;

    q = partition(v, l, r);
    QuickSort(v, l, q-1);
    QuickSort(v, q+1, r);

}

//La funzione chiama per dimensioni della soluzione decrescenti la ricerca delle combinazioni
//possibili delle attività. Si parte da k = n ovvero prendo tutte le attività. La funzione stampa la soluzione ottimale
//attualmente trovata (non salvo in un vettore a parte la soluzione ottima per tutte le dimensioni)
void CombRip(att *v, int *sol, int n, int pos, int start, int *maxS){
    for (int k = n; k > 0; k--)
        CR_r(v, sol, k, n, pos, start, maxS);

}

void CR_r(att *v, int *sol, int k, int n, int pos, int start, int *maxS){
    if (pos >= k){
        if (ValidaSol(v, sol, k, maxS)){
            printf("Soluzione ottima con %d attivita':\n", k);
            //Se la soluzione è valida si stampa
            for (int t = 0; t < k; t++)
                printf("(%d %d) ", v[sol[t]].start, v[sol[t]].end);
            printf("\n");
        }
        return;
    }
    //Ricorsione
    for (int i = start; i < n; i++){
        sol[pos] = i;
        CR_r(v, sol, k, n, pos+1, i+1, maxS);
    }
}

//Funzione di controllo validita soluzione: se trovo una attività che comincia prima del termine della precedente
//allora la soluzione non è valida (attività incompatibili)
int ValidaSol(att *v, int *sol, int k, int *maxS){
    int ok = 1, S = 0, i;
    for (i = 1; i < k; i++){
        S += v[sol[i-1]].end - v[sol[i-1]].start; //Conteggio somma durate
        if (v[sol[i]].start < v[sol[i-1]].end)
            ok = 0;
    }
    S += v[sol[i-1]].end - v[sol[i-1]].start; //poichè parto dalla seconda attività, dentro il ciclo non conto la somma della durata dell'ultima attività
    if (ok){
        if (S > *maxS){
            //se è valida e ha una durata superiore alla massima corrente, aggiorno il massimo
            *maxS = S;
            return 1;
        }
        return 0;
    }
    return 0;
}

//Funzione di ricerca pivot dell'algoritmo di ordinamento
int partition(att *v, int l, int r){
    int i = l-1, j = r;
    att x = v[r];
    while(1){
        while(v[++i].start < x.start);
        while(v[--j].start > x.start);
        if (i >= j) break;
        Swap(v, i, j);
    }
    Swap(v, i, r);
    return i;
}

//Funzione di scambio tra due attività
void Swap(att *v, int n1, int n2){
    att tmp = v[n1];
    v[n1] = v[n2];
    v[n2] = tmp;
}