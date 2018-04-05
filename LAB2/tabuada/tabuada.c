#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//declaração de funções

int getNumbers(int*, int*);

int main(void){

  //inicialização do gerador de números aleatórios

  srand(time(NULL));

  //declaração de variáveis de entrada, e que vêm da função getNumbers()

  int num1 = 0;
  int num2 = 0;
  int input = 1;
  int result = 0;


  printf("\nWelcome to the multiplication quiz!\n");
  printf("You'll be presented with two numbers, and must write their product.\n");

  //obtenção de dois numeros aleatórios, e o seu produto (retornado por getNumbers())

  result = getNumbers(&num1, &num2);

    while(input != 0){

      printf("\n%d x %d = ", num1, num2);
      scanf("%d", &input);

        if(input == result){
          printf("\nThats correct! Keep at it!\n");

          printf("Insert '0' to exit the program, or any other number to keep going!\n");

            scanf("%d", &input);
            if(input == 0)
              return EXIT_SUCCESS;

          //geração de mais dois numeros aleatórios, caso o resultado esteja correto

          result = getNumbers(&num1, &num2);
        }
        else
          printf("\nWhoops! Thats not it, try again!\n");

          input = 1;

    }

  return EXIT_SUCCESS;
}

//função que gera dois números aleatórios (0-10) e os retorna, bem como o seu produto

int getNumbers(int* num1, int* num2){

  int result = 0;

  *num1 = (rand() % 10);
  *num2 = (rand() % 10);

  result = (*num1) * (*num2);

  return result;
}
