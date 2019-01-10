/* Explanations *************************************************************************************************************************************
|
| This file implements CengBook, which is a realistic simulation of a mini social-media application.
|
****************************************************************************************************************************************************/




/* Includes ****************************************************************************************************************************************/

#include "Utilities.h"

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***************************************************************************************************************************************************/




/* Macro Definitions *******************************************************************************************************************************/

#define AUTHOR ( "Selim Temizer" )  /* Author's name */  /* TODO: Replace with your name */

/***************************************************************************************************************************************************/




/* Global Variable Definitions *********************************************************************************************************************/

BookPtr bookPtr ;

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

#if   defined(_WIN16) || defined(_WIN32) || defined(_WIN64)

  char operatingSystem[] = "Windows" ;  /* This is a Windows environment.                            */

#elif defined(__linux__)

  char operatingSystem[] = "Linux"   ;  /* This is a Linux environment (any GNU/Linux distribution). */

#elif defined(__APPLE__)

  char operatingSystem[] = "MacOSX"  ;  /* This is a Mac OS X environment.                           */

#endif

/***************************************************************************************************************************************************/




/* Functions ***************************************************************************************************************************************/

void printUsage ( String applicationName )
{
  NL ;

  printf( "Usage: %s <MaxNumberOfUsers> <MaxUserNameLength> <MaxNumberOfFriendsPerUser>\n\n" , applicationName ) ;
}

/*=================================================================================================================================================*/

void printBanner ( void )
{
  NL ;

  printf( "*******************************************************************************" "\n"          ) ;
  printf( "* CengBook                                                                    *" "\n"          ) ;
  printf( "* by %-72s *"                                                                    "\n" , AUTHOR ) ;
  printf( "*******************************************************************************" "\n"          ) ;
}

/*=================================================================================================================================================*/

void printMenu ( void )
{
  NL ;

  printf( "*******************************************************************************" "\n" ) ;
  printf( "Help                       : Print this menu"                                    "\n" ) ;
  printf( "List                       : List all users"                                     "\n" ) ;
  printf( "Plot                       : Create a plot of CengBook (requires GraphViz)"      "\n" ) ;
  printf( "Quit                       : Exit application"                                   "\n" ) ;
  printf( "-------------------------------------------------------------------------------" "\n" ) ;
  printf( "Register   <user>          : Create a new user and add it to CengBook"           "\n" ) ;
  printf( "Delete     <user>          : Delete user from CengBook"                          "\n" ) ;
  printf( "Find       <user>          : Search CengBook for user, display user information" "\n" ) ;
  printf( "Connect    <user1> <user2> : Add a connection from user1 to user2"               "\n" ) ;
  printf( "Disconnect <user1> <user2> : Remove connection from user1 to user2"              "\n" ) ;
  printf( "Path       <user1> <user2> : Find shortest path from user1 to user2"             "\n" ) ;
  printf( "-------------------------------------------------------------------------------" "\n" ) ;
  printf( "Sort <abc|pop> <asc|desc>  : Sort all users (alphabetically or by popularity)"   "\n" ) ;
  printf( "*******************************************************************************" "\n" ) ;
}

/*=================================================================================================================================================*/

void commandHelp ( void )
{
  /* TODO */
  /* ...  */
	printMenu();
}

/*=================================================================================================================================================*/

void commandList ( void )
{
  /* TODO */
  /* ...  */
	int i;
	NL;
  
  if(bookPtr->numberOfUsers==0)
  	printf("  CengBook is empty\n");
  
  for ( i = 0 ; i < bookPtr->numberOfUsers ; i++ )
  {
    
  printf("  %s",bookPtr->userPointers[i]->name);
  indent(17-strlen(bookPtr->userPointers[i]->name));
	printf(": %d Follower(s) , %d Friend(s)\n",bookPtr->userPointers[i]->numberOfFollowers,bookPtr->userPointers[i]->numberOfFriends);
  }

}

/*=================================================================================================================================================*/

