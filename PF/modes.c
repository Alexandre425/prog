#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "struct.h"
#include "define.h"

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
  countriesYearArray = textual_allocateAuxArray(countriesInfo.range);
  citiesYearArray = textual_allocateAuxArray(citiesInfo.range);

  textual_createSortedLists(countriesFile, countriesHead, countriesYearArray, citiesFile, citiesHead, citiesYearArray);

  free(countriesYearArray);
  free(citiesYearArray);
}

void visualMode(FILE* citiesFile){

}
