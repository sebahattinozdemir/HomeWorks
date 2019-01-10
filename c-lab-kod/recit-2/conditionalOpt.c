/* Conditional Operators */
#include <stdio.h>

int main()
{
   char feb;
   int days;
   printf("Enter l if the year is leap year otherwise enter 0: ");
   scanf("%c",&feb);
   days=(feb=='l')?29:28;
   /*If test condition is true, days will be equal to 29. */
   /*If test condition is false, days will be equal to 28. */ 
   printf("Number of days in February = %d",days);
   return 0;
}