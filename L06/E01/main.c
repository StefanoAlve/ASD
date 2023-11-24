#include <stdio.h>
#include <stdlib.h>
#define MAXL 50

typedef struct {
    int inizio;
    int fine;
}att;

void attSel(int N, att *v);
int leggiFile(att **v, int nr);
void attPrint(att *v, int *link, int i);

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

///FUNZIONE CHE TROVA LA DURATA MASSIMA DELLE ATTIVITA'
void attSel(int N, att *v){
    int durata[N],linkTmp, durtmp, link[N], i, j;

    ///IL PRIMO VALORE DEVE ESSERE NULLO INFATTI UTILIZZO IL -1 NEL LINK PER INDICARE L'INIZIO DI UNA SERIE DI ATTIVITA'
    link[0] = -1;
    durata[0] = v[0].fine - v[0].inizio;
    ///ITERO UNA VOLTA SU TUTTO IL VETTORE DI STRUCT
    for(i=1; i<N; i++){
        ///PREINIZIALIZZO I VALORI DI DURATA E LINK
        link[i] = -1;
        durata[i] = v[i].fine - v[i].inizio;
        ///ITERO FINO AL RAGGIUNGIMENTO DELL ELEMENTO ESAMINATO
        for(j=0; j<i; j++){
            ///CONTROLLO LA COMPATIBILITA' FRA LE DUE ATTIVITA'
            if (v[i].inizio >= v[j].fine) {
                ///MI SALVO IL VALORE DI DURATA TEMPORANEO CHE HA L ATTIVITA ARRIVATA FINO A QUEL PUNTO SEGUENDO LA SERIE
                ///INDICATA DAL VALORE ALL'INDICE J
                durtmp = v[i].fine - v[i].inizio + durata[j];

                ///SE LA DURATA E' MAGGIORE DI QUELLA PRESENTE NEL VETTORE DELLE DURATE AGIORNO I MIEI DATI CON QUELLI NUOVI
                if (durtmp >= durata[i]) {
                    link[i] = j;
                    durata[i] = durtmp;
                }
            }

        }
    }
    ///TROVO L'INDICE IN CUI SI TROVA L'DURATA MASSIMA, OVVERO LA CODA DELLA SERIE CON MAGGIOR DURATA
    linkTmp = 0;
    for (i=1; i<N; i++){
        if (durata[i] >= durata[linkTmp]){
            linkTmp = i;
        }
    }
    ///PRINTO
    attPrint(v, link, linkTmp);


    ///DEALLOCO LA STRUCT
    free(v);
}
///FUNZIONE RICORSIVA CHE PRINTA LA SOLUZIONE
void attPrint(att *v, int *link, int i) {
    ///CONDIZIONE DI ARRIVO ALLA CODA DELLA SERIE
    if(link[i] == -1){
        printf("{%d, %d} ", v[i].inizio, v[i].fine);
        return;
    }
    ///RICORSIONE CHE PARTE DALLA FINE E VA A CERCARE L'INIZIO DELLA SERIE
    attPrint(v, link, link[i]);
    ///PRINTAGGIO
    printf("{%d, %d} ", v[i].inizio, v[i].fine);
}
