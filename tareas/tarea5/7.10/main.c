#include <stdio.h>
#include <stdlib.h>

void main(void)
{
    char c,cad[10];
    int i = 0;
    float sum = 0.0;
    printf("\ndesea ingresar una cadena de caracteres (s/n)? ");
    c = getchar();
    while (c == 's')
    {
        printf("\ningrese la cadena de caracteres: ");
        fflush(stdin);
        gets(cad);
        i++;
        sum += atof(cad);
        printf("\nDesea ingresar ota cadena de caracter {s/n}? ");
        c = getchar();
    }
    printf("\nSuma : %.2f", sum);
    printf("\npromedio: %.2f",sum / i);
}
