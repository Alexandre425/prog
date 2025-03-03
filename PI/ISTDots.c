//#################################################//
// ISTDots - Alexandre Rodrigues, 90002
// Jogo Dots
// Controlos: Clicar sobre uma bola, arrastar sobre bolas da mesma cor e largar para as eliminar
// Quadrados eliminam todas as bolas da cor selecionada, bem como o seu interior
// 'N' começa um jogo novo (contabilizado com uma derrota)
// 'U' desfaz a ultima jogada. Não se podem desfazer duas jogadas seguidas!
// 'Q' termina o jogo
// As estatísticas de jogo são escritas no ficheiro 'stats.txt'
//#################################################//

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX(a,b)    (((a)>(b))?(a):(b))
#define SQR(a)      (a)*(a)
#define M_PI 3.14159265
#define STRING_SIZE 100       // max size for some strings
#define TABLE_SIZE 670        // main game space size
#define LEFT_BAR_SIZE 160     // left white bar size
#define WINDOW_POSX 200       // initial position of the window: x
#define WINDOW_POSY 200       // initial position of the window: y
#define SQUARE_SEPARATOR 8    // square separator in px
#define BOARD_SIZE_PER 0.7f   // board size in % wrt to table size
#define MAX_BOARD_POS 16      // maximum size of the board    Note: This value was altered to 16 to prevent a bug with lowering the board
#define MAX_COLORS 5          //                                    when playing with a 15x15 board. 15x15 is still the max size, however.
#define MARGIN 5              //                                    This was probably the simplest aproach to fixing this bug
#define MAX_SELBOARD_POS 200

#define RECT_MARGIN 30
#define RECT_W 98
#define RECT_H 46
#define RECT_CIRCLE_R 16
#define RECT_CIRCLE_MARGIN 23

#define MAX_GAMES 200

// declaration of the functions related to graphical issues
void InitEverything(int , int , TTF_Font **, SDL_Surface **, SDL_Window ** , SDL_Renderer **, TTF_Font ** );
void InitSDL();
void InitFont();
SDL_Window* CreateWindow(int , int );
SDL_Renderer* CreateRenderer(int , int , SDL_Window *);
int RenderText(int, int, const char *, TTF_Font *, SDL_Color *, SDL_Renderer *);
int RenderLogo(int, int, SDL_Surface *, SDL_Renderer *);
int RenderTable(int, int, int [], TTF_Font *, SDL_Surface **, SDL_Renderer *, int[][MAX_BOARD_POS]);
void ProcessMouseEvent(int , int , int [], int , int *, int * );
void RenderPoints(int [][MAX_BOARD_POS], int, int, int [], int, SDL_Renderer *);
void RenderStats( SDL_Renderer *, TTF_Font *, int [], int , int );
void filledCircleRGBA(SDL_Renderer * , int , int , int , int , int , int );
//Renders game information pop-ups
void RenderGameInfo(SDL_Renderer*, int, SDL_Surface**);

// Declaration of the functions related to functionality
//Reads the input parameters
void gameConfig(int*, int*, int*, int[MAX_COLORS], int*, char[STRING_SIZE]);
//Starts a new game with the same input parameters
void newGame(int[][MAX_BOARD_POS], int, int, int, int[MAX_COLORS], int [MAX_COLORS], int, int*);
//Generates a single randomly colored dot
int getRandom(int);
//Registers any play/input made by the user, passing it to inputVerify()
void inputRegister(int[][MAX_BOARD_POS], int[][MAX_SELBOARD_POS], int, int, int*);
//Verifies if the user made a legal move
int inputVerify(int[][MAX_BOARD_POS], int[][MAX_SELBOARD_POS], int);
//Clears the board according to the input received (and the verification)
void boardClear(int[][MAX_BOARD_POS], int[][MAX_BOARD_POS], int[][MAX_SELBOARD_POS], int, int, int, int, int [MAX_COLORS]);
//Clears the input arrays, resetting them to their default state
void inputClear(int[][MAX_BOARD_POS], int[][MAX_SELBOARD_POS]);
//Moves the dots down and generates random dots at the top
void boardDown(int[][MAX_BOARD_POS], int, int, int, int);
//Verifies if there are any possible moves left, shuffling the board if not
int shuffleVerify(int[][MAX_BOARD_POS], int, int);
//Shuffles the board's elements
void boardShuffle(int[][MAX_BOARD_POS], int, int);
//Verifies if the game has ended
int gameEndVerify(int[MAX_COLORS], int);
//Saves the current game state
void saveGameState(int[][MAX_BOARD_POS], int[][MAX_BOARD_POS], int[MAX_COLORS], int [MAX_COLORS], int, int);
//Restores the last game state
void restoreGameState(int[][MAX_BOARD_POS], int[][MAX_BOARD_POS], int[MAX_COLORS], int [MAX_COLORS], int, int, int*);
//Keeps track of the user's score
void scoreTrack(int, int[][MAX_GAMES], int, int, int*);
//Makes the file with the user's score
void filePrint(int[][MAX_GAMES], int, FILE*, char[STRING_SIZE]);

// definition of some strings: they cannot be changed when the program is executed !
const char myName[] = "Alexandre Rodrigues";
const char myNumber[] = "IST190002";
const int colors[3][MAX_COLORS] = {{255, 000, 051, 255, 255},{174, 102, 204, 036, 118},{003, 255, 051, 036, 100}};

/**
 * main function: entry point of the program
 * only to invoke other functions !
 */
