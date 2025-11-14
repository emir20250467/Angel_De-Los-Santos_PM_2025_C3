#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void main(void)
{
    char cad[50];
    int i = 0, mi= 0, ma = 0;
    printf("\ningrese la cadena de caracteres (maximo 50 caracteres): ");
    gets(cad);\
    while(cad[i] != '0')
    {
        if (islower(cad[i]))
            mi++;
            else
            if (isupper(cad[i]))
            ma++;
        i++;
    }
    printf("\nnumero de letras minusculas: %d",mi);
    printf("\nnumero de letras mayusculas: %d",ma);
}

