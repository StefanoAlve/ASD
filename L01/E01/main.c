#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int CercaLettera(char *r, char c);
char *cercaRegexp(char *src, char *regexp);

int main() {
    char str[] = "Pippoflauto";
    char Rg[] = "P[^f]\\anR.d";
    char *p = cercaRegexp(str, Rg);

    while (*p != '\0'){
        printf("%c", *p++);
    }

    return 0;
}

char *cercaRegexp(char *src, char *regexp){
    int found = 0, appartenenza;
    char *s = src;
    while (*s != '\0'){
        char *rg = regexp;
        while(*rg != '\0' && !found){
            if (*rg == '['){
                appartenenza = CercaLettera(rg, *s);
                if (*(rg+1) == '^'){
                    if (appartenenza) found = 1;
                }
                else if (!appartenenza) found = 1;
            } else if (*rg == '\\'){
                rg++;
                if ((*rg == 'a' && isupper(*s)) || (*rg == 'A' && islower(*s))) found = 1;
            } else if (*rg != '.' && *rg != *s){
                found = 1;
            }
            s++; rg++;
        }
        if (!found) return src;
        src++; s = src;
    }
    return NULL;

}

int CercaLettera(char *r, char c){

}