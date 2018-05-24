#include<SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "struct.h"
#include "define.h"

//first and last years of measurement, to help calculate the auxiliary pointer array index
int minYear = 0;
int maxYear = 0;

int main(int argc, char const *argv[]) {

  //data files from which temperature data is gathered
  FILE *countriesFile = NULL, *citiesFile = NULL;
  //names of the data files
  char fileNames[2][FILE_NAME_SIZE] = {{0}};

  //defines the mode the program will function (0 for textual, 1 for visual)
  int mode = -1;

  system("clear");
  //reads the user input arguments
  mode = readArguments(argc, argv, fileNames);
  //opening the files, depending on the read arguments
  openFiles(mode, fileNames, &countriesFile, &citiesFile);

  if (mode == 0)
    textualMode(countriesFile, citiesFile);
  else
    visualMode(citiesFile);

  closeFiles(countriesFile, citiesFile);

  printf("Exitting...\n");

  return EXIT_SUCCESS;
}
