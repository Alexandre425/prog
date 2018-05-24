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

extern float minPointTemp;
extern float maxPointTemp;

int numberOfCities;

ListInfo getFileInfo(FILE* file){

  ListInfo info;
  char buffer[BUFFER_SIZE] = {0};
  int year = 0;

  info.minYear = 3000;
  info.maxYear = 0;

  while (fgets(buffer, BUFFER_SIZE, file) != NULL){
    sscanf(buffer, "%d", &year);
    if (year < info.minYear && year > 1000)
      info.minYear = year;
    if (year > info.maxYear && year > 1000)
      info.maxYear = year;
  }
  //year > 1000 was done to avoid some apparently wrong data in the file

  info.range = info.maxYear - info.minYear;

  rewind(file);

  return info;
}

ListInfo getListInfo(node_t* head){

  ListInfo info;
  node_t* aux = head;

  info.minYear = 3000;
  info.maxYear = 0;

  while (aux != NULL){
    if (aux->data.year < info.minYear)
      info.minYear = aux->data.year;
    if (aux->data.year > info.maxYear)
      info.maxYear = aux->data.year;

    aux = aux->next;
  }

  info.range = info.maxYear - info.minYear;

  return info;
}

node_t** allocateAuxArray(int range){

  node_t** array = NULL;
  array = (node_t**)malloc(sizeof(node_t*) * (range + 1));
  if (array == NULL){
    printf("Memory allocation error!\n");
    exit (EXIT_FAILURE);
  }

  return array;
}

node_t** createGraphicalAuxArray(node_t* head){

  node_t** auxArray = NULL;
  node_t* aux = NULL;
  int counter = 1;
  int index = 0;

  aux = head;
  while (aux->next != NULL){
    if (strcmp(aux->data.name, aux->next->data.name) != 0)
      counter++;
    aux = aux->next;
  }

  numberOfCities = counter;

  auxArray = (node_t**)calloc(counter, sizeof(node_t*));
  if (auxArray == NULL){
    printf("Memory allocation error!\n");
    exit (EXIT_FAILURE);
  }

  auxArray[index] = head;
  index++;

  aux = head;
  while (aux->next != NULL){
    if (strcmp(aux->data.name, aux->next->data.name) != 0){
      auxArray[index] = aux->next;
      index++;
    }
    aux = aux->next;
  }

  return auxArray;

}

void createSortedLists(FILE* countriesFile, node_t** countriesHead, node_t** countriesYearArray,
  FILE* citiesFile, node_t** citiesHead, node_t** citiesYearArray){

  node_t* newNode;
  char buffer[BUFFER_SIZE] = {0};
  char countryName[BUFFER_SIZE] = {0};
  float deviation = 0.0f;
  //buffer to pull data from the file
  temp data;
  temp cmp = {0, 0, 1000.0f, "\0"};
  data2 pos = {0.0f, 0, 0.0f, 0};

  system("clear");
  printf("Loading files, please wait...\n");

  //creating the country list
  while (fgets(buffer, BUFFER_SIZE, countriesFile) != NULL){
    //resetting the buffer
    memcpy(&data, &cmp, sizeof(temp));
    sscanf(buffer, "%d-%d-01,%f,%f,%[^\r]", &data.year, &data.month, &data.temp,
      &deviation, data.name);
    //if the data pulled from the file has a temperature
    //(done to prevent creating a new node with no data)
    if (data.temp != 1000.0f){
      newNode = getNewNode(data, pos);
      *countriesHead = sortedInsert(*countriesHead, countriesYearArray, newNode);
    }
  }
  rewind(countriesFile);

  //creating the city list
  while (fgets(buffer, BUFFER_SIZE, citiesFile) != NULL){
    memcpy(&data, &cmp, sizeof(temp));
    sscanf(buffer, "%d-%d-01,%f,%f,%[^,],%[^,],%f%c,%f%c", &data.year, &data.month,
      &data.temp, &deviation, data.name, countryName, &pos.lat, &pos.cLat,
      &pos.lon, &pos.cLon);

    if (data.temp != 1000.0f){
      newNode = getNewNode(data, pos);
      *citiesHead = sortedInsert(*citiesHead, citiesYearArray, newNode);
    }
  }
  rewind(citiesFile);

}

