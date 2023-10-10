#include <stdio.h>
#define max 50
#define nomeFile "mappa.txt"
typedef struct{
    int altezza;
    int larghezza;
    int area;
    int coordinate[2];
}regione;
void leggiMappa(FILE *fp_read,int nr, int nc, int matrice[max][max]);
void trovaRegioni(regione vettRegioni[3], int matrice[max][max], int nr, int nc);
int main(void) {
    //Inizializzazione variabili
    FILE *fp_read;
    int nr, nc, matrice[max][max];
    regione vettRegioni[3];
    //Assegnazione variabili
    for(int h=0; h<3; h++){
        vettRegioni[h].larghezza=0;
        vettRegioni[h].altezza=0;
        vettRegioni[h].area=0;
    }
    //Apertura file
    fp_read = fopen(nomeFile,"r");
    if(fp_read==NULL){
        printf("Errore nell'apertura del file!\n");
        return 1;
    }
    //Corpo programma
    fscanf(fp_read,"%d",&nr);
    fscanf(fp_read,"%d",&nc);
    leggiMappa(fp_read,nr,nc,matrice);
    trovaRegioni(vettRegioni,matrice,nr,nc);

    //Chiusura file
    fclose(fp_read);
    return 0;
}
//Funzioni
void leggiMappa(FILE *fp_read,int nr, int nc, int matrice[max][max]){
    printf("La matrice letta risulta:\n\n");
    for(int i=0;i<nr;i++){
        for(int j=0;j<nc;j++){
            fscanf(fp_read,"%d",&matrice[i][j]);
            printf("%d ",matrice[i][j]);
        }
        printf("\n");
    }
}

void trovaRegioni(regione vettRegioni[3], int matrice[max][max], int nr, int nc){
    regione temp;
    int nero, first = 1, k;
    temp.altezza=0;
    temp.larghezza=0;
    temp.area=0;
    //Corpo funzione
    for(int i=0; i<nr; i++) // ciclo righe
    {
        for (int j = 0; j < nc; j++) // ciclo colonne
        {
            nero = matrice[i][j];
            if (nero && first) //se la casella è nera ed è la prima
            {
                temp.coordinate[0] = i;
                temp.coordinate[1] = j;
                temp.altezza = 1;
                temp.larghezza = 1;
                first = 0;
            }
            else if(nero) //se è nera ma non è la prima
                temp.larghezza++;
            if (j == nc-1  && nero || (!nero && !first))  //se l'indice di colonna è al limite destro della matrice o se la casella è bianca e non è la prima
            {
                for (k = i+1; k < nr; k++) //Ciclo verso il basso sulla colonna
                {
                    if (matrice[k][temp.coordinate[1]] == 1)
                        temp.altezza++;
                    if (matrice[k][temp.coordinate[1]] != 1 || k == nr-1)  //nel caso in cui la casella sotto sia bianca oppure nel caso in cui abbia finito la colonna assegno i vari max
                    {
                        temp.area = temp.altezza * temp.larghezza;
                        if (temp.larghezza > vettRegioni[0].larghezza) {
                            vettRegioni[0]=temp;
                        }
                        if (temp.altezza > vettRegioni[1].altezza) {
                            vettRegioni[1]=temp;
                        }
                        if (temp.area > vettRegioni[2].area) {
                           vettRegioni[2]=temp;
                        }
                        break;
                    }
                }
                first = 1;
                temp.altezza = 0;
                temp.larghezza = 0;
                temp.area = 0;
            }
        }
        first = 1;
    }
    //Stampa
    printf("\n");
    printf("Max Base: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d\n", vettRegioni[0].coordinate[0],vettRegioni[0].coordinate[1],vettRegioni[0].larghezza,vettRegioni[0].altezza,vettRegioni[0].area);
    printf("Max Altezza: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d\n", vettRegioni[1].coordinate[0],vettRegioni[1].coordinate[1],vettRegioni[1].larghezza,vettRegioni[1].altezza,vettRegioni[1].area);
    printf("Max Area: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d\n", vettRegioni[2].coordinate[0],vettRegioni[2].coordinate[1],vettRegioni[2].larghezza,vettRegioni[2].altezza,vettRegioni[2].area);
}
