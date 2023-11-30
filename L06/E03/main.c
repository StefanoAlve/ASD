
#include "personaggi.h"
#include "inventario.h"
#include "personaggi.c"
int main() {
    char filePg[MAXC] = "pg.txt";
    pnodoPg_t x, y;
    ptabPg tabPg = (ptabPg)malloc(sizeof(*tabPg));
    struct pg_t personaggio;

    tabPg = leggiPersonaggi(filePg);
    //PG0001 Sephiroth Guerriero 1832 71 116 65 41 49
    strcpy(personaggio.codice, "PG0011");
    strcpy(personaggio.nome, "PG0011");
    strcpy(personaggio.classe, "PG0011");

    inserisciPg(tabPg, personaggio);
    y = &personaggio;
    cancellaPg(tabPg, y);

    for(x = tabPg->headPg; x != NULL; x = x->next){
        printf("%s\n", x->codice);
    }

    return 0;
}
