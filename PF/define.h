#define FILE_NAME_SIZE 20
#define BUFFER_SIZE 100
#define COUNTRY 0
#define CITY 1

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
ListInfo GetFileInfo(FILE*);

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

//finds the corresponding index on the year array, based on
//the year of the new list entry
//1. data - data1 struct, containing the year
int findIndex(data1);
