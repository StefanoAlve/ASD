#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int start, end;
} att;

int LeggiAttivita(char *nomefile, att **pv);
void QuickSort(att *v, int l, int r);
int partition(att *v, int l, int r);
void Swap(att *v, int n1, int n2);
void SeqAttMax(att *v, int *opt, int *L, int n);
void StampaSol(att *v, int n, int *L, int k);

int main() {
    att *v = NULL;
    //Lettura file è riempiemnto vettore delle attività
    int n = LeggiAttivita("att2.txt", &v);
    //Ordinamento vettore
    QuickSort(v, 0, n-1);
    //Allocazione dinamica vettori: opt per calcolo durata massima
    //L per memorizzare gli indici per ciascuna attività la attività che la precede
    //nella sua sequenza. -1 se è la prima, e non è compatibile con nessuna delle precedenti
    int *opt = calloc(n, sizeof *opt);
    int *L = malloc(n*sizeof *L);

    //Chiamata a funzione per calcolo della sequenza massima
    SeqAttMax(v, opt, L, n);
    //Deallocazione vettori
    free(v);
    free(opt);
    free(L);

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

//Algoritmo di ordinamento ricorsivo
void QuickSort(att *v, int l, int r){
    int q;
    if (l >= r) return;

    q = partition(v, l, r);
    QuickSort(v, l, q-1);
    QuickSort(v, q+1, r);

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

//La funzione segue il paradigma della programmazione dinamica per trovare
//la sequenza di attività compatibili a lunghezza massima. Infine stampa la
//durata e chiama la funzione ricorsiva per la stampa della sequenza
void SeqAttMax(att *v, int *opt, int *L, int n) {
    int i = 0, max = 0, i_m; //max è la durata massima, i_m è l'indice di dove si trova l'ultima attività della sequenza temporaneamente massima
    //Imposto i vettori per la prima attività
    opt[i] = v[i].end - v[i].start;
    L[i] = -1;
    i++;
    for (; i < n; i++) { //per ogni attività...
        int dur = v[i].end - v[i].start; //calcolo la durata dell'attività corrente
        for (int j = 0; j < i; j++) { //... Ciclo sulle precedenti
            if (v[i].start >= v[j].end) { //se sono compatibili attività i e j
                if (opt[i] < dur + (v[j].end - v[j].start)) { //se la durata attuale della sequenza è minore della durata possibile tenendo conto della attività j come precedente
                    opt[i] = dur + (v[j].end - v[j].start); //Aggiorno la durata
                    L[i] = j; //Salvo l'indice dell'attività precedente
                }
            }
        }
        //Se non è compatibile con nessuna delle
        //precedenti (la durata non è stata modificata) imposto i vettori
        //come se fosse una nuova sequenza di attività
        if (opt[i] == 0){
            opt[i] = v[i].end - v[i].start;
            L[i] = -1;
        }
        //Modifico il massimo se la durata massima attuale è aumentata
        if (opt[i] > max){
            max = opt[i];
            i_m = i;
        }
    }
    //Stampa soluzione
    printf("Durata sequenza massima: %d\n", opt[i_m]);
    printf("Prima sequenza attivita' trovata: ");
    StampaSol(v, n, L, i_m);
}

//La funzione stampa ricorsivamente la sequenza di attività, ricorrendo
//all'indietro il vettore L per trovare l'inizio della sequenza con durata massima
void StampaSol(att *v, int n, int *L, int k){
    if (k == -1)
        return;
    StampaSol(v, n, L, L[k]);
    printf("(%d %d) ", v[k].start, v[k].end);
}