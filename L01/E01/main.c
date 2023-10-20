#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXS 100

char *cercaRegexp(char *regexp, char *source);
int cercaLenghtRg(char *regexp);

int main() {
    char regexp[MAXS], sorgente[MAXS], *pRegext;
    int lenght;

    printf("inserire la stringa da controllare: ");
    scanf("%s", sorgente);
    printf("inserire la stringa da cercare: ");
    scanf("%s", regexp);
    lenght = cercaLenghtRg(regexp);
    printf("La regular expression e' lunga: %d", lenght);
    pRegext = cercaRegexp(regexp, sorgente);
    printf("\nIl puntatore indica la prima occorrenza regolare:%s", pRegext);
    return 0;
}

char *cercaRegexp(char *regexp, char *source) {
    char *puntatore = NULL;
    int i, j,inreg=0,inisrc=0, k,uguale=0, contaparentesi=0, inizio=0, flag=1, avanzaSrc=1, regexpLenght = cercaLenghtRg(regexp);

    if (regexpLenght >= strlen(regexp)) {
        for (i = inisrc; i < regexpLenght && flag != 2; i++) {             //itero sorgente
            for (j = inreg; j<= strlen(source) && flag!=0; j++) {           //itero source

                // caso del punto (.)
                if (source[j] == '.') {
                    flag = 0;
                    inreg = j;
                }


                // caso \a \A
                else if (source[j] == '\\') {

                    if(source[j + 1] == 'A' && isupper(regexp[i]) || source[j + 1] == 'a' && islower(regexp[i])) {
                        flag = 0;
                        j++;            //aumento per saltare la a
                    }
                    inreg = j;
                }

                // caso []
                else if (source[j] == '[' && source[j + 1] != '^') {

                    for (k=1; source[j + k] != ']' ; k++){          //itero dentro la parentesi
                        if (source[j + k] == regexp[i] && flag != 0)
                            flag=0;
                        else{
                            if(flag != 0) {
                                flag = 1;
                            }
                        }
                        contaparentesi++;
                    }
                    j=j+contaparentesi+1;  //salto tutti i caratteri dentro le parentesi + la parentesi finale
                    inreg = j;
                }

                /// caso [^]
                else if (source[j] == '[' && source[j + 1] == '^') {
                    flag = 0;
                    for (k=2; source[j + k] != ']'; k++){          ///itero dentro la parentesi
                        if (source[j + k] == regexp[i])
                            flag=1;
                        contaparentesi++;
                    }
                    j=j+k;  ///salto tutti i caratteri dentro le parentesi + la parentesi finale
                    inreg = j;
                }
                    /// UGUAGLIANZA SEMPLICE
                else if (source[j] == regexp[i]) {
                    flag = 0;
                    inreg = j;
                }

                if (flag == 1)          // condizione per ripartire con la conta caratteri uguali
                    uguale = 0;

            }



            if (flag==0&& inizio==0) {   //condizione per trovare indice inizio e contare i caratteri giusti
                inizio = inreg;
                uguale++;
                flag=1;
                inreg++;
            }
            if(flag==0){                   //condizione per contare caratteri uguali
                uguale++;
                inreg++;
            }

            flag=1;
            if(uguale == (int) strlen(regexp)){                       // condizione di trovata uguaglianza
                flag = 2;
                puntatore = &source[inizio];
            }


        }
    }

    return puntatore;
}

int cercaLenghtRg(char *regexp) {
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
        else if (regexp[j] == '\\' && (regexp[j + 1] == 'a' || regexp[j + 1] == 'A'))
        {
            lenght++;
            j = j+1;
        }
    }
    return lenght;
}