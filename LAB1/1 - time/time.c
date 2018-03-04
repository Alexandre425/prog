#include <stdio.h>
#include <stdlib.h>

int main(void){

  int secIn = 0;  //segundos IN
  int min = 0;    //minutos OUT
  int hour = 0;   //horas OUT
  int sec = 0;    //segundos OUT

  printf("\nInsert the time in seconds to be converted: ");
  scanf("%d", &secIn);

  min = secIn / 60; //1 min = 60 seg
  hour = min / 60;  //1 hora = 60 min
  min -= hour*60;   //subtrair as horas à variavel min (para quando secIN >= 3600)
  sec = secIn - hour*3600 - min*60; //mesma operação, mas para os segundos

  printf("\n%d seconds correspond to %dh%dm%ds\n", secIn, hour, min, sec);

  return EXIT_SUCCESS;
}
