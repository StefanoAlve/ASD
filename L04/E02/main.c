#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXC1 50
#define MAXC2 6
#define MAXC3 11

typedef struct{
    char codice[MAXC2];
    char nome[MAXC1];
    char cognome[MAXC1];
    char birth[MAXC3];
    char via[MAXC1];
    char citta[MAXC1];
    char cap[MAXC1];
} Item;

typedef char *Key;

typedef struct node *link;

struct node{
    Item val;
    link next;
};

typedef enum{KBInsert, FileInsert, CodSearch, ExtrCodSearch, ExtrBSearch, printFile, end, err} comando;

Key KEYget(Item d);
int KEYeq(Key k1, Key k2);
int KEYgeq(Key k1, Key k2);




int main(){

    return 0;
}

//Ritorna la data di nascita
Key KEYget(Item d){
    return d.birth;
}

//ritorna 1 se le due date sono uguali
int KEYeq(Key k1, Key k2){
    int eq = strcmp(k1, k2);
    if (eq == 0) return 1;
    return 0;
}

//ritorna 1 se la prima data è uguale o successiva alla seconda
int KEYgeq(Key k1, Key k2){
    int eq = strcmp(k1, k2);
    if (eq >= 0) return 1;
    return 0;
}