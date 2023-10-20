#include <stdio.h>
#include <string.h>
#define inFile "../corse.txt"
#define maxRighe 1001
#define maxL 31

// Opzioni menù
typedef enum{
    rDate = 0, rPartenza, rCapolinea, rRitardo, rRitardo_tot, rFine
}comando_e;

// Struct per leggere il file
typedef struct{
    char codiceTratta[maxL], partenza[maxL], destinazione[maxL], data[11], oraPartenza[maxL], oraArrivo[maxL];
    int ritardo;
}infoFile;

comando_e scegliComando();
void leggiFile(FILE *fin, infoFile info[], int numRighe);
void selezionaDati(infoFile info[], int numRighe, comando_e comando);
void date(infoFile info[], int numRighe);
void partenza(infoFile info[], int numRighe);
void capolinea(infoFile info[], int numRighe);
void ritardo(infoFile info[], int numRighe);
void ritardo_tot(infoFile info[], int numRighe);

int main(){
    FILE *fin;
    int numRighe;
    infoFile info[maxRighe];
    comando_e comando;

    // Apertura file di input
    if((fin = fopen(inFile, "r")) == NULL){
        printf("Errore nell'apertura di corse.txt\n");
        return 1;
    }

    // Numero di righe totale scritto nella prima riga del file
    fscanf(fin, "%d", &numRighe);

    //Scrittura del file in tabella info[]
    leggiFile(fin, info, numRighe);

    //Gestione comando da tastiera
    comando = scegliComando();
    selezionaDati(info, numRighe, comando);

    // chiusura file
    fclose(fin);

    return 0;
}

// Funzione che prende le informazioni
void leggiFile(FILE *fin, infoFile info[], int numRighe){
    int i;

    //Assegnazione delle informazioni a info[]
    for(i = 0; i < numRighe; i++){
        fscanf(fin, "%s%s%s", info[i].codiceTratta, info[i].partenza, info[i].destinazione);
        fscanf(fin, "%s%s%s%d", info[i].data, info[i].oraPartenza, info[i].oraArrivo, &info[i].ritardo);
    }
}

// Riceve da tastiera il comando e ritorna il numero corrispondente al comando
comando_e scegliComando(){
    comando_e comando;
    char scelta[31];
    // Tabella per il confronto con l'input da tastiera
    char comandi[6][31] = {"date", "partenza", "capolinea", "ritardo", "ritardo_tot", "fine"};

    printf("Inserisci comando: \n-date,\n-partenza,\n-capolinea,"
           "\n-ritardo,\n-ritardo_tot,\n-fine\n");
    scanf("%s", scelta);
    strlwr(scelta);

    // Confronto tra scelta e i comandi preimpostati, ritorno del comando selezionato (un numero)
    comando = 0;
    while(comando < 6 && strcmp(scelta, comandi[comando]) != 0){
        comando++;
    }

    return comando;
}

// Menu che chiama la funzione corrispondente al comando scritto da tastiera
void selezionaDati(infoFile info[], int numRighe, comando_e comando){
    int controllo = 1;

    while(controllo) {
        switch(comando){
            case rDate:
                date(info, numRighe);
                break;
            case rPartenza:
                partenza(info, numRighe);
                break;
            case rCapolinea:
                capolinea(info, numRighe);
                break;
            case rRitardo:
                ritardo(info, numRighe);
                break;
            case rRitardo_tot:
                ritardo_tot(info, numRighe);
                break;
            case rFine:
                controllo = 0;
                break;
            default:
                printf("Comando non valido !\n");
        }
        //se il comando è 'fine' non viene chiesto ancora il comando.
        if(comando != rFine)
            comando = scegliComando();
    }
}

