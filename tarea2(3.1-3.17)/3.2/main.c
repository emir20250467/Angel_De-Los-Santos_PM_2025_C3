#include <stdio.h>
#include <stdlib.h>

void main(void)
{
    int I,N,NUM,SUM;
    SUM = 0;
    printf("Ingresa el numero de datos:\t");
    scanf("%d",&N);
    for (I=1; I<=N; I++)
    {
        printf("Ingrese el dato numero %d:\t",I);
        scanf("%d", &NUM);
        if (NUM > 0)
            SUM = SUM + NUM;
        {
            printf("\nLa suma de los numeros positivos es: %d",SUM);
        }
    }
}
