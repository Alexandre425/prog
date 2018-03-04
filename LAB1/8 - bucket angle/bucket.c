#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void){


  double vel = 0.0f;  //variáveis de entrada
  double dist = 0.0f;
  double diam = 0.0f;

  double rad = 0.0f;  //variáveis temporárias e de cálculo
  double grav = 9.8f;
  double dsine = 0.0f;
  double distMin = 0.0f;
  double distMax = 0.0f;
  double distTemp = 0.0f;
  double angMin = 0.0f;
  double angMax = 0.0f;

  double angMin1 = 0.0f;  //variáveis de saída
  double angMax1 = 0.0f;
  double angMin2 = 0.0f;
  double angMax2 = 0.0f;

  printf("\n\n\nThis program calculates the angle at which you need to throw\n");
  printf("a projectile in order for it to land inside a bucket.\n");
  printf("Insert the distance at which the bucket is from you, it's diameter and\n");
  printf("the initial speed, one at a time...\n");

  //leitura da distância e diametro do balde, e velocidade do projétil

  printf("\nDistance (in metres): ");
  scanf("%lf", &dist);
  printf("Bucket diameter (in metres): ");
  scanf("%lf", &diam);
  printf("Initial speed (in metres per second): ");
  scanf("%lf", &vel);

    //verificação da positividade do diametro, velocidade e distância

    if (diam <= 0.0f || vel < 0.0f || dist < 0.0f){

      printf("\nERROR! Values out of bounds! Please note that:\n");
      printf(" - The diameter must be larger than 0! You can't hit a non-existent bucket!\n");
      printf(" - The velocity and distance height must both be positive!\n");

      return EXIT_FAILURE;
    }

  //cálculo das distâncias da zonas mais próximas e distantes do balde

  distMin = dist - (diam / 2.0f);
  distMax = dist + (diam / 2.0f);

  //verificação da posição do balde (está diretamente abaixo do local de lançamento?)

  rad = 0.0f;
  dsine = (double)sin(2*rad);
  distTemp = (vel * vel * dsine) / grav; //cálculo da distância percorrida quando o ângulo é zero

    //condição para a verificação

    if (distTemp >= distMin && distTemp <= distMax){

      printf("The bucket is directly below the projectile! Place it further away, or reduce the diameter!\n");
      return EXIT_FAILURE;
    }

    //Determinação dos ângulos aceitaveis por tentativa e erro
    //Corre o ciclo enquanto o ângulo testado (começando a 0 graus) não ultrapassa 90 graus / pi meios
    //O ângulo é incrementado por 0.00001 radianos a cada ciclo
    //Marca o ângulo mínimo e máximo em que se acerta no balde

    while (rad < M_PI / 2.0f){

      //cálculo da distância percorrida para um determinado ângulo

      rad = rad + 0.00001f;
      dsine = (double)sin(2*rad);
      distTemp = (vel * vel * dsine) / (double)grav;

        //se a distância percorrida se inclui no intervalo do balde e o ângulo mínimo ainda não foi definido:
        //define o ângulo mínimo

        if (distTemp >= distMin && distTemp <= distMax && angMin == 0.0f){
          angMin = rad;
        }

        //se a distância percorrida não se inclui no intervalo do balde, o ângulo máximo NÃO foi definido
        //e o ângulo mínimo FOI definido:
        //define o ângulo máximo

        if ((distTemp >= distMax || distTemp <= distMin) && angMin != 0.0f && angMax == 0.0f){
          angMax = rad;
        }
    }

    //após o ciclo, verifica se foram registados alguns valores
    //caso contrário, a velocidade não é suficiente para atingir o balde
    //NOTA: o diâmetro do balde pode ser tão pequeno, e este estar tão longe que o programa não encontra ângulos válidos

    if (angMin == 0.0f && angMax == 0.0f){
      printf("You can't hit the bucket! Move it closer, or throw harder!\n");
      return EXIT_FAILURE;
    }

  //determinação do primeiro intervalo de ângulos, de radianos para graus

  angMin1 = (angMin * 360.0f) / (2.0f * M_PI);
  angMax1 = (angMax * 360.0f) / (2.0f * M_PI);

  //determinação do segundo intervalo de ângulos, sendo simétrico ao primeiro pelo ângulo 45 graus / pi quartos

  angMin2 = 90 - angMax1;
  angMax2 = 90 - angMin1;

  //print dos resultados, a primeira e segunda gama de ângulos

  printf("\nYour launching angles should be anywhere in between: \n");
  printf("%.1f and %.1f, or %.1f and %.1f degrees\n", angMin1, angMax1, angMin2, angMax2);

  return EXIT_SUCCESS;
}
