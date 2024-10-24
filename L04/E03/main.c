#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void CercaCollana(int *val, int n);
int CalcolaCollana(int pos, int *val, int *sol, int *fin, int l, int start, int maxl, int n);

int main(){

    int n = 4; //Numero tipi di pietre
    int *pietre = malloc(n*sizeof (int));
    if (pietre == NULL) exit(1);

    printf("Inserire il numero delle pietre preziose uno sotto l'altro:\n");
    printf("<zaffiri> <rubini> <topazi> <smeraldi>\n");
    for (int i = 0; i < n; i++){
        scanf("%d", &pietre[i]); //Il vettore pietre contiene il numero di pietre per tipo
    }

    CercaCollana(pietre, n);
    free(pietre);

    return 0;
}

//La funzione alloca i vettori della soluzione corrente con quella ottima,
//inizializza il vettore fin (sol ottima) a -1 e itera 4 volte la funzione ricorsiva
//a seconda di quale pietra inserisco per prima. Infine stampa la collana a lunghezza massima trovata
void CercaCollana(int *val, int n){
    int maxl = 0, ml = 0, l = 0, start = 0; //ml è la lunghezza della collana massima trovata
    for (int q = 0; q < n; q++) maxl += val[q]; //maxl è la lunghezza massima possibile della collana
    int *sol = malloc(maxl*sizeof (int));
    int *fin = malloc(maxl*sizeof (int));

    for (int k = 0; k < maxl; k++)
        fin[k] = -1;

    //Per ogni possibile inizio della collana trovo la lunghezza massima
    //e se supera quella massima generale aggiorno ml
    clock_t inizio = clock();
    for (int h = 0; h < n; h++){
        l = CalcolaCollana(h, val, sol, fin, l, start, maxl, n);
        if (l > ml) ml = l;
        l = 0; start = 0; //devo reinizializzare per ripartire con un nuovo inizio di collana
    }
    clock_t fine = clock();
    int i;
    for (i = 0; i < ml; i++){
        if (fin[i] == 0) printf("%c ", 'z');
        else if (fin[i] == 1) printf("%c ", 'r');
        else if (fin[i] == 2) printf("%c ", 't');
        else if (fin[i] == 3) printf("%c ", 's');
    }
    printf("\nLa collana a lunghezza massima e' lunga %d\n", ml);
    printf("Tempo esecuzione: %.2f secondi", (double )(fine-inizio)/CLOCKS_PER_SEC);

    free(sol);
    free(fin);

}

//La funzione cerca tutte le possibili collane seguendo le regole, applicate a seconda
//di dove scende pos nella ricorsione, che indica la posizione della pietra da inserire
//La funzione ritorna la lunghezza massima trovata l, mentre start è l'indice del vettore
//sol dove inserisco la pietra (0 = z, 1 = r, 2 = t, 3 = s)
int CalcolaCollana(int pos, int *val, int *sol, int *fin, int l, int start, int maxl, int n){
    int l1, l2, i;

    if (val[pos] > 0){ //Se ci sono ancora pietre disponibili per quel tipo
        sol[start] = pos; //aggiungo la pietra
        val[pos]--; //diminuisco il numero di quelle ancora disponibili
        l++; //incremento la lunghezza

        //a seconda che abbia inserito z r t oppure s, scendo nei due rami possibili per quella scelta
        if (pos == 0){
            l1 = CalcolaCollana(pos, val, sol, fin, l, start+1, maxl, n);
            l2 = CalcolaCollana(pos+1, val, sol, fin, l, start+1, maxl, n);
        } else if (pos == 1){
            l1 = CalcolaCollana(pos+1, val, sol, fin,  l, start+1, maxl, n);
            l2 = CalcolaCollana(pos+2, val, sol, fin, l, start+1, maxl, n);
        } else if (pos == 2){
            l1 = CalcolaCollana(pos-1, val, sol, fin, l, start+1, maxl, n);
            l2 = CalcolaCollana(pos-2, val, sol, fin, l, start+1, maxl, n);
        } else {
            l1 = CalcolaCollana(pos, val, sol, fin, l, start+1, maxl, n);
            l2 = CalcolaCollana(pos-1, val, sol, fin, l, start+1, maxl, n);
        }

        val[pos]++; //tornato dai due rami, rendo nuovamente disponibile la pietra per l'altro ramo dello stesso livello
        if (l1 == 0 && l2 == 0){ //se non ho potuto più inserire pietre
            for (i = 0; fin[i] != -1 && i < maxl; i++); //conto la lunghezza della collana massima sin ora trovata
            if (l > i) //se la nuova lunghezza supera la massima, aggiorno fin
                for (int j = 0; j < l; j++)
                    fin[j] = sol[j];
            return l; //ritorno la lunghezza della collana trovata
        }
        else if (l1 > l2) //se i due rami hanno lunghezze diverse (non sono al caso terminale) ritorno la massima tra i due
            return l1;
        return l2;
    }
    return 0; //non ci sono più pietre per quel tipo

}