int main( void )
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    TTF_Font *serif = NULL;
    TTF_Font *bigSerif = NULL;
    SDL_Surface *imgs[5];
    SDL_Event event;
    int delay = 300;
    int quit = 0;
    int width = (TABLE_SIZE + LEFT_BAR_SIZE);
    int height = TABLE_SIZE;
    int square_size_px = 0, board_size_px[2] = {0};
    int board_pos_x = 0, board_pos_y = 0;
    int board[MAX_BOARD_POS][MAX_BOARD_POS] = {{0}};
    int pt_x = 0, pt_y = 0;

    // Declaration of variables related to functionality
    //boards which store the player's selection
    //stores '1' in all the selected positions (useful for clearing the inside of squares)
    int selBoard[MAX_BOARD_POS][MAX_BOARD_POS] = {{0}};
    //stores the x and y coordinates of selected board entries (useful for checking the existence of squares)
    int selBoard2[2][MAX_SELBOARD_POS] = {{-1}};
    //parameters to configure the game
    int colorNum = 0;
    int objectives[MAX_COLORS] = {0};
    int moves = 0;
    char name[STRING_SIZE] = "";
    //informs whether the user is currently pressing down on the mouse
    int mouseDown = 0;
    //number of board entries already registered
    int currCount = 0;
    //code for use when clearing the board
    int valid = -1;
    //parameters to update as the game progresses
    int currObjectives[MAX_COLORS] = {0};
    int currMoves = 0;
    //these save the last game state
    int boardSave[MAX_BOARD_POS][MAX_BOARD_POS] = {{0}};
    int currObjectivesSave[MAX_COLORS] = {0};
    //stores 1 if the last move was reverted
    int undidLast = 0;
    //global parameters across all games
      //number of games
      int gameCount = 0;
      //[0] stores 1 if victory, 0 if defeat. [1] stores number of used moves if victory
      int gameScore[2][MAX_GAMES] = {{0}};
      //stores -1 if the current game ended in a loss, and 1 if in a victory
      int endConditions = 0;
      //stores 1 if the board needs shuffling
      int shuffle = 0;
    //time to hold the info on screen for
    int sleep = 0;
    //the file to which we will be writting the game statistics
    FILE *stats = NULL;
    //stores 1 if a play was made which changed the board, requiring the game to check for shuffles or game ends
    int gameUpdate = 0;
    //stores 1 if a game is currently running
    int gameRunning = 0;



    //random num gen initialization
    srand(1234);

    //Gather the game parameters
    gameConfig(&board_pos_x, &board_pos_y, &colorNum, objectives, &moves, name);

    // initialize graphics
    InitEverything(width, height, &serif, imgs, &window, &renderer, &bigSerif);



    while( quit == 0 )
    {
        // while there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            if( event.type == SDL_QUIT )
            {
                //quits the game
                quit = 1;
            }
            else if ( event.type == SDL_KEYDOWN )
            {
                switch ( event.key.keysym.sym )
                {
                    case SDLK_n:
                        if (gameRunning == 1){
                          printf("Game end!\n");
                          //registers a loss
                          scoreTrack(-1, gameScore, moves, currMoves, &gameCount);
                      }
                        newGame(board, board_pos_x, board_pos_y, colorNum, objectives, currObjectives, moves, &currMoves);
                        //when starting a new game, indicates that a new game is running and zeroes out the conditions for the last game's ending
                        gameRunning = 1;
                        endConditions = 0;
                          break;
                    case SDLK_q:
                        quit = 1;
                          break;
                    case SDLK_u:
                        if (gameRunning == 1){
                          //only undoes the last move if we have made at least one move, and one move after undoing
                          if (currMoves != moves && undidLast == 0){
                            restoreGameState(board, boardSave, currObjectives, currObjectivesSave, board_pos_x, board_pos_y, &currMoves);
                            //signals we can't undo next turn again
                            undidLast = 1;
                          }
                        }
                          break;
                    default:
                          break;
                }
            }
            else if ( event.type == SDL_MOUSEBUTTONDOWN )
            {
              if (gameRunning == 1){
                ProcessMouseEvent(event.button.x, event.button.y, board_size_px, square_size_px, &pt_x, &pt_y);
                printf("Button down: %d %d\n", pt_x, pt_y);
                //registers the input
                inputRegister(selBoard, selBoard2, pt_x, pt_y, &currCount);
                //indicates that we are HOLDING the mouse down
                mouseDown = 1;
              }
            }
            else if ( event.type == SDL_MOUSEBUTTONUP )
            {
              if (gameRunning == 1){
                ProcessMouseEvent(event.button.x, event.button.y, board_size_px, square_size_px, &pt_x, &pt_y);
                printf("Button up: %d %d\n", pt_x, pt_y);

                //checking to see if the play was valid and legal
                valid = inputVerify(board, selBoard2, currCount);
                if (valid != -1){
                  //saves the state of the game before altering anything (to possibly later undo this next move)
                  saveGameState(board, boardSave, currObjectives, currObjectivesSave, board_pos_x, board_pos_y);
                  //clearing the board and updating the score, as well as lowering the dots to ready the board for the next move
                  boardClear(board, selBoard, selBoard2, valid, currCount, board_pos_x, board_pos_y, currObjectives);
                  boardDown(board, board_pos_x, board_pos_y, colorNum, valid);
                  //subtracts one move from the current allowed moves
                  currMoves--;
                  //indicates the last move was a play, and not an undo (so as to let the user undo this last move)
                  undidLast = 0;
                  //indicates there was an update to the game, for use below
                  gameUpdate = 1;
                }

                //clearing the user input arrays
                inputClear(selBoard, selBoard2);

                //indicates we are no longer holding down on the mouse button
                mouseDown = 0;
                //resets the counter for the number of dots selected
                currCount = 0;
              }
            }
            else if ( event.type == SDL_MOUSEMOTION )
            {
              if (gameRunning == 1){
                ProcessMouseEvent(event.button.x, event.button.y, board_size_px, square_size_px, &pt_x, &pt_y);
                //printf("Moving Mouse: %d %d\n", pt_x, pt_y);
                if (mouseDown == 1)
                  //registers input
                  inputRegister(selBoard, selBoard2, pt_x, pt_y, &currCount);
              }
            }
        }

        // render game table
        square_size_px = RenderTable( board_pos_x, board_pos_y, board_size_px, serif, imgs, renderer, selBoard);

        // render board
        if (gameRunning == 1)
          RenderPoints(board, board_pos_x, board_pos_y, board_size_px, square_size_px, renderer);

        //if we made a move which requires the board to do the below operations
        if (gameUpdate == 1){
          // checking to see if the board needs shuffling, then shuffling it if so
          shuffle = shuffleVerify(board, board_pos_x, board_pos_y);
          if (shuffle == 1){
            boardShuffle(board, board_pos_x, board_pos_y);
            printf("Game info!\n");
          }

          //verifies if the game has ended
          // -1 if defeat, 1 if victory, 0 if the game keeps going
          endConditions = gameEndVerify(currObjectives, currMoves);
          //if a game ended, and a game is running, registers the conditions with which it ended in scoreTrack
          if (endConditions != 0 && gameRunning == 1){
            printf("Game end!\n");
            printf("Game info!\n");
            scoreTrack(endConditions, gameScore, moves, currMoves, &gameCount);
            //indicates the game ended
            gameRunning = 0;
          }
          //update is completed, so these functions don't need to be run again until the next one
          gameUpdate = 0;
        }

        //renders the game information about an event
        //if endConditions is 1, VICTORY is displayed, if it is -1, DEFEAT is displayed
        //if it is at zero, and the function still gets run, it means we are shuffling
        if (endConditions != 0 || shuffle == 1){
          RenderGameInfo(renderer, endConditions, imgs);
          //if a shuffle ocurred, adds a delay of 2 seconds to display the relevant information
          if (shuffle == 1)
            sleep = 2000;
          shuffle = 0;
        }

        // zeroes out currObjectives' indexes if they are negative
        for (int i = 0; i < colorNum; i++)
          if (currObjectives[i] < 0)
            currObjectives[i] = 0;

        // render score
        RenderStats(renderer, bigSerif, currObjectives, colorNum, currMoves);


        // render in the screen all changes above
        SDL_RenderPresent(renderer);
        //delay for when displaying a shuffle
        SDL_Delay(sleep);
        sleep = 0;
        // add a delay
        SDL_Delay( delay );
    }

    //register a loss when the user leaves the game
    if (gameRunning == 1)
      scoreTrack(-1, gameScore, moves, currMoves, &gameCount);

    // free memory allocated for images and textures and closes everything including fonts
    TTF_CloseFont(serif);
    TTF_CloseFont(bigSerif);
    for (int i = 0; i < 4; i++)
      SDL_FreeSurface(imgs[i]);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    stats = fopen("stats.txt", "w");

    if (stats == NULL){
      printf("ERROR! Could not open file!\n");
      return EXIT_FAILURE;
    }

    filePrint(gameScore, gameCount, stats, name);

    fclose(stats);

    return EXIT_SUCCESS;
}

