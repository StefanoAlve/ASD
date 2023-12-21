#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ELEM 5
#define MAXS 101
typedef enum{transizione,indietro,avanti} tipologia_e;
typedef enum{spalle,frontale}direzione_e;
typedef enum{first,not_first}precedenza_e;
typedef enum{not_last,last}finale_e;

typedef struct{
    char nome[MAXS];
    tipologia_e tipologia;
    direzione_e ingresso;
    direzione_e uscita;
    precedenza_e precedenza;
    finale_e finale;
    float valore;
    int difficolta;
}elemento;

typedef struct{
    elemento* elementi;
    int n_elementi;
    float punteggio_diag;
}diagonale;

typedef struct node *link;
struct node{
    diagonale diag;
    link next;
};


elemento* leggiFile(int *n_elementi);
link contaDiag(elemento* elementi, link head_diag, int DD, int n, int k, int* diag_possibili_tot);
link disp_rip(elemento * elementi, elemento* sol, link head_diag, int DD, int pos,  int n, int k, int* cont, int* dim_diag);
float trovaComb(diagonale *diagonali, int n_diag, int DP);
int comb_rip(diagonale *diagonali, diagonale *sol, int n, int k, int pos, int start, int DP, float*best, diagonale *bestSol);
int difficoltaProgramma(diagonale* diag, int n_diag); //calcola la difficoltà di un programma DP
int difficoltaAttuale(elemento *elementi, int n_elem); // calcola la difficolta di una diagonale dati gli elementi e il numero di elementi
diagonale* copiaELibera(link head, int num_diag);
link new_node(link next, diagonale val);
link insert_node(link head, diagonale val);
float punteggioDiag(diagonale diag); // controlla che ci sia almeno un elemento acrobatico
float punteggioPotenzialeConBonus(diagonale *diagonali, int num_diag, int* index_bonus);
int check_condizioni_programma(diagonale *diag, int n_diag); // controlla che ci sia almeno un elemento acrobatico avanti e uno indietro + almeno due elementi in seq.
void dealloc(diagonale *diagonali, int n);


int main() {
    int nEle = 0, nDiagPossibili = 0, DD, DP;
    elemento* elementi = NULL;
    link headDiag = NULL;
    diagonale* vettDiag = NULL;

    elementi = leggiFile(&nEle);

    printf("\n\nInserisci la difficolta' massima per diagonale e la difficolta' massima per il programma (DD DP):");
    scanf("%d %d", &DD, &DP);
    headDiag = contaDiag(elementi, headDiag, DD, nEle, MAX_ELEM, &nDiagPossibili);
    printf("\n\nCon le condizioni indicate si possono eseguire %d diagonali possibili.", nDiagPossibili);

    vettDiag = copiaELibera(headDiag, nDiagPossibili);

    trovaComb(vettDiag, nDiagPossibili, DP);

    dealloc(vettDiag, nDiagPossibili);
    return 0;
}


elemento* leggiFile(int* n_elementi)
{
    char filename[MAXS];
    elemento *elementi = NULL;
    int i = 0;
    FILE *fp = NULL;

    printf("\nInserisci il nome del file:");
    scanf("%s", filename);
    fp=fopen(filename, "r");
    printf("\nEcco gli elementi presenti nel file:\n");
    if(fp != NULL)
    {
        fscanf(fp, "%d", n_elementi);
        elementi = (elemento*)malloc(*n_elementi * sizeof(elemento));
        while(fscanf(fp, "%s %d %d %d %d %d %f %d ", elementi[i].nome, &elementi[i].tipologia, &elementi[i].ingresso, &elementi[i].uscita, &elementi[i].precedenza, &elementi[i].finale, &elementi[i].valore, &elementi[i].difficolta) == 8 && i < *n_elementi){
            printf("\n%s %d %d %d %d %d %f %d", elementi[i].nome, elementi[i].tipologia, elementi[i].ingresso, elementi[i].uscita, elementi[i].precedenza, elementi[i].finale, elementi[i].valore, elementi[i].difficolta);
            i++;
        }
    }
    fclose(fp);
    return elementi;
}


link contaDiag(elemento* elementi, link head_diag, int DD, int n, int k, int* diag_possibili_tot)
{
    int dim_diag = n; // inizialmente alloco n diagonali
    elemento*sol;
    sol = (elemento*)malloc(MAX_ELEM*sizeof(elemento));
    for(int i = 1; i <= k; i++)
        head_diag = disp_rip(elementi, sol, head_diag, DD, 0, n, i, diag_possibili_tot, &dim_diag);
    free(sol);
    return head_diag;
}


