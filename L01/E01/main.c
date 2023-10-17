#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXL 100

char *cercaRegxp(char *src, char *regexp); //src stringa da cercare ,regexp espressione regolare da cercare
int lunghezzaRegexp(char *regexp); //CERCA LA LUNGHEZZA DELLA REG

int main(){
    char source[MAXL] , *regExpPointer, regexp[MAXL];
    char *primaoccorrenza;

    printf("\nInserisci la stringa in cui cercare: ");
    scanf("%s", source);
    printf("\nInserisci l'espressione regolare da cercare: ");
    scanf("%s", regexp);

    primaoccorrenza = cercaRegxp(source, regexp);
    return 0;

}


char *cercaRegxp(char *src, char *regexp) {
    int lunghezza_src = strlen(src), lunghezza_regexp = lunghezzaRegexp(regexp);
    int flag1 = 1, flag2 = 1, flag3 = 1; //quando viene trovata la prima regexp fa terminare i cicli di confronto
    int pos = 0;//utilizzo pos per controllare quanti dei caratteri confrontati siano uguali
    //potrei introdurre un ulteriore flag per tenere traccia se ho trovato o no almeno una corrispondenza della regexp in src
    int prima = 1; //utilizzata per mantenere il valore della prima occorrenza della reg exp in src
    int j = 0, i, k = 0;
    char x, y;
    char *pPrimaOccorrenza = NULL;


    if ((lunghezza_src - lunghezza_regexp >= 0)) {//verifico che la lunghezza della regexp sia compatibile alla lunghezza della stringa in cui cerco
        for (j = 0; j <= (lunghezza_src - lunghezza_regexp) && flag1 && (strlen((src + j)) - lunghezza_regexp) >= 0; j++) { //mi permette di troncare i primi j caratteri da src
            flag3 = 1;
            prima = 1;
            k  = 0;
            for (i = 0; i <= lunghezza_regexp && flag1 && flag3; i++) {
                if (prima) {
                    pPrimaOccorrenza = &src[i+j];
                    prima = 0;
                }

                x = regexp[i+k];//incremento di un fattore k in caso incontrassi il caso [, il confronto viene eseguito correttamente dal carattere successivo a ]
                y = src[i+j];

                if (x == y && y != '\000' && x != '\000') {// caso di regexp più semplice, regexp e src sono la stessa stringa
                    flag1 = 1;
                    pos++;
                } else if (x == '.') {//qualsiasi carattere è valido ai fini della ricerca nella src
                    pos++;
                } else if (x == '\a' && islower(y)) {//se in src[i] ho un carattere minuscolo quando in regexp[i] ho \a, tale carattere è valido al conteggio della ricerca
                    pos++;
                } else if (x == 'A' && isupper(y)) {//se in src[i] ho un carattere maiuscolo quando in regexp[i] ho A, tale carattere è valido al conteggio della ricerca
                    pos++;
                } else if (x == '[') {
                    if (regexp[i + 1] == '^') {
                        for (k = i + 1; regexp[k] != ']' && flag2; k++) { //quando trova la prima corrispondenza termina il ciclo
                            if (regexp[k] != src[i] && regexp[k] != ']' && flag2) { //se ho già trovato una uguaglianza fra una delle lettere in [], non necessito ulteriori confronti
                                pos++;
                                flag2 = 0;
                            }
                        }
                    }
                    else{
                        for (k = i ; regexp[k] != ']' && flag2; k++) { //quando trova la prima corrispondenza termina il ciclo
                            x = regexp[k];
                            if (x == y && x != ']' && flag2) { //se ho già trovato una uguaglianza fra una delle lettere in  [], non necessito ulteriori confronti
                                pos++;
                                flag2 = 0;
                            }
                        }
                    }
                    if(regexp[k] != ']' && flag2 == 0) {
                        while (regexp[k] != ']') {
                            k++;
                        }
                        k = k-i;
                    }
                    else{k = k-i;}
                }
                else { pos = 0; flag3 = 0;}

                if (pos == lunghezza_regexp) { //se pos, e' uguale alla lunghezza della regexp la regexp è stata trovata in src
                    printf("la regexp e stata trovata");
                    return pPrimaOccorrenza;
                }
            }
        }
        printf("\nla regexp non e' stata trovata");
        pPrimaOccorrenza == NULL;
        return  pPrimaOccorrenza;
    }
    printf("\nla regexp da ricercare è più lunga della src");
    pPrimaOccorrenza == NULL;
    return pPrimaOccorrenza;
}

int lunghezzaRegexp(char *regexp){
    int lenght = 0, flag = 1;

    for (int i = 0; i <= strlen(regexp); i++) {
        if (regexp[i] == '[') {
            lenght++;
            while (regexp[i] != ']') {
                i++;
            }
        }
        if (regexp[i] ==
            ']') {//verifica se il carattere è un metacarattere, se lo è incrementa l'indice della stringa ed effettua controllo sui caratteri successivi
            i++;

            while (regexp[i] != '[' && regexp[i] != '\000') {
                lenght++;
                i++;
                flag = 0;
            }

            if (flag) { //se ho un metacarattere ma non entro nel ciclo while, torno indietro di 1 per verificare i caratteri nella giusta successione
                i--;
            }
        }

        if (regexp[i] != '[' && regexp[i] != ']' && regexp[i] != '\000') {
            lenght++; //nel caso in cui il primo carattere non entrasse in nessuno dei costrutti, viene contato come carattere valido
            //nel caso di uscita dal terzo if e quindi dal while prima di incrementare verifica se sia effettivamente un carattere valido
        } else if (regexp[i] =='[') {//nel caso di uscita dal ciclo interno se mi trovo nella condizione di regexp[i]
            i--;                     //devo tornare indietro di un indice affinche i controlli successivi siano corretti
        }

    }
    return lenght;
}
