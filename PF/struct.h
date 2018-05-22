//temporarily stores the data for a new node
typedef struct temp{
  int year;
  int month;
  float temp;
  char name[100];
} temp;

typedef struct data1{
  int year;
  int month;
  float temp;
  char* name;
} data1;

typedef struct data2{
  float lat;
  char cLat;
  float lon;
  char cLon;
} data2;

//used for cities and countries
typedef struct node{
  data1 data;
  data2 pos;

  struct node* next;
} node_t;

typedef struct{
  int maxYear;
  int minYear;
  int range;
} ListInfo;

//holds data to be printed by the history menu
typedef struct{
  int iniYear;
  int finYear;
  float maxTemp;
  float minTemp;
  float medTemp;
} hist;

//node for the yearly temperature list
//used to make the top-x
typedef struct top{
  char name[80];
  float temp;
  float range;
  struct top* next;
} top_t;

//n
typedef struct {
  int year;
  int month;
  float temp;
} median;
