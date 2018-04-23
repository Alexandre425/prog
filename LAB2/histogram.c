#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void vecGenerate(int, int, int[]);

void histogramCount(int, int[], int[]);

void histogramPrint(int*);

int main(void){

  int quant = 0;
  int max = 1;
  int vecCount[9] = {0};

  printf("\nInsert the sample count and the maximum value [1,9]: \n");
  scanf("%d %d", &quant, &max);

  int vec[100000000] = {0};

  vecGenerate(quant, max, vec);

  histogramCount(quant, vec[], &vecCount[]);

  printf("%s\n", vec[]);
  printf("%s", vecCount[]);

  return EXIT_SUCCESS;

}


void vecGenerate(int quant, int max, int* vec[]){

  int pos = 0;

  srand(time(NULL));

    for (pos = 0; pos <= quant; pos++)
      vec[pos] = rand() % max + 1;

}

void histogramCount(int quant, int vec[], int* vecCount[]){

  int vecPos = 0;
  int vecCountPos = 0;

    for (vecPos = 0; vecPos <= quant; vecPos++)
      vecCount[vec[vecPos]]++;

}

void histogramPrint(int* vecCount[])
