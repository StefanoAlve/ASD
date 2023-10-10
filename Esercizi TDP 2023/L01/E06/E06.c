//CALCOLATRICE DA FILE
#include <stdio.h>
int main(void) {
    //Inizializzazione variabili
    FILE *fp_read, *fp_write;
    char operazione;
    float op1, op2, risultato;
    //Controllo esistenza file
    if((fp_read = fopen("Operations.txt","r")) == NULL){
        printf("Errore nell'apertura del file\n");
        return 1;
    }
    if((fp_write = fopen("Results.txt", "w")) == NULL){
        printf("Errore nell'apertura del file\n");
        return 2;
    }
    //Corpo programma
    while (!feof(fp_read)){       //!feof = finchè  puntatore diverso da carattere di fine file continua a ciclare (ciclerà una volta anche su quel carattere prima di fermarsi)
        operazione = fgetc(fp_read);
        fscanf(fp_read," %f %f ",&op1,&op2);    //lo spazio dopo il doppio %f serve per eliminare il \n o il carattere feof
        if (operazione != '+' && operazione != '-' && operazione != '*' && operazione != '/') {
            fprintf(fp_write,"%s","Il segno inserito non e' valido");
            return 3;
        }
        else {
            switch (operazione) {
                case '+':
                    risultato = op1 + op2;
                    fprintf(fp_write,"%.3f + %.3f = %.2f\n", op1, op2, risultato);
                    break;
                case '-':
                    risultato = op1 - op2;
                    fprintf(fp_write,"%.3f - %.3f = %.2f\n", op1, op2, risultato);
                    break;
                case '*':
                    risultato = op1 * op2;
                    fprintf(fp_write,"%.3f * %.3f = %.2f\n", op1, op2, risultato);
                    break;
                case '/':
                    risultato = op1 / op2;
                    fprintf(fp_write,"%.3f / %.3f = %.2f\n", op1, op2, risultato);
                    break;
            }
        }
    }

    //Chiusura file
    fclose(fp_read);
    fclose(fp_write);
    return 0;
}