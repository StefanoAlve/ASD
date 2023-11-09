#include <stdio.h>
#include <stdlib.h>
#define MAXL 50



typedef struct{
    int val1;
    int val2;
}arcs;

void leggiFile(int *v, int *e, char nomefile[], arcs **archi);



///VERTEX COVER (I NODI DEVONO COPRIRE TUTTI GLI ARCHI)
int main() {
    int v, e, i;
    char nomefile[MAXL];
    arcs *archi;



    printf("inserire il nome del file in cui estrarre il grafo \t");
    scanf("%s", nomefile);

    leggiFile(&v, &e, nomefile, &archi);

    for (i = 0; i < e; i++){
        printf("arco %d : %d %d\n", i, archi[i].val1, archi[i].val2);
    }

    free(archi);
    return 0;
}


void leggiFile(int *v, int *e, char nomefile[], arcs **archi){
    FILE *fp;
    int i;


    if((fp = fopen(nomefile,"r"))==NULL){
        printf("errore in lettura file");
        exit(1);
    }

    fscanf(fp, "%d %d", v, e);

    *archi = (arcs *)malloc((*e)*sizeof(arcs ));

    for (i = 0; i < *e; i++){
        fscanf(fp, "%d %d", &((*archi)[i].val1), &((*archi)[i].val2));
    }


    fclose(fp);

}



