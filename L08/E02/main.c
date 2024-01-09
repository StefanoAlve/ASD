#include <stdio.h>
#include "grafo.h"
int contaArchi(char nomeFile[]);
int menu(pgrafo_s pGrafo);
int main(int argc, char** argv) {
    //TODO inserire argv argc
    int nArchi, flag = 0;
    arco_s *vettArchi;
    pgrafo_s pGrafo;
    //if(argc == 2) {
        nArchi = contaArchi("grafo.txt");
        pGrafo = grafoInit(nArchi * 2); //Suppongo che ogni arco colleghi due vertici distinti
        GraphLoad(pGrafo, "grafo.txt");
        printf("\nAttualmente la matrice delle adiacenze e' cosi' composta:");
        print_matrix(pGrafo);
        flag = menu(pGrafo);
        distruggiGrafo(pGrafo, flag);
    //}else{
        //printf("\nErrore nell'esecuzione del programma, inserisci il nome del file all'apertura.");
    //}
    return 0;
}

int contaArchi(char nomeFile[]){
    FILE *fp;
    int nArchi = 0, x;
    char buff[MAXC];
    fp=fopen(nomeFile, "r");
    if(fp==NULL){
        printf("Errore apertura file!\n");
        exit(1);
    }
    while(fscanf(fp,"%s %s %s %s %d", buff,buff,buff,buff,&x) == 5){
        nArchi++;
    }
    fclose(fp);
    return nArchi;
}

int menu(pgrafo_s pGrafo){
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
        //TODO Inserire Controllo su input
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
                GRAPHloadListAdj(pGrafo);
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
    return flag;
}