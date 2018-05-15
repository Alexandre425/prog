#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "struct.h"
#include "define.h"

extern int minYear;

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
  countriesInfo = GetFileInfo(countriesFile);
  citiesInfo = GetFileInfo(citiesFile);

  //setting the global variables to the minimum year in each file
  minYear = countriesInfo.minYear;

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
