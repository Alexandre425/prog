#include <stdio.h>
#include <stdlib.h>

int main( void )
{

   int month = 0; //variável de entrada

   printf(" \nPlease insert the number corresponding to a month to know how many days it has: ");

   //leitura da varável de entrada

   scanf ("%d", &month);

   //print do número de dias correspondente ao mês inserido

   switch (month) {

    case 1:
        printf("\nJanuary has 31 days.\n");
          break;
    case 2:
        printf("\nFebruary has 28 or 29 days.\n");
          break;
    case 3:
        printf("\nMarch has 31 days.\n");
          break;
    case 4:
        printf("\nApril has 30 days.\n");
          break;
    case 5:
        printf("\nMay has 31 days.\n");
          break;
    case 6:
        printf("\nJune has 30 days.\n");
          break;
    case 7:
        printf("\nJuly has 31 days.\n");
          break;
    case 8:
        printf("\nAugust has 31 days.\n");
          break;
    case 9:
        printf("\nSeptember has 30 days.\n");
          break;
    case 10:
        printf("\nOctober has 31 days.\n");
          break;
    case 11:
        printf("\nNovember has 30 days.\n");
          break;
    case 12:
        printf("\nDecember has 31 days.\n");
          break;

    //mensagem de erro, caso o número inserido não corresponda a um mês

    default:
        printf ("\nERROR! Number out of bounds!\n -Make sure the number is between 1 and 12!\n");

   }

   return EXIT_SUCCESS;

}
