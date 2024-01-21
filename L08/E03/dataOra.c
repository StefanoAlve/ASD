#include "dataOra.h"

dataOra_s leggiDataOra(FILE *fp){
    dataOra_s dataOra;
    if(fp!=stdin) {
        fscanf(fp, "%d/%d/%d %d:%d", &dataOra.data.anno, &dataOra.data.mese, &dataOra.data.giorno, &dataOra.ora.ore,
               &dataOra.ora.minuti);
    }
    else{
        fscanf(fp, "%d/%d/%d", &dataOra.data.anno, &dataOra.data.mese, &dataOra.data.giorno);
        dataOra.ora.ore = dataOra.ora.minuti = 0;
    }
    return dataOra;
}
int confrontaDate(dataOra_s d1, dataOra_s d2){
    int data1, data2;
    data1 = d1.data.giorno+d1.data.mese*100+d1.data.anno*10000;
    data2 = d2.data.giorno+d2.data.mese*100+d2.data.anno*10000;
    if(data1>data2){
        return 1;
    }else if(data1 == data2){
        return 0;
    }
    return -1;
}
int confrontaOre(dataOra_s D1, dataOra_s D2){
    int ora1, ora2;
    ora1 = D1.ora.ore*3600 + D1.ora.minuti*60;
    ora2 = D2.ora.ore*3600 + D2.ora.minuti*60;
    if(ora1>ora2){
        return 1;
    }else if(ora1 == ora2){
        return 0;
    }
    return -1;
}
int confrontaDateOre(dataOra_s dH1, dataOra_s dH2){
    int flag1, flag2;
    flag1 = confrontaDate(dH1, dH2);
    if(flag1 > 0){
        return 1;
    }else if(flag1<0) {
        return -1;
    }
    flag2 = confrontaOre(dH1, dH2);
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