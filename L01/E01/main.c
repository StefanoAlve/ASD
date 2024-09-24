#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int CercaLettera(char *r, char c);
char *cercaRegexp(char *src, char *regexp);

int main() {
    char str[] = "PipPoflauto";
    char Rg[] = "a.[rftg]\\a";
    char *p = cercaRegexp(str, Rg);
    if (p != NULL){
        while (*p != '\0'){
            printf("%c", *p++);
        }
    }

    return 0;
}

char *cercaRegexp(char *src, char *regexp){
    int appartenenza;
    char *s = src;
    while (*s != '\0'){
        int found = 0;
        char *rg = regexp;
        while(*rg != '\0' && !found){
            if (*rg == '['){
                appartenenza = CercaLettera(rg, *s);
                if (*(rg+1) == '^'){
                    if (appartenenza) found = 1;
                }
                else if (!appartenenza) found = 1;
                while(*rg != ']') rg++;
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
    int find = 0;
    char *pr = r;
    while(!isalpha(*pr)) pr++;
    while(*pr != ']'){
        if (*pr++ == c) find = 1;
    }
    return find;
}