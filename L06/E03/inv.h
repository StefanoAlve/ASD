#ifndef INV_H
    #define INV_H
    #define max_strlen 51
    #define max_oggetti 8
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    typedef struct tabInv_t *ptabInv;
    typedef struct{
        int hp;
        int mp;
        int atk;
        int def;
        int mag;
        int spr;
    }stat_t;
    typedef struct{
        char nome[max_strlen];
        char tipo[max_strlen];
        stat_t stats;
    }inv_t;
    ptabInv leggi_inventario(char *file_name);
    int trova_oggetto(ptabInv tabInv, char *nome);
    void stampa_inv(ptabInv inventario);
    stat_t restituisci_stats_oggetto(ptabInv inventario, int index);
    void stampa_oggetto(ptabInv tabInv, int index);
    void stampa_stats_oggetto(ptabInv tabInv, int index);
    void stampa_nome_oggetto(ptabInv tabInv, int index);
    void stampa_tipo_oggetto(ptabInv tabInv, int index);
    void distruggi_inventario(ptabInv tabInv);

#endif


