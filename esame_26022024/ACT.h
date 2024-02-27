

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct activities *ACT;
ACT activityRead(FILE *fin );
typedef struct {
    char name[20];
    int tempo_inizio;
    int durata;
    int profitto;
} info;