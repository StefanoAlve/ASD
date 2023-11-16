#include <stdio.h>
#include <stdlib.h>
#define MAXL 50

typedef struct {
    int inizio;
    int fine;
}att;

void attSel(int N, att *v);
int attSelR(int d,int N, att *v, int max, int *index, int *tmp, int l, int pos);
int leggiFile(att **v, int nr);

int main() {
    att *v;
    int nr=0, i;
    ///LEGGO IL FILE E RITORNO IL NUMERO DELLE RIGHE
    nr = leggiFile(&v, nr);
    ///FACCIO LA SELEZIONE DELLE ATTIVITA'
    attSel(nr, v);

    return 0;
}

int leggiFile(att **v, int nr) {
    FILE *fp;
    char nomeFile[MAXL];
    int i;

    printf("inserire il nome del file: \n");
    scanf("%s", nomeFile);

    ///CONTROLLO CHE IL PUNTATORE A FILE NON SIA VUOTO
    if((fp = fopen(nomeFile, "r")) == NULL){
        printf("errore in apertura del file");
        exit(1);
    }
    ///PRENDO IL NUMERO DI RIGHE DAL FILE
    fscanf(fp, "%d", &nr);

    ///ALLOCO IL VETTORE DI STRUCT E CONTROLLO L'AVVENUTA ALLOCAZIONE
    *v = malloc(nr*sizeof(att));
    if(v==NULL){
        printf("errore in allocazione del vettore");
        exit(1);
    }

    ///RIEMPIO IL VETTORE DI STRUCT CON GLI ELEMENTI NEL FILE
    for (i=0; i<nr; i++){
        fscanf(fp, "%d %d", &(*v)[i].inizio, &(*v)[i].fine);
    }
    ///CHIUDO IL FILE
    fclose(fp);
    return nr;
}

///WRAPPER DELLA FUNZIONE DI SELEZIONE
void attSel(int N, att *v){
    int index[N], tmp[N], i, max;

    ///MI CREO I 2 VETTORI PER POTERCI INSERIRE IN MANIERA TEMPORANEA E DEFINITIVA GLI INDICI DEI VALORI DELLA STRUCT
    ///DOVE SONO PRESENTI LE ATTIVITA' CHE CONCORRONO NEL MASSIMO DELLA DURATA E MOMENTANEAMENTE ASSEGNO IL VALORE -1
    ///DA USARE COME INDICATORE EVENTUALE DI FINE VETTORE
    for (i=0; i<N; i++){
        index[i] = -1;
        tmp[i] = -1;
    }

    ///FUNZIONE CHE SELEZIONA EFFETTIVAMENTE LE ATTIVITA' E RITORNA LA DURATA MASSIMA
    max = attSelR(0, N, v, 0, index, tmp, 0, 0);

    ///STAMPO LA DURATA MAX
    printf("la durata massima di attivita' e': %d\n", max);

    ///STAMPO I CAMPI DELLA STRUCT CHE CONCORRONO ALLA SELEZIONE
    for (i=0; index[i] != -1; i++){
        printf("{%d, %d} ", v[index[i]].inizio, v[index[i]].fine);
    }
    ///DEALLOCO LA STRUCT
    free(v);
}

///FUNZIONE DI SELEZIONE RICORSIVA
int attSelR(int d, int N, att *v, int max, int *index, int *tmp, int l, int pos){
    int i;

    for(i=l; i<=N; i++){
        ///CONDIZIONE DI FINE
        if(i==N) {
            ///SE LA DURATA TROVATA E' MAGGIORE UGUALE DELLA MASSIMA
            if (d >= max) {
                ///IL MASSIMO COMPLESSIVO E' IL MASSIMO LOCALE
                max = d;
                ///RIEMPIO IL VETTORE DEGLI INDICI
                for (i = 0; i < N; i++) {
                    index[i] = tmp[i];
                }
            }
            return max;
        }
        ///SE MI TROVO NELLA PRIMA POSIZIONE O SE LE ATTIVITA' NON SI ACCAVALLANO
        if(pos==0 || v[i].inizio >= v[tmp[pos-1]].fine) {
            ///ASSEGNO IL SEGUENTE V IN TMP E LO AGGIUNGO ALLA DURATA
            tmp[pos] = i;
            d = d + (v[i].fine - v[i].inizio);

            ///AVANZO DI POSIZIONE IN MANIERA RICORSIVA
            max = attSelR(d, N, v, max, index, tmp, i+1, pos+1);

            ///ELIMINO IL VALORE CHE AVEVO APPENA ASSEGNATO PER PROVARE UNA COMBINAZIONE CON IL PROSSIMO
            ///VALORE ALLA STESSA POSIZIONE
            d = d - (v[i].fine - v[i].inizio);
            tmp[pos] = -1;
        }
    }

    return max;
}