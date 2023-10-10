#include <stdio.h>
#include <string.h>
#define maxL 200
#define maxC 30
typedef struct{
    char parola[30];
    char codifica[10];
}dizionario;
int leggiDizio(FILE *diz, dizionario vettore_diz[maxC]);
void codifica(FILE *fin, FILE *fout, dizionario vettore_diz[maxC], int num_diz);
int main(void) {
    //Inizializzazione variabili
    FILE *fin,*diz,*fout;
    int num_diz;
    char nomeDizio[30], filein[30], fileout[30];
    dizionario vettore_diz[maxC];

    //Apertura file
    printf("\nInserire il nome del file contenente il dizionario:");
    scanf("%s",nomeDizio);
    diz = fopen(nomeDizio,"r");
    if(diz == NULL){
        printf("Errore nell'apertura del file dizionario\n");
        return 1;
    }
    printf("\nInserire il nome del file di input:");
    scanf("%s",filein);
    fin = fopen(filein,"r");
    if(fin == NULL){
        printf("Errore nell'apertura del file di input\n");
        return 2;
    }
    printf("\nInserire il nome del file di output:");
    scanf("%s",fileout);
    fout = fopen(fileout,"w");
    if(fout == NULL){
        printf("Errore nell'apertura del file di output\n");
        return 3;
    }

    //Corpo programma
    num_diz = leggiDizio(diz,vettore_diz);
    codifica(fin,fout,vettore_diz,num_diz);

    //Chiusura file
    fclose(diz);
    fclose(fin);
    fclose(fout);
    return 0;
}
//Funzioni

int leggiDizio(FILE *diz, dizionario vettore_diz[maxC]){
    //Legge il file contenente il dizionario e riempe un vettore di struct di tipo dizionario
    //Inizializzazione variabili
    int num_diz = 0;
    //Corpo funzione
    fscanf(diz,"%d",&num_diz);
    for(int i=0; i<num_diz; i++){
        fscanf(diz,"%s",vettore_diz[i].codifica);
        fscanf(diz,"%s",vettore_diz[i].parola);
    }
    return num_diz;
}

void codifica(FILE *fin, FILE *fout, dizionario vettore_diz[maxC], int num_diz){
    //Legge il file d'input, codifica tramite il dizionario e riscrive il testo codificato nel file di output
    //Inizializzazione variabili
    int i, j, cont, trovato;
    char riga[maxL];

    //Corpo programma
    while(fgets(riga, maxL, fin) != NULL){ // itero sulle righe del file
        for (i = 0; i < strlen(riga); i++){ //itero sulla riga i-esima
            trovato = 0;
            if (riga[i] != ' ' && riga[i] != '\n'){  //se fossero uguali a spazio o a \n resta trovato = 0 e verrebbe stampato giù
                for (j = 0; j < num_diz; j++){ // itero sui dizionari
                    if (riga[i] == vettore_diz[j].parola[0]) {  //se la lettera della riga i-esima è uguale alla prima lettera della parola del dizionario j-esimo
                        trovato = 1;
                        for (cont = 0; cont < strlen(vettore_diz[j].parola) && trovato == 1; cont++) {
                            if (riga[i + cont] != vettore_diz[j].parola[cont]) {
                                trovato = 0;
                            }
                        }
                    }

                    if (trovato) {
                        fprintf(fout, "%s", vettore_diz[j].codifica);
                        i = i + cont - 1;
                        break;
                    }
                }
            }
            if (trovato == 0) {
                fprintf(fout, "%c", riga[i]);
            }
        }
    }
}