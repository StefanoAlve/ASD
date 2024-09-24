#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char *cercaRegexp(char *src, char *regexp);

int main() {
    char str[] = "Pippoflauto";
    char Rg[] = "A[^f]\\anR.d";
    char *p = cercaRegexp(str, Rg);

    while (*p != '\0'){
        printf("%c", *p++);
    }

    return 0;
}

char *cercaRegexp(char *src, char *regexp){

}
