#include "dailyquotBST.h"
static link_bst insertR(link_bst h, link_bst z, dQuot_s dQuot, dateTime_s dT);
static link_bst NEWbstNode(dQuot_s dQuot, int N, dateTime_s dT, link_bst l, link_bst r, link_bst p);
static link_bst  rotR(link_bst h);
static link_bst  rotL(link_bst h);
static link_bst partR(link_bst h, int r);
static link_bst balanceR(link_bst h, link_bst z);
static void treePrintR(link_bst h, link_bst z);
static int AltezzaAlberoMassima(link_bst root);
static int AltezzaAlberoMinima(link_bst root);

struct BSTnode{
    dateTime_s dateTime;
    dQuot_s dQuot;
    int N;
    link_bst p;
    link_bst l;
    link_bst r;
};


struct bst{
    link_bst root;
    link_bst z;
};

dQuot_s calcola_dQuot(int *valori, int *scambi, int n)
{
    int i, somma2 = 0, somma1 = 0;
    dQuot_s res;
    for(i = 0; i < n; i++){
        somma1+=valori[i]*scambi[i];
        somma2+=scambi[i];
    }
    res.dailyQuot = (float)(somma1/somma2);
    return res;
}

BST bstINIT()
{
    BST bst;
    bst = (BST)malloc(sizeof(*bst));
    bst->root = ( bst->z = NEWbstNode(quotNULL(), 0, minData(), NULL, NULL, NULL));
    return bst;
}


void BSTinsert_leafR(BST bst, dQuot_s dQuot, dateTime_s dT){
    bst->root = insertR(bst->root, bst->z, dQuot, dT);
}


static link_bst insertR(link_bst h, link_bst z, dQuot_s dQuot, dateTime_s dT)
{
    if(h == z){
        return NEWbstNode(dQuot, 1, dT, z, z, z);
    }
    if(confrontaData(dT, h->dateTime) > 0)
    {
        h->r = insertR(h->r, z, dQuot, dT);
        h->r->p = h;
    }
    else
    {
        h->l = insertR(h->l, z, dQuot, dT);
        h->l->p = h;
    }
    h->N = h->N + 1;
    return h;
}

static link_bst NEWbstNode(dQuot_s dQuot, int N, dateTime_s dT, link_bst l, link_bst r, link_bst p)
{
    link_bst x = (link_bst)malloc(sizeof(*x));
    x->dateTime = dT;
    x->dQuot = dQuot;
    x->r = r; x->l = l;
    x->N = N;
    return x;
}


BST riempiBST(BST bst, FILE *fp)
{
    int i,num_transazioni = 0, *valori, *scambi, num_scambi_giornalieri = 0;
    dateTime_s *dT, currentDT;
    dQuot_s dQuot;
    fscanf(fp, " %d ", &num_transazioni);
    valori = (int*)malloc(num_transazioni*sizeof(int));
    scambi = (int*)malloc(num_transazioni*sizeof(int));
    dT = (dateTime_s *)malloc(num_transazioni*sizeof(dateTime_s));
    for(i = 0; i < num_transazioni; i++)
    {
        currentDT = leggiDateTime(fp);
        if(i == 0){
            fscanf(fp, " %d %d ", &(valori[num_scambi_giornalieri]), &(scambi[num_scambi_giornalieri]));
            dT[num_scambi_giornalieri] = currentDT;
            num_scambi_giornalieri++;
        }
        else
        {
            if(confrontaData(currentDT, dT[num_scambi_giornalieri-1]) == 0) // se la data corrente è uguale alla precedente
            {
                dT[num_scambi_giornalieri] = currentDT;
                fscanf(fp, " %d %d ", &(valori[num_scambi_giornalieri]), &(scambi[num_scambi_giornalieri]));
                num_scambi_giornalieri++;
            }
            else // se la data corrente è diversa dalla precedente allora inserisco le precedenti.
            {
                dQuot = calcola_dQuot(valori, scambi, num_scambi_giornalieri);
                BSTinsert_leafR(bst, dQuot, dT[num_scambi_giornalieri-1]);
                num_scambi_giornalieri = 0;
                fscanf(fp, " %d %d ", &(valori[num_scambi_giornalieri]), &(scambi[num_scambi_giornalieri]));
                dT[num_scambi_giornalieri] = currentDT;
                num_scambi_giornalieri++;

            }
        }
        if(i == num_transazioni-1){ //in questo caso devo inserire anche quello attuale.
            dQuot = calcola_dQuot(valori, scambi, num_scambi_giornalieri);
            BSTinsert_leafR(bst, dQuot, dT[num_scambi_giornalieri-1]);
        }
    }
    free(scambi);
    free(valori);
    free(dT);
    return bst;
}


