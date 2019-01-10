/* Explanations *************************************************************************************************************************************
|
| The Tic-Tac-Toe board has 9 cells. We will assume that the cell numbering is as follows:
|
|   c0 | c1 | c2
|   ------------
|   c3 | c4 | c5
|   ------------
|   c6 | c7 | c8
|
****************************************************************************************************************************************************/




/* Includes ****************************************************************************************************************************************/

#include "Utilities.h"

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>   /* For standard input/output functions */

/***************************************************************************************************************************************************/




/* Definitions *************************************************************************************************************************************/

#define AUTHOR  ( "Selim Temizer" )  /* Author's name                                   */

#define EMPTY   ( ' '             )  /* Label for empty cells                           */
#define PLAYER1 ( 'X'             )  /* Label for player 1 and cells marked by player 1 */
#define PLAYER2 ( 'O'             )  /* Label for player 2 and cells marked by player 2 */

/***************************************************************************************************************************************************/




/* Type Definitions ********************************************************************************************************************************/

typedef unsigned char boolean ;

/***************************************************************************************************************************************************/




/* Global Variables ********************************************************************************************************************************/

char c0 , c1 , c2 , c3 , c4 , c5 , c6 , c7 , c8 ;  /* Cells of the Tic-Tac-Toe board */

/***************************************************************************************************************************************************/




/* Functions ***************************************************************************************************************************************/

/* Initializes the global variables. */

void initializeGlobalVariables ( void )
{
  /* TODO */
  /* ...  */
	
	c0=' ';
	c1=' ';
	c2=' ';
	c3=' ';
	c4=' ';
	c5=' ';
	c6=' ';
	c7=' ';
	c8=' ';
	
}

/*=================================================================================================================================================*/

/* Prints a banner including the author name. */

void printBanner ( void )
{
  printf(                                                                                   "\n"          ) ;
  printf( "*******************************************************************************" "\n"          ) ;
  printf( "* Tic-Tac-Toe                                                                 *" "\n"          ) ;
  printf( "* by %-72s *"                                                                    "\n" , AUTHOR ) ;
  printf( "*******************************************************************************" "\n"          ) ;
}

/*=================================================================================================================================================*/

/* Prints the current board configuration. */

void printBoard ( void )
{
  /* TODO */
  /* ...  */
 	 printf("\n");
	printf("    Cells  \t\t   Board\n");
	printf(".-----------.\t       .-----------.\n");
	printf("| 0 | 1 | 2 |\t       | %c | %c | %c |\n", c0,c1,c2);
	printf("|-----------|\t       |-----------|\n");
	printf("| 3 | 4 | 5 |\t       | %c | %c | %c |\n", c3,c4,c5);
	printf("|-----------|\t       |-----------|\n");
	printf("| 6 | 7 | 8 |\t       | %c | %c | %c |\n", c6,c7,c8);
	printf("'-----------'\t       '-----------'\n");

	/*
	printf("\t    Board\n");
	printf("\t.-----------.\n");
	printf("\t| %c | %c | %c |\n", c0,c1,c2);
	printf("\t|-----------|\n");
	printf("\t| %c | %c | %c |\n", c3,c4,c5);
	printf("\t|-----------|\n");
	printf("\t| %c | %c | %c |\n", c6,c7,c8);
	printf("\t'-----------'\n");
	*/
}

/*=================================================================================================================================================*/

/* Gets the next move of "player", and marks it on the board.                     */
/* Loops (and asks again) if the input is not valid, or if the cell is not empty. */

