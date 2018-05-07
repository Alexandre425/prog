#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_INC_AMOUNT 10
#define ECHELONS 10
#define CHARS 4

void readFile(FILE*, char**, int*);

void orderFile(char**, char**, int);

void printFile(FILE*, char**, int);

int main (void){

  FILE* initial = NULL;
  FILE* final = NULL;
  char** lines = {NULL};
  char** linesOut = {NULL};

  int i = 0, l = 0;

  initial = fopen("braga17.txt", "r");
  final = fopen("braga17_out.txt", "w");

  if (initial == NULL){
    printf("Error when opening file!\n");
    exit(EXIT_FAILURE);
  }

  lines[0] = (char*)realloc(NULL, sizeof(char) * STRING_INC_AMOUNT);

  readFile(initial, lines, &l);
  orderFile(lines, linesOut, l);
  printFile(final, linesOut, l);

  fclose(initial);
  fclose(final);
  return EXIT_SUCCESS;
}

//readFile: reads the file  and reallocs the memmory
void readFile(FILE* initial, char** lines, int* l){

  int size = STRING_INC_AMOUNT;
  char c = 0;
  int p = 0; //line and position along the line

  while (fgetc(initial) != '\n');

  //Runs the file line by line until EOF
  while ( (c = fgetc(initial)) != EOF){

    lines[*l][p++] = c;

    //if current position is the same as current size, increases the size by 10
    if (p == size - 2){
      size = size + STRING_INC_AMOUNT;
      lines[*l] = (char*)realloc(lines[*l], sizeof(char) * size);
    }

    //at the end of the current line: increment line, reset position
<<<<<<< HEAD
    if (c == '\n'){
      (*l)++;
=======
    if (c == '\n' && l != FILE_SIZE - 1){
      lines[l][p] = '\0';
      l++;
>>>>>>> fcd321b4372abba00a06093d0f3dda9cd9d77696
      size = STRING_INC_AMOUNT;
      lines[*l] = (char*)realloc(lines[*l], sizeof(char) * size);
      p = 0;
    }
  }
}

//orderFile: the file is ordered by echelons
void orderFile(char** lines, char** linesOut, int maxLines){

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
    for (l = 0; l < maxLines; l++)                                                  //for every file line
      if ( strstr(lines[l], echelon[ech]) != NULL ){                                //searches for a word (echelon) in a line
        linesOut[k] = (char*)realloc(lines[l], strlen(lines[l]) * sizeof(char));    //copies the entire line to a new file
        printf("%s", linesOut[k]);
        k++;
      }
}

//printFile: prints the file
void printFile(FILE* final, char** linesOut, int maxLines){

int i = 0;
for (i = 0; i < maxLines; i++)
  fprintf(final, "%s", linesOut[i]);
}
