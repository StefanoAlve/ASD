#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXL 100

char *cercaRegxp(char *src, char *regexp); //src stringa da cercare ,regexp espressione regolare da cercare
int lunghezzaRegexp(char *regexp); //CERCA LA LUNGHEZZA DELLA REG



int main(){

    char source[] = {"ciao"}, *regExpPointer, regexp[]= {"\A[aeiou]5t[123]"};
    int x = 0 ;

    //printf("\nInserisci la stringa in cui cercare: ");
    //scanf("%s", source);
    //printf("\nInserisci l'espressione regolare da cercare: ");
    //scanf("%s", regexp);
    //cercaRegxp(source, regexp);
    x = lunghezzaRegexp(&regexp);
    printf("%d", x);


}

//in una regexpression se ho . indica un carattere, va contato nella lunghezza della regexpression

char *cercaRegxp(char *src, char *regexp){
    int i, j, k, flag = 0; //flag utilizzato per terminare la ricerca nell'espressione
    int lunghezza_regexp = strlen(regexp), lunghezza_src = strlen(src);
    char *x;

    //utilizzo prima un ciclo esterno per muovermi nella regexp
    for(i = 0; i <= lunghezza_regexp; i ++){
        if(regexp != '.'){
            for(j = 0; j <= lunghezza_src; j++ ){

            }
        }
    }
}



int lunghezzaRegexp(char *regexp) {
    int lenght = 0, i = 0, flag = 1;
    char x;

    for (i = 0; i <= strlen(regexp); i++) {
        x = regexp[i];
        if (regexp[i] == '[') {
            i++;
            while (regexp[i] != ']') {
                /*x = regexp[i];
                if(x == ']'){
                    flag = 0;
                }*/
                x = regexp[i];
                if (regexp[i] != '^' & regexp[i] != '[' & regexp[i] != ']') {
                    lenght++;
                }
                i++;
            }
        }


        x = regexp[i];
        if (regexp[i] == '\a' || regexp[i] == '\A' || regexp[i] == ']') {
            i++;
            while (regexp[i] != '[' & regexp[i] != '\0') {
                x = regexp[i];
                lenght++;
                i++;
            }
        }

    }
}