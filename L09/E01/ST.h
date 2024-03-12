
#ifndef E01_ST_H
    #define E01_ST_H
    #define MAXLEN 31
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    typedef struct st *ST;
    ST STinit(int N);
    void STfree(ST Stable);
    int STcount(ST Stable);
    void STprintName(ST Stable,  int index);
    int STgetIndex(ST Stable, char *identificatore);
    int STinsert(ST Stable, char *id);
    void STprint(ST Stable);

#endif //E01_ST_H
