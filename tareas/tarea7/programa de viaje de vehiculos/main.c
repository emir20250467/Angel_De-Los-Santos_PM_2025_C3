#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_VEHICULOS 100
#define MAX_COMBUSTBLE 20

typedef struct {
    char marca[30];
    char modelo[30];
    int ano;
    int id;
    char placa[12];
    float consumo_ciudad;        // L por 100 km
    float consumo_carretera;     // L por 100 km
    float costo_seguro_anual;
    float costo_mantenimiento_km;
    int anos_depreciacion;
    float costo_inicial;
    float km_promedio_anual;
    float costo_limpieza;
} Vehiculo;

typedef struct {
    int id;
    char nombre[30];
    float precio_litro;
} Combustible;
void agregarv(Vehiculo arr[], int *n);
void listarv(Vehiculo arr[], int n);
void editarv(Vehiculo arr[], int n);
void agregarc(Combustible arr[], int *n);
void listarc(Combustible arr[], int n);
void editarc(Combustible arr[], int n);
void guardarv(const char *ruta, Vehiculo arr[], int n);
void guardarc(const char *ruta, Combustible arr[], int n);
int cargarv(const char *ruta, Vehiculo arr[], int *n);
int cargarc(const char *ruta, Combustible arr[], int *n);
void limpiar_buffer();
void calcularViaje(Vehiculo vehiculos[], int nVehiculos, Combustible combustibles[], int nCombustibles);

