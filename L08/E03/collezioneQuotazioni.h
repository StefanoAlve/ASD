#ifndef E03_COLLEZIONEQUOTAZIONI_H
#define E03_COLLEZIONEQUOTAZIONI_H

#include "dataOra.h"

//TODO BST
typedef struct{
    int dQuot;
}dQuot_s;

typedef struct node *link;

struct node{
    dataOra_s dataOra;
    dQuot_s dQuot;
    link r;
    link l;
};
typedef struct BSTquot_s *pBSTquot;
#endif //E03_COLLEZIONEQUOTAZIONI_H
