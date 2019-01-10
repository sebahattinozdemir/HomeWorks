/* Explanations *************************************************************************************************************************************
|
| - The dungeon consists of a "start" room, an "exit" room, one room with "gold", one or more rooms with "wumpuses", and zero or more empty rooms.
| - "Start" and "exit" rooms are empty.
| - Other rooms can be empty, or can contain only a single entity (either gold, or wumpus). A room cannot contain more than one entities.
| - At the beginning of the game, the player sets the total number of rooms, and also the number of wumpuses.
| - Player starts in room "start".
| - All rooms are magical, and they all have 2 doors.
| - Doors might appear randomly in North, East, South or West directions.
| - Doors lead to randomly selected other rooms.
| - If the player visits the room with the gold, the player grabs the gold.
| - If the player visits a room with a wumpus in it, the wumpus eats the player, and the game finishes.
| - If the player visits the "exit" room, the game finishes. If the player has the gold with her, this is a successful finish.
|
****************************************************************************************************************************************************/




/* Includes ****************************************************************************************************************************************/

#include "Utilities.h"

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>   /* For standard input/output functions */

/***************************************************************************************************************************************************/




/* Definitions *************************************************************************************************************************************/

#define AUTHOR       ( "Selim Temizer" )  /* Author's name                                                                   */

#define MIN_ROOMS    (  2              )  /* Minimum number of magical rooms in the dungeon (excluding start and exit rooms) */
#define MAX_ROOMS    (  8              )  /* Maximum number of magical rooms in the dungeon (excluding start and exit rooms) */
#define MIN_WUMPUSES (  1              )  /* Minimum number of wumpuses in the dungeon                                       */
#define MAX_WUMPUSES (  4              )  /* Maximum number of wumpuses in the dungeon                                       */

#define START        ( 'S'             )  /* Label for the start room                                                        */
#define EXIT         ( 'X'             )  /* Label for the exit room                                                         */
#define GOLD         ( 'G'             )  /* Label for the single room containing the gold                                   */
#define WUMPUS       ( 'W'             )  /* Label for room(s) containing a wumpus                                           */
#define EMPTY        ( 'E'             )  /* Label for empty room(s)                                                         */

/***************************************************************************************************************************************************/




/* Type Definitions ********************************************************************************************************************************/

typedef unsigned char boolean ;

/***************************************************************************************************************************************************/




/* Global Variables ********************************************************************************************************************************/

int     numberOfMagicalRooms                            ;
int     numberOfWumpuses                                ;
int     currentRoomNo                                   ;
boolean playerFoundGold                                 ;
char    r0 , r1 , r2 , r3 , r4 , r5 , r6 , r7 , r8 , r9 ; /* r0 is start room, r1 is exit room, others are magical rooms (at most 8 magical rooms) */

/***************************************************************************************************************************************************/




/* Helper (Minor) Functions ************************************************************************************************************************/

/* The input is the room number, and the return value is the label for the room. */

char getRoomInformation ( int roomNo )
{
  switch ( roomNo )
  {
    default :
    case 0  : return r0 ;
    case 1  : return r1 ;
    case 2  : return r2 ;
    case 3  : return r3 ;
    case 4  : return r4 ;
    case 5  : return r5 ;
    case 6  : return r6 ;
    case 7  : return r7 ;
    case 8  : return r8 ;
    case 9  : return r9 ;
  }
}

/*=================================================================================================================================================*/

/* The input is the room label. The function prints out the information associated with the label. */

void printRoomInformation1 ( char room )
{
  switch ( room )
  {
    case START  : printf( "START"  ) ;  break ;
    case EXIT   : printf( "EXIT"   ) ;  break ;
    case GOLD   : printf( "GOLD"   ) ;  break ;
    case WUMPUS : printf( "WUMPUS" ) ;  break ;
    case EMPTY  : printf( "EMPTY"  ) ;  break ;
  }
}

/*=================================================================================================================================================*/

