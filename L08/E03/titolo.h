#ifndef E03_TITOLO_H
#define E03_TITOLO_H

#define MAXC 21
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct titolo_s *pTitolo;
pTitolo titoloInit();
pTitolo leggiTitolo(FILE *fp);
int confrontaTitoli(pTitolo t1, pTitolo t2);
void distruggiTitolo(pTitolo titolo);
pTitolo creaTitolo(char* tmp);
#endif //E03_TITOLO_H
