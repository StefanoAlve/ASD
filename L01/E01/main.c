#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAXN 50

// Prototipi delle funzioni
char *cercaRegexp(char *src, char *regexp);
int controlloCondizioni(char **pippo, char **pluto);
int validitaStringa(char *p_stringa);
int validitaEspReg(char *p_espreg);

int main() {
    char str[MAXN], RegExp[MAXN], *p_str;
    int pos = 0;

    // Input della stringa e dell'espressione regolare
    printf("Digitare la stringa senza spazi: (Max 50 caratteri)\n");
    scanf("%s", str);
    printf("Inserire l'espressione regolare:\n");
    scanf("%s", RegExp);

    // Verifica la validità della stringa
    if (!validitaStringa(str)){
        printf("Caratteri in stringa non validi");
        return 0;
    }

    // Verifica la validità dell'espressione regolare
    if (!validitaEspReg(RegExp)){
        printf("Caratteri in espressione regolare non validi");
        return 0;
    }

    // Cerca l'espressione regolare nella stringa
    p_str = cercaRegexp(str, RegExp);
    if (p_str == NULL){
        printf("NULL: Nessuna corrispondenza o sintassi espressione regolare non valida");
    } else {
        pos = (strlen(str) - strlen(p_str)) + 1; //individuo la posizione del puntatore in cui è presente il primo riscontro
        printf("L'espressione regolare ha trovato riscontro alla lettera: %c (posizione %d)", *p_str, pos);
    }
    return 0;
}

// Funzione per verificare la validità della stringa
int validitaStringa(char *p_stringa){
    while (*p_stringa != '\0'){
        if (!isupper(*p_stringa) && !islower(*p_stringa)){
            return 0;
        }
        p_stringa++;
    }
    return 1;
}

// Funzione per verificare la validità dell'espressione regolare
// (controlla che non siano presenti caratteri non previsti)
int validitaEspReg(char *p_espreg){
    while (*p_espreg != '\0'){
        if (*p_espreg != '.' && *p_espreg != '\\' && *p_espreg != '[' && *p_espreg != ']' && *p_espreg != '^' && !isupper(*p_espreg) && !islower(*p_espreg)){
            return 0;
        }
        p_espreg++;
    }
    return 1;
}

// Funzione per cercare l'espressione regolare nella stringa
char *cercaRegexp(char *src, char *regexp){
    int trovata = 0, vero, cont = 0; // cont serve per capire di quante lettere far retrocedere il puntatore quando necessario
    char *espReg;
    espReg = regexp; // il puntatore espReg serve per tornare all'inizio di RegExp quando non trova riscontri

    while (*regexp != '\0' && *src != '\0'){
        vero = controlloCondizioni(&src, &regexp); // vero mi dice se trovo riscontri o meno nella funzione chiamata
        if (vero == 2){
            return NULL;
        }
        if (vero == 1){
            trovata = 1;
            cont++;
        } else {
            src = src - cont; // faccio retrocedere il puntatore al primo carattere che non verifica la condizione della espr reg
            regexp = espReg; // faccio ripartire il puntatore della espr reg dal primo carattere per il nuovo ciclo di verifa condizini
            cont = 0;
            trovata = 0;
        }
    }

    // non vi è nessun riscontro se non ho finito di controllare l'espressione regolare
    if (*regexp != '\0' && *src == '\0'){
        return NULL;
    }

    if (trovata){
        src = src - cont; // posiziono il puntatore al 1 carattere che verifica tutta l'espr reg
        return src;
    } else {
        return NULL;
    }
}

// Funzione per il controllo delle condizioni dell'espressione regolare
// se ritorna 2 significa che è stato trovato un errore di sintassi nella espressione regolare
// pippo è il puntatore al puntatore a str, mentre pluto è il puntatore al puntatore a RegExp
int controlloCondizioni(char **pippo, char **pluto) {
    int a = 0; // mi consente di individuare il riscontro positivo nel controllo delle quadre con più caratteri possibili

    if (isupper(**pluto) || islower(**pluto)) {
        if (**pippo == **pluto) {
            (*pluto)++;
            (*pippo)++;
            return 1;
        }
    }
    if (**pluto == '.') {
        (*pluto)++;
        (*pippo)++;
        return 1;
    }
    if (**pluto == '\\') {
        (*pluto)++;
        if (**pluto == 'a') {
            if (islower(**pippo)) {
                (*pluto)++;
                (*pippo)++;
                return 1;
            }
        }
        if (**pluto == 'A') {
            if (isupper(**pippo)) {
                (*pluto)++;
                (*pippo)++;
                return 1;
            }
        } else {
            return 2;
        }
    }
    if (**pluto == ']'){
        return 2;
    }
    if (**pluto == '['){
        (*pluto)++;
        if (**pluto == '^'){
            (*pluto)++;
            if (!isupper(**pluto) && !islower(**pluto)){
                return 2;
            }
            if (**pippo != **pluto){
                (*pluto)++;
                if (**pluto != ']'){
                    return 2;
                } else {
                    (*pluto)++; // muovo il puntatore al primo carattere != da ]
                    (*pippo)++;
                    return 1;
                }
            }
        }
        if (**pluto != '^'){
            if (!isupper(**pluto) && !islower(**pluto)){
                return 2;
            }
            while (**pluto != ']'){
                if (**pippo == **pluto){
                    a = 1;
                }
                (*pluto)++;
            }
            (*pluto)++; // muovo il puntatore al primo carattere != da ]
            (*pippo)++;
            return a;
        }
    }
    (*pippo)++; // sposto il puntatore al carattere successivo in caso di nessun riscontro
    return 0;
}
