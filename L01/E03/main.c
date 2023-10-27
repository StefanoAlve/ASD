#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>

#define MAXL 30
struct corse {
    char codice_tratta[MAXL];
    char partenza[MAXL];
    char destinazione[MAXL];
    char data[MAXL];
    char ora_partenza[MAXL];
    char ora_arrivo[MAXL];
    int ritardo;
};
enum comando_e {r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_fine, per_data, per_tratta, per_partenza, per_capolinea,} opzione;
FILE *apri_file_lettura(const char *nome_file);
FILE *apri_file_scrittura(const char *nome_file);
struct corse *leggi_tabella();
int leggiComando();
int selezionaDati(struct corse *v, int dim, int opzione);
void leggi_per_date(struct corse *v,char *data1, char *data2, int dim, int flag_ritardo, int stampa); //funzione che mi permette di elencare le corse in un certo intervallo di date
void leggi_tratte_nome_fermata(struct corse *v, char *nome_fermata, int dim, int stampa, int flag_capolinea, int len );
int calcola_ritardo_tratta(struct corse *v, char *codice_tratta, int dim, int stampa);
int selezione_stampa();
void OrdinaPerDate(struct corse *v, int dim);
void OrdinaPerCodiceCorsa(struct corse *v, int dim);
void OrdinaPerFermata(struct corse *v, int dim, int flag_capolinea);
void stampa_tratta_video(struct corse *v, int indice);
void stampa_tratta_file(struct corse *v, int indice, FILE* fout);
void RicercaDicotomica(struct corse *v, int dim, char *nome_fermata, int len);

int main() {
    FILE *fin;
    char nome_file[] = {"C:\\Users\\calve\\OneDrive\\Desktop\\primo semestre\\Algoritmi\\laboratorio\\lab01\\ES02_lab01\\corse.txt"};
    int prima_riga = 1, dim, option , richiedi_scelta = 1;
    struct corse *tratte;

    tratte = leggi_tabella();

    fin = apri_file_lettura(nome_file);
    fscanf(fin, "%d", &dim);//ricavo la lunghezza del file e quindi delle dim struct presenti nel vettore
    if (dim > 1000) {
        printf("\nLUNGHEZZA DEL FILE NON SUPPORTATA");
    }
    fclose(fin);
    while (richiedi_scelta) {
        option = leggiComando();
        richiedi_scelta = selezionaDati(tratte, dim, option);
        printf("\n%d", richiedi_scelta);
    }
    printf("\nTermine Codice");
    free(tratte);
    return 0;
}

void stampa_tratta_video(struct corse *v, int indice){
    printf("\n%s", v[indice].codice_tratta);
    printf(" %s", v[indice].partenza);
    printf(" %s", v[indice].destinazione);
    printf(" %s", v[indice].data);
    printf(" %s", v[indice].ora_partenza);
    printf(" %s", v[indice].ora_arrivo);
    printf(" %d", v[indice].ritardo);
}
void stampa_tratta_pointer(struct corse **v, int dim){
    int indice;
    printf("\n");
    for (indice = 0; indice < dim; indice++){
        printf("\n%s", v[indice]->codice_tratta);
        printf(" %s", v[indice]->partenza);
        printf(" %s", v[indice]->destinazione);
        printf(" %s", v[indice]->data);
        printf(" %s", v[indice]->ora_partenza);
        printf(" %s", v[indice]->ora_arrivo);
        printf(" %d", v[indice]->ritardo);
    }
}

void stampa_tratta_file(struct corse *v, int indice, FILE* fout){
    fprintf(fout,"\n%s", v[indice].codice_tratta);
    fprintf(fout," %s", v[indice].partenza);
    fprintf(fout," %s", v[indice].destinazione);
    fprintf(fout," %s", v[indice].data);
    fprintf(fout," %s", v[indice].ora_partenza);
    fprintf(fout," %s", v[indice].ora_arrivo);
    fprintf(fout," %d", v[indice].ritardo);
}


