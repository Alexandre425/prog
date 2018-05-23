#include<SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "struct.h"
#include "define.h"

extern int minYear;
extern int maxYear;

int readArguments(int argc, char const *argv[], char fileNames[2][FILE_NAME_SIZE]){

  int mode = -1;

  for (int i = 1; i < argc; i++){

    printf("%s\n", argv[i]);

    if (strcmp(argv[i], "-g") == 0){
      mode = 1;
    }
    if (strcmp(argv[i], "-t") == 0){
      mode = 0;
    }
    if (strcmp(argv[i], "-f1") == 0){
      strcpy(fileNames[0], argv[i+1]);
    }
    if (strcmp(argv[i], "-f2") == 0){
      strcpy(fileNames[1], argv[i+1]);
    }
  }

  if (mode == 0)
    printf("Starting in text mode\n");
  if (mode == 1)
    printf("Starting in visual mode\n");
  if (mode == -1){
    printf("Mode undefined! Execute the program in one of the two modes\n");
    exit (EXIT_FAILURE);
  }

  return mode;
}

void openFiles(int mode, char fileNames[2][FILE_NAME_SIZE], FILE** countriesFile, FILE** citiesFile){

  //open the countries file if we are in textual mode
  if (mode == 0){
    *countriesFile = fopen(fileNames[0], "r");
    if (*countriesFile == NULL){
      printf("ERROR! Could not open file 1! Did you execute the program with the correct parameters?\n");
      exit (EXIT_FAILURE);
    }
  }

  //always open the cities file
  *citiesFile = fopen(fileNames[1], "r");
  if (*citiesFile == NULL){
    printf("ERROR! Could not open file 2! Did you execute the program with the correct parameters?\n");
    exit (EXIT_FAILURE);
  }

}

void closeFiles(FILE* countriesFile, FILE* citiesFile){

  if (citiesFile != NULL)
    fclose(citiesFile);
  if (countriesFile != NULL)
    fclose(countriesFile);
}
