#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
  int x;
  int y;
} Point;

typedef struct poly{
  Point *pts;
  int pointNum;
  struct poly* next;
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

  //Asks for n point coordinates
  printf("Note: insert the coordinates in the 'x,y' format\n");
  for (i = 0; i < *n; i++){
    printf("Insert the coordinates for point %d: ", i + 1);
    scanf("%d,%d", &pointList[i].x, &pointList[i].y);
  }

  return pointList;
}

void createPolygon(Point* pointList, int n, Polygon** head){

  Polygon* node = NULL;
  Polygon* aux = NULL;

  //allocates memmory for the new node
  node = (Polygon*)malloc(sizeof(Polygon));

  node->next = NULL;
  node->pts = malloc(n * sizeof(Point));
  memcpy(node->pts, pointList, n * sizeof(Point));
  node->pointNum = n;

  //if there is no head, the new node becomes the head
  if (*head == NULL){
    *head = node;
    return;
  }

  //auxiliary pointer
  aux = *head;

  //reaching the end of the list
  while (aux->next != NULL)
    aux = aux->next;

  //having the last entry of the list point to the new entry
  aux->next = node;

}


void writePolygons(Polygon* head){

  int i = 0, p = 0;

  Polygon* aux = head;
  Polygon* freeAux = NULL;

  printf("\n\n");

  while(aux != NULL){

    switch(aux->pointNum){
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

    for (p = 0; p < aux->pointNum; p++)
      printf("(%d,%d), ", aux->pts[p].x, aux->pts[p].y);

    printf("\n");

    freeAux = aux;
    aux = aux->next;

    free(freeAux);
  }
}

int main (void){

  int n = 0, m = 0;
  int i = 0;
  Point* pointList = NULL;
  Polygon* head = NULL;

  printf("Insert the number of polygons you wish to create: ");
  scanf("%d", &m);

  for (i = 0; i < m; i++){
    pointList = readPoints(&n);
    createPolygon(pointList, n, &head);
    n = 0;
    free(pointList);
  }

  writePolygons(head);

  return EXIT_SUCCESS;
}
