#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "struct.h"
#include "define.h"

extern int minYear;
extern int maxYear;

void mainMenu (node_t* countriesHead, node_t* citiesHead){

  //head pointers to the filtered lists
  node_t* filtCountriesHead = NULL;
  node_t* filtCitiesHead = NULL;

  char c = 0;

  //getting working copies of the list in case the user doesn't reset the data filters
  resetFilter (countriesHead, citiesHead, &filtCountriesHead, &filtCitiesHead);

  while(true){

    system("clear");

    printf("Welcome to WarmingUp! Please select an option:\n");
    printf("\n1. Filter Data\n");
    printf("2. Temperature History\n");
    printf("3. Yearly Temperature Analisis\n");
    printf("4. Global Temperature Analisis\n");
    printf("5. Exit\n");

    c = getchar();
    getchar();

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
        system("clear");
        printf("Running exit routine:\n");
        filtCountriesHead = freeSortedList(filtCountriesHead);
        filtCitiesHead = freeSortedList(filtCitiesHead);
        return;
        break;
      default:
        printf("Error! please insert one of the menu options!\n");
        break;
    }
  }


}

void dataFilterMenu (node_t* countriesHead, node_t* citiesHead, node_t** filtCountriesHead, node_t** filtCitiesHead){

  char c = 0;
  while(true) {

    system("clear");

    printf("Filter Data: \n");
    printf("\n1. By initial date\n");
    printf("2. By season\n");
    printf("3. Reset filters\n");
    printf("4. Return to main menu\n");

    c = getchar();

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
  char buffer[BUFFER_SIZE] = {0};


  while (samplePeriod <= 0 || samplePeriod > 1000){
    buffer[0] = '\0';
    system("clear");
    printf("Insert a sampling period, in years: ");
    fgets(buffer, BUFFER_SIZE, stdin);
    sscanf(buffer, "%d", &samplePeriod);

    if (samplePeriod <= 0 || samplePeriod > 1000){
      printf("Insert a valid sampling period!\n");
      sleep(2);
    }
  }

  return samplePeriod;
}

void tempHistoryMenu (node_t* filtCountriesHead, node_t* filtCitiesHead){

  char c = 0;
  int samplePeriod = 0;

  samplePeriod = getSamplePeriod ();

  while(true) {

    system("clear");

    printf("Temperature History: \n");
    printf("\n1. Global\n");
    printf("2. By country\n");
    printf("3. By city\n");
    printf("4. Change sampling period\n");
    printf("5. Return to main menu\n");

    c = getchar();
    getchar ();

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
  char buffer[BUFFER_SIZE] = {0};


  while (sampleYear < minYear || sampleYear > maxYear){
    buffer[0] = '\0';
    system("clear");
    printf("Insert the year you wish to analise:\n");
    fgets(buffer, BUFFER_SIZE, stdin);
    sscanf(buffer, "%d", &sampleYear);

    if (sampleYear < minYear || sampleYear > maxYear){
      printf("Inserted year not included in the data!\n");
      sleep(2);
    }
  }

  return sampleYear;
}

void yearlyTempMenu (node_t* filtCountriesHead, node_t* filtCitiesHead){

  char c = 0;
  int sampleYear = 0;

  sampleYear = getSampleYear ();

  while(true) {

    system("clear");

    printf("Yearly Temperature Analisis:\n");
    printf("1. By countries\n");
    printf("2. By cities\n");
    printf("3. Change year of analisis\n");
    printf("4. Return to main menu\n");

    c = getchar();
    getchar();

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
  char buffer[BUFFER_SIZE] = {0};


  while (numYears <= 0 || numYears > 1000 || (numYears % 2) == 0){
    buffer[0] = '\0';
    system("clear");
    printf("\nInsert an odd number of years for the Moving Average calculation: ");
    fgets(buffer, BUFFER_SIZE, stdin);
    sscanf(buffer, "%d", &numYears);

    if (numYears <= 0 || numYears > 1000 || (numYears % 2) == 0){
      printf("Inserted number is not valid! Make sure it is an odd number\n");
      sleep(2);
    }
  }



  return numYears;
}

void globalTempMenu (node_t* filtCountriesHead, node_t* filtCitiesHead){

  char c = 0;
  int numYears = 0;

  numYears = getNumYears ();

  while(true){

    system("clear");

    printf("Yearly Temperature Analisis:\n");
    printf("This section uses the Moving Average concept in order to eliminate temperature data fluctuations and calculate global climate change\n");
    printf("Select one of the following options to analise the temperature change:\n");
    printf("1. Globally\n");
    printf("2. By a country\n");
    printf("3. By a city\n");
    printf("4. Change the number of years selected\n");
    printf("5. Return to main menu\n");

    c = getchar();
    getchar();

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

  char buffer[BUFFER_SIZE] = {0};
  int month = 0;
  int year = 0;
  node_t* auxCountries = NULL;
  node_t* auxCities = NULL;
  node_t* oldCountriesHead = *filtCountriesHead;
  node_t* oldCitiesHead = *filtCitiesHead;

  while (month <= 0 || month > 12 || year < minYear || year > maxYear){
    buffer[0] = '\0';
    system("clear");
    printf("Insert an initial date (MM/YYYY).\n");
    printf("Any data before that date will be discarded: ");
    fgets(buffer, BUFFER_SIZE, stdin);
    sscanf(buffer, "%d/%d", &month, &year);

    if (month <= 0 || month > 12 || year < minYear || year > maxYear){
      printf("Inserted date not included in the data!\n");
      sleep(2);
    }
  }

  while ((*filtCountriesHead)->next != NULL){
    //if next entry is the first we want to keep
    if ((*filtCountriesHead)->next->data.year == year && (*filtCountriesHead)->next->data.month == month){
      auxCountries = *filtCountriesHead;
      *filtCountriesHead = (*filtCountriesHead)->next;
      //severing the list
      auxCountries->next = NULL;
      //this deletes the first part of the list
      freeSortedList(oldCountriesHead);
      break;
    }
    (*filtCountriesHead) = (*filtCountriesHead)->next;
  }

  //same for the city list
  while ((*filtCitiesHead)->next != NULL){
    if ((*filtCitiesHead)->next->data.year == year && (*filtCitiesHead)->next->data.month == month){
      auxCities = *filtCitiesHead;
      *filtCitiesHead = (*filtCitiesHead)->next;
      auxCities->next = NULL;
      freeSortedList(oldCitiesHead);
      break;
    }
    (*filtCitiesHead) = (*filtCitiesHead)->next;
  }
}

void deleteSeason(node_t** head, int iniMonth, int finMonth){

  //traverses the list
  node_t* aux = NULL;
  //the first node of an unwanted section (to be deleted)
  node_t* unwanted = NULL;
  //the end of the section of wanted data (to connect to the next)
  node_t* validEnd = NULL;
  //the end of the next section of wanted data
  node_t* validBegin = NULL;

  //finding the new head (which may stay the same)
  while (*head != NULL){
    //this condition boils down to:
    //if the head's month is within the inserted monthly bracket
    //if it is, we break from the cycle
    if(
      (
        iniMonth > finMonth &&  (
          ( (*head)->data.month >= iniMonth && (*head)->data.month <= 12) ||
          ( (*head)->data.month >= 1 && (*head)->data.month <= finMonth)
        )
      )||(
        iniMonth <= finMonth && (
          (*head)->data.month >= iniMonth && (*head)->data.month <= finMonth )
      )
    )
    break;
    //if it is not, we keep moving the head forwards until we reach the new head
    aux = *head;
    (*head) = (*head)->next;
  }
  //severing and deleting the first part of the list
  if (aux != NULL)
    aux->next = NULL;
  aux = freeSortedList(aux);


  //aux will be the pointer we use to traverse the list until we find data outside the wanted bracket
  aux = *head;

  while (true){
    //this cycle will leave aux on the last element belonging to the wanted bracket
    //which means aux->next is the beggining of a section we wish to delete
    while (aux->next != NULL){
      //if the data AFTER aux is still valid
      if(
        (
          iniMonth > finMonth &&  (
            ( aux->next->data.month >= iniMonth && aux->next->data.month <= 12) ||
            ( aux->next->data.month >= 1 && aux->next->data.month <= finMonth)
          )
        )||(
          iniMonth <= finMonth && (
            aux->next->data.month >= iniMonth && aux->next->data.month <= finMonth )
        )
      ){
        //we go to the next element and don't execute the break
        aux = aux->next;
        continue;
      }
      break;
    }

    //if it reaches the end of the list, returns
    if (aux->next == NULL)
      return;

    validEnd = aux;
    unwanted = aux->next;

    aux = unwanted;

    //this cycle leaves aux on the last element which does not belong to the wanted bracket
    //this means aux->next is what we want to connect to the last valid data
    while (aux->next != NULL){
      //if the data AFTER aux is valid
      if(
        (
          iniMonth > finMonth &&  (
            ( aux->next->data.month >= iniMonth && aux->next->data.month <= 12) ||
            ( aux->next->data.month >= 1 && aux->next->data.month <= finMonth)
          )
        )||(
          iniMonth <= finMonth && (
            aux->next->data.month >= iniMonth && aux->next->data.month <= finMonth )
        )
      )
        //we break away from the cycle
        break;
      aux = aux->next;
    }

    validBegin = aux->next;
    //severing the list
    aux->next = NULL;

    unwanted = freeSortedList(unwanted);

    //when it reaches the end of the list, returns after deleting the unwanted part of the list
    if (aux->next == NULL)
      return;

    //connecting the ending of the last wanted data with the beggining of the next
    validEnd->next = validBegin;
    aux = validBegin;
  }



}

void seasonFilter(node_t** filtCountriesHead, node_t** filtCitiesHead){

  char buffer[BUFFER_SIZE] = {0};
  int iniMonth = 0, finMonth = 0;

  while (iniMonth <= 0 || iniMonth > 12 || finMonth <= 0 || finMonth > 12){
    buffer[0] = '\0';
    system("clear");
    printf("Insert an initial and a final month (MM-MM).\n");
    printf("Any data not inserted in that bracket will be discarded: ");
    fgets(buffer, BUFFER_SIZE, stdin);
    sscanf(buffer, "%d-%d", &iniMonth, &finMonth);

    if (iniMonth <= 0 || iniMonth > 12 || finMonth <= 0 || finMonth > 12){
      printf("Inserted months are not valid!\n");
      sleep(2);
    }
  }

  deleteSeason(filtCountriesHead, iniMonth, finMonth);
  deleteSeason(filtCitiesHead, iniMonth, finMonth);


}

void resetFilter(node_t* countriesHead, node_t* citiesHead, node_t** filtCountriesHead, node_t** filtCitiesHead){

  //runs through the data to be copied
  node_t* aux1 = NULL;
  //runs through the copied data
  node_t* aux2 = NULL;
  node_t* newNode = NULL;
  temp data;
  data2 pos;

  *filtCountriesHead = freeSortedList(*filtCountriesHead);
  *filtCitiesHead = freeSortedList(*filtCitiesHead);

  //auxiliary pointer to the head of the to-be-copied list
  aux1 = countriesHead;

  //getting the head of the list copy
  data.year = aux1->data.year;
  data.month = aux1->data.month;
  data.temp = aux1->data.temp;
  pos = aux1->pos;
  strcpy(data.name, aux1->data.name);
  *filtCountriesHead = getNewNode(data, pos);

  //auxiliary pointer to the head of the list copy
  aux2 = *filtCountriesHead;

  while (aux1->next != NULL){

    aux1 = aux1->next;

    data.year = aux1->data.year;
    data.month = aux1->data.month;
    data.temp = aux1->data.temp;
    pos = aux1->pos;
    strcpy(data.name, aux1->data.name);
    newNode = getNewNode(data, pos);

    //inserting the new node after the last
    aux2->next = newNode;
    aux2 = aux2->next;
  }

    //same process for the city list

    aux1 = citiesHead;

    data.year = aux1->data.year;
    data.month = aux1->data.month;
    data.temp = aux1->data.temp;
    pos = aux1->pos;
    strcpy(data.name, aux1->data.name);
    *filtCitiesHead = getNewNode(data, pos);

    aux2 = *filtCitiesHead;

    while (aux1->next != NULL){

      aux1 = aux1->next;

      data.year = aux1->data.year;
      data.month = aux1->data.month;
      data.temp = aux1->data.temp;
      pos = aux1->pos;
      strcpy(data.name, aux1->data.name);
      newNode = getNewNode(data, pos);

      //inserting the new node after the last
      aux2->next = newNode;
      aux2 = aux2->next;
  }
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
