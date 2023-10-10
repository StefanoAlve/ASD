#include <stdio.h>
#define maxC 20
#define maxN 30
int leggiMatrice(int M[maxN][maxN], FILE *fp_read,int nr, int nc);
int main(void) {
    //Inizializzazione variabili
    FILE *fp_read;
    char filein[maxC];
    int M[maxN][maxN], nr, nc, errore;
    //Assegnazione variabili
    //Apertura file
    printf("Inserire nome file (max 20 caratteri):");
    scanf("%s",filein);
    fp_read = fopen(filein,"r");
    if(fp_read == NULL){
        printf("Errore nell'apertura del file!\n");
        return 1;
    }
    //Corpo programma
    if (fscanf(fp_read, "%d %d ", &nr, &nc) == 2) {
        errore = leggiMatrice(M,fp_read,nr,nc); //la funzione ritorna un numero, se è diverso da zero è capitato un errore
        if(errore!=0){
            printf("Errore nella lettura della matrice!\n"); 
            return 2;
        }
    }
    else{
        printf("Errore nel contenuto del file!\n");
        return 2;
    }
    //Chiusura file
    fclose(fp_read);
    return 0;
}

//Funzioni

int leggiMatrice(int M[maxN][maxN], FILE *fp_read,int nr, int nc){
    //Inizializzazione variabili
    for (int i = 0; i < nr; i++)
    {
        for(int j = 0; j < nc; j++)
        {
            if (fscanf(fp_read, "%d ", &M[i][j]) != 1){ // la matrice verrà restituita al main (essendo passata by reference)
                printf("\nErrore, formato della matrice errato nella riga del file n. %d.", i+1);
                return 1;
            }
            else{
                printf("%d ", M[i][j]);
            }
        }
        printf("\n");
    }
    //Corpo funzione
    return 0;
}