void commandPlot ( void )
{
  /*-----------------------------------------------------------------------------------------------------------------------------------------------*/

  UserPtr   userPtr             , friendPtr              ;
  int       userIndex           , friendIndex            ;
  String    runDotSystemCommand , openImageSystemCommand ;

  FILE    * file = fopen( "CengBook.dot" , "w" )         ;

  /*-----------------------------------------------------------------------------------------------------------------------------------------------*/

  fprintf( file , "digraph CengBook"                                                       "\n"                            ) ;
  fprintf( file , "{"                                                                      "\n"                            ) ;
  fprintf( file , "  graph [label=\"CengBook\\nNumber of users = %d\" , labelloc=t] ;"     "\n\n" , bookPtr->numberOfUsers ) ;
  fprintf( file , "  node  [shape=ellipse , fontcolor=black , color=red , penwidth=2.0] ;" "\n\n"                          ) ;
  fprintf( file , "  edge  [color=blue , penwidth=2.0] ;"                                  "\n\n"                          ) ;

  /*-----------------------------------------------------------------------------------------------------------------------------------------------*/

  for ( userIndex = 0 ; userIndex < bookPtr->numberOfUsers ; userIndex++ )
  {
    userPtr = bookPtr->userPointers[ userIndex ] ;

    fprintf( file , "  %s [label=\"%s\\n%d Friend(s)\\n%d Follower(s)\"] ;\n" ,
             userPtr->name                                                    ,
             userPtr->name                                                    ,
             userPtr->numberOfFriends                                         ,
             userPtr->numberOfFollowers                                       ) ;
  }

  if ( bookPtr->numberOfUsers > 0 )  { fprintf( file , "\n" ) ; }

  /*-----------------------------------------------------------------------------------------------------------------------------------------------*/

  for ( userIndex = 0 ; userIndex < bookPtr->numberOfUsers ; userIndex++ )
  {
    userPtr = bookPtr->userPointers[ userIndex ] ;

    for ( friendIndex = 0 ; friendIndex < userPtr->numberOfFriends ; friendIndex++ )
    {
      friendPtr = userPtr->friendPointers[ friendIndex ] ;

      fprintf( file , "  %s -> %s ;\n" , userPtr->name , friendPtr->name ) ;
    }
  }

  /*-----------------------------------------------------------------------------------------------------------------------------------------------*/

  fprintf( file , "}\n" ) ;
  fclose ( file         ) ;

  /*-----------------------------------------------------------------------------------------------------------------------------------------------*/

  if ( strcmp( operatingSystem , "Windows" ) == 0 )
  {
    runDotSystemCommand    = "CMD /C dot -Tgif CengBook.dot -o CengBook.gif" ;
    openImageSystemCommand = "CMD /C START CengBook.gif"                     ;
  }
  else  /* Assumption: Linux */
  {
    runDotSystemCommand    = "dot -Tgif CengBook.dot -o CengBook.gif"        ;
    openImageSystemCommand = "xdg-open CengBook.gif &"                       ;
  }

  if ( system( runDotSystemCommand    ) ) ;  /* "if" statement is used to eliminate warning about unused return value of "system" call */
  if ( system( openImageSystemCommand ) ) ;  /* "if" statement is used to eliminate warning about unused return value of "system" call */

  NL ;  I2 ;  printf( "Plot prepared\n" ) ;

  /*-----------------------------------------------------------------------------------------------------------------------------------------------*/
}

/*=================================================================================================================================================*/

void commandQuit ( void )
{
  /* TODO */
  /* ...  */
	
	printf("\n  Have a nice day\n\n");
	exit(0);
	
}

/*=================================================================================================================================================*/

void commandRegister ( String userName )
{
  /* TODO */
  /* ...  */



	UserPtr userPtr = getUserPtrByName ( bookPtr , userName );

	unsigned a 	 = getMaxNumberOfUsers          ( );
	unsigned b   = getMaxUserNameLength         ( ) ;
	NL;

	if(strlen(userName)>b)
		printf("  User name is longer than %d characters!\n",b);
	
	else if(bookPtr->numberOfUsers >= a  )
		printf("  CengBook is full, cannot register any new users!\n");

  else if(userPtr!=NULL)
		printf("  User '%s' already registered!\n",userName);
	
	else {bookPtr->userPointers[bookPtr->numberOfUsers++] = allocateUser(userName);
	  printf("  User '%s' registered successfully\n",userName);}

}

/*=================================================================================================================================================*/

