#ifndef ESAME_ACT_H
#define ESAME_ACT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXC 21
typedef struct activities *ACT;
//Elimino typedef struct attivita perchè è superfluo;
typedef struct{
    char nome[20];
    int inizio;
    int durata;
    int valore;
    char vincoli[2][MAXC]; //Ho dimenticato di modificare il tipo di dato vincoli con char al posto di attivita
    int nVin;
}attivita;

ACT activityRead(FILE *f);
int ACTfindByName(char *tmp, ACT elencoAct);
int checkSelection(ACT a, char **selected, int nsel);
int bestSelection(ACT a, char **bestNomi, int *pNsel); //Ho cambiato il tipo della funzione da void a int per poter restituire il profitto per la stampa
//Aggiunta di alcune funzioni utili per il funzionamento del codice e per il debug
int ACTgetN(ACT elencoAct);
void ACTprintAtt(int index, ACT a);
void ACTdealloc(ACT a);
#endif