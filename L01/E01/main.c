#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int CercaLettera(char *r, char c);
char *cercaRegexp(char *src, char *regexp);

int main() {
    char str[] = "VivaLanostraFiga";
    char Rg[] = "[ìknaE].[^dtfl]\\a";
    char *p = cercaRegexp(str, Rg);

    //Stampa della corrispondenza trovata di Rg in str, puntata da p
    if (p != NULL){
        while (*p != '\0'){
            printf("%c", *p++);
        }
    } else {
        printf("Nessuna corrispondenza trovata\n");
    }

    return 0;
}

//La funzione valuta tutti i casi in cui non vi è corrispondenza e attraverso
//il flag found permette cosi di passare al carattere successivo di src e ricominciare
//la ricerca. Per semplicità si suppone che regexp sia nel formato corretto
char *cercaRegexp(char *src, char *regexp){
    int appartenenza;
    char *s = src; //s è usato internamente al 2 while per controllare i caratteri
    while (*s != '\0'){
        int found = 0;
        char *rg = regexp; //rg mi fa muovere lungo i caratteri della regexp per il controllo della corrispondenza
        while(*rg != '\0' && !found){
            //fintanto che non ci sono caratteri della regexp da controllare e non ho trovato alcun errore, continuo la verifica
            //della presenza della regexp in src
            if (*rg == '['){
                //poichè all'inteerno della quadra posso avere più caratteri da controllare, lo
                //faccio fare a una funzione esterna
                appartenenza = CercaLettera(rg, *s);
                //a seconda se il successivo carattere è ^, l'errore è trovato se *s è presente o meno nelle quadre
                if (*(rg+1) == '^'){
                    if (appartenenza) found = 1;
                }
                else if (!appartenenza) found = 1;
                while(*rg != ']') rg++; //sposto rg fino al carattere ]
            } else if (*rg == '\\'){
                rg++;
                //l'if controlla, a seconda del carattere *rg, che il carattere *s di src sia maiusc o minusc rilevando l'errore
                if ((*rg == 'a' && isupper(*s)) || (*rg == 'A' && islower(*s))) found = 1;
            } else if (*rg != '.' && *rg != *s){
                //dopo tutti i controlli c'è errore solo se i due caratteri sono diversi e *rg non è .
                found = 1;
            }
            //incremento dei puntatori
            s++; rg++;
        }
        //se è stato trovato almeno un errore allora ritorna il puntatore al carattere di src da cui
        //è partita la verifica di corrispondenza di regexp, altrimenti incremento src e aggancio s a src
        if (!found) return src;
        src++; s = src;
    }
    return NULL;

}

//La funzione ritorna 0 se c non è presente all'interno della serie di caratteri dentro le quadre di r,
//1 altrimenti
int CercaLettera(char *r, char c){
    int find = 0;
    char *pr = r;
    while(!isalpha(*pr)) pr++; //faccio scorrere r fino al primo carattere alfabetico
    while(*pr != ']'){
        if (*pr++ == c) find = 1;
    }
    return find;
}