void commandDelete ( String userName )
{
  /* TODO */
  /* ...  */

		UserPtr userPtr = getUserPtrByName ( bookPtr , userName );
	  int 	UserIndex  = getUserIndexByPtr( bookPtr , userPtr  ) ;
	  int i=0;

 		if(userPtr==NULL)
		printf("\n  User '%s' not found in CengBook!\n",userName);
 
 		else {
		
			/*printf("%d\n",userPtr->numberOfFriends);*/
 			NL;
 		
 		/*printf("%d\n",bookPtr->numberOfUsers);*/
 			
 		
 		if(userPtr->numberOfFollowers!=0){
 			
 			while(i<userPtr->numberOfFollowers){

 				 printf("  User '%s' is removed from friends of user '%s'\n",userName,userPtr->friendPointers[i]->name);
 				 	
 				 userPtr->friendPointers[i]->numberOfFollowers--;
 				  				
 				 i++;

 		  }
 		}
 		
 			i=0;
 		  
 		  if(userPtr->numberOfFriends!=0){
 			
 			while(i<userPtr->numberOfFriends){
			 			
 			printf("  User '%s' is discounted from friends of user '%s'\n",userName,userPtr->friendPointers[i]->name);
     
    	userPtr->friendPointers[i]->numberOfFriends--;
  		i++; 	
  		}
  		
  	}
 		
     
  		deallocateUser(userPtr);	
  		for(i=0;i<bookPtr->numberOfUsers;i++){

  			if(i>UserIndex)
  				bookPtr->userPointers[i-1]=bookPtr->userPointers[i];
  		}
      
     	bookPtr->numberOfUsers--;
     
  		printf("  User '%s' is deleted from CengBook\n",userName);

		}

}

/*=================================================================================================================================================*/

void commandFind ( String userName )
{
  /* TODO */
  /* ...  */
	
	UserPtr userPtr = getUserPtrByName ( bookPtr , userName );
	NL;
	
 if(userPtr==NULL)
		printf("\n  User '%s' not found in CengBook!\n",userName);
	
	else printUser ( getUserPtrByName ( bookPtr , userName ) );

}

/*=================================================================================================================================================*/

void commandConnect ( String userName1 , String userName2 )
{
  /* TODO */
  /* ...  */
	UserPtr UserPtr1 = getUserPtrByName ( bookPtr , userName1 );
	UserPtr UserPtr2 = getUserPtrByName ( bookPtr , userName2 );
	unsigned c   = getMaxNumberOfFriendsPerUser ( ) ;

	 if(UserPtr1==NULL && UserPtr2==NULL){
		printf("\n  User '%s' not found in CengBook!",userName1);
		printf("\n  User '%s' not found in CengBook!\n",userName2);
	}

	else if(UserPtr1==NULL)
		printf("\n  User '%s' not found in CengBook!\n",userName1);
	
	else if(UserPtr2==NULL)
		printf("\n  User '%s' not found in CengBook!\n",userName2);

	else if (UserPtr1==UserPtr2)
		printf("\n  Connection to self is not allowed!\n");
	else if(UserPtr1->numberOfFriends>=c)
		printf("\n  Friend capacity of user '1' is full!\n");

	else if(isConnected(UserPtr1,UserPtr2))
		printf("\n  User '%s' is already connected to user '%s'!\n",userName1,userName2);
	else{
		printf("\n  User '%s' successfully connected to user '%s'\n",userName1,userName2);
		UserPtr1->friendPointers[UserPtr1->numberOfFriends++] = UserPtr2;
		UserPtr2->numberOfFollowers++;

	}
	
}

/*=================================================================================================================================================*/

void commandDisconnect ( String userName1 , String userName2 )
{
  /* TODO */
  /* ...  */
	UserPtr UserPtr1 = getUserPtrByName ( bookPtr , userName1 );
	UserPtr UserPtr2 = getUserPtrByName ( bookPtr , userName2 );


if(UserPtr1==NULL && UserPtr2==NULL){
		printf("\n  User '%s' not found in CengBook!",userName1);
		printf("\n  User '%s' not found in CengBook!\n",userName2);
	}
	else if(UserPtr1==NULL)
		printf("\n  User '%s' not found in CengBook!\n",userName1);
	
	else if(UserPtr2==NULL)
		printf("\n  User '%s' not found in CengBook!\n",userName2);
	else if(UserPtr1==UserPtr2)
		printf("\n  Disconnecting from self is not allowed!\n");
	else if(removeConnection ( UserPtr1 , UserPtr2 )==TRUE)
		printf("\n  User '%s' successfully disconnected from user '%s'\n",userName1,userName2);
	else 
		printf("\n  User '%s' and user '%s' are not connected!\n",userName1,userName2);

}

/*=================================================================================================================================================*/

