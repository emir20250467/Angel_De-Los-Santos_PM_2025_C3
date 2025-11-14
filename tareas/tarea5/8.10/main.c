#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char noba[10];
    char nucu[10];
} banco;

typedef union {
    banco che;
    banco nomi;
} fpago;

typedef struct {
    char cnu[20];
    char col[20];
    char cp[5];
    char ciu[15];
} domicilio;

typedef struct {
    int num;
    char nom[20];
    float ven[12];
    domicilio domi;
    float sal;
    fpago pago;
    int cla;
} vendedor;

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void Lectura(vendedor *, int);
void F1(vendedor *, int);
void F2(vendedor *, int);
void F3(vendedor *, int);
void F4(vendedor *, int);

int main(void)
{
    vendedor VENDEDORES[100];
    int TAM;

    do {
        printf("Ingrese el numero de vendedores: ");
        scanf("%d", &TAM);
        limpiarBuffer();
    } while (TAM < 1 || TAM > 100);

    Lectura(VENDEDORES, TAM);
    F1(VENDEDORES, TAM);
    F2(VENDEDORES, TAM);
    F3(VENDEDORES, TAM);
    F4(VENDEDORES, TAM);

    printf("\nFIN DEL PROGRAMA\n");
    return 0;
}

void Lectura(vendedor A[], int T)
{
    int I, J;

    for (I = 0; I < T; I++)
    {
        printf("\nIngrese datos del vendedor %d", I + 1);

        printf("\nNumero de vendedor: ");
        scanf("%d", &A[I].num);
        limpiarBuffer();

        printf("Nombre del vendedor: ");
        fgets(A[I].nom, sizeof(A[I].nom), stdin);
        A[I].nom[strcspn(A[I].nom, "\n")] = 0;

        for (J = 0; J < 12; J++) {
            printf("\nMes %d: ", J + 1);
            scanf("%f", &A[I].ven[J]);
        }
        limpiarBuffer();

        printf("\nCalle y numero: ");
        fgets(A[I].domi.cnu, sizeof(A[I].domi.cnu), stdin);
        A[I].domi.cnu[strcspn(A[I].domi.cnu, "\n")] = 0;

        printf("Colonia: ");
        fgets(A[I].domi.col, sizeof(A[I].domi.col), stdin);
        A[I].domi.col[strcspn(A[I].domi.col, "\n")] = 0;

        printf("Codigo Postal: ");
        fgets(A[I].domi.cp, sizeof(A[I].domi.cp), stdin);
        A[I].domi.cp[strcspn(A[I].domi.cp, "\n")] = 0;

        printf("Ciudad: ");
        fgets(A[I].domi.ciu, sizeof(A[I].domi.ciu), stdin);
        A[I].domi.ciu[strcspn(A[I].domi.ciu, "\n")] = 0;

        printf("\nSalario del vendedor: ");
        scanf("%f", &A[I].sal);
        limpiarBuffer();

        printf("\nForma de Pago (Banco-1 / Nomina-2 / Ventanilla-3): ");
        scanf("%d", &A[I].cla);
        limpiarBuffer();

        switch (A[I].cla)
        {
            case 1:
                printf("\nNombre del banco: ");
                fgets(A[I].pago.che.noba, sizeof(A[I].pago.che.noba), stdin);
                A[I].pago.che.noba[strcspn(A[I].pago.che.noba, "\n")] = 0;

                printf("Numero de cuenta: ");
                fgets(A[I].pago.che.nucu, sizeof(A[I].pago.che.nucu), stdin);
                A[I].pago.che.nucu[strcspn(A[I].pago.che.nucu, "\n")] = 0;
                break;

            case 2:
                printf("\nNombre del banco: ");
                fgets(A[I].pago.nomi.noba, sizeof(A[I].pago.nomi.noba), stdin);
                A[I].pago.nomi.noba[strcspn(A[I].pago.nomi.noba, "\n")] = 0;

                printf("Numero de cuenta: ");
                fgets(A[I].pago.nomi.nucu, sizeof(A[I].pago.nomi.nucu), stdin);
                A[I].pago.nomi.nucu[strcspn(A[I].pago.nomi.nucu, "\n")] = 0;
                break;

            case 3:
                break;
        }
    }
}

void F1(vendedor A[], int T)
{
    int I, J;
    float SUM;

    printf("\nVentas Totales de los Vendedores:");

    for (I = 0; I < T; I++)
    {
        SUM = 0.0;
        for (J = 0; J < 12; J++)
            SUM += A[I].ven[J];

        printf("\nVendedor %d  - Ventas: %.2f", A[I].num, SUM);
    }
}

void F2(vendedor A[], int T)
{
    int I, J;
    float SUM;

    printf("\n\nIncremento a los Vendedores con Ventas > 1500000");

    for (I = 0; I < T; I++)
    {
        SUM = 0;
        for (J = 0; J < 12; J++)
            SUM += A[I].ven[J];

        if (SUM > 1500000.0)
        {
            A[I].sal *= 1.05;
            printf("\nEmpleado: %d  Ventas: %.2f  Nuevo salario: %.2f",
                   A[I].num, SUM, A[I].sal);
        }
    }
}

void F3(vendedor A[], int T)
{
    int I, J;
    float SUM;

    printf("\n\nVendedores con Ventas < 300000:");

    for (I = 0; I < T; I++)
    {
        SUM = 0;
        for (J = 0; J < 12; J++)
            SUM += A[I].ven[J];

        if (SUM < 300000)
            printf("\nEmpleado: %d  Nombre: %s  Ventas: %.2f",
                   A[I].num, A[I].nom, SUM);
    }
}

void F4(vendedor A[], int T)
{
    int I;

    printf("\n\nVendedores con Cuenta en el Banco:");

    for (I = 0; I < T; I++)
        if (A[I].cla == 1)
            printf("\nVendedor %d  Banco: %s  Cuenta: %s",
                   A[I].num, A[I].pago.che.noba, A[I].pago.che.nucu);
}



