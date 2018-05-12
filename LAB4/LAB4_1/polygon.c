#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
  int x;
  int y;
} Point;

typedef struct{
  Point *pts;
  int pointNum;
} Polygon;

Point* readPoints(int *n){

  int i = 0;

  //Asks for the number of points each polygon will have
  while (*n < 3){
    printf("\nInsert the number of points by which the polygon is defined: ");
    scanf("%d", n);
    if (*n < 3)
      printf("Polygons have at least 3 points! Insert a valid value.\n");
  }

  // Allocates memmory for all points
  Point* pointList = (Point*)malloc(*n * sizeof(Point));
  if (pointList == NULL){
    printf("Error while allocating memmory!\n" );
    exit (EXIT_FAILURE);
  }

  //Asks for n point coordinates
  printf("Note: insert the coordinates in the 'x,y' format\n");
  for (i = 0; i < *n; i++){
    printf("Insert the coordinates for point %d: ", i + 1);
    scanf("%d,%d", &pointList[i].x, &pointList[i].y);
  }

  return pointList;
}

Polygon* createPolygon(Point* pointList, int n, int i, int m, Polygon* polyList){

  if (polyList == NULL)
    polyList = (Polygon*)malloc(m * sizeof(Polygon));

  polyList[i].pointNum = n;
  polyList[i].pts = malloc(n * sizeof(Point));
  //polyList[i].pts = pointList;
  memcpy(polyList[i].pts, pointList, n * sizeof(Point));

  return polyList;
}


void writePolygons(Polygon* polyList, int m){

  int i = 0, p = 0;

  printf("\n\n");

  for (i = 0; i < m; i++){

    switch(polyList[i].pointNum){
      case 3:
      printf("Polygon %d is a triangle defined by points: ", i + 1);
      break;
      case 4:
      printf("Polygon %d is a quadrilateral defined by points: ", i + 1);
      break;
      case 5:
      printf("Polygon %d is a pentagon defined by points: ", i + 1);
      break;
      case 6:
      printf("Polygon %d is an hexagon defined by points: ", i + 1);
      break;
      case 7:
      printf("Polygon %d is an heptagon defined by points: ", i + 1);
      break;
      case 8:
      printf("Polygon %d is an octagon defined by points: ", i + 1);
      break;
      case 9:
      printf("Polygon %d is an enneagon defined by points: ", i + 1);
      break;
      case 10:
      printf("Polygon %d is a decagon defined by points: ", i + 1);
      break;
      case 11:
      printf("Polygon %d is an undcagon defined by points: ", i + 1);
      break;
      case 12:
      printf("Polygon %d is a dodecagon defined by points: ", i + 1);
      break;
      default:
      printf("Polygon %d is defined by points: ", i + 1);
      break;
    }

    for (p = 0; p < polyList[i].pointNum; p++)
      printf("(%d,%d), ", polyList[i].pts[p].x, polyList[i].pts[p].y);

    printf("\n");

  }
}

int main (void){

  int n = 0, m = 0;
  int i = 0;
  Point* pointList = NULL;
  Polygon* polyList = NULL;

  printf("Insert the number of polygons you wish to create: ");
  scanf("%d", &m);

  for (i = 0; i < m; i++){
    pointList = readPoints(&n);
    polyList = createPolygon(pointList, n, i, m, polyList);
    n = 0;
    free(pointList);
  }

  writePolygons(polyList, m);

  free(polyList);
  return EXIT_SUCCESS;
}
