#include "titleList.h"

typedef enum{
    r_exit,
    r_acquisisci,
    r_print,
    r_ricerca_tit,
    r_ricerca_quot,
    r_ricerca_min_max1,
    r_ricerca_min_max2,
    r_bilanciamento,
}comandi_e;

void stampa_menu();
comandi_e acquiscisci_cmd();
pList handle_command(pList list, comandi_e cmd);

int main(void)
{
    comandi_e cmd = r_acquisisci;
    int first = 1;
    pList collezione = NULL;
    while(cmd!=r_exit){
        if(!first)
        {
            stampa_menu();
            cmd = acquiscisci_cmd();
        }
        collezione = handle_command(collezione, cmd);
        first = 0;
    }
    return 0;
}


void stampa_menu(){
    printf("\n=====================\n");
    printf("1) Leggi un file\n");
    printf("2) Stampa i contenuti del file\n");
    printf("3) Ricerca di un titolo azionario\n");
    printf("4) Ricerca della quotazione di un titolo in una certa data\n");
    printf("5) Ricerca della quotazione minima e massima dato un titolo e un range di date\n");
    printf("6) Ricerca della quotazione minima e massima dato un titolo nell'intero periodo\n");
    printf("7) Bilanciamento dell'albero delle quotazioni, dato un titolo\n");
    printf("0) Termina l'esecuzione del programma\n");
}


comandi_e acquiscisci_cmd()
{
    comandi_e cmd;
    printf("\nInserisci il numero del comando che vuoi eseguire:");
    scanf("%d", &cmd);
    if(cmd == 0) cmd = r_exit;
    else if(cmd == 1) cmd = r_acquisisci;
    else if(cmd == 2) cmd = r_print;
    else if(cmd == 3) cmd = r_ricerca_tit;
    else if(cmd == 4) cmd = r_ricerca_quot;
    else if(cmd == 5) cmd = r_ricerca_min_max1;
    else if(cmd == 6) cmd = r_ricerca_min_max2;
    else if(cmd == 7) cmd = r_bilanciamento;
    else cmd = 8;
    return cmd;
}

pList handle_command(pList list, comandi_e cmd)
{
    char filename[MAXLEN], title[MAXLEN];
    int soglia = 1;
    link x;
    FILE *fp = NULL;
    switch(cmd)
    {
        case r_exit:
        {
            printf("\nArrivederci!");
            freeALL(list);
            break;
        }
        case r_acquisisci:
        {
            if(list != NULL)
                freeALL(list);
            else
                list = listInit();
            printf("\nInserisci il nome del file:");
            scanf("%s", filename);
            fp = fopen(filename, "r");
            if(fp != NULL)
            {
                leggi_file(list, fp);
                printf("\nFile successfully loaded.");
                fclose(fp);
            }
            else
                printf("\nErrore nell'apertura del file, riprova");
            break;
        }
        case r_print:{
            printf("\nEcco i titoli presenti nel file con le rispettive quotazioni medie giornaliere:");
            printInfo(list);
            break;
        }
        case r_ricerca_tit:
        {
            printf("\nInserisci il titolo da ricercare:");
            scanf("%s", title);
            if(searchBYtitle(list, title) != NULL)
                printf("\nTitle found.");
            else
                printf("\nTitle not found.");
            break;
        }
        case r_ricerca_quot:
        {
            printf("\nInserisci il titolo da ricercare:");
            scanf("%s", title);
            x = searchBYtitle(list, title);
            if(x != NULL)
                search_for_quot(x);
            else
                printf("\nTitolo non trovato.");
            break;
        }
        case r_ricerca_min_max1:
        {
            printf("\nInserisci il titolo da ricercare:");
            scanf("%s", title);
            x = searchBYtitle(list, title);
            if(x != NULL)
                min_max_between_dates(x, 1);
            else
                printf("\nTitolo non trovato.");
            break;
        }
        case r_ricerca_min_max2:
        {
            printf("\nInserisci il titolo da ricercare:");
            scanf("%s", title);
            x = searchBYtitle(list, title);
            if(x != NULL)
                min_max_between_dates(x, 2);
            else
                printf("\nTitolo non trovato.");
            break;
        }
        case r_bilanciamento:
        {
            printf("\nInserisci il titolo da ricercare:");
            scanf("%s", title);
            printf("\nInserisci la soglia (rapporto tra cammino piu' lungo e piu' corto):");
            scanf("%d", &soglia);
            x = searchBYtitle(list, title);
            if(x != NULL)
                balance(x, soglia);
            else
                printf("\nTitolo non trovato.");
            break;
        }
        default:
            printf("\nNon ho compreso il tuo comando, riprova.");
    }
    return list;
}


// dato un titolo precedentemente selezionato, bilanciamento dell'albero di quotazioni se il rapporto tra il cammino piu' lungo e piu' corto nell'albero
// supera una certa soglia S.
// e' possibile bilanciare un dato BST mediante applicazione ricorsiva del partizionamento rispetto alla chiave mediana,