#include <stdlib.h>
#include <stdio.h>

//declaração de funções

int combination(int, int);

int factorial(int);

int main(void){

//variáveis de posição (no triângulo) e de entrada

  int currentLine = 0;
  int currentSpace = 0;
  int currentNum = 0;
  int lines = 0;

  printf("\nThis program prints a Pascal triangle of N-lines\n");
  printf("Insert the number of lines the triangle will have: ");

  //scan do numero de linhas do triângulo

  scanf("%d", &lines);

  //criação do triângulo

  for (currentLine = 0; currentLine < lines; currentLine++){

    for (currentSpace = 0; currentSpace < (lines - currentLine); currentSpace++)
      printf("  ");

    for (currentNum = 0; currentNum < currentLine + 1; currentNum++)
      printf("%d   ", combination(currentLine, currentNum));

    printf("\n");

  }

  return EXIT_SUCCESS;
}

//função que calcula as combinações (de num a line)

int combination(int line, int num){

  //declaração de variáveis de cálculo

  int factLine = 1;
  int factNum = 1;
  int factLineNum = 1;
  int lineNum = (line - num);

  //chamada da função de fatorial. cálculo dos fatoriais necessários ao cálculo

  factLine = factorial(line);
  factNum = factorial(num);
  factLineNum = factorial(lineNum);

  //fórmula das combinações

  return factLine / (factNum * factLineNum);

}

//função que calcula o fatorial de 'num'

int factorial(int num){

  int mult = 1;
  int result = 0;

  if (num == 0)
    num = 1;

  result = num;

  //cálculo do fatorial (resultado = 'num' * 1 * 2 * ... * num - 1)

  for (mult = 1; mult < num; mult++)
    result = result * mult;

  return result;

}
