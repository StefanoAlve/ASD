#include "datetime.h"


dateTime_s leggiDateTime(FILE *fp)
{
    dateTime_s tmp;
    int anno,mese,giorno,hh,min;
    if(fp != NULL)
    {
        if(fp != stdin) {
            fscanf(fp, " %d/%d/%d %d:%d", &anno, &mese, &giorno, &hh, &min);
            tmp.data.anno = anno; tmp.data.mese = mese; tmp.data.giorno = giorno; tmp.ora.hh = hh; tmp.ora.mm = min;
        }
        else{
            fscanf(fp, " %d/%d/%d", &anno, &mese, &giorno);
            tmp.data.anno = anno; tmp.data.mese = mese; tmp.data.giorno = giorno; tmp.ora.hh = tmp.ora.mm = 0;
        }
    }
    else
        printf("\nErrore nell'apertura del file.");
    return tmp;
}
int confrontaData(dateTime_s dateTime1, dateTime_s dateTime2)
{
    int flag = 0;
    long int d1 = 0, d2 = 0;
    data_s data1 = dateTime1.data, data2=dateTime2.data;
    d1 = data1.anno*10000 + data1.mese*100 + data1.giorno;
    d2 = data2.anno*10000+ data2.mese*100+ data2.giorno;
    if(d1>d2)
        flag = 1;
    else if(d1<d2)
        flag = -1;
    else
        flag = 0;
    return flag;
}
int confrontaOra(dateTime_s dateTime1, dateTime_s dateTime2)
{
    int flag = 0;
    long int d1,d2;
    ora_s ora1 = dateTime1.ora,ora2 =dateTime2.ora;
    d1 = ora1.hh*3600+ora1.mm*60;
    d2 = ora2.hh*3600+ora2.mm*60;
    if(d1>d2)
        flag = 1;
    else if(d1<d2)
        flag = -1;
    else
        flag = 0;
    return flag;
}
int confronta_data_e_ora(dateTime_s dateTime1, dateTime_s dateTime2)
{
    int flag1,flag2, flagRes;
    flag1 = confrontaData(dateTime1, dateTime2);
    flag2 = confrontaOra(dateTime1, dateTime2);
    if(flag1 != 0)
        flagRes = flag1;
    else
        flagRes = flag2;
    return flagRes;
}
void displayData(data_s data){
    printf("%d/%d/%d ", data.anno, data.mese, data.giorno);
}
void displayOra(ora_s ora){
    printf("%d:%d", ora.hh, ora.mm);
}
void displayDateTime(dateTime_s dateTime){
    displayData(dateTime.data);
}


dateTime_s minData(){
    dateTime_s x;
    x.data.anno = 0; x.data.mese = 1; x.data.giorno = 1;
    x.ora.hh = 0;x.ora.mm = 0;
    return x;
}
dateTime_s maxData(){
    dateTime_s x;
    x.data.anno = 9999; x.data.mese = 12; x.data.giorno = 31;
    x.ora.hh = 23;x.ora.mm = 59;
    return x;
}