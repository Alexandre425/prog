#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_SIZE 140
#define STRING_INC_AMOUNT 10
#define ECHELONS 10
#define CHARS 4

void readFile(FILE*, char**);

void orderFile(char**, char**);

void printFile(FILE*, char**);

int main (void){

  FILE* initial = NULL;
  FILE* final = NULL;
  char* lines[FILE_SIZE] = {NULL};
  char* linesOut[FILE_SIZE] = {NULL};

  int i = 0;

  initial = fopen("braga17.txt", "r");
  final = fopen("braga17_out.txt", "w");

  if (initial == NULL){
    printf("Error when opening file!\n");
    exit(EXIT_FAILURE);
  }

  lines[0] = (char*)realloc(NULL, sizeof(char) * STRING_INC_AMOUNT);

  readFile(initial, lines);

  orderFile(lines, linesOut);

  printFile(final, linesOut);

  fclose(initial);
  fclose(final);
  return EXIT_SUCCESS;
}

void readFile(FILE* initial, char* lines[FILE_SIZE]){

  int size = STRING_INC_AMOUNT;
  char c = 0;
  int l = 0, p = 0;

  while (fgetc(initial) != '\n');

  while ( (c = fgetc(initial)) != EOF){

    lines[l][p++] = c;

    if (p == size){
      size = size + STRING_INC_AMOUNT;
      lines[l] = (char*)realloc(lines[l], sizeof(char) * size);
    }

    if (c == '\n' && l != FILE_SIZE - 1){
      l++;
      size = STRING_INC_AMOUNT;
      lines[l] = (char*)realloc(lines[l], sizeof(char) * size);
      p = 0;
    }
  }
}

void orderFile(char* lines[FILE_SIZE], char* linesOut[FILE_SIZE]){

  int ech = 0, l = 0, k = 0;

  char echelon[ECHELONS][CHARS] = {
    "F20",
    "F40",
    "F45",
    "M20",
    "M35",
    "M40",
    "M45",
    "M50",
    "M55",
    "M60"
  };

  for (ech = 0; ech < ECHELONS; ech++)
    for (l = 0; l < FILE_SIZE; l++)
      if ( strstr(lines[l], echelon[ech]) != NULL ){
        linesOut[k] = (char*)realloc(lines[l], strlen(lines[l]) * sizeof(char));
        printf("%s", linesOut[k]);
        k++;
      }
}

void printFile(FILE* final, char** linesOut){

int i = 0;
for (i = 0; i < FILE_SIZE; i++)
  fprintf(final, "%s", linesOut[i]);
}