/* The input is the room number. The function prints out the information associated with the room. */

void printRoomInformation2 ( int roomNo )
{
  switch ( roomNo )
  {
    case 0 : printRoomInformation1( r0 ) ;  break ;
    case 1 : printRoomInformation1( r1 ) ;  break ;
    case 2 : printRoomInformation1( r2 ) ;  break ;
    case 3 : printRoomInformation1( r3 ) ;  break ;
    case 4 : printRoomInformation1( r4 ) ;  break ;
    case 5 : printRoomInformation1( r5 ) ;  break ;
    case 6 : printRoomInformation1( r6 ) ;  break ;
    case 7 : printRoomInformation1( r7 ) ;  break ;
    case 8 : printRoomInformation1( r8 ) ;  break ;
    case 9 : printRoomInformation1( r9 ) ;  break ;
  }
}

/*=================================================================================================================================================*/

/* The input is the direction. The function prints out the direction as a word, as an acronym and also displays an arrowhead. */

void printDirection ( int direction )
{
  switch ( direction )
  {
    case 0 : printf( "NORTH (N) ^" ) ;  break ;
    case 1 : printf( "EAST (E) >"  ) ;  break ;
    case 2 : printf( "SOUTH (S) v" ) ;  break ;
    case 3 : printf( "WEST (W) <"  ) ;  break ;
  }
}

/***************************************************************************************************************************************************/




/* Functions ***************************************************************************************************************************************/

/* Prints a banner including the author name. */

void printBanner ( void )
{
  /* TODO */
  /* ...  */
  printf("\n*******************************************************************************\n");
  printf("* Dungeons and Dragons with Wumpuses                                          *\n");
  printf("* by Selim Temizer                                                            *\n");
  printf("*******************************************************************************\n");

}

/*=================================================================================================================================================*/

/* Initializes all global variables.                                                                                    */
/* The number of magical rooms and the number of wumpuses are set by the player as part of the configuration process.   */
/* All possible errors in input should be handled by clearing the input buffer and asking the user again for the input. */

void configureWorld ( void )
{
  /* TODO */
  /* ...  */
  printf("\nLet's configure the DnDW World first!\n");

  do{
    printf("Enter number of magical rooms [2,8] : ");
    scanf("%d", &numberOfMagicalRooms);
    getchar();
    if(numberOfMagicalRooms > 8 || numberOfMagicalRooms < 2)
      printf("Incorrect input! Please try again.\n");
  }while(numberOfMagicalRooms > 8 || numberOfMagicalRooms < 2);


  do{
    printf("Enter number of wumpuses [1,4]      : ");
    scanf("%d", &numberOfWumpuses);
    getchar();
    if(numberOfWumpuses > 4 || numberOfWumpuses < 1 || numberOfWumpuses >= numberOfMagicalRooms)
      printf("Incorrect input! Please try again.\n");
  }while(numberOfWumpuses > 4 || numberOfWumpuses < 1 || numberOfWumpuses >= numberOfMagicalRooms);

  r0 = START ;
  r1 = EXIT  ;
  r2 = GOLD  ;
  switch(numberOfWumpuses){
    case 1:
      r3 = WUMPUS;
      r4 = EMPTY;
      r5 = EMPTY;
      r6 = EMPTY;
      r7 = EMPTY;
      r8 = EMPTY;
    break;
    case 2:
      r3 = WUMPUS;
      r4 = WUMPUS;
      r5 = EMPTY;
      r6 = EMPTY;
      r7 = EMPTY;
      r8 = EMPTY;
    break;
    case 3:
      r3 = WUMPUS;
      r4 = WUMPUS;
      r5 = WUMPUS;
      r6 = EMPTY;
      r7 = EMPTY;
      r8 = EMPTY;
    break;
    case 4:
      r3 = WUMPUS;
      r4 = WUMPUS;
      r5 = WUMPUS;
      r6 = WUMPUS;
      r7 = EMPTY;
      r8 = EMPTY;
    break;
  }

  playerFoundGold = 0;
  currentRoomNo = 0;
  /*printf("wumpuses : %d and magical rooms : %d\n", numberOfWumpuses, numberOfMagicalRooms);*/
  printf("Configuration is finished. Good luck with the game play!\n\n");
}

