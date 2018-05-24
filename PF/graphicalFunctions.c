#include<SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "struct.h"
#include "define.h"

extern int minYear;
extern int maxYear;
extern int numberOfCities;

extern float minPointTemp;
extern float maxPointTemp;

void initEverything(graph* SDL){

  //initializing the SDL library
  if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
    printf("%s\n", SDL_GetError());
    exit (EXIT_FAILURE);
  }

  //initializing the SDL font library
  if (TTF_Init() == -1){
    printf("%s\n", SDL_GetError());
    exit (EXIT_FAILURE);
  }

  //creating a window
  SDL->window = SDL_CreateWindow("WarmingUp", WINDOW_POSX, WINDOW_POSY, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
  if (SDL->window == NULL){
    printf("%s\n", SDL_GetError());
    exit (EXIT_FAILURE);
  }

  //creating a renderer for the window
  SDL->renderer = SDL_CreateRenderer(SDL->window, -1, 0);
  if (SDL->renderer == NULL){
    printf("%s\n", SDL_GetError());
    exit (EXIT_FAILURE);
  }
  //setting the renderer size
  SDL_RenderSetLogicalSize(SDL->renderer, WINDOW_WIDTH, WINDOW_HEIGHT);


  //loading the images
  //the main menu background
  SDL->image[0] = IMG_Load("Background.png");
  if (SDL->image[0] == NULL){
    printf("%s\n", SDL_GetError());
    exit (EXIT_FAILURE);
  }
  //the world map
  SDL->image[1] = IMG_Load("WorldMap.png");
  if (SDL->image[1] == NULL){
    printf("%s\n", SDL_GetError());
    exit (EXIT_FAILURE);
  }

  //loading the fonts
  //the regular font
  SDL->font = TTF_OpenFont("kenyancoffee.ttf", 24);
  if (SDL->font == NULL){
    printf("%s\n", SDL_GetError());
    exit (EXIT_FAILURE);
  }
  //the title font
  SDL->font = TTF_OpenFont("kenyancoffee.ttf", 56);
  if (SDL->font == NULL){
    printf("%s\n", SDL_GetError());
    exit (EXIT_FAILURE);
  }

}

void mainLoop(node_t* pointsHead, graph* SDL){

  int quit = 0;

  renderGreetingMenu(SDL);

  while (quit == 0){

    while (SDL_PollEvent(&SDL->event)){

      switch(SDL->event.type){

        case SDL_QUIT:
          return;
          break;

        case SDL_KEYDOWN:
          quit = mapLoop(pointsHead, SDL);
          renderGreetingMenu(SDL);
          break;
      }
    }
  }
}

void renderGreetingMenu(graph* SDL){

  SDL_Texture* background;
  SDL_Rect rectangle;

  //putting the rectangle in the upper left corner
  rectangle.x = 0;
  rectangle.y = 0;
  rectangle.w = WINDOW_WIDTH;
  rectangle.h = WINDOW_HEIGHT;

  //creating a texture from the image
  background = SDL_CreateTextureFromSurface(SDL->renderer, SDL->image[0]);
  SDL_RenderCopy(SDL->renderer, background, NULL, &rectangle);
  //freeing up the memory allocated for the texture
  SDL_DestroyTexture(background);

  SDL_RenderPresent(SDL->renderer);

}

int mapLoop(node_t* pointsHead, graph* SDL){

  int quit = 0;
  int ret = 0;
  SDL_Rect barLimits;
  SDL_Rect bar;

  int year = minYear;

  while (quit == 0 && ret == 0){

    ret = 0;
    renderMap(SDL);
    renderYears(SDL, &barLimits);
    bar = renderBar(SDL, year, barLimits);
    renderPoints(SDL, year, pointsHead);

    while (SDL_PollEvent(&SDL->event)){

      switch(SDL->event.type){

        case SDL_QUIT:
          quit = 1;
          break;

        case SDL_KEYDOWN:

          switch(SDL->event.key.keysym.sym){

            case SDLK_r:
              ret = 1;
              break;

            case SDLK_SPACE:
              mapLoopPause(SDL, &quit, &ret);
              break;
          }
          break;
      }
    }

    if (year < maxYear)
      year++;

      printf("%d\n", year);

    SDL_RenderPresent(SDL->renderer);
    SDL_Delay(100);
  }

  return quit;
}

void renderMap(graph* SDL){

  SDL_Texture* map;
  SDL_Rect rectangle;

  //putting the rectangle in the upper left corner
  rectangle.x = 0;
  rectangle.y = 0;
  rectangle.w = WINDOW_WIDTH;
  rectangle.h = WINDOW_HEIGHT;

  //creating a texture from the image
  map = SDL_CreateTextureFromSurface(SDL->renderer, SDL->image[1]);
  SDL_RenderCopy(SDL->renderer, map, NULL, &rectangle);
  //freeing up the memory allocated for the texture
  SDL_DestroyTexture(map);
}