/*
  gameConfig: reads the configuration parameters for the game
  the game is started after the parameters have been correctly input
  PARAMETERS:
    cols: Number of columns
    lines: Number of lines
    colorNum: Number of colors
    objectives: Array which stores the initially input target score
    moves: The number of allowed moves input initially
    name: The name the user inputs
*/
void gameConfig(int* cols, int* lines, int* colorNum, int objectives[MAX_COLORS], int* moves, char name[STRING_SIZE]){

  //string to store the input
  char buffer[STRING_SIZE] = "";

  printf("\n\nPlease insert the game parameters as they are requested.\n");

  //getting the columns
  do{
    printf("Columns (5-15): ");
    //getting the string
    fgets(buffer, STRING_SIZE, stdin);
    //retrieving the relevant values from the string
    sscanf(buffer, "%d", &*cols);
    //verification of the values' validity
    if(*cols < 3 || *cols > 15)
      printf("Value is not in the defined limits!\n");
    //clearing of the string
    buffer[0] = '\0';
  }while(*cols < 3 || *cols > 15);

  //getting the lines
  do{
    printf("Lines (5-15): ");
    fgets(buffer, STRING_SIZE, stdin);
    sscanf(buffer, "%d", &*lines);
    if(*lines < 3 || *lines > 15)
      printf("Value is not in the defined limits!\n");
    buffer[0] = '\0';
  }while(*lines < 3 || *lines > 15);

  //getting the number of colors
  do{
    printf("Colors (2-5): ");
    fgets(buffer, STRING_SIZE, stdin);
    sscanf(buffer, "%d", &*colorNum);
    if(*colorNum < 2 || *colorNum > 5)
      printf("Value is not in the defined limits!\n");
  }while(*colorNum < 2 || *colorNum > 5);

  //getting the target score for each color
  printf("Targets(1-99)...\n");
  for(int i = 0; i < *colorNum; i++){
    do{
      printf("Target [%d]: ", i+1);
      fgets(buffer, STRING_SIZE, stdin);
      sscanf(buffer, "%d", &objectives[i]);
      if(objectives[i] < 1 || objectives[i] > 99)
        printf("Value is not in the defined limits!\n");
      buffer[0] = '\0';
    }while(objectives[i] < 1 || objectives[i] > 99);
  }

  //getting the ammount of permited moves
  do{
    printf("Moves (1-99): ");
    fgets(buffer, STRING_SIZE, stdin);
    sscanf(buffer, "%d", &*moves);
    if(*moves < 1 || *moves > 99)
      printf("Value is not in the defined limits!\n");
    buffer[0] = '\0';
  }while(*moves < 1 || *moves > 99);

  //getting the player's name
  do{
    printf("Player name (8 characters max.): ");
    fgets(name, 50, stdin);
    //fgets counts '\n' as a character, so 8+1 characters should be the maximum
    if(strlen(name) > 9)
      printf("Name has too many characters!\n");
  }while(strlen(name) > 9);
}

/*
  newGame: Generates a new, random board, and resets the game parameters to those input initially
  PARAMETERS:
    board: The game board
    cols: Number of columns
    lines: Number of lines
    colorNum: Number of colors
    objectives: Array which stores the initially input target score
    currObjectives: The user's current score for each dot (same format as the above array)
    moves: The number of allowed moves input initially
    currMoves: The user's current moves
*/

void newGame (int board[][MAX_BOARD_POS], int cols, int lines, int colorNum, int objectives[MAX_COLORS], int currObjectives[MAX_COLORS],
              int moves, int* currMoves){

  //generating random entries for each of the board's indexes
  for (int i = 0; i < cols; i++)
    for (int j = 0; j < lines; j++)
      board[i][j] = getRandom(colorNum);

  //resetting the game parameters to match those input at the beggining
  for (int i = 0; i < MAX_COLORS; i++)
    currObjectives[i] = objectives[i];

  *currMoves = moves;

}

/*
  getRandom: Generates random entries for a single matrix entry
  executed when refilling the board's empy spots, and at the beggining of the game
  PARAMETERS:
    colorNum: Number of colors
*/

int getRandom (int colorNum){
  return (rand() % colorNum);
}

/*
  inputRegister: Registers the user's input
  puts '1' in selBoard's coordinates corresponding to the user's pointer
  puts the coordinates of the user's pointer, in order and with no repetition in selBoard2
  PARAMETERS:
    selBoard: array with the same size as the game board which stores '1' on the position corresponding to the selected dots
    selBoard2: 2 x 200 array which stores the x and y coords. corresponding to the selected dots in the order they are selected
    x: coordinate x of the cursor
    y: coordinate y of the cursor
    currCount: the count of dots we have currently selected. Is incremented in the function, and returned
*/

