
#ifndef E03_CLIENT_H
#define E03_CLIENT_H
#include "pg.h"

typedef enum{r_stampaObj, r_stampaObjS, r_stampaObjT, r_stampaInv, r_erroreInv}comandiInv_e;
typedef enum{r_inserisciPg, r_cancellaPg, r_stampaPg, r_stampaPgN, r_stampaPgCl, r_stampaPgS, r_stampaPgEq, r_stampaObjInUso, r_aggiungiObj, r_rimuoviObj, r_scegliInUso, r_stampaListaPg, r_errorePg}comandiPg_e;

int menuComandi(ptabInv inventario, ptabPg listaPersonaggi);
comandiInv_e leggiComandoInv();
void eseguiCmdInv(ptabInv inventario, comandiInv_e comandoInvE);
comandiPg_e leggiComandoPg();
void eseguiCmdPg(ptabPg listaPersonaggi, comandiPg_e comandoPgE, ptabInv inventario);

#endif //E03_CLIENT_H