void guardarv(const char *ruta,Vehiculo arr[],int n)
{
    FILE *f = fopen(ruta, "wb");
    if (!f) return;
    fwrite(arr, sizeof(Vehiculo),n,f);
    fclose(f);
}
void guardarc(const char *ruta,Combustible arr[],int n)
{
    FILE *f = fopen(ruta, "wb");
    if (!f) return;
    fwrite(arr, sizeof(Combustible),n,f);
    fclose(f);
}
int cargarv(const char *ruta, Vehiculo arr[],int *n)
{
    FILE *f = fopen(ruta,"rb");
    if(!f)
    {
        *n = 0;
        return 0;
    }
    *n = 0;
    while (fread(&arr[*n],sizeof(Vehiculo),1,f) == 1)
    {
        (*n)++;
    }
    fclose(f);
    return 1;
}
int cargarc(const char *ruta, Combustible arr[],int *n)
{
    FILE *f = fopen(ruta,"rb");
    if(!f)
    {
        *n = 0;
        return 0;
    }
    *n = 0;
    while (fread(&arr[*n],sizeof(Combustible),1,f) == 1)
    {
        (*n)++;
    }
    fclose(f);
    return 1;
}
void editarv(Vehiculo arr[], int n)
{
    int id;
    printf("ID a editar: ");
    scanf("%d", &id);

    for (int i = 0; i < n; i++)
    {
        if (arr[i].id == id)
        {
            printf("Editando vehiculo con ID %d\n", id);

            printf("Marca actual: %s\n", arr[i].marca);
            printf("Nueva marca: ");
            fflush(stdin);
            fgets(arr[i].marca, 30, stdin);
            arr[i].marca[strcspn(arr[i].marca, "\n")] = '\0';

            printf("Modelo actual: %s\n", arr[i].modelo);
            printf("Nuevo modelo: ");
            fflush(stdin);
            fgets(arr[i].modelo, 30, stdin);
            arr[i].modelo[strcspn(arr[i].modelo, "\n")] = '\0';

            printf("Ano actual: %d\n", arr[i].ano);
            printf("Nuevo ano: ");
            scanf("%d", &arr[i].ano);

            printf("Placa actual: %s\n", arr[i].placa);
            printf("Nueva placa: ");
            fflush(stdin);
            fgets(arr[i].placa, 12, stdin);
            arr[i].placa[strcspn(arr[i].placa, "\n")] = '\0';

            printf("Consumo ciudad actual (L/100km): %.2f\n", arr[i].consumo_ciudad);
            printf("Nuevo consumo ciudad: ");
            scanf("%f", &arr[i].consumo_ciudad);

            printf("Consumo carretera actual (L/100km): %.2f\n", arr[i].consumo_carretera);
            printf("Nuevo consumo carretera: ");
            scanf("%f", &arr[i].consumo_carretera);

            printf("Costo seguro anual actual: %.2f\n", arr[i].costo_seguro_anual);
            printf("Nuevo costo seguro anual: ");
            scanf("%f", &arr[i].costo_seguro_anual);

            printf("Costo mantenimiento por km actual: %.2f\n", arr[i].costo_mantenimiento_km);
            printf("Nuevo costo mantenimiento por km: ");
            scanf("%f", &arr[i].costo_mantenimiento_km);

            printf("Anos de depreciacion actual: %d\n", arr[i].anos_depreciacion);
            printf("Nuevos anos de depreciacion: ");
            scanf("%d", &arr[i].anos_depreciacion);

            printf("Costo inicial actual: %.2f\n", arr[i].costo_inicial);
            printf("Nuevo costo inicial: ");
            scanf("%f", &arr[i].costo_inicial);

            printf("Km promedio anual actual: %.2f\n", arr[i].km_promedio_anual);
            printf("Nuevo km promedio anual: ");
            scanf("%f", &arr[i].km_promedio_anual);

            printf("Costo limpieza actual: %.2f\n", arr[i].costo_limpieza);
            printf("Nuevo costo limpieza: ");
            scanf("%f", &arr[i].costo_limpieza);

            printf("Datos actualizados.\n");
            return;
        }
    }

    printf("No existe un vehiculo con ese ID.\n");
}
void calcularViaje(Vehiculo vehiculos[], int nVehiculos, Combustible combustibles[], int nCombustibles)
{
    if (nVehiculos == 0 || nCombustibles == 0)
    {
        printf("No hay vehiculos o combustibles registrados.\n");
        return;
    }

    int idVehiculo, idCombustible;
    float kmTotal, porcentajeCiudad;
    Vehiculo *v = NULL;
    Combustible *c = NULL;

    listarv(vehiculos, nVehiculos);
    printf("\nIngrese el ID del vehiculo a usar: ");
    scanf("%d", &idVehiculo);
    limpiar_buffer();

    for (int i = 0; i < nVehiculos; i++)
    {
        if (vehiculos[i].id == idVehiculo)
        {
            v = &vehiculos[i];
            break;
        }
    }

    if (v == NULL)
    {
        printf("Vehiculo no encontrado.\n");
        return;
    }

    listarc(combustibles, nCombustibles);
    printf("\nIngrese el ID del combustible a usar: ");
    scanf("%d", &idCombustible);
    limpiar_buffer();

    for (int i = 0; i < nCombustibles; i++)
    {
        if (combustibles[i].id == idCombustible)
        {
            c = &combustibles[i];
            break;
        }
    }

    if (c == NULL)
    {
        printf("Combustible no encontrado.\n");
        return;
    }

    printf("Ingrese la cantidad total de km del viaje: ");
    scanf("%f", &kmTotal);
    limpiar_buffer();

    printf("Ingrese el porcentaje de km en ciudad (0-100): ");
    scanf("%f", &porcentajeCiudad);
    limpiar_buffer();

    float kmCiudad = kmTotal * (porcentajeCiudad / 100.0);
    float kmCarretera = kmTotal - kmCiudad;

    float litrosCiudad = kmCiudad * (v->consumo_ciudad / 100.0);
    float litrosCarretera = kmCarretera * (v->consumo_carretera / 100.0);
    float litrosTotales = litrosCiudad + litrosCarretera;
    float costoCombustible = litrosTotales * c->precio_litro;

    float costoDepreciacion = (v->costo_inicial / v->anos_depreciacion / v->km_promedio_anual) * kmTotal;
    float costoMantenimiento = v->costo_mantenimiento_km * kmTotal;
    float costoSeguro = (v->costo_seguro_anual / v->km_promedio_anual) * kmTotal;
    float costoLimpieza = v->costo_limpieza; // opcional, puede ser fijo

    float costoTotal = costoCombustible + costoDepreciacion + costoMantenimiento + costoSeguro + costoLimpieza;
    float costoPorKm = costoTotal / kmTotal;

    printf("\n--- RESULTADO DEL VIAJE ---\n");
    printf("Vehiculo: %s %s (ID %d)\n", v->marca, v->modelo, v->id);
    printf("Combustible: %s (ID %d)\n", c->nombre, c->id);
    printf("Km totales: %.2f KM (Ciudad: %.2f, Carretera: %.2f)\n", kmTotal, kmCiudad, kmCarretera);
    printf("Litros totales consumidos: %.2f\n", litrosTotales);
    printf("Costo combustible: %.2f\n", costoCombustible);
    printf("Costo depreciacion: %.2f RD$\n", costoDepreciacion);
    printf("Costo mantenimiento: %.2f RD$\n", costoMantenimiento);
    printf("Costo seguro: %.2f RD$\n", costoSeguro);
    printf("Costo limpieza: %.2f RD$\n", costoLimpieza);
    printf("COSTO TOTAL DEL VIAJE: %.2f RD$\n", costoTotal);
    printf("COSTO POR KM: %.2f RD$\n", costoPorKm);
}
void agregarv(Vehiculo arr[], int *n)
{
    if (*n >= MAX_VEHICULOS)
    {
        printf("No se pueden agregar mas vehiculos.\n");
        return;
    }

    Vehiculo v;

    printf("ID: ");
    scanf("%d", &v.id);
    limpiar_buffer();


    printf("Marca: ");
    fgets(v.marca, 30, stdin);
    v.marca[strcspn(v.marca, "\n")] = '\0';

    printf("Modelo: ");
    fgets(v.modelo, 30, stdin);
    v.modelo[strcspn(v.modelo, "\n")] = '\0';

    printf("Ano: ");
    scanf("%d", &v.ano);
    limpiar_buffer();

    printf("Placa: ");
    fgets(v.placa, 12, stdin);
    v.placa[strcspn(v.placa, "\n")] = '\0';

    printf("Consumo ciudad L/100Km: ");
    scanf("%f", &v.consumo_ciudad);
     limpiar_buffer();
    printf("Consumo carretera L/100Km: ");
    scanf("%f", &v.consumo_carretera);
limpiar_buffer();
    printf("Costo seguro anual: ");
    scanf("%f", &v.costo_seguro_anual);
limpiar_buffer();
    printf("Costo mantenimiento por km: ");
    scanf("%f", &v.costo_mantenimiento_km);
limpiar_buffer();
    printf("Anos de depreciacion: ");
    scanf("%d", &v.anos_depreciacion);
limpiar_buffer();
    printf("Costo inicial: ");
    scanf("%f", &v.costo_inicial);
limpiar_buffer();
    printf("Km promedio anual: ");
    scanf("%f", &v.km_promedio_anual);
limpiar_buffer();
    printf("Costo limpieza: ");
    scanf("%f", &v.costo_limpieza);
limpiar_buffer();
    arr[*n] = v;
    (*n)++;

    printf("Vehiculo agregado.\n");
}
void listarv(Vehiculo arr[], int n)
{
    if (n == 0)
    {
        printf("No hay vehiculos registrados.\n");
        return;
    }

    printf("\nLISTA DE VEHICULOS\n");

    for (int i = 0; i < n; i++)
    {
        printf("\nID: %d\n", arr[i].id);
        printf("Marca: %s\n", arr[i].marca);
        printf("Modelo: %s\n", arr[i].modelo);
        printf("Ano: %d\n", arr[i].ano);
        printf("Placa: %s\n", arr[i].placa);
        printf("Consumo ciudad: %.2f\n", arr[i].consumo_ciudad);
        printf("Consumo carretera: %.2f\n", arr[i].consumo_carretera);
        printf("Costo seguro anual: %.2f\n", arr[i].costo_seguro_anual);
        printf("Costo mantenimiento por km: %.2f\n", arr[i].costo_mantenimiento_km);
        printf("Anos depreciacion: %d\n", arr[i].anos_depreciacion);
        printf("Costo inicial: %.2f\n", arr[i].costo_inicial);
        printf("Km promedio anual: %.2f\n", arr[i].km_promedio_anual);
        printf("Costo limpieza: %.2f\n", arr[i].costo_limpieza);
    }
}
void agregarc(Combustible arr[], int *n)
{
    if (*n >= MAX_COMBUSTBLE)
    {
        printf("No se pueden agregar mas combustibles.\n");
        return;
    }

    Combustible c;

    printf("ID combustible: ");
    scanf("%d", &c.id);

   limpiar_buffer();
    printf("Nombre: ");
    fgets(c.nombre, 30, stdin);
    c.nombre[strcspn(c.nombre, "\n")] = '\0';

    printf("Precio por litro: ");
    scanf("%f", &c.precio_litro);
limpiar_buffer();
    arr[*n] = c;
    (*n)++;

    printf("Combustible agregado.\n");
}
void listarc(Combustible arr[], int n)
{
    if (n == 0)
    {
        printf("No hay combustibles registrados.\n");
        return;
    }

    printf("\nLISTA DE COMBUSTIBLES\n");

    for (int i = 0; i < n; i++)
    {
        printf("\nID: %d\n", arr[i].id);
        printf("Nombre: %s\n", arr[i].nombre);
        printf("Precio por litro: %.2f\n", arr[i].precio_litro);
    }
}
void editarc(Combustible arr[], int n)
{
    int id;
    printf("ID del combustible a editar: ");
    scanf("%d", &id);
limpiar_buffer();
    for (int i = 0; i < n; i++)
    {
        if (arr[i].id == id)
        {
            printf("Editando combustible con ID %d\n", id);


            printf("Nombre actual: %s\n", arr[i].nombre);
            printf("Nuevo nombre: ");
            limpiar_buffer();
            fgets(arr[i].nombre, 30, stdin);
            arr[i].nombre[strcspn(arr[i].nombre, "\n")] = '\0';


            printf("Precio por litro actual: %.2f\n", arr[i].precio_litro);
            printf("Nuevo precio por litro: ");
            scanf("%f", &arr[i].precio_litro);
limpiar_buffer();
            printf("Datos del combustible actualizados.\n");
            return;
        }
    }

    printf("No existe un combustible con ese ID.\n");
}
void limpiar_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}
int main()
{
    Vehiculo vehiculos[MAX_VEHICULOS];
    Combustible combustibles[MAX_COMBUSTBLE];
    int nVehiculos = 0,nCombustibles = 0;
    int opcion;

    cargarv("vehiculos.dat",vehiculos,&nVehiculos);
    cargarc("combustibles.dat",combustibles,&nCombustibles);

    do
    {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1. Agregar vehiculo\n");
        printf("2. Listar vehiculos\n");
        printf("3. Editar vehiculo\n");
        printf("4. Agregar combustible\n");
        printf("5. Listar combustibles\n");
        printf("6. Editar combustible\n");
        printf("7. Calcular viaje\n");
        printf("0. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);
        limpiar_buffer();

        switch(opcion)
        {
            case 1:
                agregarv(vehiculos, &nVehiculos);
                guardarv("vehiculos.dat", vehiculos, nVehiculos);
                break;

            case 2:
                listarv(vehiculos, nVehiculos);
                break;

            case 3:
                editarv(vehiculos, nVehiculos);
                guardarv("vehiculos.dat", vehiculos, nVehiculos);
                break;

            case 4:
                agregarc(combustibles, &nCombustibles);
                guardarc("combustibles.dat", combustibles, nCombustibles);
                break;

            case 5:
                listarc(combustibles, nCombustibles);
                break;

            case 6:
                editarc(combustibles, nCombustibles);
                guardarc("combustibles.dat", combustibles, nCombustibles);
                break;

            case 7:
                calcularViaje(vehiculos,nVehiculos,combustibles,nCombustibles);
                break;

            case 0:
                printf("Saliendo del programa...\n");
                break;

            default:
                printf("Opcion invalida. Intenta de nuevo.\n");
        }
    }
    while(opcion != 0);
    return 0;

}
