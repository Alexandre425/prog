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

void mainMenu (node_t* countriesHead, node_t* citiesHead){

  //head pointers to the filtered lists
  node_t* filtCountriesHead = NULL;
  node_t* filtCitiesHead = NULL;

  char buffer[BUFFER_SIZE];
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

    fgets(buffer, BUFFER_SIZE, stdin);
    sscanf(buffer, "%c", &c);

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

  char buffer[BUFFER_SIZE];
  char c = 0;

  while(true) {

    system("clear");

    printf("Filter Data: \n");
    printf("\n1. By initial date\n");
    printf("2. By season\n");
    printf("3. Reset filters\n");
    printf("4. Return to main menu\n");

    fgets(buffer, BUFFER_SIZE, stdin);
    sscanf(buffer, "%c", &c);

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

  char buffer[BUFFER_SIZE];
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

    fgets(buffer, BUFFER_SIZE, stdin);
    sscanf(buffer, "%c", &c);

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

  char buffer[BUFFER_SIZE];
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

    fgets(buffer, BUFFER_SIZE, stdin);
    sscanf(buffer, "%c", &c);

    switch (c) {
      case '1':
        yearlyTempCountries (filtCountriesHead, sampleYear);
        break;
      case '2':
        yearlyTempCities(filtCitiesHead, sampleYear);
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

int getNumMonths (){
  int numMonths = 0;
  char buffer[BUFFER_SIZE] = {0};

  while (numMonths <= 1 || numMonths > 1000){
    buffer[0] = '\0';
    system("clear");
    printf("Insert the number of months for the Moving Average calculation: ");
    fgets(buffer, BUFFER_SIZE, stdin);
    sscanf(buffer, "%d", &numMonths);

    if (numMonths <= 1 || numMonths > 1000){
      printf("Inserted number is not valid!\n");
      sleep(2);
    }
  }

  return numMonths;
}

void globalTempMenu (node_t* filtCountriesHead, node_t* filtCitiesHead){

  char buffer[BUFFER_SIZE];
  char c = 0;
  int numMonths = 0;

  numMonths = getNumMonths ();

  while(true){

    system("clear");

    printf("Global Temperature Analisis:\n");
    printf("This section uses the Moving Average concept in order to eliminate temperature data fluctuations and calculate global climate change\n");
    printf("Select one of the following options to analise the temperature change:\n");
    printf("1. Globally\n");
    printf("2. By a country\n");
    printf("3. By a city\n");
    printf("4. Change the number of months selected\n");
    printf("5. Return to main menu\n");

    fgets(buffer, BUFFER_SIZE, stdin);
    sscanf(buffer, "%c", &c);

    switch (c) {
      case '1':
        globalTempGlobal (filtCountriesHead, numMonths);
        break;
      case '2':
        globalTempCountry (filtCountriesHead, numMonths);
        break;
      case '3':
        globalTempCity (filtCitiesHead, numMonths);
        break;
      case '4':
        numMonths = getNumMonths ();
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

  //runs through the filtered list
  while ((*filtCountriesHead)->next != NULL){
    //if next entry is the first we want to keep
    if ((*filtCountriesHead)->next->data.year == year && (*filtCountriesHead)->next->data.month == month){
      //in that case, we sever the list
      auxCountries = *filtCountriesHead;
      //the new head, the second part of the list
      *filtCountriesHead = (*filtCountriesHead)->next;
      auxCountries->next = NULL;
      //this deletes the first part of the list, and keeps the second
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

  while (aux != NULL){
    if (aux->next == NULL)
      break;
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

  //deletes the input season on both lists
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

  //frees the filtered lists
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

    //moves once through the main list
    aux1 = aux1->next;
    //copies the data
    data.year = aux1->data.year;
    data.month = aux1->data.month;
    data.temp = aux1->data.temp;
    pos = aux1->pos;
    strcpy(data.name, aux1->data.name);
    //allocates a new node with the copied data
    newNode = getNewNode(data, pos);

    //inserting the new node after the last (in the copied list)
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

void printTempHistory(hist* histData, char header[HEADER_SIZE], int lines){

  int page = 0;
  int maxPage = 0;
  int firstEntry = 0;
  int target = PAGE_SIZE;
  char buffer[BUFFER_SIZE] = {0};
  char c = 0;

  maxPage = lines / PAGE_SIZE;
  if ((lines % PAGE_SIZE) != 0)
    maxPage++;

  for (page = 0; page < maxPage; page++){
    system("clear");
    //printing the header
    printf("%s", header);

    //if the target excedes the number of entries (the end of the page)
    if (target > lines)
      target = lines;

    for (int i = firstEntry; i < target; i++){
      //detecting unfilled array indexes, and not printing them
      if (histData[i].iniYear != 0)
        printf("%d-%d |   %.2f\t|   %.2f\t|   %.2f\n", histData[i].iniYear, histData[i].finYear, histData[i].minTemp, histData[i].maxTemp, histData[i].medTemp);
    }

    firstEntry += (PAGE_SIZE);
    target += (PAGE_SIZE);

    printf("\nPress 'a' to go to the next page\n");
    printf("Press 'q' to return to the Temperature History Menu\n");

    c = 0;

    while (c != 'a' && c != 'q'){
      fgets(buffer, BUFFER_SIZE, stdin);
      sscanf(buffer, "%c", &c);

      switch (c) {
        case 'a':
          //goes to the next page
          break;
        case 'q':
          //returns to tempHistoryMenu (after going through the intermediate function)
          return;
          break;
        default:
          //repeats the 'while' loop
          break;
      }
    }
  }
}

void tempHistoryGlobal(node_t* filtCountriesHead, int samplePeriod){

  node_t* aux = NULL;
  char header[HEADER_SIZE] = {0};

  //getting the year range on the filtered list
  ListInfo info = getListInfo(filtCountriesHead);

  //determining the size of the array to be allocated (how many entries it will have)
  int lines = getAllocSize(info.range, samplePeriod);
  //array with all the information to be printed
  hist* histData = NULL;

  float maxTemp = -3000.0f, minTemp = 3000.0f, medTemp = 0.0f;
  float carryAdder = 0.0f;
  int counter = 0;

  int targetYear = info.minYear + samplePeriod;

  histData = (hist*)malloc(sizeof(hist) * lines);
  if (histData == NULL){
    printf("Memory allocation error!\n");
    exit(EXIT_FAILURE);
  }

  sprintf(header, "Global Temperature History - %d year sample period\n\nINTERVALS |   MIN. T\t|   MAX. T\t|   MED. T\n", samplePeriod);

  //for to fill in all the lines
  aux = filtCountriesHead;
  for (int i = 0; i < lines; i++){
    //this while will do the average from the current year to the target year
    while (aux != NULL && aux->data.year < targetYear){
      //determining the new maximum and/or minimum
      if (aux->data.temp < minTemp)
        minTemp = aux->data.temp;
      if (aux->data.temp > maxTemp)
        maxTemp = aux->data.temp;

      carryAdder += aux->data.temp;
      counter++;
      aux = aux->next;
    }
    //calculating the median temperature for the current year bracket
    medTemp = (float)carryAdder / (float)counter;
    carryAdder = 0.0f;
    counter = 0;

    //if the target year surpasses the last year on the file/filtered list
    if (targetYear > info.maxYear)
      targetYear = info.maxYear;

    //if the period has valid data (some year brackets have no data)
    histData[i].iniYear = 0;
    if (maxTemp != -3000.0f && minTemp != 3000.0f){
      //writting the data on the array which will later be printed
      histData[i].iniYear = (targetYear - samplePeriod);
      histData[i].finYear = targetYear;
      histData[i].maxTemp = maxTemp;
      histData[i].minTemp = minTemp;
      histData[i].medTemp = medTemp;
    }
    //resetting to the ddefault minimum and maximum
    minTemp = 3000.0f;
    maxTemp = -3000.f;
    medTemp = 0.0f;

    //getting the next target year
    targetYear += samplePeriod;
  }

  //printing the gathered data
  printTempHistory(histData, header, lines);
  //freeing the used array
  free(histData);
}

void tempHistoryCountry(node_t* filtCountriesHead, int samplePeriod){

  ListInfo info;
  info = getListInfo(filtCountriesHead);

  int lines = getAllocSize(info.range, samplePeriod);
  int targetYear = info.minYear + samplePeriod;

  float maxTemp = -3000.0f, minTemp = 3000.0f, medTemp = 0.0f;
  float carryAdder = 0.0f;
  int counter = 0;

  node_t* aux = NULL;
  //array with all the information to be printed
  hist* histData = NULL;
  char header[HEADER_SIZE] = {0};

  char buffer[BUFFER_SIZE] = {0};
  int foundName = 0;

  printf("Insert the name of a country to get it's temperature history\nNote: The name is case-sensitive!\nCountry: ");
  fgets(buffer, BUFFER_SIZE, stdin);
  strtok(buffer, "\n");

  //finding the name on the list
  aux = filtCountriesHead;
  while (aux != NULL){
    if (strstr(aux->data.name, buffer) != NULL){
      strcpy(buffer, aux->data.name);
      foundName = 1;
      break;
    }
    else
      aux = aux->next;
  }

  if (foundName == 0){
    printf("Could not find a country named %s\n", buffer);
    sleep(3);
    return;
  }

  //only need to allocate the array to be printed if we found the name
  histData = (hist*)calloc(lines, sizeof(hist));
  if (histData == NULL){
    printf("Memory allocation error!\n");
    exit(EXIT_FAILURE);
  }

  sprintf(header, "Temperature history for %s - %d year sample period\n\nINTERVALS |   MIN. T\t|   MAX. T\t|   MED. T\n", buffer, samplePeriod);

  //note: most of this code is simmilar to the one on the function above
  aux = filtCountriesHead;
  for (int i = 0; i < lines; i++){

    while (aux != NULL && aux->data.year < targetYear){
      //checking to see if the data corresponds to the searched country
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

    if (maxTemp != -3000.0f && minTemp != 3000.0f){
      histData[i].iniYear = (targetYear - samplePeriod);
      histData[i].finYear = targetYear;
      histData[i].maxTemp = maxTemp;
      histData[i].minTemp = minTemp;
      histData[i].medTemp = medTemp;
    }

    minTemp = 3000.0f;
    maxTemp = -3000.f;
    medTemp = 0.0f;

    targetYear += samplePeriod;

  }

  printTempHistory(histData, header, lines);

  free(histData);

}

void tempHistoryCity(node_t* filtCitiesHead, int samplePeriod){

  ListInfo info;
  info = getListInfo(filtCitiesHead);

  int lines = getAllocSize(info.range, samplePeriod);
  int targetYear = info.minYear + samplePeriod;

  float maxTemp = -3000.0f, minTemp = 3000.0f, medTemp = 0.0f;
  float carryAdder = 0.0f;
  int counter = 0;

  node_t* aux = NULL;
  //array with all the information to be printed
  hist* histData = NULL;
  char header[HEADER_SIZE] = {0};

  char buffer[BUFFER_SIZE] = {0};
  int foundName = 0;

  printf("Insert the name of a city to get it's temperature history\nNote: The name is case-sensitive!\nCity: ");
  fgets(buffer, BUFFER_SIZE, stdin);
  strtok(buffer, "\n");

  //finding the name on the list
  aux = filtCitiesHead;
  while (aux != NULL){
    if (strstr(aux->data.name, buffer) != NULL){
      strcpy(buffer, aux->data.name);
      foundName = 1;
      break;
    }
    else
      aux = aux->next;
  }

  if (foundName == 0){
    printf("Could not find a city named %s\n", buffer);
    sleep(3);
    return;
  }

  //only need to allocate the array to be printed if we found the name
  histData = (hist*)calloc(lines, sizeof(hist));
  if (histData == NULL){
    printf("Memory allocation error!\n");
    exit(EXIT_FAILURE);
  }

  sprintf(header, "Temperature history for %s - %d year sample period\n\nINTERVALS |   MIN. T\t|   MAX. T\t|   MED. T\n", buffer, samplePeriod);

  //this code is almost the same as the one on the function above, read it for the commented code
  aux = filtCitiesHead;
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

    if (maxTemp != -3000.0f && minTemp != 3000.0f){
      histData[i].iniYear = (targetYear - samplePeriod);
      histData[i].finYear = targetYear;
      histData[i].maxTemp = maxTemp;
      histData[i].minTemp = minTemp;
      histData[i].medTemp = medTemp;
    }

    minTemp = 3000.0f;
    maxTemp = -3000.f;
    medTemp = 0.0f;

    targetYear += samplePeriod;

  }

  printTempHistory(histData, header, lines);

  free(histData);


}

//######################################################

int getNumberOfEntries(){

  int numberOfEntries = 0;
  char buffer[BUFFER_SIZE] = {0};


  while (numberOfEntries <= 0 || numberOfEntries > 20){
    buffer[0] = '\0';
    system("clear");
    printf("Insert the number of entries (1-20) to be shown on the list: ");
    fgets(buffer, BUFFER_SIZE, stdin);
    sscanf(buffer, "%d", &numberOfEntries);

    if (numberOfEntries <= 0 || numberOfEntries > 20){
      printf("Inserted number is not within the limits!\n");
      sleep(2);
    }
  }

  return numberOfEntries;
}

char** allocateStringArray(int numberOfEntries){

  char** stringArray = NULL;

  //allocates an array of pointers to strings
  stringArray = (char**)malloc(sizeof(char*) * numberOfEntries);
  if (stringArray == NULL){
    printf("Memory allocation error!\n");
    exit(-1);
  }

  //allocates space for each of the strings
  for (int i = 0; i < numberOfEntries; i++){
    stringArray[i] = NULL;
    stringArray[i] = (char*)malloc(sizeof(char) * BUFFER_SIZE);
    if (stringArray[i] == NULL){
      printf("Memory allocation error!\n");
      exit(-1);
    }
  }

  return stringArray;
}

void freeStringArray(char** stringArray, int numberOfEntries){

  //frees each of the strings
  for (int i = 0; i < numberOfEntries; i++)
    free(stringArray[i]);

  //frees the array of pointers
  free(stringArray);
}

void printYearlyTemp(top_t* tempHead, top_t* rangeHead, int numberOfEntries, int type){

  char buffer[BUFFER_SIZE];
  char header[HEADER_SIZE] = {0};
  char** maxTempStrings = allocateStringArray(numberOfEntries);
  char** minTempStrings = allocateStringArray(numberOfEntries);
  char** rangeStrings = allocateStringArray(numberOfEntries);

  top_t* maxTempPointer = NULL;
  top_t* minTempPointer = NULL;
    top_t* aux = NULL;
    int counter = 0;
  top_t* rangePointer = NULL;

  system("clear");

  if (type == COUNTRY)
    sprintf(header, "Top-%d countries:\n\n\t| Hottest\t\t\t\t\t\t| Coldest\t\t\t\t\t\t| Most Extreme\n", numberOfEntries);
  if (type == CITY)
    sprintf(header, "Top-%d cities:\n\n\t| Hottest\t\t\t\t\t\t| Coldest\t\t\t\t\t\t| Most Extreme\n", numberOfEntries);

  maxTempPointer = tempHead;
  rangePointer = rangeHead;
  //setting up the pointer to the minimum temperature entries
  //ex: if the number of entries is 3, the minTempPointer points to the 3rd to last entry of the list
  minTempPointer = tempHead;
  aux = tempHead;
  while (aux->next != NULL){
    aux = aux->next;
    counter++;
    if (counter >= numberOfEntries)
      minTempPointer = minTempPointer->next;
  }

  //filling the string array with
  for (int i = 0; i < numberOfEntries; i++){
    sprintf(maxTempStrings[i], "%s", maxTempPointer->name);
    //the minimum temperature top-x is filled from the bottom up, process
    //described in the 'define.h' file
    sprintf(minTempStrings[numberOfEntries - 1 - i], "%s", minTempPointer->name);
    sprintf(rangeStrings[i], "%s", rangePointer->name);
    maxTempPointer = maxTempPointer->next;
    minTempPointer = minTempPointer->next;
    rangePointer = rangePointer->next;
  }

  //printing everything
  printf("%s\n", header);
  for (int i = 0; i < numberOfEntries; i++){
    printf("%d.\t", i + 1);

    printf("%s", maxTempStrings[i]);
    //printing spaces to place the '|' separators on the correct place
    //this depends on the length of the printed string
    for (int j = 0; j < 56 - strlen(maxTempStrings[i]); j++)
      printf(" ");
    printf("%s", minTempStrings[numberOfEntries - 1 - i]);
    for (int j = 0; j < 56 - strlen(minTempStrings[numberOfEntries - 1 - i]); j++)
      printf(" ");
    printf("%s\n", rangeStrings[i]);

  }

  //freeing the string arrays
  freeStringArray(maxTempStrings, numberOfEntries);
  freeStringArray(minTempStrings, numberOfEntries);
  freeStringArray(rangeStrings, numberOfEntries);

  printf("\nPress any key to return to the Yearly Temperature Menu\n");
  fgets(buffer, BUFFER_SIZE, stdin);
}

void yearlyTempCountries(node_t* filtCountriesHead, int sampleYear){

  int numberOfEntries = getNumberOfEntries();
  //has the countries sorted by their medium temperature
  top_t* tempHead = NULL;
  //has the countries sorted by their temperature range
  top_t* rangeHead = NULL;

  //creating the median temperature and temperature range lists, sends the country lists
  yearlyTemp_createSortedLists(filtCountriesHead, sampleYear, &tempHead, &rangeHead);

  //if nothing was returned, i.e. the input year was out of the data filter
  if (tempHead == NULL || rangeHead == NULL){
    return;
  }

  //sending the lists to the printing function
  printYearlyTemp(tempHead, rangeHead, numberOfEntries, COUNTRY);

  //freeing the lists
  tempHead = yearlyTemp_freeSortedList(tempHead);
  rangeHead = yearlyTemp_freeSortedList(rangeHead);

}

void yearlyTempCities(node_t* filtCitiesHead, int sampleYear){

  int numberOfEntries = getNumberOfEntries();
  //has the countries sorted by their medium temperature
  top_t* tempHead = NULL;
  //has the countries sorted by their temperature range
  top_t* rangeHead = NULL;

  //same as the above function, but sends the city list instead
  yearlyTemp_createSortedLists(filtCitiesHead, sampleYear, &tempHead, &rangeHead);

  printYearlyTemp(tempHead, rangeHead, numberOfEntries, CITY);

  tempHead = yearlyTemp_freeSortedList(tempHead);
  rangeHead = yearlyTemp_freeSortedList(rangeHead);

}

//######################################################

void printGlobalTemp(float tempChangeArray[5],  char header[HEADER_SIZE]){

  char buffer[BUFFER_SIZE];
  //the years where the temperature change is calculated
  int tempChangeYears[5] = {2013, 1990, 1960, 1910, 1860};

  system("clear");

  printf("%s", header);

  //printing the calculated temperature change
  for (int i = 0; i < 5; i++){
    if (tempChangeArray[i] != 0.0f)
      printf(" %d  | %.2f\n", tempChangeYears[i], tempChangeArray[i]);
  }

  printf("\nPress any key to return to the Global Temperature Analisis Menu\n");
  fgets(buffer, BUFFER_SIZE, stdin);
}

median* getMedianTempByMonth(node_t* head, int* lastIndex){

  int counter = 1;
  node_t* aux = NULL;
  median* medianArray = NULL;

  float carryAdder = 0.0f;
  int index = 0;

  //getting the allocation size
  aux = head;
  while (aux->next != NULL){
    //detecting a change in date, meaning we must allocate for one more month
    if (aux->data.year != aux->next->data.year || aux->data.month != aux->next->data.month)
      counter++;
    aux = aux->next;
  }

  *lastIndex = counter;

  //allocating the array (one entry for each different date in the data)
  medianArray = (median*)malloc(sizeof(median) * counter);
  if (medianArray == NULL){
    printf("Memory alocation error!\n");
    exit(EXIT_FAILURE);
  }

  aux = head;
  counter = 0;
  //getting the median temperature for each month
  while (aux->next != NULL){
    carryAdder += aux->data.temp;
    counter++;
    //if a month change is detected, processes the data which had been stored until now
    //and stores it. Resets the carry adder for it to gather data on the next month
    if (aux->data.year != aux->next->data.year || aux->data.month != aux->next->data.month){
      medianArray[index].year = aux->data.year;
      medianArray[index].month = aux->data.month;
      medianArray[index].temp = ((float)carryAdder / (float)counter);
      carryAdder = 0.0f;
      counter = 0;
      index++;
    }
    aux = aux->next;
  }

  return medianArray;
}

median* getMedianTempByName(node_t* head, int* lastIndex, char name[BUFFER_SIZE]){

  int counter = 0;
  node_t* aux = NULL;
  median* medianArray = NULL;

  int index = 0;

  //getting the allocation size
  aux = head;
  while (aux != NULL){
    //if we find an entry with the name we are looking for, adding an entry to the array
    if (strstr(aux->data.name, name) != NULL);
      counter++;
    aux = aux->next;
  }

  *lastIndex = counter;

  //allocating the array (one entry for each different entry for a name in the data)
  medianArray = (median*)malloc(sizeof(median) * counter);
  if (medianArray == NULL){
    printf("Memory alocation error!\n");
    exit(EXIT_FAILURE);
  }

  aux = head;
  counter = 0;
  //traversing the list
  while (aux != NULL){
    //storing the data if we find the name we are looking for
    if (strstr(aux->data.name, name) != NULL){
      medianArray[index].year = aux->data.year;
      medianArray[index].month = aux->data.month;
      medianArray[index].temp = aux->data.temp;
      index++;
    }
    aux = aux->next;
  }

  return medianArray;
}

float* getMovingAverage(median* medianTempByMonth, int numMonths, int lastIndex){

  int startIndex = 0;
  int targetIndex = 0;
  int aux = 0;

  float carryAdder = 0.0f;
  int counter = 0;

  float movingAverage = 0.0f;
  float minTemp = 1000.0f;
  float maxTemp = -1000.0f;
  int minTempYear = 0;
  int maxTempYear = 0;
  float tempChange = 0.0f;

  int tempChangeYears[5] = {2013, 1990, 1960, 1910, 1860};
  //allocating memory for the array which store the temperature change in the specific years
  float* tempChangeArray = (float*)calloc(5, sizeof(float));
  if (tempChangeArray == NULL){
    printf("Memory allocation error!\n");
    exit (EXIT_FAILURE);
  }

  //determining the initial target index
  targetIndex = startIndex + numMonths - 1;
  while (targetIndex < lastIndex){

    carryAdder = 0.0f;
    counter = 0;
    aux = startIndex;
    //adding up the values from the start index to the target index
    while (aux < targetIndex){
      carryAdder += medianTempByMonth[aux].temp;
      counter++;
      aux++;
    }
    //calculating the moving average
    movingAverage = ((float)carryAdder / (float)counter);

    //determining if the calculated average is a minimum or maximum
    if (movingAverage < minTemp){
      minTemp = movingAverage;
      minTempYear = medianTempByMonth[targetIndex].year;
    }
    if (movingAverage > maxTemp){
      maxTemp = movingAverage;
      maxTempYear = medianTempByMonth[targetIndex].year;
    }

    tempChange = maxTemp - minTemp;

    //saving the temperature change (max - min) for the specific years
    for (int i = 0; i < 5; i++){
      if (medianTempByMonth[targetIndex].year == tempChangeYears[i]){
        tempChange = maxTemp - minTemp;
        if (maxTempYear < minTempYear)
          tempChange *= -1.0f;
        tempChangeArray[i] = tempChange;
      }
    }

    startIndex++;
    targetIndex++;
  }

  return tempChangeArray;
}

void globalTempGlobal(node_t* filtCountriesHead, int numMonths){

  int lastIndex = 0;
  median* medianTempByMonth = getMedianTempByMonth(filtCountriesHead, &lastIndex);
  float* tempChangeArray = getMovingAverage(medianTempByMonth, numMonths, lastIndex);

  char header[HEADER_SIZE] = {0};
  sprintf(header, "Global Temperature Analisis\n\n Until | Temperature change\n");

  printGlobalTemp(tempChangeArray, header);

  free(medianTempByMonth);
  free(tempChangeArray);

}

void globalTempCountry(node_t* filtCountriesHead, int numMonths){

  int lastIndex = 0;
  node_t* aux = NULL;

  char buffer[BUFFER_SIZE] = {0};
  int foundName = 0;

  system("clear");
  printf("Insert the name of a country to get it's temperature change\nNote: The name is case-sensitive!\nCountry: ");
  fgets(buffer, BUFFER_SIZE, stdin);
  strtok(buffer, "\n");

  //finding the name on the list
  aux = filtCountriesHead;
  while (aux != NULL){
    if (strstr(aux->data.name, buffer) != NULL){
      strcpy(buffer, aux->data.name);
      foundName = 1;
      break;
    }
    else
      aux = aux->next;
  }

  if (foundName == 0){
    printf("Could not find a country named %s\n", buffer);
    sleep(3);
    return;
  }

  //getting the median temperature vector with entries for each month
  median* medianTempByMonth = getMedianTempByName(filtCountriesHead, &lastIndex, buffer);
  //calculating the moving average of the medians
  float* tempChangeArray = getMovingAverage(medianTempByMonth, numMonths, lastIndex);

  char header[HEADER_SIZE] = {0};
  sprintf(header, "Global Temperature Analisis for %s\n\n Until | Temperature change\n", buffer);

  //printing the temperature change
  printGlobalTemp(tempChangeArray, header);

  //freeing the arrays with the median temperatures and temperature change
  free(medianTempByMonth);
  free(tempChangeArray);
}

void globalTempCity(node_t* filtCitiesHead, int numMonths){

  int lastIndex = 0;
  node_t* aux = NULL;

  char buffer[BUFFER_SIZE] = {0};
  int foundName = 0;

  system("clear");
  printf("Insert the name of a city to get it's temperature change\nNote: The name is case-sensitive!\nCity: ");
  fgets(buffer, BUFFER_SIZE, stdin);
  strtok(buffer, "\n");

  //finding the name on the list
  aux = filtCitiesHead;
  while (aux != NULL){
    if (strstr(aux->data.name, buffer) != NULL){
      strcpy(buffer, aux->data.name);
      foundName = 1;
      break;
    }
    else
      aux = aux->next;
  }

  if (foundName == 0){
    printf("Could not find a city named %s\n", buffer);
    sleep(3);
    return;
  }

  //same as the country function, with the other list
  median* medianTempByMonth = getMedianTempByName(filtCitiesHead, &lastIndex, buffer);
  float* tempChangeArray = getMovingAverage(medianTempByMonth, numMonths, lastIndex);

  char header[HEADER_SIZE] = {0};
  sprintf(header, "Global Temperature Analisis for %s\n\n Until | Temperature change\n", buffer);

  printGlobalTemp(tempChangeArray, header);

  free(medianTempByMonth);
  free(tempChangeArray);

}
