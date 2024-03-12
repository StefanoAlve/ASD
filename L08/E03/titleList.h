
#ifndef E03_TITLELIST_H
    #define E03_TITLELIST_H
    #include "dailyquotBST.h"
    #include "title.h"
    typedef struct node *link;
    typedef struct list *pList;
    link NEW(link next, BST bst, pTitle title);
    void insert_node_sorted(pList list, BST bst, pTitle title);
    pList leggi_file(pList lista, FILE *fp);
    pList listInit();
    link searchBYtitle(pList list, char *name);
    dQuot_s search_for_quot(link node);
    void min_max_between_dates(link node, int flag);
    void freeALL(pList lista);
    void balance(link node, int soglia);
    void printInfo(pList lista);

#endif //E03_TITLELIST_H
