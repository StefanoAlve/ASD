#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define numPietre 4
#define MAXC 100

                             ///BREVE COMMENTO DEL RAGIONAMENTO APPLICATO
/*        Guardando il precedente                 Guardando il successivo      Combinazioni risultanti:
 * zaffiro -> zaffiro o rubino           |   zaffiro  <- zaffiro o topazio      zz, zr, tz
 * rubino -> smaraldo o topazio          |   rubino   <- zaffiro o topazio      rs, rt, zr, tr
 * topazio -> zaffiro o rubino           |   topazio  <- smeraldo o rubino      tz, tr, st, rt
 * smeraldo -> smaraldo o topazio        |   smeraldo <- smeraldo o rubino      ss, st, rs
 *
 * Dalle combinazioni ricavate, si può notare che il numero di zaffiri e smeraldi è un dato indipendente poichè possono essere sempre seguiti
 * da una pietra del medesimo tipo.
 * I topazi e i rubini sono in stretta dipendenza tra di loro perchè hanno entrambi una possibile configurazione rt o tr;
 * notato ciò se il numero di rubini eccede il numero di topazi di più di 1 o viceversa, allora risulta una configurazione impossibile.
 * Inoltre, notando che se il numero di rubini è inferiore al numero di topazi allora la configurazione deve per forza iniziare con t, si può usare un indice start per evitare
 * numerose chiamate ricorsive.
 */


typedef struct{
    int z;
    int r;
    int t;
    int s;
}pietre;

int leggiFile(pietre **pCollane);
void stampaCollana(char *sequenza, int n);
void stampa_collane(pietre *collane, int nCollane);
void inizializzaRimanenti(int rimanenti[numPietre], pietre collana);
void wrapperTrovaComb(int nCollane, pietre *collane);
int trovaComb(char *val, char *sol, int rimanenti[numPietre], int n_dist, int dimSol, int pos, int flag, int start);
int controlloValidita(char *sol, int pos);
int pietreValide(int *restanti);
void riduciPietre(int *restanti, int *k);
int controlloStart(int *restanti);

int main(void) {
    //Inizializzazione variabili
    int nCollane;
    pietre *collane;
    //Corpo programma
    nCollane = leggiFile(&collane);
    stampa_collane(collane,nCollane);
    wrapperTrovaComb(nCollane, collane);
    return 0;
}

int leggiFile(pietre **pCollane){
    //Inizializzazione variabili
    int nCollane, i;
    pietre *collane;
    FILE *fp;
    char *nomeFile, tmp[MAXC];

    //Corpo funzione
    printf("Inserire il nome del file:");
    scanf("%s", tmp);
    nomeFile = strdup(tmp);
    //Apertura file
    fp = fopen(nomeFile, "r");
    if(fp == NULL){
        printf("Errore nella lettura del file!\n");
        exit(1);
    }

    fscanf(fp,"%d", &nCollane); //Trovo il numero di collane

    //Allocazione vett collane
    collane = (pietre*)malloc(nCollane*sizeof(pietre));
    if(collane == NULL){
        printf("Errore nell'allozazione del vettore di collane!\n");
        exit(1);
    }
    for(i=0; i<nCollane; i++){
        fscanf(fp,"%d %d %d %d", &collane[i].z, &collane[i].r, &collane[i].t, &collane[i].s);
    }
    *pCollane = collane;

    //Chiusura file
    fclose(fp);
    //Deallocazione
    free(nomeFile);
    return nCollane;
}


void stampaCollana(char *sequenza, int n){
    for(int i=0; i<n; i++){
        printf("%c ",sequenza[i]);
    }
    printf("\n");
}

void stampa_collane(pietre *collane, int nCollane){
    for(int i = 0; i<nCollane; i++){
        printf("Test n.%d: %d zaffiri, %d rubini, %d topazi, %d smeraldi\n", i+1, collane[i].z, collane[i].r, collane[i].t,collane[i].s);
        printf("Numero pietre totali: %d\n", collane[i].z+collane[i].r+collane[i].t+collane[i].s);
    }
}

