#include "inv.h"

struct tabInv_t{
    inv_t *vettInv;
    int nInv;
    int maxInv;
};


ptabInv leggi_inventario(char *file_name)
{
    FILE *fp = fopen(file_name, "r");
    ptabInv tabInv = (ptabInv)malloc(sizeof(*tabInv));
    int n_oggetti = 0, i;
    if(fp != NULL)
    {
        fscanf(fp, "%d ", &n_oggetti);
        if(n_oggetti != 0)
        {
            tabInv->maxInv = max_oggetti;
            tabInv->nInv = n_oggetti;
            tabInv->vettInv = (inv_t *)malloc(n_oggetti * sizeof(inv_t ));
            if(tabInv->vettInv != NULL)
                for(i = 0; i < n_oggetti; i++) {
                    fscanf(fp, " %s %s", tabInv->vettInv[i].nome, tabInv->vettInv[i].tipo);
                    fscanf(fp, "%d %d %d %d %d %d", &(tabInv->vettInv[i].stats.hp), &(tabInv->vettInv[i].stats.mp), &(tabInv->vettInv[i].stats.atk), &(tabInv->vettInv[i].stats.def), &(tabInv->vettInv[i].stats.mag), &(tabInv->vettInv[i].stats.spr));
                    //stampa_oggetto(tabInv, i);
                    //printf("\n\n");
                }
            else{
                printf("\nErrore nell'allocazione della memoria per l'inventario.");
                exit(-1);
            }
        }
    }
    else{
        printf("\nErrore nella lettura del file di input");
        exit(-1);
    }
    return tabInv;
}


int trova_oggetto(ptabInv tabInv, char *nome)
{
    int index = -1, i, flag = 0;
    int n_oggetti = tabInv->nInv;
    for(i = 0; i < n_oggetti && !flag; i++)
    {
        if(!strcasecmp(nome, tabInv->vettInv[i].nome))
        {
            index = i;
            flag = 1;
        }
    }
    return index; // se non trova, ritorna -1
}
void stampa_oggetto(ptabInv tabInv, int index){
    if (index >= 0){
        stampa_nome_oggetto(tabInv, index);
        stampa_tipo_oggetto(tabInv, index);
        stampa_stats_oggetto(tabInv, index);
    }
}

void stampa_stats_oggetto(ptabInv tabInv, int index){
    if (index >= 0) {
        printf("\nHP: %d", tabInv->vettInv[index].stats.hp);
        printf("\nMP: %d", tabInv->vettInv[index].stats.mp);
        printf("\nATK: %d", tabInv->vettInv[index].stats.atk);
        printf("\nDEF: %d", tabInv->vettInv[index].stats.def);
        printf("\nMAG: %d", tabInv->vettInv[index].stats.mag);
        printf("\nSPR: %d", tabInv->vettInv[index].stats.spr);
    }
}

void stampa_nome_oggetto(ptabInv tabInv, int index){
    if (index >= 0){
        printf("\nNOME: %s", tabInv->vettInv[index].nome);
    }
}


void stampa_tipo_oggetto(ptabInv tabInv, int index){
    if (index >= 0){
        printf("\nTIPO: %s", tabInv->vettInv[index].tipo);
    }
}


void distruggi_inventario(ptabInv tabInv){
    free(tabInv->vettInv);
    free(tabInv);
}

void stampa_inv(ptabInv inventario){
    for(int i = 0; i < inventario->nInv; i++){
        stampa_oggetto(inventario, i);
        printf("\n");
    }
}

stat_t restituisci_stats_oggetto(ptabInv inventario, int index){
    stat_t res;
    res = inventario->vettInv[index].stats;
    return res;
}