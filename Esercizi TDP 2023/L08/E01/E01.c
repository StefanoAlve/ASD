#include <stdio.h>
#define maxR 50
#define nomeFile "Mappa.txt"
typedef struct{
    int altezza;
    int larghezza;
    int area;
    int coordinate[2];
}regione;
int leggiMatrice(int matrice[][maxR], int *nr, int *nc, int MaxR);
int riconosciRegione(int matrice[maxR][maxR], int nr, int nc, int r, int c, int *b, int *h);
void assegnaRegione(int r, int c, int b, int h, int area, int i, regione vettRegioni[3]);
int main(void) {
    //Inizializzazione variabili
    int nr=0, nc=0, matrice[maxR][maxR], r, c, b=0, h=0, area, i, flag_sinistra, flag_sopra, errore;
    regione vettRegioni[3];
    //Corpo programma
    errore = leggiMatrice(matrice,&nr,&nc, maxR);
    if(errore){
        return 1;
    }
    for(r=0; r<nr; r++){
        for(c=0; c<nc; c++){
            //Impongo dei flag per evitare sottomatrici
            flag_sinistra=matrice[r][c-1];
            flag_sopra=matrice[r-1][c];
            if((r==0 && c == 0) || (flag_sinistra == 0 && flag_sopra == 0)) { //Se non ho caselle nere a sinistra o sopra allora cerco
                if (riconosciRegione(matrice, nr, nc, r, c, &b, &h)) {
                    area = h * b;
                    if (b > vettRegioni[0].larghezza) {
                        i=0; //i è l'indice della struct che devo riempire
                        assegnaRegione(r,c,b,h,area,i,vettRegioni);
                    }
                    if (h > vettRegioni[1].altezza) {
                        i=1;
                        assegnaRegione(r,c,b,h,area,i,vettRegioni);
                    }
                    if (area > vettRegioni[2].area) {
                        i=2;
                        assegnaRegione(r,c,b,h,area,i,vettRegioni);
                    }
                    printf("Ho trovato una regione: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d\n", r, c, b, h, area);
                }
            }
        }
    }
    printf("\n");
    printf("Max Base: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d\n", vettRegioni[0].coordinate[0],vettRegioni[0].coordinate[1],vettRegioni[0].larghezza,vettRegioni[0].altezza,vettRegioni[0].area);
    printf("Max Altezza: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d\n", vettRegioni[1].coordinate[0],vettRegioni[1].coordinate[1],vettRegioni[1].larghezza,vettRegioni[1].altezza,vettRegioni[1].area);
    printf("Max Area: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d\n", vettRegioni[2].coordinate[0],vettRegioni[2].coordinate[1],vettRegioni[2].larghezza,vettRegioni[2].altezza,vettRegioni[2].area);
    return 0;
}
//Funzioni
int leggiMatrice(int matrice[][maxR],int *nr, int *nc, int MaxR){
    //Inizializzazione variabili
    FILE *fp_read;
    //Apertura file
    fp_read = fopen(nomeFile,"r");
    //Controllo esistenza file
    if(fp_read==NULL){
        printf("Errore nell'apertura del file!\n");
        return 1;
    }
    //Corpo funzione
    fscanf(fp_read,"%d",nr);
    fscanf(fp_read,"%d",nc);
    if(*nc > 0 && *nr > 0 && *nr < MaxR) { //Controllo che il numero di righe e di colonne sia accettabile
        printf("La matrice letta risulta:\n\n");
        for (int i = 0; i < *nr; i++) {
            for (int j = 0; j < *nc; j++) {
                fscanf(fp_read, "%d", &matrice[i][j]);
                printf("%d ", matrice[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
    else{
        printf("Numero di righe o di colonne non valido!\n");
        return 2;
    }
    //Chiusura file
    fclose(fp_read);
    return 0;
}

int riconosciRegione(int matrice[maxR][maxR], int nr, int nc, int r, int c, int *b, int *h) {
    //Inizializzazione variabili
    int nero, first = 1, k;
    (*b) = 0;
    (*h) = 0;
    //Corpo funzione
    for (int j = c; j < nc; j++) // ciclo colonne
    {
        nero = matrice[r][j];
        if (!nero && first) {
            return 0;
        }
        if (nero && first) //se la casella è nera ed è la prima
        {
            (*h) = 1;
            (*b) = 1;
            first = 0;
        } else if (nero)
            (*b)++;
        if (j == nc - 1 && nero || (!nero)) {
            for (k = r + 1; k < nr; k++) {
                if (matrice[k][c] == 1)
                    (*h)++;
                if (matrice[k][c] != 1 || k == nr -1)  //nel caso in cui la casella sotto sia bianca oppure nel caso in cui abbia finito la colonna assegno i vari max
                {
                    break;
                }
            }
            break;
        }
    }
    return 1;
}

void assegnaRegione(int r, int c, int b, int h, int area, int i, regione vettRegioni[3]){
    vettRegioni[i].coordinate[0] = r;
    vettRegioni[i].coordinate[1] = c;
    vettRegioni[i].larghezza = b;
    vettRegioni[i].altezza = h;
    vettRegioni[i].area = area;
}