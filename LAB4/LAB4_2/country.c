#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_SIZE 150

typedef struct{
  char name[50];
  int population;
  float area;
  float popDensity;
} Country;

typedef struct list{
  Country country;
  struct list* next;
} CountryList;

Country* readFile(FILE* fp, int *size){

  Country* countries = NULL;
  int i = 0;
  char buffer[STRING_SIZE] = {0};

  while (fgets(buffer, STRING_SIZE, fp) != NULL)
    (*size)++;
  rewind(fp);

  countries = (Country*)malloc(*size * sizeof(Country));

  while (fgets(buffer, STRING_SIZE, fp) != NULL){
    sscanf(buffer, "%[^\t]\t%d\t%f", countries[i].name, &countries[i].population, &countries[i].area);
    countries[i].name[strlen(countries[i].name) + 1] = '\0';
    countries[i].popDensity = (countries[i].population) / (float)(countries[i].area);
    i++;
    buffer[0] = '\0';
  }

  return countries;
}

void searchCountry(Country* countries, int size){

  char name[50] = {0};
  int i = 0;

  printf("Insert a country name: ");
  fgets(name, STRING_SIZE, stdin);
  name[strlen(name)-1] = '\0';

  for (i = 0; i < size; i++)
    if (strstr(countries[i].name, name) != NULL){
      printf("\n---- %s ----\n", countries[i].name);
      printf("Population: %d people\n", countries[i].population);
      printf("Area: %.2f sq mi\n", countries[i].area);
      return;
    }

  printf("Could not find a country named %s!\n", name);
}

void maxPopDensity(Country* countries, int size){

  float max = 0.0f;
  char name[50] = {0};
  int i = 0;

  for(i = 0; i < size; i++)
    if (countries[i].popDensity > max){
      max = countries[i].popDensity;
      name[0] = '\0';
      strcpy(name, countries[i].name);
    }

  printf("The country with the highest population density is %s\n", name);
}

void orderList(Country* countries, int size, CountryList** popHead, CountryList** areaHead){

  int i = 0;
  CountryList *pAux = NULL, *aAux = NULL;
  CountryList* newNode = NULL;

  for (i = 0; i < size; i++){
    //allocating memmory for a new node
    newNode = (CountryList*)malloc(sizeof(CountryList));
    //copying a country to that node
    newNode->country = countries[i];

    //defining auxiliary pointers to cycle through list entries
    pAux = *popHead;
    aAux = *areaHead;

    //figuring out where the node will be inserted
    if (*popHead == NULL){
      *popHead = newNode;
      (*popHead)->next = NULL;
    }
    else{

    }

    if (*areaHead == NULL){
      *areaHead = newNode;
      (*areaHead)->next = NULL;
    }
    else{

    }


    while(pAux != NULL){

    }
  }
}

int main (void){

  FILE* fp = NULL;
  Country* countries = NULL;
  CountryList* popHead = NULL;
  CountryList* areaHead = NULL;
  int size = 0;

  fp = fopen("countries.txt", "r");
  if (fp == NULL){
    printf("Error while opening file!\n");
    return EXIT_FAILURE;
  }

  countries = readFile(fp, &size);
  maxPopDensity(countries, size);
  searchCountry(countries, size);
  orderList(countries, &popHead, &areaHead)

  free(countries);
  return EXIT_SUCCESS;
}
