mat.txt
#include <stdio.h>
#define max 20
int leggiFile(FILE *fp_read, int matrice[max][max], int nR, int nC);
void leggiGiornata(int matrice[max][max], int nR, int nC);
int main(void) {
    //Inizializzazione variabili
    FILE *fp_read;
    int campionato[max][max],nR,nC,errore;
    char filein[max];
    //Apertura file
    printf("Inserire nome file:");
    scanf("%s",filein);
    fp_read = fopen(filein,"r");
    if(fp_read == NULL){
        printf("Errore nell'apertura del file!\n");
        return 1;
    }
    //Corpo programma
    fscanf(fp_read,"%d %d",&nR,&nC);
    errore = leggiFile(fp_read,campionato,nR,nC);
    if(errore==1){
        printf("Alcuni valori inseriti nella matrice non sono validi!\n");
        return 2;
    }
    else if(errore!=0){
        printf("Formato matrice non accettabile!\n");
        return 3;
    }
    else{
        leggiGiornata(campionato, nR, nC);
    }
    //Chiusura file
    fclose(fp_read);
    return 0;
}
//Funzioni
int leggiFile(FILE *fp_read, int matrice[max][max], int nR, int nC){
    //Corpo funzione
    for(int r=0; r<nR; r++){
        for(int c=0; c<nC;c++){
            if(fscanf(fp_read,"%d",&matrice[r][c]) == 1) {
                if (matrice[r][c] != 0 && matrice[r][c] != 1 && matrice[r][c] != 3) {
                    return 1;
                } else {
                    printf("%d ", matrice[r][c]);
                }
            }
            else{
                return 2;
            }
        }
        printf("\n");
    }
    return 0;
}

void leggiGiornata(int matrice[max][max], int nR, int nC){
    //Inizializzazione variabili
    int i, j, somma = 0, somma_max = -1, riga = 0, k=1;
    //Corpo programma
    while(k<=nC){
        for (i = 0; i < nR; i++){
            for(j = 0; j < k; j++){
                somma += matrice[i][j];
            }
            if (somma > somma_max){
                somma_max = somma; riga = i+1; // imposto la somma max = somma e la riga corrispondente alla squadra capolista come i+1 (evito che sia 0)
            }
            somma = 0;
        }
        printf("\nLa capolista alla giornata %d e' la squadra numero %d con una somma punti pari a %d.", k, riga, somma_max);
        k++;
    }
}
