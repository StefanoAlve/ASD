#include <stdio.h>
//Prototipo di inputIntero
int inputIntero(int nValore);
//funzione main
int main(void){
    //Inizializzazione variabili
    int numero1, numero2, resto, count, scambio;
    count = 0;
    //Corpo del programma
    printf("====================\n");
    printf(" Calcolatore di MCD\n");
    printf("====================\n\n");

    numero1 = inputIntero(1);//inserisco dentro la funzione 1 per indicare che quello che la funzione andrà a chiedere sarà il primo numero
    if (numero1 == -1){ //se la funzione inputIntero trova un problema restituisce -1 quindi faccio fermare il programma con codice 1 indicando errore
        printf("\nPrimo valore inserito non valido!");
        return 1;
    }
    else {
        numero2 = inputIntero(2);//inserisco dentro la funzione 2 per indicare che quello che la funzione andrà a chiedere sarà il secondo numero
        if (numero2 == -1){
            printf("\nSecondo valore inserito non valido!");
            return 2;
        }
        else {
            printf("\n"); //inserisco un \n prima del do while per rendere più leggibile l'output
            if (numero2 > numero1) { //se numero 2 è maggiore di numero1 allora inverto i valori
                scambio = numero1;
                numero1 = numero2;
                numero2 = scambio;
            }
            do { //dato che la prima iterazione è sempre necessaria ho optato per un ciclo do while
                count += 1;
                resto = numero1 % numero2;
                printf("passo%d: %d %% %d = %d\n", count, numero1, numero2, resto);
                numero1 = numero2;
                numero2 = resto;
            } while (resto > 0);
            printf("\nRisultato: MCD = %d", numero1);
        }
    }
    return 0;
}

int inputIntero(int nValore) {
    int numero = -1; //Assegno a numero un carattere sentinella -1 per gestire gli errori in input
    char buf[50];
    printf("Inserire valore del %d^ numero (intero positivo):",nValore);
    scanf("%d",&numero);
    gets(buf); // Prendo il buffer che prosegue da scanf per controllare eventuali caratteri dopo un numero.
    if (buf[0] != 0) // Se il primo carattere del buf è diverso da 0 (codice ascii di \000), allora
        // significa che l'utente ha tentato di inserire, a seguito dell'operazione, un altro carattere.
        // di conseguenza, evito di continuare l'esecuzione del codice e genero errore.
    {
        return -1;
    }
    else{
        if (numero <= 0){ //non richiamo il valore sentinella -1 perchè essendo negativo mi permette di ottimizzare la if escludendo un eventuale ||
            return -1;
        }
        else {
            return numero;
        }

    }
}