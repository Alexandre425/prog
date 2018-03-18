#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000

int numRead(int[]);

int numEncrypt(int, int[], int[]);

void numDecrypt(int, int[], int[]);

int main (void){

        //tamanho dos vetores
        int numDecSize = 0;
        int numEncSize = 0;

        //vetores com o número e a sua versão encriptada
        int decVec[SIZE] = {0};
        int encVec[SIZE] = {0};

        //contagem para a impressão do vetor
        int i = 0;



  //leitura do número a encriptar
  numDecSize = numRead(decVec);

  //encriptação do número
  numEncSize = numEncrypt(numDecSize, decVec, encVec);

  //print do número encriptado
  printf("\nEncrypted number: ");
  for (i = 0; i < numEncSize; i++)
  printf("%d", encVec[i]);

  //desencriptação do número
  numDecrypt(numEncSize, encVec, decVec);

  //print do número desencriptado
  printf("\nDecrypted number: ");
  for (i = 0; i < numDecSize; i++)
  printf("%d", decVec[i]);

  printf("\n\n");

  return EXIT_SUCCESS;
}

//leitura e colocação num vetor do número
int numRead(int decVec[]){

  int numDecSize = 0;
  int decNum = 0;
  int decNumTest = 0;
  int digitCount = 0;

  int i = 0;

  do {
    digitCount = 0;

    //leitura das variáveis de entrada
    printf("\nInsert the number of digits of your number: ");
    scanf("%d", &numDecSize);
    printf("Insert the number itself (make sure it has the correct ammout of digits!): ");
    scanf("%d", &decNum);

    //contagem dos algarismos de 'decNum'
    decNumTest = decNum;

    while (decNumTest != 0){
      decNumTest /= 10;
      digitCount++;
    }

    //erro se for diferente de 'numDecSize'
    if (numDecSize != digitCount || numDecSize < 1)
      printf("\nERROR! Numbers out of bounds!");

  } while (numDecSize != digitCount || numDecSize < 1);

  //associação de 'decNum' ao vetor 'decVec[]'
  for (i = numDecSize - 1; i >= 0; i--){
    decVec[i] = decNum % 10;
    decNum /= 10;
  }

  //retorno do tamanho do vetor
  return numDecSize;
}

//encriptação do número
int numEncrypt(int numDecSize, int decVec[], int encVec[]){

  //posição nos vetores
  int encVecPos = 0;
  int decVecPos = 0;

  //'r' de 'ra' (número de repetições do algarismo 'a')
  int count = 0;

  for (decVecPos = 0; decVecPos < numDecSize; decVecPos++){   //análise 1 a 1 dos algarismos do vetor 'decVec'
    count++;
    if (decVec[decVecPos] != decVec[decVecPos + 1]){    //se uma sequência de algarismos iguais é quebrada
      encVec[encVecPos] = count;                        //escrever no vetor 'encVec'
      encVecPos++;
      encVec[encVecPos] = decVec[decVecPos];
      encVecPos++;

      count = 0;      //começar a contar novamente
    }
  }

  return encVecPos;
}

//desencriptação do número
void numDecrypt(int numEncSize, int encVec[], int decVec[]){

  //posições nos vetores
  int encVecPos = 0;
  int decVecPos = 0;

  //número de repetições de um algarismo
  int target = 0;

  for (encVecPos = 0; encVecPos <= numEncSize; encVecPos += 2){ //análise par a par dos números do vetor encriptado
    target = decVecPos + encVec[encVecPos];   //definição da posição até à qual se preenche com o nº 'a'
    while (decVecPos < target){
      decVec[decVecPos] = encVec[encVecPos + 1];  //preenchimento 'r' vezes de 'decVec' com o nº 'a'
      decVecPos++;
    }
  }

}
