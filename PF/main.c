#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "struct.h"
#include "define.h"

//first year of measurement, to help calculate the auxiliary pointer array index
int minYear = 0;

int main(int argc, char const *argv[]) {

  //data files from which temperature data is gathered
  FILE *countriesFile = NULL, *citiesFile = NULL;
  //names of the data files
  char fileNames[2][FILE_NAME_SIZE] = {{0}};

  //defines the mode the program will function (0 for textual, 1 for visual)
  int mode = -1;

  mode = readArguments(argc, argv, fileNames);

  openFiles(mode, fileNames, &countriesFile, &citiesFile);

  if (mode == 0)
    textualMode(countriesFile, citiesFile);
  else
    visualMode(citiesFile);

  closeFiles(countriesFile, citiesFile);
  return EXIT_SUCCESS;
}
