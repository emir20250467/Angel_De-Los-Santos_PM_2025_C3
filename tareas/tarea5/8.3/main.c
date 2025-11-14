#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char calle[20];
    int numero;
    int cp;
    char localidad[20];
} domicilio;

struct empleado
{
    char nombre[20];
    char departamento[20];
    float sueldo;
    domicilio direccion;
};

void Lectura(struct empleado *a)
{
    int c;

    printf("\nIngrese el nombre del empleado: ");
    fgets(a->nombre, 20, stdin);
    a->nombre[strcspn(a->nombre, "\n")] = '\0';

    printf("\nIngrese el departamento de la empresa: ");
    fgets(a->departamento, 20, stdin);
    a->departamento[strcspn(a->departamento, "\n")] = '\0';

    printf("\nIngrese el sueldo del empleado: ");
    scanf("%f", &a->sueldo);
    while ((c = getchar()) != '\n' && c != EOF);

    printf("\nIngrese la direccion del empleado");
    printf("\nCalle: ");
    fgets(a->direccion.calle, 20, stdin);
    a->direccion.calle[strcspn(a->direccion.calle, "\n")] = '\0';

    printf("\nNumero: ");
    scanf("%d", &a->direccion.numero);

    printf("\nCodigo Postal: ");
    scanf("%d", &a->direccion.cp);
    while ((c = getchar()) != '\n' && c != EOF);

    printf("\nLocalidad: ");
    fgets(a->direccion.localidad, 20, stdin);
    a->direccion.localidad[strcspn(a->direccion.localidad, "\n")] = '\0';
}

int main(void)
{
    int c;

    struct empleado e0 = {
        "Arturo", "Compras", 15500.75,
        {"San Jeronimo", 120, 3490, "Toluca"}
    };

    struct empleado *e1, *e2, e3, e4;

    e1 = (struct empleado *) malloc(sizeof(struct empleado));

    printf("\nIngrese el nombre del empleado 1: ");
    scanf("%19s", e1->nombre);
    while ((c = getchar()) != '\n' && c != EOF);

    printf("\nIngrese el departamento de la empresa: ");
    fgets(e1->departamento, 20, stdin);
    e1->departamento[strcspn(e1->departamento, "\n")] = '\0';

    printf("\nIngrese el sueldo del empleado 1: ");
    scanf("%f", &e1->sueldo);
    while ((c = getchar()) != '\n' && c != EOF);

    printf("\nIngrese la direccion del empleado 1");
    printf("\nCalle: ");
    fgets(e1->direccion.calle, 20, stdin);
    e1->direccion.calle[strcspn(e1->direccion.calle, "\n")] = '\0';

    printf("\nNumero: ");
    scanf("%d", &e1->direccion.numero);

    printf("\nCodigo Postal: ");
    scanf("%d", &e1->direccion.cp);
    while ((c = getchar()) != '\n' && c != EOF);

    printf("\nLocalidad: ");
    fgets(e1->direccion.localidad, 20, stdin);
    e1->direccion.localidad[strcspn(e1->direccion.localidad, "\n")] = '\0';

    printf("\nIngrese el nombre del empleado 3: ");
    scanf("%19s", e3.nombre);
    while ((c = getchar()) != '\n' && c != EOF);

    printf("\nIngrese el departamento de la empresa: ");
    fgets(e3.departamento, 20, stdin);
    e3.departamento[strcspn(e3.departamento, "\n")] = '\0';

    printf("\nIngrese el sueldo del empleado 3: ");
    scanf("%f", &e3.sueldo);
    while ((c = getchar()) != '\n' && c != EOF);

    printf("\nCalle: ");
    fgets(e3.direccion.calle, 20, stdin);
    e3.direccion.calle[strcspn(e3.direccion.calle, "\n")] = '\0';

    printf("\nNumero: ");
    scanf("%d", &e3.direccion.numero);

    printf("\nCodigo Postal: ");
    scanf("%d", &e3.direccion.cp);
    while ((c = getchar()) != '\n' && c != EOF);

    printf("\nLocalidad: ");
    fgets(e3.direccion.localidad, 20, stdin);
    e3.direccion.localidad[strcspn(e3.direccion.localidad, "\n")] = '\0';

    e2 = (struct empleado *) malloc(sizeof(struct empleado));
    Lectura(e2);

    Lectura(&e4);

    printf("\nDatos del empleado 4\n");
    printf("%s\t%s\t%.2f\t%s\t%d\t%d\t%s\n",
           e4.nombre,
           e4.departamento,
           e4.sueldo,
           e4.direccion.calle,
           e4.direccion.numero,
           e4.direccion.cp,
           e4.direccion.localidad);

    return 0;
}l
