#include <stdio.h>
#include "grafo.h"
int contaArchi(char nomeFile[]);
void menu(pgrafo_s pGrafo);
int main() {
    //TODO inserire argv argc
    int nArchi;
    pgrafo_s pGrafo;
    nArchi = contaArchi(nomeFile);
    grafoInit(nArchi*2); //Suppongo che ogni arco colleghi due vertici distinti
    riempiGrafo(pGrafo, nomeFile);
    menu(pGrafo);
    //TODO deallocazione
    return 0;
}

int contaArchi(char nomeFile[]){
    FILE *fp;
    int nArchi = 0;
    fp=fopen(nomeFile, "r");
    if(fp==NULL){
        printf("Errore apertura file!\n");
        exit(1);
    }
    while(fscanf(fp,"%*s %*s %*s %*s %*d") == 5){
        nArchi++;
    }
    fclose(fp);
    return nArchi;
}

void menu(pgrafo_s pGrafo){
    int comando, flag = 0, scelta = 0;
    char elab1[MAXC], elab2[MAXC], elab3[MAXC];
    do{
        printf("--------------------------------------------------------\n");
        printf("1. elenca in ordine alfabetico\n");
        printf("2. dati 3 vertici verifica se sono adiacenti a coppie\n");
        printf("3. genera lista di adiacenza\n");
        printf("4. fine\n");
        printf("--------------------------------------------------------\n\n");
        printf("Inserire comando:");
        scanf("%d", &comando);
        switch(comando){
            case 1:
                elencaAlfabetico(pGrafo);
                break;
            case 2:
                printf("Inserisci il nome del primo elaboratore:");
                scanf("%s", elab1);
                printf("Inserisci il nome del secondo elaboratore:");
                scanf("%s", elab2);
                printf("Inserisci il nome del terzo elaboratore:");
                scanf("%s", elab3);
                if(flag == 1){
                    printf("Vuoi proseguire utilizzando la matrice delle adiacenze (1) o la lista di adiacenza (2)?:");
                    scanf("%d", &scelta);
                    switch(scelta){
                        case 1:
                            verificaAdiacCoppM(pGrafo, elab1,elab2,elab3);
                            break;
                        case 2:
                            verificaAdiacCoppL(pGrafo, elab1,elab2,elab3);
                            break;
                        default:
                            printf("Comando non riconosciuto!\n");
                            break;
                    }
                }else{
                    verificaAdiacCoppM(pGrafo, elab1,elab2,elab3);
                }
                break;
            case 3:
                generaListaAdiac(pGrafo);
                flag = 1;
                break;
            case 4:
                printf("Programma terminato con successo!\n");
                break;
            default:
                printf("Comando sconosciuto!");
                break;
        }
    }while(comando != 4);
}