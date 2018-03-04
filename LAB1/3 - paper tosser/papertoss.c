#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void){

  double ang = 0.0f;  //veriáveis de entrada
  double vel = 0.0f;
  double ceiling = 0.0f;

  double rad = 0.0f;  //variáveis intermédias para cálculos
  double grav = 9.8f;
  double sine = 0.0f;
  double dsine = 0.0f;

  double dist = 0.0f; //variáveis de saida
  double height = 0.0f;

  printf("\n\n\nThis program calculates the trajectory of a projectile\n");
  printf("Insert the angle of launch, initial speed and the height of the ceiling, one at a time\n");
  printf("The program will return the distance which the projectile will land from you,\n");
  printf("as well as if it hits the ceiling or not\n");

  //leitura das variáveis de entrada (angulo de lançamento, velocidade e altura do teto)

  printf("\nAngle (in degrees): ");
  scanf("%lf", &ang);
  printf("Initial speed (in metres per second): ");
  scanf("%lf", &vel);
  printf("Ceiling height (in metres): ");
  scanf("%lf", &ceiling);

    //verificação dos valores (estão dentro dos limites?)

    if (ang < 0.0f || ang > 90.0f || vel < 0.0f || ceiling < 0.0f){

      printf("\nERROR! Values out of bounds! Please note that:\n");
      printf(" - The angle must be comprehended between 0 and 90 degrees;\n");
      printf(" - The velocity and ceiling height must both be positive.\n");

      return EXIT_FAILURE;
    }

  //cálculo do ângulo em radianos (para cálculos)

  rad = (ang * (double)2 * M_PI) / (double)360;

  //cálculo dos senos de rad e 2 * rad

  dsine = (double)sin(2*rad);
  sine =  (double)sin(rad) * (double)sin(rad);

  //cálculo da distância a que o projétil chega, bem como a altura máxima atingida

  dist = (vel * vel * dsine) / grav;
  height = (vel * vel * sine) / (2 * grav);

  //print dos resultados

  printf("\nLanding distance: %.2fm\n", dist);
  printf("Maximum height: %.2fm\n", height);

    //determinação da colisão (ou não) com o teto)

    if (ceiling > height){
      printf("The projectile won't touch the ceiling!\n");
    }else{
      printf("The projectile will touch the ceiling!\n");
    }

  return EXIT_SUCCESS;
}
