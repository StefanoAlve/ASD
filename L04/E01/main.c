#include <stdio.h>
#include <stdlib.h>
#define MAXL 50

typedef int Item;
typedef struct nodo **link;
typedef struct nodo *testa;

struct nodo{
    Item val;
    link next;
};

void leggiFile(int *v, int *e, char nomefile[], testa head);
link newNode(Item val, link next);
link listInsTail(link h, Item val);


///VERTEX COVER (I NODI DEVONO COPRIRE TUTTI GLI ARCHI)
int main() {
    int v, e;
    char nomefile[MAXL];
    testa head = malloc(sizeof *head);



    printf("inserire il nome del file in cui estrarre il grafo\t");
    scanf("%s", nomefile);

    leggiFile(&v, &e, nomefile, head);
    return 0;
}


void leggiFile(int *v, int *e, char nomefile[], testa head){
    FILE *fp;
    int i, j, k, valore, puntato;

    if((fp = fopen(nomefile,"r"))==NULL){
        printf("errore in lettura file");
        exit(1);
    }

    fscanf(fp, "%d %d", v, e);



    for (i = 0; i < *e; i++){
        ///PRENDO VALORE E DATO PUNTATO DAL VALORE DAL FILE
        fscanf(fp, "%d %d", &valore, &puntato);

        ///CASO DEL VALORE DI TESTA
        if (i == 0){
            ///FACCIO LA MALLOC DEL VETTORE DI PUNTATORI CON MASSIMO V-1 COLLEGAMENTI
            link x = malloc((*v-1)*sizeof(**x));
            if (x[0] == NULL)
                exit(1);
            ///FACCIO LA MALLOC DEL SINGOLO PUNTATORE NEL VETTORE
            else {
                x[0] = malloc(sizeof(struct nodo));
                if (x == NULL)
                    exit(1);
                ///METTO NEL NODO IL VALORE E IL PUNTATORE A VUOTO
                else {
                    x[0]->val = valore;
                    x[0]->next = NULL;
                }
            }
            ///FACCIO PUNTARE x[0] ALLA HEAD DA MODO CHE SIA IL VALORE DI TESTA
            head = x[0];
        }

    }
}


link newNode(Item val, link next) {
    link x = malloc(sizeof *x);
    if (x==NULL)
        return NULL;
    else {
        x->val = val;
        x->next = next;
    }
    return x;
}

link listInsTail(link h, Item val) {
    link x;
    if (h==NULL)
        return newNode(val, NULL);
    for (x=h; x->next!=NULL; x=x->next);
    x->next = newNode(val, NULL);
    return h;
}