void inputRegister (int selBoard[][MAX_BOARD_POS], int selBoard2[][MAX_SELBOARD_POS], int x, int y, int* currCount){

  //if the pointer is out of the board, doesn't register
  if (x == -1 && y == -1)
    return;

  //if there is no previous input, registers the first without checking anything
  if (*currCount == 0){
    selBoard2[0][0] = x;
    selBoard2[1][0] = y;
    selBoard[x][y] = 1;
    (*currCount)++;
    return;
  }

  //if the last entry is the same as any other except for the previous 2 (meaning there is a square), doesn't register any further input
  for (int i = 0; i < *currCount-2; i++)
    if (selBoard2[0][*currCount-1] == selBoard2[0][i] && selBoard2[1][*currCount-1] == selBoard2[1][i])
        return;

  //if an attempted input is equal to the last two (last dot or the previous one), doesn't register
  for (int i = *currCount-2; i <= *currCount; i++) {
    if( (selBoard2[0][i] == x) && (selBoard2[1][i] == y) ){
      return;
    }
  }

  //checks wether the current input is adjacent to the last registered input (if so, writes)
  if (  ((selBoard2[0][*currCount-1] == (x+1)) && (selBoard2[1][*currCount-1] == y))
        ||
        ((selBoard2[0][*currCount-1] == (x-1)) && (selBoard2[1][*currCount-1] == y))
        ||
        ((selBoard2[0][*currCount-1] == x) && (selBoard2[1][*currCount-1] == (y+1)))
        ||
        ((selBoard2[0][*currCount-1] == x) && (selBoard2[1][*currCount-1] == (y-1)) )){
    selBoard[x][y] = 1;
    selBoard2[0][*currCount] = x;
    selBoard2[1][*currCount] = y;
    (*currCount)++;
    printf("count: %d\n", *currCount);
  }
}

/*
  inputVerify: verifies the legality of the user's move
  compares every entry of selBoard2 with the others, checking wether they are equal
  also checks for the existence of squares (by comparing the first and last entries of selBoard2)
  returns the following:
    -1 if illegal
     0 through 4 if legal AND square (corresponding to the color of the square)
     5 if legal, but NOT square
  PARAMETERS:
    board: the game board
    selBoard2: 2 x 200 array which stores the x and y coords. corresponding to the selected dots in the order they are selected
    currCount: the count of dots we have currently selected
*/

int inputVerify (int board[][MAX_BOARD_POS], int selBoard2[][MAX_SELBOARD_POS], int currCount){

  //makes sure the selection has more than one dot
  if (currCount <= 1){
    printf("Invalid!\n");
    return -1;
  }
  //verifies if all the selected entries have the same color
  //declares the move invalid otherwise
  for (int i = 0; i < currCount; i++)
    for (int j = 0; j < currCount; j++)
      if (board[selBoard2[0][i]][selBoard2[1][i]] != board[selBoard2[0][j]][selBoard2[1][j]]){
        printf("Invalid!\n");
        return -1;
      }

  //verifies if the last entry is the same as any previous one, indicating the presence of a square
  for (int i = 0; i < (currCount-2); i++)
    if (selBoard2[0][currCount-1] == selBoard2[0][i] && selBoard2[1][currCount-1] == selBoard2[1][i]){
      printf("Square!\n");
      return board [selBoard2[0][i]] [selBoard2[1][i]];
    }


  //if all other checks are false, it means it is valid, and just a simple line
  return 5;
}

/*
  ClearBoard: clears the board according to the validity of the player's move
  if square, deletes all the dots of the respective color and deletes the square's interior with the use of 'selBoard' for reference
  the algorithm for this is explained below in great detail
  if a normal selection, uses selBoard2 to delete said selection
  PARAMETERS:
    board: the game board
    selBoard: array with the same size as the game board which stores '1' on the position corresponding to the selected dots
    selBoard2: 2 x 200 array which stores the x and y coords. corresponding to the selected dots in the order they are selected
    valid: the validity and characteristic of the move. Explained in the above function. Here it is used to delete a specific color
            or just indicate we are deleting a line
    currCount: the count of dots we have currently selected
    x: number of columns
    y: number of lines
    currObjectives: The user's current score for each dot
*/

void boardClear (int board[][MAX_BOARD_POS], int selBoard[][MAX_BOARD_POS], int selBoard2[][MAX_SELBOARD_POS], int valid, int currCount,
                 int x, int y, int currObjectives[MAX_COLORS]){

  //counters for use when clearing the square's interior
  int up = 0, down = y;
  int left = 0, right = x;

  //auxiliary array to store the dots inside squares which will be deleted
  int auxBoard[MAX_BOARD_POS][MAX_BOARD_POS] = {{0}};

  //if (not a square)
  if (valid == 5){
    for (int i = 0; i < currCount; i++){
      //'board' stores the value of the color on each square
      //using its index value we decrement the objective of the color we are deleting
      currObjectives[ board[ selBoard2[0][i] ][ selBoard2[1][i] ] ]--;
      board[selBoard2[0][i]][selBoard2[1][i]] = -1;
    }
    return;
  }

  //if (a square)
  if (valid != 5){
    for (int i = 0; i < x; i++)
      for (int j = 0; j < y; j++)
        //if (it is the dot same color as the one we are deleting)
        if (board[i][j] == valid){
          currObjectives[board[i][j]]--;
          //deletes the dot
          board[i][j] = -1;
        }

    //this part below is to delete the inside of squares

    //cycles through the collumns
    for (int i = 0; i < x; i++){
      //cycles downward from the top of the board until the square's upper boundary is reached
      while (selBoard[i][up] != 1 && up < y)
        up++;
      //cycles upward from the bottom of the board until the square's lower boundary is reached
      while (selBoard[i][down] != 1 && down > 0)
        down--;

      // if (there is still some space between the boundaries)
      //(which means there is an interior to the square, and both boundaries aren't, for example, the same horizontal line)
      //cycles from the upper to the lower boundaries, marking the dots for deletion (they first need to be compared, howerver)
      while (up < down){
        auxBoard[i][up] += 1;
        up++;
      }
      up = 0;
      down = y;
    }

    //cycles through the lines
    for (int i = 0; i < y; i++){
      //cycles right from the left side of the board until the square's left boundary is reached
      while (selBoard[i][left] != 1 && left < x)
        left++;
      //cycles left from the right side of the board until the square's right boundary is reached
      while (selBoard[i][right] != 1 && right > 0)
        right--;

      // while (there is still some space between the boundaries)
      //cycles from the upper to the lower boundaries, marking the dots for deletion
      while (left < right){
        auxBoard[i][left] += 1;
        left++;
      }
      left = 0;
      right = x;
    }

    //checking the result from the last two processes, which consisted of a two step verification for the existence of squares
    //the dot is only deleted if the vertical and horizontal checkers BOTH mark it for deletion
    //this method prevents some possible bugs if the user made some complicated plays
    //admitedly, it can still be "tricked", but only if the user makes extremely impractical plays

    //cycles through the collumns
    for (int i = 0; i < x; i++)
      //cycles through the lines
      for (int j = 0; j < y; j++)
        //if (both processes marked the dot for deletion)
        if (auxBoard[i][j] == 2)
          if (board[i][j] != -1){
            currObjectives[ board[i][j] ]--;
            //deletes the corresponding dot
            board[i][j] = -1;
        }
  }
}

