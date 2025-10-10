#include <stdio.h>
#include <stdlib.h>

const int MAX=100;

void Lectura(int*,int);
int Busca(int *,int,int);

void main(void)
{
    int RES,ELE,TAM,VEC[MAX];
    do
    {
        printf("Ingrese el tamano del arreglo: ");
        scanf("%d",&TAM);
    }
    while (TAM>MAX || TAM<1);
    Lectura(VEC,TAM);
    printf("\nIngrese el elemento a buscar: ");
    scanf("%d",&ELE);
    RES = Busca(VEC,TAM,ELE);
    if (RES)
        printf("\nEl elemento se encuentra en la posicion %d",RES);
    else
        printf("\nEL elemento no se encuentra en el arreglo");
}