void BSTfree(BST bst)
{
    if(bst == NULL)
        return;
    treeFree(bst->root, bst->z);
    free(bst);
}
void treeFree(link_bst h,link_bst z)
{
    if(h == z)
        return;
    treeFree(h->l, z);
    treeFree(h->r, z);
    free(h);
}


dQuot_s BSTsearch(BST bst, dateTime_s dT){
    return BSTsearchR(bst->root, bst->z, dT);
}


dQuot_s BSTsearchR(link_bst h, link_bst z, dateTime_s dT)
{
    int cmp;
    if(h == z){
        printf("\nNon ho trovato nulla nella data specificata per questo titolo.");
        return quotNULL();
    }
    cmp = confrontaData(dT, h->dateTime); // se la chiave è piu' piccola della radice, cerco a sx; se no a dx
    if(cmp == 0)
        return h->dQuot;
    if(cmp == -1)
        return BSTsearchR(h->l, z, dT);
    return BSTsearchR(h->r, z, dT);

}


dQuot_s quotNULL(){
    dQuot_s x;
    x.dailyQuot = -1;
    return x;
}

dQuot_s quotMIN(){
    dQuot_s x;
    x.dailyQuot = -1;
    return x;
}
dQuot_s quotMAX(){
    dQuot_s x;
    x.dailyQuot = 999999;
    return x;
}



int isGreater(dQuot_s q1, dQuot_s q2){
    if(q1.dailyQuot > q2.dailyQuot)
        return 1;
    return 0;
}
int isLower(dQuot_s q1, dQuot_s q2){
    if(q1.dailyQuot < q2.dailyQuot)
        return 1;
    return 0;
}


void ricerca_min_max(BST bst, int flag)
{
    dateTime_s data1, data2;
    dQuot_s min, max;
    min = quotMAX();
    max = quotMIN();
    if(flag == 1)
    {
        printf("\nInserisci le date nel formato (aaaa/mm/gg):");
        printf("\nPrima data: ");
        data1 = leggiDateTime(stdin);
        printf("\nSeconda data: ");
        data2 = leggiDateTime(stdin);
        inOrderVisit(bst->root, bst->z, data1, data2, &min, &max);
    }
    else if(flag == 2){
        data1 = minData();
        data2 = maxData();
        inOrderVisit(bst->root, bst->z, data1, data2, &min, &max);
    }
    else
        printf("\nErrore, non ho compreso il tuo comando.");
    if(flag == 1 || flag == 2) {
        if (min.dailyQuot != quotMAX().dailyQuot && max.dailyQuot != quotMIN().dailyQuot) {
            printf("\nValore minimo: %.2f\nValore massimo: %.2f", min.dailyQuot, max.dailyQuot);
        } else{
            printf("\nNessuna operazione tra le date selezionate.");
        }

    }
}


void displayQuot(dQuot_s dQuot){
    if(dQuot.dailyQuot != -1)
        printf("\nLa quotazione e' pari a: %.2f", dQuot.dailyQuot);
    else
        printf("\nNon ci sono quotazioni nella data specificata.");
}


