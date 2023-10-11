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
    int i, j, k,uguale=0, contaparentesi=0, inizio=0, flag=1, avanzaSrc=1, regexpLenght = cercaLenghtRegexp(regexp);

    if (regexpLenght < strlen(src)) {
        for (i = 0; i < strlen(src) && flag!=2; i++) {             //itero sorgente
            for (j = 0; j<regexpLenght && flag!=0; j++) {           //itero regexp

                // caso del punto (.)
                if (regexp[j] == '.')
                    flag=0;

                // caso \a \A
                else if (regexp[j] == '\\') {

                    if(regexp[j+1] == 'A' && isupper(src[i]) || regexp[j+1] == 'a' && islower(src[i])) {
                        flag = 0;
                        j++;            //aumento per saltare la a
                    }
                }

                // caso []
                else if (regexp[j] == '[' && regexp[j+1] != '^') {

                    for (k=1; regexp[j+k] != ']' && flag != 0; k++){          //itero dentro la parentesi
                        if (regexp[j+k] == src[i])
                            flag=0;
                        contaparentesi++;
                    }
                    j=j+contaparentesi;  //salto tutti i caratteri dentro le parentesi + la parentesi finale
                }

                // caso [^]
                else if (regexp[j] == '[' && regexp[j+1] == '^') {
                    flag = 0;
                    for (k=2; regexp[j+k] != ']' && flag == 0; k++){          //itero dentro la parentesi
                        if (regexp[j+k] == src[i])
                            flag=1;
                        contaparentesi++;
                    }
                    j=j+contaparentesi;  //salto tutti i caratteri dentro le parentesi + la parentesi finale
                }

            }

            if (flag == 1)          // condizione per ripartire con la conta caratteri uguali
                uguale = 0;

            if (flag==0&& inizio==0) {   //condizione per trovare indice inizio e contare i caratteri giusti
                inizio = i;
                uguale++;
                flag=1;
            }
            if(flag==0){                   //condizione per contare caratteri uguali
                uguale++;
            }

            flag=1;
            if(uguale == regexpLenght){                       // condizione di trovata uguaglianza
                flag = 2;
            }


        }
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