FILE *apri_file_lettura(const char *nome_file){ //funzione per l'apertura del file, ritorna un puntatore al file
    FILE *file= fopen(nome_file, "r");
    if(file == NULL){
        printf("\nerrore nell'apertura del file");
        return NULL;//se non viene effettuata la lettura del file non viene creato un puntatore a struct
    }
    return file;
}

FILE *apri_file_scrittura(const char *nome_file){ //funzione per l'apertura del file, ritorna un puntatore al file
    FILE *file= fopen(nome_file, "w");
    if(file == NULL){
        printf("\nerrore nell'apertura del file");
        return NULL;//se non viene effettuata la lettura del file non viene creato un puntatore a struct
    }
    return file;
}


struct corse *leggi_tabella(){ //funzione che legge la tabella contenuta nel file corse.txt
    FILE* fin;
    char nome_file[] = {"C:\\Users\\calve\\OneDrive\\Desktop\\primo semestre\\Algoritmi\\laboratorio\\lab01\\ES02_lab01\\corse.txt"};
    int prima_riga = 1,dim;


    fin = apri_file_lettura(nome_file);

    if(fin == NULL){
        printf("\nnon e' possibile leggere la tabella");
        return NULL;//se non viene effettuata la lettura del file non viene creato un puntatore a struct
    }

    if(prima_riga){
        fscanf(fin, "%d", &dim);//ricavo la lunghezza del file e quindi delle dim struct presenti nel vettore
        if(dim> 1000){
            printf("\nLUNGHEZZA DEL FILE NON SUPPORTATA");
        }
    }
    struct corse *tratte = malloc(dim * sizeof(struct corse)); //mi crea un vettore di struct di dimensione dim in cui posso allocare dinamicamente i dati presi in lettura

    for(int i = 0; i<dim; i++) { //ciclo per riempire la struttura dati con i dati estratti da file
        fscanf(fin, "%s", tratte[i].codice_tratta);
        fscanf(fin, "%s", tratte[i].partenza);
        fscanf(fin, "%s", tratte[i].destinazione);
        fscanf(fin, "%s", tratte[i].data);
        fscanf(fin, "%s", tratte[i].ora_partenza);
        fscanf(fin, "%s", tratte[i].ora_arrivo);
        fscanf(fin, "%d", &tratte[i].ritardo);

    }
    fclose(fin);
    return tratte;
}


int leggiComando(){ //funzione che legge il comando da eseguire
    char *option;
    int scelta = 6;

    printf("\n\n\ninserisci cosa vuoi ricercare fra le possibili opzioni:\n"
           "{ date, partenza, capolinea, ritardo, ritardo_tot, fine }, "
           "\n\n------------------------------------------------------\n\n"
           "- per date, due date nel formato aaaa/gg/mm;\n"
           "- per partenza la stazione di partenza, allo stesso modo per capolinea;\n"
           "- per ritardo due date nel formato aaaa/gg/mm, per ricercare le corse che in quell'intervallo hanno avuto un ritardo;\n"
           "- per ritardo_tot il codice della linea per cui calcolarlo;\n"
           "- per terminare inserire fine.\n");
    scanf("%s", option);

    printf("\nSeleziona come vuoi che venga ordinata la base dati: "
           "\n{ per_data, per_tratta, per_partenza, per_capolinea }:\n");

    if(strcmp(option,"date") == 0)                { scelta = 0; }

    else if(strcmp(option,"partenza") == 0)       { scelta = 1; }

    else if(strcmp(option,"capolinea") == 0)      { scelta = 2; }

    else if(strcmp(option,"ritardo") == 0)        { scelta = 3; }

    else if(strcmp(option,"ritardo_tot") == 0)    { scelta = 4; }

    else if(strcmp(option,"fine") == 0)           { scelta = 5; }

    else if(strcmp(option,"per_data") == 0)       { scelta = 6; }

    else if(strcmp(option,"per_tratta") == 0)     { scelta = 7; }

    else if(strcmp(option,"per_partenza") == 0)   { scelta = 8; }

    else if(strcmp(option,"per_capolinea") == 0)  { scelta = 9; }
    return scelta; //se viene inserito un termine non valido vado nel caso di default dello switch case, ritorno a richiedere il comando
}

