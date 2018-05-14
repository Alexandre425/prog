#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "struct.h"
#include "define.h"

ListInfo GetFileInfo(FILE* file){

  ListInfo info;
  char buffer[BUFFER_SIZE];
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

node_t* createSortedLists(FILE* countriesFile, node_t* countriesHead, node_t** countriesYearArray,
  FILE* citiesFile, node_t* citiesHead, node_t** citiesYearArray){

  return NULL;
}

node_t* getNewNode(data1 data, data2 pos){

  node_t* newNode = NULL;
  newNode = (node_t*)malloc(sizeof(node_t));
  if (newNode == NULL){
    printf("Memory allocation error!\n");
    exit (EXIT_FAILURE);
  }

  newNode->data = data;
  newNode->pos = pos;
  newNode->next = NULL;
  newNode->prev = NULL;

  return newNode;
}

node_t* textual_sortedInsert(node_t* head, node_t** ptrArray, node_t* newNode){

  int index = 0;
  node_t* aux = NULL;

  index = findIndex(newNode->data);

  //if there is no head
  if (head == NULL){
    ptrArray[index] = newNode;
    return newNode;
  }

  //if the new node should be before the list head
  if (newNode->data.year <= head->data.year)
    if (newNode->data.month <= head->data.month){
      newNode->next = head;
      head->prev = newNode;
      ptrArray[index] = newNode;
      return newNode;
    }

  //if the year in question already has a pointer set up, the year pointer is recalled
  if (ptrArray[index] != NULL)
    aux = ptrArray[index];
  //if there is no pointer, the year pointer is set and we find the closest one to begin
  //going through the list from
  else{
    for (int i = index; i >= 0; i--)
      if (ptrArray[i] != NULL){
        aux = ptrArray[i];
        break;
      }
    ptrArray[index] = newNode;
  }

  //going through the list until we find an element with the same or a
  //latter date, or we reach the end of the list
  while (aux->next != NULL && newNode->data.year >= aux->next->data.year){
    if (newNode->data.year == aux->next->data.year && newNode->data.month <= aux->next->data.month)
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

int findIndex(data1 data){
  int index = 0;
  index = data.year - minYear;
  return index;
}
