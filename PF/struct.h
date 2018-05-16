typedef struct temp{
  int year;
  int month;
  float temp;
  char name[50];
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
