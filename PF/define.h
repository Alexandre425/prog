
#define FILE_NAME_SIZE 20
#define BUFFER_SIZE 100
#define HEADER_SIZE 300
#define PAGE_SIZE 20
#define COUNTRY 0
#define CITY 1
#define true 1

#define WINDOW_POSX 150
#define WINDOW_POSY 80
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 650

#define MAP_WIDTH 1000
#define MAP_HEIGHT 500

#define MARGIN 10

#define MAX_RED_BLUE 255
#define MIN_RED_BLUE 48
#define GREEN 48

#define CIRCLE_RADIUS 4
#define M_PI 3.14159265

#define PENGUIN_WIDTH 77
#define PENGUIN_HEIGHT 90
#define PENGUIN_JUMP_HEIGHT 7


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

//analizes the list and allocates an array of pointers to the
//first entry on each city on the list
//returns the pointer to the allocated array
node_t** createGraphicalAuxArray(node_t*);

//creates a sorted copy of the data files in memory
//1. *countriesFile - the file pointer to the country file
//2. **countriesHead - the head of the country list
//3. **countriesYearArray - the auxiliary year array of pointers
//4. *citiesFile - the file pointer to the cities file
//5. **citiesHead - the head of the city list
//6. **citiesYearArray - the auxiliary year array of pointers
void createSortedLists(FILE*, node_t**, node_t**, FILE*, node_t**, node_t**);

//loads the city file into a list
//returns the loaded list
//1. *citiesFile - the file pointer to the cities file
node_t* loadCityList(FILE*);

//creates a list with the cities' median temperature and coordinates for
//a year. Each node corresponds to a city in a year, sorted by
//their years
//returns the created list's head
//1. head - the head of the main list
node_t* createMedianTempCityList(node_t*);

//determines the minimum and maximum temperature point. Used to determine
//what the "red-est" and "blue-est" points will be
//1. pointsHead - the point list head
void getMinMaxTemp(node_t*);

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

//gets a new node for the top-x lists
//returns the pointer to the new allocated node
//1. data - structure with the data for the new entry
top_t* yearlyTemp_getNewNode(top_t);

//does a sorted insertion of a new node in the median tmp. list
//returns the (possibly new) head of the list
//1. head - the head of the top list
//2. newNode - the new node to be inserted
top_t* yearlyTemp_sortedInsertTemp(top_t*, top_t*);

//does a sorted insertion of a new node in the tmp. range list
//returns the (possibly new) head of the list
//1. head - the head of the top_t list
//2. newNode - the new node to be inserted
top_t* yearlyTemp_sortedInsertRange(top_t*, top_t*);

//gets the information on a country or city's temperature on a specific year
//returns a top_t struct with its name, median temp. and temp. range
//1. sampleYearPointer - the pointer to the first entry for the sample year
//2. name - the name of the country or city to search for
top_t yearlyTemp_getInfoByName(node_t*, char*);

//creates sorted median and temperature range lists for the Yearly
//Temperature menu, for a specific year
//1. head - the head of the list (city or country)
//2. sampleYear - the year being sampled
//3. tempHead - the head of the median temp. top_t list
//4. rangeHead - the head of the temp. range top_t list
void yearlyTemp_createSortedLists(node_t*, int, top_t**, top_t**);

//frees a top_t list
//returns the new head (NULL)
//1. head - the top_t list head
top_t* yearlyTemp_freeSortedList(top_t*);

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

  //gets the size of the struct array to be allocated
  int getAllocSize(int, int);
  //prints the temperature history in a 20 entry page
  void printTempHistory(hist*, char[HEADER_SIZE], int);

void tempHistoryGlobal(node_t*, int);
void tempHistoryCountry(node_t*, int);
void tempHistoryCity(node_t*, int);

//the yearly temperature analisis menu, allows the user to
//see the hottest, coldest, and most-extreme (in terms of
//temperature) countries or cities in a user-input year
//1. filtCountriesHead - the head of the filtered country list
//2. filtCitiesHead - the head of the filtered city list
void yearlyTempMenu(node_t*, node_t*);

  //prints the top x list of countries or cities, based on the
  //sorted median temp. and temp. range lists
  void printYearlyTemp(top_t*, top_t*, int, int);

