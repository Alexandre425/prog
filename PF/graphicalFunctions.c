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
  //the penguin
  SDL->image[2] = IMG_Load("Penguin.png");
  if (SDL->image[2] == NULL){
    printf("%s\n", SDL_GetError());
    exit (EXIT_FAILURE);
  }

  //loading the font
  SDL->font = TTF_OpenFont("kenyancoffee.ttf", 56);
  if (SDL->font == NULL){
    printf("%s\n", SDL_GetError());
    exit (EXIT_FAILURE);
  }

}

void freeEverything(graph* SDL){

  TTF_CloseFont(SDL->font);
  SDL_FreeSurface(SDL->image[0]);
  SDL_FreeSurface(SDL->image[1]);
  SDL_FreeSurface(SDL->image[2]);
  SDL_DestroyRenderer(SDL->renderer);
  SDL_DestroyWindow(SDL->window);
  SDL_Quit();

}

void mainLoop(node_t* pointsHead, graph* SDL){

  int quit = 0;

  renderGreetingMenu(SDL);

  //while the user has not quit
  while (quit == 0){

    //while there are events to handle
    while (SDL_PollEvent(&SDL->event)){

      switch(SDL->event.type){

        case SDL_QUIT:
          return;
          break;

        //if any key is pressed, the map loop is ran
        case SDL_KEYDOWN:
          quit = mapLoop(pointsHead, SDL);
          //as soon as we return from the map loop, draw the greeting menu
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
  //demensions equal to the window size (occupies the whole window)
  rectangle.w = WINDOW_WIDTH;
  rectangle.h = WINDOW_HEIGHT;

  //creating a texture from the image
  background = SDL_CreateTextureFromSurface(SDL->renderer, SDL->image[0]);
  SDL_RenderCopy(SDL->renderer, background, NULL, &rectangle);
  //freeing up the memory allocated for the texture
  SDL_DestroyTexture(background);

  //presenting the greeting menu
  SDL_RenderPresent(SDL->renderer);

}

int mapLoop(node_t* pointsHead, graph* SDL){

  int quit = 0;
  int ret = 0;
  SDL_Rect barLimits;
  SDL_Rect bar;

  int year = minYear;

  //while the user hasn't chosen to quit or return to the main menu
  while (quit == 0 && ret == 0){

    //render the map, the years, the moving bar, penguin and points for the current year
    ret = 0;
    renderMap(SDL);
    renderYears(SDL, &barLimits, year);
    bar = renderBar(SDL, year, barLimits);
    renderPenguin(SDL, year, bar);
    renderPoints(SDL, year, pointsHead);

    //handling the needed events
    while (SDL_PollEvent(&SDL->event)){

      switch(SDL->event.type){

        //the quit value is returned to the main loop, where it is handled and closes the window
        case SDL_QUIT:
          quit = 1;
          break;

        case SDL_KEYDOWN:

          //handling the return and pause buttons
          switch(SDL->event.key.keysym.sym){

            //this simply breaks the look, returning to the main loop
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

    //incrementing the year until we reach the end
    if (year < maxYear)
      year++;

    //presenting the renderer and applying a delay
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

void renderYears(graph* SDL, SDL_Rect* barLimits, int year){

  char startYear[5] = {0};
  char endYear[5] = {0};
  char currYear[5] = {0};
  sprintf(startYear, "%d", minYear);
  sprintf(endYear, "%d", maxYear);
  sprintf(currYear, "%d", year);

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
  //rendering in a rectangle with the corresponding size
  SDL_RenderCopy(SDL->renderer, textTexture, NULL, &rectangle);
  //freeing up the used memory
  SDL_DestroyTexture(textTexture);
  SDL_FreeSurface(textSurface);

  //defining the bar's starting point as the end of the first year plus a margin
  barLimits->x = MARGIN + rectangle.w + MARGIN;
  //as well as the same y position as the text
  barLimits->y = rectangle.y;

  //rendering the last year
  textSurface = TTF_RenderText_Blended(SDL->font, endYear, black);
  if (textSurface == NULL){
    printf("%s\n", TTF_GetError());
    exit(EXIT_FAILURE);
  }
  textTexture = SDL_CreateTextureFromSurface(SDL->renderer, textSurface);
  SDL_QueryTexture(textTexture, NULL, NULL, &rectangle.w, &rectangle.h);
  rectangle.x = WINDOW_WIDTH - MARGIN - rectangle.w;
  rectangle.y = MAP_HEIGHT + MARGIN;
  SDL_RenderCopy(SDL->renderer, textTexture, NULL, &rectangle);
  SDL_DestroyTexture(textTexture);
  SDL_FreeSurface(textSurface);

  //determining the maximum width of the bar (in between the two years, with margins)
  barLimits->w = WINDOW_WIDTH - barLimits->x - MARGIN - rectangle.w - MARGIN;
  //height is the same as the years'
  barLimits->h = rectangle.h;

  //rendering the current year
  textSurface = TTF_RenderText_Blended(SDL->font, currYear, black);
  if (textSurface == NULL){
    printf("%s\n", TTF_GetError());
    exit(EXIT_FAILURE);
  }
  textTexture = SDL_CreateTextureFromSurface(SDL->renderer, textSurface);
  SDL_QueryTexture(textTexture, NULL, NULL, &rectangle.w, &rectangle.h);
  //it is rendered in the middle of the screen
  rectangle.x = (MAP_WIDTH / 2) - (rectangle.w / 2);
  rectangle.y = MAP_HEIGHT - rectangle.h - MARGIN;
  SDL_RenderCopy(SDL->renderer, textTexture, NULL, &rectangle);
  SDL_DestroyTexture(textTexture);
  SDL_FreeSurface(textSurface);
}

SDL_Rect renderBar(graph* SDL, int year, SDL_Rect barLimits){

  SDL_Rect bar;
  SDL_Color color = {58, 128, 180, 255};

  bar.x = barLimits.x;
  bar.y = barLimits.y;

  //height is always the same
  bar.h = barLimits.h;
  //determining the width of the bar, based on the year
  bar.w = ((year - minYear) * barLimits.w) / (maxYear - minYear);

  //setting the color of the rectangle
  SDL_SetRenderDrawColor(SDL->renderer, color.r, color.g, color.b, color.a);
  //drawing the rectangle
  SDL_RenderFillRect(SDL->renderer, &bar);

  return bar;
}

void renderPenguin(graph* SDL, int year, SDL_Rect bar){

  SDL_Texture* penguin;
  SDL_Rect rectangle;

  //penguin is drawn at the end of the bar
  rectangle.x = bar.x + bar.w - (PENGUIN_WIDTH / 2);
  rectangle.y = bar.y;
  rectangle.w = PENGUIN_WIDTH;
  rectangle.h = PENGUIN_HEIGHT;

  //jumping every other year to make the penguin appear to be walking
  if (year % 2 == 0)
    rectangle.y -= PENGUIN_JUMP_HEIGHT;

  //creating the texture and drawing
  penguin = SDL_CreateTextureFromSurface(SDL->renderer, SDL->image[2]);
  SDL_RenderCopy(SDL->renderer, penguin, NULL, &rectangle);
  //destroying the texture
  SDL_DestroyTexture(penguin);

}

SDL_Color getColor(float temp){

  SDL_Color color = {0, GREEN, 0, 255};

  float redSlope = 0.0f;
  float blueSlope = 0.0f;

  int redB = 0;
  int blueB = 0;

  //determining the function slope
  redSlope = (float)(MAX_RED_BLUE - MIN_RED_BLUE) / (float)(maxPointTemp - minPointTemp);
  blueSlope = (float)(MIN_RED_BLUE - MAX_RED_BLUE) / (float)(maxPointTemp - minPointTemp);

  //determining the offset at x = 0 / temp = 0.0f
  redB = (int)( MIN_RED_BLUE - ((float)redSlope * minPointTemp) );
  blueB = (int)( MAX_RED_BLUE - ((float)blueSlope * minPointTemp) );

  //getting the color in function of the temperature
  color.r = (int)( ((float)redSlope * (float)temp) + redB );
  color.b = (int)( ((float)blueSlope * (float)temp) + blueB );

  return color;
}

SDL_Rect getPosition(data2 pos){

  SDL_Rect rectangle;
  SDL_Rect mapCenter;

  //determining the map center
  mapCenter.x = MAP_WIDTH / 2;
  mapCenter.y = MAP_HEIGHT / 2;

  //determining the coordinates in relation to the center of the map
  rectangle.x = ((float)(MAP_WIDTH / 2) * (float)pos.lon) / 180;
  rectangle.y = ((float)(MAP_HEIGHT / 2) * (float)pos.lat) / 90;

  //inverting if needed (ex: north is above the center, so the value must be negative)
  if (pos.cLon == 'W')
    rectangle.x *= -1;
  if (pos.cLat == 'N')
    rectangle.y *= -1;

  //getting the coordinates in relation to the upper left corner
  rectangle.x = mapCenter.x + rectangle.x;
  rectangle.y = mapCenter.y + rectangle.y;

  return rectangle;
}

void filledCircleRGBA(SDL_Renderer * _renderer, int _circleX, int _circleY, int _circleR, int _r, int _g, int _b){
    int off_x = 0;
    int off_y = 0;
    float degree = 0.0;
    float step = M_PI / (_circleR*8);

    SDL_SetRenderDrawColor(_renderer, _r, _g, _b, 255);

    while (_circleR > 0)
    {
        for (degree = 0.0; degree < M_PI/2; degree+=step)
        {
            off_x = (int)(_circleR * cos(degree));
            off_y = (int)(_circleR * sin(degree));
            SDL_RenderDrawPoint(_renderer, _circleX+off_x, _circleY+off_y);
            SDL_RenderDrawPoint(_renderer, _circleX-off_y, _circleY+off_x);
            SDL_RenderDrawPoint(_renderer, _circleX-off_x, _circleY-off_y);
            SDL_RenderDrawPoint(_renderer, _circleX+off_y, _circleY-off_x);
        }
        _circleR--;
    }
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

  //while we haven't reached the end of the list
  while (aux != NULL){
    //stopping when we get past the year we are printing
    if (aux->data.year != year)
      break;

    //getting the color and position to draw the point with
    color = getColor(aux->data.temp);
    pos = getPosition(aux->pos);
    filledCircleRGBA(SDL->renderer, pos.x, pos.y, CIRCLE_RADIUS, color.r, color.g, color.b);

    //traversing the list
    aux = aux->next;
  }
}

void mapLoopPause(graph* SDL, int* quit, int* ret){

  int unpause = 0;

  //while the user hasn't unpaused
  while (unpause == 0){
    //handling events
    while (SDL_PollEvent(&SDL->event)){

      switch(SDL->event.type){

        //quitting unpauses to allow previous functions to process the quit
        case SDL_QUIT:
          *quit = 1;
          unpause = 1;
          break;

        case SDL_KEYDOWN:

          switch(SDL->event.key.keysym.sym){

            //if the user returns while paused
            case SDLK_r:
              *ret = 1;
              unpause = 1;
              break;

            //if the user unpauses
            case SDLK_SPACE:
              unpause = 1;
              break;
          }
          break;
      }
    }
  }
}
