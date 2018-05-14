typedef struct data1{
  int year;
  int month;
  float temp;
  char* name;
} data1;

typedef struct data2{
  float latitude;
  float longitude;
} data2;

//used for cities and countries
typedef struct node{
  data1 data;
  data2 pos;

  struct node* next;
  struct node* prev;
} node_t;

typedef struct{
  int maxYear;
  int minYear;
  int range;
} ListInfo;
