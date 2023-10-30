#include <stdio.h>
#include <string.h>

#define righemax 1001
#define lmax 31
typedef struct{ //dizionario che conterrà le informazioni del file
    char codice_tratta[lmax];
    char partenza[lmax];
    char destinazione[lmax];
    char data[lmax];
    char ora_partenza[lmax];
    char ora_arrivo[lmax];
    int ritardo;

}dict;
typedef enum{// enum con i possibili comandi che si possono scegliere
    r_date ,
    r_partenza,
    r_capolinea ,
    r_ritardo,
    r_ritardo_tot,
    r_fine
}comando_e;
void ins_in_dict(FILE *fin,dict tratte[],int righe);
comando_e scegli_comandi();
void menuParola (comando_e comando,dict tratte[lmax],int nrighefile); //in base a ciò che viene da inpunt la funzione con uno switch vede cosa deve fare
void date (dict tratte[lmax],int nrighefile);// confronta le date nel file con quelle in input
void partenze(dict tratte[lmax],int nrighefile);// confronta le partente nel file con quelle in input
void capolinea(dict tratte[lmax],int nrighefile);// confronta i capolinea nel file con quelli in input
void ritardo(dict tratte[lmax],int nrighefile);// visualizza i ritardi delle tratte inserite in input
void ritardo_tot(dict tratte[lmax],int nrighefile);// visualizza il ritardo totale della tratta inserita da input
int main() {
    int nrighefile;
    FILE *fin;
    dict tratte[lmax];
    fin  = fopen("corse.txt","r");
    if (fin == NULL){
        printf("Errore!");
        return -1;
    }
    fscanf(fin,"%d",&nrighefile);
    //printf("%d",nrighefile);
    ins_in_dict(fin,tratte,nrighefile);
    //printf("%s",comando);
    comando_e comando = scegli_comandi();

    menuParola(comando,tratte,nrighefile);
    }


void ins_in_dict(FILE *fin,dict tratte[lmax], int nrighefile)//
{
    for (int i = 0;i<nrighefile;i++)
    {
        fscanf(fin,"%s",tratte[i].codice_tratta);
        fscanf(fin,"%s",tratte[i].partenza);
        fscanf(fin,"%s",tratte[i].destinazione);
        fscanf(fin,"%s",tratte[i].data);
        fscanf(fin,"%s",tratte[i].ora_partenza);
        fscanf(fin,"%s",tratte[i].ora_arrivo);
        fscanf(fin,"%d",&tratte[i].ritardo);
        //printf("%s\n%s\n%s\n%s\n%s\n%s\n%d\n",tratte[i].codice_tratta,tratte[i].partenza,tratte[i].destinazione,tratte[i].data,tratte[i].ora_partenza,tratte[i].ora_arrivo,tratte[i].ritardo);
    }



}
comando_e scegli_comandi() {
    char opzione[lmax];
    comando_e comando;

    char comandi_possibili[6][lmax] = {"date", "partenza", "capolinea", "ritardo", "ritardo_tot", "fine"};
    printf("Inserisci il comando (possibili: 'date (aaaa/mm/gg)','partenza','capolinea','ritardo','ritardo_tot','fine'):\n");
    scanf("%s", strlwr(opzione));
    for (comando = 0; comando < 6 && strcmp(opzione, comandi_possibili[comando]) != 0; comando++) {
    }

    if (comando == 6) {
        printf("Errore");
    }

    return comando;
}
void menuParola (comando_e comando,dict tratte[lmax],int nrighefile) {
    switch (comando) {
        case r_date:
            date(tratte,nrighefile);
            break;
        case r_partenza:
            partenze(tratte,nrighefile);
            break;
        case r_capolinea:
            capolinea(tratte,nrighefile);
            break;
        case r_ritardo:
            ritardo(tratte,nrighefile);
            break;
        case r_ritardo_tot:
            ritardo_tot(tratte,nrighefile);
            break;
        case r_fine:
            break;


    }
}
void date (dict tratte[lmax],int nrighefile)
    {
        char data1[lmax],data2[lmax];
        scanf("%s",data1);
        scanf("%s",data2);
        printf("Le corse comprese tra %s e %s sono:\n",data1,data2);
        for (int i=0;i<nrighefile;i++){
            if (strcmp(data1,tratte[i].data)<=0 && strcmp(data2,tratte[i].data)>=0){
                printf("%s\n %s\n %s\n",tratte[i].codice_tratta,tratte[i].partenza,tratte[i].destinazione);
            }
        }
    }
void partenze(dict tratte[lmax],int nrighefile){
    char partenza[lmax];
    scanf("%s",partenza);
    printf("Le corse che partite da %s sono:\n",strupr(partenza));
    for (int i=0;i<nrighefile;i++){

        if (strcasecmp((partenza),tratte[i].partenza)==0){
            printf("%s\n",tratte[i].codice_tratta);
        }
    }
}
void capolinea(dict tratte[lmax],int nrighefile){
    char destinazione[lmax];
    scanf("%s",destinazione);
    printf("Le corse aventi destinzione %s sono:", strupr(destinazione));
    for (int i=0;i<nrighefile;i++){

        if (strcasecmp((destinazione),tratte[i].destinazione)==0){
            printf("%s\n",tratte[i].codice_tratta);
        }
    }
}
void ritardo(dict tratte[lmax],int nrighefile){
    char data1[lmax],data2[lmax];
    scanf("%s",data1);
    scanf("%s",data2);
    printf("Le corse che hanno ritardo tra %s e %s sono:\n",data1,data2);
    for (int i=0;i<nrighefile;i++){
        if (strcmp(data1,tratte[i].data)<=0 && strcmp(data2,tratte[i].data)>=0 && tratte[i].ritardo!=0){
            printf("%s\n %s\n %s\n",tratte[i].codice_tratta,tratte[i].partenza,tratte[i].destinazione);
        }
    }
}
void ritardo_tot(dict tratte[lmax],int nrighefile){
    char codice_tratta[lmax];
    int ritardo_tot=0;
    scanf("%s",codice_tratta);
    printf("Il ritardo complessivo che ha quella tratta e':\n");
    for (int i=0;i<nrighefile;i++){
        if(strcasecmp(codice_tratta,tratte[i].codice_tratta)==0){
            ritardo_tot+=tratte[i].ritardo;
        }
    }
    printf("%s ha un ritardo totale di %d minuti",codice_tratta,ritardo_tot);


}





