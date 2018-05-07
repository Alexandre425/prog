#include <stdio.h>
#include <stdlib.h>

#define STRING_SIZE 100

typedef struct FinishTime{
  int h;
  int m;
  int s;
} FinishTime;

typedef struct Runner{
  int globalPos;
  int echelonPos;
  int dorsalNum;
  char echelon[4];
  char name[STRING_SIZE];
  char gender;
  struct FinishTime finishTime;

} Runner;

void structAlloc(FILE*, Runner**, int*);
void readFile(FILE*, Runner*, int);
void firstPlaceByEchelon(Runner*, int);
void timeByNumber(Runner*, int, int);

int main (void){

  FILE* file = NULL;
  Runner* runners = NULL;
  int size = 0;
  char c = 0;
  int dorsalNum = 0;


  file = fopen("braga17.txt", "r");
  if (file == NULL){
    printf("Error when opening the file!\n");
    exit (EXIT_FAILURE);
  }

  //allocating enough memmory for all participants, and passing their information to said memmory
  structAlloc(file, &runners, &size);
  readFile(file, runners, size);

  firstPlaceByEchelon(runners, size);

  printf("Type 'q' to quit, or 'n' to enter a runner number and get their time\n");

  //infinite loop to get a number or to quit the program
  while(1){

    c = getchar();

    if (c == 'q')
      break;
    if (c == 'n'){
      printf("Insert the runner number: ");
      scanf("%d", &dorsalNum);
      timeByNumber(runners, size, dorsalNum);
    }

  }

  free(runners);

  return EXIT_SUCCESS;
}

//timeByNumber: prints the time a runner (identified by his/her number) took to finish the race
void timeByNumber(Runner* runners, int size, int dorsalNum){

  for ( ; size > 0; size--)
    if (dorsalNum == runners[size].dorsalNum){
      printf("Runner number %d finish time: %dh%dm%ds\n", dorsalNum, runners[size].finishTime.h, runners[size].finishTime.m, runners[size].finishTime.s);
      return;
    }

  printf("Could not find runner number %d!\n", dorsalNum);
}

//firstPlaceByEchelon: prints all the information about the runner in first place in each echelon
void firstPlaceByEchelon(Runner* runners, int size){

  for ( ; size > 0; size--)
    if (runners[size].echelonPos == 1){
      printf("----First place in %s----\n", runners[size].echelon);
      printf("Name: %s\n", runners[size].name);
      printf("Global pos.: %d\n", runners[size].globalPos);
      printf("Dorsal num.: %d\n", runners[size].dorsalNum);
      printf("Gender: %c\n", runners[size].gender);
      printf("Time of completion: %dh%dm%ds\n\n", runners[size].finishTime.h, runners[size].finishTime.m, runners[size].finishTime.s);
    }
}


//readFile: reads the file and organizes it into the difined structures
void readFile(FILE* file, Runner* runners, int size){

  char temp[STRING_SIZE] = {0};

  int l = 0;
  //ignore the first line
  fgets(temp, 200, file);

  //saves all data into structure variables
  for (l = 0; l < size; l++){
    fgets(temp, 200, file);
    sscanf(temp, "%d\t%s\t%d\t%d\t%[^\t]\t%c\t%d:%d:%d", &runners[l].globalPos, &runners[l].echelon, &runners[l].echelonPos, &runners[l].dorsalNum,
      &runners[l].name, &runners[l].gender, &runners[l].finishTime.h, &runners[l].finishTime.m, &runners[l].finishTime.s);
  }
}

//structAlloc: aloccates memmory for all runners' data
void structAlloc(FILE* file, Runner** runners, int* size){

  char temp[STRING_SIZE] = {0};

  //ignore the first line
  fgets(temp, 200, file);

  //count all the runners
  while (fgets(temp , 200, file) != NULL)
    (*size)++;

  //rewinds the file
  rewind(file);

  //allocating memmory for all the runners
  *runners = (Runner*)malloc( (*size) * sizeof(Runner) );
    if (*runners == NULL)
      exit (EXIT_FAILURE);

}
