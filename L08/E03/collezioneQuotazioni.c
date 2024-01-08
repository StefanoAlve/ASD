#include "collezioneQuotazioni.h"

static linkB insertR(linkB root, dataOra_s d, dQuot_s quot, linkB z);
static linkB newNodeB(dataOra_s d, dQuot_s quot, linkB l, linkB r);

struct BSTquot_s{
    linkB root;
    linkB z;
};

pBSTquot bstInit(){
    pBSTquot x = (pBSTquot)malloc(sizeof(*x));
    x->root=x->z=NULL;
    return x;
}

dQuot_s calcolaDQuot(int valori[], int scambi[], int n){
    dQuot_s quotazione;
    int sommaVal=0, sommaScamb=0;
    for(int i=0; i<n; i++){
        sommaVal += valori[i]*scambi[i];
        sommaScamb += scambi[i];
    }
    quotazione.dQuot = (float)(sommaVal/sommaScamb);
    return quotazione;
}
pBSTquot riempiBST(FILE *fp){
    pBSTquot bst=bstInit();
    dataOra_s *dt;
    dQuot_s dQuot;
    int i, nTransazioni=0, *valori, *scambi, nTransazioniGiorn = 0;
    fscanf(fp, "%d", &nTransazioni);
    valori=(int*)malloc(nTransazioni* sizeof(int));
    scambi=(int*)malloc(nTransazioni* sizeof(int));
    dt = (dataOra_s*)malloc(nTransazioni*sizeof(dataOra_s));
    for(i=0; i<nTransazioni; i++){
        dt[i] = leggiDataOra(fp);
        if(i!=0 && confrontaDate(dt[i-1], dt[i]) != 0) {
            dQuot = calcolaDQuot(valori, scambi, nTransazioniGiorn);
            BSTinsert(bst, dt[i-1], dQuot);
            nTransazioniGiorn = 0;
        }
        fscanf(fp, "%d %d", &valori[nTransazioniGiorn], &scambi[nTransazioniGiorn]);
        nTransazioniGiorn++;
        if(i==nTransazioni-1){
            dQuot = calcolaDQuot(valori, scambi, nTransazioniGiorn);
            BSTinsert(bst, dt[i], dQuot);
        }
    }
    free(scambi);
    free(valori);
    free(dt);
    return bst;
}

void BSTfree(pBSTquot bst){
    if(bst == NULL){
        return;
    }
    treeFree(bst->root, bst->z);
    free(bst);
}
void treeFree(linkB h, linkB z){
    if(h==z){
        return;
    }
    treeFree(h->l, z);
    treeFree(h->r, z);
    free(h);
}

dQuot_s  BSTcerca(pBSTquot bst, dataOra_s d){
    return BSTcercaR(bst->root, bst->z, d);
}

dQuot_s  BSTcercaR(linkB h, linkB z, dataOra_s d){
    int cmp;
    if(h==z){
        return quotNULL();
    }
    cmp = confrontaDate(d, h->dataOra);
    if(cmp==0)
        return h->dQuot;
    if(cmp==-1)
        return BSTcercaR(h->l, z, d);
    return BSTcercaR(h->r, z, d);
}

dQuot_s  quotNULL(){
    dQuot_s x;
    x.dQuot = -1;
    return x;
}

void minMaxBST(pBSTquot bst, int cmd) {
    dQuot_s min = initQuotaMin(), max = initQuotaMax();
    if (cmd == 0) {
        dataOra_s dt1, dt2;
        printf("Inserisci la data da cui iniziare la ricerca nel formato (aaaa/mm/gg):");
        dt1 = leggiDataOra(stdin);
        printf("Inserisci la data in cui terminare la ricerca nel formato (aaaa/mm/gg):");
        dt2 = leggiDataOra(stdin);
        visitaInOrder(bst->root, bst->z,dt1,dt2, &min, &max);

    } else {
        visitaInOrder(bst->root, bst->z, dataMin(), dataMax(), &min, &max);
    }
    printf("I risultati ottenuti sono: ");
    printf("MIN: ");
    stampaQuot(min);
    printf("MAX: ");
    stampaQuot(max);
}
int isGreater(dQuot_s q1, dQuot_s q2){
    if(q1.dQuot > q2.dQuot){
        return 1;
    }
    return 0;
}

int isLower(dQuot_s q1, dQuot_s q2){
    if(q1.dQuot < q2.dQuot){
        return 1;
    }
    return 0;
}

void visitaInOrder(linkB root, linkB z, dataOra_s d1, dataOra_s d2, dQuot_s *min, dQuot_s *max){
    dQuot_s quota;
    if(root == z){
        return;
    }
    quota = root->dQuot;
    if(confrontaDate(root->dataOra, d1) >= 0 && confrontaDate(root->dataOra, d2) <= 0){
        if(isGreater(quota, *max))
            *max=quota;
        if(isLower(quota, *min))
            *min = quota;
    }
    visitaInOrder(root->l,z,d1,d2,min,max);
    visitaInOrder(root->r, z,d1,d2,min,max);
}

void BSTinsert(pBSTquot bst, dataOra_s d, dQuot_s quot){
    bst->root = insertR(bst->root, d, quot, bst->z);
}
static linkB insertR(linkB root, dataOra_s d, dQuot_s quot, linkB z){
    if(root==z){
        return newNodeB(d,quot,z,z);
    }
    if(confrontaDate(d, root->dataOra) < 0){
        root->l = insertR(root->l, d, quot, z);
    }else{
        root->r = insertR(root->r, d, quot, z);
    }
    return root;
}

static linkB newNodeB(dataOra_s d, dQuot_s quot, linkB l, linkB r){
    linkB x = (linkB)malloc(sizeof(*x));
    x->dataOra = d;
    x->dQuot = quot;
    x->l = l;
    x->r = r;
    return x;
}

dataOra_s dataMin(){
    dataOra_s d;
    d.data.mese = 1;
    d.data.giorno = 1;
    d.data.anno = 0;
    d.ora.ore = 0;
    d.ora.minuti = 0;
    return d;
}
dataOra_s dataMax(){
    dataOra_s d;
    d.data.mese = 12;
    d.data.giorno = 31;
    d.data.anno = 9999;
    d.ora.ore = 23;
    d.ora.minuti = 59;
    return d;
}
void stampaQuot(dQuot_s quot){
    printf("La quotazione giornaliera vale: %.2f\n", quot.dQuot);
}
dQuot_s initQuotaMin(){
    dQuot_s x;
    x.dQuot = 9999;
    return x;
}
dQuot_s initQuotaMax(){
    dQuot_s x;
    x.dQuot = 0;
    return x;
}