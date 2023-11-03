#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char codice[6];
    char birth[11];
    char nome[51];
    char cognome[51];
    char via[51];
    char citta[51];
    int CAP;
}Item;

struct node{
    Item val;
    struct node* next;
};

typedef enum
{
    r_tastiera,
    r_file,
    r_ricerca_codice,
    r_estrai_codice,
    r_estrai_date,
    r_print_on_file,
    r_fine
}comandoE;
/// FUNZIONI
comandoE acquisisci_comando(void);
Item acquisisci_campo(FILE *fp_in);
Item getItem(struct node* nodo);
struct node* InsNodeSorted(Item val, struct node* head);
struct node* new_node(struct node* next, Item val);
struct node* search_and_return_code(struct node** head, char* code);
struct node* search_between_dates(struct node** head, char* date1, char* date2);
void seleziona_funzione(comandoE cmd, struct node** head);
void libera_nodo(struct node** head, struct node* f);
void search_code(struct node* head, char* code);
void displayNode(struct node* h, FILE *fp_out);
int itemCmp(Item a, Item b);
int dateCmp(char* date_a, char* date_b);
char* convertData(char* data);


int main() {
    struct node* head = NULL; // lista vuota
    comandoE cmd = -1;
    while(cmd!=6)
    {
        cmd = acquisisci_comando();
        seleziona_funzione(cmd, &head);

    }
    return 0;
}


struct node* new_node(struct node* next, Item val)
{
    struct node* new_node = NULL;
    new_node = (struct node*)malloc(sizeof(struct node));
    if (new_node == NULL)
        return NULL;
    new_node->val = val;
    new_node->next = next;
    return new_node;
}

comandoE acquisisci_comando(void)
{
    comandoE cmd = -1;
    char comando[51];
    printf("\nScrivi il comando che vuoi inserire (input, ricerca, estrai, stampa)");
    scanf("%s", comando);
    if(!strcasecmp(comando, "input"))
    {
        printf("\nVuoi inserire il comando da tastiera o da file (tastiera, file):");
        scanf("%s", comando);
        if(!strcasecmp(comando, "tastiera"))
            cmd = r_tastiera;
        else if(!strcasecmp(comando, "file"))
            cmd = r_file;
    }
    else if(!strcasecmp(comando, "ricerca"))
        cmd = r_ricerca_codice;
    else if(!strcasecmp(comando, "estrai"))
    {
        printf("\nVuoi estrarre per codice o per data (codice, data)?");
        scanf("%s", comando);
        if(!strcasecmp(comando, "codice"))
            cmd = r_estrai_codice;
        else if(!strcasecmp(comando, "data"))
            cmd = r_estrai_date;
    }
    else if(!strcasecmp(comando, "stampa"))
        cmd = r_print_on_file;
    else
        cmd = r_fine;
    return cmd; // Nel caso di errore si ritorna cmd = -1;
}


