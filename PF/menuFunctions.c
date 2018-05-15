#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "struct.h"
#include "define.h"

void mainMenu (node_t* countriesHead, node_t* citiesHead){

  //head pointers to the filtered lists
  node_t* filtCountriesHead = NULL;
  node_t* filtCitiesHead = NULL;

  char c = 0;


  while(c = getchar()){

    printf("Welcome to WarmingUp! Please select an option:\n");
    printf("\n1. Filter data\n");
    printf("2. Temperature history\n");
    printf("3. Yearly temperature analisis\n");
    printf("4. Global temperature analisis\n");
    printf("5. Exit\n");

    switch (c) {
      case '1':
        dataFilterMenu (countriesHead, citiesHead, &filtCountriesHead, &filtCitiesHead);
        break;
      case '2':
        tempHistoryMenu (filtCountriesHead, filtCitiesHead);
        break;
      case '3':
        yearlyTempMenu (filtCountriesHead, filtCitiesHead);
        break;
      case '4':
        globalTempMenu (filtCountriesHead, filtCitiesHead);
        break;
      case '5':
        printf("Closing program ...\n");
        return;
        break;
      default:
        printf("Error! please insert one of the menu options!\n");
        break;
    }
  }

  filtCountriesHead = freeSortedList(filtCountriesHead);
  filtCitiesHead = freeSortedList(filtCitiesHead);

}

void dataFilterMenu (node_t* countriesHead, node_t* citiesHead, node_t** filtCountriesHead, node_t** filtCitiesHead){

  int c = 0;
  while(c = getchar()){

    printf("\nFilter your data: \n");
    printf("\n1. By initial date\n");
    printf("2. By season\n");
    printf("3. Reset filters\n");
    printf("4. Return to main menu\n");

    switch (c) {
      case '1':
        initalDateFilter (filtCountriesHead, filtCitiesHead);
        break;
      case '2':
        seasonFilter (filtCountriesHead, filtCitiesHead);
        break;
      case '3':
        resetFilter (countriesHead, citiesHead, filtCountriesHead, filtCitiesHead);
        break;
      case '4':
        return;
        break;
      default:
        printf("Error! please insert one of the menu options!\n");
        break;
    }
  }
}

int getSamplePeriod (){
  int samplePeriod = 0;

  printf("\nPlease insert a sampling period, in years:\n");
  scanf("%d", &samplePeriod);

  return samplePeriod;
}

void tempHistoryMenu (node_t* filtCountriesHead, node_t* filtCitiesHead){

  int c = 0;
  int samplePeriod = 0;

  samplePeriod = getSamplePeriod ();

  while(c = getchar()){

    printf("\nTemperature History: \n");
    printf("\n1. Global\n");
    printf("2. By country\n");
    printf("3. By city\n");
    printf("4. Change sampling period\n");
    printf("5. Return to main menu\n");

    switch (c) {
      case '1':
        tempHistoryGlobal (filtCountriesHead, filtCitiesHead);
        break;
      case '2':
        tempHistoryCountry (filtCountriesHead, filtCitiesHead);
        break;
      case '3':
        tempHistoryCity (filtCountriesHead, filtCitiesHead);
        break;
      case '4':
        samplePeriod = getSamplePeriod ();
        break;
      case '5':
        return;
        break;
      default:
        printf("Error! please insert one of the menu options!\n");
        break;
    }
  }

}

int getSampleYear (){
  int sampleYear = 0;

  printf("\nPlease insert the year you wish to analise:\n");
  scanf("%d", &sampleYear);

  return sampleYear;
}

void yearlyTempMenu (node_t* filtCountriesHead, node_t* filtCitiesHead){

  int c = 0;
  int sampleYear = 0;

  while(c = getchar()){
    printf("\nYearly Temperature Analisis:\n");
    sampleYear = getSampleYear ();
    printf("1. By countries\n");
    printf("2. By cities\n");
    printf("3. Change year of analisis\n");
    printf("4. Return to main menu\n");

    switch (c) {
      case '1':
        yearlyTempCountries (filtCountriesHead, filtCitiesHead);
        break;
      case '2':
        yearlyTempCities(filtCountriesHead, filtCitiesHead);
        break;
      case '3':
        sampleYear = getSampleYear ();
        break;
      case '4':
        return;
        break;
      default:
        printf("Error! please insert one of the menu options!\n");
        break;
    }
  }
}

int getNumYears (){
  int numYears = 0;

  printf("\nPlease insert the number of years you wish to use for the Moving Average calculation:\n");
  scanf("%d", &numYears);

  return numYears;
}

void globalTempMenu (node_t* filtCountriesHead, node_t* filtCitiesHead){

  int c = 0;
  int numYears = 0;

  while(c = getchar()){

    printf("\nYearly Temperature Analisis:\n");
    printf("This section uses the Moving Average concept in order to eliminate temperature data fluctuations and calculate global climate change\n");
    numYears = getNumYears ();
    printf("Select one of the following options to analise the temperature change:\n");
    printf("1. Globally\n");
    printf("2. By a country\n");
    printf("3. By a city\n");
    printf("4. Change the number of years selected\n");
    printf("5. Return to main menu\n");

    switch (c) {
      case '1':
        globalTempGlobal (filtCountriesHead, filtCitiesHead);
        break;
      case '2':
        globalTempCountry (filtCountriesHead, filtCitiesHead);
        break;
      case '3':
        globalTempCity (filtCountriesHead, filtCitiesHead);
        break;
      case '4':
        numYears = getNumYears ();
        break;
      case '5':
        return;
        break;
      default:
        printf("Error! please insert one of the menu options!\n");
        break;
    }
  }
}

//######################################################

void initalDateFilter(node_t** filtCountriesHead, node_t** filtCitiesHead){

}

void seasonFilter(node_t** filtCountriesHead, node_t** filtCitiesHead){

}

void resetFilter(node_t*countriesHead, node_t* citiesHead, node_t** filtCountriesHead, node_t** filtCitiesHead){

}

//######################################################

void tempHistoryGlobal(node_t* filtCountriesHead, node_t* filtCitiesHead){

}

void tempHistoryCountry(node_t* filtCountriesHead, node_t* filtCitiesHead){

}

void tempHistoryCity(node_t* filtCountriesHead, node_t* filtCitiesHead){

}

//######################################################

void yearlyTempCountries(node_t* filtCountriesHead, node_t* filtCitiesHead){

}

void yearlyTempCities(node_t* filtCountriesHead, node_t* filtCitiesHead){

}

//######################################################

void globalTempGlobal(node_t* filtCountriesHead, node_t* filtCitiesHead){

}

void globalTempCountry(node_t* filtCountriesHead, node_t* filtCitiesHead){

}

void globalTempCity(node_t* filtCountriesHead, node_t* filtCitiesHead){

}
