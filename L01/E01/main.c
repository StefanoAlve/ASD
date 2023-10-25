#include <string.h>
#include <stdio.h>
#include <ctype.h>
#define MAXLENGTH 100
char *cercaRegexp(char *exp, char *regexp);
int main(void){
    char regexp[MAXLENGTH],exp[MAXLENGTH];
    char *regexPointer;
    printf("Cerca un'espressione regolare in una stringa.\n");
    printf("\nInserire stringa sorgente:");
    scanf("%s",exp);
    printf("\nInserire regular expression da ricercare:");
    scanf("%s",regexp);
    //prima di chiamare la funzione controllo correttezza dell'inserimento
    if(strlen(regexp)> strlen(exp)){
        printf("\nEspressione da cercare piu' lunga della sorgente.\nErrore.");
        return 1;
    }
    return 0;
}