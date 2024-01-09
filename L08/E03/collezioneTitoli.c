#include "collezioneTitoli.h"
static void inOrder(link root);

typedef struct node *link;
struct node{
    pTitolo titolo;
    pBSTquot bstQuot;
    link next;
};
struct collezioneTitoli{
    link head;
    link z;
};


pCollezioneT listInit(){
    pCollezioneT collezione;
    collezione = (pCollezioneT)malloc(sizeof(*collezione));
    collezione->head = collezione->z = NULL;
    return collezione;
}

link newNode(pTitolo titolo, pBSTquot bstQuot, link next){
    link x;
    x=(link)malloc(sizeof(*x));
    x->next = next;
    x->titolo = titolo;
    x->bstQuot = bstQuot;
    return x;
}

void nodeInsertSorted(pCollezioneT collezioneT, pBSTquot bstQuot, pTitolo titolo){
    link x,p;
    if(collezioneT->head == collezioneT->z || (confrontaTitoli(collezioneT->head->titolo, titolo) > 0)) {
        collezioneT->head = newNode(titolo, bstQuot, collezioneT->head);
        return;
    }
    for(p=collezioneT->head, x=collezioneT->head->next; x!=NULL && (confrontaTitoli(x->titolo, titolo) < 0); p=x, x=x->next);
    p->next = newNode(titolo, bstQuot, x);

}

link ricercaTitolo(pCollezioneT collezioneT, char titolo[]){
    link x;
    pTitolo tmp = creaTitolo(titolo);
    x=collezioneT->head;
    if(x!=NULL){
        for(x=collezioneT->head; x!=NULL; x=x->next){
            if(confrontaTitoli(x->titolo, tmp) == 0){
                distruggiTitolo(tmp);
                printf("Titolo trovato!\n");
                return x;
            }
        }
    }
    else{
        printf("Lista vuota!\n");
    }
    distruggiTitolo(tmp);
    printf("Titolo inesistente!\n");
    return NULL;
}

dQuot_s cercaQuota(link node){
    dataOra_s d;
    printf("Inserisci la data in cui ricercare nel formato (aaaa/mm/gg):");
    d = leggiDataOra(stdin);
    return BSTcerca(node->bstQuot, d);
}

void minMaxSearch(link node, int cmd){
    pBSTquot bst = node->bstQuot;
    minMaxBST(bst,cmd);
}

void listaFree(link head){
    link corrente=head, successivo;
    while(corrente != NULL){
        successivo = corrente->next;
        distruggiTitolo(corrente->titolo);
        BSTfree(corrente->bstQuot);
        free(corrente);
        corrente = successivo;
    }

}

void deallocaCollezioneT(pCollezioneT collezioneT){
    listaFree(collezioneT->head);
    free(collezioneT);
}

pBSTquot cercaBST(link node){
    return node->bstQuot;
}