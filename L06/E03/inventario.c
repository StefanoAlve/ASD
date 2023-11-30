#include "inventario.h"

struct tabInv_t{
    inv_t *vettInv;
    int nInv;
    int maxInv;
};

ptabInv leggiInventario(char *nomeFile){
    //Inizializzazione variabili
    FILE *fin;
    ptabInv tabInv = (ptabInv)malloc(sizeof(*tabInv));
    int nObj,i;
    //Apertura file
    fin = fopen(nomeFile, "r");
    if(fin == NULL){
        printf("Errore nell'apertura del file inventario!\n");
        exit(1);
    }
    fscanf(fin, "%d", &nObj);
    if(nObj != 0){
        tabInv->maxInv = MAXOBJ;
        tabInv->nInv = nObj;
        tabInv->vettInv = (inv_t*)malloc(nObj*sizeof(inv_t));
        for(i=0;i<nObj;i++){
            fscanf(fin, "%s %s %d %d %d %d %d %d", tabInv->vettInv[i].nome, tabInv->vettInv[i].tipo, &tabInv->vettInv[i].stat.hp, &tabInv->vettInv[i].stat.mp, &tabInv->vettInv[i].stat.atk, &tabInv->vettInv[i].stat.def, &tabInv->vettInv[i].stat.mag, &tabInv->vettInv[i].stat.spr);
        }
    }
    //Chiusura file
    fclose(fin);
    return tabInv;
}
int ricercaObjN(ptabInv tabInv, char *nome){
    int i;
    for(i=0;i<tabInv->nInv;i++){
        if(strcasecmp(tabInv->vettInv[i].nome, nome) == 0){
            return i;
        }
    }
    return -1;
}
void stampaObj(ptabInv tabInv, int index){
    stampaObjNome(tabInv, index);
    stampaObjTipo(tabInv, index);
    stampaObjStats(tabInv, index);
}
void stampaObjStats(ptabInv tabInv, int index){
    printf("Le statistiche dell'oggetto sono:\n");
    printf("hp:%d\n",tabInv->vettInv[index].stat.hp);
    printf("mp:%d\n",tabInv->vettInv[index].stat.mp);
    printf("atk:%d\n",tabInv->vettInv[index].stat.atk);
    printf("def:%d\n",tabInv->vettInv[index].stat.def);
    printf("mag:%d\n",tabInv->vettInv[index].stat.mag);
    printf("spr:%d\n",tabInv->vettInv[index].stat.spr);
}
void stampaObjNome(ptabInv tabInv, int index){
    printf("Il nome dell'oggetto è: %s\n", tabInv->vettInv[index].nome);
}
void stampaObjTipo(ptabInv tabInv, int index){
    printf("Il tipo dell'oggetto è: %s\n", tabInv->vettInv[index].tipo);
}
void distruggiInventario(ptabInv tabInv){
    free(tabInv->vettInv);
    free(tabInv);
}
