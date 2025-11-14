
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int matricula;
    char nombre[30];
    float cal[5];
} alumno;

void Lectura(alumno *AI, int T);
void F1(alumno *AI, int TAM);
void F2(alumno *AI, int TAM);
void F3(alumno *AI, int TAM);

int main(void)
{
    alumno ARRE[50];
    int TAM;

    do
    {
        printf("\nIngrese el tamano del arreglo: ");
        scanf("%d", &TAM);
    }
    while (TAM > 50 || TAM < 1);

    Lectura(ARRE, TAM);
    F1(ARRE, TAM);
    F2(ARRE, TAM);
    F3(ARRE, TAM);

    return 0;
}

void Lectura(alumno *AI , int T)
{
    int I, J;

    for (I = 0; I < T; I++)
    {
        printf("\nIngrese los datos del alumno %d", I + 1);

        printf("\nIngrese la matricula del alumno: ");
        scanf("%d", &AI[I].matricula);
        fflush(stdin);

        printf("\nIngrese el nombre del alumno: ");
        gets(AI[I].nombre);

        for (J = 0; J < 5; J++)
        {
            printf("\nIngrese la calificacion %d del alumno %d: ", J + 1, I + 1);
            scanf("%f", &AI[I].cal[J]);
        }
    }
}

void F1(alumno *AI, int T)
{
    int I, J;
    float SUM, PRO;

    for (I = 0; I < T; I++)
    {
        printf("\nMatricula del alumno: %d", AI[I].matricula);
        SUM = 0.0;

        for (J = 0; J < 5; J++)
            SUM += AI[I].cal[J];

        PRO = SUM / 5;
        printf("\tPromedio: %.2f", PRO);
    }
}

void F2(alumno *AI, int T)
{
    int I;

    printf("\nAlumnos con calificacion en la tercera materia > 9");

    for (I = 0; I < T; I++)
        if (AI[I].cal[2] > 9)
            printf("\nMatricula del alumno: %d", AI[I].matricula);
}

void F3(alumno *AI, int T)
{
    int I;
    float PRO, SUM = 0.0;

    for (I = 0; I < T; I++)
        SUM += AI[I].cal[3];

    PRO = SUM / T;
    printf("\nPromedio de la materia 4: %.2f", PRO);
}