/*
  inputClear: resets the input arrays to their default states
  fills selBoard with '0' and selBoard2 with (-1, -1)
  PARAMETERS:
    selBoard: array with the same size as the game board which stores '1' on the position corresponding to the selected dots
    selBoard2: 2 x 200 array which stores the x and y coords. corresponding to the selected dots in the order they are selected
*/

void inputClear (int selBoard[][MAX_BOARD_POS], int selBoard2[][MAX_SELBOARD_POS]){

  for (int i = 0; i < MAX_BOARD_POS; i++)
    for (int j = 0; j < MAX_BOARD_POS; j++)
      selBoard[i][j] = 0;

  for (int i = 0; i < MAX_SELBOARD_POS; i++){
    selBoard2[0][i] = -1;
    selBoard2[1][i] = -1;
  }
}

/*
  boardDown: lowers all the board's columns, filling the empty spaces with the dots above
  generates new dots on the top of the board, if those spots are empty
  PARAMETERS:
    board: the game board
    x: the number of columns
    y: the number of lines
    colorNum: the number of colors
    valid: in this case, the color of the square which was deleted

*/

void boardDown (int board[][MAX_BOARD_POS], int x, int y, int colorNum, int valid){

  //the ammount of empty spots in each of the columns
  int emptyCount = 0;

  for (int i = 0; i < x; i++){
    //analyses the column, counting the "empty" entries
    for (int j = 0; j < y; j++)
      if (board[i][j] == -1)
        emptyCount++;

    //repeats the operation for the number of "empty" entries in the column
    for (int repeats = 0; repeats < emptyCount; repeats++){
      //from the bottom of the board up
      for (int b = y; b > 0; b--)
        //if we find an empty spot
        if (board[i][b] == -1){
          //pull the dot above into the empty spot
          board[i][b] = board[i][b-1];
          //delete the dot above
          board[i][b-1] = -1;
        }

        //while (the top spot if the column is empty, or the color generated for it is the same as the one deleted when making a square)
        while (board[i][0] == valid || board[i][0] == -1)
          //generate a new random dot
          board[i][0] = getRandom(colorNum);

    }
    //resets the empty spot counter when cycling to the next columns
    emptyCount = 0;
  }
}

/*
  saveGameState: Saves the current state of the game, for it to possible be restored
  PARAMETERS:
    board: the game board
    boardSave: the board to which we will be saving 'board'
    currObjectives: The user's current score for each dot
    currObjectivesSave: the array to which we will be saving the one above
    x: number of columns
    y: number of lines
*/

void saveGameState(int board[][MAX_BOARD_POS], int boardSave[][MAX_BOARD_POS], int currObjectives[MAX_COLORS],
   int currObjectivesSave[MAX_COLORS], int x, int y){

  //saving the game board
  for (int i = 0; i < x; i++)
    for (int j = 0; j < y; j++)
      boardSave[i][j] = board[i][j];

  //saving the score
  for (int i = 0; i < MAX_COLORS; i++)
    currObjectivesSave[i] = currObjectives[i];

}

/*
  restoreGameState: Restores the state of the game before the last move
  PARAMETERS:
    board: the game board
    boardSave: the saved board used to restore the game board
    currObjectives: The user's current score for each dot
    currObjectivesSave: the array used to restore the current objectives
    x: number of columns
    y: number of lines
    currMoves: the number of moves the user has left. It is incremented and returned
*/

void restoreGameState(int board[][MAX_BOARD_POS], int boardSave[][MAX_BOARD_POS], int currObjectives[MAX_COLORS],
   int currObjectivesSave[MAX_COLORS], int x, int y, int* currMoves){

  //restoring the game board
  for (int i = 0; i < x; i++)
    for (int j = 0; j < y; j++)
      board[i][j] = boardSave[i][j];

  //restoring the score
  for (int i = 0; i < MAX_COLORS; i++)
    currObjectives[i] = currObjectivesSave[i];

  //restoring the current moves left
  (*currMoves)++;

  }

/*
  shuffleVerify: verifies is there is any possible play by the user left
  verifies if there are any simmilarly colored dots adjacent to any of the dots on the board
  the return value is used to decide wether or not a shuffle is made.
  PARAMETERS:
    board: the game board
    x: number of columns
    y: number of lines
*/

int shuffleVerify (int board[][MAX_BOARD_POS], int x, int y){

  //by default we shuffle the board
  //it's easier to check if there IS a play left to make
  int shuffle = 1;

  //next, we check if there is a move left. if there is, we do not shuffle the board
  for (int i = 0; i < x; i++)
    for (int j = 0; j < y; j++)
      //if any one dot has an adjacent dot of the same color
      if (  (board[i][j] == board[i+1][j] && i != x-1)
          ||(board[i][j] == board[i-1][j] && i != 0)
          ||(board[i][j] == board[i][j+1] && j != y-1)
          ||(board[i][j] == board[i][j-1] && j != 0) )
            {
              shuffle = 0;
              return shuffle;
            }

  printf("Shuffle!\n");
  return shuffle;
}

/*
  boardShuffle: shuffles the entries in the game board
  switches two indexes' values a 'lines * columns' number of times
  this means every entry is shuffled at least once
  PARAMETERS:
    board: the game board
    x: number of columns
    y: number of lines
*/

void boardShuffle (int board[][MAX_BOARD_POS], int x, int y){

  //where we temporarily store a switched value
  int temp = 0;
  //where we store the index with which we switch values
  int switchIndex[2] = {0};

  //cycles through columns and lines
  for (int i = 0; i < x; i++)
    for (int j = 0; j < y; j++){
      //generates a random x coordinate
      switchIndex[0] = rand() % (x+1);
      //generates a random y coordinate
      switchIndex[1] = rand() % (y+1);

      //switches the value of index [i][j] with the randomly generated index
      temp = board[i][j];
      board[i][j] = board[switchIndex[0]][switchIndex[1]];
      board[switchIndex[0]][switchIndex[1]] = temp;
    }
}

/*
  gameEndVerify: Verifies if the game ended
  returns 1 if victory, and -1 if defeat (0 if the game is still going)
  PARAMETERS:
    currObjectives: The user's current score for each dot
    currMoves: The number of available moves the user has left
*/

int gameEndVerify (int currObjectives[MAX_COLORS], int currMoves){

  //we assume the user has won the game
  int objectivesFinished = 1;

  //verifies if there is at least one objective which is not finished
  for (int i = 0; i < MAX_COLORS; i++)
    if (currObjectives[i] > 0)
      //the user hasn't won the game
      objectivesFinished = 0;

  //if we finished out objectives (this includes finishing with no moves)
  if (objectivesFinished == 1)
    //win
    return 1;

  //if we didn't finish the objectives, and exhausted all our moves
  if (currMoves == 0)
    //loss
    return -1;

  //if we didn't finish the objectives, and still have moves left
  //game keeps going
  return 0;
}

