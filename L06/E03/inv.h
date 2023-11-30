#ifndef E03_INV_H
#define E03_INV_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXC 51
#define MAXOBJ 8
typedef struct{
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
}stat_t;
typedef struct{
    char nome[MAXC];
    char tipo[MAXC];
    stat_t stat;
}inv_t;
typedef struct tabInv_t *ptabInv;
ptabInv leggiInventario(char *nomeFile);
int ricercaObjN(ptabInv tabInv, char *nome);
void stampaObj(ptabInv tabInv, int index);
void stampaObjStats(ptabInv tabInv, int index);
stat_t fornisciStats(ptabInv tabInv, int index);
void stampaObjNome(ptabInv tabInv, int index);
void stampaObjTipo(ptabInv tabInv, int index);
void distruggiInventario(ptabInv tabInv);
#endif //E03_INV_H