link disp_rip(elemento *elementi, elemento* sol, link head_diag, int DD, int pos,  int n, int k, int* cont, int* dim_diag) {
    int flag = 0;
    diagonale tmp;

    if (pos >= k)
    {
        tmp.elementi = sol;
        tmp.n_elementi = k;
        tmp.punteggio_diag = punteggioDiag(tmp);
        for(int i = 0; i < k && !flag; i++){
            if(tmp.elementi[i].tipologia != transizione) // se almeno un elemento della diag è un elemento acrobatico:
                flag = 1;
        }
        if(flag){
            tmp.elementi = (elemento*)malloc(k*sizeof(elemento));
            for(int i = 0; i < k; i++) // ricopiatura diagonale
            {
                tmp.elementi[i].ingresso = sol[i].ingresso; tmp.elementi[i].tipologia = sol[i].tipologia; tmp.elementi[i].difficolta = sol[i].difficolta; tmp.elementi[i].valore = sol[i].valore;
                tmp.elementi[i].uscita = sol[i].uscita; tmp.elementi[i].precedenza = sol[i].precedenza; tmp.elementi[i].finale = sol[i].finale; strcpy(tmp.elementi[i].nome, sol[i].nome);
            }
            head_diag = insert_node(head_diag, tmp);
            *cont = *cont+1;
        }
        return head_diag;
    }
    for(int i = 0; i < n; i++)
    {
        sol[pos] = elementi[i];
        if(sol[0].ingresso == frontale) // si deve iniziare sempre frontalmente
        {
            if(difficoltaAttuale(sol, pos + 1) <= DD)  // altrimenti non ha senso ricorrere
            {
                if(pos == 0){
                    if(sol[pos].precedenza == first)
                        head_diag = disp_rip(elementi, sol, head_diag, DD, pos + 1, n, k, cont, dim_diag);
                }
                else if (pos >= 1) { // se la direzione di uscita del precedente coincide con quella di entrata del corrente.
                    if (sol[pos - 1].uscita == sol[pos].ingresso) {
                        if (sol[pos - 1].finale == not_last)
                            head_diag = disp_rip(elementi, sol, head_diag, DD, pos + 1, n, k, cont, dim_diag); // altrimento sol[pos] con il ciclo successivo
                    }
                }
            }
        }
    }
    return head_diag;
}

float punteggioDiag(diagonale diag) // controlla che ci sia almeno un elemento acrobatico
{
    float cont = 0;
    int n = diag.n_elementi;
    for(int i = 0; i < n; i++) // check_elem acrobatico{
        cont += diag.elementi[i].valore;
    return cont;
}


int difficoltaAttuale(elemento *elementi, int n_elem)
{
    int i, value = 0;
    for(i = 0; i < n_elem; i++){
        value+=elementi[i].difficolta;
    }
    return value;
}

//funzioni di creazione nodo e aggiunta
link new_node(link next, diagonale val)
{
    link new;
    new = (link)malloc(sizeof(*new));
    if(new != NULL){
        new->next = next;
        new->diag = val;
    }
    return new;
}
link insert_node(link head, diagonale val)
{
    head = new_node(head, val);
    return head;
}

diagonale* copiaELibera(link head, int num_diag)
{
    diagonale* vettDiagonali = (diagonale*)malloc(num_diag * sizeof(diagonale));
    link p;
    for(int i = 0; i < num_diag; i++){
        p = head;
        vettDiagonali[i].punteggio_diag = head->diag.punteggio_diag;
        vettDiagonali[i].n_elementi = head->diag.n_elementi;
        vettDiagonali[i].n_elementi = head->diag.n_elementi;
        vettDiagonali[i].elementi = head->diag.elementi;
        head = head->next;
        free(p);
    }
    return vettDiagonali;
}

float trovaComb(diagonale *diagonali, int n_diag, int DP)
{
    diagonale sol[3];
    diagonale bestSol[3];
    int i,j;
    float best = 0;
    for(i = 0; i < 3; i++){
        bestSol[i].elementi= (elemento *)malloc(MAX_ELEM * sizeof(elemento));
        bestSol[i].n_elementi = 0;
        bestSol[i].punteggio_diag = 0;
        sol[i].elementi = (elemento *)malloc(MAX_ELEM * sizeof(elemento));
        sol[i].n_elementi = 0;
        sol[i].punteggio_diag = 0;
    }
    comb_rip(diagonali, sol, n_diag, 3, 0, 0, DP, &best, bestSol);
    printf("\n\nTOT = %.3f", best);
    for(i = 0; i < 3; i++)
    {
        printf("\n\n");
        printf("DIAG #%d > %.3f\n", i+1, bestSol[i].punteggio_diag);
        for(j= 0; j < bestSol[i].n_elementi; j++)
            printf("%s ", bestSol[i].elementi[j].nome);
    }
    return best;
}


