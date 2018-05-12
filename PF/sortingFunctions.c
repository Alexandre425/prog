#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "define.h"
#include "struct.h"

ListInfo GetFileInfo(FILE* file){

  ListInfo info;
  char buffer[BUFFER_SIZE];
  int year = 0;

  info.minYear = 3000;
  info.maxYear = 0;

  while (fgets(buffer, BUFFER_SIZE, file) != NULL){
    sscanf(buffer, "%d", &year);
    if (year < info.minYear)
      info.minYear = year;
    if (year > info.maxYear)
      info.maxYear = year;
  }

  info.range = info.maxYear - info.minYear;

  return info;
}

Country* CreateSortedCountriesList(FILE* countriesFile, Country** countryYearPointers)
