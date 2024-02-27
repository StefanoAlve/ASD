

#include "ACT.h"

typedef struct activities {
    info *activities; //vettore di informazioni relative alle attività
    int n; //numero di attività
}

ACT activityRead(FILE *fin ){
    ACT A = malloc(sizeof(struct activities));
    int num_activity , num_priority, j ;
    char name[20];
    fscanf(fin, "%d %d", num_activity, num_priority);
    A->activities = malloc(num_activities * sizeof(struct info)); //allocazione della vettore
delle attività
    for(int i = 0 ; i<num_activity; i++){
    fscanf(fin, "%s", name ) ;
    j= atoi(name[strlen(name)] ) //coversione dell'ultima cifra del nome in un intero per
inserire in maniera ordinata le attività nel vettore
delle attività;
strcpy(name, A->activities[j].name);
fscanf(fin, "%d %d %d", A->activities[j].
tempo_inizio, A->activities[j].durata, A->activities[j].profitto ) ;
}
for(int i = 0; i < num_priority && name != '\0' ; i++){ //sistemare la terminazione del
ciclo
char name[20];
info temp;
fscanf(fin, "%s", name ) ;
j= atoi(name[strlen(name)] ) //coversione dell'ultima cifra del nome in un intero per
inserire in maniera ordinata le attività nel
        vettore delle attività;
for(int k = 0; k < num_activity; k++ ){ //questo ciclo si deve occupare di modificare
l'ordine delle attività del vettore, in modo
da inserire prima le attività a priorità maggiore, gestione delle priorità in maniera
greedy
if( A->activities[k].name != A->activities[j].name && j < k ){ //in questo modo effetto
uno swap solamente nel caso in cui
        j si trova prima di k nel vettore ,
//in questo modo eseguirò sicuramente prima le attività a priorità maggiore e
successivamente l'attività vincolata
A->activities[j] = temp;
A->activities[j] = A->activities[k];
A->activities[k] = temp;
}
}
}
