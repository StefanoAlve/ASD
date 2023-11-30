#include "personaggi.h"
#include "inventario.h"
#include "personaggi.c"
//ENUM PER SCELTE
typedef enum {
    carica_personaggi,
    carica_oggetti,
    aggiungi_personaggio,
    elimina_personaggio,
    aggiungi_rimuovi_obj,
    calcola_stat,
    fine
}comando_e;

comando_e scelta();
ptabPg filtroDati(comando_e comando, ptabPg tabPg, ptabInv tabInv);

int main() {
    char nomeFile[MAXC];
    ptabPg tabPg = (ptabPg)malloc(sizeof(*tabPg));
    ptabInv tabInv = (ptabInv)malloc(sizeof(*tabInv));
    comando_e comando = -1;
    //CICLO IN CUI SI PRENDE UNA SCELTA E SI AGISCE DI CONSEGUENZA
    while (comando != fine) {
        //FACCIO LA SCELTA
        comando = scelta();
        if (comando != fine) {
            if (comando == carica_oggetti) {
                //CASO IN CUI DEVO APRIRE IL FILE OGGETTI
                printf("inserisci il nome del file degli oggetti:\n");
                scanf("%s", nomeFile);
                tabInv = leggiInventario(nomeFile);
            } else {
                //TUTTI GLI ALTRI CASI
                tabPg = filtroDati(comando, tabPg, tabInv);
            }
        }
    }
    //DEALLOCAZIONE DI MEMORIA
    distruggiInventario(tabInv);
    distruggiPersonaggi(tabPg);
    return 0;
}

//GESTIONE DEL ENUM DI SCELTA
comando_e scelta(){
    char comando[MAXC];
    comando_e comandoE;
    printf("\n-------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\tLISTA COMANDI\n");
    printf("-------------------------------------------------------------------------------------------------------\n\n");
    printf("carica_personaggi -> carica la lista di personaggi da un file\n");
    printf("carica_oggetti -> carica gli oggetti in un vettore\n");
    printf("aggiungi_personaggio -> aggiungi un personaggio da tastiera\n");
    printf("elimina_personaggio -> elimina un personaggio scelto\n");
    printf("aggiungi_rimuovi_obj -> aggiunge o rimuove un oggetto\n");
    printf("calcola_stat -> calcola le statistiche di un personaggio\n");
    printf("fine -> uscita dal programma\n\n");
    printf("-------------------------------------------------------------------------------------------------------\n\n");

    printf("Inserisci comando:\n");
    scanf(" %s", comando);

    ///TROVO IL COMPANDO DI ENUM CORRISPONDENTE
    if(strcmp("carica_personaggi", comando) == 0){
    comandoE = 0;
    }
    else if(strcmp("carica_oggetti", comando) == 0){
    comandoE = 1;
    }
    else if(strcmp("aggiungi_personaggio", comando) == 0){
    comandoE = 2;
    }
    else if(strcmp("elimina_personaggio", comando) == 0){
    comandoE = 3;
    }
    else if(strcmp("aggiungi_rimuovi_obj", comando) == 0){
    comandoE = 4;
    }
    else if(strcmp("calcola_stat", comando) == 0){
    comandoE = 5;
    }
    else if(strcmp("fine", comando) == 0){
    comandoE = 6;
    }
    else{
    printf("errore nel comando");
    exit(1);
    }

    return comandoE;
}
//FILTRO DI COSA FARE IN BASE ALLA SCELTA
ptabPg filtroDati(comando_e comando, ptabPg tabPg, ptabInv tabInv){
    char nomeFile[MAXC], tmp[MAXC];
    pnodoPg_t x;
    struct pg_t personaggio;
    int i;


    ///GESTISCO OGNI CASISTICA
    switch (comando) {

        case carica_personaggi:
            printf("inserisci il nome del file\n");
            scanf("%s", nomeFile);
            tabPg = leggiPersonaggi(nomeFile);
            break;
        //AGGIUNTA PERSONAGGIO DA TASTIERA
        case aggiungi_personaggio:
            personaggio.equip = malloc(sizeof(*personaggio.equip));

            printf("inserisci il codice del personaggio\n");
            scanf("%s", personaggio.codice);
            printf("inserisci il nome del personaggio\n");
            scanf("%s", personaggio.nome);
            printf("inserisci la classe del personaggio\n");
            scanf("%s", personaggio.classe);
            personaggio.next = NULL;
            for(i=0; i<MAXOBJ; i++){
                personaggio.equip->vettEq[i] = -1;
            }
            printf("inserisci le stat del personaggio(6)\n");
            scanf("%d %d %d %d %d %d", &personaggio.stat.hp, &personaggio.stat.mp, &personaggio.stat.atk, &personaggio.stat.def, &personaggio.stat.mag, &personaggio.stat.spr);

            //LO INSERISCO IN LISTA
            tabPg = inserisciPg(tabPg, personaggio);

            break;

        case elimina_personaggio:
            //MOSTRO A VIDEO TUTTI I PERSONAGGI
            printf("scegli il codice del personaggio da eliminare tra questi:\n");
            x = tabPg->headPg;
            while(x != NULL) {
                stampaPg(x, tabInv);
                x = x->next;
            }
            scanf("%s", tmp);
            //RICERCO IL CODICE E CANCELLO IL PERSONAGGIO
            x = ricercaCodice(tabPg, tmp);
            tabPg = cancellaPg(tabPg, x);
            break;

        case aggiungi_rimuovi_obj:
            //MOSTRO A VIDEO TUTTI I PERSONAGGI
            printf("scegli il codice del personaggio dal quale aggiungere o eliminare l'oggetto:\n");
            x = tabPg->headPg;
            while(x != NULL) {
                stampaPg(x, tabInv);
                x = x->next;
            }
            scanf("%s", tmp);
            //CERCO IL CODICE E MODIFICO L'EQUIP DEL PERSONAGGIO
            x = ricercaCodice(tabPg, tmp);
            modificaEquip(x, tabInv);
            break;

        case calcola_stat:
            //FA LA SOMMA DELLE STAT DEL PG DOPO AVERLI FATTI VEDERE TUTTI E SCELTO 1
            printf("scegli il codice del personaggio al quale calcolare le stat:\n");
            x = tabPg->headPg;
            while(x != NULL) {
                stampaPg(x, tabInv);
                x = x->next;
            }
            scanf("%s", tmp);
            x = ricercaCodice(tabPg, tmp);
            calcoloStat(x, tabInv);
            break;

        case fine:
            break;
    }
    return tabPg;
}