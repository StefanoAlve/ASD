

#ifndef E03_DAILYQUOTBST_H
    #include "datetime.h"
    #include <stdlib.h>
    #define E03_DAILYQUOTBST_H
    typedef struct{
        float dailyQuot;
    }dQuot_s;
    typedef struct BSTnode *link_bst;
    typedef struct bst *BST;
    int isGreater(dQuot_s q1, dQuot_s q2);
    int isLower(dQuot_s q1, dQuot_s q2);
    BST bstINIT();
    BST riempiBST(BST bst, FILE *fp);
    void BSTfree(BST bst);
    void treeFree(link_bst h,link_bst z);
    void BSTinsert_leafR(BST bst, dQuot_s dQuot, dateTime_s dT);
    dQuot_s calcola_dQuot(int *valori, int *scambi, int n);
    dQuot_s BSTsearch(BST bst, dateTime_s dT);
    dQuot_s BSTsearchR(link_bst h, link_bst z, dateTime_s dT);
    dQuot_s quotMIN();
    dQuot_s quotMAX();
    dQuot_s quotNULL();
    void displayQuot(dQuot_s dQuot);
    void ricerca_min_max(BST bst, int flag);
    void inOrderVisit(link_bst root, link_bst z, dateTime_s d1, dateTime_s d2, dQuot_s* min, dQuot_s *max);
    void BSTbalance(BST bst, int soglia);
    void BSTvisit(BST bst);
    int AltezzaAlberoMassimaWrapper(BST bst);
    int AltezzaAlberoMinimaWrapper(BST bst);
#endif //E03_DAILYQUOTBST_H
