#include <stdio.h>
#include <stdlib.h>

int Suma(int x,int y)
{
    return(x+y);
}

int Resta(int x,int y)
{
    return(x-y);
}

int Control(int (*apf)(int,int),int x,int y)
{
    int RES;
    RES=(*apf)(x,y);
    return (RES);
}
        void main(void)
        {
            int R1,R2;
            R1 = Control(Suma,15,5);
            R2 = Control(Resta,10,4);
            printf("\nResultado 1: %d",R1);
            printf("\nResultado 2: %d",R2);
        }

