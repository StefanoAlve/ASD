#include "graph.h"

typedef enum{
    r_exit,
    r_alfabetic_order,
    r_genera_ladj,
    r_adiacenza_mat,
    r_adiacenza_ladj
}comandi_e;


int nEdges(char *filename);
comandi_e acquisisci_cmd();
void printCMD();
void gestisci_cmd(comandi_e cmd, Graph G);


int main(int argc, char** argv) {
    int numA;
    comandi_e cmd = r_alfabetic_order;
    Graph G;
    if(argc == 2)
    {
        numA = nEdges(argv[1]);
        printf("Numero di archi: %d", numA);
        G = GRAPHinit(2*numA);
        GraphLoad(G, argv[1]);
        printf("\nAttualmente la matrice delle adiacenze e' cosi' composta:");
        print_matrix(G);
        while(cmd != r_exit){
            cmd = acquisisci_cmd();
            gestisci_cmd(cmd, G);
        }
        GRAPHfree(G);
    }
    else
        printf("\nErrore nell'esecuzione del programma, inserisci il nome del file all'apertura.");
    getchar();
    getchar();
    return 0;
}


int nEdges(char *filename)
{
    int x;
    char buff[MAXSTRLEN];
    int numV = 0;

    FILE *fin = fopen(filename, "r");
    if(fin != NULL){
        while(fscanf(fin, "%s %s %s %s %d", buff, buff, buff, buff, &x) == 5)
            numV++;
        fclose(fin);
    }
    else
        printf("\nErrore nell'apertura del file di input");
    return numV;
}



void printCMD()
{
    printf("\n\t\t\t\t\tMENU' COMANDI:");
    printf("\n0) Termina programma");
    printf("\n1) Stampa in ordine alfabetico");
    printf("\n2) Genera lista di adiacenza");
    printf("\n3) Verifica sottografo completo (da matrice)");
    printf("\n4) Verifica sottografo completo (da lista)");
}

comandi_e acquisisci_cmd()
{
    comandi_e cmd;
    printCMD();
    printf("\nInserisci il comando: ");
    scanf("%d", &cmd);
    return cmd;
}


void gestisci_cmd(comandi_e cmd, Graph G)
{
    char str1[MAXSTRLEN], str2[MAXSTRLEN], str3[MAXSTRLEN];
    switch (cmd)
    {
        case r_exit:
            printf("\nArrivederci!");
            break;
        case r_alfabetic_order:
            printf("\nEcco i vertici in ordine alfabetico:");
            SortVertex(G);
            break;
        case r_genera_ladj:
            GRAPHloadListAdj(G);
            break;
        case r_adiacenza_mat:
            printf("\nInserisci i tre nomi dei vertici (v1 v2 v3): ");
            scanf("%s %s %s", str1, str2, str3);
            check_adiacenza_mat(G, str1, str2, str3);
            break;
        case r_adiacenza_ladj:
            printf("\nInserisci i tre nomi dei vertici (v1 v2 v3): ");
            scanf("%s %s %s", str1, str2, str3);
            check_adiacenza_ladj(G, str1, str2, str3);
            break;
        default:
            printf("\nNon ho compreso il comando, riprova.");
    }


}