void yearlyTempCountries(node_t*, int);
void yearlyTempCities(node_t*, int);

//the global temperature analisis menu, uses the moving average
//to calculate the temperature change globally, or for a country
//or city
//1. filtCountriesHead - the head of the filtered country list
//2. filtCitiesHead - the head of the filtered city list
void globalTempMenu(node_t*, node_t*);

  //prints the temperature change in the 5 defined years
  void printGlobalTemp(float*, char[HEADER_SIZE]);
  //returns an array with the medium global temperature each month
  median* getMedianTempByMonth(node_t*, int*);
  //returns an array with the temperature for a country/city each month
  median* getMedianTempByName(node_t*, int*, char[BUFFER_SIZE]);
  //returns the temperature change in the 5 defined years using
  //the moving average calculation
  float* getMovingAverage(median*, int, int);

void globalTempGlobal(node_t*, int);
void globalTempCountry(node_t*, int);
void globalTempCity(node_t*, int);

//gets a sampling period for the temperature history menu
//returns the input period
int getSamplePeriod();

//gets a sample year for the yearly temperature analisis menu
//returns the input year
int getSampleYear();

//gets the ammount of months to calculate the moving average with
//returns the ammount of months
int getNumMonths();

//############################################################
//DECLARATION OF GRAPHICAL FUNCTIONS
//
//functions present in 'graphicalFunctions'
//used for drawing on a window and processing events like
//key presses
//############################################################

//initializes all SDL-related things, like images, fonts, the window, etc.
//1. SDL - the SDL struct
void initEverything(graph*);

//frees the memory used by SDL
//1. SDL - the SDL struct
void freeEverything(graph*);

//the main loop of the graphical mode, runs the other functions
//1. head - the head of the city list
//2. auxArray - the auxiliary array of pointers
//3. SDL - the SDL struct
void mainLoop(node_t*, graph*);

//renders the greeting menu
//1. SDL - the SDL struct
void renderGreetingMenu(graph*);

//the loop which draws the map and the dots with the temperatures
//returns 1 if the user chose to quit the program while it was running
//1. head - the head of the city list
//2. auxArray - the auxiliary array of pointers
//3. SDL - the SDL struct
int mapLoop(node_t*, graph*);

//renders the map
//1. SDL - the SDL struct
void renderMap(graph*);

//renders the minimum and maximum years on the lower corners of the map
//1. SDL - the SDL struct
//2. barLimits - limits for the bar which will go from one text to the other
//    essentially defined as a rectangle with the dimensions of the maximum bar size
void renderYears(graph*, SDL_Rect*, int);

//renders the bar in between the years which grows with time
//1. SDL - the SDL struct
//2. year - the current year, defines the bar's length
//3. barLimits - the maximum size of the bar
SDL_Rect renderBar(graph*, int, SDL_Rect barLimits);

//renders the penguin on the end of the bar
//1. SDL - the SDL struct
//2. year - the current year, used for making the penguin jump
//3. bar - the bar, used for drawing the penguin on the end
void renderPenguin(graph*, int, SDL_Rect);

//returns a color corresponding to a temperature
//uses a linear equation to calculate the red and blue components
//1. temp -  the temperature for which the color will be returned
SDL_Color getColor(float);

//returns the position (from the upper corner of the window) where
//the point will be drawn from the coordinates
//returns the coordinates (in the form of a rectangle)
//1. pos - the coordinate struct
SDL_Rect getPosition(data2);

//draws a filled circle
//1. _renderer - the SDL renderer
//2. _circleX - the X coordinate
//3. _circleY - the Y coordinate
//4. _circleR - the radius
//5. _r - the red component of the color
//6. _g - the green component of the color
//7. _b - the blue component of the color
void filledCircleRGBA(SDL_Renderer*, int, int, int, int, int, int);

//renders the points on the map each year
//1. SDL - the SDL struct
//2. year - the current year
//3. pointsHead - the head of the points lists
void renderPoints(graph*, int, node_t*);

//pauses the map animation
//1. SDL - the SDL struct
//2. quit - detects if the user quits the program (while paused)
//3. ret - detects if the user returns to the main menu (while paused)
void mapLoopPause(graph*, int*, int*);
