
#ifndef E02_ST_H
    #define E02_ST_H
    #include <stdio.h>
    #include <stdlib.h>
    #include "string.h"

#define MAXSTRLEN 30

    typedef struct symboltable *ST;
    ST STinit(int N);
    int STcount(ST Stable);
    void STfree(ST Stable);
    int STinsert(ST Stable, char *elab, char *rete);
    int STgetIndex(ST Stable, char *elab, char *rete);
    void STprintName(ST Stable, int index);
    void STprint(ST Stable);
    void STsort(ST Stable, int* vett);

#endif //E02_ST_H