void commandPath ( String userName1 , String userName2 )
{
  /* TODO */
  /* ...  */

	
	UserPtr startUserPtr = getUserPtrByName ( bookPtr , userName1 );
	UserPtr targetUserPtr = getUserPtrByName ( bookPtr , userName2 );

	int 	startUserIndex  = getUserIndexByPtr( bookPtr , startUserPtr  ) ;
	int   targetUserIndex = getUserIndexByPtr( bookPtr , targetUserPtr ) ;
	int i;
	UserPtrArray path;
	/*UserPtr userptr;*/

	if(startUserPtr==NULL && targetUserPtr==NULL){
		printf("\n  User '%s' not found in CengBook!",userName1);
		printf("\n  User '%s' not found in CengBook!\n",userName2);
	}
	else if(startUserPtr==NULL)
		printf("\n  User '%s' not found in CengBook!\n",userName1);
	
	else if(targetUserPtr==NULL)
		printf("\n  User '%s' not found in CengBook!\n",userName2);
	

	else if(startUserPtr == targetUserPtr)
		printf("\n  Path to self queried!\n"); 
	else if(shortestPath (bookPtr ,startUserPtr ,targetUserPtr ) == NULL)
		printf("\n  There is no path from user '%s' to user '%s'\n",userName1,userName2);
	
	else{
			
			NL;
			path = shortestPath(bookPtr,startUserPtr,targetUserPtr);	
			i = 0;
		
			if(startUserIndex<targetUserIndex){
				while(startUserIndex<targetUserIndex){

		  		printf("  '%s' -> ",path[i]->name);
					i++;
					startUserIndex++;				
		  	}
		  }
		  else if(startUserIndex>targetUserIndex){

		  	while(startUserIndex>targetUserIndex){

		  	printf("'%s' -> ",path[i]->name);
				i++;
				startUserIndex--;				
		  	}
		  
		  }
				printf("'%s'",userName2);
				NL;
	}

}

/*=================================================================================================================================================*/

void commandSort ( String criterion , String order )
{
  /* TODO */
  /* ...  */
	
	int i ;
	
	ComparatorFunctionPointer compareFunctionPtr;	
 
	if(strcmp(criterion,"abc") == 0 && strcmp(order,"asc") == 0)
	{	
   
		for ( i = 0 ; i < bookPtr->numberOfUsers ; i++ )
  	{
    	compareFunctionPtr = compareByName;
	  	sortBook (bookPtr , compareFunctionPtr,TRUE);		
   
  	}
 		printf("\n  CengBook sorted 'alphabetically' in 'ascending' order\n");
	}

	else	if(strcmp(criterion,"abc") == 0 && strcmp(order,"desc") == 0)
	{	
   
		for ( i = 0 ; i < bookPtr->numberOfUsers ; i++ )
  	{
  		
    	compareFunctionPtr = compareByName;
	  	sortBook (bookPtr , compareFunctionPtr,FALSE);		
   
  	}
 		printf("\n  CengBook sorted 'alphabetically' in 'descending' order\n");
	}


	else	if(strcmp(criterion,"pop") == 0 && strcmp(order,"asc") == 0)
	{	
   
		for ( i = 0 ; i < bookPtr->numberOfUsers ; i++ )
 		{
  		
    	compareFunctionPtr = compareByPopularity;
	  	sortBook (bookPtr , compareFunctionPtr,TRUE);		
   
  }
 			printf("\n  CengBook sorted 'popularity' in 'ascending' order\n");
	}

	else	if(strcmp(criterion,"pop") == 0 && strcmp(order,"desc") == 0)
	{	
   
		for ( i = 0 ; i < bookPtr->numberOfUsers ; i++ )
  	{
  		
    	compareFunctionPtr = compareByPopularity;
	  	sortBook (bookPtr , compareFunctionPtr,FALSE);		
   
  	}
 			printf("\n  CengBook sorted 'popularity' in 'descending' order\n");
	}

	else if(strcmp(criterion,"pop") != 0 && strcmp(criterion,"abc") != 0){

	if(strcmp(order,"asc") != 0 && strcmp(order,"desc") !=0){
	
	printf("\n  Invalid sort criterion '%s'! \n",criterion);
	printf("  Invalid sort order '%s'! \n",order);

	} 
	else   printf("\n  Invalid sort criterion '%s'! \n",criterion);

	}


	else if(strcmp(order,"asc") != 0 && strcmp(order,"desc") !=0){
	printf("\n  Invalid sort order '%s'! \n",order);

	} 


}

/*=================================================================================================================================================*/

