#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXC 51
//Strutture
typedef struct{
    char *codice;
    char *nome;
    char *cognome;
    int data_di_nascita[3];
    char *via;
    char *citta;
    int cap;
}Item;

typedef struct node *link, node_t;
struct node{
    Item persona;
    link next;
};

typedef enum{r_acquisizione,r_ricerca,r_cancellazione,r_stampa, r_fine, r_errore}comando_e;
typedef enum{i_file, i_tastiera, i_errore}input_e;
typedef enum{o_codice, o_date, o_errore}opzione_e;
//Funzioni
comando_e leggiComando();
input_e leggiInput();
void sceltaComando(comando_e comando, link *listaPersone);
opzione_e leggiOpzione();
link newNode(Item persona, link next);
int acquisisci(FILE *fp, Item *persona);
void deallocaNodi(link head);
link inserisciOrdinato(link head, Item val);
void stampaLista(link head, FILE *fp);
int confrontaDate(int data1[3], int data2[3]);
link ricerca(link head);
link cancellaCodice(link head, Item *val, int *flag);
link cancellaData(link head, Item *val, int *finito, int datai[3], int dataf[3]);
//newnode
int main(void) {
    //Inizializzazione variabili
    comando_e comando;
    link listaPersone = NULL;
    do {
        comando = leggiComando();
        sceltaComando(comando, &listaPersone);
    }while(comando != r_fine);

    deallocaNodi(listaPersone);
}


comando_e leggiComando(){
    //Inizializzazione variabili
    comando_e comandoE;
    char tmp[MAXC], *comando;
    //Corpo programma
    printf("\n------------------------------------------------------------------------------\n");
    printf("\t\t\t\tLISTA COMANDI");
    printf("\n------------------------------------------------------------------------------\n");
    printf("<acquisizione> -> acquisisci da file o da tastiera un nuovo elemento\n");
    printf("<ricerca> -> ricerca di un elemento nella lista in base al codice\n");
    printf("<cancellazione> -> cancellazione di uno o piu' elementi della lista\n");
    printf("<fine> -> termina programma");
    printf("\n------------------------------------------------------------------------------\n");
    printf("\nInserisci comando:");
    scanf("%s", tmp);
    comando = strdup(tmp);
    if(strcasecmp(comando,"acquisizione") == 0){
        comandoE = r_acquisizione;
    }
    else if(strcasecmp(comando, "ricerca") == 0){
        comandoE = r_ricerca;
    }
    else if(strcasecmp(comando, "cancellazione") == 0){
        comandoE = r_cancellazione;
    }
    else if(strcasecmp(comando, "stampa") == 0){
        comandoE = r_stampa;
    }
    else if(strcasecmp(comando, "fine") == 0){
        comandoE = r_fine;
    }
    else{
        printf("Comando inserito inesistente, riprova!\n");
        comandoE = r_errore;
    }
    free(comando);
    return comandoE;
}
void sceltaComando(comando_e comando, link *listaPersone){
    input_e input;
    opzione_e opzione;
    FILE *fin, *fout;
    Item persona, cancellato;
    link head = *listaPersone, trovato = NULL;
    int flag, count = 0, finito = 0, datai[3], dataf[3];
    char tmp[MAXC], *nomeFile;

    switch (comando){
        case r_acquisizione:
            do {
                printf("Vuoi acquisire da file o da tastiera?:");
                input = leggiInput();
            }while(input == i_errore);//Finchè l'utente non inserirà un input corretto continuerò a chiedere

            switch (input){
                case i_file:
                    printf("Inserisci il nome del file:");
                    scanf("%s", tmp);
                    nomeFile = strdup(tmp);
                    fin = fopen(nomeFile, "r");
                    if(fin == NULL){
                        printf("Errore nell'apertura del file!\n");
                        exit(1);
                    }
                    while(!feof(fin)){
                        count++;
                        flag = acquisisci(fin, &persona);
                        if(flag) {
                            head = inserisciOrdinato(head, persona);
                        }
                        else{
                            printf("Nell'input a riga %d sono presenti errori di formato!\n",count);
                        }
                    }
                    printf("\n La lista attuale risulta:\n");
                    stampaLista(head, stdout);
                    fclose(fin);
                    free(nomeFile);
                    break;

                case i_tastiera:
                    printf("Inserisci i dati anagrafici <codice> <nome> <cognome> <data_di_nascita> <via> <citta'> <cap>:");
                    flag = acquisisci(stdin, &persona);
                    if(flag) {
                        head = inserisciOrdinato(head, persona);
                    }
                    else{
                        printf("Nell'input sono presenti errori di formato!\n");
                    }
                    printf("\n La lista attuale risulta:\n");
                    stampaLista(head, stdout);
                    break;
            }
            *listaPersone = head;
            break;
        case r_ricerca:
            trovato = ricerca(head);
            if(trovato != NULL){
                printf("\nLa persona trovata risulta:\n");
                printf("%s %s %s %d/%d/%d %s %s %d\n",trovato->persona.codice,trovato->persona.nome,trovato->persona.cognome,trovato->persona.data_di_nascita[0],trovato->persona.data_di_nascita[1],trovato->persona.data_di_nascita[2],trovato->persona.via,trovato->persona.citta,trovato->persona.cap);
            }
            break;
        case r_cancellazione:
            do {
                printf("Vuoi cancellare in base al codice o alle date?:");
                opzione = leggiOpzione();
            }while(opzione == o_errore);//Finchè l'utente non inserirà un parametro corretto continuerò a chiedere
            switch (opzione) {
                case o_codice:
                    flag = 0;
                    head = cancellaCodice(head, &cancellato, &flag);
                    if (!flag) {
                        printf("L'elemento cancellato risulta:\n");
                        printf("%s %s %s %d/%d/%d %s %s %d\n", cancellato.codice, cancellato.nome, cancellato.cognome,
                               cancellato.data_di_nascita[0], cancellato.data_di_nascita[1],
                               cancellato.data_di_nascita[2], cancellato.via, cancellato.citta, cancellato.cap);
                        printf("\n La lista attuale risulta:\n");
                        stampaLista(head, stdout);
                    }
                    break;
                case o_date:
                    count = 0;
                    printf("Inserisci la data di inizio nel formato gg/mm/aaaa:");
                    scanf(" %d/%d/%d", &datai[0],&datai[1],&datai[2]);
                    printf("Inserisci la data di fine nel formato gg/mm/aaaa:");
                    scanf(" %d/%d/%d", &dataf[0],&dataf[1],&dataf[2]);
                    while (!finito){
                        head = cancellaData(head, &cancellato, &finito, datai, dataf);
                        if(!finito) {
                            printf("L'elemento cancellato risulta:\n");
                            printf("%s %s %s %d/%d/%d %s %s %d\n", cancellato.codice, cancellato.nome,
                                   cancellato.cognome,
                                   cancellato.data_di_nascita[0], cancellato.data_di_nascita[1],
                                   cancellato.data_di_nascita[2], cancellato.via, cancellato.citta, cancellato.cap);
                            count++;
                        }
                    }
                    printf("Elementi eliminati: %d\n", count);
                    printf("\n La lista attuale risulta:\n");
                    stampaLista(head, stdout);
                    break;
            }
            *listaPersone = head;
            break;
        case r_stampa:
            printf("Inserisci il nome del file in cui stampare:");
            scanf(" %s", tmp);
            nomeFile = strdup(tmp);
            fout = fopen(nomeFile, "a");
            if(fout == NULL){
                printf("Errore nell'apertura del file!\n");
                exit(1);
            }
            stampaLista(head, fout);
            free(nomeFile);
            fclose(fout);
            break;
        case r_fine:
            break;
        case r_errore:
            break;
    }
}

