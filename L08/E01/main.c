#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ELEM 5
#define MAXSTRLEN 101
#define DBG 0
/// Si cerca di trovare tutte le diagonali possibili che rispettano le condizioni e di ridurre la complessità dell'esercizio LAB7E02
/// utilizzando un algoritmo di sorting che ordini in modo decrescente i punteggi delle diagonali poi si sceglie la terza diagonale come la diagonale con il pt. massimo
/// si scelgono invece le altre due tramite l'algoritmo greedy.


typedef enum{transizione,indietro,avanti} tipologia_e;
typedef enum{spalle,frontale}direzione_e;
typedef enum{first,not_first}precedenza_e;
typedef enum{not_last,last}finale_e;

typedef struct{
    char name[MAXSTRLEN];
    tipologia_e tipologia;
    direzione_e ingresso;
    direzione_e uscita;
    precedenza_e precedenza;
    finale_e finale;
    float valore;
    int difficolta;
    float rapporto;
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
typedef struct{
    diagonale diag1;
    diagonale diag2;
    diagonale diag3;
    float punteggio_tot;
    int diff_tot;
}programma;

void MergeSortWrapper(diagonale *diagonali, int num);
void MergeSortR(diagonale *ausiliario, diagonale *diagonali, int l, int r);
void Merge(diagonale *ausiliario, diagonale *diagonali, int l, int r);
elemento* leggi_elementi(int *n_elementi);
void printElements(elemento* elementi, int n_elementi);
link conta_diagonali_totali(elemento* elementi, link head_diag, int DD, int n, int k, int* diag_possibili_tot);
link disp_rip(elemento * elementi, elemento* sol, link head_diag, int DD, int pos,  int n, int k, int* cont, int* dim_diag);
diagonale* copy_on_vect_and_free_list(link head, int num_diag);
link new_node(link next, diagonale val);
link insert_node(link head, diagonale val);
float conta_punteggio_diag(diagonale diag);
int calcola_difficolta_attuale(elemento *elementi, int n_elem);
void print_on_file_diag(diagonale* diagonali, int num_diag);
void algGreedy(diagonale* diagonali, int num_diag, int DP);
void check_condizioni(diagonale diag, int* flag_acrob_avanti,int* flag_acrob_indietro,int* flag_double_acrob);


int main() {
    int n_elementi = 0, n_diag_possibili = 0;
    int DD = 12, DP = 30;
    elemento* elementi = NULL;
    elementi = leggi_elementi(&n_elementi);
    link head_diag_possibili = NULL;
    diagonale* vett_diagonali_possibili = NULL;
    printf("\nEcco le diagonali presenti nel file:\n");
    printElements(elementi, n_elementi);
    head_diag_possibili = conta_diagonali_totali(elementi, head_diag_possibili, DD, n_elementi, MAX_ELEM, &n_diag_possibili);
    printf("\n\nCon le condizioni indicate si possono eseguire %d diagonali possibili.", n_diag_possibili);
    vett_diagonali_possibili = copy_on_vect_and_free_list(head_diag_possibili, n_diag_possibili);
    MergeSortWrapper(vett_diagonali_possibili, n_diag_possibili);
#if DBG
    print_on_file_diag(vett_diagonali_possibili, n_diag_possibili);
#endif
    algGreedy(vett_diagonali_possibili, n_diag_possibili, DP);
    return 0;
}

void printElements(elemento* elementi, int n_elementi){
    for(int i = 0; i < n_elementi; i++){
        printf("\n%s %d %d %d %d %d %.2f %d rapporto: %.2f", elementi[i].name, elementi[i].tipologia, elementi[i].ingresso, elementi[i].uscita, elementi[i].precedenza, elementi[i].finale, elementi[i].valore, elementi[i].difficolta, elementi[i].rapporto);
    }
}



void print_on_file_diag(diagonale* diagonali, int num_diag)
{
    int i;
    FILE *fp = NULL;
    float punteggio;
    fp = fopen("test.txt", "w");
    for(i = 0; i < num_diag; i++)
    {
        fprintf(fp, "\n\n");
        punteggio = diagonali[i].punteggio_diag;
        fprintf(fp, "DIAG #%d > %f\n", i, punteggio);
        for(int j= 0; j < diagonali[i].n_elementi; j++)
            fprintf(fp, "%s ", diagonali[i].elementi[j].name);
    }
    fclose(fp);
}

elemento* leggi_elementi(int* n_elementi)
{
    char filename[MAXSTRLEN];
    elemento *elementi = NULL;
    int i = 0;
    FILE *fp = NULL;
    printf("\nInserisci il nome del file:");
    scanf("%s", filename);
    fp=fopen(filename, "r");
    if(fp != NULL)
    {
        fscanf(fp, "%d", n_elementi);
        elementi = (elemento*)malloc(*n_elementi * sizeof(elemento));
        while(fscanf(fp, "%s %d %d %d %d %d %f %d ", elementi[i].name, &elementi[i].tipologia, &elementi[i].ingresso, &elementi[i].uscita, &elementi[i].precedenza, &elementi[i].finale, &elementi[i].valore, &elementi[i].difficolta) == 8 && i < *n_elementi){
            elementi[i].rapporto = (float)(elementi[i].valore/elementi[i].difficolta);
            i++;
        }
    }
    fclose(fp);
    return elementi;
}

link conta_diagonali_totali(elemento* elementi, link head_diag, int DD, int n, int k, int* diag_possibili_tot)
{
    int dim_diag = n; // inizialmente alloco n diagonali
    elemento*sol;
    sol = (elemento*)malloc(MAX_ELEM*sizeof(elemento));
    for(int i = 1; i <= k; i++)
        head_diag = disp_rip(elementi, sol, head_diag, DD, 0, n, i, diag_possibili_tot, &dim_diag);
    free(sol);
    return head_diag;
}

float conta_punteggio_diag(diagonale diag)
{
    float cont = 0;
    int n = diag.n_elementi;
    for(int i = 0; i < n; i++) // check_elem acrobatico{
        cont += diag.elementi[i].valore;
    return cont;
}

int calcola_difficolta_attuale(elemento *elementi, int n_elem)
{
    int i, value = 0;
    for(i = 0; i < n_elem; i++){
        value+=elementi[i].difficolta;
    }
    return value;
}


link disp_rip(elemento *elementi, elemento* sol, link head_diag, int DD, int pos,  int n, int k, int* cont, int* dim_diag)
{
    int flag = 0;
    diagonale tmp;
    if (pos >= k)
    {
        tmp.elementi = sol;
        tmp.n_elementi = k;
        tmp.punteggio_diag = conta_punteggio_diag(tmp);
        for(int i = 0; i < k && !flag; i++){
            if(tmp.elementi[i].tipologia != transizione) // se almeno un elemento della diag è un elemento acrobatico:
                flag = 1;
        }
        if(flag){
            tmp.elementi = (elemento*)malloc(k*sizeof(elemento));
            for(int i = 0; i < k; i++) // ricopiatura diagonale
            {
                tmp.elementi[i].ingresso = sol[i].ingresso; tmp.elementi[i].tipologia = sol[i].tipologia; tmp.elementi[i].difficolta = sol[i].difficolta; tmp.elementi[i].valore = sol[i].valore;
                tmp.elementi[i].uscita = sol[i].uscita; tmp.elementi[i].precedenza = sol[i].precedenza; tmp.elementi[i].finale = sol[i].finale; strcpy(tmp.elementi[i].name, sol[i].name);
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
            if(calcola_difficolta_attuale(sol, pos+1) <= DD)  // altrimenti non ha senso ricorrere
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
diagonale* copy_on_vect_and_free_list(link head, int num_diag)
{
    diagonale* vett_diagonali = (diagonale*)malloc(num_diag * sizeof(diagonale));
    link p;
    for(int i = 0; i < num_diag; i++){
        p = head;
        vett_diagonali[i].punteggio_diag = head->diag.punteggio_diag;
        vett_diagonali[i].n_elementi = head->diag.n_elementi;
        vett_diagonali[i].n_elementi = head->diag.n_elementi;
        vett_diagonali[i].elementi = head->diag.elementi;
        head = head->next;
        free(p);
    }
    return vett_diagonali;
}

void MergeSortWrapper(diagonale *diagonali, int num)
{
    diagonale *D;
    D = (diagonale*)malloc(num * sizeof(diagonale));
    MergeSortR(D, diagonali, 0, num-1);
    free(D);
}

void MergeSortR(diagonale *ausiliario, diagonale *diagonali, int l, int r)
{
    int pm;
    if(l>=r)
        return;
    pm = (l+r)/2;
    MergeSortR(ausiliario, diagonali, l, pm);
    MergeSortR(ausiliario, diagonali, pm+1, r);
    Merge(ausiliario, diagonali, l, r);
}


void Merge(diagonale *ausiliario, diagonale *diagonali, int l, int r)
{
    int pm = (l+r)/2;
    int i = l,j = pm+1, k;
    for(k = l; k <= r; k++)
    {
        if(j > r)
            ausiliario[k] = diagonali[i++];
        else if(i > pm)
            ausiliario[k] = diagonali[j++];
        else if(diagonali[i].punteggio_diag >= diagonali[j].punteggio_diag)
            ausiliario[k] = diagonali[i++];
        else
            ausiliario[k] = diagonali[j++];
    }
    //ricopiatura
    for(k = l; k <= r; k++)
        diagonali[k] = ausiliario[k];
}


void algGreedy(diagonale* diagonali, int num_diag, int DP)
{
    int i,j, stop = 0, flag_acrob_avanti = 0, flag_acrob_indietro = 0, flag_double_acrob = 0, bonus = 0;
    int diff_attuale, min_diff = calcola_difficolta_attuale(diagonali[num_diag-1].elementi, diagonali[num_diag-1].n_elementi);
    programma prog;
    prog.diff_tot = 0;
    prog.punteggio_tot = 0;
    // Iniziamo a cercare quello che potrebbe dare il bonus
    prog.diag3 = diagonali[0];
    if(diagonali[0].elementi[diagonali[0].n_elementi-1].difficolta >= 8){
        bonus = 1;
        prog.diag3.punteggio_diag = (float)(prog.diag3.punteggio_diag * 1.5);
    }
    prog.punteggio_tot+=prog.diag3.punteggio_diag;
    prog.diff_tot = calcola_difficolta_attuale(prog.diag3.elementi, prog.diag3.n_elementi);
    // controllo che condizioni soddisfo con la terza diagonale
    check_condizioni(prog.diag3, &flag_acrob_avanti, &flag_acrob_indietro, &flag_double_acrob);
    // ricerca delle altre due diagonali
    for(i = 0; i < num_diag && !stop; i++)
    {
        prog.diag1 = diagonali[i];
        diff_attuale = calcola_difficolta_attuale(prog.diag1.elementi, prog.diag1.n_elementi);
        if(diff_attuale + prog.diff_tot +min_diff <= DP)
        {
            check_condizioni(prog.diag1, &flag_acrob_avanti, &flag_acrob_indietro, &flag_double_acrob);
            prog.diff_tot+=diff_attuale;
            prog.punteggio_tot+=prog.diag1.punteggio_diag;
            for(j = 0; j < num_diag && !stop; j++)
            {
                prog.diag2 = diagonali[j];
                diff_attuale = calcola_difficolta_attuale(prog.diag2.elementi, prog.diag2.n_elementi);
                if(diff_attuale + prog.diff_tot <= DP) // controllo condizioni ulteriori
                {
                    check_condizioni(prog.diag2, &flag_acrob_avanti, &flag_acrob_indietro, &flag_double_acrob);
                    if(flag_double_acrob && flag_acrob_avanti && flag_acrob_indietro)
                    {
                        prog.diff_tot+=diff_attuale;
                        prog.punteggio_tot+=prog.diag2.punteggio_diag;
                        stop = 1;
                    }
                }
            }
        }
    }
    if(flag_acrob_indietro && flag_acrob_avanti && flag_double_acrob)
    {
        printf("\n\n");
        printf("DIFF TOT = %d, TOT = %.2f", prog.diff_tot, prog.punteggio_tot);
        printf("\nDIAG #1 > %.3f\n", prog.diag1.punteggio_diag);
        for(j= 0; j < prog.diag1.n_elementi; j++)
            printf("%s ", prog.diag1.elementi[j].name);

        printf("\nDIAG #2 > %.3f\n", prog.diag2.punteggio_diag);
        for(j= 0; j < prog.diag2.n_elementi; j++)
            printf("%s ", prog.diag2.elementi[j].name);

        printf("\nDIAG #3 > %.3f", prog.diag3.punteggio_diag);
        if(bonus)
            printf(" (BONUS)\n");
        else
            printf("\n");
        for(j= 0; j < prog.diag3.n_elementi; j++)
            printf("%s ", prog.diag3.elementi[j].name);
    }
    else
        printf("\nNon sono riuscito a trovare alcuna diagonale.");

}



void check_condizioni(diagonale diag, int* flag_acrob_avanti,int* flag_acrob_indietro,int* flag_double_acrob)
{
    int i,j;
    for(i = 0; i < diag.n_elementi; i++)
    {
        j = i+1;
        if(diag.elementi[i].tipologia == avanti)
            *flag_acrob_avanti = 1;
        if(diag.elementi[i].tipologia == indietro)
            *flag_acrob_indietro = 1;
        if(j < diag.n_elementi)
        {
            if(diag.elementi[i].tipologia != transizione && diag.elementi[i+1].tipologia != transizione)
                *flag_double_acrob = 1;
        }
    }
}