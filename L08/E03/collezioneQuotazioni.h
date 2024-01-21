#ifndef E03_COLLEZIONEQUOTAZIONI_H
#define E03_COLLEZIONEQUOTAZIONI_H

#include "dataOra.h"


typedef struct{
    float dQuot;
}dQuot_s;

typedef struct nodeB *linkB;

struct nodeB{
    dataOra_s dataOra;
    dQuot_s dQuot;
    linkB p;
    linkB r;
    linkB l;
    int nElem;
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
linkB mostraRoot(pBSTquot bst);
void minMaxBST(pBSTquot bst, int cmd);
int isGreater(dQuot_s q1, dQuot_s q2);
int isLower(dQuot_s q1, dQuot_s q2);
void visitaInOrder(linkB root, linkB z, dataOra_s d1, dataOra_s d2, dQuot_s *min, dQuot_s *max);
float mostraRapporto(linkB head);
dataOra_s dataMin();
dataOra_s dataMax();
dQuot_s initQuotaMin();
dQuot_s initQuotaMax();
void stampaQuot(dQuot_s quot);
void BSTbalance(pBSTquot bst);
float altezzaAlberoMassima(linkB head);
float altezzaAlberoMinima(linkB head);
float altezzaAlberoMassimaR(linkB head);
float altezzaAlberoMinimaR(linkB head);
#endif //E03_COLLEZIONEQUOTAZIONI_H