node_t* loadCityList(FILE* citiesFile){

  node_t* newNode = NULL;
  node_t* aux = NULL;
  node_t* citiesHead = NULL;
  float deviation = 0.0f;
  temp data;
  temp cmp = {0, 0, 1000.0f, "\0"};
  data2 pos = {0.0f, 0, 0.0f, 0};

  char buffer[BUFFER_SIZE] = {0};
  char countryName[BUFFER_SIZE] = {0};

  system("clear");
  printf("Loading files, please wait...\n");

  while (fgets(buffer, BUFFER_SIZE, citiesFile) != NULL){
    memcpy(&data, &cmp, sizeof(temp));
    sscanf(buffer, "%d-%d-01,%f,%f,%[^,],%[^,],%f%c,%f%c", &data.year, &data.month,
      &data.temp, &deviation, data.name, countryName, &pos.lat, &pos.cLat,
      &pos.lon, &pos.cLon);

    if (data.temp != 1000.0f){
      newNode = getNewNode(data, pos);
      if (aux == NULL){
        aux = newNode;
        citiesHead = newNode;
      }
      else{
        aux->next = newNode;
        aux = aux->next;
      }
    }
  }
  rewind(citiesFile);

  return citiesHead;
}

node_t* createMedianTempCityList(node_t* citiesHead){

  node_t* aux = NULL;
  node_t* medianListHead = NULL;
  node_t* aux2 = NULL;
  node_t* newNode = NULL;

  int year = 0;

  float carryAdder = 0.0f;
  int counter = 0;
  float medianTemp = 0.0f;

  temp data = {0, 0, 0.0f, ""};
  data2 pos;

  for (year = minYear; year <= maxYear; year++){

    aux = citiesHead;
    while (aux != NULL){
      //found data on the year we are currently doing the median on
      if (aux->data.year == year){
        //copying the city's coordinates to later draw it
        pos.lat = aux->pos.lat;
        pos.lon = aux->pos.lon;
        pos.cLat = aux->pos.cLat;
        pos.cLon = aux->pos.cLon;
        data.year = year;

        //calculating the average temperature for a city in that year
        carryAdder = 0.0f;
        counter = 0;
        while (aux->data.year == year){
          carryAdder += aux->data.temp;
          counter++;
          aux = aux->next;
          if (aux == NULL)
            break;
        }
        medianTemp = ((float)carryAdder / (float)counter);
        data.temp = medianTemp;
        //getting a new node with the temperature, coordinates and year
        newNode = getNewNode(data, pos);
        //inserting the node
        if (medianListHead == NULL){
          medianListHead = newNode;
          aux2 = medianListHead;
        }
        else{
          aux2->next = newNode;
          aux2 = aux2->next;
        }
      }
      if (aux != NULL)
        aux = aux->next;
    }
  }

  return medianListHead;
}

void getMinMaxTemp(node_t* pointsHead){

  node_t* aux = NULL;

  minPointTemp = 1000.0f;
  maxPointTemp = -1000.0f;

  aux = pointsHead;
  while (aux != NULL){
    if (aux->data.temp < minPointTemp)
      minPointTemp = aux->data.temp;
    if (aux->data.temp > maxPointTemp)
      maxPointTemp = aux->data.temp;
    aux = aux->next;
  }
}

node_t* freeSortedList(node_t* head){

  node_t* aux = head;

  printf("Freeing list...\n");

  while (aux != NULL){
    aux = aux->next;
    free(head->data.name);
    free(head);
    head = aux;
  }

  //head will always be NULL
  return head;
}

