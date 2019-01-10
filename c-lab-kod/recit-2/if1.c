/* If - Else Example 1*/
#include <stdio.h>

int main()
{
  int a, b;
  printf("Please enter a and b respectively");
  scanf("%d %d", &a, &b);
  if (!(a || b) || (a && b))
  	printf("Result is 1");
  else
  	printf("Result is 0");
}