input_e leggiInput(){
    input_e inputE;
    char tmp[MAXC], *input;
    scanf(" %s", tmp);
    input = strdup(tmp);

    if(strcasecmp(input, "file") == 0){
        inputE = i_file;
    }
    else if(strcasecmp(input, "tastiera") == 0){
        inputE = i_tastiera;
    }
    else{
        printf("Tipo di input inesistente, riprova!\n");
        inputE = i_errore;
    }
    free(input);
    return inputE;
}

opzione_e leggiOpzione(){
    opzione_e opzioneE;
    char tmp[MAXC], *opzione;
    scanf(" %s", tmp);
    opzione = strdup(tmp);

    if(strcasecmp(opzione, "codice") == 0){
        opzioneE = o_codice;
    }
    else if(strcasecmp(opzione, "date") == 0){
        opzioneE = o_date;
    }
    else{
        printf("Tipo di opzione inesistente, riprova!\n");
        opzioneE = o_errore;
    }
    free(opzione);
    return opzioneE;
}

link newNode(Item persona, link next){
    link corrente;
    corrente = (link)malloc(sizeof(node_t));
    if(corrente == NULL){
        printf("Errore nell'allocazione della memoria!\n");
        exit(1);
    }
    corrente->persona = persona;
    corrente->next = next;
    return corrente;
}

int acquisisci(FILE *fp, Item *persona){
    //Inizializzazione variabili
    char tmp[MAXC];
    int flag = 0;
    //Corpo programma
    flag += fscanf(fp," %s",tmp);
    persona->codice = strdup(tmp);
    flag += fscanf(fp, " %s", tmp);
    persona->nome = strdup(tmp);
    flag += fscanf(fp, " %s", tmp);
    persona->cognome = strdup(tmp);
    flag += fscanf(fp, "%d/%d/%d", &persona->data_di_nascita[0],&persona->data_di_nascita[1],&persona->data_di_nascita[2]);
    flag += fscanf(fp, " %s", tmp);
    persona->via = strdup(tmp);
    flag += fscanf(fp, " %s", tmp);
    persona->citta = strdup(tmp);
    flag += fscanf(fp, "%d", &persona->cap);

    if(flag != 9){
        return 0;
    }
    return 1;
}

