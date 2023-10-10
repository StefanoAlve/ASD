#include <stdio.h>
#define maxN 100
void selection(int lunghezza, int v[maxN]);
void insertion(int lunghezza, int v[maxN]);
void shell(int lunghezza, int v[maxN]);
int main(void) {
    //Inizializzazione variabili
    FILE *fp_read;
    int nr, lunghezza, vSel[maxN], vIns[maxN], vShe[maxN];
    char nome_file[40];
    //Apertura file
    printf("Inserire nome del file seguito da txt:");
    scanf("%s",nome_file);
    fp_read=fopen(nome_file,"r");
    if(fp_read==NULL){
        printf("Errore nell'apertura del file!\n");
        return 2;
    }
    //Corpo programma
    fscanf(fp_read,"%d",&nr); // numero di righe
    for(int i=0;i<nr;i++){
        fscanf(fp_read,"%d ",&lunghezza); // numero di colonne
        printf("Vettore iniziale %d:\n",i+1);
        for(int j=0; j<lunghezza;j++)
        { //riempo il vettore
            fscanf(fp_read,"%d ", &vSel[j]);
            vIns[j] = vSel[j];
            vShe[j] = vSel[j];
            printf("%d ", vSel[j]);
        }
        printf("\nSelection sort %d, elementi tot: %d.\n\n", i+1, lunghezza);
        selection(lunghezza,vSel);
        printf("\nInserction sort %d, elementi tot: %d.\n\n", i+1, lunghezza);
        insertion(lunghezza,vIns);
        printf("\nShell sort %d, elementi tot: %d.\n\n", i+1, lunghezza);
        shell(lunghezza,vShe);
        printf("\n");
    }
    //Chiusura file
    fclose(fp_read);
    return 0;
}

//Funzioni
void selection(int lunghezza, int v[maxN]){
    int i,j,min,pos,passiE=0, passiI=0, scambi=0, passiTot=0;
    for(i=0; i<lunghezza-1; i++) //Ciclo esterno
    {
        passiE++;
        //Ipotizzo che v[i] sia il numero più piccolo
        pos=i;
        min=v[i];
        for(j=i+1;j<lunghezza;j++) //Ciclo interno
        {
            //Controllo il resto del vettore da i+1 a lunghezza e cerco il numero più piccolo
            if(v[j]<min)
            {
                min=v[j];
                pos=j;
            }
            passiI++;
        }
        if(pos!=i) //Se l'indice del minimo è diverso da i allora scambio il minimo con v[i]
        {
            v[pos]=v[i];
            v[i]=min;
            scambi++;
        }
        printf("Passi interni ciclo %d: %d\n",passiE,passiI);
        passiTot = passiTot+passiI+1;
        passiI=0;
    }
    printf("Numero di scambi: %d\t Numero di passi esterni: %d\t Numero di passi totali: %d\n",scambi,passiE,passiTot);
    printf("Vettore ordinato: ");
    for(int k=0; k<lunghezza;k++){
        printf("%d ",v[k]);
    }
    printf("\n\n");
}

void insertion(int lunghezza, int v[maxN]){
    int i,j,temp,passiE=0,passiI=0,nScambi=0,passiTot=0;
    for (i = 1; i < lunghezza; i++) { //Ciclo esterno
        passiE++;
        //Assegno v[i] a variabile temporanea
        temp = v[i];
        j = i - 1;
        while (j >= 0 && temp<v[j]) { //Ciclo interno
            //Fino a quando j è maggiore o uguale a zero e temp è più piccolo di v[j] scambio v[j+1] con v[j]
            v[j+1]=v[j];
            j--;
            nScambi++;
            passiI++;
        }
        //v[j+1] diventa temp (attenzione: j è stato decrementato nel ciclo)
        v[j+1] = temp;
        printf("Passi interni ciclo %d: %d\n",passiE,passiI);
        passiTot = passiTot+passiI+1;
        passiI=0;
    }
    printf("Numero di scambi: %d\t Numero di passi esterni: %d\t Numero di passi totali: %d\n",nScambi,passiE,passiTot);
    printf("Vettore ordinato: ");
    for(int k=0; k<lunghezza;k++){
        printf("%d ",v[k]);
    }
    printf("\n\n");
}


void shell(int lunghezza, int v[maxN]){
    int i,j,h=1,temp,passiE=0, passiI=0, nScambi=0, passiTot=0;
    //Nodi di Knuth
    while(h<=lunghezza/3){
        h=3*h+1;
    }
    //Fino a quando h è maggiore o uguale a 1 procedo
    while(h>=1) {
        //Insertion sort
        for (i = h; i < lunghezza; i++) { //i parte da h e viene incrementata
            passiE++;
            temp = v[i];
            j = i - h; //j parte da i-h
            while (j >= 0 && temp<v[j]) {
                //Scrivo in v[j+h] v[j]
                v[j+h]=v[j];
                j-=h; //decremento j di h
                nScambi++;
                passiI++;
            }
            v[j+h] = temp;
            printf("Passi interni ciclo %d: %d\n",passiE,passiI);
            passiTot = passiTot+passiI+1;
            passiI=0;
        }
        h=(h-1)/3;
    }
    printf("Numero di scambi: %d\t Numero di passi esterni: %d\t Numero di passi totali: %d\n",nScambi,passiE,passiTot);
    printf("Vettore ordinato: ");
    for(int k=0; k<lunghezza;k++){
        printf("%d ",v[k]);
    }
    printf("\n\n");
}
