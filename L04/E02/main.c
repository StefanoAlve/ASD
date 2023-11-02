#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXC 51
//Strutture
typedef struct{
    char *codice;
    char *nome;
    char *cognome;
    char *data_di_nascita;
    char *via;
    char *citta;
    int cap;
}Item;
typedef struct{
    Item persona;
    struct node *next;
}node, *link;

typedef enum{r_acquisizione,r_ricerca,r_cancellazione,r_stampa, r_fine, r_errore}comando_e;
typedef enum{i_file, i_tastiera, i_errore}input_e;
typedef enum{o_codice, o_date, o_errore}opzione_e;
//Funzioni
comando_e leggiComando();
input_e leggiInput();
void sceltaComando(comando_e comando);
opzione_e leggiOpzione();
link newNode(Item persona, link next);
Item acquisisci(FILE *fp);
void deallocaPersona(Item persona);

//newnode
int main(void) {
    //Inizializzazione variabili
    comando_e comando;
    do {
        comando = leggiComando();
        sceltaComando(comando);
    }while(comando != r_fine);
}


comando_e leggiComando(){
    //Inizializzazione variabili
    comando_e comandoE;
    char tmp[MAXC], *comando;
    //Corpo programma
    printf("Inserisci comando:");
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
void sceltaComando(comando_e comando){
    input_e input;
    opzione_e opzione;
    FILE *fp;
    Item persona;
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
                    fp = fopen(nomeFile, "r");
                    if(fp == NULL){
                        printf("Errore nell'apertura del file!\n");
                        exit(1);
                    }
                    while(!feof(fp)){
                        persona = acquisisci(fp);
                        deallocaPersona(persona);
                    }
                    fclose(fp);
                    free(nomeFile);
                    break;
                case i_tastiera:
                    printf("Inserisci i dati anagrafici <codice> <nome> <cognome> <data_di_nascita> <via> <citta'> <cap>:");
                    persona = acquisisci(stdin);
                    deallocaPersona(persona);
                    break;
            }
            break;
        case r_ricerca:
            break;
        case r_cancellazione:
            do {
                printf("Vuoi cancellare in base al codice o alle date?:");
                opzione = leggiOpzione();
            }while(opzione == o_errore);//Finchè l'utente non inserirà un parametro corretto continuerò a chiedere
            switch (opzione){
                case o_codice:
                    //cancellaCodice();
                    break;
                case o_date:
                    //cancellaDate();
                    break;
            }
            break;
        case r_stampa:
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
    link x;
    x = (node*)malloc(sizeof(node));
    if(x == NULL){
        printf("Errore nell'allocazione della memoria!\n");
        exit(1);
    }
    x->persona = persona;
    x->next = next;
    return x;
}

Item acquisisci(FILE *fp){
    //Inizializzazione variabili
    Item persona;
    char tmp[MAXC];
    //Corpo programma
    fscanf(fp," %s",tmp);
    persona.codice = strdup(tmp);
    fscanf(fp, " %s", tmp);
    persona.nome = strdup(tmp);
    fscanf(fp, " %s", tmp);
    persona.cognome = strdup(tmp);
    fscanf(fp, " %s", tmp);
    persona.data_di_nascita = strdup(tmp);
    fscanf(fp, " %s", tmp);
    persona.via = strdup(tmp);
    fscanf(fp, " %s", tmp);
    persona.citta = strdup(tmp);
    fscanf(fp, "%d", &persona.cap);

    return persona;
}

void deallocaPersona(Item persona){
    free(persona.codice);
    free(persona.nome);
    free(persona.cognome);
    free(persona.data_di_nascita);
    free(persona.via);
    free(persona.citta);
}
    //acquisizione
        //file:
            //leggiFile
            //for
            //acquisisci
        //tastiera:
            //acquisisci
    //ricerca:
        //ricerca
    //cancella:
        //per codice:
            //elimina elemento
        //per date:
            //for
            //elimina elemento
    //stampa:
        //stampa