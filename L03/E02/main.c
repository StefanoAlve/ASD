#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXL 256
/* N.B.
    Piuttosto che utilizzare una matrice di caratteri per memorizzare la soluzione, ho voluto memorizzare le canzoni con un certo indice
    Da 0 al numero di canzoni totali - 1 provando a sfruttare, come accennato dal Prof. Camurati a lezione, quella che può vagamente
    somigliare a una tabella di simboli. Usando la struct canzoni_proposte, la quale contiene un vettore di interi (il codice delle canzoni)
    posso convertire il codice dell'iesima canzone accedendo alla riga i-esima del vettore di puntatori a char mat_canzoni, presente nella struct match
    (ovvero la soluzione effettiva).
*/

typedef struct{
    int *codice_canzone;
    int num_canzoni_proposte;
}canzoni_proposte;

typedef struct{
    char **mat_canzoni;
    int n_canzoni;
}match;

canzoni_proposte *leggi_file(char *file_name, match *s_match, int* num_amici);
void stampa_canzone(match s_match, int pos, int flag);
void freeDataStructures(match s_match, canzoni_proposte *vett_amici, canzoni_proposte soluzione);
int principio_molt(canzoni_proposte *vett_amici, canzoni_proposte soluzione, match s_match, int num_amici, int pos, int cont);

int main(void)
{
    int num_amici;
    char file_name[MAXL];
    canzoni_proposte *vett_amici, soluzione;
    match s_match;

    printf("Inserisci il nome del file:");
    scanf("%s", file_name);
    vett_amici = leggi_file(file_name, &s_match, &num_amici);
    printf("Ecco le canzoni proposte:\n");
    for (int i = 0; i < s_match.n_canzoni; i++)
        stampa_canzone(s_match, i, 1);
    printf("Vuoi procedere con la stampa delle combinazioni possibili? y/n");
    // struct con una possibile playlist (vettore di interi contenente il codice delle canzoni e un numero di canzoni).
    soluzione.codice_canzone = (int*)malloc(num_amici*sizeof(int)); // allocazione del vettore di interi che conterrà le soluzioni
    soluzione.num_canzoni_proposte = num_amici;
    principio_molt(vett_amici, soluzione, s_match, num_amici, 0, 0);
    freeDataStructures(s_match, vett_amici, soluzione);
    return 0;
}


canzoni_proposte *leggi_file(char *file_name, match* s_match, int* num_amici)
{
    int i, j, canzoni_proposte_each= 0, codice_canzone = 0;
    canzoni_proposte *vett_amici = NULL;
    FILE *fp_in = NULL;
    char song[MAXL];
    fp_in = fopen(file_name, "r");

    if(fp_in != NULL)
    {
        fscanf(fp_in, "%d", num_amici);
        vett_amici = (canzoni_proposte *) malloc(*num_amici * sizeof(canzoni_proposte)); // Alloco tante struct quante sono il numero di amici
        s_match->mat_canzoni = (char**)malloc(5*(*num_amici)*sizeof(char*)); // alloco per un numero di stringhe > del necessario e poi libero una parte della memoria non usata
        for(i = 0; i < *num_amici; i++)
        {
            // lettura del numero C di canzoni proposte da ciascun amico:
            fscanf(fp_in, " %d ", &canzoni_proposte_each);
            vett_amici[i].num_canzoni_proposte = canzoni_proposte_each;
            vett_amici[i].codice_canzone = (int*)malloc(canzoni_proposte_each*sizeof(int)); // alloco nel vettore di codici tanti interi quante sono le canzoni proposte
            for(j = 0; j < canzoni_proposte_each; j++)
            {
                // sistemo la struct dell'i-esimo amico
                vett_amici[i].codice_canzone[j] = codice_canzone;
                // Sistemo il match
                fscanf(fp_in, " %s", song); // Leggo il nome della canzone
                s_match->mat_canzoni[codice_canzone] = (char*)malloc(strlen(song)*sizeof(char)+sizeof(char)); // alloco lo spazio necessario per ospitare la canzone nella riga "codice_canzone"
                strcpy(s_match->mat_canzoni[codice_canzone], song); // copio la canzone nella matrice contenente le canzoni (riga per riga)
                codice_canzone++;
            }
        }
    }
    s_match->n_canzoni = codice_canzone;
    s_match->mat_canzoni = (char**)realloc(s_match->mat_canzoni, s_match->n_canzoni * sizeof(char *));
    return vett_amici;
}


void stampa_canzone(match s_match, int pos, int flag){
    if (flag)
        printf("%d) %s\n", pos+1, s_match.mat_canzoni[pos]);
    else
        printf("- %s\n", s_match.mat_canzoni[pos]);
}

void freeDataStructures(match s_match, canzoni_proposte *vett_amici, canzoni_proposte soluzione)
{
    int num_canzoni_totale = s_match.n_canzoni, i;
    for (i = 0; i < num_canzoni_totale; i++)
        free(s_match.mat_canzoni[i]); // libero l'i-esima riga della matrice
    free(s_match.mat_canzoni);
    // vettore contenente i codici delle canzoni (soluzione)
    free(soluzione.codice_canzone);
    // libero il vettore di struct amici.
    for (i = 0; i < soluzione.num_canzoni_proposte; i++)
        free(vett_amici[i].codice_canzone);
    free(vett_amici);
}


int principio_molt(canzoni_proposte *vett_amici, canzoni_proposte soluzione, match s_match, int num_amici, int pos, int cont)
{
    int i;
    if(pos == num_amici)
    {
        printf("\nPlaylist %d:\n", cont+1);
        for (i = 0; i < num_amici; i++)
            stampa_canzone(s_match, soluzione.codice_canzone[i], 0);
        return cont+1;
    }
    for (i = 0; i < vett_amici[pos].num_canzoni_proposte; i++)
    {
        soluzione.codice_canzone[pos] = vett_amici[pos].codice_canzone[i];
        cont = principio_molt(vett_amici, soluzione, s_match, num_amici, pos+1, cont);
    }
    return cont;
}