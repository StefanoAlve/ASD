//CALCOLATRICE
#include <stdio.h>
int main(void) {
    //Inizializzazione variabili
    char operazione, buf[2];
    float op1 = 12929391, op2 = 12929391, risultato; //assegno a op1 e op2 due valori sentinella per cui se l'utente dovesse inserire una lettera posso restituire errore
    //Corpo programma
    printf("CALCOLATRICE\n");
    printf("-------------------------------\n"
           "Comandi:\n"
           "\t+ = Addizione\n"
           "\t- = Sottrazione\n"
           "\t* = Moltiplicazione\n"
           "\t/ = Divisione\n"
           "-------------------------------\n");
    printf("Inserisci il comando:");
    operazione = getchar();
    gets(buf); // Prendo il buffer che prosegue da getchar(ovvero tutto ciò che segue l'operazione).
    if (buf[0] != 0) // Se il primo carattere del buf è diverso da 0 (indica \000), allora
        // significa che l'utente ha tentato di inserire, a seguito dell'operazione, un altro carattere.
        // di conseguenza, evito di continuare l'esecuzione del codice e genero errore.
    {
        printf("\nErrore, operazione non valida");
        return 5;
    }
    if (operazione != '+' && operazione != '-' && operazione != '*' && operazione != '/')
    {
        printf("Il segno inserito non e' valido");
        return 1;
    }
    else
    {
        printf("Inserisci i valori dei due operandi separati da uno spazio:");
        scanf("%f %f", &op1, &op2);
        if (op1 == 12929391 || op2 == 12929391)
        {
            printf("\nErrore, uno dei due operandi ha un formato non valido");
            return 2;
        }
        printf("\nOperazione = %c       Operando1 = %.3f       Operando2 = %.3f\n\n", operazione, op1, op2);
        switch (operazione) {
            case '+':
                risultato = op1 + op2;
                printf("Eseguo l'operazione:\n\t%.3f + %.3f = %.3f", op1, op2, risultato);
                break;
            case '-':
                risultato = op1 - op2;
                printf("Eseguo l'operazione:\n\t%.3f - %.3f = %.3f", op1, op2, risultato);
                break;
            case '*':
                risultato = op1 * op2;
                printf("Eseguo l'operazione:\n\t%.3f * %.3f = %.3f", op1, op2, risultato);
                break;
            case '/':
                if (op2 == 0)
                {
                    printf("Errore, impossibile dividere per zero");
                    return 3;
                }
                risultato = op1 / op2;
                printf("Eseguo l'operazione:\n\t%.3f / %.3f = %.3f", op1, op2, risultato);
                break;
        }
    }
    return 0;
}
/*Se op2 è uguale a 0 il risultato dell'operazione divisione risulterà uguale a inf*/
