#include <stdio.h>
#define filein "numeri.txt"

int main(void) {
    //Inizializzazione variabili
    FILE *fp_read;
    int numero, count, primo, secondo, max, min, scarta, scartati;
    //Assegnazione variabili
    primo = 0;
    secondo = 0;
    count = 0;
    scarta = 0;
    scartati = 0;
    //Controllo esistenza file
    fp_read = fopen(filein,"r");
    if (fp_read == NULL){
        printf("Errore nell'apertura del file!\n");
        return 1;
    }
    //Corpo programma
    while(!feof(fp_read)){
        fscanf(fp_read,"%d", &numero);
        count++;
        if (count == 1) { //primo ciclo
            secondo = numero;
        }
        if (count == 2){ //secondo ciclo
            if (numero >= secondo){ //faccio il primo controllo di max e min
                max = numero;
                min = secondo;
            }
            else{
                max = secondo;
                min = numero;
            }
        }
        else if (count > 2){ //restanti cicli
            if (secondo != 0){ //prima controllo che secondo sia diverso da zero
                if ((primo / secondo) == numero){ //nel caso affermativo controllo se numero è uguale alla divisione dei precedenti
                    scarta = 0;
                }
                else{
                    scarta = 1;
                }

            } else scarta=0;
            if ((primo + secondo == numero) || (primo - secondo == numero) || (primo * secondo == numero) || (scarta == 0)){ //controllo le operazioni rimanenti
                    scarta = 0;
            } else scarta = 1;

            if (numero > max){ //verifico max e min
                max = numero;
                if (max < min){
                    min = max;
                }
            }
            else{
                if (numero < min){
                    min = numero;
                }
            }
        }

        if (scarta == 1){ //se scarta è uguale ad 1 scarto il numero e non lo salvo nelle altre variabili
            scartati++;
            scarta = 0;
            printf("Ho scartato il numero %d\n", numero);
        }
        else{
            primo = secondo;
            secondo = numero;
        }
    }
    printf("\nNumero massimo: %d\n", max);
    printf("Numero minimo: %d\n", min);
    printf("Numeri scartati: %d\n", scartati);
    //Chiusura file
    fclose(fp_read);
    return 0;
}