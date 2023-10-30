#include <stdio.h>
#include <string.h>

#define DimMAX 101
char *cercaRegexp(char *src, char *regexp){
    char *p;
    char *preg;
    p = src;
    preg = regexp;
    int ok = 0;
    int len = strlen(p);

    if ((char) preg[0] == '.') {
        for (int i = 0; i < len; i++) {
            if (strcmp(p, preg) > 0) {
                printf("%c", p[i]);
            }
        }
    }

}
int main() {
    FILE *fin;
    char parola[DimMAX];
    char frase[DimMAX];
    char regexp[DimMAX];

    fin=fopen("../text.txt","r");


    if (fin ==NULL)
        printf("Errore in apertura!");
    else
        fscanf(fin,"%s %[^\n]s",regexp,frase);
    fclose(fin);
    //printf("%s \n%s",regexp,frase);
    cercaRegexp(frase,regexp);

}
