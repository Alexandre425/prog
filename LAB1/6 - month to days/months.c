#include <stdio.h>
#include <stdlib.h>

int main( void )
{

   int month = 0; //variável de entrada
   int days = 0;


   printf(" \nPlease insert the number corresponding to a month\nto know how many days it has: ");

   //leitura da varável de entrada

   scanf ("%d", &month);

   //print do número de dias correspondente ao mês inserido

   switch (month) {

    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        days = 31;
            break;

    case 4:
    case 6:
    case 9:
    case 11:
        days = 30;
            break;

    case 2:
        printf("\nThe inserted month has 28 or 29 days");
        return EXIT_SUCCESS;
            break;

    //mensagem de erro, caso o número inserido não corresponda a um mês

    default:
        printf ("\nERROR! Number out of bounds!\n -Make sure the number is between 1 and 12!\n");
        return EXIT_FAILURE;
   }

   printf("The inserted month has %d days", days);

   return EXIT_SUCCESS;

}
