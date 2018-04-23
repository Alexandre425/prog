#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void vecGenerate(int, float[]);

void histogramCount(int, float, int, float, float[], int[]);

void histogramPrint(float, float, int, int[]);

int main(void){

  //variáveis de entrada
  int quant = 0;
  int intervals = 1;

  //máximo e mínimo dos valores do vetor (a determinar)
  float max = 0.0f;
  float min = 1.0f;

  //tamanho de cada intervalo individual
  float intervalSize = 0.0f;

  //vetor aleatório
  float vec[500] = {0.0f};

  //vetor que armazena o número de ocorrências em cada intervalo
  int vecCount[9] = {0};

  //ponteiro para a posição no vetor
  int vecPos = 0;


  //obtenção das variáveis de entrada
  while (quant > 500 || quant < 1 || intervals < 1 || intervals > 9){
    printf("\nInsert the sample count (max 500) and the number of intervals (from 1 to 9): ");
    scanf("%d %d", &quant, &intervals);
  }

  //geração do vetor aleatório
  vecGenerate(quant, vec);

  //determinação do maior e menor valor do vetor gerado
  for (vecPos = 0; vecPos <= quant; vecPos++) {
    if (vec[vecPos] > max) max = vec[vecPos];
  }

  for (vecPos = 0; vecPos <= quant; vecPos++) {
    if (vec[vecPos] < min) min = vec[vecPos];
  }

  //determinação do tamanho dos intervalos (fórmula do enunciado)
  intervalSize = (max - min) / (float)intervals;

  //determinação do vetor vecCount, que tem o número de ocorrências dos intervalos
  histogramCount(quant, min, intervals, intervalSize, vec, vecCount);

  //print do 'vecCount' num histograma
  histogramPrint(min, intervalSize, intervals, vecCount);

  return EXIT_SUCCESS;

}

//gera um vetor aleatório de dimensão 'quant'
void vecGenerate(int quant, float vec[]){

  int pos = 0;

  srand(time(NULL));

    for (pos = 0; pos < quant; pos++)
      vec[pos] = (float)rand() / (float)(RAND_MAX);

}

//cria o vetor 'vecCount' a partir do vetor 'vec'
void histogramCount(int quant, float min, int intervals, float intervalSize, float vec[], int vecCount[]){

  int vecPos = 0;
  int mult = 1;
  int vecCountPos = 0;

    for (vecPos = 0; vecPos <= quant; vecPos++){    //análise dos valores do vetor 'vec' um a um
      for (mult = 1; mult <= intervals; mult++){    //verificação da inclusão nos intervalos um a um
        if (vec[vecPos] < min + (mult * (float)intervalSize)){
          vecCount[mult - 1]++;   //incremento da posição 'n' no vetor 'vecCount' se for encontrado um número
          mult = 2 * intervals;   //pertencente ao intervalo 'n'

        }
      }
    }
}

//colocação de 'vecCount' numa matriz e print do gráfico
void histogramPrint(float min, float intervalSize, int intervals, int vecCount[]){

  //matriz representativa do gráfico
  int matrix[500][9] = {0};

  int max = 0;

  //ponteiros para as posições na matriz
  int vecPos = 0;
  int linePos = 0;

  //variáveis para o for da impressão
  int i = 0, c = 0;

  //determinação do intervalo com mais instâncias (maior número em 'vecCount')
  for (vecPos = 0; vecPos < 9; vecPos++){
    if (vecCount[vecPos] > max) max = vecCount[vecPos];
  }

  //escrita do gráfico (invertido) na matriz
  for (linePos = 0; linePos <= max; linePos++){       //ciclo pelas linhas da matriz
    for (vecPos = 0; vecPos < intervals; vecPos++){   //ciclo pelas colunas da matriz
      if (vecCount[vecPos] > 0){
        matrix[linePos][vecPos] = 1;                  //colocam-se 1's nos locais onde está o gráfico
        vecCount[vecPos]--;                           //decremento do vetor
      }
    }
  }

  //transformação da matriz para um gráfico (de baixo para cima da matriz)
  for (i = max; i >= 0; i--) {
    printf("   ");
    for (c = 0; c < intervals; c++) {
      if (matrix[i][c] == 1)
        printf("   *    ");
      else
        printf("        ");
    }
    printf("\n");
  }

  //criação da legenda
  for (c = 0; c <= intervals; c++)
    printf("%.3f | ", min + (c * intervalSize));

    printf("\n");

}
