#include "client.h"
int main() {
    //Inizializzazione variabili
    ptabInv inventario;
    ptabPg listaPersonaggi;
    int fine;
    char nomeFile[MAXC];
    //Corpo programma
    printf("\n------------------\n");
    printf("  GIOCO DI RUOLO\n");
    printf("------------------\n\n");
    printf("Da quale file vuoi che estragga l'inventario:");
    scanf("%s", nomeFile);
    inventario = leggiInventario(nomeFile);
    printf("Da quale file vuoi che estragga i personaggi:");
    scanf("%s", nomeFile);
    listaPersonaggi = leggiPersonaggi(nomeFile);
    stampaInv(inventario);
    stampaListaPg(listaPersonaggi, inventario);
    do{
       fine  = menuComandi(inventario, listaPersonaggi);
    }while(!fine);
    distruggiInventario(inventario);
    distruggiListaPersonaggi(listaPersonaggi);
    return 0;
}