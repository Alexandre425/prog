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

//readFile: reads the file  and reallocs the memmory
void readFile(FILE* initial, char* lines[FILE_SIZE]){

  int size = STRING_INC_AMOUNT;
  char c = 0;
  int l = 0, p = 0; //line and position along the line

  while (fgetc(initial) != '\n');

  //Runs the file line by line until EOF
  while ( (c = fgetc(initial)) != EOF){

    lines[l][p++] = c;

    //if current position is the same as current size, increases the size by 10
    if (p == size - 2){
      size = size + STRING_INC_AMOUNT;
      lines[l] = (char*)realloc(lines[l], sizeof(char) * size);
    }

    //at the end of the current line: increment line, reset position
    if (c == '\n' && l != FILE_SIZE - 1){
      lines[l][p] = '\0';
      l++;
      size = STRING_INC_AMOUNT;
      lines[l] = (char*)realloc(lines[l], sizeof(char) * size);
      p = 0;
    }
  }
}

//orderFile: the file is ordered by echelons
void orderFile(char* lines[FILE_SIZE], char* linesOut[FILE_SIZE]){

  int ech = 0, l = 0, k = 0;

  //string that contains all echelons
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

  for (ech = 0; ech < ECHELONS; ech++)                                              //for each echelon
    for (l = 0; l < FILE_SIZE; l++)                                                 //for every file line
      if ( strstr(lines[l], echelon[ech]) != NULL ){                                //searches for a word (echelon) in a line
        linesOut[k] = (char*)realloc(lines[l], strlen(lines[l]) * sizeof(char));    //copies the intire line to a new file
        printf("%s", linesOut[k]);
        k++;
      }
}

//printFile: prints the file
void printFile(FILE* final, char** linesOut){

int i = 0;
for (i = 0; i < FILE_SIZE; i++)
  fprintf(final, "%s", linesOut[i]);
}