void seleziona_funzione(comandoE cmd, struct node** head)
{
    Item val;
    char file_name[51], searched_code[6], date1[11], date2[11];
    FILE *fp_in = stdin;
    FILE *fp_out = stdout;
    struct node* tmp, *x;
    val.CAP = 0;
    switch(cmd)
    {
        case r_tastiera:
            val = acquisisci_campo(fp_in);
            printf("\n");
            if (val.CAP != -1)
            {
                *head = InsNodeSorted(val, *head);
                displayNode(*head, fp_out);
            }
            else
                printf("\nErrore, non è stato possibile aggiungere il nodo");
            break;
        case r_file:
            printf("\nInserisci il nome del file: ");
            scanf("%s", file_name);
            fp_in = fopen(file_name, "r");
            while(val.CAP != -1 && fp_in != NULL)
            {
                val = acquisisci_campo(fp_in);
                if (val.CAP != -1)
                    *head = InsNodeSorted(val, *head);
            }
            if (fp_in == NULL)
                printf("\nErrore, non è stato possibile aprire il file %s", file_name);
            printf("\n");
            displayNode(*head, fp_out);
            break;
        case r_ricerca_codice:
            printf("\nInserisci il codice da ricercare (Axxxx):");
            scanf("%s", searched_code);
            search_code(*head, searched_code);
            break;
        case r_estrai_codice:
            printf("\nInserisci il codice da ricercare (Axxxx):");
            scanf("%s", searched_code);
            tmp = search_and_return_code(head, searched_code);
            if (tmp != NULL)
            {
                printf("\nIl seguente nodo e' stato cancellato.");
                libera_nodo(head, tmp);
            }
            break;
        case r_estrai_date:
            printf("\nInserisci le due date nel formato (aaaa/mm/gg aaaa/mm/gg):");
            scanf("%s %s", date1, date2);
            tmp = search_between_dates(head, date1, date2);
            if(tmp != NULL)
                printf("\nHo trovato i seguenti match compresi tra le due date:");
            while(tmp != NULL)
            {
                printf("\n%s %s %s %s %s %s %d", tmp->val.codice, tmp->val.nome, tmp->val.cognome, tmp->val.birth, tmp->val.via, tmp->val.citta, tmp->val.CAP);
                libera_nodo(head, tmp);
                tmp = search_between_dates(head, date1,date2);
            }
            break;
        case r_print_on_file:
            printf("\nInserisci il nome del file di output:");
            scanf(" %s", file_name);
            fp_out = fopen(file_name, "w");
            if (fp_out != NULL)
            {
                displayNode(*head, fp_out);
                printf("\nStampa su file correttamente eseguita!");
            }
            else
                printf("\nImpossibile aprire il file di output.");
            fclose(fp_out);
            break;
        case r_fine:
            if(*head != NULL) {
                for (x = (*head)->next, tmp = *head; x != NULL; tmp = tmp->next, x = x->next) {
                    tmp->next = x->next;
                    free(x);
                }
                free(*head);
            }
            printf("\nArrivederci!");
            break;
        default:
            printf("\nErrore, non ho compreso correttamente il tuo comando");
    }

}


Item acquisisci_campo(FILE *fp_in)
{
    Item tmp;
    tmp.CAP = 0;
    if (fp_in != NULL) {
        if (fp_in == stdin)
            printf("\nInserisci il campo nel seguente formato:\n<codice> <nome> <cognome> <dat_dinascita> <via> <cita'> <cap>:");
        if (fscanf(fp_in, " %s %s %s %s %s %s %d", tmp.codice, tmp.nome, tmp.cognome, tmp.birth, tmp.via, tmp.citta, &(tmp.CAP)) == 7)
            return tmp;
    }
    // se non è vero, imposto un flag a tmp tale che possa accorgermi dell'errore:
    tmp.CAP=-1;
    return tmp;
}

struct node* InsNodeSorted(Item val, struct node* head)
{
    int cont = 0;
    struct node* x = NULL, *p = NULL;
    // se head è vuoto o il valore da inserire precede quello del nodo
    if (head == NULL || itemCmp(val, getItem(head)) <= 0)
        return new_node(head, val);  // ritorna il nuovo head che avrà come successivo il vecchio nel caso peggiore o un nuovo head con successivo NULL
    for (x = head->next, p = head; x!= NULL && itemCmp(val, getItem(x)) >= 0; p = x, x = x->next) // fin tanto che la data di nascita di val >= head
        cont++;
        // se sono uscito dal ciclo arrivando a x = NULL oppure in un punto tale per cui val < head, allora devo inserirlo
    // nella posizione successiva alla precedente (quella in cui si trova ora x) e far puntare quel nodo a x
    p->next = new_node(x, val);
    return head;
}


int itemCmp(Item a, Item b) // Come per la strcmp a è il "destinatario", b è "l'origine"
{
    int value = -1;
    char *date_a = convertData(a.birth);
    char *date_b = convertData(b.birth);
    value = dateCmp(date_a,date_b);
    return value;
}

