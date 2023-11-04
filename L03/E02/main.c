#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 255
#define MAXC 100

typedef struct {
    int *canzoni;
    int num_canzoni;
}Canzoni_x_Amico;

int LeggiFile(char *NomeFile, Canzoni_x_Amico **p_Scelte, char **canzoni, int *p_TotCanzoni);

int main() {
    int A, TotCanzoni = 0, *p_TotCanzoni = &TotCanzoni;
    char NomeFile[MAXN], *canzoni[MAXC];
    Canzoni_x_Amico *Scelte, **p_Scelte = &Scelte;

    for (int i = 0; i < MAXC; i++){
        canzoni[i] = NULL;
    }

    printf("Inserire il nome del file:\n");
    scanf("%s",NomeFile);

    A = LeggiFile(NomeFile,p_Scelte,canzoni,p_TotCanzoni);


    return 0;
}


int LeggiFile(char *NomeFile, Canzoni_x_Amico **p_Scelte, char **canzoni, int *p_TotCanzoni){
    FILE *fp;
    int num_amici = 0, i = 0, j = 0;
    char canzone[MAXN];
    Canzoni_x_Amico *Scelte = NULL;

    fp = fopen(NomeFile,"r");
    if (fp != NULL){
        fscanf(fp,"%d",&num_amici);

        Scelte = (Canzoni_x_Amico *)malloc(num_amici* sizeof(Canzoni_x_Amico));

        while (fscanf(fp,"%d",&Scelte[i].num_canzoni) == 1){
            Scelte[i].canzoni = (int *) malloc(Scelte[i].num_canzoni* sizeof(int));
            while (j<(Scelte[i].num_canzoni + (*p_TotCanzoni))){
                fscanf(fp,"%s",canzone);
                canzoni[j] = strdup(canzone);
                printf("%s\n",canzoni[j]);
                Scelte[i].canzoni[j] = j;
                j++;
            }
            *p_TotCanzoni += Scelte[i].num_canzoni;
            i++;

        }
    } else {
        printf("ERRORE: Impossibile aprire il file\n");
    }
    *p_Scelte = Scelte;
    fclose(fp);
    return num_amici;
}
