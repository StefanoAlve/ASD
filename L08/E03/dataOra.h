#ifndef E03_DATAORA_H
#define E03_DATAORA_H
#include <stdio.h>
typedef struct{
    int anno;
    int mese;
    int giorno;
}data_s;
typedef struct{
    int ore;
    int minuti;
}ora_s;
typedef struct{
    data_s data;
    ora_s ora;
}dataOra_s;

dataOra_s leggiDataOra(FILE *fp);
int confrontaDate(data_s d1, data_s d2);
int confrontaOre(ora_s h1, ora_s h2);
int confrontaDateOre(dataOra_s dH1, dataOra_s dH2);
void stampaData(data_s data);
void stampaOra(ora_s ora);
void stampaDataOra(dataOra_s dataOra);

#endif //E03_DATAORA_H