Item getItem(struct node* nodo)
{
    Item tmp;
    tmp = nodo->val;
    return tmp;
}

char* convertData(char* data)
{
    // conversione da gg/mm/aaaa a aaaa/mm/gg
    int i = 0;
    char *newData = malloc(strlen(data)*sizeof(char));
    while(i < 4){
        newData[i] = data[6+i];
        i++;
    }
    newData[4] = '/'; newData[5] = data[3]; newData[6] = data[4]; newData[7] = '/'; newData[8] = data[0]; newData[9] = data[1]; newData[10] = '\0';
    return newData;
}


void displayNode(struct node* h, FILE *fp_out)
{
    if (h == NULL)
        return;
    else
    {
        fprintf(fp_out, "%s %s %s %s %s %s %d\n", h->val.codice, h->val.nome, h->val.cognome, h->val.birth, h->val.via, h->val.citta, h->val.CAP);
        h = h->next;
        displayNode(h, fp_out);
    }
}

void search_code(struct node* head, char* code)
{
    int match = 0;
    Item headItem;
    for(; head != NULL && !match; head = head->next)
    {
        headItem = getItem(head);
        if (!strcasecmp(headItem.codice, code)) {
            match = 1;
            printf("\nHo trovato il seguente match:\n%s %s %s %s %s %s %d", headItem.codice, headItem.nome,
                   headItem.cognome, headItem.birth, headItem.via, headItem.citta, headItem.CAP);
        }
    }
    if(!match)
        printf("\nErrore, impossibile trovare alcun match.");
    printf("\n");
    return;
}


struct node* search_and_return_code(struct node** head, char* code)
{
    int match = 0;
    struct node *x;
    Item tmpItem;
    for(x = *head; x != NULL && !match; x= x->next)
    {
        tmpItem = getItem(x);
        if (!strcasecmp(tmpItem.codice, code))
        {
            match = 1;
            printf("\nHo trovato il seguente match:\n%s %s %s %s %s %s %d\n", tmpItem.codice, tmpItem.nome,
                   tmpItem.cognome, tmpItem.birth, tmpItem.via, tmpItem.citta, tmpItem.CAP);
            return x;
        }
    }
    if(!match)
        printf("\nErrore, impossibile trovare alcun match.");
    printf("\n");

    return NULL;
}


struct node* search_between_dates(struct node** head, char* date1, char* date2)
{
    char* nodeDate;
    char* tmpDate;
    struct node* x;
    Item tmp;
    int match = 0;
    if(dateCmp(date1,date2) > 0) // se la prima data è maggiore della seconda faccio uno swap di modo che siano ordinate
    {
        tmpDate = date1;
        date1=date2;
        date2 = tmpDate;
    }
    // se la data presente in tmp è > della data più piccola tra date1 e date 2 e < della più grande, match = 1
    x = *head;
    while(x != NULL && !match)
    {
        tmp = getItem(x);
        nodeDate = convertData(tmp.birth);
        match = dateCmp(nodeDate, date1) && dateCmp(date2, nodeDate); // restituisce 1 se nodeDate >= date1 e se nodeDate<= date2
        if(!match)
            x = x->next;
    }
    if (!match)
        x= NULL;
    return x;
}


int dateCmp(char* date_a, char* date_b)
{
    int value = 0;
    if (strcasecmp(date_a, date_b)<0) // se il destinatario precede l'origine (se il successore precede) ritorno 0
        value = 0;
    else if(strcasecmp(date_a, date_b)>=0) // se il destinatario segue l'origine(se il successore segue) ritorno 1
        value = 1;
    return value;
}
void libera_nodo(struct node** head, struct node* f)
{
    struct node *p, *x;
    p = *head;
    for(x = *head; x!= NULL && x != f; p = x, x = x->next);
    if (x == *head)
        *head = (*head)->next;
    else
        p->next = x->next;
    if (x != NULL)
        free(x);
}
