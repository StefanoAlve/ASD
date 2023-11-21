#include <stdio.h>
#include <stdlib.h>
#define lmax 15

typedef struct {
    char riga;
    int valT1;
    char colonna;
    int valT2;
}s_tessere;
typedef struct {
    int indec_tessera;
    int rotazione;
}cella_tavolo;
s_tessere *acquisisci_tessere(FILE *file,int n);
int main() {
    FILE *fin;
    int N_tessere;
    char nome_file[lmax];
    s_tessere *vett_tessere = NULL;


    printf("Insersci il nome del file che vuoi leggere: \n");
    scanf("%s",nome_file);
    if((fin = fopen(nome_file,"r"))==NULL){
        printf("Errore in apertura");
    }
    else{
        fscanf(fin,"%d",&N_tessere);
        printf("%d",N_tessere);
        vett_tessere =  acquisisci_tessere(nome_file,N_tessere);
    }
}
s_tessere *acquisisci_tessere(FILE *fin,int n){
    s_tessere *vett_tessere;
    int i = 0,j;
    vett_tessere =(s_tessere*) malloc(n*sizeof (s_tessere));
    char R, C;
    int val1,val2;

    while(fscanf(fin," %c %d %c %d ",&R,&val1,&C,&val2)==4 && i<n){
        vett_tessere[i].riga = R;
        vett_tessere[i].valT1 = val1;
        vett_tessere[i].colonna = R;
        vett_tessere[i].valT2 = val2;
        i++;
    }
    for(j = 0;j<n;j++){

        printf("%c %d %c %d",vett_tessere[j].riga,(vett_tessere[j].valT1),vett_tessere[j].colonna,(vett_tessere[j].valT2));
    }
    return vett_tessere;
}
