#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int TrovaCollanaMax(int len_max, int z, int r, int t, int s, char *sol, int pos);

int main() {
    int z,r,t,s,len_max=0,MAX=0,pos=0;
    char *sol=NULL;

    printf("Inserire il numero di pietre per tipo nel formato seguente:\n");
    printf("<zaffiri> <rubini> <topazi> <smeraldi>\n\n");
    scanf("%d %d %d %d",&z,&r,&t,&s);

    MAX = z+r+t+s;

    sol = malloc((MAX+1)* sizeof(char ));

    len_max = TrovaCollanaMax(len_max,z,r,t,s,sol,pos);
    printf("La collana è lunga %d", len_max);

    return 0;
}

int TrovaCollanaMax(int len_max, int z, int r, int t, int s, char *sol, int pos){
    int max = 0;

    









    return len_max;
}