/*=================================================================================================================================================*/

/* Prints the configured world. */

void printWorld ( void )
{
  /* TODO */
  /* ...  */
  /*
  int i;
  printf("DnD World:\n----------\nRoom 0 : START\nRoom 1 : EXIT\nRoom 2 : GOLD\n");
  for(i=3;i<numberOfWumpuses+3;i++)
    printf("Room %d : WUMPUS\n", i);

  for(i=i; i< numberOfMagicalRooms+2; i++)
    printf("Room %d : EMPTY\n", i);
  */

  int i;
  printf("DnD World:\n----------\n");
  for(i=0;i<numberOfMagicalRooms+2;i++){
    printf("Room %d : ",i);
    printRoomInformation2(i);
    printf("\n");
  }

}

/*=================================================================================================================================================*/

/* Prints the current room information and the doors of the current room.                                               */
/* Gets player's door choice as one of 'N', 'E', 'S', 'W' (small letters should also be accepted).                      */
/* All possible errors in input should be handled by clearing the input buffer and asking the user again for the input. */
/* Prints where the doors were actually opening to.                                                                     */
/* Updates current room number.                                                                                         */
/* If the current room contains gold, lets the player know that she now has gold in her posession.                      */

void getNextMove ( void )
{
  /* TODO */
  /* ...  */
  int randRoomNumber1, randRoomNumber2, direction1, direction2;
  char userDirection;
  int error = 0;
  printf("\nYou are in Room %d\nRoom information : ",currentRoomNo);
  printRoomInformation2(currentRoomNo);
  printf("\n");

  /* creating random 2 rooms */
  randRoomNumber1 = randomIntegerMinMaxUnBiasedExcept1( 0 , numberOfMagicalRooms+1 , currentRoomNo);
  randRoomNumber2 = randomIntegerMinMaxUnBiasedExcept2( 0 , numberOfMagicalRooms+1 , currentRoomNo, randRoomNumber1);

  direction1 = randomIntegerMinMaxUnBiased( 0 , 3 );
  direction2 = randomIntegerMinMaxUnBiasedExcept1( 0, 3, direction1);

  printf("There is a door to your ");
  printDirection(direction1);
  printf("\nAnd, there is another door to your ");
  printDirection(direction2);
  printf("\nWhich one will you choose? : ");

/*  
    case 0 : printf( "NORTH (N) ^" ) ;  break ;
    case 1 : printf( "EAST (E) >"  ) ;  break ;
    case 2 : printf( "SOUTH (S) v" ) ;  break ;
    case 3 : printf( "WEST (W) <"  ) ;  break ;
*/

  do{
    scanf("%c",&userDirection);
    /*getchar();*/
    clearInputBuffer();

    if((userDirection=='N' || userDirection == 'n') && ( (direction1 == 0) || direction2 == 0 ) ){
      error = 0;
      if(direction1 == 0){
        /* go to direction1 */
        currentRoomNo = randRoomNumber1;
      }else if(direction2 == 0){
        /* go to direction2 */
        currentRoomNo = randRoomNumber2;
      }

       printf("Room to your ");
       printDirection(direction1);
       printf(" was Room %d\n",randRoomNumber1);
       printf("Room to your ");
       printDirection(direction2);
       printf(" was Room %d\n",randRoomNumber2);


    }else if((userDirection=='E' || userDirection == 'e') && ( (direction1 == 1) || direction2 == 1 ) ){
      error = 0;
      if(direction1 == 1){
        /* go to direction1 */
        currentRoomNo = randRoomNumber1;
      }else if(direction2 == 1){
        /* go to direction2 */
        currentRoomNo = randRoomNumber2;
      }      

       printf("Room to your ");
       printDirection(direction1);
       printf(" was Room %d\n",randRoomNumber1);
       printf("Room to your ");
       printDirection(direction2);
       printf(" was Room %d\n",randRoomNumber2);


    }else if((userDirection=='S' || userDirection == 's') && ( (direction1 == 2) || direction2 == 2 ) ){

      error = 0;

      if(direction1 == 2){
        /* go to direction1 */
        currentRoomNo = randRoomNumber1;
      }else if(direction2 == 2){
        /* go to direction2 */
        currentRoomNo = randRoomNumber2;
      }      

       printf("Room to your ");
       printDirection(direction1);
       printf(" was Room %d\n",randRoomNumber1);
       printf("Room to your ");
       printDirection(direction2);
       printf(" was Room %d\n",randRoomNumber2);


    }else if((userDirection=='W' || userDirection == 'w') && ( (direction1 == 3) || direction2 == 3 ) ){
      error = 0;
      if(direction1 == 3){
        /* go to direction1 */
        currentRoomNo = randRoomNumber1;
      }else if(direction2 == 3){
        /* go to direction2 */
        currentRoomNo = randRoomNumber2;
      }      

       printf("Room to your ");
       printDirection(direction1);
       printf(" was Room %d\n",randRoomNumber1);
       printf("Room to your ");
       printDirection(direction2);
       printf(" was Room %d\n",randRoomNumber2);

    }else{
      error = 1;
      printf("Incorrect input! Please try again : ");
    }



  }while(error);

  /*printf("room1: %d room2: %d\n",randRoomNumber1, randRoomNumber2);*/
  if(getRoomInformation(currentRoomNo)=='G'){
    printf("You have GOLD now!\n");
    playerFoundGold = 1;
  }

}

