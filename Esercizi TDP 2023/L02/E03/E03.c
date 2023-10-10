#include <stdio.h>
#include <ctype.h>
char inputControllato(void); //funzione che controlla l'input e restituisce il valore se viene inserito un singolo carattere se no restituisce -1
int comprimi(FILE *fin,FILE *fout); //funzione che da un file decompresso ne restituisce uno compresso, ritorna numero di caratteri prodotti
int decomprimi(FILE *fin, FILE *fout); //funzione che da un file compresso ne restituisce uno decompresso, ritorna numero di caratteri prodotti
int main(void){
    //Inizializzazione variabili
    FILE *fp_read, *fp_write;
    char sceltaIn[20], sceltaOut[20], scelta;
    int caratteri;
    //Assegnazione variabili
    caratteri = 0;
    scelta = 'L';
    //Corpo programma
    printf("Inserire nome file di input seguito da .txt:");
    gets(sceltaIn);
    printf("Inserire nome file di output seguito da .txt:");
    gets(sceltaOut);
    printf("\n====================================\n");
    printf("  Opzioni:\n");
    printf("  \t<C> Comprimi\n");
    printf("  \t<D> Decomprimi\n");
    printf("====================================\n\n");
    scelta = inputControllato();
    scelta = toupper(scelta);
    //Controllo esistenza file
    if ((fp_read = fopen(sceltaIn, "r")) ==
        NULL) { //apro in lettura sorgente.txt e ne controllo l'esistenza
        printf("Errore nell'apertura del file!\n");
        return 1;
    }
    if ((fp_write = fopen(sceltaOut, "w")) ==
        NULL) { //apro in scrittura compresso.txt e ne controllo l'esistenza
        printf("Errore nell'apertura del file!\n");
        return 2;
    }
    switch (scelta) {
        case 'C':
            caratteri = comprimi(fp_read, fp_write);
            if (caratteri != 0){
                printf("\nOperazione di compressione eseguita con successo\n");
                printf("Il file compresso contiene %d caratteri\n", caratteri);
            }
            else{
                printf("\nErrore, file vuoto!\n");
            }
            break;
        case 'D':
            caratteri = decomprimi(fp_read, fp_write);
            if (caratteri != 0) {
                printf("\nOperazione di decompresione eseguita con successo\n");
                printf("Il file decompresso contiene %d caratteri\n", caratteri);
            }
            else{
                printf("\nErrore, file vuoto!\n");
            }
            break;
        default:
            printf("Opzione inserita non valida!\n");
            return 3;
    }
    fprintf(fp_write,"\n\nNumero di caratteri: %d",caratteri); //Inserisco nel file il numero di caratteri scritti

    //Chiusura file
    fclose(fp_read);
    fclose(fp_write);
    return 0;
}

int comprimi(FILE *fin, FILE *fout){
    char carattere, caratterePrima;
    int ripetizioni, max, caratteri;
    //Assegnazione variabili
    caratterePrima = '$'; //assegno a caratterePrima '$' perchè è l'unico carattere che non sarà presente nel file
    max = 9;
    ripetizioni = 0;
    caratteri = 0;
    //Corpo funzione
    while(!feof(fin)){ //eseguo un ciclo while sul file fino all'ultimo carattere
        carattere = getc(fin);//a ogni ciclo assegno a carattere il carattere indicato dal puntatore a file fin
        if(carattere != caratterePrima) {
            if (ripetizioni <= max) { //gestisco prima il caso in cui le ripetizioni siano minori del massimo richiesto
                if (ripetizioni == 1) { //pongo questa condizione in modo da scrivere normalmente i doppi caratteri
                    fprintf(fout, "%c%c", caratterePrima, caratterePrima);
                    caratteri += 2;
                } else {
                    if (caratterePrima != '$' && ripetizioni == 0) { //controllo che caratterePrima sia diverso da '$' per evitare di stampare il carattere assegnato a inizio programma
                        fprintf(fout, "%c", caratterePrima);
                        caratteri += 1;
                    } else if (ripetizioni > 1) { //se le ripetizioni sono maggiori di uno (da tre caratteri in poi) compatto
                        fprintf(fout, "%c$%d", caratterePrima, ripetizioni);
                        caratteri += 3;
                    }
                }
            }
            ripetizioni = 0;
            caratterePrima = carattere;
        }
        else if(ripetizioni == max){ //quando le ripetizioni sono uguali a max stampo e porto ripetizioni a zero, in modo da evitare un secondo ciclo while che faccia questo controllo successivamente
            fprintf(fout, "%c$%d",caratterePrima,max);
            caratteri += 3;
            ripetizioni = 0;
            caratterePrima = carattere;
        }
        else{
            ripetizioni += 1;
        }
    }
    return caratteri;
}

int decomprimi(FILE *fin, FILE *fout){
    //Inizializzazione Variabili
    int i, caratteri;
    char caratterePrima,carattere,ripeti;
    //Assegnazione variabili
    caratteri = 0;
    ripeti = 0;
    //Corpo funzione
    while(!feof(fin)){ //eseguo un ciclo while sul file fino all'ultimo carattere
        carattere = getc(fin); //a ogni ciclo assegno a carattere il carattere indicato dal puntatore a file fin
        if (!feof(fin)) { //impongo questa condizione per evitare di stampare il char che indica il termine del file
            if(isdigit(carattere) == 0) { //isdigit restituisce 0 quando il carattere inserito non è un numero
                if (carattere != '$') {
                    fprintf(fout, "%c", carattere); //stampo il carattere in fout
                    caratteri += 1;
                    caratterePrima = carattere;
                    ripeti = 0;
                }
                else{ //se il carattere è $ pongo ripeti = 1 (vero)
                    ripeti = 1;
                }
            }
            else if (isdigit(carattere) != 0) { //se il carattere è un numero
                if (ripeti == 1) { //se prima del numero è presente $
                    for (i = (carattere-'0'); i > 0; i--) { //a i viene assegnato inizialmente l'intero che rappresenta il carattere numerico inserito e poi viene decrementata fino a 0 non compreso
                        fprintf(fout, "%c", caratterePrima); //a ogni ciclo stampo il carattere
                        caratteri += 1;
                    }
                }
                else{
                    fprintf(fout, "%c", carattere);
                    caratterePrima = carattere;
                    caratteri += 1;
                }
                ripeti = 0;
            }
        }
    }
    return caratteri;
}

char inputControllato(void) {
    char scelta,buf[50];
    printf("Inserisci un'opzione:");
    scanf("%c",&scelta);
    gets(buf); // Prendo il buffer che prosegue da scanf per controllare eventuali caratteri dopo quello ricercato.
    if (buf[0] != 0 && buf[0] != 32){ // Se il primo carattere del buf è diverso da 0 (codice ascii di \000) e diverso da 32 (codice ascii di ' '), allora significa che l'utente ha tentato di inserire, a seguito dell'operazione, un altro carattere.
        // di conseguenza, evito di continuare l'esecuzione del codice e genero errore.
        return -1;
    }
    else{
        return scelta;
    }
}