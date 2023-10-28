#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define inFile "corse.txt"
#define maxRighe 1001
#define maxL 31

// Opzioni menù
typedef enum{
    rStampaFile = 0, rStampaVideo, rOrdinaData, rOrdinaCodice, rOrdinaPartenza, rOrdinaArrivo, rRicercaLineare,
    rRicercaDicotomica, rDate, rPartenza, rCapolinea, rRitardo, rRitardo_tot, rFine
}comando_e;

// Struct per leggere il file
typedef struct{
    char codiceTratta[maxL], partenza[maxL], destinazione[maxL], data[11], oraPartenza[maxL], oraArrivo[maxL];
    int ritardo;
}infoFile;

comando_e scegliComando();
int comparaCampi(infoFile *info, infoFile *key, char *campo);
void date(infoFile *info, int numRighe);
void partenza(infoFile *info, int numRighe);
void capolinea(infoFile *info, int numRighe);
void ritardo(infoFile *info, int numRighe);
void ritardo_tot(infoFile *info, int numRighe);
void leggiFile(FILE *fin, infoFile *info, int numRighe);
void selezionaDati(infoFile *info, int numRighe);
void stampaFile(infoFile *info, int numRighe);
void stampaVideo(infoFile *info, int numRighe);
void insertionSort(infoFile *info, int numRighe, char *campo);
void ricercaLineare(infoFile *info, int numRighe);
void ricercaDicotomica(infoFile *v, int N, char *k);
void stampaArray(infoFile *array);

int main(){
    FILE *fin;
    int numRighe;
    infoFile info[maxRighe];
    comando_e comando;

    // Apertura file di lettura e controllo errori
    if((fin = fopen(inFile, "r")) == NULL){
        printf("Errore nell'apertura di corse.txt\n");
        exit(1);
    }

    // Numero di righe totale scritto nella prima riga del file
    fscanf(fin, "%d ", &numRighe);

    //Scrittura del file in tabella info[]
    leggiFile(fin, info, numRighe);

    //Gestione comando da tastiera
    selezionaDati(info, numRighe);

    // chiusura file
    fclose(fin);

    return 0;
}

// Riceve da tastiera il comando e ritorna il numero corrispondente al comando
comando_e scegliComando(){
    comando_e comando;
    char scelta[maxL];

    // Tabella per il confronto con l'input da tastiera
    char comandi[14][maxL] = {"stampa_file", "stampa_video", "ordina_data", "ordina_codice",
                              "ordina_partenza","ordina_arrivo","ricerca_lineare","ricerca_dicotomica",
                              "date", "partenza","capolinea", "ritardo", "ritardo_tot", "fine"};

    //input da tastiera
    printf("------------------------------------------------------------------\n");
    printf("\t\t\tINSERISCI COMANDO\n");
    printf("------------------------------------------------------------------\n");
    printf("-stampa_file \n-stampa_video \n-ordina_data \n-ordina_codice"
           "\n-ordina_partenza \n-ordina_arrivo \n-ricerca_lineare \n-ricerca_dicotomica \n-date \n-partenza"
           "\n-capolinea \n-ritardo \n-ritardo_tot \n-fine:\n");
    scanf("%s", scelta);
    strlwr(scelta);

    // Confronto tra scelta e i comandi preimpostati, ritorno del comando selezionato (un numero)
    comando = 0;
    while(comando < 14 && strcmp(scelta, comandi[comando]) != 0){
        comando++;
    }

    return comando;
}

// Funzione che prende le informazioni
void leggiFile(FILE *fin, infoFile *info, int numRighe){
    int i;

    //Assegnazione delle informazioni a info[]
    for(i = 0; i < numRighe; i++){
        fscanf(fin, "%s%s%s", info[i].codiceTratta, info[i].partenza, info[i].destinazione);
        fscanf(fin, "%s%s%s%d", info[i].data, info[i].oraPartenza, info[i].oraArrivo, &info[i].ritardo);
    }
}

