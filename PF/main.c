#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "define.h"
#include "struct.h"

int main(int argc, char const *argv[]) {

  //data files from which temperature data is gathered
  FILE *countriesFile = NULL, *citiesFile = NULL;
  //names of the data files
  char fileNames[2][FILE_NAME_SIZE] = {{0}};

  //defines the mode the program will function (0 for textual, 1 for visual)
  int mode = -1;

  mode = readArguments(argc, argv, fileNames);

  openFiles(mode, fileNames, &countriesFile, &citiesFile);

  if (mode == 0);
    textualMode();
  else
    visualMode();

  closeFiles(countriesFile, citiesFile);
  return EXIT_SUCCESS;
}
