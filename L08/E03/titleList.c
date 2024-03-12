#include "titleList.h"


struct node{
    pTitle title;
    BST bst;
    link next;
};


struct list{
    link head;
    link z;
};


pList listInit(){
    pList list;
    list = (pList)malloc(sizeof(*list));
    list->head = list->z = NULL;
    return list;
}


pList leggi_file(pList lista, FILE *fp)
{
    int num_titoli = 0, i;
    pTitle tit;
    BST bst;
    if(lista != NULL && fp != NULL)
    {
        fscanf(fp, "%d", &num_titoli);
        for(i = 0; i < num_titoli; i++)
        {
            bst = bstINIT();
            tit = title_init();
            tit = leggi_titolo(fp);
            bst = riempiBST(bst, fp);
            insert_node_sorted(lista, bst, tit);
        }
    }
    return lista;
}
link NEW(link next, BST bst, pTitle title)
{
    link x;
    x = (link)malloc(sizeof(*x));
    x->next = next;
    x->title = title;
    x->bst = bst;
    return x;
}


void insert_node_sorted(pList list, BST bst, pTitle title)
{
    link x,p;
    if(list->head == list->z || title_cmp(list->head->title, title) > 0){
        list->head = NEW(list->head, bst, title);
        return;
    }
    for(x = list->head->next, p = list->head; x!=NULL && title_cmp(x->title, title) < 0; p = x, x = x->next);
    p->next = NEW(x, bst, title);
}

link searchBYtitle(pList list, char *name)
{
    link x;
    pTitle tmp = title_cpy(name);
    x = list->head;
    if(x != NULL){
        for(x = list->head; x != NULL; x = x->next){
            if(title_cmp(x->title, tmp) == 0){
                title_free(tmp);
                return x;
            }
        }
    }
    else
        printf("\nEmpty list");
    title_free(tmp);
    return NULL;
}


dQuot_s search_for_quot(link node)
{
    dQuot_s dQuot;
    BST x = node->bst;
    dateTime_s dT;
    printf("\nInserisci la data: (aaaa/mm/gg):");
    dT = leggiDateTime(stdin);
    dQuot = BSTsearch(x, dT);
    displayQuot(dQuot);
    return dQuot;
}


void min_max_between_dates(link node, int flag){
    ricerca_min_max(node->bst, flag);
}

void freeALL(pList lista)
{
    link x = lista->head;
    while(x != NULL)
    {
        lista->head = lista->head->next;
        title_free(x->title);
        BSTfree(x->bst);
        free(x);
        x = lista->head;
    }
}

void balance(link node, int soglia){
    BSTbalance(node->bst, soglia);
}


void printInfo(pList lista)
{
    link x;
    if(lista!=NULL)
    {
        for(x = lista->head; x != NULL; x = x->next)
        {
            printf("\nTITOLO: ");
            title_print(x->title);
            BSTvisit(x->bst);
            printf("\n");
        }
    }
    else
        printf("\nNo info");
}