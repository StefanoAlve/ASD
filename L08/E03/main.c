#include "collezioneTitoli.h"
#define MAXDIM 100
typedef enum {leggiFile_e, cercaTitolo_e, cercaQinData_e, cercaMaxMin_e, ribilanciaBST_e, fine_e, errore_e}comando_e;

void stampaMenu();
pCollezioneT leggiFile();
comando_e leggiComando();
void menu(pCollezioneT collezioneT, comando_e comando);
int main() {
    comando_e comando;
    pCollezioneT collezioneT;
    stampaMenu();
    collezioneT = leggiFile();
    do {
        comando = leggiComando();
        menu(collezioneT, comando);
    }while(comando != fine_e);
    return 0;
}

void stampaMenu(){
    printf("----------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\tMENU\t\t\t\t\n");
    printf("----------------------------------------------------------------------------------------------------------------\n");
    printf("<leggiFile> -> leggi i contenuti di un file ed estrapola la collezione di titoli\n");
    printf("<cercaTitolo> -> cerca un titolo nella collezione, il programma dice se il titolo è presente o meno\n");
    printf("<cercaQinData> -> cerca la quotazione di un titolo in una certa data\n");
    printf("<cercaMaxMin> -> cerca la quotazione massima e la minima in un certo intervallo di date o tra tutte le date\n");
    printf("<ribilanciaBST> -> bilancia nuovamente il BST delle quotazioni\n");
    printf("<fine> -> termina il programma\n");
    printf("----------------------------------------------------------------------------------------------------------------\n");
}

pCollezioneT leggiFile(){
    char nomeFile[MAXDIM];
    FILE *fp;
    int nTitoli;
    pCollezioneT collezione = listInit();
    pBSTquot bst;
    pTitolo titolo;
    printf("Inserisci il nome del file: ");
    scanf("%s", nomeFile);
    fp=fopen(nomeFile, "r");
    if(fp==NULL){
        printf("File inesistente!\n");
        exit(1);
    }
    fscanf(fp,"%d", &nTitoli);
    for(int i=0; i<nTitoli; i++){
        titolo = leggiTitolo(fp);
        bst = riempiBST(fp);
        nodeInsertSorted(collezione, bst, titolo);
    }
    fclose(fp);
    return collezione;
}

comando_e leggiComando(){
    char comando[MAXDIM];
    printf("Inserisci comando:");
    scanf("%s", comando);
    if(strcasecmp(comando, "leggifile") == 0){
        return leggiFile_e;
    }else if(strcasecmp(comando, "cercatitolo") == 0){
        return cercaTitolo_e;
    }else if(strcasecmp(comando, "cercaQinData") == 0){
        return cercaQinData_e;
    }else if(strcasecmp(comando, "cercaMaxMin") == 0){
        return cercaMaxMin_e;
    }else if(strcasecmp(comando, "ribilanciaBST") == 0){
        return ribilanciaBST_e;
    }else if(strcasecmp(comando, "fine") == 0){
        return fine_e;
    }else{
        return errore_e;
    }
}

void menu(pCollezioneT collezioneT, comando_e comando){
    char titolo[MAXC];
    link x;
    dQuot_s quot;
    int cmd;
    switch(comando){
        case leggiFile_e:
            deallocaCollezioneT(collezioneT);
            collezioneT = leggiFile();
            break;
        case cercaTitolo_e:
            printf("Inserisci il titolo: ");
            scanf("%s", titolo);
            ricercaTitolo(collezioneT,titolo);
            break;
        case cercaQinData_e:
            printf("Inserisci il titolo: ");
            scanf("%s", titolo);
            x = ricercaTitolo(collezioneT,titolo);
            quot = cercaQuota(x);
            stampaQuot(quot);
            break;
        case cercaMaxMin_e:
            printf("Inserisci il titolo: ");
            scanf("%s", titolo);
            x = ricercaTitolo(collezioneT,titolo);
            printf("Inserisci 0 se vuoi cercare tra due date, 1 se vuoi cercare lungo tutto il periodo registrato:");
            scanf("%d", &cmd);
            minMaxSearch(x, cmd);
            break;
        case ribilanciaBST_e:
            printf("Inserisci il titolo: ");
            scanf("%s", titolo);
            x = ricercaTitolo(collezioneT,titolo);
            //ribilanciaBST(x);
            break;
        case fine_e:
            deallocaCollezioneT(collezioneT);
            break;
        case errore_e:
            printf("Comando inesistente, riprova\n");
            break;
    }
}
