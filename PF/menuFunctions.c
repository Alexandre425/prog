#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "struct.h"
#include "define.h"

//Main Menu: leads to all textual funtionalities
void mainMenu (){

  char c = 0;

  printf("Welcome to WarmingUp! Please select an option:\n");
  printf("\n1. Filter data\n");
  printf("2. Temperature history\n");
  printf("3. Yearly temperature analisis\n");
  printf("4. Global temperature analisis\n");
  printf("5. Exit\n");
  c = fgetc (stdin);

  switch (c) {
    case '1':
      dataFilterMenu ();
      break;
    case '2':
      tempHistoryMenu ();
      break;
    case '3'
      yearlyTempMenu ();
      break;
    case '4':
      globalTempMenu ();
      break;
    case '5':
      printf("Closing program ...\n");
      return;
      break;
    default:
      printf("Error! please insert one of the menu options!\n");
  }

}

//dataFilterMenu: allows the user to narrow the amount of information
void dataFilterMenu (){

  int c = 0;

  printf("\nFilter your data: \n");
  printf("\n1. By initial date\n");
  printf("2. By season\n");
  printf("3. Reset filters\n");
  printf("4. Return to main menu\n");
  c = fgetc (stdin);

  switch (c) {
    case '1':
      initalDateFilter ();
      break;
    case '2':
      seasonFilter ();
      break;
    case '3'
      resetFilter ();
      break;
    case '4':
      return;
      break;
    default:
      printf("Error! please insert one of the menu options!\n");
  }

}

//Function necessary to Temperature History calculations
int getSamplePeriod (){
  int samplePeriod = 0;

  printf("\nPlease insert a sampling period, in years:\n");
  scanf("%d", &samplePeriod);

  return samplePeriod;
}

//tempHistoryMenu: studies maximum, minimum and average temperatures in a defined period
void tempHistoryMenu (){

  int c = 0;
  int samplePeriod = 0;

  printf("\nTemperature History: \n");
  samplePeriod = getSamplePeriod ();
  printf("\n1. Global\n");
  printf("2. By country\n");
  printf("3. By city\n");
  printf("4. Change sampling period\n", );
  printf("5. Return to main menu\n");
  c = fgetc (stdin);

  switch (c) {
    case '1':
      tempHistoryGlobal ();
      break;
    case '2':
      tempHistoryCountry ();
      break;
    case '3'
      tempHistoryCity ();
      break;
    case '4':
      samplePeriod = getSamplePeriod ();
      break;
    case '5':
      return;
      break;
    default:
      printf("Error! please insert one of the menu options!\n");
  }

}

//Funtion necessary to
int getSampleYear (){
  int sampleYear = 0;

  printf("\nPlease insert the year you wish to analise:\n");
  scanf("%d", &sampleYear);

  return sampleYear;
}

void yearlyTempMenu (){

  int c = 0;
  int sampleYear = 0;

  printf("\nYearly Temperature Analisis:\n");
  sampleYear = getSampleYear ();
  printf("1. By countries\n");
  printf("2. By cities\n");
  printf("3. Change year\n", );
  printf("4. Return to main menu\n");
  c = fgetc (stdin);

  switch (c) {
    case '1':
      yearlyTempCountries ();
      break;
    case '2':
      yearlyTempCities();
      break;
    case '3'
      sampleYear = getSampleYear ();
      break;
    case '4':
      return;
      break
    default:
      printf("Error! please insert one of the menu options!\n");
  }

}

int getNumMonths (){
  int numMonths = 0;

  printf("\nPlease insert the number of months you wish to use on the Moving Average calculation:\n");
  scanf("%d", &numMonths);

  return numMonths;
}

void globalTempMenu (){

  int c = 0;
  int numMonths = 0;

  printf("\nYearly Temperature Analisis:\n");
  printf("This section uses the Moving Average concept in order to eliminate
  temperature data fluctuations and calculate global warming (or cooling)\n");
  numMonths = getNumMonths ();
  printf("Select one of the following options to analise data:\n");
  printf("1. Global\n");
  printf("2. By countries\n");
  printf("3. By cities\n");
  printf("4. Change the number of months selected\n");
  printf("5. Return to main menu\n");
  c = fgetc (stdin);

  switch (c) {
    case '1':
      globalTempGlobal ();
      break;
    case '2':
      globalTempCounries ();
      break;
    case '3':
      globalTempCities ();
      break;
    case '4'
      numMonths = getNumMonths ();
      break;
    case '5':
      return;
      break
    default:
      printf("Error! please insert one of the menu options!\n");
  }

}
