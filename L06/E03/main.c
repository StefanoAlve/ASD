
#include "personaggi.h"
#include "inventario.h"
#include "personaggi.c"
int main() {
    char filePg[MAXC] = "pg.txt";
    pnodoPg_t x;
    ptabPg tabPg = (ptabPg)malloc(sizeof(*tabPg));
    tabPg = leggiPersonaggi(filePg);

    for(x = tabPg->headPg; x->next != NULL; x = x->next){
        printf("%s\n", x->codice);
    }

    return 0;
}
