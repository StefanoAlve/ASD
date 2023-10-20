#include <stdio.h>
#include <ctype.h>
#define MAX 51

int match(char *src, char *regexp);
char *cercaRegexp(char *src, char *regexp);

int main() {
    char source[MAX], regexp[MAX];

    //input
    printf("Inserisci stringa da trovare e espressione regolare:\n");
    scanf("%s %s", source, regexp);

    //corrispondenze
    char *corrispondenza = cercaRegexp(source, regexp);

    //output
    if (corrispondenza != NULL)
        printf("Corrispondenza trovata: %s\n", corrispondenza);
    else
        printf("Nessuna corrispondenza.\n");

    return 0;
}

//funzione principale per cercare un'espressione regolare in source
char *cercaRegexp(char *src, char *regexp){
    while (*src){
        if (match(src, regexp))
            return src; //restituisce il puntatore alla corrispondenza trovata
        src++;
    }
    return NULL; //nessuna corrispondenza trovata
}

//verifica se source corrisponde all'espressione regolare
int match(char *src, char *regexp){
    int found = 1;
    //itero su tutta regexp
    while (*regexp && found){

        //il punto corrisponde a qualsiasi carattere, quindi continua la ricerca
        if (*regexp == '.'){
            src++; regexp++;
        }

        else if (*regexp == '['){
            //avanza di un carattere dopo '['
            regexp++;

            if(*regexp == '^'){
                //il carattere successivo non deve essere presente
                regexp++;

                while(*regexp != ']'){

                    if (*src == *regexp)
                        found = 0; //il carattere non va bene

                    regexp++;
                }
            }
            else{
                found = 0;
                //il carattere successivo deve essere presente
                while(*regexp != ']'){

                    if(*src == *regexp)
                        found = 1; //il carattere va bene

                    regexp++;
                }
            }
            //avanti dopo ']'
            regexp++;
            src++;
        }

            // controllo maiuscole/minuscole
        else if(*regexp == '\\'){
            regexp++;

            //controllo maiuscole nell'espressione regolare
            if(isupper(*regexp)){

                //se nella frase non abbiamo una maiuscola found = 0
                if( !isupper(*src) )
                    found = 0;
            }

                //controllo minuscole
            else if(islower(*regexp)) {

                //se nella frase non abbiamo una minuscola found = 0
                if (!islower(*src))
                    found = 0;
            }
            else
                found = 0; //errore

            //dopo il controllo vado avanti
            src++;
            regexp++;
        }

        else if(*src != *regexp){
            found = 0; //carattere diverso, nessuna corrispondenza
        }
        else{
            //continua la ricerca
            src++;
            regexp++;
        }
    }
    return found;
}