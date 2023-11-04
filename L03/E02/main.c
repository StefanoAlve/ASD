#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXC 100
//Utilizzato per definire la dim max del vettore di puntatori a stringhe. Poichè non si conosce il
//numero di canzoni totali fino al termine della lettura del file, si ipotizza che all'interno del file ci siano al più 100 canzoni totali

#define MAXN 255

typedef struct {
    int *canzoni;
    int num_canzoni;
} Canzoni_x_Amico;

//Funzioni
int LeggiFile(char *NomeFile, Canzoni_x_Amico **p_Scelte, char **Canzoni, int *p_TotCanzoni);
int princ_molt(int pos, Canzoni_x_Amico *Scelte, int *sol, int A, int n_sol, char **Canzoni);
void StampaSol(int *sol, int A, char **Canzoni);
void Dealloc(int *sol, Canzoni_x_Amico *Scelte, char **Canzoni, int A, int TotCanzoni);

int main() {
    int A, n_sol = 0, pos = 0, TotCanzoni = 0, *p_TotCanzoni = &TotCanzoni, *sol = NULL;
    char NomeFile[MAXN], *Canzoni[MAXC]; //Canzoni è un vettore di puntatori a stringhe; usato per memorizzare i nomi di tutte le canzoni del file
    Canzoni_x_Amico *Scelte, **p_Scelte = &Scelte; //Scelte rappresenta il vettore di struct con le canzoni di ogni amico

    printf("Inserire il nome del file:\n");
    scanf("%s", NomeFile);

    A = LeggiFile(NomeFile, p_Scelte, Canzoni, p_TotCanzoni);

    //Allocazione dinamica del vettore delle possibili playlist
    sol = (int *)malloc(A * sizeof(int));

    if (sol != NULL) {
        //Chiamata alla funzione che calcola il numero delle playlist e le stampa
        n_sol = princ_molt(pos, Scelte, sol, A, n_sol, Canzoni);
        printf("Le possibili playlist sono %d", n_sol);
    } else {
        printf("Errore allocazione dinamica");
        exit(1);
    }

    //Deallocazione memoria dinamica
    Dealloc(sol,Scelte,Canzoni,A,TotCanzoni);

    return 0;
}

//La funzione LeggiFile si occupa di leggere il contenuto ed assegnare i dati alle rispettive strutture dati
// i = indice delle strutture di Scelte, j = indice del vettore Canzoni, t = indice del vettore canzoni di ogni struttura
int LeggiFile(char *NomeFile, Canzoni_x_Amico **p_Scelte, char **Canzoni, int *p_TotCanzoni) {
    FILE *fp;
    int num_amici = 0, i = 0, j = 0, t = 0;
    char canzone[MAXN];
    Canzoni_x_Amico *Scelte = NULL;

    //Inizializzazione del vettore di puntatori a stringhe
    for (int h = 0; h < MAXC; h++) {
        Canzoni[h] = NULL;
    }

    fp = fopen(NomeFile, "r");
    if (fp != NULL) {
        fscanf(fp, "%d", &num_amici);

        //Allocazione dinamica del vettore di struct Scelte
        Scelte = (Canzoni_x_Amico *)malloc(num_amici * sizeof(Canzoni_x_Amico));
        if (Scelte == NULL) {
            printf("Errore allocazione dinamica");
            exit(1);
        }

        while (fscanf(fp, "%d", &Scelte[i].num_canzoni) == 1) {
            //Allocazione del vettore canzoni della i-esima struct della dimensione del numero delle canzoni dell'i-esimo amico
            Scelte[i].canzoni = (int *)malloc(Scelte[i].num_canzoni * sizeof(int));
            if (Scelte[i].canzoni == NULL) {
                printf("Errore allocazione dinamica");
                exit(1);
            }
            //j è usato come intero assegnato a canzoni che rappresenta la j-esima canzone letta dal file, oltre che la j-esima canzone del vettore Canzoni
            while (j < (Scelte[i].num_canzoni + (*p_TotCanzoni))) {
                fscanf(fp, "%s", canzone);
                Canzoni[j] = strdup(canzone); //Allocazione dinamica delle singole canzoni
                if (Canzoni[j] == NULL) {
                    printf("Errore allocazione dinamica");
                    exit(1);
                }
                Scelte[i].canzoni[t] = j; //nei vettori canzoni delle struct metto come valore intero la posizione della canzone all'interno del vettore Canzoni
                j++; t++;
            }
            *p_TotCanzoni += Scelte[i].num_canzoni; //Aggiorno il numnero totale delle canzoni
            i++;
            t = 0; //t deve tornare a 0 ogni volta che passo alla successiva struct, e quindi al successivo vettore canzoni del successivo amico
        }
        fclose(fp);
    } else {
        printf("ERRORE: Impossibile aprire il file\n");
    }
    *p_Scelte = Scelte;
    return num_amici;
}

//La funzione usa l'algoritmo che implementa ricorsivamente il principio della moltiplicazione del calcolo combinatorio
int princ_molt(int pos, Canzoni_x_Amico *Scelte, int *sol, int A, int n_sol, char **Canzoni) {
    if (pos >= A) {
        StampaSol(sol, A, Canzoni);
        return n_sol + 1;
    }
    for (int i = 0; i < Scelte[pos].num_canzoni; i++) {
        sol[pos] = Scelte[pos].canzoni[i];
        n_sol = princ_molt(pos + 1, Scelte, sol, A, n_sol, Canzoni);
    }
    return n_sol;
}

void StampaSol(int *sol, int A, char **Canzoni) {
    for (int i = 0; i < A; i++) {
        printf(" %s", Canzoni[sol[i]]); //sol[i] è quindi l'indice del vettore Canzoni, così stampo direttamente il nome
    }
    printf("\n");
}

void Dealloc(int *sol, Canzoni_x_Amico *Scelte, char **Canzoni, int A, int TotCanzoni){
    free(sol);
    for (int h = 0; h < A; h++) free(Scelte[h].canzoni);
    free(Scelte);
    for (int y = 0; y < TotCanzoni; y++) free(Canzoni[y]);
}