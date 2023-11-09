#include <stdio.h>
#include <stdlib.h>
#define MAXL 50



typedef struct{
    int val1;
    int val2;
}arcs;

void leggiFile(int *v, int *e, char nomefile[], arcs **archi);
int controlloVortex(int *tmp, arcs *archi, int e, int v);
void insDellePart(int pos, int *tmp, arcs *archi, int e, int v);



///VERTEX COVER (I NODI DEVONO COPRIRE TUTTI GLI ARCHI)
int main() {
    int v, e, i, *nodi, *tmp, cont = 0, pos = 0;
    char nomefile[MAXL];
    arcs *archi;



    printf("inserire il nome del file in cui estrarre il grafo");
    scanf("%s", nomefile);

    leggiFile(&v, &e, nomefile, &archi);
    for (i = 0; i < e; i++){
        printf("arco %d : %d--%d\n", i, archi[i].val1, archi[i].val2);
    }
    printf("\n\n\n");

    ///creo un vettore contenente tutti i nodi e uno per gli indici temporanei
    nodi = malloc(v*sizeof(int));
    if(nodi == NULL){
        printf("errore nel malloc");
        exit(1);
    }
    for (i = 0; i < v; i++){
        nodi[i] = i;
    }
    tmp = malloc(v*sizeof(int));
    for (i = 0; i < v; i++){
        tmp[i] = 0;
    }
    if(tmp == NULL){
        printf("errore nel malloc");
        exit(1);
    }

    ///INSIEME DELLE PARTI
    insDellePart(pos, tmp, archi, e, v);


    free(tmp);
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
    ///FACCIO LA MALLOC DELLA STRUCT E LA RIEMPIO
    *archi = (arcs *)malloc((*e)*sizeof(arcs ));

    for (i = 0; i < *e; i++){
        fscanf(fp, "%d %d", &((*archi)[i].val1), &((*archi)[i].val2));
    }


    fclose(fp);

}





int controlloVortex(int *tmp, arcs *archi, int e, int v){
    int i, j, bool = 0;
    ///CICLO PER TUTTI GLI ARCHI
    for (j = 0; j < e; j++){
        ///CICLO PER TUTTI I VERTICI
        for (i = 0; i < v; i++){
            ///TMP CONTIENE GLI INDICI DEI VERTICI DA ANALIZZARE
            if (tmp[i] == 1) {
                if (i == archi[j].val1 || i == archi[j].val2)
                    bool = 1;
            }
        }
        ///CONDIZIONE DI USCITA NEL CASO DI MANCATA CORRISPONDENZA
        if (bool == 0){
            return bool;
        }
        ///CONDIZIONE PER PROSEGUIRE IL CONTROLLO SUL PROSSIMO ARCO, SE SIAMO ALL'ULTIMO ARCO NON DEVE CAMBIARE IN 0
        else if (j+1 < e)
            bool = 0;
    }

    return bool;
}

void insDellePart(int pos, int *tmp, arcs *archi, int e, int v) {
    int j;
    if (pos >= v) {
        ///controllo e stampa
        if (controlloVortex(tmp, archi, e, v)){
            printf("vertex cover : \n{ ");
            for (j = 0; j < v; j++){
                if (tmp[j] == 1){
                    printf("%d ", j);
                }
            }
            printf("}\n");
        }
    }
    else {
        tmp[pos] = 0;
        insDellePart(pos + 1, tmp, archi, e, v);
        tmp[pos] = 1;
        insDellePart(pos + 1, tmp, archi, e, v);
    }
}
