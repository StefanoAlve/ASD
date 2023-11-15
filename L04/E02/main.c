#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define lmax 50
typedef struct{
    int gg;
    int mm;
    int aa;
}data_t;
typedef struct {
    char codice[6];
    char nome[lmax];
    char cognome[lmax];
    data_t data;
    char via[lmax];
    char citta[lmax];
    int cap;
}item;
typedef struct node *link;
struct node {
    item val;
    link next;
};
typedef enum{// enum con i possibili comandi che si possono scegliere
    r_ins_tastiera,
    r_ins_file,
    r_ricerca_cod,
    r_canc_per_cod,
    r_fine
}comando_e;
link newnode(item val,link next);
link leggifile(FILE *file,link head);
link SortListIns(link head , item val);
int controllaData(item val1, item val2);
link menuParola (comando_e comando,link head);
comando_e scegli_comando();
link inserisci_new_node(link head);
link inserisci_new_node_file(link head);
link ricerca_cod(link head);
link cancella_per_cod(link head);
void stampapersona(link persona);
void stampa_su_file(link head);
int main() {
    FILE *fin;
    link head = NULL;
    if ((fin = fopen("ana01.txt","r"))==NULL){
        printf("Errorre nell'apertura del file");
    }
    else {
        head = leggifile(fin, head);
    }
    comando_e comando = scegli_comando();
    head = menuParola(comando,head);
}
link leggifile(FILE *file, link head){
    item persona;
    char data[11];
    while(!feof(file)){
        fscanf(file,"%s %s %s %s %s %s %d",persona.codice,persona.nome,persona.cognome,data,persona.via,persona.citta,&persona.cap);
        sscanf(data,"%d/%d/%d",&persona.data.gg,&persona.data.mm,&persona.data.aa);
        head = SortListIns(head,persona);
    }
    fclose(file);
    return head;
}
link newnode(item val,link next){
    link x = malloc(sizeof *x);
    if (x == NULL)
        return NULL;
    else{
        x->val = val ;
        x->next = next;
    }
    return x;
}
int controllaData(item val1,item val2){
    if (val1.data.aa > val2.data.aa){
        return 1;
    }
    else if(val1.data.aa == val2.data.aa ){
        if(val1.data.mm > val2.data.mm){
            return 1;
        }
        else if(val1.data.mm== val2.data.mm){
            if(val1.data.gg >= val2.data.gg){
                return 1;
            }
            else
                return 0;
        }
        else
            return 0;
    }
    else
        return 0;
}
link SortListIns(link head , item val){
    link x,p;
    if (head == NULL || controllaData(val,head->val))
        return head = newnode(val,head);
    for(x = head->next, p=head;x!=NULL && controllaData(x->val, val);p = x,x = x->next);
    p->next = newnode(val,x);
    return head;
}
comando_e scegli_comando(){
    char opzione[lmax];
    comando_e comando;

    char comandi_possibili[5][lmax] = {"ins_da_tastiera","ins_da_file","ricerca_cod","canc_per_cod","fine"};
    printf("Inserisci il comando (possibili: 'ins_da_tastiera','ins_da_file','ricerca_cod','canc_per_cod','fine'):\n");
    scanf("%s", strlwr(opzione));
    for (comando = 0; comando < 5 && strcmp(opzione, comandi_possibili[comando]) != 0; comando++) {
    }

    if (comando == 5) {
        printf("Errore");
    }

    return comando;
}
link menuParola (comando_e comando,link head){
    link x;
    switch (comando) {
        case r_ins_tastiera:
            head = inserisci_new_node(head);
            stampa_su_file(head);
            break;
        case r_ins_file:
            head = inserisci_new_node_file(head);
            stampa_su_file(head);
            break;
        case r_ricerca_cod:
            x = ricerca_cod(head);
            stampapersona(x);
            break;
        case r_canc_per_cod:
            head = cancella_per_cod(head);
            stampa_su_file(head);
            break;
        case r_fine:
            break;
    }
    return head;
}
void stampapersona(link persona){
    printf("\n%s %s %s %02d/%02d/%02d %s %s %05d\n", persona->val.codice, persona->val.nome, persona->val.cognome,
           persona->val.data.gg, persona->val.data.mm, persona->val.data.aa, persona->val.via, persona->val.citta, persona->val.cap);
}
link inserisci_new_node(link head){
    item val;
    char data[11];
    printf("Inserisci la nuova persona: \n");
    scanf("%s %s %s %s %s %s %d",val.codice,val.nome,val.cognome,data,val.via,val.citta,&val.cap);
    sscanf(data,"%d/%d/%d",&val.data.gg,&val.data.mm,&val.data.aa);
    head = SortListIns(head , val);
    return head;
}
link inserisci_new_node_file(link head){
    FILE *file;
    char nuovo_file[lmax];
    printf("inserisci il nuovo file da cui prendere i dati anagrafici: \n");
    scanf("%s",nuovo_file);

    if ((file = fopen(nuovo_file,"r"))==NULL){
        printf("Errore nell'apertura del file");
    }
    else{
        head = leggifile(file, head);
    }
    return head;
}
link ricerca_cod(link head){
    link x;
    char codice[6];
    printf("Inserisci il codice per la ricerca: \n");
    scanf("%s",codice);
    for(x = head;x!=NULL;x = x->next){
        if (strcmp(x->val.codice,codice)==0){
            return x;
        }
    }

}
link cancella_per_cod(link head){
    char codice[6];
    link x,p;
    printf("Inserisci il codice per eliminare quell codice: \n");
    scanf("%s",codice);
    if (head == NULL)
        return NULL;
    for(x = head, p = NULL; x!=NULL;p = x, x = x->next){
        if(strcmp(x->val.codice,codice)==0){
            if(head == x)
                head = x->next;
            else
                p->next = x->next;
            free(x);
            break;
        }
    }
    return head;
}
void stampa_su_file(link head){
    link x;
    FILE *fout;
    char fileOut[lmax];
    printf("Inserisci il nome del file dove vuoi stampare: \n");
    scanf("%s",fileOut);
    if ((fout = fopen(fileOut,"w"))==NULL){
        printf("Errore nell'apertura del file");
    }
    else{
        for(x = head; x!=NULL;x = x->next){
            fprintf(fout,"\n%s %s %s %02d/%02d/%02d %s %s %05d\n", x->val.codice, x->val.nome, x->val.cognome,
                    x->val.data.gg, x->val.data.mm, x->val.data.aa, x->val.via, x->val.citta, x->val.cap);
        }
    }
    fclose(fout);
}