void inizializzaRimanenti(int rimanenti[4], pietre collana){
    rimanenti[0] = collana.z;
    rimanenti[1] = collana.r;
    rimanenti[2] = collana.t;
    rimanenti[3] = collana.s;
}

int trovaComb(char *val, char *sol, int rimanenti[4], int n_dist, int dimSol, int pos, int flag, int start){
    int i;
    if(pos>=dimSol){
        printf("La collana piu' lunga puo' essere riempita con %d pietre:\n", dimSol);
        stampaCollana(sol, dimSol);
        flag = 1;
        return flag;
    }
    for(i=start; i<n_dist; i++){
        if(rimanenti[i] > 0){
            rimanenti[i]--;
            sol[pos] = val[i];
            if(controlloValidita(sol, pos)){
                flag = trovaComb(val, sol, rimanenti, n_dist, dimSol, pos+1, flag, 0);
            }
            rimanenti[i]++;
            if(flag){ //inutile continuare a cercare perchè ho già trovato la soluzione che mi serve
                return flag;
            }
        }
    }
    return flag;
}

int controlloValidita(char *sol, int pos){
    /// Eseguo il controllo delle condizioni imposte
    char precedente = sol[pos-1], valido = 0;
    if(pos == 0){
        valido = 1;
    }
    else{
        switch(precedente){
            case 'z':
                if(sol[pos] == 'z' || sol[pos] == 'r')
                    valido = 1;
                break;
            case 'r':
                if(sol[pos] == 's' || sol[pos] == 't')
                    valido = 1;
                break;
            case 't':
                if(sol[pos] == 'z' || sol[pos] == 'r')
                    valido = 1;
                break;
            case 's':
                if(sol[pos] == 's' || sol[pos] == 't')
                    valido = 1;
                break;
            default:
                break;
        }
    }
    return valido;
}

void wrapperTrovaComb(int nCollane, pietre *collane){
    /// Utilizzo un wrapper per contenere la funzione trovaComb in modo da non inserire troppi dati superflui nel main
    int flag, rimanenti[numPietre],dimSol, pos = 0;
    float inizio, tempo;
    char val[numPietre] = {'z','r','t','s'}, *sol;

    //Corpo funzione
    for(int i = 0; i<nCollane; i++){
        inizio = (float)clock();
        printf("\nTest n.%d:\n", i+1);
        inizializzaRimanenti(rimanenti, collane[i]);
        dimSol = rimanenti[0]+rimanenti[1]+rimanenti[2]+rimanenti[3];
        flag = 0;
        while(!flag){
            sol = (char*)malloc(dimSol*sizeof(char));
            if(pietreValide(rimanenti)) {
                flag = trovaComb(val, sol, rimanenti, 4, dimSol, pos, flag, controlloStart(rimanenti));
                dimSol--;
            }
            else{
                riduciPietre(rimanenti, &dimSol);
            }
            free(sol);
        }
        tempo = (float)clock()-inizio;
        printf("Tempo impiegato: %.3f secondi\n",(tempo/1000));
    }
    free(collane);
}

int pietreValide(int *restanti){
    /// Una collana, per essere valida deve avere al massimo un numero di rubini che differisce al massimo da quello dai topazi di 1
    int valido = 0;
    int r,t;
    r = restanti[1]; t = restanti[2];
    if (t <= 1+r && r <= t+1)
        valido = 1;
    return valido;
}

void riduciPietre(int *restanti, int *k){
    /// Impongo una collana valida imponendo la condizione presentata il pietreValide, se ho rubini o topazi in eccesso li modifico e aggiorno la nuova dimensione massima
    int r,t;
    r = restanti[1]; t = restanti[2];
    if (r > t+1)
        r = t+1;
    if (t > 1+r)
        t = r+1;
    *k = restanti[0]+restanti[3]+r+t; //aggiornamento dimensione
    restanti[1] = r; restanti[2] = t;
}

int controlloStart(int *restanti){
    /// Se il numero di rubini è minore di quello di topazi la sequenza inizierà sicuramente con il topazio (applico questa condizione per ottimizzare di molto la velocità di esecuzione)
    int start = 0;
    if(restanti[1]<restanti[2]){
        start = 2;
    }
    return start;
}