void renderYears(graph* SDL, SDL_Rect* barLimits){

  char startYear[5] = {0};
  char endYear[5] = {0};
  sprintf(startYear, "%d", minYear);
  sprintf(endYear, "%d", maxYear);

  SDL_Color black = {0, 0, 0};

  SDL_Surface* textSurface;
  SDL_Texture* textTexture;
  SDL_Rect rectangle;

  //position to draw the text
  rectangle.x = MARGIN;
  rectangle.y = MAP_HEIGHT + MARGIN;
  //creating a surface with the text
  textSurface = TTF_RenderText_Blended(SDL->font, startYear, black);
  if (textSurface == NULL){
    printf("%s\n", TTF_GetError());
    exit(EXIT_FAILURE);
  }
  //creating a texture from the surface
  textTexture = SDL_CreateTextureFromSurface(SDL->renderer, textSurface);
  //getting the texture size
  SDL_QueryTexture(textTexture, NULL, NULL, &rectangle.w, &rectangle.h);
  //rendering
  SDL_RenderCopy(SDL->renderer, textTexture, NULL, &rectangle);

  barLimits->x = MARGIN + rectangle.w + MARGIN;
  barLimits->y = rectangle.y;

  //creating a surface with the text
  textSurface = TTF_RenderText_Blended(SDL->font, endYear, black);
  if (textSurface == NULL){
    printf("%s\n", TTF_GetError());
    exit(EXIT_FAILURE);
  }
  //creating a texture from the surface
  textTexture = SDL_CreateTextureFromSurface(SDL->renderer, textSurface);
  //getting the texture size
  SDL_QueryTexture(textTexture, NULL, NULL, &rectangle.w, &rectangle.h);
  //position to draw the text
  rectangle.x = WINDOW_WIDTH - MARGIN - rectangle.w;
  rectangle.y = MAP_HEIGHT + MARGIN;
  //rendering
  SDL_RenderCopy(SDL->renderer, textTexture, NULL, &rectangle);

  barLimits->w = WINDOW_WIDTH - barLimits->x - MARGIN - rectangle.w - MARGIN;
  barLimits->h = rectangle.h;

  SDL_DestroyTexture(textTexture);
  SDL_FreeSurface(textSurface);

}

SDL_Rect renderBar(graph* SDL, int year, SDL_Rect barLimits){

  SDL_Rect bar;
  SDL_Color color = {160, 192, 255, 255};

  bar.x = barLimits.x;
  bar.y = barLimits.y;

  bar.h = barLimits.h;
  //determining the width of the bar, based on the year
  bar.w = ((year - minYear) * barLimits.w) / (maxYear - minYear);

  //setting the color of the rectangle
  SDL_SetRenderDrawColor(SDL->renderer, color.r, color.g, color.b, color.a);
  //drawing the rectange
  SDL_RenderFillRect(SDL->renderer, &bar);

  return bar;
}

SDL_Color getColor(float temp){

  SDL_Color color = {0, GREEN, 0, 255};

  float redSlope = 0.0f
  float blueSlope = 0.0f

  //determining the function slope
  redSlope = (float)(MAX_RED_BLUE - MIN_RED_BLUE) / (float)(maxPointTemp - minPointTemp);
  blueSlope = (float)(MIN_RED_BLUE - MAX_RED_BLUE) / (float)(maxPointTemp - minPointTemp);

  //getting the color in function of the temperature
  color.r = redSlope * temp;
  color.b = blueSlope * temp;

  return color;
}

SDL_Rect getPosition(data2 pos){

  SDL_Rect rectangle;

  

  return rectangle;
}

void renderPoints(graph* SDL, int year, node_t* pointsHead){

  node_t* aux = NULL;
  SDL_Color color = {0, 0, 0, 255};
  SDL_Rect pos;

  //finding the year to print the corresponding points
  aux = pointsHead;
  while (aux != NULL){
    if (aux->data.year == year)
      break;
    aux = aux->next;
  }

  while (aux != NULL){
    //stopping when we get past the year we are printing
    if (aux->data.year != year)
      break;

    color = getColor(aux->data.temp);
    pos = getPosition(aux->pos);


    aux = aux->next;
  }

}

void mapLoopPause(graph* SDL, int* quit, int* ret){

  int unpause = 0;

  while (unpause == 0){
    while (SDL_PollEvent(&SDL->event)){

      switch(SDL->event.type){

        case SDL_QUIT:
          *quit = 1;
          unpause = 1;
          break;

        case SDL_KEYDOWN:

          switch(SDL->event.key.keysym.sym){

            case SDLK_r:
              *ret = 1;
              unpause = 1;
              break;

            case SDLK_SPACE:
              unpause = 1;
              break;
          }
          break;
      }
    }
  }
}