node_t* getNewNode(temp data, data2 pos){

  node_t* newNode = NULL;
  newNode = (node_t*)malloc(sizeof(node_t));
  if (newNode == NULL){
    printf("Memory allocation error!\n");
    exit (EXIT_FAILURE);
  }

  newNode->data.year = data.year;
  newNode->data.month = data.month;
  newNode->data.temp = data.temp;
  newNode->pos = pos;
  newNode->data.name = (char*)malloc( (strlen(data.name) + 1) * sizeof(char) );
  strcpy(newNode->data.name, data.name);
  newNode->next = NULL;

  return newNode;
}

node_t* sortedInsert(node_t* head, node_t** ptrArray, node_t* newNode){

  int index = 0;
  node_t* aux = NULL;

  index = findIndex(newNode->data);

  //if there is no head
  if (head == NULL){
    ptrArray[index] = newNode;
    return newNode;
  }

  //if the new node should be before the list head
  if (newNode->data.year <= head->data.year){
    //if the year of the new node is inferior
    //or the year is equal and the month is equal or inferior
    if (newNode->data.year < head->data.year ||
      (newNode->data.year == head->data.year && newNode->data.month <= head->data.month)){

      newNode->next = head;
      ptrArray[index] = newNode;
      return newNode;
    }
  }

  //if the year in question already has a pointer set up, the year pointer is recalled
  if (ptrArray[index] != NULL)
    aux = ptrArray[index];
  //if there is no pointer, the year pointer is set and we find the closest one to begin
  //going through the list from
  else{
    aux = head;
    for (int i = index; i >= 0; i--)
      if (ptrArray[i] != NULL){
        aux = ptrArray[i];
        break;
      }
    ptrArray[index] = newNode;
  }

  //going through the list until we find an element with the same or a
  //latter date, or we reach the end of the list
  while (aux->next != NULL){
    if ((newNode->data.year == aux->next->data.year && newNode->data.month <= aux->next->data.month) ||
      newNode->data.year < aux->next->data.year)
      break;
    aux = aux->next;
  }

  //if the new node is being inserted at the end of the list
  if (aux->next == NULL){
    aux->next = newNode;
    //the year pointer is set if it has not been yet
    if (ptrArray[index] == NULL)
      ptrArray[index] = newNode;
    return head;
  }
  //if it is being inserted in the middle
  else{
    newNode->next = aux->next;
    aux->next = newNode;
    //if the previous year pointer needs to be substituted, or there is none
    if (ptrArray[index] == aux->next || ptrArray[index] == NULL)
      ptrArray[index] = newNode;
    return head;
  }

}

void deleteNode(node_t* aux){

  node_t* tmp = NULL;

  if (aux == NULL || aux->next == NULL)
    return;

  tmp = aux->next->next;
  free(aux->next->data.name);
  free(aux->next);
  aux->next = tmp;
}

node_t* deleteHead(node_t* head){

  node_t* newHead = NULL;

  if (head == NULL)
    return NULL;

  newHead = head->next;
  free(head->data.name);
  free(head);

  return newHead;
}

int findIndex(data1 data ){
  int index = 0;
  index = data.year - minYear;
  return index;
}

top_t* yearlyTemp_getNewNode(top_t data){

  top_t* newNode = NULL;
  newNode = (top_t*)malloc(sizeof(top_t));
  if (newNode == NULL){
    printf("Memory allocation error!\n");
    exit (EXIT_FAILURE);
  }

  strcpy(newNode->name, data.name);
  newNode->temp = data.temp;
  newNode->range = data.range;
  newNode->next = NULL;

  return newNode;
}

top_t* yearlyTemp_sortedInsertTemp(top_t* head, top_t* newNode){

  top_t* aux = NULL;

  //if there is no head
  if (head == NULL){
    return newNode;
  }

  //if the new node has a higher temperature (if it belongs before the list head)
  if (newNode->temp > head->temp){
    newNode->next = head;
    return newNode;
  }

  //traversing the list until aux->next has a lower temperature
  aux = head;
  while (aux->next != NULL){
    if (newNode->temp > aux->next->temp)
      break;
    aux = aux->next;
  }

  //if we are inserting at the end of the list
  if (aux->next == NULL){
    aux->next = newNode;
    return head;
  }

  //if we are inserting in the middle of the list
  else{
    newNode->next = aux->next;
    aux->next = newNode;
    return head;
  }

}

