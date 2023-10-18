#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXN 30

typedef struct{
    char codiceTratta[MAXN];
    char partenza[MAXN];
    char destinazione[MAXN];
    char data[MAXN];
    char o_partenza[MAXN];
    char o_arrivo[MAXN];
    int ritardo;
} struct_tratte;

typedef enum {
    stampa_log, ord_data_ora, ord_codTratta, ord_partenza, ord_destinazione, search_tratta_partenza, invalid
} comando_e;

int main() {

    return 0;
}
