#include <stdio.h>
#include <stdlib.h>

int majority(int *a, int N);

int main(){
    int n, maj, *vett;

    printf("Quanti elementi vuoi inserire nel vettore? :\n");
    scanf("%d", &n);
    printf("Inserire uno sotto l'altro i valori:\n");
    vett = malloc(n*sizeof *vett); //allocazione dinamica vettore
    for (int i = 0; i < n; i++)
        scanf("%d", vett+i); //inserimento valori nel vettore
    maj = majority(vett, n); //chiamata a funzione
    printf("Elemento maggioritario:\n");
    if (maj >= 0) printf("%d", maj);
    else printf("Nessun elemento maggioritario\n");
    free(vett); //deallocazione memoria

    return 0;
}

//Funzione ricorsiva: divide il vettore in due e cerca il maggioritario in entrambi;
//se almeno uno dei 2 esiste, si contano le occorrenze nel vettore di partenza e se
//supera il controllo viene ritornato
int majority(int *a, int n){
    int mdx, msx, cnt = 0;
    if (n == 1) return a[0]; //condizione di terminazione

    //chiamate ricorsive
    msx = majority(a, n/2);
    mdx = majority(a+n/2, n-n/2);

    //se è stato trovato un maggioritario nel vettore dx si contano le occorrenze,
    //se invece nel sx conto le sue occorrenze
    if (mdx != -1){
        for (int i = 0; i < n; i++){
            if (a[i] == mdx) cnt++;
        }
        if (cnt > n/2) return mdx;
        else return -1;
    } else if (msx != -1){
        for (int i = 0; i < n; i++){
            if (a[i] == msx) cnt++;
        }
        if (cnt > n/2) return msx;
        else return -1;
    } else return -1;

    /*
     senza ripetizione di codice

     if (mdx == msx){
        return msx; //Se i due maggioritari sono uguali, ne torno uno dei due (torna -1 quando in entrambi non c'è maggioritario)
     } else { //Entro nell'else quando sicuramente in almeno un sottovettore c'è maggioritario
        for (int i = 0; i<n; i++){ //Ricerca lineare nel vettore per trovare corrispondenze del maggioritario
            if (vett[i] == msx) Lcont++;
            if (vett[i] == mdx) Rcont++;
        }
        //Controllo che il presunto maggioritario del vettore superi la soglia di m
        if (Lcont>m) return msx;
        if (Rcont>m) return mrx;
        return -1;
    }
     */
}