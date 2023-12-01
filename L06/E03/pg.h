#ifndef PG_H
    #define PG_H
    #ifndef INV_H
        #include "inv.h" // sto includendo anche stdin ,stdlib, string.h
    #endif
    #define max_code_lenght 7
    typedef struct tabPg_t *ptabPg;
    typedef struct pg_t *nodoPg_t; // puntatore a nodo
    typedef struct tabEquip_t *pTabEquip;


    struct pg_t{ // nodo con personaggio
        char nome[max_strlen];
        char classe[max_strlen];
        char codice[max_code_lenght];
        pTabEquip equip;
        stat_t stats;
        nodoPg_t next;
    };
    ptabPg inizializza_personaggi(void);
    ptabPg leggi_pg(ptabPg lista_pg, char *file_name);
    nodoPg_t new_node(nodoPg_t next, struct pg_t personaggio);
    ptabPg insert_node(ptabPg tabPg, struct pg_t personaggio);
    nodoPg_t ricerca_x_code(ptabPg tabPg, char codice[]);
    ptabPg cancella_personaggio(ptabPg tabPg, nodoPg_t pg_da_cancellare);
    void stampa_tutti_pg(ptabPg personaggi);
    void stampa_pg_compreso_stats_oggetti(ptabInv inventario, nodoPg_t nodoPg);
    void stampa_pg_nome(nodoPg_t nodoPg);
    void stampa_pg_codice(nodoPg_t nodoPg);
    void stampa_pg_classe(nodoPg_t nodoPg);
    void stampa_pg_stats(nodoPg_t nodoPg);
    void stampa_equip(ptabInv inventario, nodoPg_t nodoPg);
    void aggiungi_equip(nodoPg_t nodoPg, ptabInv inventario, char nome_equip[max_strlen]);
    void scegli_equip_in_uso(nodoPg_t nodoPg, ptabInv inventario, char nome_equip[max_code_lenght]);
    void rimuovi_equip(nodoPg_t nodoPg, ptabInv inventario, char nome_equip[max_code_lenght]);
    void freeALL(ptabPg lista_pg);
#endif


