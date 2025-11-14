#include <stdio.h>
#include <stdlib.h>

void sumypro(FILE *);

void main(void) {
    FILE *ap;
    if ((ap = fopen("arc2.txt", "r")) != NULL) {
        sumypro(ap);
        fclose(ap);
    } else
        printf("No se puede abrir el archivo");
}

void sumypro(FILE *ap1) {
    char cad[30];
    int i;
    float sum = 0.0, r;
    while (!feof(ap1)) {
        gets(cad);
        r = atof(cad);
        if (r != 0) {
            i++;
            sum += r;
        }
    }
    printf("\nSuma: %.2f", sum);
    if (i)
        printf("\nPromedio: %.2f", sum / i);
}