// Menu che chiama la funzione corrispondente al comando scritto da tastiera
void selezionaDati(infoFile *info, int numRighe){
    int controllo = 1;
    char key[maxL] = "\0" ;

    while(controllo){

        //Chiedo il comando
        comando_e comando = scegliComando();

        switch(comando){

            //Stampa su file
            case rStampaFile:
                stampaFile(info, numRighe);
                break;

                //Stampa a video
            case rStampaVideo:
                stampaVideo(info, numRighe);
                break;

                //Ordina secondo la data
            case rOrdinaData:
                insertionSort(info, numRighe, "data");
                printf("Vettore ordinato:\n");
                stampaVideo(info, numRighe);
                break;

                //Ordina secondo il codice
            case rOrdinaCodice:
                insertionSort(info, numRighe, "codiceTratta");
                printf("Vettore ordinato:\n");
                stampaVideo(info, numRighe);
                break;

                //Ordina secondo la partenza
            case rOrdinaPartenza:
                insertionSort(info, numRighe, "partenza");
                printf("Vettore ordinato:\n");
                stampaVideo(info, numRighe);
                break;

                //Ordina secondo la stazione di arrivo
            case rOrdinaArrivo:
                insertionSort(info, numRighe,"destinazione");
                printf("Vettore ordinato:\n");
                stampaVideo(info, numRighe);
                break;

                //Ricerca lineare
            case rRicercaLineare:
                ricercaLineare(info,numRighe);
                break;

                //Ricerca Dicotomica
            case rRicercaDicotomica:
                //input
                printf("Inserisci la sottostringa da cercare:\n");
                scanf("%s", key);

                insertionSort(info, numRighe,"partenza");
                ricercaDicotomica(info, numRighe, key);
                break;

                //Ricerca per data
            case rDate:
                date(info, numRighe);
                break;

                //Ricerca per partenza
            case rPartenza:
                partenza(info, numRighe);
                break;

                //Ricerca per capolinea
            case rCapolinea:
                capolinea(info, numRighe);
                break;

                //Ricerca ritardo
            case rRitardo:
                ritardo(info, numRighe);
                break;

                //Ritardo totale
            case rRitardo_tot:
                ritardo_tot(info, numRighe);
                break;

                //Chiusura programma
            case rFine:
                controllo = 0;
                break;

            default:
                printf("Comando non valido, riprova!\n");
        }
    }
}

// Insertion Sort
void insertionSort(infoFile *info, int numRighe, char *campo){
    int i, j;
    infoFile key;

    for(i = 1; i < numRighe; i++){
        key = info[i];
        j = i - 1;

        while(j >= 0 && comparaCampi(&info[j], &key, campo) > 0){
            info[j + 1] = info[j];
            j = j - 1;
        }
        info[j + 1] = key;
    }
}

//Compara i campi
int comparaCampi(infoFile *info, infoFile *key, char *campo){

    if(strcmp(campo, "data") == 0){
        int data = strcmp(info->data, key->data);

        //Se è zero quindi info e key sono uguali, confronto l'orario
        if(data == 0)
            return strcmp(info->oraArrivo, key->oraArrivo);
        return data;
    }

    if(strcmp(campo, "codiceTratta") == 0)
        return(strcmp(info->codiceTratta, key->codiceTratta));

    if(strcmp(campo, "partenza") == 0)
        return(strcmp(info->partenza, key->partenza));

    if(strcmp(campo, "destinazione") == 0)
        return(strcmp(info->destinazione, key->destinazione));

    //Errore
    return 0;
}

//Stampa della struct infoFile
void stampaArray(infoFile *array){
    printf("%s %s %s", array->codiceTratta, array->partenza, array->destinazione);
    printf(" %s %s %s %d\n", array->data, array->oraPartenza, array->oraArrivo, array->ritardo);
}

// Stampa log in file di scrittura
void stampaFile(infoFile *info, int numRighe){
    char nomeFile[maxL];
    FILE *fout;

    //nome file
    printf("Inserisci nome del file dove viene scritto il log:\n");
    scanf("%s", nomeFile);

    //apertura file di scrittura
    fout = fopen(nomeFile, "w");

    //stampa nel file
    for(int i = 0; i < numRighe; i++){
        fprintf(fout,"%s %s %s", info[i].codiceTratta, info[i].partenza, info[i].destinazione);
        fprintf(fout," %s %s %s %d\n", info[i].data, info[i].oraPartenza, info[i].oraArrivo, info[i].ritardo);
    }
    fclose(fout);
    printf("Log scritto con successo!\n");
}

// Stampa a video
void stampaVideo(infoFile *info, int numRighe){
    for(int i = 0; i < numRighe; i++)
        stampaArray(&info[i]);
}

//Ricerca lineare
void ricercaLineare(infoFile *info, int numRighe){
    int trovato = 0;
    char prefisso[maxL];

    //input
    printf("Inserisci il prefisso:\n");
    scanf("%s",prefisso);

    //ricerca lineare
    printf("Ecco le corrispondenza della ricerca:\n");

    for(int i = 0; i < numRighe; i++){
        if (strstr(info[i].partenza, prefisso) != NULL) {

            // La stazione di partenza contiene il prefisso
            stampaArray(&info[i]);
            trovato = 1;
        }
    }
    if(!trovato)
        printf("Nessuna corrispondenza!\n");
}

