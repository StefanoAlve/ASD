#include <stdio.h>
#include <ctype.h>
#define MAX 51

int match(char *src, char *regexp);
char* cercaRegexp(char *src, char *regexp);
void parentesiQuadre(char **src, char **regexp, int *found);
void maiuscMinusc(char **src, char**regexp, int *found);

int main(){
    char src[MAX], regexp[MAX];

    //input
    printf("Inserisci stringa da trovare e espressione regolare:\n");
    scanf("%s %s", src, regexp);

    //corrispondenze
    char *corrispondenza = cercaRegexp(src, regexp);

    //output
    if (corrispondenza != NULL)
        printf("Corrispondenza trovata: %s\n", corrispondenza);
    else
        printf("Nessuna corrispondenza.\n");

    return 0;
}

//funzione principale per cercare un'espressione regolare in source
char* cercaRegexp(char *src, char *regexp){

    //itero interamente su src, carattere per carattere fino a NULL
    while(*src){
        if(match(src, regexp))
            return src; //restituisce il puntatore alla corrispondenza trovata

        //vado avanti in src
        src++;
    }
    return NULL; //nessuna corrispondenza trovata
}

//verifica se source corrisponde all'espressione regolare
int match(char *src, char *regexp) {
    int found = 1;

    //itero su tutta regexp
    while(*regexp && found){

        //il punto corrisponde a qualsiasi carattere, quindi continua la ricerca
        if(*regexp == '.')
            src++, regexp++;

            //Caso parentesi
        else if(*regexp == '['){
            //avanza di un carattere dopo '['
            regexp++;
            //gestione parentesi
            parentesiQuadre(&src, &regexp, &found);
        }
            //Caso \a oppure \A
        else if(*regexp == '\\'){
            //avanza dopo '\'
            regexp++;
            //gestione maiuscole/minuscole
            maiuscMinusc(&src, &regexp, &found);

        }

            //Controllo se si hanno gli stessi caratteri
        else if (*src != *regexp){
            found = 0; //carattere diverso, nessuna corrispondenza
        }

            //Se si ha corrispondenza si va avanti
        else
            //continua la ricerca
            src++, regexp++;
    }
    return found;
}

//Controllo carattere in presenza di parentesi quadre
void parentesiQuadre(char **src, char **regexp, int *found){

    if(**regexp == '^'){
        //il carattere successivo non deve essere presente
        (*regexp)++;

        while(**regexp != ']'){

            if (*src == *regexp)
                *found = 0; //il carattere non va bene

            (*regexp)++;
        }
    }
    else{
        *found = 0;
        //il carattere successivo deve essere presente
        while(**regexp != ']'){
            if(**src == **regexp)
                *found = 1; //il carattere va bene

            (*regexp)++;
        }
    }
    //avanti dopo ']'
    (*regexp)++, (*src)++;
}

void maiuscMinusc(char **src, char**regexp, int *found){

    //Controllo maiuscole nell'espressione regolare
    if(isupper(**regexp)){

        //se nella src non abbiamo una maiuscola found = 0
        if (!isupper(**src))
            *found = 0;
    }

        //Controllo minuscole
    else if(islower(**regexp)){

        //se nella frase non abbiamo una minuscola found = 0
        if(!islower(**src))
            *found = 0;
    }
    else
        *found = 0; //errore

    //dopo il controllo vado avanti
    (*src)++, (*regexp)++;
}
