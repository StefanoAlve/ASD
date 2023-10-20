#include <stdio.h>

int gdc(int a, int b);
int pari(int a);

int main(){
    int a, b, result;

    //input
    printf("Inserisci due numeri tra cui trovare gdc:\n");
    scanf("%d %d", &a, &b);

    //Funzione per trovare il gdc
    result = gdc(a, b);

    //Output
    if(result != 0) printf("GDC = %d", result);
    else printf("Errore nel calcolo di gdc.");

    return 0;
}

int gdc(int a, int b){
    int tmp, result = 1;

    //Se b è maggiore di a, vengono scambiati
    if(a<b){
        tmp = a;
        a = b;
        b = tmp;
    }

    //Condizione di terminazione
    if( a % b == 0) return b;

    //Ricorsione per trovare gdc

    if(pari(a) && pari(b)){
        return 2 * gdc(a/2, b/2);
    }
    else if(!pari(a) && pari(b)){
        return gdc(a, b/2);
    }
    else if(pari(a) && !pari(b)){
        return gdc(a/2,b);
    }
    else{
        return gdc((a - b) / 2, b);
    }
}

int pari(int a){

    if(a % 2 == 0) return 1;

    return 0;
}