void getNextMove ( char player )
{
  /* TODO */
  /* ...  */

	int m;
	printf("\nPlayer %c, enter your next move (0-8) : ", player);
	scanf("%d",&m);

	switch(m){
		case 0:
			if(c0==' ') c0 = player; else { printf("\nCell is not empty! Please try again.\n"); getNextMove(player); }
		break;
		case 1:
			if(c1==' ') c1 = player; else { printf("\nCell is not empty! Please try again.\n"); getNextMove(player); }
		break;
		case 2:
			if(c2==' ') c2 = player; else { printf("\nCell is not empty! Please try again.\n"); getNextMove(player); }
		break;
		case 3:
			if(c3==' ') c3 = player; else { printf("\nCell is not empty! Please try again.\n"); getNextMove(player); }
		break;
		case 4:
			if(c4==' ') c4 = player; else { printf("\nCell is not empty! Please try again.\n"); getNextMove(player); }
		break;
		case 5:
			if(c5==' ') c5 = player; else { printf("\nCell is not empty! Please try again.\n"); getNextMove(player); }
		break;
		case 6:
			if(c6==' ') c6 = player; else { printf("\nCell is not empty! Please try again.\n"); getNextMove(player); }
		break;
		case 7:
			if(c7==' ') c7 = player; else { printf("\nCell is not empty! Please try again.\n"); getNextMove(player); }
		break;
		case 8:
			if(c8==' ') c8 = player; else { printf("\nCell is not empty! Please try again.\n"); getNextMove(player); }
		break;
		default:
			printf("\nIncorrect input! Please try again.\n");
			getNextMove(player);
	}

}

/*=================================================================================================================================================*/

/* Checks if one of the players wins the game, or if the board is full and the game ended with a draw. Prints how the game ended. */
/* Returns TRUE if the game ended, otherwise, does not print anything and just returns FALSE.                                     */

boolean checkAndPrintGameResult ( void )
{
  /* TODO */
  /* ...  */

	if(c0 != ' ' && c0 == c1 && c1 == c2){
		printf("\nPlayer %c WINS (top row)!\n",c0);
		return 1;
	}
	if(c3 != ' ' && c3 == c4 && c4 == c5){
		printf("\nPlayer %c WINS (middle row)!\n",c3);
		return 1;
	}
	if(c6 != ' ' && c6 == c7 && c7 == c8){
		printf("\nPlayer %c WINS (bottom row)!\n",c6);
		return 1;
	}
	if(c0 != ' ' && c0 == c3 && c3 == c6){
		printf("\nPlayer %c WINS (left column)!\n",c0);
		return 1;
	}
	if(c1 != ' ' && c1 == c4 && c4 == c7){
		printf("\nPlayer %c WINS (middle columb)!\n",c1);
		return 1;
	}
	if(c2 != ' ' && c2 == c5 && c5 == c8){
		printf("\nPlayer %c WINS (right column)!\n",c2);
		return 1;
	}
	if(c0 != ' ' && c0 == c4 && c4 == c8){
		printf("\nPlayer %c WINS (primary diagonal)!\n",c0);
		return 1;
	}
	if(c2 != ' ' && c2 == c4 && c4 == c6){
		printf("\nPlayer %c WINS (secondary diagonal)!\n",c2);
		return 1;
	}

	if(c0!=' ' && c1!=' ' && c2!=' ' && c3!=' ' && c4!=' ' && c5!=' ' && c6!=' ' && c7!=' ' && c8!=' '){
		printf("\nDraw!\n");
		return 1;
	}
	
	return 0;
	
}

/***************************************************************************************************************************************************/




/* Main Function ***********************************************************************************************************************************/

/* Initializes the global variables.                                                                                                          */
/* Prints banner.                                                                                                                             */
/* Randomly chooses one of the players to start first.                                                                                        */
/* Asks each player to make a move in turn until the game finishes (prints the board configuration each time before a player makes her move). */
/* Prints the game result.                                                                                                                    */
/* Prints a goodbye message.                                                                                                                  */
/* Prints the number of random numbers that were generated during the game play.                                                              */

int main ( void )
{
  char currentPlayer = ( ( randomIntegerMinMaxUnBiased( 0 , 1 ) == 0 ) ? PLAYER1 : PLAYER2 ) ;

  initializeGlobalVariables() ;
  printBanner              () ;
  printBoard               () ;

  do
  {
    getNextMove( currentPlayer ) ;
    printBoard (               ) ;

    if   ( currentPlayer == PLAYER1 )  { currentPlayer = PLAYER2 ; }
    else                               { currentPlayer = PLAYER1 ; }
  }
  while ( checkAndPrintGameResult() == FALSE ) ;

  printf( "\nGood game. Have a nice day!\n" ) ;

  printf( "\n%d random numbers were generated during the game play.\n\n" , numberOfRandomNumbersGenerated ) ;

  return 0 ;
}

/***************************************************************************************************************************************************/
