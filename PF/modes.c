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

float minPointTemp;
float maxPointTemp;

void textualMode(FILE* countriesFile, FILE* citiesFile){

  //information structs about the lists
  ListInfo countriesInfo, citiesInfo;

  //head pointers to both lists
  node_t* countriesHead = NULL;
  node_t* citiesHead = NULL;

  //Arrays of pointers (to the first measurement of each year) for a faster
  //insertion sort
  node_t **countriesYearArray = NULL;
  node_t **citiesYearArray = NULL;

  //getting the information about the files needed to set up auxiliary pointers
  countriesInfo = getFileInfo(countriesFile);
  citiesInfo = getFileInfo(citiesFile);

  //setting the global variables to the minimum and maximum years in each file
  minYear = countriesInfo.minYear;
  maxYear = countriesInfo.maxYear;

  //allocating the auxiliary pointer arrays
  countriesYearArray = allocateAuxArray(countriesInfo.range);
  citiesYearArray = allocateAuxArray(citiesInfo.range);

  //creating both sorted lists
  createSortedLists(countriesFile, &countriesHead, countriesYearArray, citiesFile, &citiesHead, citiesYearArray);

  mainMenu(countriesHead, citiesHead);
  //freeing all memory still in use
  countriesHead = freeSortedList(countriesHead);
  citiesHead = freeSortedList(citiesHead);
  free(countriesYearArray);
  free(citiesYearArray);
}

void visualMode(FILE* citiesFile){

  ListInfo citiesInfo;
  node_t* citiesHead = NULL;
  node_t* pointsHead = NULL;

  graph* SDL = malloc(sizeof(graph));
  if (SDL == NULL){
    printf("Memory allocation error!\n");
    exit (EXIT_FAILURE);
  }

  //getting the information about the file
  citiesInfo = getFileInfo(citiesFile);
  //setting the global variables to the minimum and maximum years in each file
  minYear = citiesInfo.minYear;
  maxYear = citiesInfo.maxYear;
  //loading the file onto a list
  citiesHead = loadCityList(citiesFile);
  //creating a list to easily draw all the points
  pointsHead = createMedianTempCityList(citiesHead);
  //getting the minimum and maximum median temperatures for point color determination
  //these are assigned to global variables
  getMinMaxTemp(pointsHead);
  //freeing the first list (will not be needed anymore)
  citiesHead = freeSortedList(citiesHead);

  //initializing everything SDL related
  initEverything(SDL);

  mainLoop(pointsHead, SDL);

  //freeing the list used for drawing points
  pointsHead = freeSortedList(pointsHead);
}
