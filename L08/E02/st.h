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
int STsearchIndexElab(ST sTable, char name[MAXC]);
int STsearchIndexReti(ST sTable, char name[MAXC]);
void STinsertElab(ST sTable, char name[MAXC], int i);
void STinsertRete(ST sTable, char name[MAXC], int i);

#endif
