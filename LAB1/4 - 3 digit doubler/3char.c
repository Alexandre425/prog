#include <stdio.h>
#include <stdlib.h>

int main ( void ){

  int num1 = 0; //variáveis correspondentes aos dígitos
  int num2 = 0;
  int num3 = 0;

  int num = 0;  //variável do número final * 2

  printf("Insert 3 positive numbers, one at a time, for them to be assembled into a 3-digit integer, and doubled\n");

  //leitura dos três digitos

  printf("Insert the first digit:  \n");
  scanf("%d", &num1);
  printf("Insert the second digit: \n");
  scanf("%d", &num2);
  printf("Insert the third digit:  \n");
  scanf("%d", &num3);

    //verificação da postitividade dos digitos inseridos

    if(num1 < 0 || num2 < 0 || num3 <0){
      printf("\nERROR! Inserted digits are not positive!\n Shutting down...\n");
      return EXIT_FAILURE;
    }

  //cálculo do valor final

  num = (num1 * 100 + num2 * 10 + num3 * 1) * 2;

  //print do valor final

  printf("The result is %d\n", num);

  return EXIT_SUCCESS;
}
