/* If - Else Example 3*/
#include <stdio.h>

int main()
{ 
  int numb1, numb2;
  printf("Enter two integers to check\n");
  scanf("%d %d", &numb1, &numb2); 
  if (numb1 == numb2) //checking whether two integers are equal.
  	printf("Result: %d = %d", numb1, numb2); 
  else 
  	if (numb1 > numb2) //checking whether numb1 is greater than numb2. 
      printf("Result: %d > %d", numb1, numb2); 
  	else 
      printf("Result: %d > %d", numb2, numb1); 
  return 0; 
} 