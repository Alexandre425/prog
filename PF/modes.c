#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "struct.h"
#include "define.h"

extern int minYear;
extern int maxYear;

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

}