void inOrderVisit(link_bst root, link_bst z, dateTime_s d1, dateTime_s d2, dQuot_s* min, dQuot_s *max)
{
    dQuot_s current_quot;
    if(root == z)
        return;
    current_quot = root->dQuot;
    if(confrontaData(root->dateTime, d1) >= 0 && confrontaData(root->dateTime, d2)<=0){
        if(isGreater(current_quot, *max))
            *max = current_quot;
        if(isLower(current_quot, *min))
            *min = current_quot;
    }
    inOrderVisit(root->l, z, d1, d2, min, max);
    inOrderVisit(root->r, z, d1, d2, min, max);
}


static link_bst  rotR(link_bst h)
{
    link_bst x = h->l;
    h->l = x->r;
    x->r->p = h;
    x->r = h;
    x->p = h->p;
    h->p = x;
    x->N = h->N;
    h->N = 1;
    h->N += (h->l) ? h->l->N:0;
    h->N += (h->r) ? h->r->N:0;
    return x;
}
static link_bst  rotL(link_bst h)
{
    link_bst x = h->r;
    h->r = x->l;
    x->l->p = h;
    x->l = h;
    x->p = h->p;
    h->p = x;
    x->N = h->N;
    h->N = 1;
    h->N += (h->l) ? h->l->N:0;
    h->N += (h->r) ? h->r->N:0;
    return x;
}

static link_bst partR(link_bst h, int r)
{
    int t = h->l->N;
    if(t > r){
        h->l = partR(h->l, r);
        h = rotR(h);
    }
    if(t<r){
        h->r = partR(h->r, r-t-1);
        h = rotL(h);
    }
    return h;
}


static link_bst balanceR(link_bst h, link_bst z)
{
    int r;
    if (h==z)
        return z;
    r = (h->N+1)/2-1;
    h = partR(h,r);
    h->l = balanceR(h->l,z);
    h->r = balanceR(h->r, z);
    return h;
}


int AltezzaAlberoMassimaWrapper(BST bst){
    return AltezzaAlberoMassima(bst->root);
}


static int AltezzaAlberoMassima(link_bst root){
    int h1, h2;
    if (root == NULL)
        return 0;
    if (root->l==NULL && root->r==NULL)
        return 1;
    h1 = AltezzaAlberoMassima(root->l);
    h2 = AltezzaAlberoMassima(root->r);
    if (h1 > h2)
        return h1 + 1;
    return h2 + 1;
}


int AltezzaAlberoMinimaWrapper(BST bst){
    return AltezzaAlberoMinima(bst->root);
}


static int AltezzaAlberoMinima(link_bst root){
    int h1, h2;
    if (root == NULL) return 0;
    if (root->l==NULL && root->r==NULL)
        return 1;
    h1 = AltezzaAlberoMinima(root->l);
    h2 = AltezzaAlberoMinima(root->r);
    if (h1 <= h2){
        return h1 + 1;
    }
    return h2 + 1;
}


void BSTbalance(BST bst, int soglia)
{
    int min, max,rapporto = 0;
    min = AltezzaAlberoMinima(bst->root);
    max = AltezzaAlberoMassima(bst->root);
    rapporto = max/min;
    printf("\nIl rapporto tra il cammino massimo e il cammino minimo vale: %d", rapporto);
    if(rapporto > soglia)
    {
        bst->root = balanceR(bst->root, bst->z);
        if(bst->root != bst->z)
            printf("\nSuccessfully balanced.");
        else
            printf("\nUnsuccessfully balanced.");
    }
    else
        printf("\nNon c'e' bisogno di bilanciare.");
}


void BSTvisit(BST bst)
{
    if(bst->root == bst->z)
        return;
    treePrintR(bst->root, bst->z);
}


static void treePrintR(link_bst h, link_bst z)
{
    if(h == z)
        return;
    treePrintR(h->l, z);
    printf("\n");
    displayDateTime(h->dateTime);
    displayQuot(h->dQuot);
    treePrintR(h->r, z);
}