/*
  scoreTrack: Keeps track of the user score, for later use when writting it to the file
  increments the game counter
  PARAMETERS:
    endConditions: 1 if victory, -1 if defeat
    gameScore: the array to which we store the user's score across all games
    moves: the total allowed moves
    currMoves: The number of available moves the user has left
    gameCount: the counter for the ammount of games made
*/

void scoreTrack(int endConditions, int gameScore[][MAX_GAMES], int moves, int currMoves, int* gameCount){

  //index (0, game number) stores victory or defeat
  gameScore[0][*gameCount] = endConditions;
  //index (1, game number) stores the moves the user expended
  gameScore[1][*gameCount] = (moves - currMoves);

  //increments the game counter
  (*gameCount)++;

}

/**
 * ProcessMouseEvent: gets the square pos based on the click positions !
 * \param _mouse_pos_x position of the click on pixel coordinates
 * \param _mouse_pos_y position of the click on pixel coordinates
 * \param _board_size_px size of the board !
 * \param _square_size_px size of each square
 * \param _pt_x square nr
 * \param _pt_y square nr
 */
void ProcessMouseEvent(int _mouse_pos_x, int _mouse_pos_y, int _board_size_px[], int _square_size_px,
        int *_pt_x, int *_pt_y )
{

    int circleX = 0, circleY = 0, circleR = 0;

    int dist = 0;

    int sqrX = 0, sqrY = 0;
    // corner of the board
    int x_corner = (TABLE_SIZE - _board_size_px[0]) >> 1;
    int y_corner = (TABLE_SIZE - _board_size_px[1] - 15);

    // verify if valid cordinates
    if (_mouse_pos_x < x_corner || _mouse_pos_y < y_corner || _mouse_pos_x > (x_corner + _board_size_px[0])
        || _mouse_pos_y > (y_corner + _board_size_px[1]) )
    {
        *_pt_x = -1;
        *_pt_y = -1;
        return;
    }

    //computes which square we are mousing over
    sqrX = (_mouse_pos_x - x_corner) / (_square_size_px + SQUARE_SEPARATOR);
    sqrY = (_mouse_pos_y - y_corner) / (_square_size_px + SQUARE_SEPARATOR);

    //computes the square's center, and circle radius
    circleX = x_corner + (sqrX+1)*SQUARE_SEPARATOR + sqrX*(_square_size_px)+(_square_size_px>>1);
    circleY = y_corner + (sqrY+1)*SQUARE_SEPARATOR + sqrY*(_square_size_px)+(_square_size_px>>1);
    circleR = (int)(_square_size_px*0.4f);

    //computes the distance to the circle's center
    dist = (int)floor( sqrt( SQR((_mouse_pos_x - circleX)) + SQR(_mouse_pos_y - circleY) ) );

    //if (the mouse is inside the circle)
    if (dist < circleR){
      //set the coordinates to the circle's respective square
      *_pt_x = sqrX;
      *_pt_y = sqrY;
    }
    else{
      //otherwise, set them as invalid
      *_pt_x = -1;
      *_pt_y = -1;
    }
}

/**
 * RenderPoints: renders the board
 * \param _board 2D array with integers representing board colors
 * \param _board_pos_x number of positions in the board (x axis)
 * \param _board_pos_y number of positions in the board (y axis)
 * \param _square_size_px size of each square
 * \param _board_size_px size of the board
 * \param _renderer renderer to handle all rendering in a window
 */
void RenderPoints(int _board[][MAX_BOARD_POS], int _board_pos_x, int _board_pos_y,
        int _board_size_px[], int _square_size_px, SDL_Renderer *_renderer )
{
    int clr, x_corner, y_corner, circleX, circleY, circleR;

    // corner of the board
    x_corner = (TABLE_SIZE - _board_size_px[0]) >> 1;
    y_corner = (TABLE_SIZE - _board_size_px[1] - 15);

    // renders the squares where the dots will appear
    for ( int i = 0; i < _board_pos_x; i++ )
    {
        for ( int j = 0; j < _board_pos_y; j++ )
        {
                // define the size and copy the image to display
                circleX = x_corner + (i+1)*SQUARE_SEPARATOR + i*(_square_size_px)+(_square_size_px>>1);
                circleY = y_corner + (j+1)*SQUARE_SEPARATOR + j*(_square_size_px)+(_square_size_px>>1);
                circleR = (int)(_square_size_px*0.4f);
                // draw a circle
                clr = _board[i][j];
                filledCircleRGBA(_renderer, circleX, circleY, circleR, colors[0][clr], colors[1][clr], colors[2][clr]);
        }
    }
}

/**
 * filledCircleRGBA: renders a filled circle
 * \param _circleX x pos
 * \param _circleY y pos
 * \param _circleR radius
 * \param _r red
 * \param _g gree
 * \param _b blue
 */
