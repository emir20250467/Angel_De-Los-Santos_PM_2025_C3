#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char mat[20];
    int pro;
} matpro;

typedef struct
{
    int matri;
    char nom[20];
    matpro cal[5];
} alumno;

void Lectura(alumno *, int);
void F1(alumno *, int);
void F2(alumno *, int);
void F3(alumno *, int);

int main(void)
{
    alumno ALU[50];
    int TAM;

    do
    {
        printf("Ingrese el tamano del arreglo: ");
        scanf("%d", &TAM);
    }
    while (TAM > 50 || TAM < 1);

    Lectura(ALU, TAM);
    F1(ALU, TAM);
    F2(ALU, TAM);
    F3(ALU, TAM);

    return 0;
}

void Lectura(alumno A[], int T)
{
    int I, J;

    for (I = 0; I < T; I++)
    {
        printf("\nIngrese los datos del alumno %d", I + 1);

        printf("\nIngrese la matricula del alumno: ");
        scanf("%d", &A[I].matri);
        fflush(stdin);

        printf("Ingrese el nombre del alumno: ");
        gets(A[I].nom);

        for (J = 0; J < 5; J++)
        {
            printf("Materia %d: ", J + 1);
            fflush(stdin);
            gets(A[I].cal[J].mat);

            printf("Promedio %d: ", J + 1);
            scanf("%d", &A[I].cal[J].pro);
        }
    }
}

void F1(alumno AL[], int T)
{
    int I, J;
    float SUM;

    for (I = 0; I < T; I++)
    {
        printf("\nMatricula del alumno: %d", AL[I].matri);

        SUM = 0.0;
        for (J = 0; J < 5; J++)
            SUM += AL[I].cal[J].pro;

        SUM /= 5;
        printf("\nPromedio: %.2f", SUM);
    }
}

void F2(alumno AL[], int T)
{
    int I;

    printf("\n\nAlumnos con calificacion mayor a 9 en la tercera materia:");

    for (I = 0; I < T; I++)
        if (AL[I].cal[2].pro > 9)
            printf("\nMatricula del alumno: %d", AL[I].matri);
}

void F3(alumno AL[], int T)
{
    int I;
    float SUM = 0.0;

    for (I = 0; I < T; I++)
        SUM += AL[I].cal[3].pro;

    SUM /= T;

    printf("\n\nPromedio de la cuarta materia: %.2f", SUM);
}

