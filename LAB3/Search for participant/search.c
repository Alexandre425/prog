#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_SIZE 140
#define STRING_SIZE 200
#define ECHELONS 10
#define CHARS 3


int main(int argc, char *argv[]) {

  FILE* initial = NULL;
  char name[STRING_SIZE] = {0};
  char temp[STRING_SIZE] = {0};
  int i = 0;

  int globalPos = 0, age = 0, echelonPos = 0;
  char gender = 0;


  initial = fopen(argv[1], "r");
  if (initial == NULL){
    printf("Error when opening file!\n");
    exit(EXIT_FAILURE);
  }

  strcpy(name, argv[2]);
  for (i = 3; i < argc; i++){
    strcat(name, " ");
    strcat(name, argv[i]);
  }

  while ( fgets(temp, STRING_SIZE, initial) != NULL )
    if (strstr(temp, name) != NULL){
      printf("-------Participant %s-------\n", name);
      sscanf(temp, "%d\t%c%d\t%d", &globalPos, &gender, &age, &echelonPos);
      printf("Global position: %d \n", globalPos);
      printf("Echelon position: %d \n", echelonPos);
    }


  fclose(initial);
  return EXIT_SUCCESS;
}
