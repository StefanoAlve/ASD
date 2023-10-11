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
    int i=0, j=0, flagUg=1, avanzaSrc=1, regexpLenght= cercaLenghtRegexp(regexp);

    for (i=0; i< strlen(src); i++){             //itero sorgente
        for (j=0; regexp+j != "\0" && flagUg != 0 && avanzaSrc != 0;j++) {           //itero regexp

            if (regexp+j == src+i) {            //ricerca uguaglianza
                flagUg=0;
            }


            if (flag){
                avanzaSrc=0;                //condizione uscita dal for in j
            }
        }
        avanzaSrc=1;

    }


    return puntatore;
}

int cercaLenghtRegexp(char *regexp) {
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