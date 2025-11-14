#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int cuentap(char *);

void main(void)
{
    int i;
    char fra[50];
    printf("\nIngrese la linea de texto: ");
    gets(fra);
    strcat(fra, " ");
    i = cuentap(fra);
    printf("\nLa linea de texto tiene %d palabras", i);
}

int cuentap(char *cad)
{
    char *cad0 = "";
    int i = 0;
    cad0 = strstr(cad, " ");
    while (strcmp(cad0, " "))
    {
        strcpy(cad0, cad0);
        i++;
        cad0 = strstr(cad0 + 1, " ");
    }
    return (i);
}
