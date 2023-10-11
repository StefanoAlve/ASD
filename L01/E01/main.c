#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXS 100

char *cercaRegexp(char *src, char *regexp);
int cercaLenghtRegexp(char *regexp);

int main() {
    char src[MAXS], regexp[MAXS], *pRegext;

    printf("inserire la stringa da ricercare: ");
    scanf("%s", regexp);
    printf("inserire la stringa da controllare: ");
    scanf("%s", src);
}

char *cercaRegexp(char *src, char *regexp) {
    char *puntatore = NULL;
    int i, j, k, contaparentesi=0, inizio=0, flagUg=1, avanzaSrc=1, regexpLenght = cercaLenghtRegexp(regexp);

    if (regexpLenght < strlen(src)) {
        for (i = 0; i < strlen(src); i++) {             //itero sorgente
            for (j = 0; j<regexpLenght && flagUg != 0; j++) {           //itero regexp

                // caso del punto (.)
                if (regexp[j] == '.')
                    flagUg=0;

                // caso \a \A
                else if (regexp[j] == '\\') {

                    if(regexp[j+1] == 'A' && isupper(src[i]) || regexp[j+1] == 'a' && islower(src[i])) {
                        flagUg = 0;
                        j++;            //aumento per saltare la a
                    }
                }
                // caso []
                else if (regexp[j] == '[' && regexp[j+1] != '^') {

                    for (k=0; regexp[j+1+k] != ']' && flagUg!=0; k++){          //itero dentro la parentesi
                        if (regexp[j+k+1] == src[i])
                            flagUg=0;
                        contaparentesi++;
                    }

                }


            }


        }
    }


    return puntatore;
}

int cercaLenghtRegexp(char *regexp) {//
    int lenght = 0, j;
    for (j = 0; j < strlen(regexp); j++)
    {
        if (regexp[j] == '[')
        {
            while (regexp[j] != ']')
                j++;
            lenght++;
        }
        else if (regexp[j] == '.' || isalpha(regexp[j]))
            lenght++;
        else if (regexp[j] == '\\' && (regexp[j+1] == 'a' || regexp[j+1] == 'A'))
        {
            lenght++;
            j = j+1;
        }
    }
    return lenght;
}