int difficoltaProgramma(diagonale* diag, int n_diag)
{
    int diff_p = 0, diff_diag;
    for(int i = 0; i < n_diag; i++){
        diff_diag = difficoltaAttuale(diag[i].elementi, diag[i].n_elementi);
        diff_p+=diff_diag;
    }
    return diff_p;
}


int comb_rip(diagonale *diagonali, diagonale *sol, int n, int k, int pos, int start, int DP, float* best, diagonale *bestSol)
{
    int diff_attuale, index_finale = -1, j = 0;
    float punteggioTmp;
    if(pos >= k)
    {
        diff_attuale = difficoltaProgramma(sol, pos);
        if(diff_attuale <= DP) {
            punteggioTmp = punteggioPotenzialeConBonus(sol, k, &index_finale);
            if (punteggioTmp >= *best) {
                punteggioTmp = punteggioPotenzialeConBonus(sol, k, &index_finale);
                if (check_condizioni_programma(sol, k) > 0) {
                    //punteggioTmp = punteggioPotenzialeConBonus(sol, k, &index_finale);
                    // ricopiatura risultato
                    for (int i = 0; i < k; i++) {
                        if (i != index_finale)
                            bestSol[j++] = sol[i];
                        else if(i == index_finale)
                        {
                            bestSol[k-1] = sol[i];
                            bestSol[k-1].punteggio_diag = (float) (sol[i].punteggio_diag * 1.5);
                        }
                    }
                    *best = punteggioTmp;
                }
            }
        }
        return 0;
    }
    for(int i = start; i < n; i++)
    {
        sol[pos] = diagonali[i];
        diff_attuale = difficoltaProgramma(sol, pos + 1);
        if(diff_attuale <= DP)
        {
            comb_rip(diagonali, sol, n, k, pos+1, start, DP, best, bestSol);
            start++;
        }
    }
    return 0;
}


float punteggioPotenzialeConBonus(diagonale *diagonali, int num_diag, int* index_bonus)
{
    int i, index = -1;
    float pt_finale, best_finale = 0, punteggio_finale = 0;
    for(i = 0; i < num_diag; i++)
    {
        if(diagonali[i].elementi[diagonali[i].n_elementi-1].difficolta >= 8)
        {
            pt_finale = diagonali[i].punteggio_diag;
            if(pt_finale > best_finale)
            {
                best_finale = pt_finale;
                index = i;
            }
        }
    }
    for(i = 0; i < num_diag; i++)
    {
        if(i != index)
            punteggio_finale+=diagonali[i].punteggio_diag;
        else
            punteggio_finale+=(float)(diagonali[i].punteggio_diag * 1.5);
    }
    *index_bonus = index;
    return punteggio_finale;
}


int check_condizioni_programma(diagonale *diag, int n_diag)
{
    int flag = 0;
    int flag1, flag2, flag3;
    flag1 = flag2 = flag3 = 0;
    for (int i = 0; i < n_diag && (flag1 * flag2*flag3 == 0); i++) {
        for (int j = 0; (j < diag[i].n_elementi) && (flag1 * flag2*flag3 == 0); j++) {
            // ALMENO DUE ELEMENTI ACROBATICI IN SEQUENZA
            if ( (j + 1 < diag[i].n_elementi) && (diag[i].elementi[j].tipologia == indietro || diag[i].elementi[j].tipologia == avanti) && (diag[i].elementi[j + 1].tipologia == indietro || diag[i].elementi[j + 1].tipologia == avanti)){
                flag3 = 2;
            }
            // ALMENO UNO AVANTI E UNO INDIETRO NEL CORSO DEL PROGRAMMA
            if (diag[i].elementi[j].tipologia == indietro)
                flag1 = 1;
            if (diag[i].elementi[j].tipologia == avanti)
                flag2 = 1;
        }
    }
    if(flag1*flag2*flag3 > 0)
        flag = 1;
    return flag;
}


void dealloc(diagonale *diagonali, int n)
{
    int i;
    for(i = 0; i < n; i++){
        free(diagonali[i].elementi);
    }
    free(diagonali);
}