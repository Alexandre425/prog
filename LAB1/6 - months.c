#include <stdio.h>
#include <stdlib.h>

int main( void )
{
   int month = 0;


   printf(" \n Please insert a month number to know how many days it has: ");
   scanf ("%d", &month) ;


   switch (month) {

    case 1:
        printf("\n January has 31 days."); break;
    case 2:
        printf("\n February has 28 or 29 days."); break;
    case 3:
        printf("\n March has 31 days."); break;
    case 4:
        printf("\n April has 30 days."); break;
    case 5:
        printf("\n May has 31 days."); break;
    case 6:
        printf("\n June has 30 days."); break;
    case 7:
        printf("\n July has 31 days."); break;
    case 8:
        printf("\n August has 31 days."); break;
    case 9:
        printf("\n September has 30 days."); break;
    case 10:
        printf("\n October has 31 days."); break;
    case 11:
        printf("\n November has 30 days."); break;
    case 12:
        printf("\n December has 31 days."); break;

    default:
        printf ("\n Number out of bounds! Shutting down ...");

   };

   return EXIT_SUCCESS;


}
