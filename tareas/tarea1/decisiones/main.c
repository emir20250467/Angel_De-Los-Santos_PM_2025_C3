#include <stdio.h>
#include <stdlib.h>
#define VERDADERO 1
#define FLASO 0
#define MAX_EDAD 120
#define MIN_EDAD 0
int main()
{
    //0-2 infante
    //3-12 niño
    //13-17 adolecente
    //18-40 mayor de edad
    //41-65 adulto mayor
    //> 65 envejeciente

    int edad = 0;
    printf("\nIngrese la edad: ");
    scanf("%i", &edad);
    if(edad >= MIN_EDAD  && edad <= MAX_EDAD )
    {
      if(edad <=2)
      {
          printf("\nEs un infante");
      }
      if(edad >= 13 && edad <=17)
      {
        printf("\nEs un adolecente");
      }
      if(edad >= 18 && edad <= 40)
      {
        printf("\nEs mayor de edad");
      }
      if(edad >= 41 && edad <= 64)
      {
         printf("\nEs un adulto mayor");

      }
      if(edad>= 65)
      {
       printf("\nEs un envejeciente");
      }
        if(edad == 16)
        {
            printf("\nUsted gano un apartamento");
        }
        if(edad == 75)
        {
          printf("\nUsted gano una crv");
        }
    }else
    {
        printf("\nEdad fuera de rango!");

        if(edad< MIN_EDAD)
      {
          printf("\nUsted viene del pasado");
      }
      if(edad> MAX_EDAD)
      {
          printf("\nUsted es un vampiro");
      }
    }
    return 0;
}
