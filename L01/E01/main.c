#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXL 100

char *cercaRegxp(char *src, char *regexp); //src stringa da cercare ,regexp espressione regolare da cercare
int lunghezzaRegexp(char *regexp); //CERCA LA LUNGHEZZA DELLA REG



int main(){

    char source[MAXL], *regExpPointer, regexp[MAXL];


    printf("\nInserisci la stringa in cui cercare: ");
    scanf("%s", source);
    printf("\nInserisci l'espressione regolare da cercare: ");
    scanf("%s", regexp);

    cercaRegxp(source, regexp);

}



char *cercaRegxp(char *src, char *regexp){
    int len ;
    return 0;
}
