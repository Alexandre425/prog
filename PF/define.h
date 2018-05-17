
#define FILE_NAME_SIZE 20
#define BUFFER_SIZE 100
#define TABLE_SIZE 50
#define PAGE_SIZE 20
#define COUNTRY 0
#define CITY 1
#define true 1

//############################################################
//DECLARATION OF THE MODE FUNCTIONS
//
//functions present in 'modes'
//the two functions corresponding to a functionality mode,
//each of them being the main function for their respective
//mode. Most of the functions needed are called here
//############################################################

//the main function of the textual mode of the program
//runs all the functions related to the functionality of the
//textual mode
//1. *countriesFile - the file pointer to the countries file
//2. *citiesFile - the file pointer to the cities file
void textualMode(FILE*, FILE*);

//the main function of the visual mode of the program
//runs all the functions related to the functionality of the
//visual mode. Only needs the cities file
//1. *citiesFile - the file pointer to the cities file
void visualMode(FILE*);

//############################################################
//DECLARATION OF GENERAL PURPOSE FUNCTIONS
//
//functions present in 'generalFunctions'
//used for various things related to the core functionality,
//like opening files and processing the arguments
//############################################################

//reads the arguments passed to main, returning the mode in which the program will start
//1. argc - number of arguments
//2. argv - argument array, from which mode and file names will be determined
//3. fileNames - two strings corresponding to the file names, to be written in this function
int readArguments(int, char const*[], char[2][FILE_NAME_SIZE]);

//opens the data files
//1. mode - the program operating mode
//2. fileNames - names of the two files, read by readArguments
//3. **countriesFile - the file pointer to the country file
//4. **citiesFile - the file pointer to the cities file
void openFiles(int, char[2][FILE_NAME_SIZE], FILE**, FILE**);

//closes the data files
//1. *countriesFile - the file pointer to the countries file
//2. *citiesFile - the file pointer to the cities file
void closeFiles(FILE*, FILE*);

//############################################################
//DECLARATION OF LISTING AND SORTING FUNCTIONS
//
//functions present in 'sortingFunctions'
//used for creating and deleting nodes, lists, head and other
//pointers, sorting the lists, etc.
//############################################################

//returns a 'ListInfo' struct for a file, with information on
//its year range
//1. *file - a file, can either be countriesFile or citiesFile
ListInfo getFileInfo(FILE*);

ListInfo getListInfo(node_t*);

//allocates memory for the auxiliary array of pointers to nodes
//from the lists
//returns the pointer to the allocated array
//1. range - year range of the file
node_t** allocateAuxArray(int);

//creates a sorted copy of the data files in memory
//1. *countriesFile - the file pointer to the country file
//2. **countriesHead - the head of the country list
//3. **countriesYearArray - the auxiliary year array of pointers
//4. *citiesFile - the file pointer to the cities file
//5. **citiesHead - the head of the city list
//6. **citiesYearArray - the auxiliary year array of pointers
void createSortedLists(FILE*, node_t**, node_t**, FILE*, node_t**, node_t**);

//frees the sorted copies of the data files in memory
//returns the new head (which will be NULL)
//1. *head - the head of the list to be freed
node_t* freeSortedList(node_t*);

//allocates memory for a new list node
//returns the pointer to the new node
//1. data - data1 struct. Described in 'struct.h'
//2. pos - data2 struct. Described in 'struct.h'
node_t* getNewNode(temp, data2);

//does a sorted insertion of a new list node
//returns the head pointer of the list
//1. head - the list head
//2. ptrArray - the array of year pointers
//3. newNode - the new node to be inserted
node_t* sortedInsert(node_t*, node_t**, node_t*);

//deletes a node from the list
//1. aux - pointer to the list entry before the
//  one which will be deleted
void deleteNode(node_t*);

//deletes the list head
//returns the new list head (the second entry)
//1. head - the head of the list
node_t* deleteHead(node_t*);

//finds the corresponding index on the year array, based on
//the year of the new list entry
//1. data - data1 struct, containing the year
int findIndex(data1);

//############################################################
//DECLARATION OF MENU FUNCTIONS
//
//functions present in 'menuFunctions'
//used for user interaction, all of them being connected by
//'mainMenu'.
//############################################################

//the main menu, accesses all the other 4 menus
//1. countriesHead - the head of the country lists
//2. citiesHead - the head of the city list
void mainMenu(node_t*, node_t*);

//the data filtering menu, allows the user to narrow the data
//1. countriesHead - the head of the country lists
//2. citiesHead - the head of the city list
//3. filtCountriesHead - the head of the filtered country list
//4. filtCitiesHead - the head of the filtered city list
void dataFilterMenu(node_t*, node_t*, node_t**, node_t**);

void initalDateFilter(node_t**, node_t**);
void seasonFilter(node_t**, node_t**);
  void deleteSeason(node_t**, int, int);
void resetFilter(node_t*, node_t*, node_t**, node_t**);

//the temperature history menu, allows the user to see
//maximum, minimum and average temperatures in a periodic
//manner, in a certain country or city, or globally
//1. filtCountriesHead - the head of the filtered country list
//2. filtCitiesHead - the head of the filtered city list
void tempHistoryMenu(node_t*, node_t*);

  //gets the size of string page to be allocated
  int getAllocSize(int, int);
  //prints the temperature history in a 20 entry page
  void printTempHistory(char**, int);

void tempHistoryGlobal(node_t*, int);
void tempHistoryCountry(node_t*, int);
void tempHistoryCity(node_t*, int);

//the yearly temperature analisis menu, allows the user to
//see the hottest, coldest, and most-extreme (in terms of
//temperature) countries or cities in a user-input year
//1. filtCountriesHead - the head of the filtered country list
//2. filtCitiesHead - the head of the filtered city list
void yearlyTempMenu(node_t*, node_t*);

void yearlyTempCountries(node_t*, node_t*);
void yearlyTempCities(node_t*, node_t*);

//the global temperature analisis menu, uses the moving average
//to calculate the temperature change globally, or for a country
//or city
//1. filtCountriesHead - the head of the filtered country list
//2. filtCitiesHead - the head of the filtered city list
void globalTempMenu(node_t*, node_t*);

void globalTempGlobal(node_t*, node_t*);
void globalTempCountry(node_t*, node_t*);
void globalTempCity(node_t*, node_t*);

//gets a sampling period for the temperature history menu
//returns the input period
int getSamplePeriod();

//gets a sample year for the yearly temperature analisis menu
//returns the input year
int getSampleYear();

//gets the ammount of years to calculate the moving average with
//returns the ammount of years
int getNumYears();