/*=================================================================================================================================================*/

/* Checks if the current room that the player is in is the exit room.                                           */
/* If so, checks if the player already has the gold or not, and prints out an appropriate message in each case. */
/* Also checks if the player is in a room with a wumpus.                                                        */
/* If so, informs the player about the unhappy ending of the game.                                              */
/* Returns TRUE if the game ended, otherwise, does not print anything and just returns FALSE.                   */

boolean checkAndPrintGameResult ( void )
{
  /* TODO */
  /* ...  */

/*
#define START        ( 'S'             )  
#define EXIT         ( 'X'             )  
#define GOLD         ( 'G'             )  
#define WUMPUS       ( 'W'             )  
#define EMPTY        ( 'E'  
*/
  char currRoom = getRoomInformation(currentRoomNo);

  if(currRoom == 'X'){
    if(playerFoundGold)
      printf("You are safely out of the dungeon with the GOLD! Congratulations!\n");
    else
      printf("You are safely out of the dungeon, but you did not find the GOLD! Better luck next time!\n");
    return 1;
  }else if(currRoom == 'W'){
    printf("Wumpus is full, and you are in heaven! What a pity!\n");
    return 1;
  }

  return 0;

}

/***************************************************************************************************************************************************/




/* Main Function ***********************************************************************************************************************************/

/* Prints banner.                                                                */
/* Configures the dungeon world.                                                 */
/* Prints the configured world.                                                  */
/* Asks the player to make a move until the game finishes .                      */
/* Prints the game result.                                                       */
/* Prints a goodbye message.                                                     */
/* Prints the number of random numbers that were generated during the game play. */

int main ( void )
{
  /* TODO */
  /* ...  */
  printBanner              () ;
  configureWorld           () ;
  printWorld               () ;
  
  
  /*while(1)
    getNextMove();*/
  
  do
  {
    getNextMove( ) ;
  }
  while ( checkAndPrintGameResult() == FALSE ) ;

  printf( "\nGood game. Have a nice day!\n" ) ;

  printf( "\n%d random numbers were generated during the game play.\n\n" , numberOfRandomNumbersGenerated ) ;

  return 0;
}

/***************************************************************************************************************************************************/
