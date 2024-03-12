//
// Created by gianb on 06/01/2024.
//

#ifndef E03_DATETIME_H
    #define E03_DATETIME_H
    #include <stdio.h>
    typedef struct{
        int anno;
        int mese;
        int giorno;
    }data_s;
    typedef struct{
        int hh;
        int mm;
    }ora_s;
    typedef struct{
        data_s data;
        ora_s ora;
    }dateTime_s;
    dateTime_s leggiDateTime(FILE *fp);
    dateTime_s minData();
    dateTime_s maxData();
    int confrontaData(dateTime_s dateTime1, dateTime_s dateTime2);
    int confrontaOra(dateTime_s dateTime1, dateTime_s dateTime2);
    int confronta_data_e_ora(dateTime_s dateTime1, dateTime_s dateTime2);
    void displayData(data_s data);
    void displayOra(ora_s ora);
    void displayDateTime(dateTime_s dateTime);
#endif //E03_DATETIME_H
