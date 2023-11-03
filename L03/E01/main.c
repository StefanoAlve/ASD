#include <stdio.h>
#include <stdlib.h>

int majority(int *vett, int len_vett);

int main() {
    int *vett, len_vett, num, maj;

    printf("Inserire la grandezza del vettore: ");
    scanf("%d", &len_vett); printf("\n");

    if (len_vett == 0){
        printf("Non esiste maggioritario in un vettore vuoto\n");
        exit(1);
    }
    vett = (int *)malloc(len_vett* sizeof(int));

    for (int i = 0; i<len_vett; i++){
        printf("Inserire il %d numero del vettore: ",i+1);
        scanf("%d",&num);
        printf("\n");
        vett[i] = num;
    }

    printf("\n");
    maj = majority(vett,len_vett);
    if (maj != -1) printf("Il maggioritario del vettore e' %d\n", maj);
    else printf("Il vettore non ha maggioritario\n");

    free(vett);
    return 0;
}

int majority(int *vett, int len_vett){
    int L_maj, R_maj, Lcont = 0, Rcont = 0, m = len_vett/2;
    if (len_vett==1){
        return vett[0];
    }

    L_maj = majority(vett,m);
    R_maj = majority(vett+m,len_vett-m);

    if (L_maj==R_maj){
        return R_maj;
    } else {
        for (int i = 0; i<len_vett; i++){
            if (vett[i] == L_maj) Lcont++;
            if (vett[i] == R_maj) Rcont++;
        }
        if (Lcont>m) return L_maj;
        if (Rcont>m) return R_maj;
        return -1;
    }


}