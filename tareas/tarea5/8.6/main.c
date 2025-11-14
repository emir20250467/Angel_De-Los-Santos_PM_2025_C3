#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int clave;
    char nombre[15];
    float precio;
    int existencia;
} producto;

void Lectura(producto *, int);
void Ventas(producto *, int);
void Reabastecimiento(producto *, int);
void Nuevos_Productos(producto *, int *);
void Inventario(producto *, int);

int main(void)
{
    producto INV[100];
    int TAM, OPE;

    do
    {
        printf("\nIngrese el numero de productos: ");
        scanf("%d", &TAM);
    } while (TAM > 100 || TAM < 1);

    Lectura(INV, TAM);

    printf("\nIngrese operacion a realizar. \n\t1 - Ventas \n\t2 - Reabastecimiento \n\t3 - Nuevos Productos \n\t4 - Inventario \n\t0 - Salir: ");
    scanf("%d", &OPE);

    while (OPE)
    {
        switch (OPE)
        {
        case 1: Ventas(INV, TAM); break;
        case 2: Reabastecimiento(INV, TAM); break;
        case 3: Nuevos_Productos(INV, &TAM); break;
        case 4: Inventario(INV, TAM); break;
        }

        printf("\nIngrese operacion a realizar. \n\t1 - Ventas \n\t2 - Reabastecimiento \n\t3 - Nuevos Productos \n\t4 - Inventario \n\t0 - Salir: ");
        scanf("%d", &OPE);
    }

    return 0;
}

void Lectura(producto A[], int T)
{
    int I;

    for (I = 0; I < T; I++)
    {
        printf("\nIngrese informacion del producto %d", I + 1);
        printf("\nClave: ");
        scanf("%d", &A[I].clave);
        fflush(stdin);

        printf("\tNombre: ");
        gets(A[I].nombre);

        printf("\tPrecio: ");
        scanf("%f", &A[I].precio);

        printf("\tExistencia: ");
        scanf("%d", &A[I].existencia);
    }
}

void Ventas(producto A[], int T)
{
    int CLA, CAN, I, RES;
    float TOT = 0.0, PAR;

    printf("\nIngrese clave del producto -0 para salir-: ");
    scanf("%d", &CLA);

    while (CLA)
    {
        printf("\tCantidad: ");
        scanf("%d", &CAN);

        I = 0;
        while ((I < T) && (A[I].clave < CLA))
            I++;

        if ((I == T) || (A[I].clave > CLA))
        {
            printf("\nLa clave del producto es incorrecta");
        }
        else
        {
            if (A[I].existencia >= CAN)
            {
                A[I].existencia -= CAN;
                PAR = A[I].precio * CAN;
                TOT += PAR;
            }
            else
            {
                printf("\nNo existe en inventario la cantidad solicitada. Solo hay %d", A[I].existencia);
                printf("\nLos lleva 1 - Si 0 - No?: ");
                scanf("%d", &RES);

                if (RES)
                {
                    PAR = A[I].precio * A[I].existencia;
                    TOT += PAR;
                    A[I].existencia = 0;
                }
            }
        }

        printf("\nIngrese la siguiente clave del producto -0 para salir-: ");
        scanf("%d", &CLA);
    }

    printf("\nTotal de la venta: %f", TOT);
}

void Reabastecimiento(producto A[], int T)
{
    int CLA, CAN, I;

    printf("\nIngrese clave del producto -0 para salir-: ");
    scanf("%d", &CLA);

    while (CLA)
    {
        I = 0;
        while ((I < T) && (A[I].clave < CLA))
            I++;

        if ((I == T) || (A[I].clave > CLA))
            printf("\nLa clave del producto ingresada es incorrecta");
        else
        {
            printf("\tCantidad: ");
            scanf("%d", &CAN);
            A[I].existencia += CAN;
        }

        printf("\nIngrese otra clave del producto -0 para salir-: ");
        scanf("%d", &CLA);
    }
}

void Nuevos_Productos(producto A[], int *T)
{
    int CLA, I, J;

    printf("\nIngrese clave del producto -0 para salir-: ");
    scanf("%d", &CLA);

    while (*T < 100 && CLA)
    {
        I = 0;
        while (I < *T && A[I].clave < CLA)
            I++;

        if (I == *T)  // agregar al final
        {
            A[I].clave = CLA;
            fflush(stdin);
            printf("\tNombre: ");
            gets(A[I].nombre);
            printf("\tPrecio: ");
            scanf("%f", &A[I].precio);
            printf("\tCantidad: ");
            scanf("%d", &A[I].existencia);
            (*T)++;
        }
        else if (A[I].clave == CLA) // clave repetida
        {
            printf("\nEl producto ya se encuentra en el inventario");
        }
        else // insertar en medio
        {
            for (J = *T; J > I; J--)
                A[J] = A[J - 1];

            A[I].clave = CLA;
            fflush(stdin);
            printf("\tNombre: ");
            gets(A[I].nombre);
            printf("\tPrecio: ");
            scanf("%f", &A[I].precio);
            printf("\tCantidad: ");
            scanf("%d", &A[I].existencia);
            (*T)++;
        }

        printf("\nIngrese otra clave de producto -0 para salir-: ");
        scanf("%d", &CLA);
    }

    if (*T == 100)
        printf("\nYa no hay espacio para incorporar nuevos productos");
}

void Inventario(producto A[], int T)
{
    int I;
    for (I = 0; I < T; I++)
    {
        printf("\nClave: %d", A[I].clave);
        printf("\nNombre: %s", A[I].nombre);
        printf("\nPrecio: %4.2f", A[I].precio);
        printf("\nExistencia: %d\n", A[I].existencia);
    }
}
