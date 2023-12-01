#ifndef E03_INVENTARIO_H
#define E03_INVENTARIO_H
#include <stdio.h>
#include <stdlib.h>
#define maxL 50

typedef struct{
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
}stat_s;

typedef struct{
    char nome[maxL];
    char tipologia[maxL];
    stat_s stat;
}oggetti_s;

oggetti_s *caricaOggetti(char nomeFile[], int *numOggetti);
void deallocaOggetti(oggetti_s *v);
void stampaOggetti(oggetti_s *v, int numOggetti);

#endif //E03_INVENTARIO_H
