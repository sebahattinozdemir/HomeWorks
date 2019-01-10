/*Math Library Example */
#include <stdio.h>
#include <math.h>

int main()
{ 
  int a, b;
  printf("Enter a negative number:");
  scanf("%d", &a);
  if (a < 0){
    b = pow(a, 2);
    printf("Square of %d is %d\n", a, b);
    printf("Square-root of %d is %d\n", b, sqrt(b));
    if (sqrt(b) == sqrt(pow(a, 2)))
    	printf("You can combine the functions!\n");
  }
  else
  	printf("Input is invalid. Program will be terminated!\n");
  return 0; 
} 