void processInput ( String input )
{
  int         i                                                    ;
  int         numberOfTokens = 0                                   ;
  StringArray tokens         = tokenize( input , &numberOfTokens ) ;
  String      command                                              ;

  if ( numberOfTokens < 1 )  { return ; }

  command = tokens[0] ;

  for ( i = 0 ; i < strlen( command ) ; i++ )  { if ( ( command[i] >= 'A' ) && ( command[i] <= 'Z' ) )  { command[i] += 'a' - 'A' ; } }

  if      ( strcmp( command , "help"       ) == 0 )  { if ( numberOfTokens == 1 ) { commandHelp      (                       ) ;  return ; } }
  else if ( strcmp( command , "list"       ) == 0 )  { if ( numberOfTokens == 1 ) { commandList      (                       ) ;  return ; } }
  else if ( strcmp( command , "plot"       ) == 0 )  { if ( numberOfTokens == 1 ) { commandPlot      (                       ) ;  return ; } }
  else if ( strcmp( command , "quit"       ) == 0 )  { if ( numberOfTokens == 1 ) { commandQuit      (                       ) ;  return ; } }
  else if ( strcmp( command , "register"   ) == 0 )  { if ( numberOfTokens == 2 ) { commandRegister  ( tokens[1]             ) ;  return ; } }
  else if ( strcmp( command , "delete"     ) == 0 )  { if ( numberOfTokens == 2 ) { commandDelete    ( tokens[1]             ) ;  return ; } }
  else if ( strcmp( command , "find"       ) == 0 )  { if ( numberOfTokens == 2 ) { commandFind      ( tokens[1]             ) ;  return ; } }
  else if ( strcmp( command , "connect"    ) == 0 )  { if ( numberOfTokens == 3 ) { commandConnect   ( tokens[1] , tokens[2] ) ;  return ; } }
  else if ( strcmp( command , "disconnect" ) == 0 )  { if ( numberOfTokens == 3 ) { commandDisconnect( tokens[1] , tokens[2] ) ;  return ; } }
  else if ( strcmp( command , "path"       ) == 0 )  { if ( numberOfTokens == 3 ) { commandPath      ( tokens[1] , tokens[2] ) ;  return ; } }
  else if ( strcmp( command , "sort"       ) == 0 )  { if ( numberOfTokens == 3 ) { commandSort      ( tokens[1] , tokens[2] ) ;  return ; } }
  else                                               { NL ;  I2 ;  printf( "Invalid command!\n" ) ;                               return ;   }

  /* If we reach here, the user must have provided incorrect number of arguments to a valid command */

  command[0] += 'A' - 'a' ;

  NL ;  I2 ;  printf( "Incorrect number of arguments provided for the command '%s'!\n" , command ) ;
}

/***************************************************************************************************************************************************/




/* Main Function ***********************************************************************************************************************************/

int main ( int argc , char * argv[] )
{
  char input [ MAX_INPUT_LENGTH ] ;

  if ( argc < 4 )  { printUsage( argv[0] ) ;  return 0 ; }

  configureCengBook( /* maxNumberOfUsers          */ atoi( argv[1] ) ,
                     /* maxUserNameLength         */ atoi( argv[2] ) ,
                     /* maxNumberOfFriendsPerUser */ atoi( argv[3] ) ) ;

  bookPtr = allocateBook() ;

  if ( bookPtr == NULL )  { NL ;  printf( "Error: Cannot allocate memory to store CengBook! Exiting!\n\n" ) ;  exit( 0 ) ; }

  printBanner() ;
  printMenu  () ;

  while ( TRUE )
  {
    NL                        ;  /* New line     */
    printf( "[CENGBOOK] > " ) ;  /* Print prompt */

    if ( fgets( input , MAX_INPUT_LENGTH , stdin ) == NULL )  /* Read input line, 'fgets' is safer than 'gets'. */
    {
      /* In the following two lines, the "if" statements surrounding the "freopen" function calls are used to eliminate warnings. */

      if   ( strcmp( operatingSystem , "Windows" ) == 0 )  { if ( freopen( "CON"      , "r" , stdin ) == NULL ) ; }
      else /* Assumption:               Linux          */  { if ( freopen( "/dev/tty" , "r" , stdin ) == NULL ) ; }

      continue ;
    }

    processInput( input ) ;  /* Tokenize and process the input command */
  }

  return 0 ;
}

/***************************************************************************************************************************************************/
