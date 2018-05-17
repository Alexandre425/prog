#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "struct.h"
#include "define.h"

extern int minYear;
extern int maxYear;

int filteredByInitialDate = 0;
int filteredBySeason = 0;

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
        if (filteredByInitialDate == 0)
          initalDateFilter (filtCountriesHead, filtCitiesHead);
        else{
          printf("Already filtered! To change the filters, reset them first\n");
          sleep(3);
        }
        filteredByInitialDate = 1;
        break;
      case '2':
        if (filteredBySeason == 0)
          seasonFilter (filtCountriesHead, filtCitiesHead);
        else{
          printf("Already filtered! To change the filters, reset them first\n");
          sleep(3);
        }
          filteredBySeason = 1;
        break;
      case '3':
        resetFilter (countriesHead, citiesHead, filtCountriesHead, filtCitiesHead);
        filteredBySeason = 0;
        filteredByInitialDate = 0;
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
        tempHistoryGlobal (filtCountriesHead, samplePeriod);
        break;
      case '2':
        tempHistoryCountry (filtCountriesHead, samplePeriod);
        break;
      case '3':
        tempHistoryCity (filtCitiesHead, samplePeriod);
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

  //finding the new head (which may stay the same)
  while (*head != NULL){
    //this condition boils down to:
    //if the head's month is within the inserted monthly bracket
    //we break from the cycle
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
    //if it is not, we keep deleting the head, until the above condition is met
    *head = deleteHead(*head);
  }

  aux = *head;

  while (aux->next != NULL){
    //if the auxiliary pointer's month is within the inserted monthly bracket
    //we go through to the next list entry from the cycle
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
      aux = aux->next;
    else
      //if it is not, we delete the node
      deleteNode(aux);
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

int getAllocSize(int range, int samplePeriod){

  int allocSize = 0;

  range++;

  allocSize = range / samplePeriod;

  if ((range % samplePeriod) != 0)
    allocSize++;

  return allocSize;
}

void printTempHistory(char** table, int lines){

  int page = 0;
  int maxPage = 0;
  int firstEntry = 2;
  int target = 2 + PAGE_SIZE;

  maxPage = lines / PAGE_SIZE;
  if ((lines % PAGE_SIZE) != 0)
    maxPage++;

  for (page = 0; page < maxPage; page++){
    system("clear");
    //printing the header
    printf("%s%s", table[0], table[1]);

    //if the target excedes the number of entries (the end of the page)
    if (target > lines + 2)
      target = lines + 2;

    for (int i = firstEntry; i < target; i++){
      printf("%s\n", table[i]);
    }

    firstEntry += (PAGE_SIZE);
    target += (PAGE_SIZE);

    getchar();

  }

}

void tempHistoryGlobal(node_t* filtCountriesHead, int samplePeriod){

  ListInfo info;
  info = getListInfo(filtCountriesHead);
  int lines = getAllocSize(info.range, samplePeriod);
  node_t* aux = NULL;
  int targetYear = info.minYear + samplePeriod;
  float maxTemp = -3000.0f, minTemp = 3000.0f, medTemp = 0.0f;
  float carryAdder = 0.0f;
  int counter = 0;
  char (*table)[TABLE_SIZE] = NULL;

  table = (char*)malloc(sizeof(char*) * (lines + 2));
    if (table == NULL){
      printf("Memory allocation error!\n");
      exit (EXIT_FAILURE);
    }
  aux = filtCountriesHead;

  system("clear");
  sprintf(table[0], "Global Temperature History - %d year sample period\n\n", samplePeriod);
  sprintf(table[1], "INTERVALS |   MIN. T\t|   MAX. T\t|   MED. T\n");

  for (int i = 0; i < lines; i++){

    while (aux != NULL && aux->data.year < targetYear){
      if (aux->data.temp < minTemp)
        minTemp = aux->data.temp;
      if (aux->data.temp > maxTemp)
        maxTemp = aux->data.temp;

      carryAdder += aux->data.temp;
      counter++;
      aux = aux->next;
    }

    medTemp = (float)carryAdder / (float)counter;
    carryAdder = 0.0f;
    counter = 0;

    if (targetYear > info.maxYear)
      targetYear = info.maxYear;

    if (maxTemp != -3000.0f && minTemp != 3000.0f)
      sprintf(table[i+2], "%d-%d |   %.2f\t|   %.2f\t|   %.2f\n", (targetYear - samplePeriod), targetYear, maxTemp, minTemp, medTemp);

    minTemp = 3000.0f;
    maxTemp = -3000.f;
    medTemp = 0.0f;

    targetYear += samplePeriod;

  }

  printTempHistory(table, lines);
  //free(table);

}

void tempHistoryCountry(node_t* filtCountriesHead, int samplePeriod){

  ListInfo info;
  info = getListInfo(filtCountriesHead);
  int lines = getAllocSize(info.range, samplePeriod);
  node_t* aux = NULL;
  char buffer[BUFFER_SIZE] = {0};
  int targetYear = info.minYear + samplePeriod;
  float maxTemp = -3000.0f, minTemp = 3000.0f, medTemp = 0.0f;
  float carryAdder = 0.0f;
  int counter = 0;
  char (*table)[TABLE_SIZE] = NULL;
  int foundName = 0;

  table = (char*)malloc(sizeof(char*) * (lines + 2));
    if (table == NULL){
      printf("Memory allocation error!\n");
      exit (EXIT_FAILURE);
    }

  system("clear");

  printf("Insert the name of a country to get it's temperature history\nNote: The name is case-sensitive!\nCountry: ");
  fgets(buffer, BUFFER_SIZE, stdin);
  strtok(buffer, "\n");

  aux = filtCountriesHead;
  while (aux != NULL){
    if (strstr(aux->data.name, buffer) != NULL){
      strcpy(buffer, aux->data.name);
      foundName = 1;
      break;
    }

    aux = aux->next;
  }

  if (foundName == 0){
    printf("Could not find a country named %s\n", buffer);
    sleep(3);
    return;
  }

  sprintf(table[0], "Temperature history for %s - %d year sample period\n\n", buffer, samplePeriod);
  sprintf(table[1], "INTERVALS |   MIN. T\t|   MAX. T\t|   MED. T\n");

  aux = filtCountriesHead;
  for (int i = 0; i < lines; i++){

    while (aux != NULL && aux->data.year < targetYear){
      if (strstr(aux->data.name, buffer) != NULL){
        if (aux->data.temp < minTemp)
          minTemp = aux->data.temp;
        if (aux->data.temp > maxTemp)
          maxTemp = aux->data.temp;

        carryAdder += aux->data.temp;
        counter++;
      }
      aux = aux->next;
    }

    medTemp = (float)carryAdder / (float)counter;
    carryAdder = 0.0f;
    counter = 0;

    if (targetYear > info.maxYear)
      targetYear = info.maxYear;

    if (maxTemp != -3000.0f && minTemp != 3000.0f)
      sprintf(table[i+2], "%d-%d |   %.2f\t|   %.2f\t|   %.2f\n", (targetYear - samplePeriod), targetYear, maxTemp, minTemp, medTemp);

    minTemp = 3000.0f;
    maxTemp = -3000.f;
    medTemp = 0.0f;

    targetYear += samplePeriod;

  }

  getchar();
  //free(table);


}

void tempHistoryCity(node_t* filtCitiesHead, int samplePeriod){

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
