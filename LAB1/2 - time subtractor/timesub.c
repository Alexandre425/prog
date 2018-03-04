#include <stdio.h>
#include <stdlib.h>

int main(void){


  int hour1 = 0;  //variáveis do primeiro tempo
  int min1 = 0;
  int sec1 = 0;
  int secTotal1 = 0;

  int hour2 = 0;  //variáveis do segundo tempo
  int min2 = 0;
  int sec2 = 0;
  int secTotal2 = 0;

  int hourOut = 0;  //variáveis de saida (resultado a apresentar)
  int minOut = 0;
  int secOut = 0;
  int secTotalTemp = 0; //variável que armazena temporariamente secTotal1 - secTotal2

  int secTotal3 = 0; //variável para a troca de tempo (caso o segundo seja o maior)



  printf("\n\n\nThis program subtracts two given times.\n");
  printf("Please insert the longest time first, followed by the shortest.\n");
  printf("Insert the longest time, one unit at a time...\n\n");

  printf("Hours: ");  //leitura das horas, minutos e segundos do primeiro tempo
  scanf("%d", &hour1);
  printf("Minutes: ");
  scanf("%d", &min1);
  printf("Seconds: ");
  scanf("%d", &sec1);

    //verificação do primeiro valor (garante que este não está "out of bounds")

    if (hour1 >= 24 || hour1 < 0|| min1 >= 60 || min1 < 0|| sec1 >= 60 || sec1 < 0){
      printf("ERROR! Minutes or seconds given are out of bounds!\nShutting down...\n");
      return EXIT_FAILURE;
    }

  printf("\nLongest time inserted!\n");
  printf("Insert the shortest time, one unit at a time...\n\n");

  printf("Hours: ");  //leitura das horas, minutos e segundos do segundo tempo
  scanf("%d", &hour2);
  printf("Minutes: ");
  scanf("%d", &min2);
  printf("Seconds: ");
  scanf("%d", &sec2);

    //verificação do segundo valor (garante que este não está "out of bounds")

    if (hour2 >= 24 || hour2 < 0|| min2 >= 60 || min2 < 0|| sec2 >= 60 || sec2 < 0){
      printf("ERROR! Minutes or seconds given are out of bounds!\nShutting down...\n");
      return EXIT_FAILURE;
    }

  secTotal1 = hour1*3600 + min1*60 + sec1;  //cálculo do tempo em segundos, para ambos os tempos
  secTotal2 = hour2*3600 + min2*60 + sec2;

    //verifica se o segundo tempo é maior que o primeiro. Caso seja, informe o utilizador e troca os valores

    if (secTotal2 > secTotal1){
      printf("\nWarning! Second time longer than the first! Switching values...\n");
      secTotal3 = secTotal1;
      secTotal1 = secTotal2;
      secTotal2 = secTotal3;
    }

  secTotalTemp = secTotal1 - secTotal2; //calcula a diferença entre os tempos fornecidos, em segundos

  //Conversão de segundos para tempo em H, m e s
  //Processo igual ao utilizado no código de "time.c"
  //Consultar os comentários do ficheiro referido

  minOut = secTotalTemp / 60;
  hourOut = minOut / 60;
  minOut = minOut - hourOut * 60;
  secOut = secTotalTemp - hourOut * 3600 - minOut * 60;

  //Print do resultado final no formato calculado anteriormente

  printf("\nThe difference between the two times equates to:\n%dH%dm%ds\n", hourOut, minOut, secOut);

  return EXIT_SUCCESS;
}
