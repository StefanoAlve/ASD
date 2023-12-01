#include "pg.h"


typedef enum{
    r_exit,
    r_stampa_tutti_pg,
    r_stampa_inv,
    r_aggiungi_pg,
    r_elimina_pg,
    r_stampa_stats,
    r_modifica_equip,
    r_pass
}comandi_menu;

comandi_menu stampa_menu(void);



int main() {
    ptabInv inventario;
    ptabPg personaggi = inizializza_personaggi();
    comandi_menu comando;
    int finito = 0;
    char file_name[max_strlen];
    char ausiliario[max_strlen];
    char code[max_code_lenght];
    nodoPg_t pg;
    printf("\n\t\t\t\t\t\t\t\t\t\tBENVENUTO");
    printf("\nInserisci il nome del file da cui leggere l'inventario:");
    scanf("%s", file_name);
    inventario = leggi_inventario(file_name);
    if(inventario != NULL)
        printf("\n\t\t\t\t\t\t\t\t   Inventario correttamente caricato!");
    getchar();
    while(!finito)
    {
        comando = stampa_menu();
        switch(comando)
        {
            case r_stampa_inv:
            {
                stampa_inv(inventario);
                break;
            }
            case r_aggiungi_pg:
            {
                printf("\nInserisci il nome del file oppure digita 'tastiera':");
                scanf("%s", file_name);
                personaggi = leggi_pg(personaggi, file_name);
                printf("\nPersonaggi correttamente caricati.");
                break;
            }
            case r_stampa_tutti_pg:{
                stampa_tutti_pg(personaggi);
                break;
            }
            case r_elimina_pg:{
                stampa_tutti_pg(personaggi);
                printf("\nInserisci il codice del personaggio da eliminare:");
                scanf("%s", code);
                pg = ricerca_x_code(personaggi, code);
                cancella_personaggio(personaggi, pg);
                break;
            }
            case r_modifica_equip:
            {
                printf("\nEcco tutti i personaggi disponibili:");
                stampa_tutti_pg(personaggi);
                printf("\nInserisci il codice del personaggio cui vuoi modificare dell'equipaggiamento:");
                scanf("%s", code);
                pg = ricerca_x_code(personaggi, code);
                if(pg != NULL)
                {
                    printf("\n\t\t\t\t\t\t\t\t\tEQUIPAGGIAMENTO ATTUALE:");
                    stampa_equip(inventario, pg);
                    printf("\nVuoi *aggiungere*, *eliminare*, *selezionare* un oggetto da usare presente nell'equipaggiamento oppure *visualizzare* l'equipaggiamento?");
                    scanf("%s", ausiliario);

                    if(!strcasecmp(ausiliario, "aggiungere")){
                        printf("\nEcco tutti gli oggetti disponibili:");
                        stampa_inv(inventario);
                        printf("\nChe oggetto vorresti aggiungere all'equipaggiamento del personaggio da te scelto?");
                        scanf("%s", ausiliario);
                        aggiungi_equip(pg, inventario, ausiliario);
                    }
                    else if(!strcasecmp(ausiliario, "eliminare")){
                        printf("\n\t\t\t\t\t\t\t\t\tEQUIPAGGIAMENTO ATTUALE:");
                        stampa_equip(inventario, pg);
                        printf("\nChe oggetto vorresti eliminare dall'equipaggiamento del personaggio da te scelto?");
                        scanf("%s", ausiliario);
                        rimuovi_equip(pg, inventario, ausiliario);
                    }
                    else if(!strcasecmp(ausiliario, "selezionare"))
                    {
                        printf("\n\t\t\t\t\t\t\t\t\tEQUIPAGGIAMENTO ATTUALE:");
                        stampa_equip(inventario, pg);
                        printf("\nQuale tra gli oggetti sopra-citati vuoi equipaggiare?");
                        scanf("%s", ausiliario);
                        scegli_equip_in_uso(pg, inventario, ausiliario);
                    }
                    else if(!strcasecmp(ausiliario, "visualizzare")){
                        printf("\n\t\t\t\t\t\t\t\t\tEQUIPAGGIAMENTO ATTUALE:");
                        stampa_equip(inventario, pg);
                    }
                    else
                        printf("\nNon ho compreso il tuo comando, riprova.");
                }
                else
                    printf("\nRiprova.");
                break;
            }
            case r_stampa_stats:
            {
                printf("\nInserisci il codice del personaggio del quale vuoi stampare le statistiche:");
                scanf("%s", code);
                pg = ricerca_x_code(personaggi, code);
                printf("\nEcco l'equipaggiamento attuale del tuo personaggio:");
                stampa_equip(inventario, pg);
                stampa_pg_compreso_stats_oggetti(inventario, pg);
                break;
            }
            case r_exit:{
                printf("\nArrivederci.");
                distruggi_inventario(inventario);
                freeALL(personaggi);
                finito = 1;
                break;
            }
            default:
                break;
        }
    }
    return 0;
}







comandi_menu stampa_menu(void){
    int cmd = 0;
    comandi_menu menu;
    printf("\n\n\t\t\t\t\t\t\t\t\t\t  MENU");
    printf("\n0)Chiudere il gioco;");
    printf("\n1)Aggiungere uno o piu' personaggi;");
    printf("\n2)Eliminare un personaggio;");
    printf("\n3)Stampare tutti i personaggi presenti");
    printf("\n4)Stampare tutti gli oggetti disponibili");
    printf("\n5)Gestisci l'equipaggiamento di un personaggio.");
    printf("\n6)Stampare le statistiche di un personaggio");
    printf("\nInserisci il comando:");
    scanf("%d", &cmd);
    if(cmd == 0)
        menu = r_exit;
    else if(cmd == 1)
        menu = r_aggiungi_pg;
    else if(cmd == 2)
        menu = r_elimina_pg;
    else if(cmd == 3)
        menu = r_stampa_tutti_pg;
    else if(cmd == 4)
        menu = r_stampa_inv;
    else if(cmd == 5)
        menu = r_modifica_equip;
    else if(cmd == 6)
        menu = r_stampa_stats;
    else{
        printf("\nNon ho compreso il tuo comando.");
        menu = r_pass;
    }
    return menu;
}