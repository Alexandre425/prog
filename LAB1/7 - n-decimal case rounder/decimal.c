#include<stdio.h>
#include<stdlib.h>

int main(void){

  double num = 0; //número introduzido
  int dec = 0;    //número de casas decimais

  printf("\nThis program rounds an inserted number to your choice of decimal places\n");
  printf("Insert the number first, then the decimal places for it to be rounded to...\n");

  //leitura das variáveis de entrada

  printf("\nNumber: ");
  scanf("%lf", &num);
  printf("Decimal places (between 1 and 7): ");
  scanf("%d", &dec);

    //Escolha do número de casas decimais a apresentar, de acordo com o valor introduzido

    switch (dec) {
      case 1:
        printf("\nThe rounded number with 1 decimal place equates to: %.1f\n", num);
          break;
      case 2:
        printf("\nThe rounded number with 2 decimal place equates to: %.2f\n", num);
          break;
      case 3:
        printf("\nThe rounded number with 3 decimal place equates to: %.3f\n", num);
          break;
      case 4:
        printf("\nThe rounded number with 4 decimal place equates to: %.4f\n", num);
          break;
      case 5:
        printf("\nThe rounded number with 5 decimal place equates to: %.5f\n", num);
          break;
      case 6:
        printf("\nThe rounded number with 6 decimal place equates to: %.6f\n", num);
          break;
      case 7:
        printf("\nThe rounded number with 7 decimal place equates to: %.7f\n", num);
          break;
      default:
        printf("\nERROR! The number of decimal places must be between 1 and 7!\n");
          break;
    }



  return EXIT_SUCCESS;
}
