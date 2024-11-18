#ifndef E03_INVENTARIO_H
#define E03_INVENTARIO_H

#define MAXC 50

typedef struct wrapperINV *INV;

typedef struct{
    int hp, mp, atk, def, mag, spr;
} stat_t;

typedef struct{
    char *nome, *tipo;
    stat_t stat;
} inv_t;

struct wrapperINV{
    inv_t *vettINV;
    int nINV, maxINV;
};

INV RiempiInventario(char *nomefile);
inv_t INVNameSrc(INV inv, char *nome);
inv_t VoidInv_t();
void INVPrint(inv_t tmp);


#endif //E03_INVENTARIO_H