top_t* yearlyTemp_sortedInsertRange(top_t* head, top_t* newNode){

  top_t* aux = NULL;

  //if there is no head
  if (head == NULL){
    return newNode;
  }

  //if the new node has a higher temperature range (if it belongs before the list head)
  if (newNode->range > head->range){
    newNode->next = head;
    return newNode;
  }

  //traversing the list until aux->next has a lower temperature
  aux = head;
  while (aux->next != NULL){
    if (newNode->range > aux->next->range)
      break;
    aux = aux->next;
  }

  //if we are inserting at the end of the list
  if (aux->next == NULL){
    aux->next = newNode;
    return head;
  }
  //if we are inserting in the middle of the list
  else{
    newNode->next = aux->next;
    aux->next = newNode;
    return head;
  }
}

top_t yearlyTemp_getInfoByName(node_t* sampleYearPointer, char* name){

  node_t* aux = sampleYearPointer;

  int sampleYear = sampleYearPointer->data.year;
  top_t data;

  float carryAdder = 0.0f;
  int counter = 0;
  float maxTemp = -1000.0f, minTemp = 1000.0f;

  while (aux->data.year == sampleYear && aux->next != NULL){
    if (strstr(aux->data.name, name) != NULL){
      carryAdder += aux->data.temp;
      counter++;

      if (aux->data.temp < minTemp)
        minTemp = aux->data.temp;
      if (aux->data.temp > maxTemp)
        maxTemp = aux->data.temp;
    }
    aux = aux->next;
  }

  strcpy(data.name, name);
  data.temp = ((float)carryAdder / (float)counter);
  data.range = maxTemp - minTemp;
  data.next = NULL;

  return data;
}

void yearlyTemp_createSortedLists(node_t* head, int sampleYear, top_t** tempHead, top_t** rangeHead){

  node_t* aux = NULL;
  node_t* sampleYearPointer = NULL;

  top_t* aux2 = NULL;
  top_t data;
  top_t* newNodeTemp = NULL;
  top_t* newNodeRange = NULL;

  //getting the pointer to the first occurrence of the year being sampled
  aux = head;
  while (aux != NULL){
    if (aux->data.year == sampleYear){
      sampleYearPointer = aux;
      break;
    }
    else
      aux = aux->next;
  }
  //if the sample year is not included in the list
  if (aux == NULL || aux->next == NULL){
    system("clear");
    printf("The selected sample year is not present in the filtered data!\n");
    sleep(3);
    *tempHead = NULL;
    *rangeHead = NULL;
    return;
  }

  aux = sampleYearPointer;
  while (aux->data.year == sampleYear && aux->next != NULL){
    //searching for the name of a main list entry in the top_t median temp. list (could be either list)
    //if we find it (which means we already have data on that specific country or city)
    aux2 = *tempHead;
    while (aux2 != NULL){
      if (strstr(aux2->name, aux->data.name) != NULL){
        break;
      }
      else
        aux2 = aux2->next;
    }
    //if we don't find it, we get the info on that country or city and insert it
    if (aux2 == NULL){
      data = yearlyTemp_getInfoByName(sampleYearPointer, aux->data.name);
      newNodeTemp = yearlyTemp_getNewNode(data);
      newNodeRange = yearlyTemp_getNewNode(data);
      *tempHead = yearlyTemp_sortedInsertTemp(*tempHead, newNodeTemp);
      *rangeHead = yearlyTemp_sortedInsertRange(*rangeHead, newNodeRange);
    }
    //after that, we move on to the next entry on the list
    aux = aux->next;
  }

}

top_t* yearlyTemp_freeSortedList(top_t* head){

  top_t* aux = head;
  while (aux != NULL){
    aux = aux->next;
    free(head);
    head = aux;
  }
  //head will always be NULL
  return head;
}
