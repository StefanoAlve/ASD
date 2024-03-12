#include <stdio.h>
#include <ctype.h>


void clearBuff();

int main(void)
{
    int num;
    int flag = 0;
    char val;
    printf("\nInserisci il valore: ");
    while(!flag && scanf("%c", &val) == 1)
    {
        clearBuff();
	    if(isdigit(val))
        {
            num = val - '0';
            if(num == 7)
		        flag = 1;

	    }
	    if(!flag)
            printf("\nRiprova:");
    }
}

void clearBuff()
{
    char tmp;
    while(scanf("%c", &tmp) == 1)
        if(tmp == '\n' || tmp == '\0')
            return;
}