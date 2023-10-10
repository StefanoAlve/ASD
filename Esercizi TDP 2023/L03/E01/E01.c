#include <stdio.h>
#include <ctype.h>
#define filein "input.txt"
#define fileout "testo.txt"
int main(void) {
    //Inizializzazione variabili
    FILE *fp_read, *fp_write;
    char carattere, carattereDopo;
    int caratteriOr, maiuscolo, count; //caratteriOr indica i caratteri del file originale, count invece serve per tenere il conto dei caratteri scritti in una riga del file nuovo
    //Assegnazione variabili
    count = 0;
    maiuscolo = 0;
    caratteriOr = 0;
    //Controllo esistenza file
    fp_read = fopen(filein, "r");
    fp_write = fopen(fileout,"w");
    if (fp_read == NULL){
        printf("Impossibile aprire file di input!\n");
        return 1;
    }
    if (fp_write == NULL){
        printf("Impossibile aprire file di output!\n");
        return 2;
    }
    //Corpo programma
    if(!feof(fp_read)){ //controllo che il file in input non sia vuoto e leggo il promo carattere
        carattereDopo = getc(fp_read);
    }
    else{
        printf("Errore, file vuoto!");
        return 3;
    }
    while(!feof(fp_read)){
        carattere = carattereDopo; //assegno a carattere il valore di carattereDopo del ciclo precedente
        carattereDopo = getc(fp_read);

        if (carattere == '\n') { //se il carattere letto nel file di input è '\n' stampo degli spazi aggiuntivi per completare i 25 caratteri richiesti
            for (int i = count; i < 25; i++) {
                fprintf(fp_write, " ");
            }
            fprintf(fp_write,"| c:%d \n", caratteriOr+1);
            count = 0;
            caratteriOr = 0;
        }
        else {
            if (count == 25){
                fprintf(fp_write,"| c:%d \n",caratteriOr);
                fprintf(fp_write,"%c",carattere);
                count = 0;
                caratteriOr = 0;
            }
            else {
                if (isdigit(carattere) != 0) {
                    fprintf(fp_write, "*");
                }

                else if (ispunct(carattere) != 0) {
                    if (carattere == '!' || carattere == '.' || carattere == '?') {
                        maiuscolo = 1;
                    }
                    if (carattereDopo != ' ' && carattereDopo != '\n') {
                        fprintf(fp_write, "%c ", carattere);
                        count++;
                    } else {
                        fprintf(fp_write, "%c", carattere);
                    }
                }

                else if (isalpha(carattere) != 0 && maiuscolo == 1) {
                    fprintf(fp_write, "%c", toupper(carattere));
                    maiuscolo = 0;
                }
                else {
                    fprintf(fp_write, "%c", carattere);
                }
            }
            caratteriOr++;
            count++;
        }
    }
    for (int i = count; i < 25; i++) { //quando il while termina avrò per forza carattere = EOF quindi non impongo la condizione in un if perchè risulterebbe sempre vera
        fprintf(fp_write, " "); //completo la riga con gli spazi mancanti
    }
    fprintf(fp_write,"| c:%d \n", caratteriOr+1); //stampo il numero di caratteri originali scritti

    //Chiusura file
    fclose(fp_read);
    fclose(fp_write);
    return 0;
}