int selezionaDati(struct corse *v, int dim, int opzione ){ //funzione che mi permette di effettuare una selezione sulla funzione da richiamare in base alla selezione ricevuta
    char data1[MAXL], data2[MAXL], input_fermata_codice[MAXL];//la variabile input_fermata_codice, viene utilizzata sia per il nome delle fermate che per il codice di tratta
    int stampa = 1, len = 0;
    switch (opzione) { //il return 1 mi permette di continuare a chiamare la funzione per la scelta dell'operazione da eseguire
        case r_date://se seguito da due date dopo il comando "date" leggerle e stampare tutte le date inserite nell'intervallo di quelle date
            printf("\ninserisci la prima data nel formato aaaa/gg/mm: ");
            scanf("%s", data1);
            printf("\ninserisci la seconda data nel formato aaaa/gg/mm: ");
            scanf("%s", data2);
            stampa = selezione_stampa();
            leggi_per_date(v,data1, data2, dim, 0, stampa);
            return 1;

        case r_partenza://se il comando "partenze" è seguito da una stazione di partenza, elencare tutte le corse corrispondenti
            printf("\nInserisci una stazione di partenza: ");
            scanf("%s", input_fermata_codice);
            stampa = selezione_stampa();
            len  = strlen(input_fermata_codice);
            RicercaDicotomica(v,dim,input_fermata_codice, len);
            return 1;

        case r_capolinea://se il comando "capolinea" è seguito da una stazione capolinea, elencare tutte le corse corrispondenti
            printf("\nInserisci un capolinea: ");
            scanf("%s", input_fermata_codice);
            len = strlen(input_fermata_codice);
            stampa = selezione_stampa();
            leggi_tratte_nome_fermata(v,input_fermata_codice, dim, stampa, 1, len);
            return 1;

        case r_ritardo:// quando seguito da delle date, elencare tutte le corse che hanno avuto un ritardo in quell'intervallo
            printf("\ninserisci la prima data nel formato aaaa/gg/mm: ");
            scanf("%s", data1);
            printf("\ninserisci la seconda data nel formato aaaa/gg/mm: ");
            scanf("%s", data2);
            stampa = selezione_stampa();
            leggi_per_date(v,data1, data2, dim, 1, stampa);
            return 1;

        case r_ritardo_tot:// quando seguito da un codice di tratta, sommare tutti i ritardi per quella tratta e stampare la somma
            printf("Inserisci il codice della tratta di cui vuoi conoscere il ritardo complessivo: ");
            scanf("%s",input_fermata_codice );
            stampa = selezione_stampa();
            calcola_ritardo_tratta(v, input_fermata_codice, dim, stampa);
            return 1;

        case r_fine://l'esecuzione del codice termina solamente in caso di selezione "fine"
            return 0;

        case per_data:
            OrdinaPerDate(v,dim);
            return 1;

        case per_tratta:
            OrdinaPerCodiceCorsa(v, dim);
            return 1;

        case per_partenza:
            OrdinaPerFermata(v,dim, 0);
            return 1;

        case per_capolinea:
            OrdinaPerFermata(v,dim, 1);
            return 1;

        default:
            printf("\nOpzione non disponibile\n");
            return 1;


    }
}


