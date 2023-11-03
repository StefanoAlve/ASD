#include <stdio.h>
#include <ctype.h>
#define MAX 51

int corrispondenza(char *src, char *regexp);
char* cercaRegexp(char *src, char *regexp);
void Par_Quadre(char **src, char **regexp, int *flag);
void maiuscMinusc(char **src, char**regexp, int *flag);

int main(){
    char src[MAX], regexp[MAX];

    //inserimento delle frasi
    printf("Inserisci frase da trovare e espressione regolare in cui cercare: \n");
    scanf("%s %s", src, regexp);

    //trovata
    char *trovata = cercaRegexp(src, regexp);

    //stampa se è stata trovata
    if (trovata != NULL)
        printf("Corrispondenza trovata: %s\n", trovata);
    else
        printf("Non è stato trovato niente\n");

    return 0;
}

//funzione per cercare la frase all'interno dell'espressione regolare
char* cercaRegexp(char *src, char *regexp){

    //controllo carattere per carattere fino a NULL
    while(*src){
        if(corrispondenza(src, regexp))
            return src; //restituisce il puntatore alla corrispondenza trovata

        //vado avanti nella frase
        src++;
    }
    return NULL; //nessuna corrispondenza trovata
}

//verifica se la frase inserita corrisponde all'espressione regolare
int corrispondenza(char *src, char *regexp) {
    int flag = 1;

    //itero su tutta l'espressione regolare
    while(*regexp && flag){

        //il punto corrisponde a qualsiasi carattere, quindi continua la ricerca
        if(*regexp == '.')
            src++, regexp++;

            //Caso parentesi
        else if(*regexp == '['){
            //avanza di un carattere dopo '['
            regexp++;
            //gestione parentesi
            Par_Quadre(&src, &regexp, &flag);
        }
            //Caso \a oppure \A
        else if(*regexp == '\\'){
            //avanza dopo '\'
            regexp++;
            //gestione maiuscole/minuscole
            maiuscMinusc(&src, &regexp, &flag);
        }

            //Controllo se si hanno gli stessi caratteri
        else if (*src != *regexp){
            flag = 0; //carattere diverso, nessuna corrispondenza
        }

            //Se si ha corrispondenza si va avanti
        else
            //continua la ricerca
            src++, regexp++;
    }
    return flag;
}

//Controllo carattere in presenza di parentesi quadre
void Par_Quadre(char **src, char **regexp, int *flag){

    if(**regexp == '^'){
        //il carattere successivo non deve essere presente
        (*regexp)++;

        while(**regexp != ']'){

            if (*src == *regexp)
                *flag = 0; //il carattere non va bene

            (*regexp)++;
        }
    }
    else{
        *flag = 0;
        //il carattere successivo deve essere presente
        while(**regexp != ']'){
            if(**src == **regexp)
                *flag = 1; //il carattere va bene

            (*regexp)++;
        }
    }
    //avanti dopo ']'
    (*regexp)++, (*src)++;
}

void maiuscMinusc(char **src, char**regexp, int *flag){

    //Controllo maiuscole nell'espressione regolare
    if(isupper(**regexp)){

        //se nella src non abbiamo una maiuscola flag = 0
        if (!isupper(**src))
            *flag = 0;
    }

        //Controllo minuscole
    else if(islower(**regexp)){

        //se nella frase non abbiamo una minuscola flag = 0
        if(!islower(**src))
            *flag = 0;
    }
    else
        *flag = 0; //errore

    //dopo il controllo vado avanti
    (*src)++, (*regexp)++;
}