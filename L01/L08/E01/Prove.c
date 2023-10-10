#include <stdio.h>

int textStats(char* filename){
    FILE *fp_read;
    int maxC=20, caratteri[maxC],lunghezza, maiuscolo, vocali=0, paroleMaiuscolo=0,parole=0,carattere=0;
    float percentuale,numeroMedio;
    char parola[maxC];

    //Apertura file
    fp_read=fopen(filename,"r");
    if(fp_read==NULL){
        return 1;
    }
    else{
        //Corpo programma
        for(i=0;i<maxC;i++){
            caratteri[i]=0;
        }
        while(!feof(fp_read)){
            lunghezza=0;
            maiuscolo=1;
            fscanf(fp_read,"%s",parola);
            parole+=1;
            lunghezza=strlen(parola);
            caratteri[lunghezza]++;
            for(j=0;j<lunghezza;j++){
                carattere+=1;
                if(isupper(parola[j]!=1){
                    maiuscolo=0;
                }
                if(tolower(parola[j]=='a' || parola[j]=='e' || parola[j]=='i' || parola[j]=='o' || parola[j]=='u'){
                    vocali+=1;

                }
                if(maiuscolo == 1){
                    paroleMaiuscolo+=1;
                }
            }
        }

        for(k=1;k<maxC;k++){
            if(caratteri[k]>0)
                printf("%d string/s with length %d", caratteri[k],k);
        }

        percentuale=(paroleMaiuscolo/parole)*100;
        printf("%.2f% with all capital letters",percentuale);
        numeroMedio=vocali/carattere;
        printf("Avarage number of vowels: %.2f",numeroMedio);


    }

    //Chiusura file
    fclose(fp_read);

    return parole;

}