#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXR 1000
#define MAXN 30

typedef enum{r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_fine}comando_e;

typedef struct{
    char codt[MAXN];
    char partenza[MAXN];
    char destinazione[MAXN];
    char data[MAXN];
    char oraP[MAXN];
    char oraA[MAXN];
    int ritardo;
}s_tratta;

int LeggiFile(FILE *fp, s_tratta tratte[MAXN]);

int main(){
    FILE *fin = fopen("corse.txt", "r");
    s_tratta V_Tratte[MAXR];
    int N_Tratte = 0;

    if (fin == NULL) {printf("Errore apertura file\n"); return 1;}
    N_Tratte = LeggiFile(fin, V_Tratte);
    fclose(fin);



    return 0;
}

int LeggiFile(FILE *fp, s_tratta tratte[MAXN]){
    int n = 0;

    fscanf(fp, "%d", &n);

    for (int i = 0; i < n; i++){
        fscanf(fp, "%s %s %s %s %s %s %d", tratte[i].codt, tratte[i].partenza, tratte[i].destinazione, tratte[i].data, tratte[i].oraP, tratte[i].oraA, &tratte[i].ritardo);
    }

    return n;
}