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
    int lenght = 0, flag = 1;

    for (int i = 0; i <= strlen(regexp); i++) {
        if (regexp[i] == '[') {
            i++;
            while (regexp[i]!=']'){
                if (regexp[i] != '^'){
                    lenght++;
                }
                i++;
            }
        }

        if ( regexp[i] == '\a' || regexp[i] == 'A'|| regexp[i] == ']') {//verifica se il carattere è un metacarattere, se lo è incrementa l'indice della stringa ed effettua controllo sui caratteri successivi
            i++;

            while(regexp[i] != '[' && regexp[i] != '\a' && regexp[i] != 'A' && regexp[i] != '\000' ){
                lenght++;
                i++;
                flag = 0;
            }

            if(flag){ //se ho un metacarattere ma non entro nel ciclo while, torno indietro di 1 per verificare i caratteri nella giusta successione
                i--;
            }
        }

        if (regexp[i] != '[' && regexp[i] != '\a' && regexp[i] != 'A' && x != ']' && regexp[i] != '\000' ){
            lenght++; //nel caso in cui il primo carattere non entrasse in nessuno dei costrutti, viene contato come carattere valido
            //nel caso di uscita dal terzo if e quindi dal while prima di incrementare verifica se sia effettivamente un carattere valido
        }
        else if(regexp[i] == '['){//nel caso di uscita dal ciclo interno se mi trovo nella condizione di regexp[i]
            i--;                     //devo tornare indietro di un indice affinche i controlli successivi siano corretti
        }

    }
    return lenght;
}