void leggi_per_date(struct corse *v,char *data1, char *data2, int dim, int flag_ritardo, int stampa){//v è puntatore al vettore di struct FUNZIONA
    int flag = 1;

    if (strcmp(data1, data2) <= 0 ) { //nel caso in cui venga data come prima data una data successiva alla seconda, l'intervallo di date non è valido
        if(stampa){
            FILE* fout = apri_file_scrittura("C:\\Users\\calve\\OneDrive\\Desktop\\primo semestre\\Algoritmi\\laboratorio\\lab01\\ES02_lab01\\lettura_date.txt");
            for (int i = 0; i < dim; i++) {
                if(strcmp(v[i].data,data1) >= 0 && strcmp(v[i].data, data2) <= 0 && !flag_ritardo) {
                    stampa_tratta_file(v, i, fout);

                    flag = 0;

                }
                if(strcmp(v[i].data,data1) >= 0 && strcmp(v[i].data, data2) <= 0 && v[i].ritardo > 0 && flag_ritardo) {
                    stampa_tratta_file(v, i, fout);
                    flag = 0;
                }
            }
            fclose(fout);
        }
        else {
            for (int i = 0; i < dim; i++ && !stampa) {
                if (strcmp(v[i].data, data1) >= 0 && strcmp(v[i].data, data2) <= 0 && !flag_ritardo) {
                    stampa_tratta_video(v, i);
                    flag = 0;
                }
                if (strcmp(v[i].data, data1) >= 0 && strcmp(v[i].data, data2) <= 0 && v[i].ritardo > 0 && flag_ritardo) {
                    stampa_tratta_video(v, i);
                    flag = 0;
                }
            }
        }
    }
    if(flag){ printf("\nintervallo di date non valido o non disponibile\n"); }
}


void leggi_tratte_nome_fermata(struct corse *v, char *nome_fermata, int dim, int stampa, int flag_capolinea, int len ){
    int flag = 1;
    if(stampa){
        FILE* fout = apri_file_scrittura("C:\\Users\\calve\\OneDrive\\Desktop\\primo semestre\\Algoritmi\\laboratorio\\lab01\\ES02_lab01\\lettura_per_stazione.txt");
        for (int i = 0; i < dim && !flag_capolinea; i++ ) { //il flag_capolinea viene utilizzato in base all'utilizzo della funzione,
            //se per la ricerca a partire da una stazione di partenza, flag_capolinea = 0, o per la ricerca
            // a partire da un capolinea flag_capolinea = 1
            if(strncasecmp(v[i].partenza,nome_fermata, len) == 0 ) {
                stampa_tratta_file(v, i, fout);
                flag = 0;
            }
        }
        for (int i = 0; i < dim && flag_capolinea; i++ ) {
            if(strncasecmp(v[i].destinazione,nome_fermata,len) == 0 ) {
                stampa_tratta_file(v, i, fout);
                flag = 0;
            }
        }
        fclose(fout);
    }
    else {
        for (int i = 0; i < dim && !flag_capolinea; i++) {
            if (strncasecmp(v[i].partenza, nome_fermata,len) == 0) {
                stampa_tratta_video(v, i);
                flag = 0;
            }
        }
        for (int i = 0; i < dim && flag_capolinea; i++) {
            if (strncasecmp(v[i].destinazione, nome_fermata,len) == 0) {
                stampa_tratta_video(v, i);
                flag = 0;
            }
        }
    }
    if(flag){ printf("\nnon ci sono tratte disponibili per questa stazione\n");}
}

int calcola_ritardo_tratta(struct corse *v, char *codice_tratta, int dim, int stampa) {
    int ritardo_tot = 0, flag = 1;
    for (int i = 0; i < dim; i++) {
        if (strcmp(v[i].codice_tratta, codice_tratta) == 0) {
            ritardo_tot += v[i].ritardo;
            flag = 0;
        }
    }
    if(stampa){
        FILE* fout = apri_file_scrittura("C:\\Users\\calve\\OneDrive\\Desktop\\primo semestre\\Algoritmi\\laboratorio\\lab01\\ES02_lab01\\ritardo_totale_linea.txt");
        fprintf(fout,"%d", ritardo_tot);
        fclose(fout);
    }
    else{ printf("\nil ritardo totale su questa tratta è di %d minuti\n", ritardo_tot); }

    if(flag){ printf("\nQuesta tratta non ha mai effettuato ritardo\n"); return ritardo_tot;}

    return ritardo_tot;
}

