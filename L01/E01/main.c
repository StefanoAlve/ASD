#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXL 100

char *cercaRegexp(char *src, char *regexp, int regexp_lenght);
int cercaLenghtRegexp(char *regexp);


int main(void){
    //Inizializzazione variabili
    char source[MAXL], *regexpPointer, regexp[MAXL];
    int lenght;
    //Corpo programma
    printf("Inserisci la stringa sorgente da cercare:");
    gets(source);
    printf("Inserisci l'espressione regolare da cercare:");
    scanf("%s", regexp);
    lenght = cercaLenghtRegexp(regexp);
    printf("La regular expression e' lunga: %d", lenght);
    regexpPointer = cercaRegexp(source, regexp, lenght);
    printf("\nIl puntatore indica la prima occorrenza regolare:%s", regexpPointer);
    return 0;
}



char *cercaRegexp(char *src, char *regexp, int regexp_lenght){
    int i,j = 0, pos, equals = 0, flag, uscita;
    char* regexpPointer = NULL;
    if (strlen(src)-regexp_lenght >= 0){
        for (i = 0; i <= strlen(src) - regexp_lenght; i++){ //Fisso la lettera della stringa da cui iniziare la ricerca
            pos = 0;
            uscita = 0;
            while(regexp[j] != '\0' && !uscita){ //Eseguo l'analisi della stringa
                flag = 0;
                /// CASO UGUAGLIANZA SEMPLICE
                if(regexp[j] == src[i+pos])
                    flag = 1;
                /// CASO '.'
                if(regexp[j] == '.' && (isalpha(src[i+pos]) || isalnum(src[i+pos])))
                    flag = 1;
                /// CASO '\A' o '\a'
                else if(regexp[j] == '\\'){
                    j++; // considero il carattere A o a
                    if(regexp[j] == 'A' && isupper(src[i+pos]))
                        flag = 1;
                    else if(regexp[j] == 'a' && islower(src[i+pos]))
                        flag = 1;
                }
                /// CASI []
                else if(regexp[j] == '['){
                    j++; // considero il carattere successivo
                    /// CASO CON APICE [^]
                    if(regexp[j] == '^'){
                        flag = 1; j++; // considero il carattere successivo all'apice
                        for (int k = j; regexp[k] != ']' && flag; k++){
                            if(regexp[k] == src[i+pos])
                                flag = 0;
                            j++; // sia k che j alla fine del ciclo saranno pari a regexp[k] = ']'
                        }
                    }
                        /// CASO []
                    else{
                        for (int k = j; regexp[k] != ']'; k++){
                            if(regexp[k] == src[i+pos])
                                flag = 1;
                            j++; // sia k che j alla fine del ciclo saranno pari a regexp[k] = ']'
                        }
                    }
                }
                /// CONDIZIONI
                if(flag){
                    j++;
                    pos++;
                    equals++;
                }
                else{
                    equals = 0;
                    uscita = 1;
                    j = 0;
                }
            }
            if (equals == regexp_lenght){ //Se ho trovato tanti caratteri corrispondenti quanto la lunghezza dell'espressione regolare allora faccio puntare al primo carattere della parola trovata
                regexpPointer=&src[i];
                return regexpPointer;
            }
        }
    }
    else
        printf("\nErrore, impossibile confrontare la stringa e l'espressione regolare.");
    return regexpPointer;
}

int cercaLenghtRegexp(char *regexp) {
    // DETERMINO LA LUNGHEZZA DELL'ESPRESSIONE "REGOLARE" DA CERCARE
    int lenght = 0, j;
    for (j = 0; j < strlen(regexp); j++){
        if (regexp[j] == '['){
            while (regexp[j] != ']')
                j++;
            lenght++;
        }
        else if (regexp[j] == '.' || isalpha(regexp[j]))
            lenght++;
        else if (regexp[j] == '\\' && (regexp[j+1] == 'a' || regexp[j+1] == 'A')){
            lenght++;
            j = j+1;
        }
    }
    return lenght;
}