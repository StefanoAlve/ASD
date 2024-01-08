#ifndef E03_COLLEZIONEQUOTAZIONI_H
#define E03_COLLEZIONEQUOTAZIONI_H

#include "dataOra.h"

//TODO BST


typedef struct{
    float dQuot;
}dQuot_s;

typedef struct nodeB *linkB;

struct nodeB{
    dataOra_s dataOra;
    dQuot_s dQuot;
    linkB r;
    linkB l;
};

typedef struct BSTquot_s *pBSTquot;
pBSTquot bstInit();
dQuot_s calcolaDQuot(int valori[], int scambi[], int n);
pBSTquot riempiBST(FILE *fp);
void BSTinsert(pBSTquot bst,dataOra_s d,dQuot_s quot);
void BSTfree(pBSTquot bst);
void treeFree(linkB h, linkB z);
dQuot_s BSTcerca(pBSTquot bst, dataOra_s d);
dQuot_s BSTcercaR(linkB h, linkB z, dataOra_s d);
dQuot_s quotNULL();
void minMaxBST(pBSTquot bst, int cmd);
int isGreater(dQuot_s q1, dQuot_s q2);
int isLower(dQuot_s q1, dQuot_s q2);
void visitaInOrder(linkB root, linkB z, dataOra_s d1, dataOra_s d2, dQuot_s *min, dQuot_s *max);
dataOra_s dataMin();
dataOra_s dataMax();
dQuot_s initQuotaMin();
dQuot_s initQuotaMax();
void stampaQuot(dQuot_s quot);
#endif //E03_COLLEZIONEQUOTAZIONI_H
