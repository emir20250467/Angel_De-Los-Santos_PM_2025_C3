#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void main(void)
{
    float x1,y1,x2,y2,x3,y3,LA1,LA2,LA3,PER;
    printf("Ingrese la coordenada del punto P1:");
    scanf("%f %f", &x1,&y1);
    printf("ingrese las coordenadas del punto P2:");
    scanf("%f %f",&x2,&y2);
    printf("ingrese las coordenadas del punto P3:");
    scanf("%f %f",&x3,&y3);
    LA1 = sqrt(pow(x1-x2,2) + pow(y1-y2,2));
    LA2 = sqrt(pow(x2-x3,2) + pow(y2-y3,2));
    LA3 = sqrt(pow(x1-x3,2) + pow(y1-y3,2));
    PER = LA1 + LA2 + LA3;
    printf("\nEl perimetro del triangulo es: %6.3f",PER);
}