int selezione_stampa(){
    int flag = 1, option = 0;
    char stampa[7];

    while(flag) {
        printf("\nscegli se stampare a video o su file: ");
        scanf("%s", stampa);

        if(strcmp(stampa, "video") == 0){ printf("\nHai scelto stampa su video "); flag = 0; return option; }

        else if(strcmp(stampa, "file") == 0){  printf("\nHai scelto stampa su file"); flag = 0; option = 1; return option; }
    }
}

void OrdinaPerDate(struct corse *v, int dim){
    struct corse **ptratte, *tmp ;//**ptratte è un puntatore a un vettore di struct
    int i, j, r = dim-1, flag = 1;

    for (i =1 ; i<= dim ; i++) {
        ptratte[i] = &v[i];
    }
    for(i = 1; i <= r; i++){
        tmp = ptratte[i];
        j = i-1;
        flag = 1; //flag per lo scambio
        while(j >= 0 && flag) {
            if(strcmp(tmp->data, ptratte[j]->data) < 0)
                ptratte[j+1] = ptratte[j];
            else if(strcmp(tmp->data, ptratte[j]->data) == 0 && strcmp(tmp->ora_partenza, ptratte[j]->ora_partenza) < 0)
                ptratte[j+1] = ptratte[j];
            else if(!strcmp(tmp->data, ptratte[j]->data) && !strcmp(tmp->ora_partenza, ptratte[j]->ora_partenza) && strcmp(tmp->ora_arrivo, ptratte[j]->ora_arrivo) < 0)
                ptratte[j+1] = ptratte[j];
            else
                flag = 0;
            if (flag)
                j--;
        }
        ptratte[j+1] = tmp;
    }
    stampa_tratta_video(v, dim);
}


void OrdinaPerCodiceCorsa(struct corse *v, int dim){
    struct corse **ptratte, *tmp ;
    int i, j, r = dim-1, flag = 1;

    for (i =1 ; i<= dim ; i++) {
        ptratte[i] = &v[i];
    }
    for(i = 1; i <= r; i++){
        tmp = ptratte[i];
        j = i-1;
        while(j >= 0 && strcasecmp(tmp->codice_tratta, ptratte[j]->codice_tratta) < 0) {
            ptratte[j+1] = ptratte[j];
            j--;
        }
        ptratte[j+1] = tmp;
    }

    stampa_tratta_pointer(*ptratte, dim);
}

void OrdinaPerFermata(struct corse *v, int dim, int flag_capolinea){
    struct corse *tmp ;
    int i, j;

    for(i = 1; i < dim; i++)
    {
        tmp = &v[i];
        j = i-1;
        if (flag_capolinea)
            while (j >= 0 && strcasecmp(tmp->destinazione, v[j].destinazione) < 0)
            {
                v[j+1] = v[j];
                j--;
            }
        else if(!flag_capolinea)
            while (j >= 0 && strcasecmp(tmp->partenza, v[j].partenza) < 0)
            {
                v[j+1] = v[j];
                j--;
            }
        v[j+1] = *tmp;
    }
    stampa_tratta_video(v, dim);
}

void RicercaDicotomica(struct corse *v, int dim, char *nome_fermata, int len){
    int m = 0, found = 0, l = 0, r = dim - 1;

    while( l <= r ) {
        m = (l+r)/2;
        if (strncasecmp(v[m].destinazione, nome_fermata,len) == 0){
            stampa_tratta_video(v, m);
            found = 1;
        }
        if(strncasecmp(v[m].destinazione, nome_fermata,len) < 0 ){
            l = m+1;
        }
        else{
            r = m-1;
        }
    }
    if(found == 0){
        printf("\nnon sono state trovate informazioni relative alla fermata richiesta");
    }
}
