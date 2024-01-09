#ifndef E02_ST_H
#define E02_ST_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXC 30

typedef struct symbolTable *ST;
ST STInit(int n);
void STfree(ST sTable);
int STcount(ST sTable);
void STprintName(ST sTable, int index);
int STgetIndex(ST sTable, char *elab, char *rete);
int STinsert(ST Stable, char *elab, char *rete);
void STsort(ST Stable, int* vett);
void STprint(ST Stable);
#endif
