#ifndef E01_ST_H
#define E01_ST_H
#define MAXC 30
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ST_S *ST;

ST STInit(int n);
void STfree(ST sTable);
int STcount(ST sTable);
void STprint(ST sTable, int index);
int STgetIndex(ST sTable, char name[MAXC]);
int STinsert(ST sTable, char name[MAXC]);

#endif //E01_ST_H