//Ricerca dicotomica
void ricercaDicotomica(infoFile *v, int N, char *k){
    int m, l = 0, r = N-1, found = 0;

    while(l <= r) {
        m = (l + r) / 2;

        //Se contiene la sotto stringa stampa
        if(strstr(v[m].partenza, k) != NULL) {
            stampaArray(&v[m]);
            found = 1;
        }

        //Se la sotto stringa è maggiore si sposta nel sotto vettore di destra
        if(strcasecmp(v[m].partenza, k) < 0 || found == 1){
            l = m+1;
            found = 0;
        }
            //si sposta nel sotto vettore di sinistra
        else
            r = m-1;
    }
}

// Stampa a seconda delle date messe
void date(infoFile *info, int numRighe){
    char start[maxL], end[maxL];
    int i, controllo = 1;

    // Prendo le informazioni scritte in input
    printf("Inserisci la data di inizio e di fine da controllare:\n");
    scanf("%s %s", start, end);

    printf("Le corse tra il %s e il %s sono:\n", start, end);
    for (i = 0; i < numRighe; i++){

        // Se start è piu piccolo ed end è piu grande della data si stampa la data
        if (strcasecmp(start, info[i].data) != 1 && strcasecmp(info[i].data, end) != 1){
            stampaArray(&info[i]);
            controllo = 0;
        }
    }
    if(controllo){
        printf("Nessuna corrispondenza trovata.");
    }
    printf("\n");
}

// Stampa in base alla partenza scritta da tastiera
void partenza(infoFile *info, int numRighe){
    char partenza[maxL];
    int i, controllo = 1;

    // Prendo la destinazione di partenza in input
    printf("Inserire la destinazione di partenza:\n");
    scanf("%s", partenza);
    printf("Le fermate con partenza %s sono:\n", partenza);

    for(i = 0; i < numRighe; i++){
        if(strcasecmp(partenza, info[i].partenza) == 0){
            stampaArray(&info[i]);
            controllo = 0;
        }
    }
    if(controllo){
        printf("Nessuna corrispondenza trovata.\n");
    }
    printf("\n");
}

// Stampa a seconda del capolinea scritto da tastiera
void capolinea(infoFile *info, int numRighe){
    char arrivo[maxL];
    int i, controllo = 1;

    // Prendo la destinazione di arrivo in input
    printf("Inserire la destinazione di arrivo:\n");
    scanf("%s", arrivo);
    printf("Le fermate con destinazione %s sono:\n", arrivo);

    for(i = 0; i < numRighe; i++){
        if(strcasecmp(arrivo, info[i].destinazione) == 0){
            stampaArray(&info[i]);
            controllo = 0;
        }
    }
    if(controllo) {
        printf("Nessuna corrispondenza trovata.\n");
    }
    printf("\n");
}

// Stampa in base alle date inserite da tastiera
void ritardo(infoFile *info, int numRighe){
    char start[maxL], end[maxL];
    int i, controllo = 1;

    // Prendo le informazioni da tastiera
    printf("Inserire le date di inizio e fine da controllare:\n");
    scanf("%s", start);
    scanf("%s", end);

    printf("Le corse tra il %s e il %s con ritardo sono:\n", start, end);
    for (i = 0; i < numRighe; i++){

        // Se start è piu piccolo ed end è piu grande della data e ritardo è diverso da 0 si stampa la data
        if (strcasecmp(start, info[i].data) != 1 && strcasecmp(info[i].data, end) != 1 && info[i].ritardo != 0){
            stampaArray(&info[i]);
            controllo = 0;
        }
    }

    if(controllo){
        printf("Nessuna corrispondenza trovata.\n");
    }
    printf("\n");
}

// Stampa in base al codice scritto da tastiera
void ritardo_tot(infoFile *info, int numRighe){
    char codice[maxL];
    int i, ritardo = 0, controllo = 1;

    //Prendo le informazioni da tastiera
    printf("Inserire il codice del mezzo da controllare:\n");
    scanf("%s", codice);
    printf("Ritardo totale del codice %s:", codice);

    for(i = 0; i < numRighe; i++){
        if(strcasecmp(codice, info[i].codiceTratta) == 0 && info[i].ritardo != 0){
            ritardo += info[i].ritardo;
            controllo = 0;
        }
    }
    if(controllo){
        printf("Nessuna corrispondenza trovata.\n");
    }
    printf(" %d\n", ritardo);
}
