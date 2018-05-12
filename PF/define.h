#define FILE_NAME_SIZE 20
#define BUFFER_SIZE 100

//############################################################
//DECLARATION OF THE MODE FUNCTIONS
//
//functions present in 'modes'
//the two functions corresponding to a functionality mode,
//each of them being the main function for their respective
//mode. Most of the functions needed are called here
//############################################################

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
