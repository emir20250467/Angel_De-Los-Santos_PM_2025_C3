#include <stdio.h>
#include <stdlib.h>


typedef struct
{
    int matricula;
    char nombre[20];
    int carrera;
    float promedio;
} alumno;

void escribe(FILE *);

void main(void)
{
 FILE *ar;
   if ((ar = fopen("ad1.dat", "w")) != NULL)
    escribe(ar);
else
    printf("\nEl archivo no se puede abrir");
fclose(ar);
}

void escribe(FILE *ap)
{
    alumno alu;
    int r, i = 0;
    printf("\nDesea ingresar informacion sobre alumnos? (Si-1 No-0): ");
    scanf("%d", &r);
    while (r)
    {
        i++;
        printf("\nMatricula del alumno %d: ", i);
        scanf("%d", &alu.matricula);
        printf("\nNombre del alumno %d: ", i);
        fflush(stdin);
        gets(alu.nombre);
        printf("\nCarrera del alumno %d: ", i);
        scanf("%d", &alu.carrera);
        printf("\nPromedio del alumno %d: ", i);
        scanf("%f", &alu.promedio);

        fwrite(&alu, sizeof(alumno), 1, ap);

        printf("\nDesea ingresar informacion sobre mas alumnos? (Si-1 No-0): ");
        scanf("%d", &r);
    }
}
