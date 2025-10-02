#include <stdio.h>
#include <stdlib.h>

int Z,Y;

int F1(float);
void F2(float,int *);

void main(void)
{
    int W;
    float X;
    Z = 5;
    Y = 7;
    W = 2;
    X = (float)Y / Z;
    printf("\nPrograma principal: %d %d %.2f %d",Z,Y,X,W);
    F2(X,&W);
    printf("\nPrograma principal: %d %d %.2f %d",Z,Y,X,W);
}
int F1(float X)
{
    int K;
    if(X != 0)
    {
        K = Z-Y;
        X++;
    }
    else
        K = Z+Y;
    printf("\nF1: %d %d %.2f %d",Z,Y,X,K);
    return(K);
}
void F2(float t,int *r)
{
    int Y;
    Y = 5;
    Z = 0;

    printf("\nF2: %d %d %.2f %d",Z,Y,t,*r);
    if(Z == 0)
    {
        Z =(*r) * 2;
        t =(float)Z/3;
        printf("\nIngresa el valor: ");
        scanf("%d",r);
        printf("\nF2: %d %d %.2f %d",Z,Y,t,*r);
    }
    else
    {
        Z = (*r)*2;
        printf("\nF2: %d %d %.2f %d",Z,Y,t,*r);
    }
    *r = F1(t);
}
