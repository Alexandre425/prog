#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "struct.h"
#include "define.h"

extern int minYear;

ListInfo GetFileInfo(FILE* file){

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

node_t** allocateAuxArray(int range){

  node_t** array = NULL;
  array = (node_t**)malloc(sizeof(node_t*) * (range + 1));
  if (array == NULL){
    printf("Memory allocation error!\n");
    exit (EXIT_FAILURE);
  }

  return array;
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
  data2 pos = {0.0f, 0.0f};

  //creating the country list
  while (fgets(buffer, BUFFER_SIZE, countriesFile) != NULL){
    //resetting the buffer
    memcpy(&data, &cmp, sizeof(temp));
    sscanf(buffer, "%d-%d-01,%f,%f,%[^\n]", &data.year, &data.month, &data.temp,
      &deviation, data.name);
    //if the data pulled from the file has a temperature
    if (data.temp != 1000.0f){
      newNode = getNewNode(data, pos);
      *countriesHead = sortedInsert(*countriesHead, countriesYearArray, newNode);
    }
  }
  rewind(countriesFile);

  //creating the city list
  //ignoring the first line
  fgets(buffer, BUFFER_SIZE, citiesFile);
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

node_t* freeSortedList(node_t* head){

  //skipping first element, then freeing it
  head = head->next;
  free(head->prev);
  //freeing all elements in between
  while (head->next != NULL){
    head = head->next;
    free(head->prev);
  }
  //freeing the last element
  free(head);
  head = NULL;

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
  newNode->prev = NULL;

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
      head->prev = newNode;
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
    newNode->prev = aux;
    //the year pointer is set if it has not been yet
    if (ptrArray[index] == NULL)
      ptrArray[index] = newNode;
    return head;
  }
  //if it is being inserted in the middle
  else{
    newNode->next = aux->next;
    aux->next->prev = newNode;
    newNode->prev = aux;
    aux->next = newNode;
    //if the previous year pointer needs to be substituted, or there is none
    if (ptrArray[index] == aux->next || ptrArray[index] == NULL)
      ptrArray[index] = newNode;
    return head;
  }

}

int findIndex(data1 data ){
  int index = 0;
  index = data.year - minYear;
  return index;
}
