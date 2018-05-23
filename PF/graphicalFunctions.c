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

void mainLoop(node_t* head, node_t** auxArray, graph* SDL){

  int quit = 0;

  renderGreetingMenu(SDL);

  while (quit == 0){

    while (SDL_PollEvent(&SDL->event)){

      switch(SDL->event.type){

        case SDL_QUIT:
          return;
          break;

        case SDL_KEYDOWN:
          quit = mapLoop(head, auxArray, SDL);
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

int mapLoop(node_t* head, node_t** auxArray, graph* SDL){

  int quit = 0;
  int ret = 0;

  int year = minYear;

  while (quit == 0 && ret == 0){

    ret = 0;
    renderMap(SDL);

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

  SDL_RenderPresent(SDL->renderer);

}

void renderYears(graph* SDL){

  char startYear[5] = {0};
  char endYear[5] = {0};

  SDL_Surface* textSurface;
  SDL_Texture* textTexture;
  SDL_Rect rectangle;

  sprintf(startYear, "%d", minYear);
  sprintf(endYear, "%d", maxYear);


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
