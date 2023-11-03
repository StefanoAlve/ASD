#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define righemax 1000
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
typedef struct{
    dict *ordina_date[righemax];
    dict *ordina_codice[righemax];
    dict *ordina_partenza[righemax];
    dict *ordina_arrivo[righemax];
}spOrdinamenti;
typedef enum{// enum con i possibili comandi che si possono scegliere
    r_date ,
    r_partenza,
    r_capolinea ,
    r_ritardo,
    r_ritardo_tot,
    r_stampa_log,
    r_ordina_data,
    r_ordina_codice,
    r_ordina_partenza,
    r_ordina_arrivo,
    r_ricerca_lineare,
    r_ricerca_dico_part,
    r_fine
}comando_e;
void ins_in_dict(FILE *fin,dict tratte[],int righe);
comando_e scegli_comandi();
void menuParola (comando_e comando,dict tratte[lmax],spOrdinamenti *spOrdinamenti,int nrighefile); //in base a ciò che viene da inpunt la funzione con uno switch vede cosa deve fare
void date (dict tratte[lmax],int nrighefile);// confronta le date nel file con quelle in input
void partenze(dict tratte[lmax],int nrighefile);// confronta le partente nel file con quelle in input
void capolinea(dict tratte[lmax],int nrighefile);// confronta i capolinea nel file con quelli in input
void ritardo(dict tratte[lmax],int nrighefile);// visualizza i ritardi delle tratte inserite in input
void ritardo_tot(dict tratte[lmax],int nrighefile);// visualizza il ritardo totale della tratta inserita da input
void stampa_log(dict *ptratte[lmax],int nrighefile);
void ordina_per_data(dict *ptratte[lmax],int nrighemax);
void ordina_codice(dict *ptratte[lmax],int nrighefile);
void ordina_partenza(dict *ptratte[lmax],int nrighefile);
void ordina_partenza2(dict tratte[lmax],int nrighefile);
void ordina_arrivo(dict *ptratte[lmax],int nrighefile);
void ricerca_lineare(dict tratte[lmax],int nrighefile);
void ricerca_dico(dict tratte[lmax],int nrighefile);
void inizializzaSpOrdinamenti(spOrdinamenti *pOrdinamenti,int nrighefile,dict tratte[lmax]);
int main() {
    int nrighefile;
    FILE *fin;
    int *pfine = NULL,fine = 0;
    dict tratte[lmax];
    spOrdinamenti ordinamenti;
    spOrdinamenti *pOrdinameti;
    pOrdinameti = &ordinamenti;
    pfine = &fine;
    fin  = fopen("corse.txt","r");
    if (fin == NULL){
        printf("Errore!");
        return -1;
    }
    fscanf(fin,"%d",&nrighefile);
    //printf("%d",nrighefile);
    ins_in_dict(fin,tratte,nrighefile);
    //printf("%s",comando);
    fclose(fin);

    comando_e comando = scegli_comandi();
    inizializzaSpOrdinamenti(pOrdinameti,nrighefile,tratte);

    menuParola(comando,tratte,pOrdinameti,nrighefile);

}
void ins_in_dict(FILE *fin,dict tratte[lmax], int nrighefile){
    for (int i = 0;i<nrighefile;i++)
    {
        fscanf(fin,"%s",tratte[i].codice_tratta);
        fscanf(fin,"%s",tratte[i].partenza);
        fscanf(fin,"%s",tratte[i].destinazione);
        fscanf(fin,"%s",tratte[i].data);
        fscanf(fin,"%s",tratte[i].ora_partenza);
        fscanf(fin,"%s",tratte[i].ora_arrivo);
        fscanf(fin,"%d",&tratte[i].ritardo);
    }
}
comando_e scegli_comandi() {
    char opzione[lmax];
    comando_e comando;
    char comandi_possibili[13][lmax] = {"date", "partenza", "capolinea", "ritardo", "ritardo_tot", "stampa_log", "ordina_data",
                                        "ordina_codice", "ordina_partenza", "ordina_arrivo","ricerca_lineare","ricerca_dico_part", "fine"};
    printf("Inserisci il comando (possibili: 'date (aaaa/mm/gg)','partenza','capolinea','ritardo','ritardo_tot','stampa_log','ordina_data','ordina_codice','ordina_partenza','ordina_arrivo','ricerca_lineare','ricerca_dico_part','fine'):\n");
    scanf("%s", strlwr(opzione));
    for (comando = 0; comando < 12 && strcmp(opzione, comandi_possibili[comando]) != 0; comando++) {
    }

    if (comando == 12) {
        printf("Errore");
    }

    return comando;
}
void menuParola (comando_e comando,dict tratte[lmax],spOrdinamenti *spOrdinamenti ,int nrighefile) {
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
        case r_stampa_log:
            stampa_log(&tratte,nrighefile);
            break;
        case r_ordina_data:
            //ordina_per_data(&tratte,nrighefile);
            stampa_log(spOrdinamenti->ordina_date,nrighefile);
            break;
        case r_ordina_codice:
            //ordina_codice(&tratte,nrighefile);
            stampa_log(spOrdinamenti->ordina_codice,nrighefile);
            break;
        case r_ordina_partenza:
            //ordina_partenza(&tratte,nrighefile);
            stampa_log(spOrdinamenti->ordina_partenza,nrighefile);
            break;
        case r_ordina_arrivo:
            //ordina_arrivo(&tratte,nrighefile);
            stampa_log(spOrdinamenti->ordina_arrivo,nrighefile);
            break;
        case r_ricerca_lineare:
            ricerca_lineare(tratte,nrighefile);
        case r_ricerca_dico_part:
            ricerca_dico(tratte,nrighefile);
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
void stampa_log(dict *ptratte[lmax], int nrighefile){
    FILE *file;
    char scelta[lmax];
    printf("Dove vuoi stampare su 'file' o su 'schermo': \n");
    scanf("%s",scelta);
    if(strcmp(scelta,"schermo")==0){
        for(int i=0;i<nrighefile;i++) {
            printf("%s %s %s %s", ptratte[i]->codice_tratta,ptratte[i]->partenza,ptratte[i]->destinazione,ptratte[i]->data);
            printf(" %s %s %d \n",ptratte[i]->ora_partenza,ptratte[i]->ora_arrivo,ptratte[i]->ritardo);
        }
    }
    else if(strcmp(scelta,"file")==0){
        file =  fopen("stampa_log.txt","w");
        for(int i=0;i<nrighefile;i++){
            fprintf(file,"%s %s %s %s", ptratte[i]->codice_tratta,ptratte[i]->partenza,ptratte[i]->destinazione,ptratte[i]->data);
            fprintf(file," %s %s %d \n",ptratte[i]->ora_partenza,ptratte[i]->ora_arrivo,ptratte[i]->ritardo);
        }
        fclose(file);

    }
}
void ordina_per_data(dict *ptratte[lmax],int nrighefile){
    int i, j, l=0, r=nrighefile-1, x;
    dict *key;

    for (i = l+1; i <= r; i++) {
        key = ptratte[i];
        j = i - 1;
        x = 1;
        while (j >= l && x){

            if(strcmp(key->data,ptratte[j]->data)<0){
                ptratte[j+1] = ptratte[j];
            }
            else if (strcmp(key->data,ptratte[j]->data)==0 && strcmp(key->ora_partenza,ptratte[j]->ora_partenza)<0){
                ptratte[j+1] = ptratte[j];
            }
            else if(strcmp(key->data,ptratte[j]->data)==0 && strcmp(key->ora_partenza,ptratte[j]->ora_partenza)==0 && strcmp(key->ora_arrivo,ptratte[j]->ora_arrivo)<0){
                ptratte[j+1] = ptratte[j];
            }
            else{
                x =0;
            }
            if(x){
                j--;
            }
        }
        ptratte[j+1] = key;
    }
    //stampa_log(ptratte,nrighefile);
}
void ordina_codice(dict *ptratte[lmax],int nrighefile){
    dict *key;
    int i, j, l=0, r=nrighefile-1;
    for (i = l+1; i <= r; i++) {
        key = ptratte[i];
        j = i - 1;
        while(j>=l && strcmp(key->codice_tratta,ptratte[i]->codice_tratta)<0){
            ptratte[j+1]=ptratte[j];
            j--;
        }
        ptratte[j+1] = key;
    }
    //stampa_log(ptratte,nrighefile);
}
void ordina_partenza(dict *ptratte[lmax],int nrighefile){
    dict *key;
    int i, j, l=0, r=nrighefile-1;
    for (i = l+1; i <= r; i++) {
        key = ptratte[i];
        j = i - 1;
        while(j>=l && strcmp(key->partenza,ptratte[j]->partenza)<0){
            ptratte[j+1]=ptratte[j];
            j--;
        }
        ptratte[j+1] = key;
    }
   // stampa_log(ptratte,nrighefile);
}
void ordina_partenza2(dict tratte[lmax],int nrighefile){
    dict tratte2;
    int i, j, l=0, r=nrighefile-1;
    for (i = l+1; i <= r; i++) {
        tratte2 = tratte[i];
        j = i - 1;
        while(j>=l && strcmp(tratte2.partenza,tratte[j].partenza)<0){
            tratte[j+1]=tratte[j];
            j--;
        }
        tratte[j+1] = tratte2;
    }
}
void ordina_arrivo(dict *ptratte[lmax],int nrighefile){
    dict *key;
    int i, j, l=0, r=nrighefile-1;
    for (i = l+1; i <= r; i++) {
        key = ptratte[i];
        j = i - 1;
        while(j>=l && strcmp(key->destinazione,ptratte[j]->destinazione)<0){
            ptratte[j+1]=ptratte[j];
            j--;
        }
        ptratte[j+1] = key;
    }
    //stampa_log(ptratte,nrighefile);
}
void ricerca_lineare(dict tratte[lmax],int nrighefile) {
    ordina_partenza2(tratte, nrighefile);
    int i;
    char partenza[lmax];
    printf("Scegli la stazione di partenza da cercare: \n");
    scanf("%s", partenza);
    FILE *file;
    char scelta[lmax];
    printf("Dove vuoi stampare su 'file' o su 'schermo': \n");
    scanf("%s", scelta);
    for (i = 0; i < nrighefile; i++) {
        if (strcasecmp(tratte[i].partenza, partenza)==0) {
            if (strcmp(scelta, "schermo") == 0){
                printf("%s %s %s %s", tratte[i].codice_tratta, tratte[i].partenza, tratte[i].destinazione,tratte[i].data);
                printf(" %s %s %d \n", tratte[i].ora_partenza, tratte[i].ora_arrivo, tratte[i].ritardo);


            }
            else if(strcmp(scelta, "file") == 0){
                fprintf(file,"%s %s %s %s", tratte[i].codice_tratta, tratte[i].partenza, tratte[i].destinazione,tratte[i].data);
                fprintf(file," %s %s %d \n", tratte[i].ora_partenza, tratte[i].ora_arrivo, tratte[i].ritardo);

            }

        }
    }

}
void ricerca_dico(dict tratte[lmax], int nrighefile) {
    ordina_partenza2(tratte, nrighefile);
    int l = 0, r = nrighefile - 1, m, flag = 1;
    char partenza[lmax];
    printf("Scegli la stazione di partenza da cercare: \n");
    scanf("%s", partenza);
    while (l <= r && flag && flag != 2) {
        m = (r + l) / 2;
        if (strcasecmp(tratte[m].partenza, partenza) > 0) {
            r = m - 1;
        } else if (strcasecmp(tratte[m].partenza, partenza) < 0) {
            l = m + 1;
        } else if (strcasecmp(tratte[m].partenza, partenza) == 0) {
            flag = 0;

        } else {
            printf("Non è stata trovata la stazione %s", partenza);
            flag = 2;
        }
    }
    if (!flag && m != 0) {
        while (strcasecmp(tratte[m - 1].partenza, partenza) == 0) {
            m--;
        }
    }
    FILE *file;
    char scelta[lmax];
    printf("Dove vuoi stampare su 'file' o su 'schermo': \n");
    scanf("%s", scelta);
    while (strcasecmp(tratte[m].partenza, partenza) == 0) {
        if (strcmp(scelta, "schermo") == 0) {
            while (strcasecmp(tratte[m].partenza, partenza) == 0) {
                printf("%s %s %s %s", tratte[m].codice_tratta, tratte[m].partenza, tratte[m].destinazione,tratte[m].data);
                printf(" %s %s %d \n", tratte[m].ora_partenza, tratte[m].ora_arrivo, tratte[m].ritardo);
                m++;
            }
        }
        else if (strcmp(scelta, "file") == 0) {
            file = fopen("stampa_log.txt", "w");
            while (strcasecmp(tratte[m].partenza, partenza) == 0) {
                fprintf(file, "%s %s %s %s", tratte[m].codice_tratta, tratte[m].partenza, tratte[m].destinazione,tratte[m].data);
                fprintf(file, " %s %s %d \n", tratte[m].ora_partenza, tratte[m].ora_arrivo, tratte[m].ritardo);
                m++;
            }
            fclose(file);
        }
    }
}
void inizializzaSpOrdinamenti(spOrdinamenti *pOrdinamenti,int nrighefile,dict tratte[lmax]){
    for (int i =0 ;i <nrighefile;i++){
        pOrdinamenti->ordina_date[i] = &tratte[i];
        pOrdinamenti->ordina_codice[i] = &tratte[i];
        pOrdinamenti->ordina_partenza[i] = &tratte[i];
        pOrdinamenti->ordina_arrivo[i] = &tratte[i];
    }
    ordina_per_data(pOrdinamenti->ordina_date,nrighefile);
    ordina_partenza(pOrdinamenti->ordina_partenza,nrighefile);
    ordina_codice(pOrdinamenti->ordina_codice,nrighefile);
    ordina_arrivo(pOrdinamenti->ordina_arrivo,nrighefile);
}