void deallocaNodi(link head){
    link corrente = head, successivo;
    Item persona;
    while(corrente!=NULL) {
        successivo=corrente->next;
        persona = corrente->persona;

        free(persona.codice);
        free(persona.nome);
        free(persona.cognome);
        free(persona.via);
        free(persona.citta);

        free(corrente);
        corrente = successivo;
    }
}

link inserisciOrdinato(link head, Item val) {
    link corrente, successivo;
    int key[3];
    //Inizializzazione della chiave
    for(int i = 0; i<3; i++){
        key[i] = val.data_di_nascita[i];
    }
    //Corpo funzione
    if(head == NULL || confrontaDate(head->persona.data_di_nascita, key) <= 0)  //Se il la data di nascita di head è più piccola della key significa che è head è più vecchio
        return newNode(val, head); //Inserisco in testa
    for (successivo=head->next, corrente=head; successivo!=NULL && (confrontaDate(key, successivo->persona.data_di_nascita) <= 0); corrente=successivo, successivo=successivo->next); //Ciclo sulla lista fino alla posizione corretta
    corrente->next = newNode(val, successivo); //Inserisco in mezzo
    return head;
}

void stampaLista(link head, FILE *fp){
    link corrente;
    if(head == NULL){
        printf("Lista Vuota!\n");
        return;
    }
    for(corrente=head; corrente != NULL; corrente=corrente->next){
        fprintf(fp,"%s %s %s %d/%d/%d %s %s %d\n",corrente->persona.codice,corrente->persona.nome,corrente->persona.cognome,corrente->persona.data_di_nascita[0],corrente->persona.data_di_nascita[1],corrente->persona.data_di_nascita[2],corrente->persona.via,corrente->persona.citta,corrente->persona.cap);
    }
    fprintf(fp,"\n");
    if(fp != stdout) {
        printf("Stampa su file eseguita con successo!\n");
    }
}


int confrontaDate(int data1[3], int data2[3]){
    int dataN1, dataN2;
    //Passo in numero le date e le confronto
    dataN1 = data1[0]+100*data1[1]+10000*data1[2];
    dataN2 =data2[0]+100*data2[1]+10000*data2[2];
    if(dataN1 > dataN2)
        return 1;
    else if(dataN1 == dataN2)
        return 0;
    else
        return -1;
}

link ricerca(link head){
    link corrente;
    char tmp[MAXC], *codice;
    printf("Inserire il codice su cui eseguire la ricerca del tipo AXXXX dove x e' un numero tra 0 e 9:");
    scanf(" %s", tmp);
    codice = strdup(tmp);
    if(head == NULL){
        printf("La lista e' vuota, acquisire almeno una persona prima di effettuare la ricerca\n");
        free(codice);
        return NULL;
    }
    for(corrente=head; corrente!=NULL; corrente=corrente->next){
        if(strcasecmp(corrente->persona.codice, codice) == 0){
            free(codice);
            return corrente;
        }
    }
    printf("Non esiste nessuna persona corrispondente a tale codice\n");
    free(codice);
    return NULL;
}

link cancellaCodice(link head, Item *val, int *flag){
    link corrente, precedente, cancellato;
    int trovato = 0;
    cancellato = ricerca(head);
    if(cancellato !=NULL){
        for(corrente = head, precedente = NULL; corrente != NULL; precedente = corrente, corrente = corrente->next){
            if(corrente == cancellato){
                if(corrente == head){ //Aggiunta in testa
                    head = corrente->next;
                }
                else { // Aggiunta tra due nodi
                    precedente->next = cancellato->next;
                }
                trovato = 1;
                *val = cancellato->persona;
                free(cancellato);
                break;
            }
        }
    }
    if(!trovato){
        *flag = 1;
    }
    return head;
}

link cancellaData(link head, Item *val, int *finito, int datai[3], int dataf[3]){
    link corrente, precedente;
    int flag = 0;
    for(corrente = head, precedente = NULL; corrente != NULL; precedente = corrente, corrente = corrente->next){
        if(confrontaDate(corrente->persona.data_di_nascita, datai) >= 0 && confrontaDate(corrente->persona.data_di_nascita, dataf) <= 0){
            if(corrente == head){ //Aggiunta in testa
                head = corrente->next;
            }
            else{ //Aggiunta tra due nodi
                precedente->next = corrente->next;
            }
            *val = corrente->persona;
            flag = 1;
            free(corrente);
            break;
        }
    }
    if(!flag){
        *finito = 1;
    }
    return head;
}


