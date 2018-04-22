#include <stdio.h>
#include <stdlib.h>

#define STRING_SIZE 100

typedef struct FinishTime{
  int h;
  int m;
  int s;
} FinishTime;

typedef struct Runner{
  int globalPos;
  int echelonPos;
  int dorsalNum;
  char echelon[4];
  char name[STRING_SIZE];
  char gender;
  struct FinishTime finishTime;

} Runner;

void structAlloc(FILE*, Runner**, int*);
void readFile(FILE*, Runner*, int);

int main (void){

  Runner* runners = NULL;
  int size = 0;

  FILE* file;

  file = fopen("braga17.txt", "r");
  if (file == NULL){
    printf("Error when opening the file!\n");
    exit (EXIT_FAILURE);
  }

  structAlloc(file, &runners, &size);
  readFile(file, runners, size);

  free(runners);

  return EXIT_SUCCESS;
}


void readFile(FILE* file, Runner* runners, int size){

  char temp[STRING_SIZE] = {0};

  int l = 0;
  //ignore the first line
  fgets(temp, 200, file);

  for (l = 0; l < size; l++){
    fgets(temp, 200, file);
    sscanf(temp, "%d\t%s\t%d\t%d\t%s\t%c\t%d:%d:%d", runners[l].globalPos, runners[l].echelon, runners[l].echelonPos, runners[l].dorsalNum,
      runners[l].name, runners[l].gender, runners[l].finishTime.h, runners[l].finishTime.m, runners[l].finishTime.s);
  }
}

void structAlloc(FILE* file, Runner** runners, int* size){

  char temp[STRING_SIZE] = {0};

  //ignore the first line
  fgets(temp, 200, file);

  //count all the runners
  while (fgets(temp , 200, file) != NULL)
    (*size)++;

  //rewinds the file
  rewind(file);

  //allocating memmory for all the runners
  *runners = (Runner*)malloc( (*size) * sizeof(Runner) );
    if (*runners == NULL)
      exit (EXIT_FAILURE);

}
