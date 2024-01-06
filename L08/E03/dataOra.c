#include "dataOra.h"

dataOra_s leggiDataOra(FILE *fp){
    dataOra_s dataOra;
    scanf("%d/%d/%d %d:%d", &dataOra.data.anno, &dataOra.data.mese, &dataOra.data.giorno, &dataOra.ora.ore, &dataOra.ora.minuti);
    return dataOra;
}
int confrontaDate(data_s d1, data_s d2){
    int data1, data2;
    data1 = d1.giorno+d1.mese*100+d1.anno*10000;
    data2 = d2.giorno+d2.mese*100+d2.anno*10000;
    if(data1>data2){
        return 1;
    }else if(data1 == data2){
        return 0;
    }
    return -1;
}
int confrontaOre(ora_s h1, ora_s h2){
    int ora1, ora2;
    ora1 = h1.ore*3600 + h1.minuti*60;
    ora2 = h2.ore*3600 + h2.minuti*60;
    if(ora1>ora2){
        return 1;
    }else if(ora1 == ora2){
        return 0;
    }
    return -1;
}
int confrontaDateOre(dataOra_s dH1, dataOra_s dH2){
    int flag1, flag2;
    flag1 = confrontaDate(dH1.data, dH2.data);
    if(flag1 > 0){
        return 1;
    }else if(flag1<0) {
        return -1;
    }
    flag2 = confrontaOre(dH1.ora, dH2.ora);
    if(flag2 > 0){
        return 1;
    }else if(flag2 == 0){
        return 0;
    }
    return -1;
}
void stampaData(data_s data){
    printf("%d/%d/%d ", data.anno, data.mese, data.giorno);
}
void stampaOra(ora_s ora){
    printf("%d:%d", ora.ore, ora.minuti);
}
void stampaDataOra(dataOra_s dataOra){
    stampaData(dataOra.data);
    stampaOra(dataOra.ora);
    printf("\n");
}