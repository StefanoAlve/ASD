#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXL 100

char *cercaRegexp(char *src, char *regexp);
int cercaLenghtRegexp(char *regexp);


int main(void)
{
    char source[MAXL], *regexpPointer, regexp[MAXL];
    int lenght = 0;

    printf("Inserisci la stringa sorgente da cercare:");
    gets(source);
    printf("Inserisci l'espressione regolare da cercare:");
    scanf("%s", regexp);
    lenght = cercaLenghtRegexp(regexp);
    printf("La regular expression è lunga: %d", lenght);
    regexpPointer = cercaRegexp(source, regexp);
    printf("\nIl puntatore indica la prima occorrenza regolare:%s", regexpPointer);
    return 0;
}



char *cercaRegexp(char *src, char *regexp)
{
    char* regexpPointer = NULL;
    int i, j, regexpLenght, flag, equals = 0, first = 1, pos = 0;
    // Cerco la lunghezza effettiva della Regular Expression:
    regexpLenght = cercaLenghtRegexp(regexp);
    if ((int)strlen(src) - regexpLenght >= 0) // Condizione utile per verificare che sia possibile cercare nella source
        for(i = 0; i < strlen(src) && equals != regexpLenght; i++) //verifico di non sforare la stringa e che non abbia trovato un match
        {
            flag = 0;
            for (j = pos; j < strlen(regexp) && !flag; j++)
            {
                /// CASO PUNTO
                if (regexp[j] == '.' && (isalpha(src[i]) || isdigit(src[i]))) // Se c'è un punto mi va bene qualsiasi carattere alfanumerico
                    flag = 1;
                    /// CASI /A E /a
                else if (regexp[j] == '\\')
                    if ((regexp[j + 1] == 'A' && isupper(src[i])) || (regexp[j + 1] == 'a' && islower(src[i])))
                    {
                        flag = 1;
                        pos++;
                    }
                        /// CASI PARENTESI QUADRE
                    else if (regexp[j] == '[')
                    {
                        if(regexp[j+1] == '^')
                        {
                            flag = 1;
                            for(int k = j+2; regexp[k] != ']'; k++) // Inizio a cercare dal carattere successivo all'apice
                            {
                                if(regexp[k] == src[i] && flag)
                                    flag = 0;
                                pos++;
                            }
                            pos+=2; //incrementa la posizione sia per l'^ che per la ]
                        }
                        else
                        {
                            for(int k = j+1; k < pos; k++) //[abc] aasa basa casa
                            {
                                if(regexp[k] == src[i] && !flag)
                                    flag = 1;
                                pos++;
                            }
                            pos++;
                        }
                    }
                        /// UGUAGLIANZA SEMPLICE
                    else if (regexp[j] == src[i])
                        flag = 1;
                /// GESTIONE DELLE CONDIZIONI
                if(flag) {
                    equals++;
                    pos++;
                }
                else {
                    equals = 0;
                    pos = 0;
                    flag = 1; // esce dal for più interno
                }
            }
            /// CASI DI MATCH
            if (equals == regexpLenght){
                if(first) {
                    printf("\nLe parole che contengono espressioni regolari sono:\n");
                    regexpPointer = &src[i - regexpLenght + 1];
                    first = 0;
                }
                for (int k = 0; k < regexpLenght; k++)
                    printf("%c", src[i-regexpLenght+1+k]);
                printf("; ");
                equals = 0;
                pos = 0;
            }
        }
    else
        printf("\nImpossibile ricercare l'espressione regolare nella stringa di origine");

    return regexpPointer;
}


// DETERMINO LA LUNGHEZZA DELLA STRINGA "REGOLARE" DA CERCARE
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