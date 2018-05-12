typedef struct Country{
  int year;
  int month;
  float temp;
  char* name;
  struct Country* next;
  struct Country* prev;
} Country;

typedef struct City{
  int year;
  int month;
  float temp;
  char* name;
  float latitude;
  float longitude;
  struct City* next;
  struct City* prev;
} City;

typedef struct{
  int maxYear;
  int minYear;
  int range;
} ListInfo;
