#ifndef E03_COLLEZIONETITOLI_H
#define E03_COLLEZIONETITOLI_H
#include "titolo.h"
#include "collezioneQuotazioni.h"

typedef struct node *link;
typedef struct collezioneTitoli *pCollezioneT;

pCollezioneT listInit();
link newNode(pTitolo titolo, pBSTquot bstQuot, link next);
void nodeInsertSorted(pCollezioneT collezioneT, pBSTquot bstQuot, pTitolo titolo);
link ricercaTitolo(pCollezioneT collezioneT, char titolo[]);
dQuot_s cercaQuota(link node);
pBSTquot cercaBST(link node);
void minMaxSearch(link node, int cmd);
void listaFree(link head);
void deallocaCollezioneT(pCollezioneT collezioneT);
#endif //E03_COLLEZIONETITOLI_H