void filledCircleRGBA(SDL_Renderer * _renderer, int _circleX, int _circleY, int _circleR, int _r, int _g, int _b)
{
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

/*
 * Shows some information about the game:
 * - Goals of the game
 * - Number of moves
 * \param _renderer renderer to handle all rendering in a window
 * \param _font font to display the scores
 *  PARAMETERS:
 *    currObjectives: The user's current score for each dot
 *    colorNum: number of colors
 *    currMoves: the number of moves left
 */
void RenderStats( SDL_Renderer *_renderer, TTF_Font *_font, int currObjectives[], int colorNum, int currMoves)
{
  //colors
  SDL_Color light = { 205, 205, 205, 105 };
  SDL_Color black = { 0, 0, 0, 255};
  //squares for the score and the moves left
  SDL_Rect scoreRect, movesRect;
  //the string which will be written
  char num[STRING_SIZE] = "";

  scoreRect.x = RECT_MARGIN + ( (5-colorNum)*(RECT_MARGIN + RECT_W) ) / 2;
  scoreRect.y = 2 * RECT_MARGIN;
  scoreRect.w = RECT_W;
  scoreRect.h = RECT_H;

  movesRect.x = RECT_MARGIN + (4*(RECT_MARGIN + RECT_W) ) / 2;
  movesRect.y = 2 * RECT_MARGIN + RECT_H + 15;
  movesRect.w = RECT_W;
  movesRect.h = RECT_H;

  //generates one score rectangle for each color we are playing with
  for (int i = 0; i < colorNum; i++){
    //color for the rectangle
    SDL_SetRenderDrawColor(_renderer, light.r, light.g, light.b, light.a);
    //drawing the rectangle
    SDL_RenderFillRect(_renderer, &scoreRect);
    //drawing the circle of the respective color
    filledCircleRGBA(_renderer, scoreRect.x + RECT_CIRCLE_MARGIN, scoreRect.y + RECT_CIRCLE_MARGIN, RECT_CIRCLE_R, colors[0][i],  colors[1][i],  colors[2][i]);
    //printing our current objective for the respective color into a string
    sprintf(num, "%d", currObjectives[i]);
    //renders said string
    RenderText(scoreRect.x + 45, scoreRect.y, num, _font, &black, _renderer);
    //clears the string
    num[0] = '\0';
    //increments the position for the next rect to be drawn in
    scoreRect.x += RECT_MARGIN + RECT_W;
  }

  //generates the rectangle for the moves
  //color for the rectangle
  SDL_SetRenderDrawColor(_renderer, light.r, light.g, light.b, light.a);
  //drawing the rectangle
  SDL_RenderFillRect(_renderer, &movesRect);
  //printing the current moves
  sprintf(num, "%d", currMoves);
  //rendering the moves
  RenderText(movesRect.x + 35, movesRect.y, num, _font, &black, _renderer);
}

/*
 * RenderTable: Draws the table where the game will be played, namely:
 * -  some texture for the background
 * -  the right part with the IST logo and the student name and number
 * -  the grid for game board with squares and seperator lines
 * \param _board_pos_x number of positions in the board (x axis)
 * \param _board_pos_y number of positions in the board (y axis)
 * \param _board_size_px size of the board
 * \param _font font used to render the text
 * \param _img surfaces with the table background and IST logo (already loaded)
 * \param _renderer renderer to handle all rendering in a window
 *  PARAMETERS:
 *    selBoard: array with the same size as the game board which stores '1' on the position corresponding to the selected dots
 */
int RenderTable( int _board_pos_x, int _board_pos_y, int _board_size_px[],
        TTF_Font *_font, SDL_Surface *_img[], SDL_Renderer* _renderer, int selBoard[][MAX_BOARD_POS])
{
    SDL_Color black = { 0, 0, 0 }; // black
    SDL_Color light = { 205, 205, 205 };
    SDL_Color dark = { 120, 110, 102 };
    SDL_Color highlight = { 61, 61, 61 };
    SDL_Texture *table_texture;
    SDL_Rect tableSrc, tableDest, board, board_square;
    int height, board_size, square_size_px, max_pos;

    // set color of renderer to some color
    SDL_SetRenderDrawColor( _renderer, 255, 255, 255, 255 );

    // clear the window
    SDL_RenderClear( _renderer );

    tableDest.x = tableSrc.x = 0;
    tableDest.y = tableSrc.y = 0;
    tableSrc.w = _img[0]->w;
    tableSrc.h = _img[0]->h;
    tableDest.w = TABLE_SIZE;
    tableDest.h = TABLE_SIZE;

    // draws the table texture
    table_texture = SDL_CreateTextureFromSurface(_renderer, _img[0]);
    SDL_RenderCopy(_renderer, table_texture, &tableSrc, &tableDest);

    // render the IST Logo
    height = RenderLogo(TABLE_SIZE, 0, _img[1], _renderer);

    // render the student name
    height += RenderText(TABLE_SIZE+3*MARGIN, height, myName, _font, &black, _renderer);

    // this renders the student number
    RenderText(TABLE_SIZE+3*MARGIN, height, myNumber, _font, &black, _renderer);

    // compute and adjust the size of the table and squares
    max_pos = MAX(_board_pos_x, _board_pos_y);
    board_size = (int)(BOARD_SIZE_PER*TABLE_SIZE);
    square_size_px = (board_size - (max_pos+1)*SQUARE_SEPARATOR) / max_pos;
    _board_size_px[0] = _board_pos_x*(square_size_px+SQUARE_SEPARATOR)+SQUARE_SEPARATOR;
    _board_size_px[1] = _board_pos_y*(square_size_px+SQUARE_SEPARATOR)+SQUARE_SEPARATOR;

    // renders the entire board background
    SDL_SetRenderDrawColor(_renderer, dark.r, dark.g, dark.b, dark.a );
    board.x = (TABLE_SIZE - _board_size_px[0]) >> 1;
    board.y = (TABLE_SIZE - _board_size_px[1] - 15);
    board.w = _board_size_px[0];
    board.h = _board_size_px[1];
    SDL_RenderFillRect(_renderer, &board);

    // renders the squares where the numbers will appear
    SDL_SetRenderDrawColor(_renderer, light.r, light.g, light.b, light.a );

    // iterate over all squares
    for ( int i = 0; i < _board_pos_x; i++ )
    {
        for ( int j = 0; j < _board_pos_y; j++ )
        {
            //if (the square corresponds to a selected dot)
            if (selBoard[i][j] == 1)
              //change the square's color to highlight the move
              SDL_SetRenderDrawColor(_renderer, highlight.r, highlight.g, highlight.b, highlight.a);
            board_square.x = board.x + (i+1)*SQUARE_SEPARATOR + i*square_size_px;
            board_square.y = board.y + (j+1)*SQUARE_SEPARATOR + j*square_size_px;
            board_square.w = square_size_px;
            board_square.h = square_size_px;
            SDL_RenderFillRect(_renderer, &board_square);
            //change the color back to the default
            SDL_SetRenderDrawColor(_renderer, light.r, light.g, light.b, light.a );
        }
    }

    // destroy everything
    SDL_DestroyTexture(table_texture);
    // return for later use
    return square_size_px;
}

/*
  RenderGameInfo: Renders the 3 game info displays
  victory, defeat or shuffle, depending endConditions and shuffle
  PARAMETERS:
    renderer: the SDL renderer
    endConditions: -1 if defeat, 1 if victory. In this context, if it is 0 we display a shuffle
    imgs[]: the images to be displayed
*/

void RenderGameInfo(SDL_Renderer* renderer, int endConditions, SDL_Surface* imgs[]){

  //what we will be rendering
  SDL_Texture *info;
  //the square representing the image size
  SDL_Rect boardPos;

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  //position and space occupied by the image
  boardPos.x = 185;
  boardPos.y = 250;
  boardPos.w = imgs[2]->w;
  boardPos.h = imgs[2]->h;

  //render one of the images
  if (endConditions == 1){
    //victory
    info = SDL_CreateTextureFromSurface(renderer, imgs[2]);
    SDL_RenderCopy(renderer, info, NULL, &boardPos);
  }
  else if (endConditions == -1){
    //defeat
    info = SDL_CreateTextureFromSurface(renderer, imgs[3]);
    SDL_RenderCopy(renderer, info, NULL, &boardPos);
  }
  else{
    //shuffle
    info = SDL_CreateTextureFromSurface(renderer, imgs[4]);
    SDL_RenderCopy(renderer, info, NULL, &boardPos);
  }

  //destroy the texture
  SDL_DestroyTexture(info);

}

/**
 * RenderLogo function: Renders the IST logo on the app window
 * \param x X coordinate of the Logo
 * \param y Y coordinate of the Logo
 * \param _logoIST surface with the IST logo image to render
 * \param _renderer renderer to handle all rendering in a window
 */

int RenderLogo(int x, int y, SDL_Surface *_logoIST, SDL_Renderer* _renderer)
{
    SDL_Texture *text_IST;
    SDL_Rect boardPos;

    // space occupied by the logo
    boardPos.x = x;
    boardPos.y = y;
    boardPos.w = _logoIST->w;
    boardPos.h = _logoIST->h;

    // render it
    text_IST = SDL_CreateTextureFromSurface(_renderer, _logoIST);
    SDL_RenderCopy(_renderer, text_IST, NULL, &boardPos);

    // destroy associated texture !
    SDL_DestroyTexture(text_IST);
    return _logoIST->h;
}

/**
 * RenderText function: Renders some text on a position inside the app window
 * \param x X coordinate of the text
 * \param y Y coordinate of the text
 * \param text string with the text to be written
 * \param _font TTF font used to render the text
 * \param _color color of the text
 * \param _renderer renderer to handle all rendering in a window
 */
int RenderText(int x, int y, const char *text, TTF_Font *_font, SDL_Color *_color, SDL_Renderer* _renderer)
{
    SDL_Surface *text_surface;
    SDL_Texture *text_texture;
    SDL_Rect solidRect;

    solidRect.x = x;
    solidRect.y = y;
    // create a surface from the string text with a predefined font
    text_surface = TTF_RenderText_Blended(_font,text,*_color);
    if(!text_surface)
    {
        printf("TTF_RenderText_Blended: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    // create texture
    text_texture = SDL_CreateTextureFromSurface(_renderer, text_surface);
    // obtain size
    SDL_QueryTexture( text_texture, NULL, NULL, &solidRect.w, &solidRect.h );
    // render it !
    SDL_RenderCopy(_renderer, text_texture, NULL, &solidRect);
    // clear memory
    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text_surface);
    return solidRect.h;
}

/**
 * InitEverything: Initializes the SDL2 library and all graphical components: font, window, renderer
 * \param width width in px of the window
 * \param height height in px of the window
 * \param _font font that will be used to render the text
 * \param _img surface to be created with the table background and IST logo, as well as the informative screens (WIN, LOSS, SHUFFLE)
 * \param _window represents the window of the application
 * \param _renderer renderer to handle all rendering in a window
 */
void InitEverything(int width, int height, TTF_Font **_font, SDL_Surface *_img[], SDL_Window** _window, SDL_Renderer** _renderer, TTF_Font **_font2)
{
    InitSDL();
    InitFont();
    *_window = CreateWindow(width, height);
    *_renderer = CreateRenderer(width, height, *_window);

    // load the table texture
    _img[0] = IMG_Load("table_texture.png");
    if (_img[0] == NULL)
    {
        printf("Unable to load image: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // load IST logo
    _img[1] = SDL_LoadBMP("ist_logo.bmp");
    if (_img[1] == NULL)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // load victory screen
    _img[2] = IMG_Load("VICTORY.png");
    if (_img[2] == NULL)
    {
        printf("Unable to load png: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    //load defeat screen
    _img[3] = IMG_Load("DEFEAT.png");
    if (_img[3] == NULL)
    {
        printf("Unable to load png: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    //load shuffle screen
    _img[4] = IMG_Load("SHUFFLE.png");
    if (_img[4] == NULL)
    {
        printf("Unable to load png: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // this opens (loads) a font file and sets a size
    *_font = TTF_OpenFont("FreeSerif.ttf", 16);
    if(!*_font)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    *_font2 = TTF_OpenFont("OpenSans.ttf", 32);
    if(!*_font)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
}

/**
 * InitSDL: Initializes the SDL2 graphic library
 */
void InitSDL()
{
    // init SDL library
    if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        printf(" Failed to initialize SDL : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

/**
 * InitFont: Initializes the SDL2_ttf font library
 */
void InitFont()
{
    // Init font library
    if(TTF_Init()==-1)
    {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
}

/**
 * CreateWindow: Creates a window for the application
 * \param width width in px of the window
 * \param height height in px of the window
 * \return pointer to the window created
 */
SDL_Window* CreateWindow(int width, int height)
{
    SDL_Window *window;
    // init window
    window = SDL_CreateWindow( "ISTDots", WINDOW_POSX, WINDOW_POSY, width, height, 0 );
    // check for error !
    if ( window == NULL )
    {
        printf("Failed to create window : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    return window;
}

/**
 * CreateRenderer: Creates a renderer for the application
 * \param width width in px of the window
 * \param height height in px of the window
 * \param _window represents the window for which the renderer is associated
 * \return pointer to the renderer created
 */
SDL_Renderer* CreateRenderer(int width, int height, SDL_Window *_window)
{
    SDL_Renderer *renderer;
    // init renderer
    renderer = SDL_CreateRenderer( _window, -1, 0 );

    if ( renderer == NULL )
    {
        printf("Failed to create renderer : %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // set size of renderer to the same as window
    SDL_RenderSetLogicalSize( renderer, width, height );

    return renderer;
}

/*
  filePrint: Prints the user statistics to the file at the end of the game
    PARAMETERS:
      gameScore: array to store the score across all games
      gameCount: the number of games played
      stats: the file pointer
      name: the name input by the user
*/
void filePrint(int gameScore[][MAX_GAMES], int gameCount, FILE* stats, char name[STRING_SIZE]){

  //cutting the '\n' character from the string
  name = strtok(name, "\n");
  int wins = 0;
  int losses = 0;

  //counting the wins and losses
  for (int i = 0; i < gameCount; i++){
    if (gameScore[0][i] == 1)
      wins++;
    else
      losses++;
  }

  fprintf(stats, "Game statistics for user %s:\n\n", name);
  fprintf(stats, "Number of games: %d games, %d wins and %d losses\n", gameCount, wins, losses);

  //printing the result for each individual game, as well as the moves used in case the user won
  for (int i = 0; i < gameCount; i++){
    if (gameScore[0][i] == 1)
      fprintf(stats, "Game %d: Win  | Moves used: %d \n", i + 1, gameScore[1][i]);
    else
      fprintf(stats, "Game %d: Loss \n", i + 1);

  }
}
